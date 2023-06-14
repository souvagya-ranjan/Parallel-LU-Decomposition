#include <iostream>
#include <bits/stdc++.h>
using namespace std;


int main(int argc, char* argv[]){
    int n = stoi(argv[1]);
    // int t = atoi(argv[2]);


    //manually set 
    n = 3;    

    // double *a;
    // a = (double*)malloc(n*n*sizeof(double));
    
    // for(int i = 0; i < n; i++){
    //     for (int j = 0; j < n; j++){
    //         a[i*n + j] = drand48();
    //     }
    // }


    //manually initialise
    double a[9] = {-2, 2, -1, 6, -6, 7, 3, -8, 4};

    double *l;
    double *u;
    l = (double*)malloc(n*n*sizeof(double));
    u = (double*)malloc(n*n*sizeof(double));

    double *p;
    p = (double*)malloc(n*sizeof(double));
    for(int i = 0; i < n; i++){
        p[i] = i;
    }

    //initialise l & u
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            u[i*n + j] = 0;
            if(i == j){
                l[i*n + j] = 1;
            }
            else{
                l[i*n + j] = 0;
            }
        }
    }

    //perform LU decomposition
    for( int k = 0; k < n; k++){
        cout<< "A: "<< endl;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                cout << a[i*n + j] << " ";
            }
            cout << endl;
        } 
        cout << endl;
        cout << "P: "<< endl;
        for(int i = 0; i < n; i++){
            cout << p[i] << " ";
        }
        cout << endl;
        cout <<"L: "<< endl;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                cout << l[i*n + j] << " ";
            }
            cout << endl;
        }
        cout << endl;
        cout << "U: "<< endl;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                cout << u[i*n + j] << " ";
            }
            cout << endl;
        }
        cout << endl;

        int max_row = k;
        double max_val = 0;
        for ( int i = k+1; i < n; i++){
            if (abs(a[i*n + k]) > max_val){
                max_val = abs(a[i*n + k]);
                max_row = i;
            }
        }
        if (max_val == 0 and k!=n-1){
            cout << "Singular Matrix" << endl;
            cout << "k: "<< k << endl;
            return -1;
        }
        else{
            swap(p[k], p[max_row]);
            for (int i = 0; i < n; i++){
                swap(a[k*n + i], a[max_row*n + i]);
            }

            for(int i = 0; i < k; i++){
                swap(l[k*n + i], l[max_row*n + i]);
            }

            u[k*n + k] = a[k*n + k];

            for( int i = k+1; i < n; i++){
                l[i*n + k] = a[i*n + k]/u[k*n + k];
                u[k*n + i] = a[k*n + i];
            }

            for(int i = k+1; i < n; i++){
                for(int j = k+1; j < n; j++){
                    a[i*n + j] = a[i*n + j] - l[i*n + k]*u[k*n + j];
                }
            }
        }
    }

    //print l & u
    cout << "L:" << endl;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << l[i*n + j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "U:" << endl;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << u[i*n + j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    return 0;
}