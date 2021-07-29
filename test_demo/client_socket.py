import socket
import struct

HOST_NAME = "127.0.0.1"
PORT_NAME = 6666

def unpack_str(data):
    name_end_index = data.index(bytes([0]))
    return data[:name_end_index].decode("utf-8"), data[name_end_index + 1:]

def main():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
        client_socket.connect((HOST_NAME, PORT_NAME))
        while True:
            data = input("name : ")
            client_socket.send(data.encode("utf-8"))
            recv_data = client_socket.recv(1024)
            # 解析数据
            data_len, id = struct.unpack("!2H", recv_data[:4])
            name,recv_data = unpack_str(recv_data[4:])
            # age
            age, = struct.unpack("!H", recv_data[:2])
            address, recv_data = unpack_str(recv_data[2:])
            number, = struct.unpack("!f", recv_data)

            print(" id->%d \n name->%s \n age->%d \n address->%s \n number->%.2f" % (id, name, age, address, number))

main()
