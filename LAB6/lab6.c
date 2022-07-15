#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct AVLtree {
    int key;
    int height;
    struct AVLtree* left;
    struct AVLtree* right;
} AVLtree;


int Height (AVLtree* tree) {
    if (tree != NULL)
        return tree->height;
    else return 0;
}

int FindMaxHeight(int height_left, int height_right) {
    if(height_left > height_right)
        return height_left + 1;
    else
        return height_right + 1;
}

//Пересчет высоты для перестроенного дерева
void RecountHeight(AVLtree* tree) {
    int height_right = Height(tree->right);
    int height_left = Height(tree->left);

    tree->height = FindMaxHeight(height_left, height_right);
}



//Правый и левый малые повороты
AVLtree* RightRotate (AVLtree* tree) {
    AVLtree* left_node = tree->left;
    tree->left = left_node->right;
    left_node->right = tree;

    RecountHeight(tree);
    RecountHeight(left_node);

    return left_node;
}

AVLtree* LeftRotate (AVLtree* tree) {
    AVLtree* right_node = tree->right;
    tree->right = right_node->left;
    right_node->left = tree;

    RecountHeight(tree);
    RecountHeight(right_node);

    return right_node;
}

int FactorBalance (AVLtree* tree) {  
    return Height(tree->right) - Height(tree->left);
}


//Выбор поворота
AVLtree* Rotate(AVLtree* tree) {
    RecountHeight(tree);

    if (FactorBalance(tree) == 2) {
        if (FactorBalance(tree->right) < 0)
            tree->right = RightRotate(tree->right);
        tree = LeftRotate(tree);
    }

    if (FactorBalance(tree) == -2) {
        if (FactorBalance(tree->left) > 0)
            tree->left = LeftRotate(tree->left);
        tree = RightRotate(tree);
    }

    return tree;
}

//Вставка узлов в дерево
AVLtree* Insert (AVLtree* tree, int key, AVLtree* array_of_nodes, int i) {
    if(tree == NULL) {
        AVLtree* new_node = array_of_nodes + i;
        new_node->key = key;
        new_node->left = new_node->right = NULL;
        new_node->height = 1;
        return new_node;
    }

    if(key >= tree->key)
        tree->right = Insert(tree->right, key, array_of_nodes, i);
    else
        tree->left = Insert(tree->left, key, array_of_nodes, i);

    return Rotate(tree);
}

int main() {
    AVLtree* tree = NULL;
    int n, elem;

    if (scanf("%d", &n) == 0) {
        printf("Bad input");
        free(tree);
        return 0;
    }

    AVLtree* array_of_nodes = (AVLtree*)malloc(n * sizeof(AVLtree));

    for (int i = 0; i < n; i++) {
        if(scanf("%d", &elem) == 0) {
            printf("Bad input");
            return 0;
        }
        tree = Insert(tree, elem, array_of_nodes, i);
    }

    printf("%d", Height(tree));

    free(array_of_nodes);
    return 0;
}
