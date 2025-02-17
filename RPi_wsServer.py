import websocket
import time
import rel

def on_message(ws, message):
    print(f"Sunucudan gelen mesaj: {message}")

def on_error(ws, error):
    print(f"Hata: {error}")

def on_close(ws, close_status_code, close_msg):
    print("Bağlantı kapandı")
    ws.close()

def on_open(ws):
    print("Bağlantı açıldı")
    
    def run():
        while True:
            try:
                ws.send("ON")
                time.sleep(2)
                
                ws.send("OFF")
                time.sleep(2)
              
                ws.send("TEST")
                time.sleep(2)
            except Exception as e:
                print(f"Hata oluştu: {e}")
                break
    
    import threading
    threading.Thread(target=run).start()

def main():
    websocket.enableTrace(True)
    ws = websocket.WebSocketApp("ws://192.168.1.12:81",
                              on_open=on_open,
                              on_message=on_message,
                              on_error=on_error,
                              on_close=on_close)
    
    ws.run_forever(dispatcher=rel)
    rel.signal(2, rel.abort)
    rel.dispatch()

if __name__ == "__main__":
    main()
