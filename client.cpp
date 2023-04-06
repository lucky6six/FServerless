#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <iostream>
#include <stdio.h>
#include <curl/curl.h>
#include "config.h"


using namespace std;

int main(int argc,char **argv)
{
    if(argc < 3){
        cout<<"too short para"<<endl;
        return 0;
    }
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    if(curl) {
        char url[100]="";
        char buff[2048]="";
        char* baseurl = BASEURL;
        strcat(url,baseurl);
        char* tmp;
        // cout<<url<<endl;
        // cout<<buff<<endl;
        if(!strcmp(argv[1],"create")){
            strcat(url,argv[1]);
            //funcName
            strcat(buff,argv[2]);
            tmp = " ";
            strcat(buff,tmp);
            //code
            strcat(buff,argv[3]);
            curl_easy_setopt(curl, CURLOPT_URL, url);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, buff);
            res = curl_easy_perform(curl);
            if(res != CURLE_OK) {
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            }
        }else if(!strcmp(argv[1],"invoke")){
            strcat(url,argv[1]);
            tmp = "?name=";
            strcat(url,tmp);
            //funcName
            strcat(url,argv[2]);
            tmp = "&para=";
            strcat(url,tmp);
            //para
            strcat(url,argv[3]);
            // cout<<url<<endl;
            curl_easy_setopt(curl, CURLOPT_URL, url);
            res = curl_easy_perform(curl);
            if(res != CURLE_OK) {
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            }
        }else{
            cout<<"error commond"<<endl;
            return 0;
        }
        curl_easy_cleanup(curl);
    }
    return 0;
}
