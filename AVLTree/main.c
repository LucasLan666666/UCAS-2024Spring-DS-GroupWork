#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BBST.h"

// 打印凹入表形式的平衡二叉树
void PrintIndentedTree(BBSTree T, int depth) {
    if (T == NULL) return;
    PrintIndentedTree(T->rchild, depth + 1);
    for (int i = 0; i < depth; i++) {
        printf("    ");
    }
    printf("%d\n", T->data);
    PrintIndentedTree(T->lchild, depth + 1);
}

void PrintTree(BBSTree T) {
    PrintIndentedTree(T, 0);
}

int main() {
    BBSTree T1 = NULL;
    Status taller, shorter;
    int choice;
    ElemType key;

    while (1) {
        printf("\n请选择操作：\n");
        printf("1. 插入\n");
        printf("2. 删除\n");
        printf("3. 查找\n");
        printf("4. 合并\n");
        printf("5. 分裂\n");
        printf("6. 退出\n");
        printf("输入选择：");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("请输入插入的关键字：");
                scanf("%d", &key);
                if (InsertAVL(&T1, key, &taller) == YES) {
                    printf("插入成功，当前平衡二叉树：\n");
                } else {
                    printf("插入失败，关键字已存在。\n");
                }
                PrintTree(T1);
                break;
            
            case 2:
                printf("请输入删除的关键字：");
                scanf("%d", &key);
                if (DeleteAVL(&T1, key, &shorter) == YES) {
                    printf("删除成功，当前平衡二叉树：\n");
                } else {
                    printf("删除失败，关键字不存在。\n");
                }
                PrintTree(T1);
                break;

            case 3:
                printf("请输入查找的关键字：");
                scanf("%d", &key);
                BBSTree result = SearchBBST(T1, key);
                if (result != NULL) {
                    printf("查找成功，关键字存在：%d\n", result->data);
                } else {
                    printf("查找失败，关键字不存在。\n");
                }
                break;

            case 4: {
                BBSTree T2 = NULL;
                printf("请输入合并的两棵树的元素（以空格分隔，输入完按回车）：\n");
                printf("第一棵树：");
                char buffer[256];
                getchar(); // 清除缓冲区
                fgets(buffer, 256, stdin);
                char *token = strtok(buffer, " ");
                while (token != NULL) {
                    int num = atoi(token);
                    InsertAVL(&T1, num, &taller);
                    token = strtok(NULL, " ");
                }
                printf("第二棵树：");
                fgets(buffer, 256, stdin);
                token = strtok(buffer, " ");
                while (token != NULL) {
                    int num = atoi(token);
                    InsertAVL(&T2, num, &taller);
                    token = strtok(NULL, " ");
                }
                printf("第一棵树：\n");
                PrintTree(T1);
                printf("第二棵树：\n");
                PrintTree(T2);
                MergeBBSTree(&T1, T2);
                printf("合并后的树：\n");
                PrintTree(T1);
                DestroyBBST(&T2); // 销毁T2，避免内存泄漏
                break;
            }

            case 5: {
                BBSTree T2 = NULL;
                BBSTree T3 = NULL;
                printf("请输入要分裂的树的元素（以空格分隔，输入完按回车）：\n");
                getchar(); // 清除缓冲区
                char buffer[256];
                fgets(buffer, 256, stdin);
                char *token = strtok(buffer, " ");
                while (token != NULL) {
                    int num = atoi(token);
                    InsertAVL(&T1, num, &taller);
                    token = strtok(NULL, " ");
                }
                printf("请输入分裂的关键字：");
                scanf("%d", &key);
                printf("分裂前的树：\n");
                PrintTree(T1);
                DivBBSTree(T1, &T2, &T3, key);
                printf("分裂后的树1：\n");
                PrintTree(T2);
                printf("分裂后的树2：\n");
                PrintTree(T3);
                DestroyBBST(&T1); // 销毁T1，避免内存泄漏
                break;
            }

            case 6:
                DestroyBBST(&T1);
                exit(0);

            default:
                printf("无效的选择，请重新输入。\n");
        }
    }

    return 0;
}
