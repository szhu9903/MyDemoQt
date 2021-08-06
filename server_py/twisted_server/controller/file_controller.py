import random
import time
import random
import struct

# 临时存放数据
file_data = {}

# 解析文件信息 011E01
def comm_file_req(message):
    recv_data = message.get("recv_data")
    file_len, = struct.unpack("!Q", recv_data[:8]) # 接收到的总文件大小
    file_name_len, = struct.unpack('!I', recv_data[8:12])
    file_name = recv_data[12:file_name_len + 12].decode("utf-8")
    # 生成上传文件的KEY
    file_key = random.randint(1000,9990)
    while True:
        if file_data.get(file_key):
            file_key = random.randint(100, 9999)
        else:
            break
    # 应答消息
    res_data = bytes([1])
    res_data += struct.pack("!H", file_key)
    # 创建临时存储空间
    file_data[file_key] = {"data_len": file_len, "file_name":file_name, "data": ""}
    message["PROTOCOL"].transport.write(res_data)

# 接收文件内容
def comm_file_data_req(message):
    try:
        # 获取文件存储空间
        recv_data = message['recv_data']
        file_key, = struct.unpack('!H', recv_data[:2])
        fileData = file_data[file_key]
        # 解析数据
        recv_file_data_len, = struct.unpack('!I', recv_data[2:6])
        fileData['data'] += recv_data[6:recv_file_data_len + 6].decode("utf-8")
        # 待接收文件大小-本次接收的文件大小
        fileData['data_len'] -= recv_file_data_len
        print(fileData['data_len'])
        if fileData['data_len'] <= 0:
            # 保存文件
            with open("CMakeCache.txt", "w") as file:
                file.write(fileData['data'])
            del file_data[file_key] # 保存文件后清除缓存
        time.sleep(0.5)
        message["PROTOCOL"].transport.write(bytes([1]))
    except Exception as Err:
        print("接收文件失败：%s " % str(Err))
        message["PROTOCOL"].transport.write(bytes([0]))


