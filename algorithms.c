/** AUTHOR: Lucas Viana Vilela */

#include <stdio.h>
#include <stdlib.h>

// Receives a vector and the position of two sorted subvectors inside it - merges both of them into a fully sorted one
void mergeSubvectors(int *vector, int firstLeftIndex, int firstRightIndex, int secondLeftIndex, int secondRightIndex){
    int vectorSize = (firstRightIndex - firstLeftIndex + 1) + (secondRightIndex - secondLeftIndex + 1);

    int *tmp = (int*)malloc(vectorSize * sizeof(int)); // Temporary vector in which the interpolation will occur
    
    int i, j, k = 0; // Auxiliar variables that'll index the for-loops

    // Loops through both subvectors, merging them
    for(i = firstLeftIndex, j = secondLeftIndex; k < vectorSize; k++){

        // If there are still elements in both subvector
        if(i <= firstRightIndex && j <= secondRightIndex){ 
            // Compares them and copies the lowest one to tmp
            if(vector[i] < vector[j]){ tmp[k] = vector[i++]; }
            else{ tmp[k] = vector[j++]; }
        }

        // If not, copies the remaining element to tmp
        else if(i <= firstRightIndex){ tmp[k] = vector[i++]; }
        else if(j <= secondRightIndex){ tmp[k] = vector[j++]; }

    }

    // Copies the sorted vector in tmp to the original one, replacing the subvectors
    for(i = firstLeftIndex, j = secondLeftIndex, k = 0; k < vectorSize; k++){
        if(i <= firstRightIndex){ vector[i++] = tmp[k]; }
        else{ vector[j++] = tmp[k]; }

    }

    free(tmp); tmp = NULL;

    return;
}

// Receives a parent element and turns the vector into a heap starting at it
void heapify(int *vector, int parent, int lastElement){
    int child;

    while(parent <= lastElement){
        child = 2*parent + 1;

        if(child <= lastElement){
            // Selects the highest value child
            if(child + 1 <= lastElement && vector[child+1] > vector[child]){ child++; }

            if(vector[parent] < vector[child]){ swapElements(vector, parent, child); }
        }

        parent = child;
    }

    return;
}



// SELECTION SORT
void selectionSort(int *vector, int vectorSize){
    int unsortedSubvector; // First element in the unsorted subvector's index
    int lowestValueIndex;  // Lowest value element in the unsorted subvector's index

    // Loops through the whole vector (each iteration grows the sorted subvector by 1)
    for (unsortedSubvector = 0; unsortedSubvector < vectorSize; unsortedSubvector++){

        // A new iteration starts with it's unsorted subvector's first element as the lowest value
        lowestValueIndex = unsortedSubvector;

        // Loops through the unsorted subvector and selects the lowest element
        for (int i = unsortedSubvector + 1; i < vectorSize; i++){

            // If the current element is greater than the lowest value, set it as the lowest value
            if (vector[i] < vector[lowestValueIndex]){ lowestValueIndex = i; }

        }

        swapElements(vector, unsortedSubvector, lowestValueIndex);
    }

    return;
}

// BUBBLE SORT
void bubbleSort(int *vector, int vectorSize){
    boolean hasSwapped; // Has a swap occurred in the last iteration?
    int lastSwapped; // Last swapped element in this iteration's index
    int sentinella = vectorSize; // Last unsorted element's index

    do{
        hasSwapped = False; // A new iteration starts with no swaps

        // Loops through the vector
        for(int i = 1; i < sentinella; i++){ 
            if(vector[i-1] > vector[i]){ // If an element is greater than it's subsequent, swap'em
                swapElements(vector,i-1,i);

                hasSwapped = True; // A swap just occurred 
                lastSwapped = i;
            }
        }

        // Sentinella is moved to the last swapped element in this iteration
        sentinella = lastSwapped; 

    } while(hasSwapped == True); // Once a iteration with no swaps occur, the vector is sorted

    return;
}

// INSERTION SORT
void insertionSort(int *vector, int vectorSize){

    // Loops through the whole vector
    for(int i = 1; i < vectorSize; i++){
        int aux = vector[i]; // Auxiliar variable to store the "current" element

        // Goes through the already passed part of the vector
        // And takes the "current" element as far left as needed
        int j = i - 1;
        while(j >= 0 && aux < vector[j]){ 
            vector[j+1] = vector[j]; 
            j--;
        }

        vector[j+1] = aux;
    }

    return;
}

