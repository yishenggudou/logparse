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

"""
"""

import os
import sys
import numpy as np
import pandas as pd

DIR_PATH = os.path.abspath(os.path.dirname(os.path.realpath(__file__)))
NAME_FILE = os.path.relpath(__file__)

import numpy as np

class Merge(object):

    def __init__(self, mergerule=(), use_shelve=False,):
        self.arrays = {}
        self.seq = ','
        self.mergerule = mergerule
        self.buffsize = 100000
        self.buff_paths = set()
        self.keyindex = [i[0]  for i in zip(range(len(self.mergerule)),self.mergerule) if (not i[1][1])]
        self.mergeindex = [i[0]  for i in zip(range(len(self.mergerule)),self.mergerule) if (i[1][1])]
        self.glob_readlines = 0


    def init_np_array(self):
        self.buff_readline = 0
        self.array_keys = []
        for i in self.mergeindex:
            self.arrays[i] = self.create_np_mmap()

    def create_np_mmap(self):
        from uuid import uuid4
        import os
        path = os.path.join('/letvlogroot/tmp/', 'np_array_' + str(uuid4()))
        fpr = np.memmap(path,
                        dtype='float64',
                        mode='w+',
                        shape=(1, self.buff_size))
        self.buff_paths.add(path)
        return fpr

    def merge_buff(self):
        pd_obj = {
                  'mergekey': np.array(self.array_keys),
                 }
        for i in self.mergekey:
            key = 'field_' + str(i)
            pd_obj[key] = self.arrars[i]


    def add(self, line):
        line = line.strip()
        fields = line.split(self.seq)
        key = ''
        for i in self.keyindex:
            key += fields[i] + ','
        self.array_keys.append(key)
        for i in self.mergekey:
            self.arrays[i][self.buff_readline] = fields[i]
        self.buff_readline += 1
        if self.buff_readline >= self.buff_size:
            pass
