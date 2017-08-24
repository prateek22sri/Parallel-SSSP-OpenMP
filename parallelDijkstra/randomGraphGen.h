#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <limits.h>
#include <string.h>
#include <assert.h>
#include <omp.h>

#define MAX_WEIGHT 10
#define INFINITY INT_MAX

char **str_split(char *a_str, char a_delim);

int flip() {
	int i = rand() % 2;
	if (i == 0)
		return 0;
	else
		return 1;
}

// void generate_adj_matrix(int N, int *graph) {

//     int i, j;

//     for (i = 0; i < N; i++) {
//         for (j = 0; j < N; j++) {
//             graph[(i * N) + j] = flip();
//         }
//     }

//     for (i = 0; i < N; i++) {
//         for (j = 0; j < N; j++) {
//             if (graph[(i * N) + j])
//                 graph[(i * N) + j] = rand() % MAX_WEIGHT + 1;
//             else
//                 graph[(i * N) + j] = INT_MAX;
//         }
//     }

//     for (i = 0; i < N; i++)
//         graph[(i * N) + i] = 0;

//     return;
// }

// void writer(int N, int *adj_mat) {
//     int i, j;
//     FILE *f;
//     f = fopen("/home/pratsriv/Desktop/HPCProject/a1.txt", "w");

//     for (i = 0; i < N; i++) {
//         for (j = 0; j < N; j++) {
//             if (j + 1 < N)
//                 fprintf(f, "%d|", adj_mat[(i * N) + j]);
//             else
//                 fprintf(f, "%d", adj_mat[(i * N) + j]);
//         }

//         if (i + 1 < N)
//             fprintf(f, "\n");
//     }
//     fclose(f);
// }

void print_graph(int N, int *graph) {

	int i, j;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++)
			if (j + 1 < N)
				if (graph[(i * N) + j] != INT_MAX)
					printf("%d|", graph[(i * N) + j]);
				else
					printf("INF|");

			else if (graph[(i * N) + j] != INT_MAX)
				printf("%d", graph[(i * N) + j]);
			else
				printf("INF");
		printf("\n");
	}
}

void reader(char *filename, int N, int *graph) {
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char **cols;
	int numVertices;
	int i, j, cnt = 0;

	fp = fopen(filename, "r");
	if (fp == NULL)
		exit(EXIT_FAILURE);

	int rownum = 0;
	while ((read = getline(&line, &len, fp)) != -1) {
		++rownum;
		// printf("%s", line);
		if (rownum == 5 && cnt == 0) {
			cols = str_split(line, ':');
			if (cols) {
				if (cols[1][0] == ' ')
					memmove(cols[1], cols[1] + 1, strlen(cols[1]));
				numVertices = atoi(cols[1]);
			}

		if(numVertices != N){
			printf("Error : The number of vertices does not match\n");
			exit(1);
		}

            // printf("%d\n", numVertices);

            for (i = 0; i < numVertices; i++) {
                for (j = 0; j < numVertices; j++) {
                    if (i == j)
                        //graph[(i * numVertices) + j] = 0;
                        *(graph + i*numVertices + j) = 0;
                    else
                        //graph[(i * numVertices) + j] = INT_MAX;
                        *(graph + i*numVertices + j) = INT_MAX; 
                }
            }
			
		            cnt = 1;
			        } else if (rownum > 6) {
			//            printf("%s",line);
			            char* pch;
			            pch = strtok (line," ");
			            int count=0;
			            while (pch != NULL)
			            {
			//                printf ("%s\n",pch);
			                if(count==0)
			                    i=atoi(pch)-1;
			                else if(count==1)
			                    j=atoi(pch)-1;
			                pch = strtok (NULL, " ");
			                count++;
			            }
			            graph[(i*numVertices)+j] = rand() % MAX_WEIGHT + 1;
			}
	}
	fclose(fp);
}

// void readGraph(char *filename, int numVertices, int *graph) {
//     FILE *fp;
//     int i,j;
//     char *line = NULL;
//     size_t len = 0;
//     ssize_t read;
//     fp = fopen(filename, "r");
//     char **raggedGraph;
//     raggedGraph = (char **)malloc(sizeof(char *)*numVertices);
//     if(raggedGraph==NULL){
//         printf("Error: Malloc Failure");
//         exit(1);
//     }

//     char **cols;
//     if (fp == NULL)
//         exit(EXIT_FAILURE);
//     int rownum = 0;
//     while ((read = getline(&line, &len, fp)) != -1) {
//         rownum++;
//         // printf("Retrieved line of length %lld:\n", (long long) read);
//         raggedGraph[rownum] = (char *)malloc(sizeof(char) * read);
//         if(raggedGraph[rownum]==NULL){
//             printf("Error: Malloc Failure");
//             exit(1);
//         }
//         raggedGraph[rownum] = line;
//         cols = str_split(raggedGraph[rownum], '|');
//         if (cols){
//             for (i = 0; *(cols + i); i++){
//                 graph[((rownum-1)*numVertices)+i] = atoi(cols[i]);
//             }
//         }
//     }

