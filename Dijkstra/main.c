#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

int printSolution(int dist[], int size){
	for (int i = 0; i < size; i++)
		printf("Vertice[%d] \t\t Distancia = %d\n", i, dist[i]);
}

int distanciaMinima(int dist[], bool sptSet[], int size)
{
	int min = INT_MAX, indice_min;
  
	for (int v = 0; v < size; v++)
		if (sptSet[v] == false && dist[v] <= min)
         	min = dist[v], indice_min = v;
  
  	 return indice_min;
}
  
void dijkstra(int **graph, int src, int size){
	int dist[size];   
	bool sptSet[size]; 

	for (int i = 0; i < size; i++)
		dist[i] = INT_MAX, sptSet[i] = false;
  
	dist[src] = 0;
  
	for (int contador = 0; contador < size-1; contador++)
	{
		int u = distanciaMinima(dist, sptSet, size);
  
		sptSet[u] = true;

		for (int v = 0; v < size; v++)
		{
			if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u]+graph[u][v] < dist[v])
			{
				dist[v] = dist[u] + graph[u][v];
			}	
		}	
    }
	printSolution(dist, size);
}
  

int main(int argc, char** argv)
{
	
	if (argc < 1)
	{
		exit(EXIT_FAILURE);
	}
	int size, i, j;
	scanf("%d", &size);

	int ** graph = (int**) malloc(sizeof(int*)*size);
	
	for(i = 0; i < size ; i++)
	{
		graph[i] = (int*) malloc(sizeof(int)*size);
		for(j= 0; j < size ; j++)
		{
			if(i == j)
			{
				graph[i][j] = 0;
			}
			else if(i > j)
			{
				graph[i][j] = graph[j][i];
			}
			else
			{
				scanf("%d", &graph[i][j]);
			}
		}
		
	}
	dijkstra(graph, 0, size);
	return 0;		
}