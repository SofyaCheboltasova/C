#include <stdio.h>
#include <malloc.h>

void Swap (int* a, int* b){
    int c = *a;
    *a = *b;
    *b = c;
}

void Sift (int *arr, long long length, long long i) {
    long long tmp = i;
    long long left = 2 * i + 1;
    long long right = 2 * i + 2;

    if ((left < length && arr[tmp] < arr[left]) || (right < length && arr[tmp] < arr[right])) {
        if (arr[left] > arr[right] || right >= length)
            tmp = left;
        else
            tmp = right;
    }

    if (tmp == i)
        return;
    else {
        Swap (&arr[i], &arr[tmp]);
        Sift(arr, length, tmp);
    }
}


void HeapSort (int *arr, long long n) {
    for (long long i = n/2 - 1; i >= 0; --i)
        Sift(arr, n, i);

    for (long long i = n - 1; i >= 0; --i){
        Swap(&arr[0], &arr[i]);
        Sift(arr, i, 0); //i = i/2 - 1
    }
}

int main() {
    long long n;
    if (scanf("%lld ", &n) != 1) {
        printf("bad input");
        return 0;
    }
    int *heap = malloc((n + 1) * sizeof(int));

    for (long long i = 0; i < n; i++) {
        if (scanf("%d", &heap[i]) != 1) {
            printf("bad input");
            return 0;
        }
    }
    HeapSort(heap, n);

    for (long long i = 0; i < n; ++i)
        printf("%d ", heap[i]);

    free (heap);
    return 0;
}
