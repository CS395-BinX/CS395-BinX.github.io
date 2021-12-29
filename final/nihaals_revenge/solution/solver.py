from z3 import *
from pwn import *

x = Int("x")# handles the first four digits of the key
z = "GM3R" # middle four digits, always the same. (found by using ghidra)
y = Int("y")# handles the last four digits of the key

s = Solver()
#add constraints taken from ghidra
s.add(y > 100)
s.add(x-(y/3) == 380)
s.add(y % 3 == 1)

print(s.check())
print(s.model())

#Output from terminal:
#sat
#[y = 103, x = 414]

# to win: 
#./cd_validator 414 GM3R 103
