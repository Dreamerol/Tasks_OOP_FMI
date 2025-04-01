#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
class ArrayWrapper{
    public:
    
    ArrayWrapper();
    explicit ArrayWrapper(size_t n);
    ArrayWrapper(const int* arr, size_t size);
    void add(size_t index, int num);
    void remove(size_t index);
    ArrayWrapper(const ArrayWrapper& other);
    ArrayWrapper& operator = (const ArrayWrapper& other);
    ~ArrayWrapper();
    
    ArrayWrapper& addArrayWrapper(const ArrayWrapper& other);
    ArrayWrapper& substractArrayWrapper(const ArrayWrapper& other);
    size_t getSize() const;
    int getAtIndex(size_t index) const;
    int& getAtIndex(size_t index); // go promenqme
    void setAtIndex(size_t index, int num);
    
    void serialize(std::ostream& os);
    void deserialize(std::istream& is);
    void writeToBinaryFile(std::ifstream& os) const;
    void readFromBinaryFile(std::ifstream& is);
    private:
    void resize(size_t newCapacity);
    void free();
    void copyFrom(const ArrayWrapper& other);
    size_t size = 0;
    int* arr = nullptr;
    void modifyArray(const ArrayWrapper& other);
};


#include "ArrayWrapper.h"

//anonimen namespace - vidima e samo za tozi file
namespace{
    constexpr size_t INITIAL_CAPACITY = 16;
}
ArrayWrapper::ArrayWrapper(): size(0), capacity(INITIAL_CAPACITY)
{
     arr = new int[capacity] {};
 }
ArrayWrapper::ArrayWrapper(size_t n):size(n), capacity(n)
{
    arr = new int[capacity] {};
}
ArrayWrapper::ArrayWrapper(const int* arr, size_t size): ArrayWrapper(size)
{
    for(int i = 0;i<size;i++){
        this->arr[i] = arr[i];
    }
}
    void ArrayWrapper::add(size_t index, int num){
        if(index >= capacity){
            resize(index + 1);
            arr[size++] = num;
            return;
            
        }
        arr[index] = num;
    }
    void ArrayWrapper::resize(size_t newCapacity){
        capacity = newCapacity;
        int* resizedArray = new int[capacity];
        for(int i = 0;i<size;i++){
            resizedArray[i] = this->arr[i];
        }
        delete[] this->arr;
        this->arr = resizedArray;
    }
    void remove(size_t index);
    ArrayWrapper::ArrayWrapper(const ArrayWrapper& other){
        copyFRom(other);
    }
    ArrayWrapper& ArrayWrapper::operator = (const ArrayWrapper& other){
        if(this!=&other){
            free();
            copyFrom(other;)
        }
        return *this;
    }
    ~ArrayWrapper(){
        free();
    }
     void ArrayWrapper::serialize(std::ostream& os){
         os << size;
         for(int i = 0;i<size;i++){
             os<<arr[i];
         }
     }
     void ArrayWrapper::writeToBinaryFile(std::ifstream& ofs) const{
         ofs.write((const char*)&capacity,sizeof(capacity));
         ofs.write((const char*)&size, sizeof(size));
         ofs.write((const char*)&arr, sizeof(arr[0]) * size);//za da promenqme promenlivite
     }
    void ArrayWrapper::readFromBinaryFile(std::ifstream& ifs){
        //free();
        delete[] arr;
        ifs.read((char*)&capacity,sizeof(capacity));
         ifs.read((char*)&size, sizeof(size));
         ifs.read((char*)&arr, sizeof(arr[0]) * size);
    }
    void ArrayWrapper::deserialize(std::istream& is){
        is>>size;
        if(size >= capacity){
            resize();
        }
         for(int i = 0;i<size;i++){
             is>>arr[i];
         }
    }
    
    ArrayWrapper& ArrayWrapper::addArrayWrapper(const ArrayWrapper& other){
        modifyArray(other, add);
        size_t maxSize = std::max(size, other.size);
        for(int i = 0;i<maxSize;i++){
            setAtIndex(i, other.getAtIndex(i) + getAtIndex(i));
        }
        return *this;
    }
    void ArrayWrapper::modifyArray(const ArrayWrapper& other, bool add){
        size_t maxSize = std::max(size, other.size);
        if(add){
        for(int i = 0;i<maxSize;i++){
            setAtIndex(i, other.getAtIndex(i) + getAtIndex(i));
        }}
        else{
          for(int i = 0;i<maxSize;i++){
            setAtIndex(i, other.getAtIndex(i) - getAtIndex(i));
        }  
        }
        return *this;
    }
    ArrayWrapper& ArrayWrapper::substractArrayWrapper(const ArrayWrapper& other);
    size_t getSize() const;
    int ArrayWrapper::getAtIndex(size_t index) const{
        if(index >= size){
            return 0;
        }
        return arr[index];
    }
    int& ArrayWrapper::getAtIndex(size_t index); // go promenqme
    void ArrayWrapper::setAtIndex(size_t index, int num){
        if(index >= size){
            resize();
            arr[size++]=num;
        }
        arr[index] = num;
    }
   
    void ArrayWrapper::free(){
        delete[] arr;
        arr = nullptr;
        size = 0;
        capacity = 0;
        //dynamic object delete just
    }
    
    void ArrayWrapper::copyFrom(const ArrayWrapper& other){
        size = other.size;
        capacity = other.capacity;
        //arr = other.arr ne e dobre
        int* this->arr = new int[capacity];
        for(int i = 0;i<size;i++){
            this->arr[i] = other.arr[i];
        }
    }
    
int main()
{
    

    return 0;
}
