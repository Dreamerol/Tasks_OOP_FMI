
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
//zad 2
#pragma once
#include <iostream>
class BinaryNumber{
    char* num;
    int number;
    int len;
    
    public:
    BinaryNumber();
    BinaryNumber(const char* num);
    BinaryNumber(int num);
    BinaryNumber(const BinaryNumber& other);
    BinaryNumber& operator=(const BinaryNumber& other);
    ~BinaryNumber();
    int getNumber() const;
    const char* getNum() const;
    BinaryNumber operator&(const BinaryNumber& other);
    BinaryNumber operator|(const BinaryNumber& other);
    BinaryNumber operator^(const BinaryNumber& other);
    BinaryNumber operator+(const BinaryNumber& other);
    BinaryNumber& operator>>(int n);
    BinaryNumber& operator<<(int n);
    void operator<<(std::ostream& os);
    void operator>>(std::istream& is);
    void creationHelp(const char* num);
    bool operator==(const BinaryNumber& other);
    bool operator!=(const BinaryNumber& other);
    private:
    void free();
    void copyFrom(const BinaryNumber& other);
    
};

#include "BinaryNumber.h"
#include <fstream>
#include <cstring>
#pragma warning (disable:4996)

BinaryNumber::BinaryNumber() {
    
    number = 0;
    num = nullptr;
}
BinaryNumber::~BinaryNumber(){
    free();
}
BinaryNumber::BinaryNumber(const BinaryNumber& other){
    copyFrom(other);
}
BinaryNumber& BinaryNumber::operator=(const BinaryNumber& other){
    if(this != &other){
        free();
        copyFrom(other);
    }
    return *this;
}
        num++;

int pow(int base,int stepen){
    int n = 1;
    for(int i=0;i<stepen;i++){
        n *= base;
    }
    return n;
}
int charConverter(char el){
    return el-'0';
}
char intConverter(int n){
    return n +'0';
}
int findLen(int num){
    int l = 0;
    while(num){
        l++;
        num /= 2;
    }
    return l;
}
BinaryNumber::BinaryNumber(int number){
    int l = findLen(number);
    this->num = new char[l+1];
    this->len = l;
    this->number = number;
    for(int i = l - 1;i>=0;i--){
        this->num[i] = intConverter(number %2);
        number /=2;
    }
    
}
int findLenNiz(const char* num){
    int l = 0;
        while((*num) != '\0'){
        num++;
        l++;
    }
    return l;
}
int findStartIdx(const char* num, int l){
    for(int i =0;i<l;i++){
        if(num[i] == '1'){
            
            return i;
        }
    }
    return -1;
}
void BinaryNumber::creationHelp(const char* num){
    if(num == nullptr){
        return;
    }
    int l = findLenNiz(num);
    int len = 0;
 
    
    int startidx=findStartIdx(num, l);
    

    for(int j = startidx;j<l;j++){
        if(num[j] == '1' || num[j] =='0'){
            len++;
        }
    }
    this->num = new char[len+1];
    for(int o = startidx;o<startidx + len;o++){
        this->num[o-startidx] = num[o];
    }
    
    this->len = len;
    this->number = 0;
    for(int i = 0;i<this->len;i++){
        this->number += pow(2, this->len-i-1) * charConverter(this->num[i]);
    }
}
BinaryNumber::BinaryNumber(const char* num){
    creationHelp(num);
    
    
}
bool BinaryNumber::operator==(const BinaryNumber& other){
    return (other.number == this->number);
}

bool BinaryNumber::operator!=(const BinaryNumber& other){
    return (other.number != this->number);
}
// //po kopie 
BinaryNumber BinaryNumber::operator&(const BinaryNumber& other){
    
    int newnum = other.number & this->number;
    BinaryNumber B(newnum);
    return B;
}
BinaryNumber BinaryNumber::operator|(const BinaryNumber& other){
      
    int newnum = other.number | this->number;
    BinaryNumber B(newnum);
    return B;
}

BinaryNumber BinaryNumber::operator^(const BinaryNumber& other){
      
    int newnum = other.number ^ this->number;
    BinaryNumber B(newnum);
    return B;
}


BinaryNumber BinaryNumber::operator+(const BinaryNumber& other){
      
    int newnum = other.number + this->number;
    BinaryNumber B(newnum);
    return B;
}
BinaryNumber& BinaryNumber::operator>>(int n){
    this->number =  this->number >> n;
    char* newnum = new char[this->len - n];
    for(int i = 0;i<len-n;i++){
        newnum[i] = this->num[i];
    }
    delete[] this->num;
    this->num = newnum;
    this->len -= n;
    return *this;
}
BinaryNumber& BinaryNumber::operator<<(int n){
    this->number =  this->number << n;
    char* newnum = new char[this->len + n + 1];
    for(int i = 0;i<len;i++){
        newnum[i] = this->num[i];
    }
    for(int i = len;i<len+n;i++){
        newnum[i] = '0';
    }
    delete[] this->num;
    this->num = newnum;
    this->len += n;
    return *this;
}
void BinaryNumber::operator<<(std::ostream& os){
    
    os << this->num;
    os <<'\n';
    os << this->number;
}
void BinaryNumber::operator>>(std::istream& is){
    free();
    char buffer[1024];
   
    is.getline(buffer, 1024);
    creationHelp(buffer);
    
}



void BinaryNumber::free(){
    delete[] num;
    num = nullptr;
}
void BinaryNumber::copyFrom(const BinaryNumber& other){
    num = new char[other.len];
    len = other.len;
    strcpy(num, other.num);
    number = other.number;
}
int BinaryNumber::getNumber() const{
        return this->number;
    }
    
const char* BinaryNumber::getNum() const{
        return this->num;
    }

int main()
{

    //zad 1
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

    //zad 2

    char num[1024] = "aaas01010hsghs";
    BinaryNumber bin(num);
    BinaryNumber bin1(15);
    BinaryNumber b1 = bin ^ bin1;
  //  std::cout<<b1.getNumber()<<'\n';
    b1 = b1 >> 2;
   // std::cout<<b1.getNumber()<<'\n';
    b1 = b1 << 4;
 //   std::cout<<b1.getNumber();
    std::ofstream ofs("lolo.txt");
    b1 << ofs;
    ofs.close();
   // std::cout<<bin1.getNum();
    //1010
    //1111
   // std::cout<< (bin != bin1);
    // std::cout<<bin.getNumber();
    // std::cout<<bin.getNum();
    //std::cout<<"Hello World";
 
 BinaryNumber n1(nullptr);
 std::cout<<n1.getNumber()<<'\n';
    std::ifstream ifs("lolo.txt");
    // char buffer[100];
    // ifs.getline(buffer, 100);
    // std::cout<<buffer;
    std::cout<<bin.getNumber()<<'\n';
    bin >> ifs;
    std::cout<<bin.getNumber()<<'\n';
    //BinaryNumber b0 = b1;
    //std::cout<<b0.getNumber();
  //  std::cout<<b1.getNumber();
    return 0;
}
