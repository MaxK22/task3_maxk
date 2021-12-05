#ifndef UNTITLED_MATRIX_H
#define UNTITLED_MATRIX_H

#include <iostream>
#include <vector>
#include <cassert>
#include "math.h"

using namespace std;

template<typename T>
class Matrix
{
    int n;
    int m;
    vector< vector<T> > data;
public:
    vector< vector<double> > inverse;
    Matrix(vector< vector<T> >);
    Matrix(vector< vector<double> >, int j);
    Matrix(vector< vector<T> >, int i, int j);
    Matrix(int n_);
    Matrix(int n_, int m_);
    int rows() const { return n; };
    int columns() const { return m; };
    vector< vector<T> > Data() { return data; };
    const Matrix operator+(const Matrix&) const;
    const Matrix operator*(const Matrix&) const;
    const Matrix operator^(int) const;
    const Matrix operator*(T) const;
    vector<double> dline(vector<double>, vector<double>, double);
    const Matrix transparent();
    const Matrix<double> Gause();
    T determinant();
    vector<T>& operator[](int i) { return data[i]; };
    const vector<T>& operator[](int i) const { return data[i]; };
    template<typename Type> friend istream& operator>>(istream&, Matrix<Type>&);
    template<typename Type> friend ostream& operator<<(ostream&, const Matrix<Type>&);
};

template<typename T>
Matrix<T>::Matrix(vector< vector<T> > vect)
{
    data = vect;
    n = vect.size();
    m = vect[0].size();
}

template<typename T>
Matrix<T>::Matrix(vector< vector<double> > vect, int j)
{
    data = vect;
    for(int i = 0; i < vect.size(); ++i)
    {
        data[i].resize(1);
        data[i][0] = vect[i][j];
    }
    n = vect.size();
    m = 1;
}

template<typename T>
Matrix<T>::Matrix(vector< vector<T> > vect, int x, int y)
{
    data = vector< vector<T> >(vect.size()-1);
    for (int i = 0; i < vect.size(); ++i) {
        if(i < x)
        {
            for (int j = 0; j < vect[0].size(); ++j) {
                if(j != y)
                data[i].push_back(vect[i][j]);
            }
        }
        else if(i > x)
        {
            for (int j = 0; j < vect[0].size(); ++j) {
                if(j != y)
                data[i-1].push_back(vect[i][j]);
            }
        }
    }
    n = data.size();
    m = data.size();
}

template<typename T>
Matrix<T>::Matrix(int n_)
{
    n = n_;
    m = n_;
    vector<T> x;
    x.assign(m, 0);
    data.assign(n, x);
}

template<typename T>
Matrix<T>::Matrix(int n_, int m_)
{
    n = n_;
    m = m_;
    vector<T> x;
    x.assign(m, 0);
    data.assign(n, x);
}

template<typename T>
vector<double> Matrix<T>::dline(vector<double> a, vector<double> b, double k)
{
    if (a.size() != b.size())
        throw "Lines have different sizes";
    vector<double> res;
    for(int i = 0; i < a.size(); ++i)
        res.push_back(a[i] - b[i] * k);
    return res;
}

template<typename T>
const Matrix<T> Matrix<T>::operator+(const Matrix& a) const
{
    if (a.rows() != n || a.columns() != m)
        throw "Matrices have different sizes";
    vector< vector<T> > res(n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            res[i].push_back(data[i][j] + a[i][j]);
    return Matrix(res);
}

template<typename T>
const Matrix<T> Matrix<T>::operator*(T k) const
{
    vector< vector<T> > res(n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            res[i].push_back(data[i][j] * k);
    return Matrix(res);
}

template<typename T>
ostream& operator<<(ostream& out, const Matrix<T>& a)
{
    for (int i = 0; i < a.rows(); ++i)
    {
        for (int j = 0; j < a.columns(); ++j)
            out << a[i][j] << " ";
        out << endl;
    }
    return out;
}

template<typename T>
istream &operator>>(istream& in, Matrix<T>& a) {
    for (int i = 0; i < a.rows(); ++i)
        for (int j = 0; j < a.columns(); ++j)
            in >> a[i][j];
    return in;
}

template<typename T>
const Matrix<T> Matrix<T>::operator*(const Matrix& a) const
{
    if (a.rows() != m)
        throw "Matrices haven't match sizes";
    vector< vector<T> > res(n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < a.columns(); ++j) {
            res[i].push_back(0);
            for (int l = 0; l < m; ++l)
                res[i][j] += data[i][l] * a[l][j];
        }
    return Matrix(res);
}

template<typename T>
const Matrix<T> Matrix<T>::transparent()
{
    vector< vector<T> > res(m);
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            res[i].push_back(data[j][i]);
    return Matrix(res);
}

template<typename T>
T Matrix<T>::determinant()
{
    if (n != m)
        throw "Matrix hasn't match size";
    T a = 0;
    if(n > 1) {
        for (int j = 1; j <= n; ++j) {
            Matrix<T> M = Matrix(data, 0, j - 1);
            a += pow(-1, j + 1) * data[0][j - 1] * M.determinant();
        }
    }
    else
        a = data[0][0];
    return a;
}

template<typename T>
const Matrix<T> Matrix<T>::operator^(int k) const
{
    if (n != m)
        throw "Matrix hasn't match size";
    vector< vector<T> > res = data;
    for(int i = 1; i < k; ++i)
        res = res * data;
    return Matrix(res);
}

template<typename T>
const Matrix<double> Matrix<T>::Gause()
{
    if (n > m)
        throw "Matrix hasn't match size";
    vector<double> x;
    x.assign(m, 0);
    inverse.assign(n, x);
    for (int i = 0; i < n; ++i)
        inverse[i][i] = 1;
    vector< vector<double> > res(n);
    res = data;
    for (int j = 0; j < n - 1; ++j) {
        if (res[j][j] == 0) {
            for (int k = j + 1; k < n; ++k) {
                if (res[k][j] != 0) {
                    res[j] = dline(res[j], res[k], -1);
                    inverse[j] = dline(inverse[j], inverse[k], -1);
                    k = n;
                }
            }
        }
        for (int k = j + 1; k < n && res[j][j] != 0; ++k) {
            if (res[k][j] != 0) {
                double p = res[k][j] / res[j][j];
                res[k] = dline(res[k], res[j], p);
                inverse[j] = dline(inverse[k], inverse[j], p);
            }
        }
    }
    return Matrix<double>(res);
}
#endif //UNTITLED_MATRIX_H
