// Họ và tên: Đàm Ngọc Khánh
// MSSV: 20205207
// File này bao gồm 1 số cấu trúc của danh sách liên kết đơn, hàm khởi tạo, và hàm push 
#include <iostream>
#include <string>
using namespace std;

// Cấu trúc node danh sách móc nối đơn lưu trữ các dòng.
typedef struct slnode_l {
  int line;
  slnode_l* next;
}slnode_l;
// Cấu trúc danh sách liên kết đơn các dòng xuất hiện
typedef struct sllist_l {
  slnode_l *front;
  slnode_l *back;
}sllist_l;
// Cấu trúc node của danh sách móc nối đơn các từ
typedef struct slnode_w {
    string word;
    int count;
    sllist_l* list_line;
    slnode_w* next;
}slnode_w;
// Cấu trúc danh sách liên kết đơn các từ
typedef struct sllist_w {
  slnode_w *front;
  slnode_w *back;
}sllist_w;
// Hàm khởi tạo 1 danh sách móc nối các từ
sllist_w* createList_w() {
   sllist_w * list = new sllist_w;
  list -> front = list -> back = NULL;
  return list;
}
// Hàm tạo list danh sách liên kết đơn các dòng xuất hiện
sllist_l *createList_l() {
  sllist_l * list = new sllist_l;
  list -> front = list -> back = NULL;
  return list;
}
// Hàm tạo 1 node mới với đầu vào là 1 string
slnode_w* createNode_w(string str) {
  slnode_w* node_new = new slnode_w;
  node_new -> word= str;
  node_new -> count = 1;
  node_new -> list_line = createList_l();
  node_new -> next = NULL;
  return node_new;
}

// Hàm tạo 1 node với đầu vào là dòng xuất hiện
slnode_l* createNode_l(int line) {
  slnode_l* node_new = new slnode_l;
  node_new -> line = line;
  node_new -> next = NULL;
  return node_new;
}
// Hàm thêm node vào danh sách đơn lưu trữ dòng xuất hiện
void sll_push_l(sllist_l *list, int line ) {
  if(list -> front == NULL) {
    slnode_l* node = createNode_l(line);
    list -> back = list -> front = node;
  } else {
    if(list -> back ->line != line) {
      slnode_l* node = createNode_l(line);
      list -> back -> next = node;
      list -> back = node;
    }
  }
}
// Hàm chèn node word vào danh sách liên kết đơn các từ
slnode_w* sll_push_w(sllist_w *list, string w) {
  if (list -> front == NULL) {
    slnode_w* node = createNode_w(w);
    list -> front = list -> back = node;
    return node;
  } else {
    if((list -> front -> word).compare(w) > 0) {
      slnode_w* node = createNode_w(w);
      node -> next = list -> front;
      list -> front = node;
      return node;
    } else if ((list -> back -> word).compare(w) < 0) {
      slnode_w* node = createNode_w(w);
      list -> back -> next = node;
      list -> back = node;
      return node;
    } else {
      for(slnode_w* i_node = list ->front; i_node != NULL ; i_node = i_node -> next) {
        if ((i_node -> word).compare(w) == 0) {
          i_node -> count ++;
          return i_node;
        }
        if((i_node -> word).compare(w) < 0 && (i_node -> next -> word).compare(w) > 0) {
           slnode_w* node = createNode_w(w);
           node -> next = i_node -> next;
           i_node -> next = node;
           return node;
        }
      }
    }
  }
  return NULL;
}

// Hàm kiểm tra string có trong danh sách hay chưa
int checkListString(sllist_w* list, string str) {
  for (slnode_w* p = list -> front; p != NULL; p = p -> next) {
    if((p ->word).compare(str) == 0) return 0;
  }
  return 1;
}




