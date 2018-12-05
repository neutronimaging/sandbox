#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import numpy as np
import pybindtest as pt

# add

print("Adding 3+9 using the add function is = 9",pt.add(3,6)==9.0)

# adding using adder class

adder = pt.adder(1,2)

print("Adding initialized values 1,2 = 3", adder.sum()==3.0)

adder.setValues(3,4)
print("Adding set values 3,4 = 7", adder.sum()==7.0)

# Testing Pet class

p=pt.Pet('molly')

print("pet is molly", p.getName()=='molly')

p.setName("pelle")
print("pet is pelle", p.getName()=='pelle')

# Testing numpy array adding

a = np.ones((10,3))
b = np.ones((10,3)) *4
c= pt.add_arrays(a,b)
good=True
for e in np.nditer(c):
    if e!=5.0:
        good=False

print("element check all==5 ",good)
