#include <stdio.h>

void BMfunc(unsigned char *pattern, int *table, int lng_pattern)
{
    unsigned char text[16];
    int point = 0, tmp;
    int enter_p = 0;                                           
    int enter_t = lng_pattern;

    while (enter_t <= lng_pattern && (tmp = getchar()) != EOF){ 
        if (enter_t != 0) {
            text[lng_pattern - enter_t] = (unsigned char)tmp;
            --enter_t;

            if (enter_t != 0)
                continue;
        }

        for (int i = lng_pattern - 1; i >= 0; --i) {
            printf("%d ", point + i + 1);                       
          
            if (pattern[i] != text[i]) {
               //Если совпадений не было сдвигаемся на значение = символу из текста
                if (enter_p == 0) {                            
                    enter_t = table[text[i]];
                    point += table[text[i]];
                }
              
              //Если совпадения были сдвигаемся на значение =  символу из образа
                else {                                          
                    enter_t = table[pattern[lng_pattern - 1]];
                    point += table[pattern[lng_pattern - 1]];
                }

               if (enter_t < lng_pattern) {
                    for (int i = 0; i < lng_pattern - enter_t; ++i) 
                        text[i] = text[i + enter_t];
                }
                break;
            }
            enter_p++;                                          
        }
        enter_p = 0;

        if (enter_t == 0) {
            enter_t = lng_pattern;
            point += lng_pattern;                               
        }
        if (tmp == EOF)
            return;
    }
}

int main() {
    unsigned char p[17];
    int i = 0, tmp;

    while ((tmp = getchar()) != '\n') {                         
        p[i] = (unsigned char) tmp;
        i++;
    }

    int table[256], lng = i, count = 1;

    for (i = 0; i < 256; ++i)
        table[i] = lng;

    for (i = lng - 2; i >= 0; --i) {                            
        if (table[p[i]] == lng) {
            table[p[i]] = count;

            if (p[i] == p[lng - 1])
                table[p[lng - 1]] = count;
        }
        ++count;
    }

    BMfunc(p, table, lng);
    return 0;
}

