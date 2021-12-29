import angr
import IPython

proj = angr.Project("crackme",load_options={'auto_load_libs':False})
state = proj.factory.entry_state()
sim = proj.factory.simgr(state)

sim.explore(find=0x00401250)
print(sim.found[0].posix.stdin.concretize())
IPython.embed()
