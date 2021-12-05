#include <iostream>
#include "vector"
#include "matrix.h"

using namespace std;

vector<vector<double> > RandomMatrix(int n, int m)
{
    vector< vector<double> > res(n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            res[i].push_back(double (rand()%100));
    return res;
}

int main() {
    int n,m;
    cout << "enter A.size(2 numbers): ";
    cin >> n >> m;
    cout << "enter matrix A: " << endl;
    Matrix<double> a(n,m);
    cin >> a;
    //Matrix<int> b(RandomMatrix(4, 4));
    //cout << "A: \n" << a << endl;
    try
    {
        Matrix<double> x1(a.Data(), (a.columns()-1));
        //cout << "" << (a*b) << endl;
        cout << "Gause: \n" << (a.Gause()) << endl;
        Matrix<double> x2(a.inverse);
        cout << "x = A-1 * b = \n" << (x2 * x1);

        cout << "inverse to A: \n" << x2;
    }
    catch (const char* msg)
    {
        cerr << "Exception caught: " << msg << endl;
    }
    return 0;
}
