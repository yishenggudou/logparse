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
import numpy as np
from uuid import uuid4
import leveldb
from collections import defaultdict
DIR_PATH = os.path.abspath(os.path.dirname(os.path.realpath(__file__)))
NAME_FILE = os.path.relpath(__file__)


class Merge(object):
    """
    使用Numpy和LevelDB 合并数据
    最大限度少使用内存
    len(key) == 40 则 40*10000000/1000/1000 = 400M
    转换成py对象需要空间在G级别
    该用numpy的mmap和leveldb 0内存使用
    """

    def __init__(self, mergerule=(), use_shelve=False,):
        self.arrays = {}
        self.seq = ','
        self.mergerule = mergerule
        self.tmp_root = '/letvlogroot/buff/'
        self.buffsize = 100000
        self.buff_paths = set()
        self.keyindex = filter(lambda x: not x[1], self.mergerule)
        self.mergeindex = filter(lambda x: x[1], self.mergerule)
        self.keys_index = map(lambda x: x[0], self.keyindex)
        self.values_index = map(lambda x: x[0], self.mergeindex)
        self.leveldb_path = os.path.join(self.tmp_root, str(uuid4()) + '.db')
        self.keydb = leveldb.LevelDB(self.leveldb_path)
        self.glob_readlines = 0
        self.npmmaps = []
        self.merge_funs = []
        for i, f in self.mergeindex:
            if f in [len, 'len']:
                new_f = lambda x, y: x + 1
            elif f in [sum, 'sum']:
                new_f = lambda x, y: x + np.float64(y)
            elif f in ['and']:
                new_f = lambda x, y: np.int(x) and np.int(y)
            elif f in ['or']:
                new_f = lambda x, y: int(x) or int(y)
            self.merge_funs.append((i, new_f))
        self.count = defaultdict(int)
        self.count['buffsize'] = self.buffsize

    @property
    def np_path(self):
        path = os.path.join(self.tmp_root, str(uuid4()) + '.np.mmap')
        msg = "GEN NEW PATH: " + path
        print msg
        return path

    def npmmap(self):
        shape = (self.buffsize, len(self.mergeindex))
        n = np.memmap(self.np_path,
                      dtype='float64',
                      mode='w+',
                      shape=shape)
        return n

    def get_index_map(self):
        if (len(self.npmmaps) > 0) and (self.npmmaps[-1]['nowrow'] < self.buffsize):
            obj = self.npmmaps[-1]
            obj['nowrow'] = obj['nowrow'] + 1
            return len(self.npmmaps) - 1, obj
        else:
            obj = {'nowrow': 0}
            obj['np'] = self.npmmap()
            self.npmmaps.append(obj)
            self.count['npmmaps'] += 1
            print 'add new mmap'
            return len(self.npmmaps) - 1, obj

    def add(self, line):
        fields = line.strip().split(',')
        key = ','.join([fields[i[0]] for i in self.keyindex])
        values = [(fields[i[0]], i[1]) for i in self.merge_funs]
        try:
            index_map = self.keydb.Get(key)
            np_index, now_row = index_map.split(':')
            np_index, now_row = int(np_index), int(now_row)
        except:
            np_index, now_row = self.get_index_map()
            now_row = now_row['nowrow']
            key_val = "{0}:{1}".format(np_index, now_row)
            self.keydb.Put(key, key_val)
        #print key, np_index, now_row
        #print self.npmmaps
        np_row = self.npmmaps[np_index]['np'][now_row]
        try:
            for index, v in enumerate(values):
                val, m_fun = v
                np_row[index] = m_fun(np_row[index], val)
        except:
            self.count['adderrorlines'] += 1
        self.count['addlines'] += 1

    def write_row(self, key, key_val):
        np_index, now_row = key_val.split(':')
        np_index = int(np_index)
        now_row = int(now_row)
        keys = key.split(',')
        values = self.npmmaps[np_index]['np'][now_row]
        line_fields = range(len(self.mergerule))
        for i, v in zip(self.keys_index, keys):
            line_fields[i] = v
        for i, v in zip(self.values_index, values):
            line_fields[i] = v
        return ','.join([str(i) for i in line_fields])

    def to_file(self, path):
        print '>>> to file'
        for fp in self.npmmaps:
            fp['np'].flush()
        with open(path, 'w') as f:
            for key, key_val in self.keydb.RangeIter():
                line = self.write_row(key, key_val)
                f.write(line + '\n')

    def clean(self, *args, **kwargs):
        from shutil import rmtree
        try:
            rmtree(self.leveldb_path)
            msg = 'Remove {0} \n'.format(self.leveldb_path)
        except:
            pass
        for fp in self.npmmaps:
            path = os.path.abspath(fp['np'].filename)
            msg += "Remove {0} \n".format(path)
            os.remove(path)
        print msg
        print self.count

    clear = clean
    __exit__ = clean
    __clear__ = clean
    __del__ = clean
