#include <stdio.h>
#include <stdlib.h>

// Định nghĩa node của cây nhị phân
struct tnode {
    int data;              // dữ liệu
    struct tnode* left;    // con trái
    struct tnode* right;   // con phải
};

// (a) Cấp phát node mới
struct tnode* talloc(int data) {
    struct tnode* node = (struct tnode*)malloc(sizeof(struct tnode));
    node->data = data;
    node->left = node->right = NULL; // ban đầu chưa có con
    return node;
}

// (b) Thêm node vào cây (Binary Search Tree)
struct tnode* addnode(struct tnode* root, int data) {
    if (root == NULL)
        return talloc(data); // nếu rỗng → tạo node mới

    // nhỏ hơn → sang trái
    if (data < root->data)
        root->left = addnode(root->left, data);
    else
        root->right = addnode(root->right, data); // lớn hơn → sang phải

    return root;
}

// (c) Duyệt preorder (root-left-right)
void preorder(struct tnode* root) {
    if (root != NULL) {
        printf("%d ", root->data); // thăm node
        preorder(root->left);      // duyệt trái
        preorder(root->right);     // duyệt phải
    }
}

// (d) Duyệt inorder (left-root-right)
void inorder(struct tnode* root) {
    if (root != NULL) {
        inorder(root->left);       // trái
        printf("%d ", root->data);// root
        inorder(root->right);      // phải
    }
    // 👉 với BST → kết quả tăng dần
}

// (e) Xóa toàn bộ cây (postorder)
int deltree(struct tnode* root) {
    if (root == NULL) return 0;

    // xóa từ dưới lên (trái → phải → root)
    int left = deltree(root->left);
    int right = deltree(root->right);

    free(root); // giải phóng node hiện tại

    return left + right + 1; // tổng số node đã xóa
}

// (f) Test
int main() {
    struct tnode* root = NULL;

    int arr[] = {3,1,0,2,8,6,5,9};

    // xây dựng cây
    for (int i = 0; i < 8; i++)
        root = addnode(root, arr[i]);

    printf("Preorder: ");
    preorder(root);

    printf("\nInorder: ");
    inorder(root);

    // xóa cây
    int count = deltree(root);
    printf("\nDeleted nodes: %d\n", count);

    return 0;
}
