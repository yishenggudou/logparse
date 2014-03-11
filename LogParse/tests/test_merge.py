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

def test():
    rule=[(0, None), (1, None), (2, None),
        (3, None), (4, None), (5, None),
        (6, sum), (7, len), (8, sum),
        ]
    p = '/data/tmp/cdn.20140226-1135.201402261152_f2f4cb4c-7a3e-499d-92c7-ee6a47bce882_convered_split.201402261135'
    mp = p + '.merged'
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
