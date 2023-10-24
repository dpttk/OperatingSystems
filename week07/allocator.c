#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_MEM 10000000
int mem[MAX_MEM]; 

void allocateFirstFit(int adrs, int size) {
    int j = 0;
    for (int i = 0; i < MAX_MEM; i++) {
        if (mem[i] == 0) { 
            j++;    
            if (j>=size) {
                for (int o = j - size; o < j; o++) {
                mem[o] = adrs; 
                }
                break;
            }
        }
        else {
            j = 0;
        }
    }
}

void allocateBestFit(int adrs, int size) {
    int min = MAX_MEM; 
    int index = -1;
    int firstZero = -1;
    for (int i = 0; i < MAX_MEM; i++) {
    
        if (mem[i] == 0) {
            if(firstZero==-1){
                firstZero = i;
            }
        } else {
            int contigFree = i-firstZero;
            if (contigFree >= size && contigFree < min) {
                min = contigFree;
                index = i;
            } 
            firstZero = -1;
        }
    }

  if (index != -1) {
    for (int i = index; i < index + size; i++) {
      mem[i] = adrs;
    }
  }
}

void allocateWorstFit(int adrs, int size) {
  int max = -1;
  int index = -1;
  int firstZero = -1;
  for (int i = 0; i < MAX_MEM; i++) {
    if (mem[i] == 0) {
      if (firstZero==-1){
        firstZero = i;
      }
    } else {
        int contigFree = i - firstZero;
        if (contigFree >= size && contigFree > max) {
        max = contigFree;
        index = i; 
        firstZero++;
      }
    }
  }

  if (index != -1) {
    for (int i = index; i < index + size; i++) {
      mem[i] = adrs;
    }
  }
}

void clear(int adrs) {
    int i;
    for (i = 0; i < MAX_MEM; i++) {
        if (mem[i] == adrs) {
        mem[i] = 0; 
        }
    }
}

int main() {

    FILE* fp = fopen("queries.txt", "r");

    for (int i = 0; i < MAX_MEM; i++) {
        mem[i] = 0;
    }

    char query[100];

    int adrs, size;
    clock_t startFF, endFF, startBF, endBF, startWF, endWF;
    double totalTimeFF = 0, totalTimeBF = 0, totalTimeWF = 0;
    int queriesFF = 0, queriesBF = 0, queriesWF = 0;

    startFF = clock();

    while (fgets(query, 100, fp) != NULL) {
        sscanf(query, "%*s %d %d", &adrs, &size);  
        if (strcmp(query, "end\n") == 0) {
            break;
        } else if (strncmp(query, "allocate", 8) == 0) {
            allocateFirstFit(adrs, size);
        } else if (strncmp(query, "clear", 5) == 0) {
            clear(adrs);
        }
        queriesFF++;
    }

    endFF = clock();
    totalTimeFF = (double)(endFF - startFF) / CLOCKS_PER_SEC;

    for (int i = 0; i < MAX_MEM; i++) {
        mem[i] = 0;
    }

    startBF = clock();
    rewind(fp); 
    while (fgets(query, 100, fp) != NULL) {
        sscanf(query, "%*s %d %d", &adrs, &size);
        if (strcmp(query, "end\n") == 0) {
            break;  
        } else if (strncmp(query, "allocate", 8) == 0) {
            allocateBestFit(adrs, size);
        } else if (strncmp(query, "clear", 5) == 0) {
            clear(adrs);
        }
        queriesBF++;
    }
    endBF = clock();
    totalTimeBF = (double)(endBF - startBF) / CLOCKS_PER_SEC;

    for (int i = 0; i < MAX_MEM; i++) {
    mem[i] = 0;
    }

    startWF = clock();
    rewind(fp);
    while (fgets(query, 100, fp) != NULL) {
        sscanf(query, "%*s %d %d", &adrs, &size);
        if (strcmp(query, "end\n") == 0) {
            break;
        } else if (strncmp(query, "allocate", 8) == 0) {
            allocateWorstFit(adrs, size);
        } else if (strncmp(query, "clear", 5) == 0) {
            clear(adrs);
        }
        queriesWF++;
    }
    fclose(fp);
    endWF = clock();
    totalTimeWF = (double)(endWF - startWF) / CLOCKS_PER_SEC;

    double throughputFF = queriesFF/totalTimeFF;
    double throughputBF = queriesBF/totalTimeBF;
    double throughputWF = queriesWF/totalTimeWF;

    printf("First Fit: %lf\n", throughputFF);
    printf("Best Fit: %lf\n", throughputBF);
    printf("Worst Fit: %lf\n", throughputWF);


    return 0;
}