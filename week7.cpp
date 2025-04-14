
//zad 1
#pragma once
class Matrix{
    int** matrix;
    int n;
    int m;
    
    public:
    Matrix();
    Matrix(int n, int m);
    Matrix(const Matrix& other);
    Matrix& operator=(const Matrix& other);
    //Matrix& operator+=(const Matrix& other);
    void print() const;
    ~Matrix();
    void setN(int n);
    void setM(int m);
    Matrix(int n, int m, int** arr);
    
    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(const Matrix& other);
    Matrix& operator*=(int scalar);
    int* operator[](int idx);
    bool isNotNullMatrix() const;
    Matrix operator*(int scalar);
    Matrix operator-(const Matrix& other);
    bool operator==(const Matrix& other);
    bool operator!=(const Matrix& other);
    //bool operator bool(const Matrix& other);
    
    Matrix operator+(const Matrix& other);
    Matrix operator*(const Matrix& other);
    private:
    void free();
    void copyFrom(const Matrix& other);
    
};


#include <iostream>
#include "matrix.h"
// Matrix::Matrix() : Matrix(2, 2){};
    
Matrix::Matrix(int n, int m){
    setN(n);
    setM(m);
        matrix = new int*[n];
        for(int i = 0;i<n;i++){
            matrix[i] = new int[m];
        }
}

Matrix::Matrix(int n, int m, int** arr){
    setN(n);
    setM(m);
        matrix = new int*[n];
        for(int i = 0;i<n;i++){
            matrix[i] = new int[m];
        }
        for(int i = 0;i<n;i++){
            for(int j = 0;j<m;j++){
                this->matrix[i][j] = arr[i][j];
            }
        }
}
Matrix::Matrix() : Matrix(2,2)
{
    
}
void Matrix::setN(int n){
    if(n<0){
        return;
    }
    this->n =n; 
}
void Matrix::setM(int m){
    if(m<0){
        return;
    }
    this->m =m; 
}
Matrix& Matrix::operator=(const Matrix& other){
    if(this != &other){
        free();
        copyFrom(other);
    }
    return *this;
}
Matrix::Matrix(const Matrix& other){
    copyFrom(other);
}
Matrix::~Matrix(){
    free();
}
void Matrix::free(){
    for(int i = 0;i<n;i++){
        delete[] matrix[i];
    }
    delete matrix;
}
void Matrix::copyFrom(const Matrix& other){
    this->n = other.n;
    this->m = other.m;
    
    this->matrix = new int*[n];
    for(int i = 0;i<n;i++){
        matrix[i] = new int[m];
    }
    
    for(int i = 0;i<n;i++){
        for(int j=0;j<m;j++){
            matrix[i][j] = other.matrix[i][j];
        }
}}
void Matrix::print() const{
    for(int i = 0;i<n;i++){
        for(int j = 0;j<m;j++){
            std::cout<<matrix[i][j]<<' ';
        }
        std::cout<<'\n';
    }
}
Matrix& Matrix::operator+=(const Matrix& other){
    if(other.n != n || other.m != m){
        return *this;
    }
    for(int i = 0;i<n;i++){
        for(int j = 0;j<m;j++){
            matrix[i][j] += other.matrix[i][j];
        }
    }
    return *this;
    
}
Matrix Matrix::operator+(const Matrix& other){
    if(other.n != n || other.m != m){
        return *this;
    }
    Matrix new_matrix = Matrix(n, m);
    for(int i = 0;i<n;i++){
        for(int j = 0;j<m;j++){
            new_matrix.matrix[i][j] = matrix[i][j] + other.matrix[i][j];
        }
    }
    return new_matrix;
    
}
Matrix& Matrix::operator-=(const Matrix& other){
    if(other.n != n || other.m != m){
        return *this;;
    }
    for(int i = 0;i<n;i++){
        for(int j = 0;j<m;j++){
            matrix[i][j] -= other.matrix[i][j];
        }
    }
    return *this;
}    

