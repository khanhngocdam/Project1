// Họ và tên: Đàm ngọc Khánh
// MSSV: 20205207
// File này bao gồm: 
//  + cấu trúc cây nhị phân tìm kiếm với keyword là từ chỉ mục 
// và một số hàm khởi tạo, push, duyệt
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

// Cấu trúc node danh sách móc nối đơn lưu trữ các dòng.
typedef struct slnode_line {
  int line;
  slnode_line* next;
}slnode_line;

// Cấu trúc danh sách liên kết đơn các dòng xuất hiện
typedef struct sllist_line {
  slnode_line *front;
  slnode_line *back;
}sllist_line;

// Hàm tạo list danh sách liên kết đơn các dòng xuất hiện
sllist_line *createList_line() {
  sllist_line * list = new sllist_line;
  list -> front = list -> back = NULL;
  return list;
}

// Hàm tạo 1 node với đầu vào là dòng xuất hiện
slnode_line* createNode_line(int line) {
  slnode_line* node_new = new slnode_line;
  node_new -> line = line;
  node_new -> next = NULL;
  return node_new;
}

// Hàm thêm node vào danh sách đơn lưu trữ dòng xuất hiện
void sll_push_line(sllist_line *list, int line ) {
  if(list -> front == NULL) {
    slnode_line* node = createNode_line(line);
    list -> back = list -> front = node;
  } else {
    if(list -> back ->line != line) {
      slnode_line* node = createNode_line(line);
      list -> back -> next = node;
      list -> back = node;
    }
  }
}

// Khai báo node của cây nhị phân
 typedef struct node_tree {
    int count;
    string word;
    sllist_line* list_l;
    node_tree* left;
    node_tree* right;
 }node_tree;

// Hàm tạo node tree với đầu vào là string w;
 node_tree* createNodeTree(string w) {
    node_tree* node_t = new node_tree;
    node_t -> count = 1;
    node_t ->left = node_t -> right = NULL;
    node_t -> word = w;
    node_t -> list_l = createList_line();
    return node_t;
 }
 // Hàm chèn node vào cây
 node_tree* insertTree(node_tree* &root, string w) {
    if (root == NULL) {
       root = createNodeTree(w);
       return root;
    } else {
        if((root -> word).compare(w) == 0) {
            root -> count ++;
            return root;
        } else if((root -> word).compare(w) < 0) {
             return insertTree(root -> right, w);
        } else {
             return insertTree(root -> left, w);
        }
    }
 }
 
 //kiểm tra xem word có trong file stopw hay không
 int checkTreeString(node_tree* &root, string w) {
    if(root != NULL) {
        if((root -> word).compare(w) == 0) return 0;
        else if((root -> word).compare(w) < 0) {
            return checkTreeString(root -> right, w);
        } else {
            return checkTreeString(root -> left, w);
        }
    }
    return 1;
 }

// viết vào file 
void writeFile(node_tree* &root, ofstream *f){
    if (root!=NULL){
        //su dung de quy de duyet tiep cay con trai
         writeFile(root->left, f);
        //xy ly node goc
        *f << setw(10) << left << root->word;
        *f << setw(5) << left << root->count << "Line:   ";
        for (slnode_line *p_l = root->list_l->front; p_l != NULL; p_l = p_l->next)
            {
                *f << p_l->line << "  ";
            }
            *f << "\n";
        //su dung de quy de duyet tiep cay con phai
        writeFile(root->right, f);
    }
}

