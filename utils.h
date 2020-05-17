#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define initCapacity 4

typedef int TCost; // Cost(weight) of path to a specific node
typedef int Item;

typedef struct ListNode {
    int key;
    struct ListNode *next;
    struct ListNode *prev;
} ListNode;

typedef struct List {
    ListNode *head;
} List;

typedef List Stack;
typedef List Queue;

typedef struct TNode {
	int v;              // Actor index
	TCost c;            // Cost of the edge associated with the nodes
	struct TNode *next; // Link to the next node in the list
} TNode, *ATNode;

typedef struct {
    char *name;
    int id;
} Actor;

typedef struct {
	int nn;             // Number of nodes in the graph
    int nCapacity;      // Capacity of adjancency list
    char *title;        // Movies title.
    Actor *actorList;   // Actor list.
    int actorSize;      // Actor list size.
    int actorCapacity;  // Actor list capacity.
	ATNode *adl;        // Adjacency list (TNode**)
} TGraphL;

typedef struct MinHeapNode {
    int v;
    int d;
} MinHeapNode;


typedef struct MinHeap {
    int size;
    int capacity;
    int *pos;
    MinHeapNode **elem;
} MinHeap;

typedef struct {
    int sizeMovies;      // Will be number of movies
    TGraphL **graph;     // List of graphs
    char **names;        // 2 names we must check degree of kinship for
} Data;


int min(int a, int b);


List* createList(void);
void destroyList(List* list);
int isListEmpty(List *list);
int listSize(List *list);

Stack* createStack(void);
void destroyStack(Stack* stack);
void push(Stack* stack, int key);
void pop(Stack* stack);
int isStackEmpty(Stack* stack);
int top(Stack* stack);

Queue* createQueue(void);
void destroyQueue(Queue* queue);
void enqueue(Queue* queue, int key);
void dequeue(Queue* queue);
int isQueueEmpty(Queue *queue);
int front(Queue* queue);


MinHeapNode* newHeapNode(int v, int d);
MinHeap* newMinHeap(int capacity);
void minHeapSwap(MinHeapNode** a, MinHeapNode** b);
void siftDown(MinHeap* h, int idx);
int isEmpty(MinHeap* h);
MinHeapNode* removeMin(MinHeap* h);
void siftUp(MinHeap* h, int v, int d);
int isInMinHeap(MinHeap *h, int v);
void freeMinHeap(MinHeap *h);


TGraphL* createGraphAdjList(int numberOfNodes, char *title);
void addGraphNode(TGraphL* g1, int id1, TGraphL *g2, int id2);
void addEdgeList(TGraphL* graph, int v1, int v2);
void removeEdgeList(TGraphL* graph, int v1, int v2);
void removeNodeList(TGraphL* graph, int v);
List* dfsRecursive(TGraphL* G, int s);
void destroyGraphAdjList(TGraphL* graph);

void createActorList(TGraphL *graph);
/**
 * Returns 1 if actor with given name exists in graph.
 * Returns 0 otherwise.
 */
int actorExists(TGraphL *graph, char *name);

/**
 * Adds actor with give name and id into graph, if it doesn't exists already.
 * Returns 1 if added actor to graph.
 * Returns 0 otherwise.
 */
int addActor(TGraphL *graph, char *name, int id);

/**
 * Returns NULL if actor doesn't exist in graph.
 */
char* getActorName(TGraphL *graph, int id);

/**
 * Returns -1 if actor doesn't exist in graph.
 */
int getActorId(TGraphL *graph, char *name);

/**
 * Returns 0 on success.
 */
int readInput1(char *inputPath, Data *data);

/**
 * Returns 0 on success.
 */
int readInput2(char *inputPath, Data *data);

void printGraph(TGraphL *graph);

/**
 * Return 1 if graphs intersect.
 * Return 0 otherwise.
 */
int intersect(TGraphL *g1, TGraphL *g2);

/**
 * Merge graph g2 into g1.
 */
void merge(TGraphL *g1, TGraphL *g2);
int comparator1(const void *p, const void *q);
int comparator2(const void *p, const void *q);

/**
 * Return 0 if successful.
 */
int writeOutput1(char *outputPath, int maxProduction, int maxProductionIdx,
                Data *data);

/**
 * Return 0 if successful.
 */
