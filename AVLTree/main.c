#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AVLTree.h"

/* 清屏 */
void ClearScreen(void){
    int clear = system("cls");
    (void)clear;
}

/* 按下回车继续，读到 EOF 退出，不接受实际输入 */
void Continue(void){
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
    if (c == EOF) exit(0); /* 接收到 EOF 直接退出 */
}

// 打印凹入表形式的平衡二叉树
void PrintIndentedTree(AVLTree T, int depth) {
    if (T == NULL) 
        return;
    PrintIndentedTree(T->rchild, depth + 1);
    for (int i = 0; i < depth; i++) {
        printf("    ");
    }
    printf("%d\n", T->data);
    PrintIndentedTree(T->lchild, depth + 1);
}

void PrintTree(AVLTree T) {
    PrintIndentedTree(T, 0);
}

int main() {
    AVLTree T1 = NULL;
    Status taller, shorter;
    int choice;
    ElemType key;

    while (1) {
        ClearScreen();
        printf("\nPlease input the operation type: \n");
        printf("Enter 1 to insert node in the AVLTree\n");
        printf("Enter 2 to delete node in the AVLTree\n");
        printf("Enter 3 to search elem in the AVLTree\n");
        printf("Enter 4 to merge two AVLTree\n");
        printf("Enter 5 to split the AVLTree\n");
        printf("Enter 6 to exit\n");
        printf("Please enter your choice: ");
        scanf("%d", &choice);
        puts("====================================================================================================================================");
        switch (choice) {
            case 1:
                printf("Please enter the keyword you want to insert: ");
                scanf("%d", &key);
                puts("====================================================================================================================================");
                if (InsertAVL(&T1, key, &taller) == TRUE) {
                    printf("Insert successfully, the current AVLTree is: \n");
                } else {
                    printf("Insertion failed. The keyword already exists.\n");
                }
                PrintTree(T1);
                puts("====================================================================================================================================");
                Continue();
                break;
            
            case 2:
                printf("Please enter the keyword you want to delete: ");
                scanf("%d", &key);
                puts("====================================================================================================================================");
                if (DeleteAVL(&T1, key, &shorter) == TRUE) {
                    printf("Delete successfully, the current AVLTree is: \n");
                } else {
                    printf("Deletion failed. The keyword doesn't exist.\n");
                }
                PrintTree(T1);
                puts("====================================================================================================================================");
                Continue();
                break;

            case 3:
                printf("Please enter the keyword you are searching: ");
                scanf("%d", &key);
                puts("====================================================================================================================================");
                AVLTree result = SearchAVLTree(T1, key);
                if (result != NULL) {
                    printf("Search successfully, the keyword exists: %d\n", result->data);
                } else {
                    printf("Search failed, the keyword does not exist.\n");
                }
                puts("====================================================================================================================================");
                Continue();
                break;

            case 4: {
                DestroyAVLTree(&T1);
                AVLTree T2 = NULL;
                printf("Please enter the elements of the two trees to be merged (separated by space, press enter after entering): \n");
                printf("First tree: ");
                char buffer[256];
                getchar(); // 清除缓冲区
                fgets(buffer, 256, stdin);
                char *token = strtok(buffer, " ");
                while (token != NULL) {
                    int num = atoi(token);
                    InsertAVL(&T1, num, &taller);
                    token = strtok(NULL, " ");
                }
                printf("Second tree: ");
                fgets(buffer, 256, stdin);
                token = strtok(buffer, " ");
                while (token != NULL) {
                    int num = atoi(token);
                    InsertAVL(&T2, num, &taller);
                    token = strtok(NULL, " ");
                }
                puts("====================================================================================================================================");
                printf("First tree: \n");
                PrintTree(T1);
                puts("====================================================================================================================================");
                printf("Second tree: \n");
                PrintTree(T2);
                puts("====================================================================================================================================");
                MergeAVLTree(&T1, T2);
                printf("The merged tree: \n");
                PrintTree(T1);
                puts("====================================================================================================================================");
                DestroyAVLTree(&T2); // 销毁T2，避免内存泄漏
                break;
            }

            case 5: {
                DestroyAVLTree(&T1);
                AVLTree T2 = NULL;
                AVLTree T3 = NULL;
                printf("Please enter the elements of the tree to be split (separated by space, press enter after entering): \n");
                getchar(); // 清除缓冲区
                char buffer[256];
                fgets(buffer, 256, stdin);
                char *token = strtok(buffer, " ");
                while (token != NULL) {
                    int num = atoi(token);
                    InsertAVL(&T1, num, &taller);
                    token = strtok(NULL, " ");
                }
                printf("Please enter the split keyword: ");
                scanf("%d", &key);
                puts("====================================================================================================================================");
                printf("The tree before the split: \n");
                PrintTree(T1);
                puts("====================================================================================================================================");
                DivAVLTree(T1, &T2, &T3, key);
                printf("The split tree 1: \n");
                PrintTree(T2);
                puts("====================================================================================================================================");
                printf("The split tree 2: \n");
                PrintTree(T3);
                puts("====================================================================================================================================");
                DestroyAVLTree(&T1); // 销毁T1，避免内存泄漏
                Continue();
                break;
            }

            case 6:
                DestroyAVLTree(&T1);
                exit(0);

            default:
                printf("Invalid selection, please enter again!\n");
                puts("====================================================================================================================================");
                Continue();
        }
        printf("Please press Enter to continue...");
        Continue();
    }
    return 0;
}
