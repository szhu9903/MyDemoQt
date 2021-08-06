from twisted.internet import reactor
from twisted.internet.protocol import Protocol
from twisted.internet.protocol import Factory
from twisted_server.help.req_controller import generic_data_pars
from twisted_server.help.thread_func import query_client_pool


client_pool = []

class GenericProtocol(Protocol):

    def __init__(self, factory):
        self.factory = factory
        self.client_host = None
        self.client_port = None

    def connectionMade(self):
        self.client_host = self.transport.getPeer().host
        self.client_port = self.transport.getPeer().port

    def dataReceived(self, data: bytes):
        req_message = {}
        req_message["PROTOCOL"] = self
        req_message["recv_data"] = data
        reactor.callFromThread(generic_data_pars, req_message)

    def connectionLost(self, reason):
        client_pool.remove(reason)
        self.transport.loseConnection()

class GenericFactory(Factory):
    # protocol = GenericProtocol
    def buildProtocol(self, addr):
        newClient = GenericProtocol(self)
        client_pool.append(newClient)
        return newClient

def create_thread_func():
    reactor.callInThread(query_client_pool, client_pool)

if __name__ == '__main__':
    reactor.listenTCP(8899,GenericFactory())
    reactor.suggestThreadPoolSize(10)
    create_thread_func()
    reactor.run()


