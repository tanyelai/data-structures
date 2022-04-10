#include <stdio.h>

void swap(int *, int *);
void heapify(int *, int, int *);
void insert(int *, int, int *);
void delete(int *, int, int *);
void print(int *, int);

int main(){
    int array[10];
    int SIZE = 0;
    int i, n, new_element;
    printf("\nEnter how many elements you will enter: ");
    scanf("%d", &n);
            
    for (i=0; i<n; i++){
        printf("Enter new element: ");
        scanf("%d", &new_element);
        insert(array, new_element, &SIZE);
    }

    printf("\nMax-heap array: ");
    print(array, SIZE);

    delete(array, 9, &SIZE);
    delete(array, 3, &SIZE);

    printf("\nAfter deleting an element: ");
    print(array, SIZE);
}

void swap(int *x, int *y){
    int temp = *y;
    *y = *x;
    *x = temp;
}

void heapify(int array[], int i, int *SIZE){
    
    if(*SIZE == 1){
        printf("\nOnly one element in the heap tree.\n");
    }
    else{
        int largest = i;
        int left = (2*i)+1;
        int right = (2*i)+2;
   
        if(left < *SIZE && array[left] > array[largest])
            largest = left;
        if(right < *SIZE && array[right] > array[largest])
            largest = right;
        if(largest != i){
            swap(&array[i], &array[largest]);
            heapify(array, largest, SIZE);
        }
    }
}

void insert(int array[], int element, int *SIZE){
    if(*SIZE == 0){
        array[0] = element;
        *SIZE += 1;
    }
    else{
        array[*SIZE] = element;
        *SIZE += 1;
        int i;
        for(i = (*SIZE/2)-1; i >= 0; i--)
            heapify(array, i, SIZE);
    }
}

void delete(int array[], int element, int *SIZE){
    int i=0;
    while(element != array[i] || (i > *SIZE))
        i++;
            
    swap(&array[i], &array[*SIZE-1]);
    *SIZE -= 1;
    for(i = (*SIZE/2)-1; i >= 0; i--)
        heapify(array, i, SIZE);
}

void print(int array[], int SIZE){
    int i;
    for(i=0; i < SIZE; i++)
        printf("%d ", array[i]);
    printf("\n");
}