import urllib.request

def call(func,para) :
    url = "http://173.50.0.1:16666/call?name=" + func + "&para=" + para
    response = urllib.request.urlopen(url)
    ret = (response.read().decode('utf-8'))
    print(ret)
    return ret
