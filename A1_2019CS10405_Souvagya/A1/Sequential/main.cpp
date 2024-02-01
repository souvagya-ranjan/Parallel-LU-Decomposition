#include <iostream>
#include <bits/stdc++.h>
#include <chrono>


using namespace std;

void initialise_matrix(double **a, int n){
    for( int i = 0; i < n; i++){
        for( int j = 0; j < n; j++){
            a[i][j] = drand48();
        }
    }
}

void print_matrix(double** a, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

double verification(double** P, double** A, double** L, double** U, double** res, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            res[i][j] = 0;
            for(int k = 0; k < n; k++){
                res[i][j] += P[i][k]*A[k][j];
                res[i][j] -= L[i][k]*U[k][j];
            }
        }
    }
    // cout<<"Residual Matrix: "<<endl;
    // print_matrix(res,n);
    double norm = 0;
    for(int i = 0; i < n; i++){
        double column_norm = 0;
        for(int j = 0; j < n; j++){
            column_norm += res[j][i]*res[j][i];
        }
        norm += sqrt(column_norm);
    }
    return norm;
}

void get_matrix(int *P, double** R, int n){
    for(int i = 0; i < n; i++){
        int k = P[i];
        R[i][k] = 1;
    }
}

int LUD(double** A, double** L, double** U, int* P, int n){
    for(int k = 0; k < n; k++){
        int max_row = k;
        double max_val = 0;
        for(int i = k+1; i < n; i++){
            if(abs(A[i][k]) > max_val){
                max_val = abs(A[i][k]);
                max_row = i;
            }
        }
        if (max_val == 0 and k != n-1){
            cout << "Singular Matrix" << endl;
            return -1;
        } else if(max_row == k && k != n-1){
            continue;
        } else{
            swap(P[k], P[max_row]);
            for(int i = 0; i < n; i++){
                swap(A[k][i], A[max_row][i]);
            }
            for(int i = 0; i < k; i++){
                swap(L[k][i], L[max_row][i]);
            }

            U[k][k] = A[k][k];

            for(int i = k+1; i < n; i++){
                L[i][k] = A[i][k]/U[k][k];
                U[k][i] = A[k][i];
            }

            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    A[i][j] = A[i][j] - L[i][k]*U[k][j];
                }
            }
        }
    }
    return 0;
}


int main( int argc, char* argv[]){
    int n = stoi(argv[1]);
    int t = stoi(argv[2]);

    double** A = new double*[n];
    double** L = new double*[n];
    double** U = new double*[n];
    int* P = new int[n];
    for(int i = 0; i < n; i++){
        A[i] = new double[n];
        L[i] = new double[n];
        U[i] = new double[n];
    }

    initialise_matrix(A, n);
    // A[0][0] = -2;
    // A[0][1] = 2;
    // A[0][2] = -1;
    // A[1][0] = 6;
    // A[1][1] = -6;
    // A[1][2] = 7;
    // A[2][0] = 3;
    // A[2][1] = -8;
    // A[2][2] = 4;

    double** A_org = new double*[n];
    for(int i = 0; i < n; i++){
      A_org[i] = new double[n];
      for(int j = 0; j < n; j++){
        A_org[i][j] = A[i][j];
      }
    }

    // cout << "A: "<< endl;
    // print_matrix(A, n);
    
    for(int i = 0; i < n; i++){
        P[i] = i;
        for(int j = 0; j < n; j++){
            L[i][j] = 0;
            U[i][j] = 0;
            if (i == j){
                L[i][j] = 1;
            }
        }
    }

    chrono::high_resolution_clock::time_point start_time, end_time;
    start_time = chrono::high_resolution_clock::now();
  
    int res = LUD(A,L,U,P,n);
    // cout<<"LUD complete"<<endl;

    end_time = chrono::high_resolution_clock::now();
    chrono::duration<double> time_elapsed = end_time - start_time;
    double seconds = time_elapsed.count();
    cout << "Time elapsed: " << seconds << " nano-seconds" << endl;
    
    if (res == -1){
        return -1;
    }
    else{
        double** Pie = new double*[n];
        double** res = new double*[n];
        for(int i = 0; i < n; i++){
            Pie[i] = new double[n];
            res[i] = new double[n];
        }
        // for(int i = 0; i < n; i++){
        //     cout<< P[i]<< " ";
        // }
        // cout<<endl;
        get_matrix(P, Pie, n);

        double norm = verification(Pie,A_org,L,U,res,n);
        cout << "The norm of the residual matrix AP-LU is: "<< norm <<endl;

        // cout << "P: "<< endl;
        // print_matrix(Pie, n);

        // cout << "L: "<< endl;
        // print_matrix(L, n);

        // cout << "U: "<< endl;
        // print_matrix(U, n);

        return 0;
    }
}