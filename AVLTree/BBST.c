#include "BBST.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 中序遍历
void InOrderTraverse(BBSTree T) {
    if (NULL == T) return;
    InOrderTraverse(T->lchild);
    printf("%d ", T->data);
    InOrderTraverse(T->rchild);
}

// 左旋转
void L_Rotation(BBSTree *T) {
    BBSTree t;
    t = (*T)->rchild;
    (*T)->rchild = t->lchild;
    t->lchild = *T;
    *T = t;
}

// 右旋转
void R_Rotation(BBSTree *T) {
    BBSTree t;
    t = (*T)->lchild;
    (*T)->lchild = t->rchild;
    t->rchild = *T;
    *T = t;
}

// 插入之后树 T 失衡时的平衡函数
void L_Balance(BBSTree *T) {
    BBSTree lc, rc;
    lc = (*T)->lchild;
    switch (lc->bf) {
        case 1: // LH
            (*T)->bf = lc->bf = 0; // EH
            break;
        case -1: // RH
            rc = lc->rchild;
            switch (rc->bf) {
                case 1: (*T)->bf = -1; lc->bf = 0; break; // LH
                case 0: (*T)->bf = lc->bf = 0; break; // EH
                case -1: (*T)->bf = 0; lc->bf = 1; break; // RH
            }
            rc->bf = 0;
            L_Rotation(&(*T)->lchild);
            break;
    }
    R_Rotation(T);
}

// 删除之后树 T 的左子树失衡时的平衡函数
Status L_D_Balance(BBSTree *T) {
    BBSTree lc, rc;
    lc = (*T)->lchild;
    Status result;
    switch (lc->bf) {
        case 1: // LH
            (*T)->bf = lc->bf = 0; // EH
            result = YES;
            break;
        case -1: // RH
            rc = lc->rchild;
            switch (rc->bf) {
                case 1: (*T)->bf = -1; lc->bf = 0; break; // LH
                case 0: (*T)->bf = lc->bf = 0; break; // EH
                case -1: (*T)->bf = 0; lc->bf = 1; break; // RH
            }
            rc->bf = 0;
            L_Rotation(&(*T)->lchild);
            result = YES;
            break;
        case 0: // EH
            (*T)->bf = 1; // LH
            lc->bf = -1; // RH
            result = NO;
            break;
    }
    R_Rotation(T);
    return result;
}

// 插入之后右子树失衡时的平衡函数
void R_Balance(BBSTree *T) {
    BBSTree lc, rc;
    rc = (*T)->rchild;
    switch (rc->bf) {
        case -1: // RH
            (*T)->bf = rc->bf = 0; // EH
            break;
        case 1: // LH
            lc = rc->lchild;
            switch (lc->bf) {
                case -1: (*T)->bf = 1; rc->bf = 0; break; // RH
                case 0: (*T)->bf = rc->bf = 0; break; // EH
                case 1: (*T)->bf = 0; rc->bf = -1; break; // LH
            }
            lc->bf = 0;
            R_Rotation(&(*T)->rchild);
            break;
    }
    L_Rotation(T);
}

// 删除之后右子树失衡时的平衡函数
Status R_D_Balance(BBSTree *T) {
    BBSTree lc, rc;
    rc = (*T)->rchild;
    Status result;
    switch (rc->bf) {
        case -1: // RH
            (*T)->bf = rc->bf = 0; // EH
            result = YES;
            break;
        case 1: // LH
            lc = rc->lchild;
            switch (lc->bf) {
                case -1: (*T)->bf = 1; rc->bf = 0; break; // RH
                case 0: (*T)->bf = rc->bf = 0; break; // EH
                case 1: (*T)->bf = 0; rc->bf = -1; break; // LH
            }
            lc->bf = 0;
            R_Rotation(&(*T)->rchild);
            result = YES;
            break;
        case 0: // EH
            (*T)->bf = -1; // RH
            rc->bf = 1; // LH
            result = NO;
            break;
    }
    L_Rotation(T);
    return result;
}

