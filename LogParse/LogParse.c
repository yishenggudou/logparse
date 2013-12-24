//
//  LogParse.c
//  LogParse
//
//  Created by haibo zhang on 12/22/13.
//  Copyright (c) 2013 DaFeng. All rights reserved.
//

#include <stdio.h>
#include "bstring/bstraux.h"
#include "bstring/bstrlib.h"
#include "LogParse.h"

/**
 * 解析一条日志
 60.217.237.225 119.188.122.17 [31/Jul/2013:21:49:40 +0800] "GET /m3u8/jiangxi/desc.m3u8?tag=live&video_type=m3u8&stream_id=jiangxi&useloc=0&clipsize=128&clipcount=10&f_ulrg=0&cmin=3&cmax=10&path=0&geo=CN-19-248-2&cipi=456010935&tmn=1375277573&pnl=709,751,225&sign=live_ipad HTTP/1.0" 200 777 0.000 "-" "GStreamer souphttpsrc libsoup/2.32.2" "-" owninneragent HIT
**/
struct parsed_log * handle_log(const char *base_log){
  bstring log = bfromcstr(base_log);
  char string_split_marker[]="GET";
  bstring bstring_split_marker= bfromcstr(string_split_marker);
  struct parsed_log *log_obj;
  struct bstrList *log_split_GET = bsplitstr(log, bstring_split_marker);
  
  

}


struct parsed_query * handle_request(const char *request){



}




