#include <iostream>
#include<cctype>
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
int main() {
  char str[10] = "Hel";
  cout << isWord(str) ;
}