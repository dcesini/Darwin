#!/usr/bin/python

from ctypes import cdll

lib = cdll.LoadLibrary('./libctest.so')

#class world(object):
#    def __init__(self):
#        self.obj = lib.world_new()
#
#    def stats(self):
#        lib.Foo_stats(self.obj.stats())

#Once you have that you can call it like

#f = Foo()
#f.stats() #and you will see "Hello" on the screen
