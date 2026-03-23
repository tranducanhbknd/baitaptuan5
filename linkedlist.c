#include <stdio.h>
#include <stdlib.h>

// Định nghĩa node của danh sách liên kết
struct node {
    int data;           // dữ liệu
    struct node* next;  // con trỏ tới node tiếp theo
};

// (a) In toàn bộ danh sách
void display(struct node* head) {
    struct node* temp = head; // dùng con trỏ duyệt
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;    // sang node tiếp theo
    }
    printf("NULL\n");
}

// (b) Thêm phần tử vào cuối danh sách
struct node* addback(struct node* head, int data) {
    // cấp phát node mới
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->next = NULL;

    // nếu danh sách rỗng → node mới là head
    if (head == NULL) return newnode;

    // duyệt đến node cuối
    struct node* temp = head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newnode; // nối node mới vào cuối
    return head;
}

// (c) Tìm node có giá trị data
struct node* find(struct node* head, int data) {
    while (head != NULL) {
        if (head->data == data)
            return head; // tìm thấy
        head = head->next;
    }
    return NULL; // không tìm thấy
}

// (d) Xóa node được trỏ bởi pelement
struct node* delnode(struct node* head, struct node* pelement) {
    if (head == NULL || pelement == NULL) return head;

    // trường hợp xóa node đầu
    if (head == pelement) {
        struct node* temp = head;
        head = head->next; // cập nhật head
        free(temp);        // giải phóng bộ nhớ
        return head;
    }

    // tìm node đứng trước pelement
    struct node* prev = head;
    while (prev->next != pelement)
        prev = prev->next;

    prev->next = pelement->next; // bỏ qua node cần xóa
    free(pelement);              // giải phóng node

    return head;
}

// (e) Xóa toàn bộ danh sách
void freelist(struct node* head) {
    struct node* temp;
    while (head != NULL) {
        temp = head;       // lưu node hiện tại
        head = head->next; // sang node tiếp theo
        free(temp);        // giải phóng node
    }
}

// (f) Test chương trình
int main() {
    struct node* head = NULL;

    // thêm phần tử
    head = addback(head, 2);
    head = addback(head, 3);
    head = addback(head, 5);
    head = addback(head, 6);
    head = addback(head, 9);
    head = addback(head, 1);
    head = addback(head, 7);


    printf("List: ");
    display(head);

    // tìm phần tử
    struct node* f = find(head, 3);
    if (f) printf("Found: %d\n", f->data);

    // xóa phần tử
    head = delnode(head, f);

    printf("After delete 2: ");
    display(head);

    // giải phóng toàn bộ
    freelist(head);
    head = NULL;  // 🔥 rất quan trọng

    printf("danh sach sau khi xoa het: ");
    display(head);

    return 0;
}