//     long long numEdges = 0;
//     for (i = 0; i < numVertices; i++) {
//         for (j = 0; j < numVertices; j++) {
//             if ((graph[(i * numVertices) + j] != 0) && (graph[(i * numVertices) + j] != INT_MAX))
//                 numEdges++;
//         }
//     }

//     printf("Number of edges in the graph is %lld\n", numEdges);


//     // free raggedGraph
// //    for (i = 0; i < numVertices; i++){
// //        int *tmp = raggedGraph[i];
// //        free(tmp);
// //    }
// //    free(raggedGraph);

//     fclose(fp);
// }

//http://stackoverflow.com/questions/9210528/split-string-with-delimiters-in-c
char **str_split(char *a_str, char a_delim) {
	char **result = 0;
	size_t count = 0;
	char *tmp = a_str;
	char *last_comma = 0;
	char delim[2];
	delim[0] = a_delim;
	delim[1] = 0;

	/* Count how many elements will be extracted. */
	while (*tmp) {
		if (a_delim == *tmp) {
			count++;
			last_comma = tmp;
		}
		tmp++;
	}
	/* Add space for trailing token. */
	count += last_comma < (a_str + strlen(a_str) - 1);
	/* Add space for terminating null string so caller
	   knows where the list of returned strings ends. */
	count++;
	result = (char**)malloc(sizeof(char *) * count);
	if (result) {
		size_t idx = 0;
		char *token = strtok(a_str, delim);
		while (token) {
			assert(idx < count);
			*(result + idx++) = strdup(token);
			token = strtok(0, delim);
		}
		assert(idx == count - 1);
		*(result + idx) = 0;
	}
	return result;
}

void relax(int s, int e, int *shortestPath,
		int *visited, int *local_dist,
		int *local_ind) {
	*local_dist = INFINITY;
	*local_ind = -1;
	int i;
	for (i = s; i <= e; i++) {
		if ((visited[i] == 0) && (shortestPath[i] < *local_dist)) {
			*local_dist = shortestPath[i];
			*local_ind = i;
		}
	}
	return;
}

void update_shortest_path(int numVertices, int s, int e, int glob_ind,
		int *visited, int *graph,
		int *shortestPath) {
	int i;
	for (i = s; i <= e; i++) {
		if (visited[i] == 0) {
			if (graph[(glob_ind * numVertices) + i] < INFINITY) {
				if (shortestPath[glob_ind] + graph[(glob_ind * numVertices) + i] < shortestPath[i]) {
					shortestPath[i] = shortestPath[glob_ind] + graph[(glob_ind * numVertices) + i];
				}
			}
		}
	}
	return;
}

void execute_algorithm(int numVertices, int *graph, int *shortestPath) {
	int i, j;
	// initialize the visited nodes
	int *visited = (int*)malloc(sizeof(int)*numVertices);
	if(visited==NULL){
		printf("Error: Malloc Failure");
		exit(1);
	}

	visited[0] = 1;
	for (i = 1; i < numVertices; i++) {
		visited[i] = 0;
	}

	// initialize the shortest path matrix with adjacent distances
	for (i = 0; i < numVertices; i++) {
		shortestPath[i] = graph[(0 * numVertices) + i];
	}

	int numprocs;
	int glob_dist = INFINITY, glob_ind;

#pragma omp parallel
	{
		int local_dist, local_index;
		int rank = omp_get_thread_num();
		numprocs = omp_get_num_threads();

		int s = rank * numVertices / numprocs;
		int e = (rank + 1) * numVertices / numprocs - 1;

		// for dijkstra iterations would be n-1
		int it;
		for (it = 1; it < numVertices; it++) {

#pragma omp single
			{
				glob_dist = INFINITY;
				glob_ind = -1;
			}

			relax(s, e, shortestPath, visited, &local_dist, &local_index);


#pragma omp critical
			{
				if (local_dist < glob_dist) {
					glob_dist = local_dist;
					glob_ind = local_index;
				}
			}

# pragma omp single
			{
				if (glob_ind != -1) {
					visited[glob_ind] = 1;
				}
			}

# pragma omp barrier
			if (glob_ind != -1) {
				update_shortest_path(numVertices, s, e, glob_ind, visited, graph, shortestPath);
			}

#pragma omp barrier
		}
	}

	free(visited);
	return;
}

void print_results(int numVertices, int *shortestPath) {
	int i;
	printf("Distances from the Node 0:\n");
	for (i = 0; i < numVertices; i++) {
		if (shortestPath[i] == INT_MAX)
			printf("%d\tINF\n", i);
		else
			printf("%d\t%d\n", i, shortestPath[i]);
	}
}

// [1] http://www.cse.buffalo.edu/faculty/miller/Courses/CSE633/Ye-Fall-2012-CSE633.pdf
// [2] https://people.sc.fsu.edu/~jburkardt/c_src/dijkstra_openmp/dijkstra_openmp.html
