#PBS -l nodes=1:ppn=16
#PBS -M pratsriv@iu.edu
#PBS -m abe
#PBS -N job_myprog


export OMP_NUM_THREADS=1
cd /N/u/pratsriv/Karst/parallelDijkstra 
./a.out file10 1024

