#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <emscripten/emscripten.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Get the max value of the array
 **/
EMSCRIPTEN_KEEPALIVE int max(int8_t t_size, int8_t *table) {
    int max = 0;
    for(int8_t index = 0; index < t_size; index++) {
        if (max < table[index]){
            max = table[index];
        }
    }
    return max;
}

/**
 * Sort the array given in parameter
 **/
EMSCRIPTEN_KEEPALIVE int8_t * spaghettiSort(int8_t t_size, int8_t *tableToSort ) {
    // get the maximum of the array
    int8_t valueMax = max(t_size, tableToSort);
    
    // allocate an array that will contain the value of tableSort as his index
    int8_t * valueAsIndexTable = (int8_t *)malloc((valueMax+1)*sizeof(int8_t));

    // initialize the array with 0 value
    memset(valueAsIndexTable, 0, valueMax);

    // foreach value of tableSort increment the value for the corresponding index in valueAsIndexTable
    for(int8_t index = 0; index < t_size; index++) {
        valueAsIndexTable[tableToSort[index]]++;
    }

    int8_t sortedIndex = 0;
    // read valueAsIndexTable to get the sorted array
    for (int8_t index = 0; index <= valueMax; index++) {
        while(valueAsIndexTable[index] > 0) {
            if(sortedIndex > t_size) {
                printf("Error sortedIndex > t_size");
                return tableToSort;
            }
            tableToSort[sortedIndex] = index;
            sortedIndex++;
            valueAsIndexTable[index]--;
        }
    }

    free(valueAsIndexTable);

    return tableToSort;
}

#ifdef __cplusplus
}
#endif

