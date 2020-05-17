#include "utils.h"

void tryMerge(Data *data) {
    if (data == NULL) return;
    for (int i = 0; i < data->sizeMovies - 1; i++) {
        if (data->graph[i] == NULL) continue;  // Graph i is deleted.
        for (int j = i + 1; j < data->sizeMovies; j++) {
            if (data->graph[j] == NULL) continue; // Graph j is deleted.
            if (intersect(data->graph[i], data->graph[j])) {
                /* If they intersect, we merge to graph[i] and delete
                graph[j]. */
                merge(data->graph[i], data->graph[j]);
                destroyGraphAdjList(data->graph[j]);
                data->graph[j] = NULL;
                i--;
                break;
            }
        }
    }
}

/**
 * Returns 0 on success.
 */
int first(char *inputPath, char *outputPath) {
    Data *data = (Data*) malloc(sizeof(Data));
    if (readInput1(inputPath, data)) return -1;
    
    tryMerge(data);

    int maxProduction = 0;     // Contains most populated graph.
    int maxProductionIdx = 0;  // Contains most populated graph idx.
    for (int i = 0; i < data->sizeMovies; i++) {
        if (data->graph[i] != NULL) {  // Graph i is not deleted.
            if (maxProduction < data->graph[i]->nn) {
                maxProduction = data->graph[i]->nn;
                maxProductionIdx = i;
            }
        }
    }
    writeOutput1(outputPath, maxProduction, maxProductionIdx, data);
    destroyData(&data);
    return 0;
}

/**
 * Returns 0 on success.
 */
int second(char *inputPath, char *outputPath) {
    Data *data = (Data*) malloc(sizeof(Data));
    if (readInput2(inputPath, data)) return -1;
    
    tryMerge(data);

    int kinship = -1;
    for (int i = 0; i < data->sizeMovies; i++) {
        if (data->graph[i] == NULL) continue;  // Graph i is deleted.
        if (actorExists(data->graph[i], data->names[0])
            && actorExists(data->graph[i], data->names[1])) {
            kinship = dijkstra(data->graph[i], getActorId(data->graph[i],
                            data->names[0]), getActorId(data->graph[i],
                            data->names[1]));
            break;
        }        
    }

    writeOutput2(outputPath, kinship);
    destroyData(&data);
    return 0;
}

/**
 * Returns 0 on success.
 */
int third(char *inputPath, char *outputPath) {
    Data *data = (Data*) malloc(sizeof(Data));
    if (readInput1(inputPath, data)) return -1;
    
    tryMerge(data);
    
    int totalGraphs = 0;
    for (int i = 0; i < data->sizeMovies; i++) {
        if (data->graph[i] != NULL) {  // Graph i is not deleted.
            totalGraphs++;
        }
    }

    int decks[totalGraphs];
    memset(decks, 0, totalGraphs * sizeof(int));
    int **deck = (int**) malloc(totalGraphs * sizeof(int*));
    int **parent = (int**) malloc(totalGraphs * sizeof(int*));

    int count = 0;
    for (int i = 0; i < data->sizeMovies; i++) {
        if (data->graph[i] == NULL) continue;  // Graph i is deleted.
        // Initialization.
        int nn = data->graph[i]->nn;
        
        int d[nn];
        memset(d, 0, nn * sizeof(int));

        int low[nn];
        memset(low, 0, nn * sizeof(int));
        
        int *tmpParent = (int*) malloc(nn * sizeof(int));
        memset(tmpParent, -1, nn * sizeof(int));

        // 'w' = white; 'g' = grey; 'b' = black;
        char color[nn];
        memset(color, 'w', nn * sizeof(char));

        int *tmpDeck = (int*) malloc(nn * sizeof(int));
        memset(tmpDeck, 0, nn * sizeof(int));
        
        int time = 0;

        int tmpDecks = 0;
        for (int u = 0; u < data->graph[i]->nn; u++) {
            if (color[u] == 'w') {
                color[u] = 'g';
                explore(data->graph[i], u, d, low, tmpParent, color, &tmpDeck,
                        &tmpDecks, time);
            }
        }
        decks[count] = tmpDecks;
        deck[count] = tmpDeck;
        parent[count] = tmpParent;
        count++;

    }
    writeOutput3(outputPath, deck, decks, data, parent, totalGraphs);

    for (int i = 0; i < totalGraphs; i++) {
        free(deck[i]);
        free(parent[i]);
    }
    free(deck);
    free(parent);
    destroyData(&data);
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 4) {
        printf("There should be 3 arguments\n");
        return -1;
    }
    if (!strcmp(argv[1], "-c1")) {
        if (first(argv[2], argv[3])) return -1;
    } else if (!strcmp(argv[1], "-c2")) {
        if (second(argv[2], argv[3])) return -1;
    } else if (!strcmp(argv[1], "-c3")) {
        if (third(argv[2], argv[3])) return -1;
    }
    return 0;
}
