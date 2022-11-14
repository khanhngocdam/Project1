#include <iostream>
#include <fstream>
using namespace std;
    int n, f = 0, min_path = INT_MAX;
    int **city;
    int *visited;
    int *x, *path;
void printMenuCreatData() {
    cout << "1. From keyboard\n";
    cout << "2. File\n";
    cout << "Enter your choice:  ";
}
//-------------------------------------------------------------
void printMenuAlgorithm() {
    cout << "1. Complete search\n";
    cout << "2. Branch and bound\n";
    cout << "Enter your choice:   ";
}
//--------------------------------------------------------------
int cityMin(int x[], int k) {
    int cmin = INT_MAX;
    for(int i = 0; i < n; i++) {
        for( int j = 0; j < n; j++) {
            if(i != j && (visited[i] == 0 || visited[j] == 0) && city[i][j] < cmin )
                	cmin = city[i][j]; 
        }
    }    
    if (city[x[k]][x[0]] < cmin) return city[x[k]][0];
    else return cmin;    
}
//-------------------------------------------------------------
//Branch and bound
void tryBranchBound(int k) {
    for(int v = 0; v < n; v++) {
        if(visited[v] == 0) {
            x[k] = v;
            visited[v] = 1;
    	    f += city[x[k-1]][x[k]];
            if(k == n-1) {
                if(f + city[x[n-1]][x[0]] < min_path) {
// Update result and min path
                    min_path = f + city[x[n-1]][x[0]]; 
                    for( int j = 0; j < n; j++) {
                        path[j] = x[j];
                    }
                } 
            } else {
                if ( f + cityMin(x,k) * ( n - k) < min_path) tryBranchBound(k+1);
            }
            f = f - city[x[k-1]][x[k]];
            visited[v] = 0;
        }
    }
}
//-------------------------------------------------------------
void tryCompleteSearch(int k) {
    for(int v = 0; v < n; v++) {
        if(visited[v] == 0) {
            x[k] = v;
            visited[v] = 1;
    	    f += city[x[k-1]][x[k]];
            if(k == n-1) {
                if(f + city[x[n-1]][x[0]] < min_path) {
// Update result and min path
                    min_path = f + city[x[n-1]][x[0]]; 
                    for( int j = 0; j < n; j++) {
                        path[j] = x[j];
                    }
                } 
            } else {
                 tryCompleteSearch(k+1);
            }
            f = f - city[x[k-1]][x[k]];
            visited[v] = 0;
        }
    }
}
//--------------------------------------------------------------
int main() {

    int choice_input, choice_algorithm;
    printMenuCreatData();
    cin >> choice_input;
    if(choice_input == 1) {
        cout << "Enter the number of cities:  " ;
        cin >> n;
// dynamic allocation of 2 dimensional arrays
        city = new int*[n];
        visited = new int[n]; 
        x = new int[n];
        path = new int[n];
        for(int i = 0; i < n; i++) {
            city[i] = new int[n];
            visited[i] = 0;
        }   
        cout << "Enter the cost of moving between cities: \n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j ++) {
                if (i != j) {
                     cout << "City " << i + 1 << " -> city " << j + 1 << " : ";
                        cin >> city[i][j];
                } else {
                    city[i][j] = 0;
                }
            }
        }
// starting from city 1
         visited[0] = 1;
         x[0] = 0;  
// print menu algorithm
        printMenuAlgorithm();
        cin >> choice_algorithm;
        if(choice_algorithm == 1) {
            tryCompleteSearch(1);
            cout << "Value of min path : " << min_path << endl;
            for ( int i = 0; i < n; i++) {
                cout << path[i] + 1 << " --> ";
            }
            cout << path[0] + 1 << endl;
        }
        if(choice_algorithm == 2) {
            tryBranchBound(1);
            cout << "Value of min path : " << min_path << endl;
            for ( int i = 0; i < n; i++) {
                cout << path[i] + 1 << " --> ";
            }
            cout << path[0] + 1 << endl;
        }     
// release memory
        for (int i = 0; i < n; i++) {
            delete[] city[i];
        }
        delete[] city;
    }
//-------------------------------------------------------------------------------------------
// File
    if(choice_input == 2) {
        ifstream file;
        file.open("data_tsp.txt");
        file >> n;
// dynamic allocation of 2 dimensional arrays
    city = new int*[n];
    visited = new int[n]; 
    x = new int[n];
    path = new int[n];
    for(int i = 0; i < n; i++) {
        city[i] = new int[n];
        visited[i] = 0;
    }
// get data from file -> array
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                file >> city[i][j];
            }
        }
// starting from city 1
    visited[0] = 1;
    x[0] = 0;    
//---------------------------------------------------    
// print menu algorithm
        printMenuAlgorithm();
        cin >> choice_algorithm;
        if(choice_algorithm == 1) {
            tryCompleteSearch(1);
            cout << "Value of min path: " << min_path << endl;
            for ( int i = 0; i < n; i++) {
                cout << path[i] + 1 << " --> ";
            }
            cout << path[0] + 1 << endl;
        }
        if(choice_algorithm == 2) {
            tryBranchBound(1);
            cout << "Value of min path: " << min_path << endl;
            for ( int i = 0; i < n; i++) {
                cout << path[i] + 1 << " --> ";
            }
            cout << path[0] + 1 << endl;
        }
        file.close();
// release memory
        for (int i = 0; i < n; i++) {
            delete[] city[i];
        }
        delete[] city;
    }
}