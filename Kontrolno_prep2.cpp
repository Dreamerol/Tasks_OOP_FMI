//zad 1
#pragma once
class MyVector{
    int* data;
    int size;
    
    public:
    MyVector();
    MyVector(int size);
    MyVector(int* data, int size);
    ~MyVector();
    MyVector(const MyVector& other);
    MyVector& operator=(const MyVector& other);
    
    MyVector& operator++();
    MyVector operator++(int);
    MyVector& operator+=(const MyVector& other);
    MyVector& operator-=(const MyVector& other);
    MyVector& operator*=(double scalar);
    int operator[](int index) const;
    int& operator[](int index);//this can't be const because & means we can change the returned object
    int operator~() const;
MyVector& calculate(const MyVector& other, int(*operation)(int, int));
void saveToFile(std::ofstream& ofs) const;
void loadFromFile(std::ifstream& ifs);
friend std::ostream& operator<<(std::ostream& os,const MyVector& other);
friend std::istream& operator>>(std::istream& is, MyVector& other); 
    
    private:
    void resize(int newSize);
    void copyFrom(const MyVector& other);
    void free();
};

MyVector operator+(const MyVector& a, const MyVector& b);
MyVector operator-(const MyVector& a, const MyVector& b);
int operator%(const MyVector& a, const MyVector& b);
MyVector operator*(const MyVector& a, int scalar);
MyVector operator*(int scalar, const MyVector& other);
bool operator|(const MyVector& a, const MyVector& b);
bool operator||(const MyVector& a, const MyVector& b);


#include <iostream>
#include <fstream>
#include "MyVector.h"

    MyVector::MyVector():MyVector(3){};
    MyVector::MyVector(int size){
        data = new int[size]{};
        this->size = size;
    }
    MyVector::MyVector(int* data, int size){
        this->size = size;
        this->data = new int[size];
        for(int i = 0;i<size;i++){
            this->data[i] = data[i];
        }
    }
    MyVector::~MyVector(){
        free();
    }
    MyVector::MyVector(const MyVector& other){
        copyFrom(other);
    }
    MyVector& MyVector::operator=(const MyVector& other){
        if(this!=&other){
            free();
            copyFrom(other);
        }
        return *this;
    }
    int sum(int a, int b){
        return a+b;
    }    
    MyVector& MyVector::operator+=(const MyVector& other){
        return calculate(other, sum);
        // if(other.size != size){
        //     throw std::logic_error("Can't sum them!!!");
        // }
        // for(int i = 0;i<size;i++){
        //     data[i] += other.data[i];
        // }
        // return *this;
    }

    MyVector& MyVector::operator-=(const MyVector& other){
        return calculate(other, [](int a, int b){return a-b;});
        // if(other.size != size){
        //     throw std::logic_error("Can't sum them!!!");
        // }
        // for(int i = 0;i<size;i++){
        //     data[i] -= other.data[i];
        // }
        // return *this;
    }
    MyVector& MyVector::calculate(const MyVector& other,int (*pred)(int, int)){
        int maxi = size > other.size ? size : other.size;
        if(size < maxi){
            resize(maxi);
        }
        
        for(int i = 0;i<maxi;i++){
            if(i <other.size){
            data[i] = pred(data[i],other.data[i]);
                
            }
        }
        return *this;
    }
    MyVector& MyVector::operator*=(double scalar){
        for(int i = 0;i<size;i++){
            data[i] *= scalar;
        }
        return *this;
    }
    int MyVector::operator[](int index) const{
        if(index > size || index < 0){
            throw(std::out_of_range("index_out_of_range"));
        }
        return data[index];
    }
    int& MyVector::operator[](int index){
        if(index > size){
            throw(std::out_of_range("index_out_of_range"));
        }
        return data[index];
    }
        //this can't be const because & means we can change the returned object
    int MyVector::operator~() const{
        return size;
    }
