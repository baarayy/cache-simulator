#include "cachelab.h"
#include <getopt.h>

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
void readContent(char content[] , int b ,int s ,int S ,int E ,CacheLine** cache) {
    FILE* file = fopen(content, "r");
    char operation; 
    long int address , size;
    
    while(fscan(file , " %c %lx,%lx", &operation , &address , &size)) {
        if (operation == 'I') {
            continue;
        }
        if (operation == 'M') {
            hits++;
        }
        long int tag = address >> (s + b);
        long int setIndex = address >> b & (S - 1);
    }
    fclose(file);
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
    printSummary(0, 0, 0);
    return 0;
}
