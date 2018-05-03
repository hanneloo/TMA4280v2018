#!/bin/bash
#PBS -N hannelore
#PBS -q training
#PBS -l walltime=00:15:00
#PBS -W group_list=itea_lille-tma4280
#PBS -A itea_lille-tma4280
#PBS -l select=2:ncpus=20:mpiprocs=20:ompthreads=8
#PBS -j oe

cd $PBS_O_WORKDIR


module load GCC/6.4.0-2.28

module load OpenMPI/2.1.2

KMP_AFFINITY="granularity=fine ,compact"


for n in 2 4 8 16 32 64 128 256 512 1024 16384 
do
	mpirun -np 36 ./poisson $n 8
done