//NVector& calculate(const NVector& other, int(*operation)(int, int));
// void MyVector::saveToFile(std::ofstream& ofs) const
// {
// 	ofs.write((const char*)&size, sizeof(size));
// 	ofs.write((const char*)data, size * sizeof(data[0]));
// }
void MyVector::saveToFile(std::ofstream& ofs) const{
    ofs.write((const char*)&this->size, sizeof(int));
    ofs.write((const char*)this->data, sizeof(int) * this->size);
    
    // for(int i = 0;i<size;i++){
    //     ofs << data[i]<< ' ';
    // }
    
}
void MyVector::loadFromFile(std::ifstream& ifs){
    
    ifs.read((char*)&this->size, sizeof(int));
    ifs.read((char*)this->data, sizeof(int) * this->size);
}
 
    
  
    void MyVector::resize(int newSize){
        int* newdata = new int[newSize];
        for(int i = 0;i<size;i++){
            newdata[i] = data[i];
        }
        delete[] data;
        this->size = newSize;
        data = newdata;
    }
    void MyVector::copyFrom(const MyVector& other){
        this->size = other.size;
        this->data = new int[this->size];
        for(int i = 0;i<size;i++){
            this->data[i] = other.data[i];
        }
    }
    void MyVector::free(){
        delete[] data;
        data = nullptr;
        size = 0;
    }
    
MyVector operator+(const MyVector& a, const MyVector& b){
    MyVector prim(a);
    prim += b;
    return prim;
}
MyVector operator-(const MyVector& a, const MyVector& b){
    MyVector prim(a);
    prim -= b;
    return prim;
}
int operator%(const MyVector& a, const MyVector& b){
    if(~a != ~b){
        return -1;
    }
    int result = 0;
    for(int i = 0;i<~a;i++){
        result += a[i] * b[i];
    }
    
    return result;
}
MyVector operator*(const MyVector& a, int scalar){
    MyVector prim(a);
    prim *= scalar;
    // for(int i = 0;i<~a;i++){
    //     a[i] *= scalar;
    // }
    return prim;
}
MyVector operator*(int scalar, const MyVector& other){
    MyVector prim(other);
    prim *= scalar;
    return prim;
}
bool operator|(const MyVector& a, const MyVector& b){
    return (a%b == 0);
}
const double EPSILON = 1e-10;
bool operator||(const MyVector& a, const MyVector& b){
    if(~a != ~b){
        return false;
    }
    bool flag = false;
    double currentRatio = 0;
    for(int i = 0;i<~a;i++){
        double ratio;
        if(a[i] == 0 && b[i]==0){
            continue;
        }
        else if(a[i] == 0 || b[i] == 0){
            return false;
        }
        ratio = a[i] / b[i];
        if(flag){
        if(abs(ratio-currentRatio) > EPSILON){
            return false;}
        }
        currentRatio = ratio;
        flag = true;
    }
    return true;
    
}
std::ostream& operator<<(std::ostream& os,const MyVector& other){
    for(int i = 0;i<other.size;i++){
        os << other.data[i]<<' ';
    }
    return os;
}
std::istream& operator>>(std::istream& is,MyVector& other){
    for(int i = 0;i<other.size;i++){
        is >> other.data[i];
    }
    return is;
}
    MyVector& MyVector::operator++(){
        for(int i = 0;i<size;i++){
            data[i] += 1;
        }
        return *this;
    }
    MyVector MyVector::operator++(int){
        for(int i = 0;i<size;i++){
            data[i]++;
        }
        return *this;
    }

//zad 2
#pragma once
class Car{
    char* model=nullptr;
    unsigned miles=0;
    
    public:
    Car();
    Car(const char* model, unsigned miles);
    Car(const Car& other);
    Car& operator=(const Car& other);
    ~Car();
    const char* getModel() const;
    unsigned getMiles() const;
    void travel(unsigned miles);
    
    private:
    void copyFrom(const Car& other);
    void free();
    void setModel(const char* model);
    
};
#pragma once
class Parking{
  Car** spaces = nullptr;
  size_t carsCount = 0;
  size_t maxCap = 0;
  size_t firstfreeIndex = 0;
  
