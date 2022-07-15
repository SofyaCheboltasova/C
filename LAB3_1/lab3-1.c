#include <stdio.h>
#include <malloc.h>

void swap (int* a, int* b){
    int c = *a;
    *a = *b;
    *b = c;
}

void QuickS (int *mas, int left, int right)
{
    int L = left, R = right;
    int pivot  = mas[(left + right) / 2];

    while (L <= R) {
        while (mas[L] < pivot)
            ++L;

        while (mas[R] > pivot)
            --R;

        if  (L <= R)
            swap(&mas[L++], &mas[R--]);
    }

    if (left < R)
        QuickS(mas, left, R);
    if (right > L)
        QuickS(mas, L, right);
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) {
        printf("bad input");
        return 0;
    }
    int *a = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++){
        if (scanf("%d", &a[i]) != 1) {
            printf("bad input");
            return 0;
        }
}

    QuickS (a, 0, n - 1);

    for (int i = 0; i < n; ++i)
        printf("%d ", a[i]);

    free(a);
    return 0;
}



