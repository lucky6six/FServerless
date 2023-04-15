# import inter
# def hello(a) :
#     return "Hello "+ a

# def caller(a) :
#     return inter.call(hello(a))

# if __name__=="__main__":
#     ret = inter.call(hello("lz"))
#     print(ret)

from http.server import BaseHTTPRequestHandler, HTTPServer
from urllib.parse import urlparse, parse_qs

class MyHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # 解析URL中的查询字符串
        query = parse_qs(urlparse(self.path).query)

        # 获取参数值
        name = query.get('para', [''])[0]

        # 构造响应
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()
        # self.wfile.write(bytes("<html><head><title>Python HTTP Server</title></head>", "utf-8"))
        # self.wfile.write(bytes("<body><p>Hello, %s!</p>" % name, "utf-8"))
        self.wfile.write(bytes("wow %s " % para, "utf-8"))

if __name__ == '__main__':
    # 启动HTTP服务器
    server_address = ('', 8000)
    httpd = HTTPServer(server_address, MyHandler)
    print('Starting server...')
    httpd.serve_forever()
