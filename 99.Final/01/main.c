#include <stdlib.h>
#include <assert.h>
#include <stdio.h>


struct BiTreeNode {
    int nodeId;                 // each node has a unique identifier
    struct BiTreeNode *left;    // left sub-tree
    struct BiTreeNode *right;   // right sub-tree
};

void PreOrder(struct BiTreeNode *root);

void InOrder(struct BiTreeNode *root);

void PostOrder(struct BiTreeNode *root);

void ReleaseBiTree(struct BiTreeNode *root);


struct BiTreeNode *CreateOneNode(int nodeId, struct BiTreeNode *left, struct BiTreeNode *right) {
    struct BiTreeNode *pNode = (struct BiTreeNode *) malloc(sizeof(struct BiTreeNode));
    assert(pNode);
    pNode->left = left;
    pNode->right = right;
    pNode ->nodeId = nodeId;
    return pNode;
}

struct BiTreeNode *CreateBiTree(int *preOrder, int *inOrder, int n) {
    if(n <= 0) {
        return NULL;
    } else {
        // 创建当前树的根节点。在前序遍历中，第一个元素是根节点,因此第一个位置应该是preOrder[0]
        struct BiTreeNode *pNode = CreateOneNode(preOrder[0], NULL, NULL);
        if (n>1){
            for (int i =0; i< n; i++){
                // 循环的目的是在中序遍历中找到根节点的位置（preOrder[0]），
                // 因为中序遍历中，根节点左边的元素属于左子树，右边的元素属于右子树。
                if (inOrder[i] == preOrder[0]) {
                // if ((inOrder + i) == preOrder) { （错误的）
                // if (*(inOrder + i) == *preOrder) {（这是正确的）
                    // 1. 左子树的前序遍历数组的起始位置是在根节点之后的第一个位置, 因此应该是 preOrder + 1
                    // 2. 左子树的中序遍历数组的起始位置和原中序遍历的起始位置相同 inOrder的位置不变, 因此应该是 inOrder。
                    // 3. 左子树的节点数为 i，因为中序遍历中前 i 个元素属于左子树, 因此应该是 i
                    pNode->left = CreateBiTree(preOrder + 1, inOrder, i);
                    // pNode->left = CreateBiTree(&preOrder[1], inOrder, i);
                    // 1. 右子树的前序遍历数组的起始位置在左子树节点数 i 之后, 所以应该是 preOrder + i + 1。
                    // 2. 右子树的中序遍历数组的起始位置在根节点之后，因此应该是 inOrder + i + 1
                    // 3. 右子树的节点数为 n - i - 1，因为总节点数是 n，左子树节点数是 i，再去掉根节点。
                    pNode->right = CreateBiTree(preOrder + i + 1, inOrder + i + 1, n - i - 1);
                    break;
                }
            }
        }
        return pNode;
    }
}

struct BiTreeNode *CreateBiTree(int *postOrder, int *inOrder, int n) {
    if(n <= 0) {
        return NULL;
    } else {
        // 创建当前树的根节点。在前序遍历中，第一个元素是根节点,因此第一个位置应该是preOrder[0]
        struct BiTreeNode *pNode = CreateOneNode(postOrder[n - 1], NULL, NULL);
        if (n>1){
            for (int i =0; i< n; i++){
                // 循环的目的是在中序遍历中找到根节点的位置（preOrder[0]），
                // 因为中序遍历中，根节点左边的元素属于左子树，右边的元素属于右子树。
                if (inOrder[i] == postOrder[n - 1]) {
                // if ((inOrder + i) == preOrder) { （错误的）
                // if (*(inOrder + i) == *preOrder) {（这是正确的）
                    // 1. 左子树的前序遍历数组的起始位置是在根节点之后的第一个位置, 因此应该是 preOrder + 1
                    // 2. 左子树的中序遍历数组的起始位置和原中序遍历的起始位置相同 inOrder的位置不变, 因此应该是 inOrder。
                    // 3. 左子树的节点数为 i，因为中序遍历中前 i 个元素属于左子树, 因此应该是 i
                    pNode->left = CreateBiTree(postOrder, inOrder, i);
                    // pNode->left = CreateBiTree(&preOrder[1], inOrder, i);
                    // 1. 右子树的前序遍历数组的起始位置在左子树节点数 i 之后, 所以应该是 preOrder + i + 1。
                    // 2. 右子树的中序遍历数组的起始位置在根节点之后，因此应该是 inOrder + i + 1
                    // 3. 右子树的节点数为 n - i - 1，因为总节点数是 n，左子树节点数是 i，再去掉根节点。
                    pNode->right = CreateBiTree(postOrder + i, inOrder + i + 1, n - i - 1);
                    break;
                }
            }
        }
        return pNode;
    }
}

struct BiTreeNode *CreateBiTree(int *preOrder, int *inOrder, int n) {
    if(n <= 0) {
        return NULL;
    } else {
        struct BiTreeNode *pNode = CreateOneNode(___________, ___________, ___________);
        if (___________){
            for (int i =0; i< n; i++){
                if (______________________) {
                    pNode->left = CreateBiTree(___________, ___________, ___________);
                    pNode->right = CreateBiTree(___________, ___________, ___________);
                    break;
                }
            }
        }
        return pNode;
    }
}

// struct BiTreeNode *CreateBiTree(int *preOrder, int n) {
//     if(n <= 0) {
//         return NULL;
//     } else {
//         // 创建当前树的根节点。在前序遍历中，第一个元素是根节点,因此第一个位置应该是preOrder[0]
//         struct BiTreeNode *pNode = CreateOneNode(preOrder[0],NULL, NULL);
//         if (n>1){
//             // 0    1  2  3   4   5  6
//             // 20, 10, 5, 1, 40, 30, 50
//             // 20, 10, 5, 3, 2
//             int right = -1;
//             for (int i=0; i< n; i++) {
//                 if (preOrder[i] > preOrder[0]) {
//                     right = i;
//                     break;
//                 }
//             }
//             // 没有找到右子树
//             if (right == -1) {
//                 pNode->left = CreateBiTree(preOrder + 1, n - 1);
//             } else {
//                 pNode->left = CreateBiTree(preOrder + 1, right - 1);
//                 pNode->right = CreateBiTree(preOrder + right, n - right);
//             }
        
//         }
//         return pNode;
//     }
// }

void ReleaseBiTree(struct BiTreeNode *root) {
    if (root) {
        ReleaseBiTree(root->left);
        ReleaseBiTree(root->right);
        free(root);
    }
}


void PreOrder(struct BiTreeNode *root){
    // 等价与 if (root != NULL) {
    if (root) {
        printf(" %d ", root->nodeId);
        PreOrder(root->left);    
        PreOrder(root->right);
    }
}

void InOrder(struct BiTreeNode *root){
    if (root) {
        InOrder(root->left); 
        printf(" %d ", root->nodeId);   
        InOrder(root->right);
    }
}

void PostOrder(struct BiTreeNode *root){
    if (root) {
        PostOrder(root->left); 
        PostOrder(root->right);
        printf(" %d ", root->nodeId);  
    }
}

int main(void) {
    // Given a binary tree in which each node has a unique identifier
    // its preorder and inorder traversals are represented as follows.
    int inOrder[] = { 10,  20, 30, 40, 50};
    int preOrder[] = {20, 10, 40, 30, 50};
    assert(sizeof(preOrder) == sizeof(inOrder));
    int n = sizeof(preOrder)/sizeof(preOrder[0]);
    struct BiTreeNode * root = CreateBiTree(preOrder, inOrder, n);
    PostOrder(root);
    ReleaseBiTree(root);

    return 0;
}