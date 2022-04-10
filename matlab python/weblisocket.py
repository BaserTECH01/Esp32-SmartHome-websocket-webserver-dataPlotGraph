import websocket 

def Connect():
    ws = websocket.WebSocket()
    ws.connect("ws://192.168.1.43:81")
    data=ws.recv()
    data=data.replace("{","").replace("}","").replace(":",",").replace('"',"")
    arrdata=data.split(',')
    ws.close()    
    return arrdata
 