Matrix Matrix::operator-(const Matrix& other){
    if(other.n != n || other.m != m){
        return *this;
    }
    Matrix new_matrix = Matrix(n, m);
    for(int i = 0;i<n;i++){
        for(int j = 0;j<m;j++){
            new_matrix.matrix[i][j] = matrix[i][j] - other.matrix[i][j];
        }
    }
    return new_matrix;
    
}
Matrix& Matrix::operator*=(const Matrix& other){
    if(this->m != other.n){
        return *this;
    }
    Matrix new_matrix=Matrix(n, other.m);
  
    for(int i = 0;i<n;i++){
        for(int j = 0;j<other.m;j++){
            int sum = 0;
            for(int k = 0;k<m;k++){
                sum += matrix[i][k] * other.matrix[k][j];
            }
            new_matrix.matrix[i][j] = sum;
            
        }
    }
    m = other.m;
    this->matrix = new int*[n];
    for(int j =0;j<n;j++){
        matrix[j] = new int[other.m];
    }
    for(int i = 0;i<n;i++){
        for(int j = 0;j<other.m;j++){
            matrix[i][j] = new_matrix.matrix[i][j];
        }
    }
    return *this;
}
Matrix Matrix::operator*(const Matrix& other){
    if(this->m != other.n){
        return *this;
    }
    Matrix new_matrix=Matrix(n, other.m);
  
    for(int i = 0;i<n;i++){
        for(int j = 0;j<other.m;j++){
            int sum = 0;
            for(int k = 0;k<m;k++){
                sum += matrix[i][k] * other.matrix[k][j];
            }
            new_matrix.matrix[i][j] = sum;
            
        }
    }
    return new_matrix;
}

Matrix& Matrix::operator*=(int scalar){
    
    
  
    for(int i = 0;i<n;i++){
        for(int j = 0;j<m;j++){
           matrix[i][j] *= scalar;
            
        }
    }
   
    
    return *this;
}
Matrix Matrix::operator*(int scalar){
    
   Matrix mcopy = Matrix(*this);
    for(int i = 0;i<mcopy.n;i++){
        for(int j = 0;j<mcopy.m;j++){
            
            mcopy.matrix[i][j]*=scalar;
            
        }
    }
    return mcopy;
}
bool Matrix::operator==(const Matrix& other){
    if(other.n != n || other.m != m){
        return 0;
    }
    for(int i = 0;i<n;i++){
        for(int j = 0;j<m;j++){
            if(matrix[i][j] != other.matrix[i][j]){
                return 0;
            }
        }
    }
    return 1;
}
bool Matrix::operator!=(const Matrix& other){
    if(other.n != n || other.m != m){
        return 1;
    }
    for(int i = 0;i<n;i++){
        for(int j = 0;j<m;j++){
            if(matrix[i][j] == other.matrix[i][j]){
                return 0;
            }
        }
    }
    return 1;
}
bool Matrix::isNotNullMatrix() const{
    
    for(int i = 0;i<n;i++){
        for(int j = 0;j<m;j++){
            if(matrix[i][j] != 0){
                return 1;
            }
        }
    }
    return 0;
}

int* Matrix::operator[](int idx){
    if(idx<0 || idx > m){
        return nullptr;
    }
    return matrix[idx];
} 

int main()
{
    int** k = new int*[2];
    for(int i = 0;i<2;i++){
        k[i] = new int[2];
    }
    int  o =0;
    for(int i = 0;i<2;i++){
        for(int j=0;j<2;j++){
            k[i][j] = o++;
        }
    }
    Matrix mat(2, 2, k);
    //mat.print();
    int** k1 = new int*[2];
    for(int i = 0;i<2;i++){
        k1[i] = new int[2];
    }
    int  o1 =10;
    for(int i = 0;i<2;i++){
        for(int j=0;j<2;j++){
            k1[i][j] = o1++;
        }
    }
    Matrix mat1(2, 2, k1);
    //mat1.print();
    mat+=mat1;
    mat-=mat1;
    mat.print();
    Matrix m = mat1 + mat;
    m.print();
    //mat1.print();
    m*=mat1;
    mat1*=0;
    mat1.print();
    //m.print();
    // Matrix s = mat1*m;
    // s.print();
   std::cout<<(m != mat1);
   std::cout<<m[0];
   std::cout<<m.isNotNullMatrix();
   Matrix r = m * 8;
   r.print();
    return 0;
}
