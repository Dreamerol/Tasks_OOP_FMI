
//zad 1
#include <iostream>
template <class T>

class Optional{
    private:
    bool hasValue;
    T value;
    public:
    Optional() : hasValue(false){};
    Optional(const T& val) : hasValue(true), value(val){};
    
    bool has_value() const{
        return hasValue;
    }
    
    T& get_value() {
        if(!hasValue){
            throw std::runtime_error("NO value!");
        }
        return value;
    }
    
    void set_value(const T& other){
        this->value = other;
        hasValue = true;
    }
    void reset(){
        hasValue = false;
    }
    
    T& operator*(){
        if(!hasValue){
            throw std::runtime_error("ERROR");
        }
        return value;
    }
};
    

int main()
{
    
    Optional<int> opt;

    if (!opt.has_value()) {
        std::cout << "No value yet.\n";
    }

    opt.set_value(42);

    if (opt.has_value()) {
        std::cout << "Value is: " << *opt << std::endl;
        std::cout << "Also using get_value(): " << opt.get_value() << std::endl;
    }

    opt.reset();

    if (!opt.has_value()) {
        std::cout << "Value has been reset.\n";
    }

    return 0;

}

//zad2
#include <iostream>
template<class T, const unsigned S>
class Stack {
	T arr[S];
	size_t size = 0;
public:
	void push(const T& other);
	const T& peek() const;
	void pop();
	const size_t getSize() const;
	bool isEmpty() const;
	bool isFull() const;


};
template<class T, const unsigned S>
void Stack<T, S>::push(const T& other) {
	if(isFull()) {
		throw std::runtime_error("No space!");
	}
	arr[size++] = other;
}
template<class T, const unsigned S>
void Stack<T, S>::pop() {
	if(isEmpty()) {
		throw std::out_of_range("empty");
	}
	size--;
}
template<class T, const unsigned S>
const T& Stack<T, S>::peek() const{
if(isEmpty()){
        throw std::out_of_range("empty");
    }
    return arr[size-1];
}
template<class T, const unsigned S>
const size_t Stack<T,S>::getSize()const{
    return size;
}
template<class T, const unsigned S>
bool Stack<T, S>::isEmpty() const{
    return size==0;
    
}
template<class T, const unsigned S>
bool Stack<T, S>::isFull() const{
    return size==S;

//zad 3
#include <iostream>
#define T1 template<class T>

template <class T>
class Queue{
    
    private:
    T* arr = nullptr;
    
    size_t size = 0;
    size_t capacity = 8;
    
    size_t get = 0;
    size_t put = 0;
    
    void free();
    void copyFrom(const Queue<T>& other);
    void resize(size_t newCap);
    
    public:
    
    Queue();
    Queue(const Queue<T>& other);
    Queue(size_t capacity);
    
    Queue& operator=(const Queue<T>& other);
    void push(const T& other);
    void pop();
    const T& peek() const;
    const size_t getSize() const;
    bool isEmpty() const;
    ~Queue();
    
};

T1
void Queue<T>::free(){
    delete[] arr;
    arr = nullptr;
}
T1
void Queue<T>::copyFrom(const Queue<T>& other){
    this->size = other.size;
    this->capacity = other.capacity;
    this->put = other.put;
    this->get = other.get;
    
    arr = new T[other.capacity];
    for(int i = 0;i<size;i++){
        this->arr[i] = other.arr[i];
    }
    
}
T1
void Queue<T>::resize(size_t newCap){
    T* newarr = new T[newCap];
    for(int i = 0;i<size;i++){
        newarr[i] = arr[get];
        (++get)%=capacity;
    }
    
    delete[] arr;
    arr = newarr;
    this->capacity = newCap;
    get = 0;
    put = size;
}
T1 
Queue<T>::Queue() : Queue(8){};
T1
Queue<T>::Queue(size_t newCap){
    arr = new T[newCap]{};
    this->capacity = newCap;
}
T1
Queue<T>::Queue(const Queue<T>& other){
    copyFrom(other);
}
T1
Queue<T>& Queue<T>::operator=(const Queue<T>& other){
    if(this != &other){
        free();
        copyFrom(other);
    }
    return *this;
}
T1
Queue<T>::~Queue(){
    free();
}

T1
void Queue<T>::push(const T& obj){
    if(size >= capacity){
        resize(capacity*2);
    }
    if(put == capacity){
        put = 0;
    }
    else{
        put++;
    }
    arr[put] = obj;
    size++;
    
}
T1
void Queue<T>::pop(){
    if(isEmpty()){
        throw std::out_of_range("ERROR");
    }
    (++get)%=capacity;
    size--;
}
T1
const T& Queue<T>::peek() const{
    if(isEmpty()){
        throw std::out_of_range("ERROR");
    }
    return arr[get];
}
T1
bool Queue<T>::isEmpty()const {
    return size == 0;
}
T1
const size_t Queue<T>::getSize() const{
    return size;
}
//zad 4
#pragma once
enum class BattleOutput{
    WIN,
    DRAW,
    LOSS
};
class Minotaur;
class Centaur;
class Sphinx;

class Beast{
    public:
    Beast() = default;
    virtual Beast* clone() const = 0;
    virtual ~Beast() = default;
    virtual BattleOutput beats(const Beast* other) const = 0;
    virtual BattleOutput beatsMinotaur(const Minotaur* other) const = 0;
    virtual BattleOutput beatsCentaur(const Centaur* other) const = 0;
    virtual BattleOutput beatsSphinx(const Sphinx* other) const = 0;
};
#pragma once
#include "Beast.h"
class Minotaur : public Beast{
    public:
    Minotaur() = default;
    virtual Beast* clone() const override;
    virtual BattleOutput beats(const Beast* other) const override;
    virtual BattleOutput beatsMinotaur(const Minotaur* other) const override;
    virtual BattleOutput beatsCentaur(const Centaur* other) const override;
    virtual BattleOutput beatsSphinx(const Sphinx* other) const override;
    
};
#pragma once
#include "Beast.h"
class Centaur:public Beast{
    public:
    Centaur() = default;
    virtual Beast* clone() const override;
    virtual BattleOutput beats(const Beast* other) const override;
    virtual BattleOutput beatsMinotaur(const Minotaur* other) const override;
    virtual BattleOutput beatsCentaur(const Centaur* other) const override;
    virtual BattleOutput beatsSphinx(const Sphinx* other) const override;
    
};

#pragma once
#include "Beast.h"
class Sphinx:public Beast{
    public:
    Sphinx() = default;
    virtual Beast* clone() const override;
    virtual BattleOutput beats(const Beast* other) const override;
    virtual BattleOutput beatsMinotaur(const Minotaur* other) const override;
    virtual BattleOutput beatsCentaur(const Centaur* other) const override;
    virtual BattleOutput beatsSphinx(const Sphinx* other) const override;
    
};

#include "Minotaur.h"

Beast* Minotaur::clone() const{
    return new Minotaur(*this);
    
}
BattleOutput Minotaur::beats(const Beast* other) const{
    return other->beatsMinotaur(this);
}
BattleOutput Minotaur::beatsMinotaur(const Minotaur* other) const{
    return BattleOutput::DRAW;
}

BattleOutput Minotaur::beatsCentaur(const Centaur* other) const{
    return BattleOutput::LOSS;
}
BattleOutput Minotaur::beatsSphinx(const Sphinx* other) const{
    return BattleOutput::WIN;
}

#include "Centaur.h"

Beast* Centaur::clone() const{
    return new Centaur(*this);
    
}
BattleOutput Centaur::beats(const Beast* other) const{
    return other->beatsCentaur(this);
}
BattleOutput Centaur::beatsMinotaur(const Minotaur* other) const{
    return BattleOutput::WIN;
}

BattleOutput Centaur::beatsCentaur(const Centaur* other) const{
    return BattleOutput::DRAW;
}
BattleOutput Centaur::beatsSphinx(const Sphinx* other) const{
    return BattleOutput::LOSS;
}


#include "Sphinx.h"

Beast* Sphinx::clone() const{
    return new Sphinx(*this);
    
}
BattleOutput Sphinx::beats(const Beast* other) const{
    return other->beatsSphinx(this);
}
BattleOutput Sphinx::beatsMinotaur(const Minotaur* other) const{
    return BattleOutput::LOSS;
}

BattleOutput Sphinx::beatsCentaur(const Centaur* other) const{
    return BattleOutput::WIN;
}
BattleOutput Sphinx::beatsSphinx(const Sphinx* other) const{
    return BattleOutput::DRAW;
}
#pragma once
#include "Minotaur.h"
#include "Centaur.h"
#include "Sphinx.h"

class Arena{
  private:
  Beast** beasts;
  int size;
  int capacity;
  
  void copy(const Arena& other);
  void resize(int newCap);
  void destroy();
  
  public:
  
  Arena();
  ~Arena();
  Arena(const Beast** monsters, int size);
  Arena(const Arena& other);
  Arena& operator=(const Arena& other);
  Beast* getBeastOnIdx(int idx) const;
  int NumberBeatenMonsters(const Beast* beats) const;
};
#include "ARENA.h"

void Arena::copy(const Arena& other){
    capacity = other.capacity;
    size = other.size;
    beasts = new Beast*[capacity];
    for(int i = 0;i<size;i++){
        beasts[i] = other.beasts[i]->clone();
    }
    
}
  void Arena::resize(int newCap){
      Beast** newb = new Beast*[newCap];
      for(int i =0;i<size;i++){
         newb[i] = beasts[i]->clone();
         // newb[i] = new Beast(*beasts[i]);
      }
      this->capacity = newCap;
      destroy();
      //delete[] beasts;
      beasts = newb;
  }
  void Arena::destroy(){
      for(int i = 0;i<size;i++){
          delete beasts[i];
      }
      delete[] beasts;
      beasts = nullptr;
  }
  

  Arena::~Arena(){
      destroy();
  }
  Arena::Arena(const Arena& other){
      copy(other);
  }
  Arena::Arena(){
      this->capacity = 8;
     beasts = new Beast*[capacity];
     size = 0;
  }
  Arena::Arena(const Beast** monsters, int size){
     beasts = new Beast*[size];
     this->capacity = size;
     this->size= size;
     for(int i = 0;i,size;i++){
         beasts[i] = monsters[i]->clone();
         }
  }
  Arena& Arena::operator=(const Arena& other){
      if(this != &other){
          destroy();
          copy(other);
      }
      return *this;
  }
  Beast* Arena::getBeastOnIdx(int idx) const{
      if(idx > size || idx<0){
          return nullptr;
      }
      return beasts[idx]->clone();
  }
  int Arena::NumberBeatenMonsters(const Beast* beast) const{
      int count = 0;
      for(int i = 0;i<size;i++){
          if(beasts[i]->beats(beast) == BattleOutput::WIN){
              count++;
          }
      }
      return count;
  }

//zad 5 - MyVector
template<typename T>
#define T1 template<typename T>
class MyVector{
    private:
    T* els;
    size_t size;
    size_t capacity;
    
    
    void copy(const MyVector<T>& other);
    void resize(size_t newCap);
    void free();

public:    
    MyVector();
    ~MyVector();
    MyVector(const MyVector<T>& other);
    MyVector<T>& operator=(const MyVector<T>& other);
    
MyVector(size_t n);
MyVector(size_t n, const T& elem);
void push_back(const T& elem);
void pop_back();
void insert(size_t idx, const T& elem);
void erase(size_t idx);
T& operator[](size_t idx);
const T& operator[](size_t idx) const;
void shrink_to_fit();
void clear();
T& front();
T& back();
const T& front() const;
const T& back() const;
bool empty() const;
size_t getSize() const;
size_t getCapacity() const;
    
    
};

T1
void MyVector<T>::copy(const MyVector<T>& other){
    size = other.size;
    capacity = other.capacity;
    els = new T[capacity];
    for(int i = 0;i<size;i++){
        els[i] = other.els[i];
    }
}
T1
void MyVector<T>::resize(size_t newCap){
    T* newels = new T[newCap];
    for(int i = 0;i<size;i++){
        newels[i] = els[i];
    }
    delete[] els;
    els = newels;
    this->capacity = newCap;
}
T1
void MyVector<T>::free(){
    delete[] els;
    els = nullptr;
}
T1
MyVector<T>::MyVector(){
    capacity = 8;
    size = 0;
    els = new T[capacity]{};
    
}
T1
MyVector<T>::~MyVector(){
    free();
}
T1
MyVector<T>::MyVector(const MyVector<T>& other){
    copy(other);
}
T1
MyVector<T>& MyVector<T>::operator=(const MyVector<T>& other){
    if(this != &other){
        free();
        copy(other);
    }
    return *this;
}
T1    
MyVector<T>::MyVector(size_t n){
    size = n;
    capacity = n;
    els = new T[capacity]{};
}
T1
MyVector<T>::MyVector(size_t n, const T& elem){
    size = n;
    capacity = n;
    els = new T[capacity];
    for(int i = 0;i<size;i++){
        els[i] = elem;
    }
}
T1
void MyVector<T>::push_back(const T& elem){
    if(size == capacity){
        resize(capacity * 2);
    }
    els[size++] = elem;
}
T1
void MyVector<T>::pop_back(){
    if(empty()){
         throw std::out_of_range("ERROR");
    }
    size--;
}
T1
void MyVector<T>::insert(size_t idx, const T& elem){
    if(idx >= size){
        throw std::out_of_range("ERROR");
    }
    if(size == capacity){
        resize(capacity*2);
    }
    T* newels = new T[capacity];
    int l = 0;
    for(int i = 0;i<size;i++){
        if(idx == i) {
            newels[l++] = elem;
            
        }
        newels[l++] = els[i];
    }
    size++;
    delete[] els;
    els = newels;
}
T1
void MyVector<T>::erase(size_t idx){
    if(idx >= size || empty()){
        throw std::out_of_range("ERROR");
    }
    T* newels = new T[capacity];
    int l = 0;
    for(int i = 0;i<size;i++){
        if(idx == i) continue;
        newels[l++] = els[i];
    }
    size--;
    delete[] els;
    els = newels;

// for(int i = idx;i<size-1;i++){
    //     els[i] = els[i+1];
    // }
    // size--;
}
T1
const T& MyVector<T>::operator[](size_t idx) const {
    if(idx >= size){
        throw std::out_of_range("ERROR");
    }
    return els[idx];
}
T1
T& MyVector<T>::operator[](size_t idx){
    if(idx >= size){
        throw std::out_of_range("ERROR");
    }
    return els[idx];
}
T1
void MyVector<T>::shrink_to_fit(){
    resize(size);
}
T1
void MyVector<T>::clear(){
    size = 0;
}
T1
const T& MyVector<T>::front() const{
    if(empty()){
        throw std::out_of_range("ERROR");
    }
    return els[0];
}
T1
const T& MyVector<T>::back() const{
    if(empty()){
        throw std::out_of_range("ERROR");
    }
    return els[size-1];
}
T1
T& MyVector<T>::front(){
    if(empty()){
        throw std::out_of_range("ERROR");
    }
    return els[0];
}
T1
T& MyVector<T>::back(){
    if(empty()){
        throw std::out_of_range("ERROR");
    }
    return els[size-1];
}
T1
bool MyVector<T>::empty() const{
    return size==0;
}
T1
size_t MyVector<T>::getSize() const{
    return size;
}
T1
size_t MyVector<T>::getCapacity() const{
    return capacity;
}

//REF trqbva da byde const const T& - nqma da imame parvo da promenqme obekta=>func e konst
//const T& getT() const{
return T_var;
}

//REF ne e const -  moje da izmeni systoqnieto a obekta => nqma kak func da e konst;
//T& getT() {
return T_var;
}