  public:
  explicit Parking(size_t maxCap);
  Parking();
  ~Parking();
  Parking(const Parking& other);
  Parking& operator=(const Parking& other);
  void updateFreeIndex();
  size_t getCarsCount() const;
  size_t getMaxCap() const;
  size_t getFirstFreeIndex() const;
  
  bool parkCar(const Car& other);
  bool removeCar(size_t index);
  private:
  
  void copyFrom(const Parking& other);
  void free();
  
  
};



#include <iostream>
#include <cstring>
#include "Car.h"
#include "Parking.h"
Car::Car() = default; 
    Car::Car(const Car& other){
        copyFrom(other);
    }
    Car& Car::operator=(const Car& other){
        if(this != &other){
            free();
            copyFrom(other);
        }
        return *this;
    }
    Car::~Car(){
        free();
    }
    const char* Car::getModel() const{
        return model;
    }
    unsigned Car::getMiles() const{
        return miles;
    }
    void Car::travel(unsigned miles){
       this->miles += miles;
    }
    void Car::setModel(const char* model){
        if(model == nullptr){
            return;
        }
        if(this->model == model){
            return;
        }
        
        delete[] this->model;
        this->model = new char[strlen(model) + 1];
        strcpy(this->model, model);
    }
    Car::Car(const char* model, unsigned miles){
        this->miles = miles;
        setModel(model);
    }
    void Car::copyFrom(const Car& other){
        setModel(other.model);
        miles = other.miles;
    }
    void Car::free(){
        delete[] this->model;
        this->model = nullptr;
    }
    
    
  Parking::Parking(size_t maxCap){
      spaces = new Car*[maxCap]{nullptr};
      this->maxCap = maxCap;
  }
  Parking::Parking() : Parking(8){};
  Parking::~Parking(){
      free();
  }
  Parking::Parking(const Parking& other){
      copyFrom(other);
  }
  Parking& Parking::operator=(const Parking& other){
      if(this != &other){
          free();
          copyFrom(other);
      }
      return *this;
  }
  
  size_t Parking::getCarsCount() const{
      return carsCount;
  }
  size_t Parking::getMaxCap() const{
      return maxCap;
  }
  size_t Parking::getFirstFreeIndex() const{
      return firstfreeIndex;
  }
  
  void Parking::updateFreeIndex(){
      for(int i = 0;i<maxCap;i++){
          if(spaces[i] == nullptr){
              firstfreeIndex = i;
              return;
          }
      }
  }
  bool Parking::parkCar(const Car& other){
      if(maxCap == carsCount){
          return false;
      }
      
      spaces[firstfreeIndex] = new Car(other);
      carsCount++;
      updateFreeIndex();
      return true;
      
  }
  bool Parking::removeCar(size_t index){
      if(index <0 || index > maxCap){
          throw std::out_of_range("No car with this idx!");
      }
      if(spaces[index] == nullptr){
          return false;
      }
      
      if(firstfreeIndex > index){
          firstfreeIndex = index;
      }
      carsCount--;
      delete spaces[index];
      spaces[index] = nullptr;
      return true;
      
  }
  
  void Parking::copyFrom(const Parking& other){
      maxCap = other.maxCap;
      firstfreeIndex = other.firstfreeIndex;
      carsCount = other.carsCount;
      spaces = new Car*[maxCap];
      for(int i=0;i<maxCap;i++){
          spaces[i] = other.spaces[i];
      }
  }
  void Parking::free(){
      for(int i = 0;i<maxCap;i++){
          delete spaces[i];
      }
      delete[] spaces;
  }
int main(){
    int* data = new int[3];
    data[0] = 1;
    data[1] = 2;
    data[2] = 3;
    MyVector v(data, 3);
    MyVector v1(data, 3);
    MyVector v2 = v * 9;
    v2++;
    std::cout<< v2[0];
    
    return 0;
}
