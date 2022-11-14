#include <iostream>
using namespace std;
int x[9] = {0};
#define n 8
void printSolution() {
    cout << " ___ ___ ___ ___ ___ ___ ___ ___ \n";
      for ( int i = 1; i <= n; i++) {
    for ( int j = 1; j <= n; j++) {
      if(x[i] == j) printf("| Q ");
      else printf("|   ");
    }
    cout << "|\n";
    cout << "|___|___|___|___|___|___|___|___|\n";
  }
  cout <<"\n\n\n";
}

int checkQueen(int v, int k) {
    for(int i = 1; i < k; i++) {
        if(x[i] == v)           return 0;
        if(x[i] + i == v + k)   return 0;
        if(x[i] - i == v - k)   return 0;
    }
    return 1;
}

void setQueen(int k) {
    for (int v = 1; v <= n; v++) {
        if (checkQueen(v, k)) {
            x[k] = v;
            if (k == n) printSolution();
            else setQueen(k+1);
        }
    }
}

int main() {
    setQueen(1);
}