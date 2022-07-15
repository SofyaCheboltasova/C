#include <stdio.h>

// Подсчет хэша
int HashFunc (char *array, int *three, short lng){
    int hash = 0, j = 0;

    for (int i = 0; i < lng; ++i) {
        hash += ((unsigned char)array[i] % 3) * (three[j]);
        ++j;
    }
    return hash;
}

// Работа с текстом
void RollingHash (int hPattern, short lng, int *three, char *pattern)
{
    int i = 0, a = 0;
    int temp;
    char text[2048];

    while ((temp = getchar()) != EOF && i < lng) {
        text[i] = (unsigned  char)temp;
        ++i;
    }

    printf("%d ", hPattern); 
    if(hPattern == 0) return;


    int nextPoint = i;
    int hText = HashFunc(text, three, lng); 
    int point;

    if (hText == hPattern) {
        point = 1;
        for (int j = 0; j < lng; ++j)
        {
            printf("%d ", point); 
            if(text[point - 1] != pattern[j])
                break;
            ++point;
        }
    }

    ++a;           
    text[i] = temp;
    hText = ((hText - ((unsigned char)text[(a - 1) % 2048] % 3)) / 3) + (((unsigned char)text[i] % 3) * three[lng - 1]);
    ++i;


    // Ввод следующего символа
    while ((temp = getchar()) != EOF) {
        ++a;
        text[i] = temp;
        hText = ((hText - ((unsigned char)text[(a - 1) % 2048] % 3)) / 3) + (((unsigned char)text[i] % 3) * three[lng - 1]);
        ++i;
        ++nextPoint;

        if (i == 2048)
            i = 0;

        if(temp == EOF)
            break;

        // Если хэши совпали
        if (hText == hPattern) {
          // (Всего символов (22) - длина слова(7)) + 1 (тк включительно) + 1 (тк i c 0 - индексы массива)
            point = nextPoint - lng + 2; 
            for (int j = 0; j < lng; ++j)
            {
                printf("%d ", point); 
                ++point;
            }
        }
    }
}

int main() {
    char pattern [17];
    int i = 0;
    char temp;

    while (( temp = getchar()) != '\n'){
        pattern[i] = (unsigned char)temp;
        i++;
    }

    short lng = i;

    int three[17];
    three[0] = 1;

    for (int i = 1; i < 17; ++i)
        three[i] = three[i - 1] * 3;


    int hash = HashFunc(pattern, three, lng);

    RollingHash(hash, lng, three, pattern);

    return 0;
}


