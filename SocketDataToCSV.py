import websocket
import csv
import json
x_value = 0
brd1V = 0
brd1C = 0

with open('data.csv', 'w',newline='') as csv_file:
        fieldnames = ["x_value", "brd1V", "brd1C"]
        csv_writer = csv.DictWriter(csv_file, fieldnames=fieldnames)
        csv_writer.writeheader()



while True:
    ws = websocket.WebSocket()
    ws.connect("ws://192.168.1.43:81")
    #ws.send("Hello, Server")
    print(ws.recv())
    data=ws.recv()
    #data=data.replace("{","").replace("}","").replace(":",",").replace('"',"")
    #arrdata=data.split(',')
    arrdata=json.loads(data)

    with open('data.csv', 'a',newline='') as csv_file:
        csv_writer = csv.DictWriter(csv_file, fieldnames=fieldnames)
        info = {
            "x_value": x_value,
            "brd1V": arrdata["brd1V"],
            "brd1C": arrdata["brd1C"]
        }
        #print(info)
        csv_writer.writerow(info)
        print(arrdata["brd1V"], arrdata["brd1C"])
 
    x_value += 1
    ws.close()
