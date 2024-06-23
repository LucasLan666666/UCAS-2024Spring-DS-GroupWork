#include "AVLTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 中序遍历
void InOrderTraverse(AVLTree T) {
    if (T == NULL) 
        return;
    InOrderTraverse(T->lchild);
    printf("%d ", T->data);
    InOrderTraverse(T->rchild);
}

// 左旋转
void L_Rotate(AVLTree *T) {
    AVLTree rc;
    rc = (*T)->rchild;
    (*T)->rchild = rc->lchild;
    rc->lchild = *T;
    *T = rc;
}

// 右旋转
void R_Rotate(AVLTree *T) {
    AVLTree lc;
    lc = (*T)->lchild;
    (*T)->lchild = lc->rchild;
    lc->rchild = *T;
    *T = lc;
}

// 插入之后树 T 失衡时的平衡函数
void LeftBalance(AVLTree *T) {
    AVLTree lc, rc;
    lc = (*T)->lchild;
    switch (lc->bf) {
        case LH: 
            (*T)->bf = lc->bf = EH; 
            break;
        case RH: 
            rc = lc->rchild;
            switch (rc->bf) {
                case LH: 
                    (*T)->bf = RH; 
                    lc->bf = EH; 
                    break; 
                case EH: 
                    (*T)->bf = lc->bf = EH; 
                    break; 
                case RH: 
                    (*T)->bf = EH; 
                    lc->bf = LH; 
                    break; 
            }
            rc->bf = EH;
            L_Rotate(&(*T)->lchild);
            break;
    }
    R_Rotate(T);
}

// 删除之后树 T 的左子树失衡时的平衡函数
Status LeftDeleteBalance(AVLTree *T) {
    AVLTree lc, rc;
    lc = (*T)->lchild;
    Status result;
    switch (lc->bf) {
        case LH: 
            (*T)->bf = lc->bf = EH; 
            result = TRUE;
            break;
        case RH: 
            rc = lc->rchild;
            switch (rc->bf) {
                case LH:
                    (*T)->bf = RH; 
                    lc->bf = EH; 
                    break; 
                case EH: 
                    (*T)->bf = lc->bf = EH; 
                    break; 
                case RH: 
                    (*T)->bf = EH; 
                    lc->bf = LH; 
                    break; 
            }
            rc->bf = EH;
            L_Rotate(&(*T)->lchild);
            result = TRUE;
            break;
        case EH: 
            (*T)->bf = LH; 
            lc->bf = RH; 
            result = FALSE;
            break;
    }
    R_Rotate(T);
    return result;
}

// 插入之后右子树失衡时的平衡函数
void RightBalance(AVLTree *T) {
    AVLTree lc, rc;
    rc = (*T)->rchild;
    switch (rc->bf) {
        case RH: 
            (*T)->bf = rc->bf = EH; 
            break;
        case LH: 
            lc = rc->lchild;
            switch (lc->bf) {
                case RH: 
                    (*T)->bf = LH; 
                    rc->bf = EH; 
                    break; 
                case EH: 
                    (*T)->bf = rc->bf = EH; 
                    break; 
                case LH: 
                    (*T)->bf = EH; 
                    rc->bf = RH; 
                    break; 
            }
            lc->bf = EH;
            R_Rotate(&(*T)->rchild);
            break;
    }
    L_Rotate(T);
}

// 删除之后右子树失衡时的平衡函数
Status RightDeleteBalance(AVLTree *T) {
    AVLTree lc, rc;
    rc = (*T)->rchild;
    Status result;
    switch (rc->bf) {
        case RH: 
            (*T)->bf = rc->bf = EH; 
            result = TRUE;
            break;
        case LH: 
            lc = rc->lchild;
            switch (lc->bf) {
                case RH: 
                    (*T)->bf = LH; 
                    rc->bf = EH; 
                    break; 
                case EH: 
                    (*T)->bf = rc->bf = EH; 
                    break; 
                case LH: 
                    (*T)->bf = EH; 
                    rc->bf = RH; 
                    break; 
            }
            lc->bf = EH;
            R_Rotate(&(*T)->rchild);
            result = TRUE;
            break;
        case EH: 
            (*T)->bf = RH; 
            rc->bf = LH; 
            result = FALSE;
            break;
    }
    L_Rotate(T);
    return result;
}

// 插入函数
Status InsertAVL(AVLTree *T, ElemType e, Status *taller) {
    if (*T == NULL) {
        *T = (AVLTree)malloc(sizeof(struct AVLTreeNode));
        if (*T == NULL) return FALSE;
        (*T)->data = e;
        (*T)->lchild = (*T)->rchild = NULL;
        (*T)->bf = EH;
        *taller = TRUE;
    } else if (e == (*T)->data) {
        *taller = FALSE;
        return FALSE;
    } else if (e < (*T)->data) {
        if (InsertAVL(&(*T)->lchild, e, taller) == FALSE) 
            return FALSE;
        if (*taller == TRUE) {
            switch ((*T)->bf) {
                case LH: 
                    LeftBalance(T); 
                    *taller = FALSE; 
                    break; 
                case RH: 
                    (*T)->bf = EH; 
                    *taller = FALSE; 
                    break; 
                case EH: 
                    (*T)->bf = LH; 
                    *taller = TRUE; 
                    break; 
            }
        }
    } else {
        if (InsertAVL(&(*T)->rchild, e, taller) == FALSE) 
            return FALSE;
        if (*taller == TRUE) {
            switch ((*T)->bf) {
                case RH: 
                    RightBalance(T); 
                    *taller = FALSE; 
                    break; 
                case LH: 
                    (*T)->bf = EH; 
                    *taller = FALSE; 
                    break; 
                case EH: 
                    (*T)->bf = RH; 
                    *taller = TRUE; 
                    break; 
            }
        }
    }
    return TRUE;
}