// 插入函数
Status InsertAVL(BBSTree *T, ElemType e, Status *taller) {
    if (*T == NULL) {
        *T = (BBSTree)malloc(sizeof(struct BBSTNode));
        if (*T == NULL) return NO;
        (*T)->data = e;
        (*T)->bf = 0; // EH
        *taller = YES;
        (*T)->lchild = (*T)->rchild = NULL;
    } else if (e == (*T)->data) {
        *taller = NO;
        return NO;
    } else if (e < (*T)->data) {
        if (InsertAVL(&(*T)->lchild, e, taller) == NO) return NO;
        if (*taller == YES) {
            switch ((*T)->bf) {
                case 1: L_Balance(T); *taller = NO; break; // LH
                case -1: (*T)->bf = 0; *taller = NO; break; // RH
                case 0: (*T)->bf = 1; *taller = YES; break; // EH
            }
        }
    } else {
        if (InsertAVL(&(*T)->rchild, e, taller) == NO) return NO;
        if (*taller == YES) {
            switch ((*T)->bf) {
                case -1: R_Balance(T); *taller = NO; break; // RH
                case 1: (*T)->bf = 0; *taller = NO; break; // LH
                case 0: (*T)->bf = -1; *taller = YES; break; // EH
            }
        }
    }
    return YES;
}

// 删除函数
Status DeleteAVL(BBSTree *T, ElemType e, Status *shorter) {
    if (*T == NULL) {
        return NO;
    } else if (e < (*T)->data) {
        if (DeleteAVL(&(*T)->lchild, e, shorter) == NO) return NO;
        if (*shorter == YES) {
            switch ((*T)->bf) {
                case 1: (*T)->bf = 0; *shorter = YES; break; // LH
                case 0: (*T)->bf = -1; *shorter = NO; break; // EH
                case -1: *shorter = R_D_Balance(T); break; // RH
            }
        }
    } else if (e > (*T)->data) {
        if (DeleteAVL(&(*T)->rchild, e, shorter) == NO) return NO;
        if (*shorter == YES) {
            switch ((*T)->bf) {
                case -1: (*T)->bf = 0; *shorter = YES; break; // RH
                case 0: (*T)->bf = 1; *shorter = NO; break; // EH
                case 1: *shorter = L_D_Balance(T); break; // LH
            }
        }
    } else {
        BBSTree p;
        p = *T;
        if ((*T)->lchild != NULL && (*T)->rchild != NULL) {
            p = (*T)->lchild;
            while (p->rchild != NULL) {
                p = p->rchild;
            }
            (*T)->data = p->data;
            DeleteAVL(&(*T)->lchild, p->data, shorter);
            if (*shorter == YES) {
                switch ((*T)->bf) {
                    case 1: (*T)->bf = 0; *shorter = YES; break; // LH
                    case 0: (*T)->bf = -1; *shorter = NO; break; // EH
                    case -1: *shorter = R_D_Balance(T); break; // RH
                }
            }
        } else {
            *T = ((*T)->lchild == NULL) ? (*T)->rchild : (*T)->lchild;
            free(p);
            *shorter = YES;
        }
    }
    return YES;
}

void DestroyBBST(BBSTree *T) {
    if (*T == NULL) return;
    if ((*T)->lchild != NULL) DestroyBBST(&(*T)->lchild);
    if ((*T)->rchild != NULL) DestroyBBST(&(*T)->rchild);
    free(*T);
    *T = NULL;
}

BBSTree SearchBBST(BBSTree T, ElemType key) {
    if (T == NULL) return NULL;
    if (T->data == key) return T;
    if (T->data > key) return SearchBBST(T->lchild, key);
    else return SearchBBST(T->rchild, key);
}

int max(int a, int b) {
    return a > b ? a : b;
}

int GetDepth(BBSTree T) {
    if (T == NULL) return 0;
    return max(GetDepth(T->lchild), GetDepth(T->rchild)) + 1;
}

Status isBalanced(BBSTree T) {
    if (T == NULL) return YES;
    if ((T->lchild != NULL && T->data < T->lchild->data) || (T->rchild != NULL && T->data > T->rchild->data)) return NO;
    if (isBalanced(T->lchild) == NO) return NO;
    if (isBalanced(T->rchild) == NO) return NO;
    int depthLeft = GetDepth(T->lchild);
    int depthRight = GetDepth(T->rchild);
    if (abs(depthLeft - depthRight) > 1) return NO;
    return YES;
}

void MergeBBSTree(BBSTree *T1, BBSTree T2) {
    Status s;
    if (T2 == NULL) return;
    if (T2->lchild != NULL) MergeBBSTree(T1, T2->lchild);
    InsertAVL(T1, T2->data, &s);
    if (T2->rchild != NULL) MergeBBSTree(T1, T2->rchild);
}

void DivBBSTree(BBSTree R, BBSTree *T1, BBSTree *T2, ElemType e) {
    if (R == NULL) return;
    DivBBSTree(R->lchild, T1, T2, e);
    Status s;
    if (R->data > e) InsertAVL(T2, R->data, &s);
    else InsertAVL(T1, R->data, &s);
    DivBBSTree(R->rchild, T1, T2, e);
}
