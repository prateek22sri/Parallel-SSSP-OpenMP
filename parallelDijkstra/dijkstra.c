#include "randomGraphGen.h"

int main(int argc, char *argv[]) {

	struct timeval start, end;
	srand(time(NULL));
	// argument validation
	if (argc != 3) {
		printf("Error : Usage : ./a.out file_name num_vertices\n");
		exit(1);
	}
	int numVertices = atoi(argv[2]);
	printf("num vertices = %d\n",numVertices);
	//int* graph = reader("/N/u/pratsriv/BigRed2/HPCProject/file11",&numVertices);

	int *graph = (int *)malloc(sizeof(int) * numVertices * numVertices);
	if(graph==NULL){
		printf("Error: Malloc Failure");
		exit(1);
	}

	printf("begining the reader\n");
	reader(argv[1],numVertices,graph);
	printf("ending the reader\n");

	int *shortestPath = (int*)malloc(sizeof(int*) * numVertices);
	if(shortestPath==NULL){
		printf("Error: Malloc Failure");
		exit(1);
	}
	// count the word count of file

	// print_graph(numVertices, graph);
	gettimeofday(&start, NULL);
	int i;
	printf("begining the execution");
	execute_algorithm(numVertices, graph, shortestPath);
	gettimeofday(&end, NULL);
	double delta = ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;
	printf("Time taken by the algorithm is %lf\n", delta);
	//print_results(numVertices,shortestPath);
	free(graph);
	free(shortestPath);

	return 0;
}
