#!/bin/bash
#Author: timger <yishenggudou@gmail.com>
#weibo <http://t.sina.com/zhanghaibo>
#@yishenggudou http://twitter.com/yishenggudou
gcc -Wall tests_log_parse.c  ../bstring/bstrlib.c ../bstring/bstraux.c ../LogParse.c -o testhandlog
