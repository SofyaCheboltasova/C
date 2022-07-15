#include <stdio.h>
#include <malloc.h>

typedef struct Node {
    struct Node * next;
    char value;
} Node;

void push (Node **head, char value){
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL)
        return;
    new_node->value = value;
    new_node->next = *head;
    *head = new_node;
}

void pop (Node **head) {
    Node *last_node = *head;
    if (last_node == NULL)
        return;
    *head = last_node->next;
    free(last_node);
}

char peek (Node **head) {
    Node *last_node = *head;
    if(last_node != NULL)
        return last_node->value;
    return -1;
}

typedef struct NodeInt {
    struct NodeInt * next;
    int value;
} NodeInt;

void push_int (NodeInt **head, int value){
    NodeInt *new_node = malloc(sizeof(NodeInt));
    if (new_node == NULL)
        return;
    new_node->value = value;
    new_node->next = *head;
    *head = new_node;
}

int peek_int (NodeInt **head) {
    NodeInt *last_node = *head;
    if(last_node != NULL)
        return last_node->value;
    printf("hi");
    return -1;
}

void pop_int (NodeInt **head) {
    NodeInt *last_node = *head;
    if (last_node == NULL)
        return;
    *head = last_node->next;
    free(last_node);
}

int priority (char value) {
    if(value == '(' || value == ')')
        return 1;
    if (value == '+' || value == '-')
        return 2;
    if (value == '*' || value == '/')
        return 3;
    if (value >= '0' && value <= '9')
        return 0;
    return -1;
}

int count (int operation, NodeInt **result) {
    int operand1, operand2, res;
    operand2 = peek_int(result); pop_int(result);
    operand1 = peek_int(result); pop_int(result);

    if(operation == -5) {
        res = (operand1 + operand2);
        return res;
    }
    if(operation == -6) {
        res = (operand1 * operand2);
        return res;
    }
    if(operation == -3) {
        res = (operand1 - operand2);
        return res;
    }
    if(operation == -1 && operand2) {
        res = (operand1 / operand2);
        return res;
    }
    else printf("division by zero");
    return -1;
}

int main() {
    char elem[1001], tmp;
    char symbols[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '*', '-', '+', '/', '(', ')'};

    int i = 0, bracket1 = 0, bracket2 = 0;
    while ((tmp = getchar()) != '\n')
    {
        int flag = 0;
        for (int j = 0; j < 16; ++j) {
            if (tmp == symbols[j])
                flag = 1;
            if (tmp == ')') ++bracket1;
            if (tmp == '(') ++bracket2;     
        }

        if (flag == 0) {
            printf("syntax error");         
            return 0; }

        elem[i] = tmp;
        i++;
    }

    if (bracket1 != bracket2) {
        printf("syntax error");            
        return 0;
    }

    
    int size = i;
    if (size <= 0) {
        printf("syntax error");
        return 0;
    }

    Node *stack = NULL;
    NodeInt *output = NULL;
    NodeInt *result = NULL;

    //Проверки на ошибки
    for (int i = 1; i < size; ++i)
    {
        if (elem[i - 1] == '/' && elem[i] == '0') {
            printf("division by zero");
            return 0;
        }

        if ((elem[i - 1] == '(' && elem[i] == ')') || (elem[i - 1] == ')' && elem[i] == '(')) {
            printf("syntax error");
            return 0;
        }

        if ((priority(elem[i - 1]) == 2 || priority(elem[i - 1]) == 3) && elem[i] == ')') {
            printf("syntax error");
            return 0;
        }
        if (elem[0] == ')') {
            printf("syntax error");
            return 0;
        }

        if (priority(elem[size - 1]) >= 2) {
            printf("syntax error");
            return 0;
        }

        if ((priority(elem[i - 1]) == 2 || priority(elem[i - 1]) == 3) &&
            (priority(elem[i]) == 2 || priority(elem[i]) == 3)) {
            printf("syntax error");
            return 0;
        }
    }

    //Создание ОПЗ
    int number = 0;
    for (int i = 0; i < size; ++i)
    {
        if (priority(elem[i]) == 0 && i != size - 1)
            number = (elem[i] - '0') + number * 10;

        else if(elem[i] == '(')
            push(&stack, elem[i]);

        else if (elem[i] == ')' && i) {
            if(elem[i - 1] != ')') {
                push_int(&result, number);
                number = 0;
            }
            while(peek(&stack) != '('){
                push_int(&result, peek(&stack) - '0');
                pop(&stack);
            }
            pop(&stack);
        }

        else if (priority(elem[i]) >= 2 || i == size - 1)
        {
            if(i == size - 1)
                number = (elem[i] - '0') + number * 10;

            if(number) {
                push_int(&result, number);
                number = 0;
            }

            if(i != size - 1 && priority(peek(&stack)) >= 2){
                while (priority(elem[i]) <= priority(peek(&stack)) && stack != NULL) {
                    push_int(&result, peek(&stack) - '0');
                    pop(&stack);
                }
            }

            if(i != size - 1)
                push(&stack, elem[i]);
        }
    }

    while(stack != NULL){
        push_int(&result, peek(&stack) - '0');      
        pop(&stack);
    }

    while(result != NULL) {                       
        push_int(&output, peek_int(&result));
        pop_int(&result);
    }

    //Вычисления
    int Res;
    while(output != NULL) {
        if (peek_int(&output) >= 0) {
            push_int(&result, peek_int(&output));
            pop_int(&output);
        }
        else {
            Res = count(peek_int(&output), &result);
            pop_int(&output);
            if (Res == -1) {
                while(result != NULL)
                    pop_int(&result);

                while(output != NULL)
                    pop_int(&output);
                return 0;
            }
            push_int(&result, Res);
        }
    }

    printf("%d", peek_int(&result));

    while(result != NULL)
        pop_int(&result);

    return 0;
}
