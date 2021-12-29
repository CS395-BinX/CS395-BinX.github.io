import angr
from claripy import *
import IPython

proj = angr.Project("crackme",load_options={'auto_load_libs':False})
num1 = BVS("num1",16)
num2 = BVS("num2",16)
num3 = BVS("num3",16)
num4 = BVS("num4",16)
state = proj.factory.entry_state(argc=5,args=["crackme",num1,num2,num3,num4])
simgr = proj.factory.simgr(state)

simgr.explore(find=0x0040126d)
solver = simgr.found[0].solver
print(solver.eval(num1,cast_to=bytes))
print(solver.eval(num2,cast_to=bytes))
print(solver.eval(num3,cast_to=bytes))
print(solver.eval(num4,cast_to=bytes))
IPython.embed()
