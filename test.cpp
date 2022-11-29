#include <iostream>
#include<cctype>
#include<string>
using namespace std;

typedef struct node_tree {
  node_tree* left;
  node_tree* right;
  int v;
}node_tree;

node_tree* createNodeTree(int value) {
  node_tree* node = new node_tree;
  node -> left = node -> right = NULL;
  node -> v = value;
  return node;
}
 void insertTree(node_tree* &root, int value) {
    
    if(root != NULL) {
        if(root -> v == value) {
        } else if(root -> v < value) {
             insertTree(root -> right, value);
        } else {
             insertTree(root -> left, value);
        }
    } else {
      root = createNodeTree(value);
    }
 }
int main() {
  node_tree* root = createNodeTree(12);
  cout << root <<"  "<<root ->v<<endl;
  cout << root -> right << root -> left <<endl;
  insertTree(root, 15);
  cout << root -> right->v ;
}