SCALE = 10;
edgefactor = 500;
NBFS = 64;

rand ("seed", 103);

ij = kronecker_generator (SCALE, edgefactor);

tic;
G = kernel_1 (ij);
save file10 G;
