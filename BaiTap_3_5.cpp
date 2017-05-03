#include <iostream>
#include <fstream>

using namespace std;

void out_arr(int a[100][100], int m,  int n){
    int i, j;
    for (i=0 ; i<m ; i++){
        for (j=0 ; j<n ; j++)
            cout << "  " << a[i][j];
        cout << endl;
    }
}

int SUM(int a[], int size){
    if (size == 1)  return a[0];
    return a[size-1] + SUM(a, size-1);
}

bool check(int a[], int b[], int size){
    if (SUM(a, size) == SUM(b, size))
        return true;
    return false;
}
bool check_Hoan_Chinh(int a){
    int i;
    int T=0;
    for (i=1 ; i<=a/2 ; i++)
        if (a%i == 0)
            T+=i;
    if (T==a) return true;
    return false;
}
int main(){
    ifstream inpfile("Number.txt" );
    ofstream outfile("Ketqua.txt", ios::out);
    int A[100][100];
    int i, j, m, n;
    inpfile >> m >> n;
    for (i=0 ; i<m ; i++)
        for (j=0 ; j<n ; j++)
            inpfile >> A[i][j];
    out_arr(A, m, n);

    outfile << "Cau 1: ";

    for (i=0 ; i<m-1 ; i++)
        if (check(A[i], A[i+1], n))
            outfile << i+1 << " ";
    outfile << endl;

    outfile << "Cau 2: ";
    for (i=0 ; i<m ; i++)
        for (j=0 ; j<n ; j++)
            if (check_Hoan_Chinh(A[i][j]))
                outfile << A[i][j] << " ";
    outfile << endl;
    return 0;
}
