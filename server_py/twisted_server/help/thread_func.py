
import time

def query_client_pool(client_pool):
    while True:
        print("当前连接数：%d" % len(client_pool))
        client_pool_message_list = ["[%s-%s]" % (client.client_host, client.client_port) for client in client_pool]
        client_pool_message = "-".join(client_pool_message_list)
        print(client_pool_message)
        time.sleep(10)
