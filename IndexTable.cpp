// Họ và tên: Đàm Ngọc Khánh
// MSSV: 20205207
// SOICT - HUST
#include <iostream>
#include <fstream>
#include "sll.h"
#include<cctype>
#include <iomanip>

using namespace std;

int isWord(char str[]) {
    int i = 0;
    while(str[i] != '\0') {
        if(!isalpha(str[i])) {
            return 0;
        }
        i++;
    }
    return 1;
}

void sll() {
    
}
int main(int argc, char *argv[]) {
    //f1 -> file vanban.txt
    //f2 -> file stopw.txt
    //f3 -> file index.txt
    ifstream f1, f2;
    ofstream f3;
    f1.open(argv[1]);
    f2.open(argv[2]);
    f3.open(argv[3]);
    char c, str[13];
    int j = 0, count_line = 1;
//List chứa các từ chỉ mục tra cứu
    sllist_w* list_w = createList_w();
//List chứa từ không có ý nghĩa tra cứu
    sllist_w* list_stopw = createList_w();
// đọc các từ không có ý nghĩa tra cứu từ file -> lưu vào list
    while(!f2.eof()) {
        f2 >> str;
        sll_push_w(list_stopw, str);
    }
// lưu từ có ý nghĩa tra cứu vào danh sách liên kết
    do { 
        f1.get(c);
// Đếm dòng
        if(c == '\n') {
            count_line++;
        }
// Nếu gặp  kí tự cách, xuống dòng hoặc kí tự kết thúc file thì lấy ra từ
            if(c == ' ' || c == '\n' || f1.eof() ) {
                str[j] = '\0';
                if(isWord(str) && checkString(list_stopw, str)) {
                    slnode_w* node_w = sll_push_w(list_w, str);
                    sll_push_l(node_w -> list_line, count_line);
                }
                j = 0;
            } else {
               str[j] = tolower(c);
                j++;
            }
    }  while(!f1.eof()) ;
// Ghi vào file index.txt
        for (slnode_w* p_w = list_w -> front; p_w != NULL; p_w = p_w -> next) {
            f3 << setw(10) << left << p_w -> word;
            f3 << setw(5) << left << p_w ->count << "Line:   "  ;
            for (slnode_l* p_l = p_w ->list_line -> front; p_l != NULL; p_l = p_l -> next) {
                f3 << p_l -> line<< "  ";
            }
            f3 << "\n" ;
        }

    f1.close();
    f2.close();
    f3.close();
}