import json
import struct
from twisted_server import comm_config

def generic_data_pars(req_message):
    try:
        recv_data = req_message.get("recv_data")
        # 解析消息类型
        frame_type, cmd_type, cmd_code = struct.unpack("!3B", recv_data[:3])
        req_message['data_len'] = struct.unpack('!I', recv_data[3:7])
        req_message['recv_data'] = recv_data[7:]
        # TODO 验证消息类型
        # 执行响应的处理
        message_type = "%02X%02X%02X" % (frame_type, cmd_type, cmd_code)
        comm_config.PROTOCOL_MESSAGE_FUNC_CONFIG[message_type]["func"](req_message)
    except Exception as Err:
        print("消息解析失败 %s", str(Err))


