#include "cachelab.h"
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static int hits = 0;
static int misses = 0;
static int evictions = 0;

typedef struct {
    int validBit;
    long long tag;
    int LRU;
} CacheLine;
// in order to create cache i need to know 
// the number of sets and the number of lines in each set
CacheLine** createCache(int S ,int E) {
    CacheLine** cache = (CacheLine**)malloc(S * sizeof(CacheLine*)); 
    for(int i = 0 ; i < S ; i++) {
        cache[i] = (CacheLine*)malloc(E * sizeof(CacheLine));
    }
    return cache;
}

void simulation(CacheLine ** cache, unsigned long int setIndex, unsigned long int tag, unsigned int S, unsigned int E) {
	int match = 0; int addIndex = -1;
	CacheLine * cacheSet = cache[setIndex];
	for (int i = 0; i < E; i++) {
		if (cacheSet[i].validBit == 1) {
			// hit
			if (cacheSet[i].tag == tag) {
				match = 1;
				hits++;
				cache[setIndex][i].LRU = 0;
				break;
			}
			// valid bit - tag doesn't match
			else {
				cache[setIndex][i].LRU += 1;
			}
		}
		else {
			addIndex = i;
		}
	}
	// misses
	if (match == 0) {
		// miss - no eviction
        misses++;
		if (addIndex != -1) {
			CacheLine addLine = {1, tag, 0}; // block == line
			cache[setIndex][addIndex] = addLine;
		}
		// miss - do evict
		else {
			int max = 0; int evictIndex = -1;
            // Get the least recently used block to be evicted
			for (int i = 0; i < E; i++) {
				if (cache[setIndex][i].validBit == 1 && cache[setIndex][i].LRU >= max) {
					max = cache[setIndex][i].LRU;
					evictIndex = i;
				}
			}
			CacheLine replaceLine = {1, tag, 0};
			cache[setIndex][evictIndex] = replaceLine;
			evictions++;
		}
	}
}
void readContent(char fileContents[], unsigned int b, unsigned int s, unsigned int S, unsigned int E, CacheLine ** cache) {
	FILE * file1 = fopen(fileContents, "r");
	char operation; unsigned long int address; int size;
	while (fscanf(file1, " %c %lx,%d", &operation, &address, &size) != EOF) {
		if (operation == 'I') {
			continue;
		}
		if (operation == 'M') {
			hits++;
		}
		unsigned long int tag = address >> s >> b;
		unsigned long int setIndex = address >> b & (S - 1);
		simulation(cache, setIndex, tag, S, E);
	}
	fclose(file1);
}
void clearCache(CacheLine ** cache, unsigned int S) {
	for (int i = 0; i < S; i++) {
		free(cache[i]);
	}
	free(cache);
}
int main(int argc ,char *argv[])
{
    // We need to parse the command arguments to get the values of s , E , b
    int s = 0 , E = 0 , b = 0;
    char content[1000] = "";
    int init = 0;
    while ((init = getopt(argc, argv, "s:E:b:t:")) != -1) {
            switch (init) {
                case 's':
                    s = atoi(optarg);
                    break;
                case 'E':
                    E = atoi(optarg);
                    break;
                case 'b':
                    b = atoi(optarg);
                    break;
                case 't':
                    strcpy(content, optarg);
                    break;
                default:
                    break;
            }
    }
    int S = 1 << s; // number of sets is 2^s 
    CacheLine** cache = createCache(S, E);
    readContent(content , b , s , S , E , cache);
    clearCache(cache, S);
    printSummary(hits, misses, evictions);
    return 0;
}