int writeOutput2(char *outputPath, int kinship);

/**
 * Return 0 if successful.
 */
int writeOutput3(char *outputPath, int **deck, int *decks, Data *data,
                int **parent, int totalGraphs);

/**
 * Finds minimum distance between s and f.
 */
int dijkstra(TGraphL *g, int s, int f);

/**
 * Some kind of dfs.
 */
void explore(TGraphL *g, int u, int *d, int *low, int *parent, char *color,
            int **deck, int *decks, int time);
void destroyData(Data **data);



int min(int a, int b) {
    return (a < b) ? a : b; 
}

List* createList(void){
	List* newList = (List*) malloc(sizeof(List));
	newList->head = (ListNode*) malloc(sizeof(ListNode));
	newList->head->next = newList->head->prev = newList->head;
	return newList;
}

void destroyList(List* list){
	ListNode* it = list->head->next;
	while(it != list->head){
		ListNode* aux = it;
		it = it->next;
		free(aux);
	}
	free(list->head);
	free(list);
}

int isListEmpty(List *list){
	return list->head->next == list->head;
}

int listSize(List *list) {
    if (list == NULL) return 0;
    int size = 0;
    ListNode *iter = list->head->next;
    while (iter != list->head) {
        size++;
        iter = iter->next;
    }
    return size;
}

Stack* createStack(void){
	return createList();
}

void destroyStack(Stack* stack){
	destroyList(stack);
}

void push(Stack* stack, int key){
	ListNode* newNode = (ListNode*) malloc(sizeof(ListNode));
	newNode->key = key;

	newNode->next = stack->head->next;
	newNode->prev = stack->head;

	stack->head->next->prev = newNode;
	stack->head->next = newNode;
}

void pop(Stack* stack){
	ListNode* aux = stack->head->next;
	stack->head->next = stack->head->next->next;
	stack->head->next->prev = stack->head;
	free(aux);
}

int isStackEmpty(Stack* stack){
	return isListEmpty(stack);
}

int top(Stack* stack){
	return stack->head->next->key;
}

Queue* createQueue(void){
	return createList();
}

void destroyQueue(Queue* queue){
	destroyList(queue);
}

void enqueue(Queue* queue, int key){
	push(queue,key);
}

void dequeue(Queue* queue){
	ListNode* aux = queue->head->prev;
	queue->head->prev = queue->head->prev->prev;
	queue->head->prev->next = queue->head;
	free(aux);
}

int isQueueEmpty(Queue *queue){
	return isListEmpty(queue);
}

int front(Queue* queue){
	return queue->head->prev->key;
}



MinHeapNode* newHeapNode(int v, int d) {
    MinHeapNode *n = (MinHeapNode*) malloc(sizeof(MinHeapNode));
    n->v = v;
    n->d = d;
    return n;
}

MinHeap* newMinHeap(int capacity) {
    MinHeap* h =(MinHeap*) malloc(sizeof(MinHeap));
    h->pos = (int *)malloc(capacity * sizeof(int));
    h->size = 0;
    h->capacity = capacity;
    h->elem =(MinHeapNode**) malloc(capacity * sizeof(MinHeapNode*));
    return h;
}

void minHeapSwap(MinHeapNode** a, MinHeapNode** b) {
    MinHeapNode *t = *a;
    *a = *b;
    *b = t;
}

void siftDown(MinHeap* h, int idx) {
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < h->size && h->elem[left]->d < h->elem[smallest]->d)
      smallest = left;

    if (right < h->size && h->elem[right]->d < h->elem[smallest]->d)
      smallest = right;

    if (smallest != idx) {
        MinHeapNode *a = h->elem[smallest];
        MinHeapNode *b = h->elem[idx];
        h->pos[a->v] = idx;
        h->pos[b->v] = smallest;
        minHeapSwap(&h->elem[smallest], &h->elem[idx]);
        siftDown(h, smallest);
    }
}

int isEmpty(MinHeap* h) {
    return h->size == 0;
}

MinHeapNode* removeMin(MinHeap *h) {
    if (isEmpty(h)) return NULL;
    MinHeapNode* min = h->elem[0];
    MinHeapNode* last = h->elem[h->size - 1];
    h->elem[0] = last;
    h->pos[min->v] = h->size-1;
    h->pos[last->v] = 0;
    h->size--;
    siftDown(h, 0);
    return min;
}

