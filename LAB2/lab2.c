#include <stdio.h>
#include <string.h>

void swap (int* a, int* b) {
    int c = *a;
    *a = *b;
    *b = c;
}

void NextPermutation(int *mass, int n, int length) {
    while (n > 0) {
        int check = 0, i;
        for (int k = 1; k < length; k++) 
        {
            if (mass[k] > mass[k - 1])
            {
                check = 1;
                i = k - 1;
            }
        }
        if(check == 0) return;

        for (int j = length - 1; j > 0;) { 
            if (mass[j] > mass[i]) {
                swap(&mass[j], &mass[i]);
                break;
            } else --j;
        }

        int left = i + 1;
        int right = length - 1;

        //сортировка хвоста
        while (left < right && right > 0 && left < (length - 1)) { 
            swap(&mass[left], &mass[right]);
            left++;
            right--;
        }

        for (int k = 0; k < length; ++k)
            printf("%d", mass[k]);
        printf("\n");

        --n;
    }
}


int main()
{
    int symb[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int mass[100] = {0};

    int i = 0, temp;
    while ((temp = getchar()) != '\n'){
        mass[i] = temp - '0';
        i++;
    }

    int number;
    if(scanf("%d", &number) != 1){
        printf("bad input\n");
        return 0;
    }

    int length = i;
    if (length > 10) {
        printf("bad input\n");
        return 0;
    }

    int count[11] = {0};
    for (i = 0; i < length; ++i) { 
        int check = -1;
        for (int j = 0; j < 10; ++j) {
            if (mass[i] == symb[j]) {
                check = j;
            }

        }
        if (check == -1) {
            printf("bad input\n");
            return 0;
        }
        count[mass[i]]++;
    }

    for (i = 0; i < 10; ++i){ 
        if(count[i] > 1){
            printf("bad input\n");
            return 0;
        }
    }

    NextPermutation(mass, number, length);
    return 0;
}



