import numpy as np
from sys import argv
from write_pview_file import *

def read_amrex_particle_file(fname):

    infile=open(fname,'r')
    line=infile.readline()
    nparticles=int(line.split()[0])

    particle_pos=np.zeros((nparticles,3))

    for i in range(nparticles):
        spltline=infile.readline().split()
        particle_pos[i][0]=float(spltline[0])
        particle_pos[i][1]=float(spltline[1])
        particle_pos[i][2]=float(spltline[2])

    return(particle_pos,nparticles)


#main
filenum_min=int(argv[1])
filenum_max=int(argv[2])
file_prefix=argv[3]

nfiles=filenum_max-filenum_min+1
ncdata=np.array([])
for i in range(nfiles):
    filename=file_prefix+"%5.5d"%(filenum_min+i)
    (ppos,npart)=read_amrex_particle_file(filename)
    write_paraview_file_particles(filename+".vtp",ppos,ncdata)


