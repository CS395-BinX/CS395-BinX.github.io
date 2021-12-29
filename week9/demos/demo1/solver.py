#!/usr/bin/python3
from z3 import *
one = Int('a')
two = Int('b')
three = Int('c')
four = Int('d')
s = Solver()

#add x < 20 constraint
s.add(one < 20)
s.add(two < 20)
s.add(three < 20)
s.add(four < 20)

#copy programs hashing math
s.add(3*(one*three) == 96)
s.add((two%four)-1 == 1)
s.add(three + 2*four == 18)
s.add(four*four + one*one*one == 89)

#show answer
print(s.check())
print(s.model())
