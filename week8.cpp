//zad 1

#pragma once
class SpecialCustomFunction{
    int (*special) (int);
    int* numbers;
    int size;
    
    public:
    SpecialCustomFunction(int* arr, int size, int (*special) (int));
    SpecialCustomFunction();
    SpecialCustomFunction(const SpecialCustomFunction& other);
    SpecialCustomFunction& operator=(const SpecialCustomFunction& other);
    void print() const;
    ~SpecialCustomFunction();
    int operator()(int number);
      
    SpecialCustomFunction operator!();
    SpecialCustomFunction& operator++();
    SpecialCustomFunction operator++(int);
    SpecialCustomFunction& operator--();
    SpecialCustomFunction operator--(int);
    private:
    void copyFrom(const SpecialCustomFunction& other);
    void free();
    
};
// C++ program to create a global function as a friend
// function of some class
#include <iostream>
#include "SpecialCustomFunction.h"
SpecialCustomFunction::SpecialCustomFunction(int* arr, int size, int (*special) (int)){
        numbers = new int[size];
        this->size = size;
        for(int i = 0;i<size;i++){
            numbers[i] = arr[i];
        }
        this->special = special;
    }
    SpecialCustomFunction::SpecialCustomFunction() : size(0), numbers(nullptr), special(nullptr){};
    SpecialCustomFunction::SpecialCustomFunction(const SpecialCustomFunction& other){
        copyFrom(other);
    }
    SpecialCustomFunction& SpecialCustomFunction::operator=(const SpecialCustomFunction& other){
        if(this!=&other){
            free();
            copyFrom(other);
        }
        return *this;
    }
    
    SpecialCustomFunction::~SpecialCustomFunction(){
        free();
    }
    int SpecialCustomFunction::operator()(int number){
        for(int i = 0;i<size;i++){
            if(number == numbers[i]){
                return (number*number);
            }
        }
        return special(number);
    }
    SpecialCustomFunction SpecialCustomFunction::operator!(){
        SpecialCustomFunction other = *this;
        for(int i = 0;i<other.size;i++){
            other.numbers[i] = -other.numbers[i];
        }
        return other;
    }
    SpecialCustomFunction SpecialCustomFunction::operator++(int){
        SpecialCustomFunction other = *this;
        for(int i = 0;i<other.size;i++){
            other.numbers[i]+=1;
        }
        return other;
    }
    SpecialCustomFunction& SpecialCustomFunction::operator++(){
        for(int i = 0;i<size;i++){
            numbers[i]++;
        }
        return *this;
    }
    SpecialCustomFunction SpecialCustomFunction::operator--(int){
        SpecialCustomFunction other = *this;
        for(int i = 0;i<other.size;i++){
            other.numbers[i]-=1;
        }
        return other;
    }
    // SpecialCustomFunction& SpecialCustomFunction::operator++(){
    //     for(int i = 0;i<other.size;i++){
    //         numbers[i]--;
    //     }
    //     return *this;
    // }
    SpecialCustomFunction& SpecialCustomFunction::operator--(){
        for(int i = 0;i<size;i++){
            numbers[i] -= 1;
            //std::cout<<numbers[i]<<' ';
        }
        return *this;
    }
    void SpecialCustomFunction::copyFrom(const SpecialCustomFunction& other){
        special = other.special;
        size = other.size;
        numbers = new int[size];
        for(int  i = 0;i<size;i++){
            numbers[i] = other.numbers[i];
        }
    }
    void SpecialCustomFunction::free(){
        delete[] numbers;
    }
    void SpecialCustomFunction::print() const{
        for(int i = 0;i<size;i++){
            std::cout<<numbers[i]<<' ';
        }
    }


int main()
{
    int arr[5] = { 3,-4,0,10,40 };
    SpecialCustomFunction func(arr, 5, [](int num) -> int { return num * num + num; });
   // std::cout<<func(3);
     --func;
     func.print();
     std::cout << func(-5) << std::endl;
         SpecialCustomFunction func2 = !func; 
         func2.print();
         std::cout << func2(5) << std::endl; // 25
    // std::cout << func(7) << std::endl << func(-4); // 56 16
    func2--;
    func2.print();
    
    return 0;
}

