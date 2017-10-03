#include <stdio.h>
#include <stdlib.h>
 
struct node {
    int val;
    int weight;
    struct node * next;
};
 
struct edge {
    int weight;
    int u, v;   // edge de u ---> v
};
 
// Adiciona um edge
struct node * addEdge(struct node * head, int num, int weight)
{
    struct node * p = (struct node *) malloc(sizeof(struct node));
 
    p->val = num;
    p->next = head;
    p->weight = weight;
    head = p;
 
    return p;
}
 
// Envia uma entrada na fila de prioridade
void enqueue(struct edge heap[], int size, struct edge value)
{
    heap[size] = value;
 
    int i = size;
    struct edge temp;
 
    while (i >= 1) {
        if (heap[i / 2].weight > heap[i].weight) {
            temp = heap[i / 2];
            heap[i / 2] = heap[i];
            heap[i] = temp;
 
            i = i / 2;
        } else {
            break;
        }
    }
}
 
void heapify(struct edge heap[], int size, int index)
{
    int i = index;
    struct edge temp;
 
    while ((2 * i) < size) {
        if ((2 * i) + 1 >= size) {
            if (heap[i].weight > heap[2 * i].weight) {
                temp = heap[i];
                heap[i] = heap[2 * i];
                heap[2 * i] = temp;
 
                break;
            }
        }
 
        if (heap[i].weight > heap[2 * i].weight || heap[i].weight > heap[2 * i + 1].weight) {
            if (heap[2 * i].weight <= heap[(2 * i) + 1].weight) {
                temp = heap[2 * i];
                heap[2 * i] = heap[i];
                heap[i] = temp;
 
                i = 2 * i;
            } else if (heap[2 * i].weight > heap[(2 * i) + 1].weight) {
                temp = heap[(2 * i) + 1];
                heap[(2 * i) + 1] = heap[i];
                heap[i] = temp;
 
                i = (2 * i) + 1;
            }
        } else {
            break;
        }
    }
}
 
// Deleta uma entrada na fila de prioridade
void deleteNode(struct edge heap[], int size, int index)
{
    struct edge temp = heap[index];
 
    heap[index] = heap[size - 1];
    heap[size - 1] = temp;
 
    int i = index;
    --size;
 
    heapify(heap, size, i);
}
 
// Retorna o elemento com
// Prioridade mínima e o exclui
struct edge extractMin(struct edge heap[], int size)
{
    struct edge min = heap[0];

    deleteNode(heap, size, 0);

    return min;
}
 
// Função do Algoritmo PRIM
void prim(struct node * adjacencylist[], int vertices, int edges, int startVertex, struct node * MST[])
{
    int current = startVertex, newVertex;
    int visited[vertices + 1];
    struct node * temp;
    struct edge var;
    struct edge priorityQueue[2 * edges];
    int queueSize = 0;
 
    int i;
 
    for (i = 0; i <= vertices; ++i) {        // Iniciando
        visited[i] = 0;
    }
 
    i = 0;
 
    while (i < vertices) {
        if (visited[current] == 0) {            // Se o nó atual não for visitado
            visited[current] = 1;        // Marque como visitado
            temp = adjacencylist[current];
 
            while (temp != NULL) {
                var.u = current;
                var.v = temp->val;
                var.weight = temp->weight;
 
                if (!visited[var.v]) {
                    //Se a borda conduz a um vértice não visitado somente, então faça queueSize
                    enqueue(priorityQueue, queueSize, var);
                    ++queueSize;
                }
 
                temp = temp->next;
            }
 
            var = extractMin(priorityQueue, queueSize);  
            --queueSize;
 
            newVertex = var.v;
            current = var.u;
 
            if (visited[newVertex] == 0) {
                // Se ele conduz a um vértice não visitado, adicione-o ao MST
                MST[current] = addEdge(MST[current], newVertex, var.weight);
                MST[newVertex] = addEdge(MST[newVertex], current, var.weight);
            }
 
            current = newVertex;
            ++i;
        } else {
            var = extractMin(priorityQueue, queueSize);
            --queueSize;
            newVertex = var.v;
            current = var.u;
 
            if (visited[newVertex] == 0) {
                MST[current] = addEdge(MST[current], newVertex, var.weight);
                MST[newVertex] = addEdge(MST[newVertex], current, var.weight);
            }
 
            current = newVertex;
        }
    }
}
 
int main()
{
    int vertices, edges, i, j, v1, v2, weight;

    char url[]="input.txt";
    int valor;
    
    FILE *arq;

    arq = fopen(url, "r");

    if(arq == NULL)
        printf("Erro, nao foi possivel abrir o arquivo\n");
 
    printf("Enter the Number of Vertices -\n");
    fscanf(arq,"%d\n", &vertices);
    printf("%d\n", vertices);
 
    printf("Enter the Number of Edges -\n");
    fscanf(arq,"%d\n", &edges);
    printf("%d\n", edges);
 
    struct node * adjacencyList[vertices + 1];
    struct node * MST[vertices + 1];
 
    for (i = 0; i <= vertices; ++i) {
        adjacencyList[i] = NULL;
        MST[i] = NULL;
    }
 
    for (i = 1; i <= edges; ++i) {
        fscanf(arq,"%d %d %d\n", &v1, &v2, &weight);
        printf("%d %d %d\n", v1, v2, weight);
        adjacencyList[v1] = addEdge(adjacencyList[v1], v2, weight);       //Adiciona edge v1 ---W---> v2
        adjacencyList[v2] = addEdge(adjacencyList[v2], v1, weight);       //Adiciona edge v2 ---W---> v1
    }
 
    // Imprime a Lista de Adjacencia
    printf("\nAdjacency List -\n\n");
    for (i = 1; i <= vertices; ++i) {
        printf("adjacencyList[%d] -> ", i);
 
        struct node * temp = adjacencyList[i];
 
        while (temp != NULL) {
            printf("%d (%d) -> ", temp->val, temp->weight);
            temp = temp->next;
        }
 
        printf("NULL\n");
    }
 
    int startVertex;
 
    printf("\nEnter a Start Vertex - ");
    fscanf(arq,"%d\n", &startVertex);
    printf("%d", startVertex);
    prim(adjacencyList, vertices, edges, startVertex, MST);
 
    // Imprime MST na tela
    printf("\nMinimum Spanning Tree -\n\n");
    for (i = 1; i <= vertices; ++i) {
        printf("MST[%d] -> ", i);
 
        struct node * temp = MST[i];
 
        while (temp != NULL) {
            printf("%d (%d) -> ", temp->val, temp->weight);
            temp = temp->next;
        }
 
        printf("NULL\n");
    }
 
    fclose(arq);
    return 0;
}
