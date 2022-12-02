// Họ và tên: Đàm Ngọc Khánh
// MSSV: 20205207
// SOICT - HUST
#include <iostream>
#include <fstream>
#include "sll_hash.cpp"
#include <cctype>
#include <iomanip>
#include "bns.cpp"

using namespace std;
// Kiểm tra xem chuỗi kí tự có phải 1 từ không 
int isWord(char str[])
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (!isalpha(str[i]))
        {
            return 0;
        }
        i++;
    }
    return 1;
}


void printMenu()
{
    cout << "Data structure: \n";
    cout << "1. Single link list\n";
    cout << "2. Binary tree\n";
    cout << "3. Hash table\n";
}
int main(int argc, char *argv[])
{
    // f1 -> file vanban.txt
    // f2 -> file stopw.txt
    // f3 -> file index.txt
    printMenu();
    int choice;
    cout << "Enter your choice: ";
    cin >> choice;
    ifstream f1, f2;
    ofstream f3;
    f1.open(argv[1]);
    f2.open(argv[2]);
    f3.open(argv[3]);
    //
    if (choice == 1)
    {
        char c, str[13];
        int j = 0, count_line = 1;
        // List chứa các từ chỉ mục tra cứu
        sllist_w *list_w = createList_w();
        // List chứa từ không có ý nghĩa tra cứu
        sllist_w *list_stopw = createList_w();
        // đọc các từ không có ý nghĩa tra cứu từ file -> lưu vào list
        while (!f2.eof())
        {
            f2 >> str;
            sll_push_w(list_stopw, str);
        }
        // lưu từ có ý nghĩa tra cứu vào danh sách liên kết
        do {
            f1.get(c);
            // Đếm dòng
            if (c == '\n') {
                count_line++;
            }
            // Nếu gặp  kí tự cách, xuống dòng hoặc kí tự kết thúc file thì lấy ra từ
            if (c == ' ' || c == '\n' || f1.eof()) {
                str[j] = '\0';
                if (isWord(str) && checkListString(list_stopw, str)) {
                    slnode_w *node_w = sll_push_w(list_w, str);
                    sll_push_l(node_w->list_line, count_line);
                }
                j = 0;
            }
            else {
                str[j] = tolower(c);
                j++;
            }
        } while (!f1.eof());
        // Ghi vào file index.txt
        for (slnode_w *p_w = list_w->front; p_w != NULL; p_w = p_w->next) {
            f3 << setw(10) << left << p_w->word;
            f3 << setw(5) << left << p_w->count << "Line:   ";
            for (slnode_l *p_l = p_w->list_line->front; p_l != NULL; p_l = p_l->next) {
                f3 << p_l->line << "  ";
            }
            f3 << "\n";
        }
// Message : 
        cout << "Please check the result in index.txt\n";
    }
    if(choice == 2) {
        char c, str[13];
        int j = 0, count_line = 1;
        node_tree* root_w = NULL;
        node_tree* root_stopw = NULL ;


        while(!f2.eof()) {
            f2 >> str;
            insertTree(root_stopw, str);
        }
        do {
            f1.get(c);
            // Đếm dòng
            if (c == '\n') {
                count_line++;
            }
            // Nếu gặp  kí tự cách, xuống dòng hoặc kí tự kết thúc file thì lấy ra từ
            if (c == ' ' || c == '\n' || f1.eof()) {
                str[j] = '\0';
                if (isWord(str) && checkTreeString(root_stopw, str)) {
                    node_tree* node_t = insertTree(root_w, str);
                    sll_push_line(node_t ->list_l, count_line);
                }
                j = 0;
            } else {
                str[j] = tolower(c);
                j++;
            }
        } while(!f1.eof());
// Ghi ra file
         writeFile(root_w, &f3);
    }
    if(choice == 3) {
        char c, str[13];
        // Bảng băm 
        sllist_w** hash_list = new sllist_w*[275];
        for (int i = 0; i < 275; i++) {
            hash_list[i] = createList_w();
        }
        // List chứa các từ chỉ mục tra cứu
        sllist_w *list_stopw = createList_w();
        while (!f2.eof()) {
            f2 >> str;
            sll_push_w(list_stopw, str);
        }
        int count_line = 1, j = 0, index;
        do {
            f1.get(c);
            // Đếm dòng
            if (c == '\n') {
                count_line++;
            }
            // Nếu gặp kí tự cách, xuống dòng hoặc kí tự kết thúc file thì lấy ra từ
            if (c == ' ' || c == '\n' || f1.eof()) {
                str[j] = '\0';
                if (isWord(str) && checkListString(list_stopw, str)) {
                    index = hash_index(str);
                    slnode_w *node_w = sll_push_w(hash_list[index], str);
                    sll_push_l(node_w -> list_line, count_line);

                }
                j = 0;
            }
            else {
                str[j] = tolower(c);
                j++;
            }
        } while (!f1.eof());
        writeHashToFile(hash_list, &f3);
    }
    f1.close();
    f2.close();
    f3.close();
}