//
//  LogParse.h
//  LogParse
//
//  Created by haibo zhang on 12/22/13.
//  Copyright (c) 2013 DaFeng. All rights reserved.
//

#ifndef LogParse_LogParse_h
#define LogParse_LogParse_h

/*
 * URL storage
 * 60.217.237.225 119.188.122.17 [31/Jul/2013:21:49:40 +0800] "GET /m3u8/jiangxi/desc.m3u8?tag=live&video_type=m3u8&stream_id=jiangxi&useloc=0&clipsize=128&clipcount=10&f_ulrg=0&cmin=3&cmax=10&path=0&geo=CN-19-248-2&cipi=456010935&tmn=1375277573&pnl=709,751,225&sign=live_ipad HTTP/1.0" 200 777 0.000 "-" "GStreamer souphttpsrc libsoup/2.32.2" "-" owninneragent HIT
 */

const char* base_log_keys[] = {
                            "ptime",
                            "idc",
                            "isp",
                            "area",
                            "yewu",
                            "consumer",
                            "filetype",
                            "pla",
                            "device",
                            "bandwidth",
                            "requests",
                            "slowrequest",
                            "users",
                            "maliu",
                            "userip",
                            "hit",
                            }

const char* base_bw_keys[] = {    
                            "qs",
                            "http_code",
                            }

const char* converted_keys[] = {
                            "path",
                            "loadtime_str",
                            "stream_id",
                            "http_code",
                            "serverip",
                            "ua",
                            "qs",
                            "termid",
                            "tag",
                            }

#endif
