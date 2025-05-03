
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

//zad 3
#include <iostream>
#include <fstream>
#include <cstring>
enum class Genre : char{
  ROCK = 1 <<0,
  POP = 1 << 1,
  HIPHOP = 1 << 2,
  EDM = 1 << 3,
  JAZZ = 1 << 4,
  Default
};
Genre toGenre(char el){
    switch(el){
        case 'r': return Genre::ROCK;
        case 'p': return Genre::POP;
        case 'h':return Genre::HIPHOP;
        case 'e':return Genre::EDM;
        case 'j':return Genre::JAZZ;
        default: return Genre::Default;
    }
}
void Kbit(unsigned char& el,int k){
        el |= (1 << (k-1));
        
    }
class Song{
    char* name = nullptr;
    int duration =0;
    char genre=0;
    unsigned char* content = nullptr;
    int len = 0;
    
    public:
    Song() = default;
    Song(const Song& other){
        copyFrom(other);
    }
    Song& operator=(const Song& other){
        if(this!=&other){
            free();
            copyFrom(other);
        }
        return *this;
    }
    ~Song(){
        free();
    }
    void setName(const char* name){
        if(name == nullptr){
            return;
        }
        if(name == this->name){
            return;
        }
        delete[] this->name;
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }
    
    void setGenre(const char* genres){
        for(int i = 0;i<strlen(genres);i++){
            genre |= (char)toGenre(genres[i]);
        }
    }
    void setDuration(int duration){
        if(duration < 0){
            return;
        }
        this->duration = duration;
    }
    void setContentFromFile(const char* filename){
        std::ifstream file;
        
        file.open(filename, std::ios::binary);
        if(!file){
            throw std::runtime_error("Can't open file!");
        }
        if(content != nullptr){
            delete[] this->content;
        }
        file.read((char*)&this->len, sizeof(int));
        content = new unsigned char[this->len];
        file.read((char*)content, sizeof(char) * this->len);
        file.close();
        
        
    }
    
    const unsigned char* getContent() const{
        return content;
    }
    void changeKbit(int k){
        int br = k;
        for(int i = len-1;i>=0;i--){
            while(br <= 8){
                Kbit(content[i], br);
                br+=k;
            }
            br-=8;
            //content[i]
        }
    }
    void mixSongs(const Song& other){
        int l = len < other.len ? len : other.len;
        for(int i = 0;i<l;i++){
            content[i] ^= other.content[i];
        }
    }
    // void setContent(const char* content){
    //     this->content = new char[strlen(content)]
    // }
    void setContentFromMemory(const unsigned char* data, int size) {
    delete[] content;
    len = size;
    content = new unsigned char[len];
    for(int i = 0;i<len;i++){
        content[i] = data[i];
    }
    //memcpy(content, data, len);
}
char getGenre() const{
    return genre;
}

    private:
    void free(){
        delete[] name;
        name = nullptr;
        
        delete[] content;
        content = nullptr;
    }
    void copyFrom(const Song& other){
        setDuration(other.duration);
        genre = other.genre;
        setName(other.name);
        len = other.len;
        this->content = new unsigned char[len];
        for(int i = 0;i<len;i++){
            this->content[i] = other.content[i];
        }
        
    }
};


//zad 4

#pragma once
class MultiSet{
    int size;
    int* multiset;
    
    public:
    MultiSet();
    MultiSet(int n);
    MultiSet(const MultiSet& other);
    MultiSet& operator=(const MultiSet& other);
    ~MultiSet();
    int getSize() const;
    void print() const;
    void print(const MultiSet& other) const;
    void addNum(int num);
    void shifting(int idx);
    bool isinthere(int num) const;
    int findIdx(int idx) const;
    
    int count(int num) const;
    void removeNum(int num);
    int countNum(int num);
    //void print() const;
    
    friend MultiSet intersection(const MultiSet& other1, const MultiSet& other2);
    friend MultiSet unionSets(const MultiSet& other1, const MultiSet& other2);
    
