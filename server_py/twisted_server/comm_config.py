
from controller import file_controller

PROTOCOL_MESSAGE_FUNC_CONFIG = {
    "011E01":{
        "func": file_controller.comm_file_req,
        "event": bytes([0x01, 0x1e, 0x01]),
    },
    "011E02": {
        "func": file_controller.comm_file_data_req,
        "event": bytes([0x01, 0x1e, 0x02]),
    }
}
