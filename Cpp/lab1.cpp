#include <iostream>
#include <fstream>
using namespace std;

class Matrix
{
private:
    int **A;
    int sizeN;
    int sizeM;
    
public:
    Matrix(){}
    Matrix(const Matrix &obj){
        sizeN = obj.sizeN;
        sizeM = obj.sizeM;
        A = new int*[sizeN];
        for (int i = 0; i < sizeN; i++){
            A[i] = new int[sizeM];
            for (int j = 0; j < sizeM; j++)
                A[i][j] = obj.A[i][j];
        }
    }
    Matrix(int n, int m) {
        this->sizeN = n;
        this->sizeM = m;
        A = new int*[n];
        for (int i = 0; i < n; i++){
            A[i] = new int[m];
            for (int j = 0; j < m; j++)
                A[i][j] = 0;
        }
    }

    Matrix(int n) {
        this->sizeN = n;
        this->sizeM = n;
        A = new int*[n];
        for (int i = 0; i < n; i++)
            A[i] = new int[n];
    }
    
    ~Matrix() {
        if (A){
            for (int i = 0; i < sizeN; i++)
                delete[] A[i];
        delete[] A;
        }
    }

    int operator () (int i, int j) const{
        return this->A[i][j];
    }
    
    Matrix &operator += (const Matrix &obj){
        for (int i = 0; i < sizeN; i++){
            for (int j = 0; j < sizeM; j++){
                A[i][j] += obj.A[i][j];
            }
        }
        return *this;
    }
    
    Matrix &operator += (int x){
        for (int i = 0; i < sizeN; i++){
            for (int j = 0; j < sizeM; j++){
                A[i][j] += x;
            }
        }
        return *this;
    }
    
    Matrix &operator -= (const Matrix &obj){
        for (int i = 0; i < sizeN; i++){
            for (int j = 0; j < sizeM; j++){
                A[i][j] -= obj.A[i][j];
            }
        }
        return *this;
    }
    
    Matrix &operator -= (int x){
        for (int i = 0; i < sizeN; i++){
            for (int j = 0; j < sizeM; j++){
                A[i][j] -= x;
            }
        }
        return *this;
    }
    
    Matrix operator + (const Matrix &obj) const{
        Matrix result(*this);
        result += obj;
        return result;
    }
    
    Matrix operator + (int x) const{
        Matrix result(*this);
        result += x;
        return result;
    }
    
    Matrix operator - (const Matrix &obj) const{
        Matrix result(*this);
        result -= obj;
        return result;
    }
    Matrix operator - (int x) const{
        Matrix result(*this);
        result -= x;
        return result;
    }
    
    Matrix operator = (const Matrix &obj){
        for (int i = 0; i < sizeN; i++){
            for (int j = 0; j < sizeM; j++){
                A[i][j] = obj.A[i][j];
            }
        }
        return *this;
    }
    
    Matrix operator * (int x){
        Matrix result(sizeN, sizeM);
        for(int i = 0; i < sizeN; i++)
            for(int j = 0; j < sizeM; j++)
                result.A[i][j] = A[i][j] * x;
        return result;
    }
    
    Matrix &operator *= (int x){
        for(int i = 0; i < sizeN; i++)
            for(int j = 0; j < sizeM; j++)
                A[i][j] *= x;
        return *this;
    }
    
    Matrix operator * (const Matrix &obj){
        Matrix result(this->sizeN, obj.sizeM);
        for(int i = 0; i < sizeN; i++)
            for(int j = 0; j < obj.sizeM; j++)
                for(int k = 0; k < obj.sizeN; k++)
                    result.A[i][j] += A[i][k] * obj.A[k][j];
        return result;
    }
    
    Matrix &operator *= (const Matrix &obj){
        Matrix result(this->sizeN, obj.sizeM);
        for(int i = 0; i < sizeN; i++)
            for(int j = 0; j < obj.sizeM; j++)
                for(int k = 0; k < obj.sizeN; k++)
                    result.A[i][j] += A[i][k] * obj.A[k][j];
        *this = result;
        return *this;
    }

    Matrix dot(const Matrix &obj2){
        Matrix result(this->sizeN, obj2.sizeM);
        for(int i = 0; i < sizeN; i++)
            for(int j = 0; j < obj2.sizeM; j++)
                for(int k = 0; k < obj2.sizeM; k++)
                    result.A[i][j] += A[i][k] * obj2.A[k][j];
        return result;
    }
    
    Matrix transpose(){
        Matrix result(this->sizeM, this->sizeN);
        for (int i = 0; i < sizeN; i++)
            for (int j = 0; j < sizeM; j++)
                result.A[j][i] = A[i][j];
        return result;
    }
    friend istream& operator>>(istream &in, Matrix &M);
    friend ostream& operator<<(ostream &out, const Matrix &M);

};

istream& operator>>(istream &in, Matrix &M){
    for (int i = 0; i < M.sizeN; i++){
        for (int j = 0; j < M.sizeM; j++){
            in>>M.A[i][j];
        }
    }
    return in;
}
ostream& operator<<(ostream &out, const Matrix &M){
    for (int i = 0; i < M.sizeN; i++){
        for (int j = 0; j < M.sizeM; j++){
            out<<M.A[i][j]<<" ";
        }
        out<<endl;
    }
    return out;
}


int main(int argc, char* argv[])
{
    ifstream fin ("/Users/emidiant/Documents/C++First/C++First/input.txt");
    int n, m;
    fin>>n>>m;
    Matrix obj1(n, m);
    fin>>obj1;
    Matrix obj2(n, m), obj3(n ,m);
    fin>>obj2;
    cout<<obj1<<endl;
    cout<<obj2<<endl;
    obj3 = obj1 + obj2;
    cout<<obj3<<endl;
    obj1 += 2;
    cout<<obj1<<endl;
    obj3 = obj1 * obj2;
    cout<<obj3<<endl;
    cout<<obj3(1, 1)<<endl;
    cout<<obj3.transpose()<<endl;
    cout<<obj1.dot(obj2);

    return 0;
}

