#ifndef BBSTREE_H
#define BBSTREE_H

#define LH +1
#define EH 0
#define RH -1

typedef enum {
    OK, ERROR, YES, NO
} Status;

typedef char ElemType;
typedef struct BBSTNode {
    ElemType data;
    int bf; // 平衡因子
    struct BBSTNode *lchild, *rchild;
} *BBSTree;

void InOrderTraverse(BBSTree T);
void L_Rotation(BBSTree *T);
void R_Rotation(BBSTree *T);
void L_Balance(BBSTree *T);
void R_Balance(BBSTree *T);
Status L_D_Balance(BBSTree *T);
Status R_D_Balance(BBSTree *T);

Status InsertAVL(BBSTree *T, ElemType e, Status *taller);
Status DeleteAVL(BBSTree *T, ElemType e, Status *shorter);

void DestroyBBST(BBSTree *T);
BBSTree SearchBBST(BBSTree T, ElemType key);

Status isBalanced(BBSTree T);

int GetDepth(BBSTree T);

void MergeBBSTree(BBSTree *T1, BBSTree T2);

void DivBBSTree(BBSTree R, BBSTree *T1, BBSTree *T2, ElemType e);

#endif // BBSTREE_H