    private:
    void free();
    void copyFrom(const MultiSet& other);
    void resize(int newCap);
    
};
#include <iostream>
#include "MultiSet.h"
MultiSet::MultiSet() : multiset(nullptr), size(0){};
MultiSet::MultiSet(int n){
    size = n;
    multiset = new int[n];
    for(int i = 0;i<n;i++){
        multiset[i] = i;
    }
}
    MultiSet::MultiSet(const MultiSet& other){
        copyFrom(other);
    }
    MultiSet& MultiSet::operator=(const MultiSet& other){
        if(this != &other){
            free();
            copyFrom(other);
        }
        return *this;
    }
    MultiSet::~MultiSet(){
        free();
    }
    int MultiSet::count(int num) const{
        int count = 0;
        for(int i = 0;i<size;i++){
            if(multiset[i] == num){
                count++;
            }
        }
        
        return count;
    }
    bool MultiSet::isinthere(int num) const{
        for(int i=0;i<size;i++){
            if(num == multiset[i]){
                return 1;
            }
        }
        return 0;
    }
    bool isinthereprim(int num, int arr[], int size){
        for(int i=0;i<size;i++){
            if(num == arr[i]){
                return 1;
            }
        }
        return 0;
    }
    void MultiSet::addNum(int num){
        if(count(num) >= 3){
            return;
        }
        resize(size+1);
        multiset[size++] = num;
    }
    int MultiSet::findIdx(int num) const{
        for(int i = 0;i<size;i++){
            if(num == multiset[i]){
                return i;
            }
        }
        return -1;
    }
    void MultiSet::shifting(int idx){
        int* helper = new int[size - 1];
        int l = 0;
        for(int i = 0;i<size;i++){
            if(idx == i){
                continue;
            }
            helper[l++] = multiset[i];
        }
        delete[] multiset;
        multiset = helper;
        size--;
        
    }
    void MultiSet::removeNum(int num){
        if(!isinthere(num)){
            return;
        }
        int idx = findIdx(num);
        shifting(idx);
    }
        
  
    int countels(int arr[], int size, int num){
        int c = 0;
        for(int i = 0;i<size;i++){
            if(num == arr[i]){
                c++;
            }
        }
        return c;
    }
    MultiSet intersection(const MultiSet& other1, const MultiSet& other2){
        int* uniqueels = new int[other1.size];
        int len = 0;
        for(int i = 0;i<other1.size;i++){
            if(!isinthereprim(other1.multiset[i], uniqueels, len)){
                uniqueels[len++] = other1.multiset[i];
            }
        }
        
        int* uniqueels1 = new int[other2.size];
        int len1 = 0;
        for(int i = 0;i<other2.size;i++){
            if(!isinthereprim(other2.multiset[i], uniqueels1, len1)){
                uniqueels1[len1++] = other2.multiset[i];
            }
        }
        int sizetwo = other1.size > other2.size ? other2.size : other1.size;
        int* elsintwo  = new int[sizetwo];
        int l = 0;
        for(int i=0;i<len;i++){
            for(int j = 0;j<len1;j++){
                if(uniqueels[i] == uniqueels1[j]){
                    elsintwo[l++] = uniqueels1[j];
                }
            }
        }
        int* counts = new int[l];
        for(int i = 0;i<l;i++){
            int count1 = countels(other1.multiset, other1.size, elsintwo[i]);
            int count2 = countels(other2.multiset, other2.size, elsintwo[i]);
            counts[i] = count1 > count2 ? count2 : count1;
        }
        MultiSet m;
        int Count = 0;;
        for(int i = 0;i<l;i++){
          Count += counts[i];
        }
        int k = 0;
        m.multiset = new int[Count];
        for(int i = 0;i<l;i++){
            for(int j=0;j<counts[i];j++){
                m.multiset[k++] = elsintwo[i];
            }
        }
        m.size = Count;
        delete[] uniqueels1;
        delete[] uniqueels;
        delete[] counts;
        delete[] elsintwo;
        
        return m;
    }
    MultiSet unionSets(const MultiSet& other1, const MultiSet& other2){
        int newsize = other1.size + other2.size;
        int* nums = new int[newsize];
        for(int i = 0;i<other1.size;i++){
            nums[i] = other1.multiset[i];
        }
        for(int j = 0;j<other2.size;j++){
            nums[other1.size+j] = other2.multiset[j];
        }
        
        int* uniqueels2 = new int[newsize];
        int len2 = 0;
        for(int i = 0;i<newsize;i++){
            if(!isinthereprim(nums[i], uniqueels2, len2)){
                uniqueels2[len2++] = nums[i];
            }
        }
        int* counts = new int[len2];
        int Count = 0;
        for(int k = 0;k<len2;k++){
            int c = countels(nums, newsize, uniqueels2[k]);
            counts[k] = c >= 3 ? 3 : c; 
            
            Count+=counts[k];
            
        }
      
        int* final = new int[Count];
        int o = 0;
        for(int k = 0;k<len2;k++){
            for(int j = 0;j<counts[k];j++){
                final[o++] = uniqueels2[k];
            }
        }
        
        MultiSet m;
        m.multiset = final;
        m.size = Count;
        delete[] uniqueels2;
        delete[] counts;
        delete[] nums;
    
        return m;
    }
    

    void MultiSet::free(){
        delete[] multiset;
        multiset = nullptr;
    }
    void MultiSet::copyFrom(const MultiSet& other){
        size = other.size;
        multiset = new int[size];
        for(int i = 0;i<size;i++){
            multiset[i] = other.multiset[i];
        }
    }
    void MultiSet::resize(int newCap){
        int* helper = new int[newCap];
        for(int i = 0;i<size;i++){
            helper[i] = multiset[i];
        }
        
        delete[] multiset;
        multiset = helper;
        
    }
    void MultiSet::print() const{
        for(int i = 0;i<size;i++){
            std::cout<<multiset[i]<<' ';
        }
        std::cout<<'\n';
    }
    
    void MultiSet::print(const MultiSet& other) const{
        for(int i = 0;i<other.size;i++){
            std::cout<<other.multiset[i]<<' ';
        }
        std::cout<<'\n';
    }
    
    int MultiSet::getSize() const{
        return size;
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
//zad 3
    Song s1, s2;
    s1.setName("TestSong");
    s1.setGenre("rphej");
    std::cout<<(int)s1.getGenre();
    s1.setDuration(200);
    
    // Fake content for testing (no file needed)
    unsigned char data1[] = {0b01100001, 0b10101010};
    unsigned char data2[] = {0b01010101};
    
    s1.setContentFromMemory(data1, 2);  // you'd need to add this helper
    // s1.changeKbit(8);
    // s2.setContentFromMemory(data2, 1);
    
    // s1.mixSongs(s2);
    // const unsigned char* mixed = s1.getContent();
    // for (int i = 0; i < 2; i++) {
    //     printf("%02X ", mixed[i]);
    // }
    // std::cout << std::endl;
    // std::cout<<s1.getGenre();


    unsigned char el = 'a';
    Kbit(el, 2);
    //std::cout<<el;
    //zad 4
      MultiSet m(6);
    //m.print();
    m.addNum(8);
    //m.print();
    m.addNum(8);
    m.addNum(8);
    //m.addNum(8);
    //std::cout<<m.getSize();
    //std::cout<<m.count(8);
    m.addNum(8);
    m.removeNum(0);
    m.removeNum(8);
    m.removeNum(1);
    m.removeNum(3);
    m.addNum(4);
    m.print();
    
    MultiSet s(10);
    s.addNum(8);
    s.addNum(4);
    s.print();
    MultiSet m1;
  //  unionSets(m,s);
    m1 = intersection(m, s);
    m1.print();
    
    MultiSet m2 = unionSets(m, s);
    m2.print();
  //  m.addNum(8);
    //m.print();
    return 0;
}
