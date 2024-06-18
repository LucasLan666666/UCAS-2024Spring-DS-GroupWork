#ifndef BBSTREE_H
#define BBSTREE_H

#define LH +1
#define EH 0
#define RH -1

typedef enum {
    OK, ERROR, TRUE, FALSE
} Status;

typedef int ElemType;
typedef struct BBSTNode {
    ElemType data;
    int bf; // 平衡因子
    struct BBSTNode *lchild, *rchild;
} *BBSTree;

void InOrderTraverse(BBSTree T);
void L_Rotate(BBSTree *T);
void R_Rotate(BBSTree *T);
void LeftBalance(BBSTree *T);
void RightBalance(BBSTree *T);
Status LeftDeleteBalance(BBSTree *T);
Status RightDeleteBalance(BBSTree *T);

Status InsertAVL(BBSTree *T, ElemType e, Status *taller);
Status DeleteAVL(BBSTree *T, ElemType e, Status *shorter);

void DestroyBBST(BBSTree *T);
BBSTree SearchBBST(BBSTree T, ElemType key);

Status isBalanced(BBSTree T);

int GetDepth(BBSTree T);

void MergeBBSTree(BBSTree *T1, BBSTree T2);

void DivBBSTree(BBSTree R, BBSTree *T1, BBSTree *T2, ElemType e);

#endif // BBSTREE_H