// MERGE SORT
void mergeSort(int *vector, int leftIndex, int rightIndex){
    int vectorSize = rightIndex - leftIndex + 1;

    if (vectorSize > 1){
        int middleIndex = (rightIndex + leftIndex) / 2;

        mergeSort(vector, leftIndex, middleIndex);
        mergeSort(vector, middleIndex + 1, rightIndex);
        mergeSubvectors(vector, leftIndex, middleIndex, middleIndex + 1, rightIndex);
    }

    return;
}

// HEAP SORT
void heapSort(int *vector, int vectorSize){
    int unsortedSubvector; // Last element in the unsorted subvector's index

    // Turns the input vector into a max heap
    for(int i = (int) (vectorSize-1)/2; i >= 0; i--){ heapify(vector, i, vectorSize-1); }

    // Actually sorts
    for(unsortedSubvector = vectorSize-1; unsortedSubvector > 0; unsortedSubvector--){
        swapElements(vector, 0, unsortedSubvector);
        heapify(vector, 0, unsortedSubvector - 1);
    }

    return;

}

// SHELL SORT
void shellSort(int *vector, int vectorSize){
    // Sets gap to 2^k - 1
    int gap = 1;
    while(gap <= vectorSize){ gap *= 2; }
    gap = gap/2 - 1;

    while(gap > 0){
        // Insertion sorts the gapped-subvector
        for(int i = gap; i < vectorSize; i += gap){
            int aux = vector[i]; 

            int j = i - gap;
            while(j >= 0 && aux < vector[j]){ 
                vector[j+gap] = vector[j]; 
                j -= gap;
            }

            vector[j+gap] = aux;
        }

        // Halves the gap each iteration
        gap /= 2;
    }

    return;

}

// QUICK SORT
void quickSort(int *vector, int leftIndex, int rightIndex){
    if(leftIndex < rightIndex){
        int pivot = vector[(int)((rightIndex+leftIndex)/2)];
        int left = leftIndex, right = rightIndex;

        while(True){
            // Selects elements from the left that are >= to the pivot
            while(vector[left] < pivot){ left++; }

            // Selects elements from the right that are <= to the pivot
            while(vector[right] > pivot){ right--; }

            // If the swapping the above selected elements is worth it, do it
            if(left < right){ swapElements(vector, left++, right--); } // And pass to the next element

            // If the swap is not worth it, the vector was successfully partitionted
            else{ break; }

        }

        // Sorts the partitions
        quickSort(vector, leftIndex, right);
        quickSort(vector, right+1, rightIndex);
    }

    return;

}

// COUNTING SORT
void countingSort(int *vector, int vectorSize, int maxValue){
    int *counters = (int *)malloc((maxValue + 1) * sizeof(int));
    int *aux = (int *)malloc(vectorSize * sizeof(int));

    // Sets all counters to 0
    for(int i = 0; i <= maxValue; i++){ counters[i] = 0; }

    // Counts how many of each number the vector contains
    for(int i = 0; i < vectorSize; i++){ counters[vector[i]]++; }

    // counters[i]: quantity of i in the vector ---> last position + 1 of an i in the vector
    for(int i = 1; i <= maxValue; i++){ counters[i] += counters[i-1]; }

    // Sorts (stable)
    for(int i = vectorSize - 1; i >= 0; i--){
        aux[counters[vector[i]]-- - 1] = vector[i];
    }

    for(int i = 0; i < vectorSize; i++){ vector[i] = aux[i]; }

    free(counters);
    free(aux);

    return;
}

// RADIX SORT
void radixSort(int *vector, int vectorSize, int maxValue, int base){
    int *counters = (int *)malloc((base+1) * sizeof(int));
    int *aux = (int *)malloc(vectorSize * sizeof(int));

    // Counting sorts each digit d (starting by the unit, d = 1)
    for(unsigned long d = 1; maxValue/d > 0; d *= base){
        // Sets all counters to 0
        // Digit range is 0-base --> digitMaxValue = base
        for(int i = 0; i <= base; i++){ counters[i] = 0; }

        // Counts how many of each digit in the d position the vector contains
        // (vector[i]/d) % base = value of the digit in the position d of the number vector[i]
        for(int i = 0; i < vectorSize; i++){ counters[(vector[i]/d) % base]++; }

        // counters[i]: quantity of i in the vector ---> last position + 1 of an i in the vector
        for(int i = 1; i <= base; i++){ counters[i] += counters[i-1]; }

        // Sorts (stable)
        for(int i = vectorSize - 1; i >= 0; i--){
            aux[counters[(vector[i]/d) % base]-- - 1] = vector[i];
        }

        for(int i = 0; i < vectorSize; i++){ vector[i] = aux[i]; }
    }

    free(counters);
    free(aux);

    return;
}