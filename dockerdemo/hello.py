from http.server import BaseHTTPRequestHandler, HTTPServer
from urllib.parse import urlparse, parse_qs
import Fhttp

class MyHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # 解析URL中的查询字符串
        query = parse_qs(urlparse(self.path).query)

        # 获取参数值
        para = query.get('para', [''])[0]

        # 构造响应
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()
        # self.wfile.write(bytes("<html><head><title>Python HTTP Server</title></head>", "utf-8"))
        # self.wfile.write(bytes("<body><p>Hello, %s!</p>" % name, "utf-8"))
        # para = Fhttp.call(para)
        self.wfile.write(bytes("hello %s " % para, "utf-8"))

if __name__ == '__main__':
    # 启动HTTP服务器
    server_address = ('', 8000)
    httpd = HTTPServer(server_address, MyHandler)
    print('Starting server...')
    httpd.serve_forever()