// 删除函数
Status DeleteAVL(AVLTree *T, ElemType e, Status *shorter) {
    if (*T == NULL) {
        return FALSE;
    } else if (e < (*T)->data) {
        if (DeleteAVL(&(*T)->lchild, e, shorter) == FALSE) 
            return FALSE;
        if (*shorter == TRUE) {
            switch ((*T)->bf) {
                case LH: 
                    (*T)->bf = EH; 
                    *shorter = TRUE; 
                    break; 
                case EH: 
                    (*T)->bf = RH; 
                    *shorter = FALSE; 
                    break; 
                case RH: 
                    *shorter = RightDeleteBalance(T); 
                    break; 
            }
        }
    } else if (e > (*T)->data) {
        if (DeleteAVL(&(*T)->rchild, e, shorter) == FALSE) 
            return FALSE;
        if (*shorter == TRUE) {
            switch ((*T)->bf) {
                case RH: 
                    (*T)->bf = EH; 
                    *shorter = TRUE; 
                    break; 
                case EH: 
                    (*T)->bf = LH; 
                    *shorter = FALSE; 
                    break; 
                case LH: 
                    *shorter = LeftDeleteBalance(T); 
                    break; 
            }
        }
    } else {
        AVLTree p;
        p = *T;
        if ((*T)->lchild != NULL && (*T)->rchild != NULL) {
            p = (*T)->lchild;
            while (p->rchild != NULL) {
                p = p->rchild;
            }
            (*T)->data = p->data;
            DeleteAVL(&(*T)->lchild, p->data, shorter);
            if (*shorter == TRUE) {
                switch ((*T)->bf) {
                    case LH: 
                        (*T)->bf = EH; 
                        *shorter = TRUE; 
                        break; 
                    case EH: 
                        (*T)->bf = RH; 
                        *shorter = FALSE; 
                        break; 
                    case RH: 
                        *shorter = RightDeleteBalance(T); 
                        break; 
                }
            }
        } else {
            *T = ((*T)->lchild == NULL) ? (*T)->rchild : (*T)->lchild;
            free(p);
            *shorter = TRUE;
        }
    }
    return TRUE;
}

void DestroyAVLTree(AVLTree *T) {
    if (*T == NULL) return;
    if ((*T)->lchild != NULL) 
        DestroyAVLTree(&(*T)->lchild);
    if ((*T)->rchild != NULL) 
        DestroyAVLTree(&(*T)->rchild);
    free(*T);
    *T = NULL;
}

AVLTree SearchAVLTree(AVLTree T, ElemType key) {
    if (T == NULL) 
        return NULL;
    if (T->data == key) 
        return T;
    if (T->data > key) 
        return SearchAVLTree(T->lchild, key);
    else 
        return SearchAVLTree(T->rchild, key);
}

int max(int a, int b) {
    return a > b ? a : b;
}

int GetDepth(AVLTree T) {
    if (T == NULL) 
        return 0;
    return max(GetDepth(T->lchild), GetDepth(T->rchild)) + 1;
}

Status isBalanced(AVLTree T) {
    if (T == NULL) 
        return TRUE;
    if ((T->lchild != NULL && T->data < T->lchild->data) || (T->rchild != NULL && T->data > T->rchild->data)) 
        return FALSE;
    if (isBalanced(T->lchild) == FALSE) 
        return FALSE;
    if (isBalanced(T->rchild) == FALSE) 
        return FALSE;
    int depthLeft = GetDepth(T->lchild);
    int depthRight = GetDepth(T->rchild);
    if (abs(depthLeft - depthRight) > 1) 
        return FALSE;
    return TRUE;
}

void MergeAVLTree(AVLTree *T1, AVLTree T2) {
    Status s;
    if (T2 == NULL) 
        return;
    if (T2->lchild != NULL) 
        MergeAVLTree(T1, T2->lchild);
    InsertAVL(T1, T2->data, &s);
    if (T2->rchild != NULL) 
        MergeAVLTree(T1, T2->rchild);
}

void DivAVLTree(AVLTree R, AVLTree *T1, AVLTree *T2, ElemType e) {
    if (R == NULL) 
        return;
    DivAVLTree(R->lchild, T1, T2, e);
    Status s;
    if (R->data > e) 
        InsertAVL(T2, R->data, &s);
    else 
        InsertAVL(T1, R->data, &s);
    DivAVLTree(R->rchild, T1, T2, e);
}
