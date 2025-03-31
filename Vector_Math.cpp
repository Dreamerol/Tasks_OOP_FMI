#pragma once
class VectorOperations{
  public:
  Vector operatingWithVectors(Vector& a, Vector& b, double (*pred) (double , double));
  double scalarMultiplicationTwoVectors(Vector& a, Vector& b);
  bool isValidOperation(Vector& a, Vector& b);
  
};

#pragma once
class Vector{
  double* components=nullptr;
  int n=0;
  public:
  Vector() = default;
  Vector(const Vector& other);
  Vector& operator=(const Vector& other);
  double* getComponents() const;
  int getN() const;
  void setComponents(const double* components, int n);
  void scalarMultiplyVector(int scalar);
  void oneVector();
  double getLength();
  void print();
  
  ~Vector();
  private:
  void free();
  void copyFrom(const Vector& other);
  
};

#include "Vector.h"
#include "VectorOpeartions.h"

#include <iostream>
#include <cmath>
#include <fstream>
#include "Vector.cpp"

namespace vector_predicate_functions{
    double add(double a, double b){
        return a+b;
    }
    double substract(double a, double b){
        return a-b;
    }
}
Vector::Vector(const Vector& other){
    copyFrom(other);
}
Vector& Vector::operator = (const Vector& other){
    if(this != &other){
        free();
        copyFrom(other);
    }
    return *this;
}
void Vector::free(){
    if(components == nullptr){
        return;
    }
    delete[] components;
    components = nullptr;
}
void Vector::copyFrom(const Vector& other){
    if(other.n <= 0 || other.n != this->n){
        return;
    }
    this->n = other.n;
    for(int i = 0;i<this->n;i++){
        this->components[i] = other.components[i];
    }
}
void Vector::setComponents(const double* components, int n){
    if(components == nullptr){
        return;
    }
    this->n = n;
    this->components = new double[n];
    for(int i = 0;i<n;i++){
        this->components[i] = components[i];
    }
}
int Vector::getN() const{
    return n;
}
double Vector::getLength(){
    double sum = 0;
    for(int i = 0;i<n;i++){
        sum+=components[i]*components[i];
    }
    return sqrt(sum);
}
void Vector::oneVector(){
    
    double len = getLength();
    for(int i = 0;i<n;i++){
        components[i] = (components[i] / len);
    }
}

void Vector::scalarMultiplyVector(int scalar){
    for(int i = 0;i<n;i++){
        components[i] = (components[i] * scalar);
    }
}
Vector::~Vector(){
    free();
}
void Vector::write_in_binary_file(const char* filename){
    std::ofstream file(filename, std::ios::binary);
    if(!file){
        return;
    }
    file.write((const char*)&this->n, sizeof(int));
    for(int i = 0;i<n;i++){
        file.write((const char*)&this->components[i], sizeof(double));
    }
    file.close();
}
void Vector::read_from_file(const char* filename){
  
    std::ifstream file(filename, std::ios::binary);
    if(!file){
    
        return;
    }
    
    free();
    //first we free the memory before fulling it with
   // int size;
   
    file.read((char*)&this->n, sizeof(int));
    this->components = new double[this->n];
   // double* new_components = new double[size];
    for(int i = 0;i<n;i++){
        file.read((char*)&this->components[i], sizeof(double));
    
    }
    
    file.close();
}
void Vector::print(){
    std::cout<<n<<'\n';
    for(int i = 0;i<n;i++){
        std::cout<<components[i]<<' ';
    }
    std::cout<<'\n';
    std::cout<<getLength();
   // std::cout<<add_numbers(1, 2);
}
//bool Vector::isValidOperation()
double* Vector::getComponents() const{
    return this->components;
}
bool VectorOperations::isValidOperation(Vector& a, Vector& b){
    return(a.getN() == b.getN());
}
double VectorOperations::scalarMultiplicationTwoVectors(Vector& a, Vector& b){
    if(!isValidOperation(a, b)){
        return 0;
    }
    double sum = 0;
    for(int i =0;i<a.getN();i++){
        sum += a.getComponents()[i] * b.getComponents()[i];
    }
    return sum;
}
Vector VectorOperations::operatingWithVectors(Vector& a, Vector& b, double (*pred) (double , double)){
    if(!isValidOperation(a, b)){
       // return ;
    }
    Vector v;
    double* components_prim = new double[a.getN()];
    for(int i = 0;i<a.getN();i++){
        components_prim[i] = pred(a.getComponents()[i], b.getComponents()[i]);
    }
    v.setComponents(components_prim, a.getN());
    delete[] components_prim;
    
    return v;
    
}
int main()
{
     double* components = new double[5]{1, 2, 3, 4, 5.0};
     double* components1 = new double[5]{2, 3, 4, 6, 4};
//   //  components = ;
     Vector v1, v2;
     v1.setComponents(components, 5);
     v1.write_in_binary_file("v.bin");
     std::ifstream file("v.bin");
    //  int n;
    
    //  file.read((char*)&n, sizeof(int));
    //  std::cout<<n;
    //  for(int i = 0;i<n;i++){
    //      double v4;
    //      file.read((char*)&v4, sizeof(double));
    //      std::cout<<v4<<' ';
    //  }
    Vector v5;
    v5.setComponents(nullptr, 5);
     v5.read_from_file("v.bin");
     v5.print();
    //  v2.setComponents(components1, 5);
    //  VectorOperations v;
    //  Vector v3 = v.operatingWithVectors(v1, v2, vector_predicate_functions::substract);
    //  v3.print();
//     v.print();
//     v.scalarMultiplyVector(5);
//     v.print();
//      v.oneVector();
//      v.print();
    return 0;
}
