#include "cachelab.h"
#include <getopt.h>
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
    printSummary(0, 0, 0);
    return 0;
}
