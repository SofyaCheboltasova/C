#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    int b1, b2;
    char mas[102] = {0};
    char symb[] = "0123456789abcdef";

    if (scanf("%d%d%100s", &b1, &b2, mas) != 3) {
        printf("bad input");
        return 0;
    }
    int length = strlen(mas);


    if ((b1 > 16) || (b1 < 2) || (b2 > 16) || (b2 < 2))
        printf("bad input\n");
        
    else {
        int FirstC = 0, dots  = 0;
        
        for (int i = 0; i < length; i++) {
            int find = -1;
            for (int j = 0; j < (int) strlen(symb); j++) {
                if (tolower(mas[i]) == symb[j]) {
                    find = j;
                }
            }
            
            if (mas[i] == '.') {
                dots++;
                FirstC = i;
            } else if ((find == -1) || find >= b1) {
                printf("bad input\n");
                return 0;
            }
        }
        
        if ((dots > 1) || (mas[0] == '.') || (mas[length - 1] == '.')) {
            printf("bad input\n");
            return 0;
        }

        //перевод из b1 в 10 сс
        long long int TenthCel = 0;
        long double TenthDrob = 0;
        if (dots != 0) {
            long double chisl = 1, znam = 1;
            for (int i = 0; i < FirstC; i++) {
                int find = 0;
                for (int j = 0; j < (int) strlen(symb); j++) {
                    if (tolower(mas[i]) == symb[j]) {
                        find = j;
                    }
                }
                TenthCel = TenthCel * b1 + find;
            }
            
            long long int q = 1;
            for (int i = (FirstC + 1); i < length; i++) {
                int find = 0;
                
                for (int j = 0; j < (int) strlen(symb); j++) {
                    if (tolower(mas[i]) == symb[j]) {
                        find = j;
                    }
                }
                
                chisl = chisl * b1 + find;
                znam = b1 * q;
                q = b1 * q;
            }
            TenthDrob = (chisl / znam) - 1;
        } else {
            for (int i = 0; i < length; i++) {
                int find = -1;
                
                for (int j = 0; j < (int) strlen(symb); j++) {
                    if (tolower(mas[i]) == symb[j]) {
                        find = j;
                    }
                }
                TenthCel = TenthCel * b1 + find;
            }
        }

        //перевод в b2 сс
        char mas1[102] = {0};
        int i = 0;
        while (TenthCel != 0) {
            int f = TenthCel % b2;
            mas1[i++] = symb[f];
            TenthCel = (TenthCel - f) / b2;
        }

        if (i == 0) {
            printf("0");
        } else {
            for (int j = i - 1; j >= 0; j--) {
                printf("%c", mas1[j]);
            }
        }

        if (dots != 0) {
            if (TenthDrob == 0.0)
                printf(".0");
            else {
                printf(".");
                int z = 0;
                
                while (z < 12 && (TenthDrob - (int) TenthDrob != 0)) {
                    TenthDrob = TenthDrob * b2;
                    printf("%c", symb[(int) TenthDrob]);
                    TenthDrob = TenthDrob - (int) TenthDrob;
                    z++;
                }
            }
        }
        
    }
    return 0;
}
