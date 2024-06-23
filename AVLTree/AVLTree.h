#ifndef AVLTree_H
#define AVLTree_H

#define LH +1
#define EH 0
#define RH -1

typedef enum {
    OK, ERROR, TRUE, FALSE
} Status;

typedef int ElemType;
typedef struct AVLTreeNode {
    ElemType data;
    int bf; // 平衡因子
    struct AVLTreeNode *lchild, *rchild;
} *AVLTree;

void InOrderTraverse(AVLTree T);
void L_Rotate(AVLTree *T);
void R_Rotate(AVLTree *T);
void LeftBalance(AVLTree *T);
void RightBalance(AVLTree *T);
Status LeftDeleteBalance(AVLTree *T);
Status RightDeleteBalance(AVLTree *T);
Status InsertAVL(AVLTree *T, ElemType e, Status *taller);
Status DeleteAVL(AVLTree *T, ElemType e, Status *shorter);
void DestroyAVLTree(AVLTree *T);
AVLTree SearchAVLTree(AVLTree T, ElemType key);
Status isBalanced(AVLTree T);
int GetDepth(AVLTree T);
void MergeAVLTree(AVLTree *T1, AVLTree T2);
void DivAVLTree(AVLTree R, AVLTree *T1, AVLTree *T2, ElemType e);

#endif // AVLTree_H
