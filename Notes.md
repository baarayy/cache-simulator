# Cache Memory Notes

## Table of Contents
1. [Introduction](#introduction)
2. [Cache Organization](#cache-organization)
3. [Cache Levels](#cache-levels)
4. [Cache Parameters](#cache-parameters)
5. [Cache Structure](#cache-structure)
6. [Cache Mapping](#cache-mapping)
7. [Cache Replacement Policies](#cache-replacement-policies)
8. [Cache Write Policies](#cache-write-policies)
9. [Cache Coherency](#cache-coherency)
10. [MESI Protocol](#mesi-protocol)
11. [Indexing in Cache](#indexing-in-cache)
12. [Example Code](#example-code)

## Introduction
Cache memory is a small, high-speed storage located close to the CPU that stores frequently accessed data and instructions. It improves the overall speed and efficiency of a computer by reducing the time needed to access data from the main memory.

## Cache Organization
Cache organization refers to the structure and management of data storage in the cache. It includes aspects such as cache levels, mapping techniques, replacement policies, write policies, and coherency mechanisms.

## Cache Levels
- **L1 Cache**: Smallest, fastest cache, located closest to the CPU.
- **L2 Cache**: Larger and slower than L1, acts as an intermediary.
- **L3 Cache**: Larger and slower than L2, shared among multiple CPU cores.

## Cache Parameters
Cache parameters define the characteristics and capabilities of the cache:
- **Cache Size**: The total amount of data the cache can hold.
- **Block Size**: The unit of data transfer between cache and main memory.
- **Associativity**: The number of locations in a cache where a particular piece of data can be placed. It can be direct-mapped, set-associative, or fully associative.
- **Number of Sets**: The number of unique locations in the cache determined by the cache size and associativity.

## Cache Structure
The structure of a cache involves several components:
- **Cache Lines (Blocks)**: The smallest unit of data in a cache, consisting of a tag, data block, and status bits.
- **Tags**: Part of the address used to identify if a particular block of data is in the cache.
- **Index**: Part of the address used to determine which cache set the data maps to.
- **Offset**: Part of the address used to identify the specific byte within a cache line.

## Cache Mapping
- **Direct-Mapped Cache**: Each block of main memory maps to exactly one cache line.
- **Fully Associative Cache**: Any block of memory can be stored in any cache line.
- **Set-Associative Cache**: A compromise where memory blocks are mapped to a set of lines, and each set can store multiple blocks.

## Cache Replacement Policies
- **Least Recently Used (LRU)**: Replaces the least recently accessed data.
- **First-In, First-Out (FIFO)**: Replaces the oldest data in the cache.
- **Least Frequently Used (LFU)**: Replaces data that is accessed least frequently.

## Cache Write Policies
- **Write-Through**: Data is written to both the cache and the main memory simultaneously.
- **Write-Back**: Data is written to the cache first and only to the main memory when evicted from the cache.

## Cache Coherency
Cache coherency ensures that multiple cache copies of the same data remain consistent across the system, crucial in multi-core processors. Common protocols include:
- **MESI (Modified, Exclusive, Shared, Invalid)**

## MESI Protocol
The MESI protocol is a cache coherency mechanism used to maintain consistency:
- **Modified (M)**: Cache line is modified and not in main memory.
- **Exclusive (E)**: Cache line is exclusive and matches the main memory.
- **Shared (S)**: Cache line is shared and matches the main memory.
- **Invalid (I)**: Cache line is invalid.

## Indexing in Cache
- **Higher-Order Bits Indexing**: Maps addresses with higher-order bits, reducing conflict misses for random access patterns.
- **Middle-Order Bits Indexing**: Maps addresses with middle-order bits, improving distribution for strided access patterns.

## Example Code
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {
    unsigned int s = 0; // Number of bits in set address
    unsigned int E = 0; // Number of cache blocks in a set
    unsigned int b = 0; // Number of bits in a cache block
    char fileContents[1000] = "";

    int initializer = 0;
    while ((initializer = getopt(argc, argv, "s:E:b:t:")) != -1) {
        switch (initializer) {
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
                strcpy(fileContents, optarg);
                break;
            default:
                break;
        }
    }
    return 0;
}
