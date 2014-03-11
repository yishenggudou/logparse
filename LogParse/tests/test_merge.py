#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#    Copyright 2011 timger
#    +Author timger
#    +Gtalk&Email yishenggudou@gmail.com
#    +Msn yishenggudou@msn.cn
#    +Weibo @timger http://t.sina.com/zhanghaibo
#    +twitter @yishenggudou http://twitter.com/yishenggudou
#    Licensed under the MIT License, Version 2.0 (the "License");
import os
import sys
DIR_PATH = os.path.abspath(os.path.dirname(os.path.realpath(__file__)))
if not DIR_PATH in sys.path:
    sys.path.append(DIR_PATH)
parent_dir = os.path.abspath(os.path.join(DIR_PATH, '..'))
if not parent_dir in sys.path:
    sys.path.append(parent_dir)
from  NumPyMerge import Merge

@profile
def test():
    rule=[(0, None), (1, None), (2, None),
        (3, None), (4, None), (5, None),
        (6, sum), (7, len), (8, sum),
        ]
    """
    201403101215,GD-GZ-CNNET,crc,Guangdong,10.1012key,live_ipad,ts,null,null,940188,1,0,0,300,222.50.66.230,0,path,4.094,jiangsu,200,122.72.124.15:80,null,nu,null,live,null
201403101215,GD-GZ-CNNET,cmcc,Guangdong,10.1012key,null,m3u8,null,null,1097,1,0,0,300,223.73.172.65,0,path,0.125,cctvnew,200,122.72.124.15:80,null,nu,null,live,null
201403101215,GD-GZ-CNNET,crc,Guangdong,1.101_new,letv,ts,null,null,335016,1,0,0,300,123.88.114.160,0,path,0.395,,200,122.72.124.15:80,null,nu,1,letv,0
201403101215,GD-GZ-CNNET,letv-in,GD-GZ-CNNET,10.1012key,live_tv,m3u8,null,null,1187,1,0,0,300,122.72.124.13,0,path,0.124,cctvmusic,200,122.72.124.15:80,null,nu,null,live,null"""
    p = '/data/tmp/cdn.20140226-1135.201402261152_f2f4cb4c-7a3e-499d-92c7-ee6a47bce882_convered_split.201402261135'
    p = "/letvlogroot/buff/2014/201403/20140310/cdn.201403101220.1319e1d4-133a-4a91-bca4-2f79c526f4cd._convered_split.201403101215"
    mp = os.path.join(DIR_PATH, 'test.merged')
    merge = Merge(rule)
    with open(p) as f:
        for line in f:
            _ = line.strip().split(',')
            vv = ','.join([_[0], _[1], _[2],
                        _[3], _[4], _[5],
                        _[9], _[10], _[17]
                        ])
            merge.add(vv)
    merge.to_file(mp)

test()