void siftUp(MinHeap *h, int v, int d) {
    int i = h->pos[v];
    h->elem[i]->d = d;
    while (i && h->elem[i]->d < h->elem[(i - 1) / 2]->d) {
        h->pos[h->elem[i]->v] = (i-1)/2;
        h->pos[h->elem[(i-1)/2]->v] = i;
        minHeapSwap(&h->elem[i],  &h->elem[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int isInMinHeap(MinHeap *h, int v) {
   if (h->pos[v] < h->size) return 1;
   return 0;
}

void freeMinHeap(MinHeap *h) {
    free(h->pos);
    for (int i = 0; i < h->size; i++) {
        free(h->elem[i]);
    }
    free(h->elem);
    free(h);
}



TGraphL* createGraphAdjList(int numberOfNodes, char *title) {
	TGraphL *graph = (TGraphL*) malloc(sizeof(TGraphL));
    graph->nn = numberOfNodes;
    graph->nCapacity = numberOfNodes;
    graph->adl = (ATNode*) malloc(numberOfNodes * sizeof(ATNode));
    for (int i = 0; i < numberOfNodes; i++) {
        graph->title = title;
        graph->adl[i] = NULL;
    }
    createActorList(graph);
	return graph;
}

void addGraphNode(TGraphL *g1, int id1, TGraphL *g2, int id2) {
    if (g1 == NULL) return;

    if (g1->nn >= g1->nCapacity) {
        g1->nCapacity *= 2;
        g1->adl = (ATNode*) realloc(g1->adl,
                                    g1->nCapacity * sizeof(ATNode));
        for (int i = g1->nn; i < g1->nCapacity; i++) {
            g1->adl[i] = NULL;
        }
    }

    TNode *iter = g2->adl[id2];
    while (iter != NULL) {
        char *tmpName = getActorName(g2, iter->v);
        if (actorExists(g1, tmpName)) {
            addEdgeList(g1, id1, getActorId(g1, tmpName));
        }
        iter = iter->next;
    }
    g1->nn++;
}

void addEdgeList(TGraphL *graph, int v1, int v2) {
    if (graph == NULL) return;

    if (graph->adl[v1] != NULL) {
        TNode *tmp = (TNode*) malloc(sizeof(TNode));
        tmp->v = v2;
        tmp->c = 1;
        tmp->next = graph->adl[v1];
        graph->adl[v1] = tmp;
    }
    if (graph->adl[v2] != NULL) {
        TNode *tmp = (TNode*) malloc(sizeof(TNode));
        tmp->v = v1;
        tmp->c = 1;
        tmp->next = graph->adl[v2];
        graph->adl[v2] = tmp;
    }
    if (graph->adl[v1] == NULL) {
        graph->adl[v1] = (TNode*) malloc(sizeof(TNode));
        graph->adl[v1]->v = v2;
        graph->adl[v1]->c = 1;
        graph->adl[v1]->next = NULL;
    }
    if (graph->adl[v2] == NULL) {
        graph->adl[v2] = (TNode*) malloc(sizeof(TNode));
        graph->adl[v2]->v = v1;
        graph->adl[v2]->c = 1;
        graph->adl[v2]->next = NULL;
    }
}

void dfsRecHelper(TGraphL* graph, int* visited, List* path, int s) {
    for (TNode *i = graph->adl[s]; i != NULL; i = i->next) {
        if (!visited[i->v]) {
            visited[i->v] = 1;
            push(path, i->v);
            dfsRecHelper(graph, visited, path, i->v);
        }
    }
}

List* dfsRecursive(TGraphL* graph, int s) {
    int *visited = (int*) calloc(graph->nn, sizeof(int)); // Initialized to 0
    Stack *path = createStack();

    push(path, s);
    visited[s] = 1;

    dfsRecHelper(graph, visited, path, s);

    free(visited);
    return path;
}

void destroyGraphAdjList(TGraphL* graph) {
    for (int i = 0; i < graph->nn; i++) {
        removeNodeList(graph, i);
    }
    free(graph->adl);
    for (int i = 0; i < graph->actorSize; i++) {
        free(graph->actorList[i].name);
    }
    free(graph->actorList);
    free(graph->title);
    free(graph);
}

void removeEdgeList(TGraphL* graph, int v1, int v2) {
	TNode* it = graph->adl[v1];
	TNode* prev = NULL;
    
	while (it != NULL && it->v != v2) {
		prev = it;
		it = it->next;
	}

	if (it == NULL) return;

	if (prev != NULL) {
		prev->next = it->next;
    } else {
		graph->adl[v1] = it->next;
    }

	free(it);

	it = graph->adl[v2];
	prev = NULL;

	while (it != NULL && it->v != v1) {
		prev = it;
		it = it->next;
	}
	if (it == NULL) return;

	if (prev != NULL) {
		prev->next = it->next;
    } else {
		graph->adl[v2] = it->next;
    }

	free(it);
}

void removeNodeList(TGraphL* graph, int v) {
	for (int i = 0; i < graph->nn; i++) {
		removeEdgeList(graph, v, i);
	}
}

void createActorList(TGraphL *graph) {
    if (graph == NULL) return;
    graph->actorList = (Actor*) malloc(initCapacity * sizeof(Actor));
    for (int i = 0; i < initCapacity; i++) {
        graph->actorList[i].name = NULL;
    }
    graph->actorCapacity = initCapacity;
    graph->actorSize = 0;
}

int actorExists(TGraphL *graph, char *name) {
    for (int i = 0; i < graph->actorSize; i++) {
        if (!strcmp(graph->actorList[i].name, name)) {
            return 1;
        }
    }
    return 0;
}

int addActor(TGraphL *graph, char *name, int id) {
    if (graph == NULL || name == NULL) return 0;
    if (actorExists(graph, name)) return 0;
    
    if (graph->actorSize >= graph->actorCapacity) {
        graph->actorCapacity *= 2;
        graph->actorList = (Actor*) realloc(graph->actorList,
                                        graph->actorCapacity * sizeof(Actor));
        for (int i = graph->actorSize; i < graph->actorCapacity; i++) {
            graph->actorList[i].name = NULL;
        }
    }

    graph->actorList[graph->actorSize].id = id;
    graph->actorList[graph->actorSize].name = strdup(name);
    graph->actorSize++;
    return 1;
}

char* getActorName(TGraphL *graph, int id) {
    if (graph == NULL) return NULL;
    for (int i = 0; i < graph->actorSize; i++) {
        if (graph->actorList[i].id == id) {
            return graph->actorList[i].name;
        }
    }
    return NULL;
}

int getActorId(TGraphL *graph, char *name) {
    if (graph == NULL || name == NULL) return -1;

    for (int i = 0; i < graph->actorSize; i++) {
        if (!strcmp(graph->actorList[i].name, name)) {
            return graph->actorList[i].id;
        }
    }
    return -1;
}

int readInput1(char *inputPath, Data *data) {
    FILE *fp = fopen(inputPath, "r");
    if (fp == NULL) {
        printf("[readInput1] Error at opening file %s\n", inputPath);
        return -1;
    }
    
    char buff[200];
    fgets(buff, 200, fp);
    sscanf(buff, "%d", &data->sizeMovies);

    data->graph = (TGraphL**) malloc(data->sizeMovies * sizeof(TGraphL*));


    for (int i = 0; i < data->sizeMovies; i++) {
        char *title = (char*) malloc(200 * sizeof(char));
        fgets(title, 200, fp);

        int nn;

        memset(buff, 0, 200);
        fgets(buff, 200, fp);
        sscanf(buff, "%d", &nn);
        
        data->graph[i] = createGraphAdjList(nn, title);

        for (int u = 0; u < nn; u++) {

            char name[200];
            fgets(name, 200, fp);

            addActor(data->graph[i], name, u);
            for (int v = u + 1; v < nn; v++) {
                if (u == v) continue;
                addEdgeList(data->graph[i], u, v);
            }
        }
    }

    data->names = NULL;

    fclose(fp);
    return 0;
}

int readInput2(char *inputPath, Data *data) {
    FILE *fp = fopen(inputPath, "r");
    if (fp == NULL) {
        printf("[readInput2] Error at opening file %s\n", inputPath);
        return -1;
    }
    
    char buff[200];
    fgets(buff, 200, fp);
    sscanf(buff, "%d", &data->sizeMovies);

    data->graph = (TGraphL**) malloc(data->sizeMovies * sizeof(TGraphL*));


    for (int i = 0; i < data->sizeMovies; i++) {
        char *title = (char*) malloc(200 * sizeof(char));
        fgets(title, 200, fp);

        int nn;

        memset(buff, 0, 200);
        fgets(buff, 200, fp);
        sscanf(buff, "%d", &nn);
        
        data->graph[i] = createGraphAdjList(nn, title);

        for (int u = 0; u < nn; u++) {

            char name[200];
            fgets(name, 200, fp);

            addActor(data->graph[i], name, u);
            for (int v = u + 1; v < nn; v++) {
                if (u == v) continue;
                addEdgeList(data->graph[i], u, v);
            }
        }
    }

    data->names = (char**) malloc(2 * sizeof(char*));
    // Unlike readInput1 we must read 2 extra lines from the file.
    fgets(buff, 200, fp);
    data->names[0] = strdup(buff);
    fgets(buff, 200, fp);
    data->names[1] = strdup(buff);

    fclose(fp);
    return 0;
}

void printGraph(TGraphL *graph) {
    if (graph == NULL) return;
    printf("Number of nodes = %d\n", graph->nn);
    for (int i = 0; i < graph->nn; i++) {
        printf("%4d: ", i);
        TNode *tmp = graph->adl[i];
        while (tmp != NULL) {
            printf("%d ", tmp->v);
            tmp = tmp->next;
        }
        printf("\n");
    }

    printf("Actor list size = %d\n", graph->actorSize);
    printf("Actor list capacity = %d\n", graph->actorCapacity);
    printf("Movie title = %s\n", graph->title);

    printf("Actor id   |   Actor name\n");
    for (int i = 0; i < graph->actorSize; i++) {
        printf("%8d   |   %s", graph->actorList[i].id,
                            graph->actorList[i].name);
    }
}

int intersect(TGraphL *g1, TGraphL *g2) {
    for (int i = 0; i < g1->actorSize; i++) {
        for (int j = 0; j < g2->actorSize; j++) {
            if (!strcmp(g1->actorList[i].name, g2->actorList[j].name)) {
                return 1;
            }
        }
    }
    return 0;
}

void merge(TGraphL *g1, TGraphL *g2) {
    for (int i = 0; i < g1->actorSize; i++) {
        for (int j = 0; j < g2->actorSize; j++) {
            if (!strcmp(g1->actorList[i].name, g2->actorList[j].name)) {
                for (int k = 0; k < g2->nn; k++) {
                    char *name = getActorName(g2, k);

                    // Update g1's actor list.
                    int newNode = addActor(g1, name, g1->actorSize);
                    if (newNode) {
                        int id = g1->actorSize - 1;
                        
                        addGraphNode(g1, id, g2, k);
                    }
                }
            }
        }
    }
}

int comparator1(const void *p, const void *q) {
    return strcmp(((Actor*)p)->name, ((Actor*)q)->name);
}
int comparator2(const void *p, const void *q) {
    return strcmp(((char*)p), ((char*)q));
}

int writeOutput1(char *outputPath, int maxProduction, int maxProductionIdx,
                Data *data) {
    FILE *fp = fopen(outputPath, "w");
    if (fp == NULL) {
        printf("[writeOutput] Error at opening file %s\n", outputPath);
        return 1;
    }

    fprintf(fp, "%d\n", maxProduction);

    for (int i = 0; i < data->graph[maxProductionIdx]->actorSize; i++) {
        fprintf(fp, "%s", data->graph[maxProductionIdx]->actorList[i].name);
    }

    fclose(fp);
    return 0;
}

int writeOutput2(char *outputPath, int kinship) {
    FILE *fp = fopen(outputPath, "w");
    if (fp == NULL) {
        printf("[writeOutput] Error at opening file %s\n", outputPath);
        return 1;
    }

    fprintf(fp, "%d\n", kinship);

    fclose(fp);
    return 0;
}

int writeOutput3(char *outputPath, int **deck, int *decks, Data *data,
                int **parent, int totalGraphs) {
    if (data == NULL) return 1;
    FILE *fp = fopen(outputPath, "w");
    if (fp == NULL) {
        printf("[writeOutput] Error at opening file %s\n", outputPath);
        return 1;
    }

    int totalDecks = 0;
    for (int i = 0; i < totalGraphs; i++) {
        totalDecks += decks[i];
    }
    fprintf(fp, "%d\n", totalDecks);

    char buff[totalDecks][100];
    int deckNo = 0;
    int count = 0;
    for (int i = 0; i < data->sizeMovies; i++) {
        if (data->graph[i] == NULL) continue;
        for (int id = 0; id < data->graph[i]->nn; id++) {
            if (deck[count][id] == 1) {
                char buff1[50];
                strcpy(buff1, getActorName(data->graph[i], id));
                buff1[strlen(buff1) - 1] = 0;  // Removing \n.

                char buff2[50];
                strcpy(buff2, getActorName(data->graph[i], parent[count][id]));
                buff2[strlen(buff2) - 1] = 0;  // Removing \n.

                if (strcmp(buff1, buff2) < 0) {
                    sprintf(buff[deckNo], "%s %s\n", buff1, buff2);
                } else {
                    sprintf(buff[deckNo], "%s %s\n", buff2, buff1);
                }
                deckNo++;
            }
        }
        count++;
    }

    qsort((void*)buff, totalDecks, 100, comparator2);
    for (int i = 0; i < totalDecks; i++) {
        // printf("%s", buff[i]);
        fprintf(fp, "%s", buff[i]);
    }

    fclose(fp);
    return 0;
}

int dijkstra(TGraphL *g, int s, int f) {
    int v = s;
    int d[g->nn];
    MinHeap *h = newMinHeap(g->nn);

    for (int i = 0; i < g->nn; i++) {
        d[i] = INT_MAX;
        h->elem[i] = newHeapNode(i, d[i]);
        h->pos[i] = i;
    }

    d[s] = 0;

    h->elem[s]->v = s;
    h->elem[s]->d = d[s];
    h->pos[s] = s;
    siftUp(h, s, d[s]);
    h->size = g->nn;
    while (!isEmpty(h)) {
        MinHeapNode *min = removeMin(h);
        int u = min->v;

        TNode *node = g->adl[u];

        while (node != NULL) {
            v = node->v;
            if (isInMinHeap(h, v) && d[u] != INT_MAX 
                && d[u] + node->c < d[v]) {
                d[v] = d[u] + node->c;
                siftUp(h, v, d[v]);
            }
            node = node->next;
        }
        free(min);
    }
    freeMinHeap(h);
    // d[f] is distance between s and f. f being any node from graph.
    return d[f];
}

void explore(TGraphL *g, int u, int *d, int *low, int *parent, char *color,
            int **deck, int *decks, int time) {
	int v = 0;

	d[u] = time;
	low[u] = time;

	time++;
	color[u] = 'g';

	/* 
	  While the verification is not over, verify if a node was explored before.
	Depending on that, we will update low for this node, after we are done
    exploring.
	*/
	while (v < g->nn) {
        // Check if v is a successor.
        TNode *iter = g->adl[u];
        __uint8_t isSucc = 0;
        while (iter != NULL) {
            if (v == iter->v) {
                isSucc++;
                break;
            }
            iter = iter->next;
        }
        if (!isSucc) {
			v++;
			continue;
        }

		if (color[v] == 'w') {
			parent[v] = u;

			explore(g, v, d, low, parent, color, deck, decks, time);

			low[u] = min(low[u], low[v]);

			if (low[v] > d[u]) {  // Known condition.
				(*deck)[v] = 1;
                (*decks)++;
                // Is deck between u and v where u is parent[v].
			}

		} else if (parent[u] != v) {
			low[u] = min(low[u], d[v]);
		}
		v++;
	}
	color[u] = 'b';
}

void destroyData(Data **data) {
    for (int i = 0; i < (*data)->sizeMovies; i++) {
        if ((*data)->graph[i] == NULL) continue;
        destroyGraphAdjList((*data)->graph[i]);
    }
    if ((*data)->names != NULL) {
        if ((*data)->names[0] != NULL) {
            free((*data)->names[0]);
        }
        if ((*data)->names[1] != NULL) {
            free((*data)->names[1]);
        }
        free((*data)->names);
    }
    free((*data)->graph);
    free(*data);
}

#endif
