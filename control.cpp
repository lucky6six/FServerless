#include "hv/HttpServer.h"
#include <iostream>
#include <string>
#include "config.h"
#include "FuncFactory.h"
#include "FuncScheduler.h"
using namespace std;

int main() {
    HttpService router;
    // FuncFactory* factory = new FuncFactory();
    // factory->functionCreate(funcName,code);
    // // curl -v http://ip:port/
    // router.Static("/", "./html");
    // // curl -v http://ip:port/proxy/get
    // router.Proxy("/proxy/", "http://httpbin.org/");
    // // curl -v http://ip:port/ping
    // router.GET("/invoke", [](HttpRequest* req, HttpResponse* resp) {
    //     return resp->String("ret");
    // });
    // // curl -v http://ip:port/data
    // router.GET("/data", [](HttpRequest* req, HttpResponse* resp) {
    //     static char data[] = "0123456789";
    //     return resp->Data(data, 10 /*, false */);
    // });
    // // curl -v http://ip:port/paths
    // router.GET("/paths", [&router](HttpRequest* req, HttpResponse* resp) {
    //     return resp->Json(router.Paths());
    // });

    // curl -v http://ip:port/get?env=1
    router.GET("/invoke", [](HttpRequest* req, HttpResponse* resp) {
        // cout<<req->query_params["name"]<<endl;
        // cout<<req->query_params["para"]<<endl;
        static FuncScheduler* scheduler = new FuncScheduler();
        string funcName = req->query_params["name"];
        string para = req->query_params["para"];
        string ret = scheduler->invokeFunc(funcName,para);
        resp->json["origin"] = req->client_addr.ip;
        resp->json["url"] = req->url;
        resp->json["args"] = req->query_params;
        resp->json["headers"] = req->headers;
        resp->json["body"] = ret;
        return 200;
    });

    // // curl -v http://ip:port/echo -d "hello,world!"
    // router.POST("/echo", [](const HttpContextPtr& ctx) {
    //     return ctx->send(ctx->body(), ctx->type());
    // });

    // curl -v http://ip:port/echo -d "hello,world!"
    router.POST("/create", [](const HttpContextPtr& ctx) {
        static FuncFactory* factory = new FuncFactory();
        string funcName,code;
        string body = ctx->body();
        string ret;
        int i = 0;
        if(body!=""){
            funcName = body.substr(0,body.find(' '));
            body.erase(0,body.find(' ')+1);
            code = body;
            cout<<funcName<<"1    1"<<code<<endl;
        }
        //createfunc name 
        ret = factory->functionCreate(funcName,code);
        // delete factory;
        //type == 100 -> TEXT
        return ctx->send(ret,CONTENT_TYPE_TEXT);
    });

    // // curl -v http://ip:port/user/123
    // router.GET("/user/{id}", [](const HttpContextPtr& ctx) {
    //     hv::Json resp;
    //     resp["id"] = ctx->param("id");
    //     return ctx->send(resp.dump(2));
    // });
    http_server_t server;
    server.port = PORT;
    server.service = &router;
    http_server_run(&server);
    return 0;
}