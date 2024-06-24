#include "AVLTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 中序遍历得到有序数组
void InOrderTraversal(AVLTree T, ElemType *arr, int *index) {
    if (T == NULL) return;
    InOrderTraversal(T->lchild, arr, index);
    if (*index == 0 || arr[*index - 1] != T->data) { // 确保没有重复元素
        arr[(*index)++] = T->data;
    }
    InOrderTraversal(T->rchild, arr, index);
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

// 合并两个有序数组
ElemType* MergeSortedArrays(ElemType *arr1, int size1, ElemType *arr2, int size2, int *newSize) {
    int totalSize = size1 + size2;
    ElemType *mergedArray = (ElemType*)malloc(totalSize * sizeof(ElemType));
    int i = 0, j = 0, k = 0;
    while (i < size1 && j < size2) {
        if (arr1[i] < arr2[j]) {
            if (k == 0 || mergedArray[k - 1] != arr1[i]) {
                mergedArray[k++] = arr1[i];
            }
            i++;
        } else if (arr1[i] > arr2[j]) {
            if (k == 0 || mergedArray[k - 1] != arr2[j]) { 
                mergedArray[k++] = arr2[j];
            }
            j++;
        } else { // 相等时只插入一个
            if (k == 0 || mergedArray[k - 1] != arr1[i]) {
                mergedArray[k++] = arr1[i];
            }
            i++;
            j++;
        }
    }
    while (i < size1) {
        if (k == 0 || mergedArray[k - 1] != arr1[i]) {
            mergedArray[k++] = arr1[i];
        }
        i++;
    }
    while (j < size2) {
        if (k == 0 || mergedArray[k - 1] != arr2[j]) { 
            mergedArray[k++] = arr2[j];
        }
        j++;
    }
    *newSize = k;
    return mergedArray;
}

// 创建平衡二叉树的辅助函数
AVLTree CreateAVLFromSortedArray(ElemType *arr, int start, int end) {
    if (start > end) return NULL;
    int mid = (start + end) / 2;
    AVLTree node = (AVLTree)malloc(sizeof(struct AVLTreeNode));
    node->data = arr[mid];
    node->bf = EH;
    node->lchild = CreateAVLFromSortedArray(arr, start, mid - 1);
    node->rchild = CreateAVLFromSortedArray(arr, mid + 1, end);
    return node;
}

// 合并两个AVL树
void MergeAVLTree(AVLTree *T1, AVLTree T2) {
    if (T2 == NULL) return;
    int size1 = GetDepth(*T1) * 2;
    int size2 = GetDepth(T2) * 2;
    ElemType *arr1 = (ElemType*)malloc(size1 * sizeof(ElemType));
    ElemType *arr2 = (ElemType*)malloc(size2 * sizeof(ElemType));
    int index1 = 0, index2 = 0;
    InOrderTraversal(*T1, arr1, &index1);
    InOrderTraversal(T2, arr2, &index2);
    int newSize;
    ElemType *mergedArray = MergeSortedArrays(arr1, index1, arr2, index2, &newSize);
    *T1 = CreateAVLFromSortedArray(mergedArray, 0, newSize - 1);
    free(arr1);
    free(arr2);
    free(mergedArray);
}

// 分裂AVL树
void DivAVLTree(AVLTree R, AVLTree *T1, AVLTree *T2, ElemType e) {
    if (R == NULL) return;
    int size = GetDepth(R) * 2;
    ElemType *arr = (ElemType*)malloc(size * sizeof(ElemType));
    int index = 0;
    InOrderTraversal(R, arr, &index);
    int mid = 0;
    for (int i = 0; i < index; i++) {
        if (arr[i] > e) {
            mid = i;
            break;
        }
    }
    *T1 = CreateAVLFromSortedArray(arr, 0, mid - 1);
    *T2 = CreateAVLFromSortedArray(arr, mid, index - 1);
    free(arr);
}
