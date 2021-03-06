//
//  LogParse.c
//  LogParse
//
//  Created by haibo zhang on 12/22/13.
//  Copyright (c) 2013 DaFeng. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include "bstring/bstraux.h"
#include "bstring/bstrlib.h"
//#include "dict/dict.h"
#include "LogParse.h"

/**
 * 解析一条日志
 60.217.237.225 119.188.122.17 [31/Jul/2013:21:49:40 +0800] "GET /m3u8/jiangxi/desc.m3u8?tag=live&video_type=m3u8&stream_id=jiangxi&useloc=0&clipsize=128&clipcount=10&f_ulrg=0&cmin=3&cmax=10&path=0&geo=CN-19-248-2&cipi=456010935&tmn=1375277573&pnl=709,751,225&sign=live_ipad HTTP/1.0" 200 777 0.000 "-" "GStreamer souphttpsrc libsoup/2.32.2" "-" owninneragent HIT
**/

const char* ptime_mons_keys[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
const char* ptime_mons_vals[] = {"01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12"};




char* getPtime(char* datestr){
  dict * ptimeMap;
  ptimeMap = dict_new();
    //[31/Jul/2013:21:49:40
//    char day[3], year[5], mon[3], hour[3], min[3]; 
//    char ptime[12];
//    char mon_tmp[3];
//    int mon_eq;
//    day[0] = datestr[1];
//    day[1] = datestr[2];
//    day[2] = "\0";
//    mon_tmp[0] = datestr[4];
//    mon_tmp[1] = datestr[5];
//    mon_tmp[2] = datestr[6];
//    mon_tmp[3] = "\0";
//    for (int i=0; i < 4; i++){
//        year[i] = datestr[ 8 + i]; 
//    };
//    year[5] = "\0";
//    for (int i=0; i < 12; i++){
//        //mon_eq = strcmp (const char *s1, const char *s2);
//    }
//    
//  return "201312232100";
};


char* getValueFromQuery(char* query, char* key){
    /*
     * tag=live&video_type=m3u8&stream_id=jiangxi&useloc=0
     * 比如 输入 tag 返回 live
    */

};

char* getMaliu(char* maliu){
    //计算得到码流值

};

char* getIdc(char* serverip){
    //计算得到IDC值

};

char* getLocation(char* userip){
    //得到用户地区信息isp area


};

char* getYewu(dict* logMap){
    //根据规则得到业务值

};


dict* logHandle(const char* base_log){
    /*
    * 解析日志返回一个完整的dict数据
    */
    bstring log = bfromcstr(base_log);
    struct bstrList * log_left_fields;
    struct bstrList * log_right_fields;
    struct bstrList * log_right_fields_http;
    struct bstrList * log_right_fields_ua;
    struct bstrList * log_right_fields_hit;
    char string_split_marker[] = "GET";
    char string_split_right[] = "\" ";
    char string_split_right_http[] = " ";
    char string_split_right_ua[] = "\" \"";
    char z = ' ';
    char * empty = "NULL";
    bstring log_left, log_right;
    bstring bstring_split_marker= bfromcstr(string_split_marker);
    bstring bstring_split_right = bfromcstr(string_split_right);
    bstring bstring_split_right_http = bfromcstr(string_split_right_http);
    bstring bstring_split_right_ua = bfromcstr(string_split_right_ua);
    dict *d;
 
    d = dict_new();
    struct bstrList *log_split_GET = bsplitstr(log, bstring_split_marker);
    if (log_split_GET -> qty > 2){
    return NULL;
    }
    else{
        log_left = log_split_GET ->entry[0];
        log_right = log_split_GET ->entry[1];
    }
    log_left_fields = bsplit(log_left, ' ');
    dict_add(d, "serverip", bstr2cstr(log_left_fields->entry[0], z));
    dict_add(d, "userip", bstr2cstr(log_left_fields->entry[1], z));
    dict_add(d, "date", bstr2cstr(log_left_fields->entry[2], z));
    //char *date =  getPtime(bstr2cstr(log_left_fields->entry[2],z));
    dict_add(d, "ptime", "");
    log_right_fields = bsplitstr(log_right,bstring_split_right);
    char *request_path = bstr2cstr(log_right_fields->entry[0], z);
    printf(">>>\n\n");
    dict_add(d, "path", request_path);
    log_right_fields_http = bsplitstr(log_right_fields->entry[1],bstring_split_right_http);


    if (log_right_fields_http->mlen >= 3){
        dict_add(d, "httpcode", bstr2cstr(log_right_fields_http->entry[0], z));
        dict_add(d, "contlength", bstr2cstr(log_right_fields_http->entry[1], z));
        dict_add(d, "loadtime", bstr2cstr(log_right_fields_http->entry[2], z));
    } else {
        dict_add(d, "httpcode", empty); 
        dict_add(d, "contlength", empty);
        dict_add(d, "loadtime", empty); 
    }
    if (log_right_fields_http->mlen >= 4){
        dict_add(d, "refer", bstr2cstr(log_right_fields_http->entry[3], z));
    } else{
        dict_add(d, "refer", empty);
    }

    log_right_fields_ua = bsplitstr(log_right, bstring_split_right_ua);
    if (log_right_fields_ua->qty >=2 ){
        int ua_index = log_right_fields_ua->qty - 2;
        dict_add(d, "ua", bstr2cstr(log_right_fields_ua->entry[ua_index], z));
    } else{
        dict_add(d, "ua", empty);
    }

    log_right_fields_hit = bsplitstr(log_right, bstring_split_right_http);
    int hit_index = log_right_fields_hit->qty - 3;
    if (log_right_fields_hit->qty > 3){
        dict_add(d, "hit", bstr2cstr(log_right_fields_hit->entry[hit_index], z));
    } else{
        dict_add(d, "hit", empty);
    }
  
  
    bdestroy(log);
//
    bstrListDestroy(log_left_fields);
    bstrListDestroy(log_right_fields);
    bstrListDestroy(log_right_fields_http);
    bstrListDestroy(log_right_fields_ua);
    bstrListDestroy(log_right_fields_hit);
//  char string_split_marker[] = "GET";
//  char string_split_right[] = "\" ";
//  char string_split_right_http[] = " ";
//  char string_split_right_ua[] = "\" \"";
//  char z = ' ';
//  char * empty = "NULL";
    bdestroy(log_left);
    bdestroy(log_right);
    bdestroy(bstring_split_marker);
    bdestroy(bstring_split_right);
    bdestroy(bstring_split_right_http);
    bdestroy(bstring_split_right_ua);
    return d;
};


