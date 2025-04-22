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
//zad 2
#pragma once
enum class Type{
    Villa,
    Hotel,
    Apartment,
    Default
};
struct Point{
    int x;
    int y;
};
class Accomodation{
    size_t id = 0;
    char* name = nullptr;
    Type type = Type::Default;
    Point location = {0, 0};
    double price = 0;
    bool isTaken = 0;
    size_t daysCount = 0;
    
    public:
    void setIsTaken(bool taken);
    void setName(const char* name);
    void setType(Type type);
    Point& getLocation();
    Accomodation(size_t id, const char* name, Type type,Point location,double price,bool isTaken,size_t daysCount);
    Accomodation();
    ~Accomodation();
    Accomodation& operator=(const Accomodation& other);
    Accomodation(const Accomodation& other);
    size_t getId() const;
    void makeReservation(size_t daysCount);
    void removeReservation();
    double priceStay();
    void setDaysCount(int daysCount);
    private:
    void copyFrom(const Accomodation& other);
    void free();
    
    
};

#pragma once
class AirBnB{
  Accomodation* places = nullptr;
  int count = 0;
  
  public:
  AirBnB();
  AirBnB(const AirBnB& other);
  AirBnB& operator=(const AirBnB& other);
  ~AirBnB();
  
  bool isValidId(size_t id) const;
  void addPlace(const Accomodation& other);
  void makeReservationById(size_t id, size_t daysCount);
  void removeReservationById(size_t id);
  double profit();
  Point& closestLocation(Point point);
  void removePlace(size_t id);
  int findIndex(size_t id) const;
  friend double calculateDistance(int x1, int y1, int x2, int y2);
  void print();
  void err(size_t id);
  private:
  void copyFrom(const AirBnB& other);
  void free();
    
};





#include <iostream>
#include <cmath>
#include <cstring>
#include "Accomodation.h"
#include "AirBnB.h"
#pragma warning (disable:4996)

 
  Point& Accomodation::getLocation() {
        return location;
    }
    void Accomodation::setType(Type type){
        this->type = type;
    }
    void Accomodation::setIsTaken(bool taken){
        this->isTaken = taken;
    }
    Accomodation::Accomodation(size_t id, const char* name, Type type,Point location,double price,bool isTaken,size_t daysCount){
        setName(name);
        setType(type);
        this->id = id;
        this->location = {location.x, location.y};
        this->price = price;
        this->isTaken = isTaken;
        this->daysCount = daysCount;
    }
    Accomodation::Accomodation() = default;
    Accomodation::~Accomodation(){
        free();
    }
    Accomodation& Accomodation::operator=(const Accomodation& other){
        if(this != &other){
            free();
            copyFrom(other);
        }
        return *this;
    }
    Accomodation::Accomodation(const Accomodation& other){
        copyFrom(other);
    }
    
    void Accomodation::makeReservation(size_t daysCount){
        this->isTaken = true;
        this->daysCount = daysCount;
        
    }
    void Accomodation::removeReservation(){
        this->daysCount = 0;
        this->isTaken = false;
    }
    double Accomodation::priceStay(){
        if(this->isTaken){
        return this->daysCount * this->price;
    }
        else return 0;
    }
    
    void Accomodation::copyFrom(const Accomodation& other){
        setName(other.name);
        this->type = other.type;
        this->daysCount = other.daysCount;
        this->price = other.price;
        this->isTaken = other.isTaken;
        this->id = other.id;
        this->location = {other.location.x, other.location.y};
        
    }
    void Accomodation::free(){
        delete[] name;
    }
    size_t Accomodation::getId() const{
        return id;
    }
void Accomodation::setName(const char* name){
        if(name == nullptr){
            return;
        }
        if(this->name == name){
            return;
        }
        delete[] this->name;
        this->name=  new char[strlen(name) + 1];
        strcpy(this->name, name);
    }
    void Accomodation::setDaysCount(int daysCount){
        this->daysCount = daysCount;
    }
    
    AirBnB::AirBnB() = default;
  AirBnB::AirBnB(const AirBnB& other){
      copyFrom(other);
  }
  AirBnB& AirBnB::operator=(const AirBnB& other){
      if(this!=&other){
          free();
          copyFrom(other);
      }
      return *this;
  }
  AirBnB::~AirBnB(){
      free();
  }
  
  void AirBnB::addPlace(const Accomodation& other){
      Accomodation* newPlaces = new Accomodation[++count];
      for(int i = 0;i<count-1;i++){
          newPlaces[i] = places[i];
      }
      newPlaces[count-1] = other;
      delete[] places;
      places = newPlaces;
  }
  bool AirBnB::isValidId(size_t id) const{
      for(int i = 0; i < count;i++){
          if(places[i].getId() == id){
              return 1;
          }
      }
      return 0;
  }
  int AirBnB::findIndex(size_t id) const{
      for(int i = 0; i < count;i++){
          if(places[i].getId() == id){
              return i;
          }
      }
      return -1;
  }
  void AirBnB::err(size_t id){
      if(!isValidId(id)){
          throw id;
      }
  }
  void AirBnB::makeReservationById(size_t id, size_t daysCount){
      try {
          err(id);
      }
      catch(size_t id){
          free();
          std::cerr<<"Invalid id!";
      }
        //  if(!isValidId(id)){
        //   throw "INVALID ID";
             
        //  }
         int idx = findIndex(id);
         places[idx].setDaysCount(daysCount);
         places[idx].setIsTaken(true);
         
      }
      
  
  void AirBnB::removeReservationById(size_t id){
      {
          try {
          err(id);
      }
      catch(size_t id){
          free();
          std::cerr<<"Invalid id!";
      }
       
         int idx = findIndex(id);
         places[idx].setIsTaken(false);
         
      }
      
  }
  
  double AirBnB::profit(){
      double profit = 0;
      for(int i = 0;i<count;i++){
          profit += places[i].priceStay();
      }
      return profit;
  }
  double calculateDistance(int x1, int y1, int x2, int y2){
      return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
  }
  Point& AirBnB::closestLocation(Point point){
      int minidx= 0;
      double mindistance = calculateDistance(point.x, point.y, places[0].getLocation().x, places[0].getLocation().y);
      std::cout<<mindistance<<'\n';
      for(int i = 0;i<count;i++){
          double currdistance = calculateDistance(point.x, point.y, places[i].getLocation().x, places[i].getLocation().y);
          if(mindistance > currdistance){
              
              mindistance=currdistance;
              minidx = i;
          }
      }
      return places[minidx].getLocation();
  }
  void AirBnB::removePlace(size_t id){
      try {
          err(id);
      }
      catch(size_t id){
          free();
          std::cerr<<"Invalid id!";
      }
    //   if(!isValidId(id)){
    //       std::cerr<<"INVALID ID";
    //       //throw ("INVALID ID");
             
    //      }
         int idx = findIndex(id);
         Accomodation* newPlaces = new Accomodation[count-1];
         int l = 0;
         for(int i = 0;i<count;i++){
            if(idx == i){
                continue;
            } 
            newPlaces[l++] = places[i];
            
         }
         count--;
         delete[] places;
         places = newPlaces;
  }
  
  

  void AirBnB::copyFrom(const AirBnB& other){
      if(other.places == nullptr || other.count<1){
          return;
      }
      count = other.count;
      places = new Accomodation[count];
      
      for(int i = 0;i<count;i++){
          places[i] = other.places[i];
      }
  }
  void AirBnB::free(){
      delete[] places;
  }
  void AirBnB::print(){
      for(int i = 0;i<count;i++){
          std::cout<<places[i].getId()<<' ';
      }
  }
//zad 3
#pragma once
class Computer{
 int serial_number;
static size_t currentId;
 char* brand = nullptr;
 char* processor = nullptr;
 int video = 0;
 int hard_drive = 0;
 int weight = 0;
 int battery_life = 0;
 double price = 0;
int quantity = 0;

    public:
    Computer(const char* brand,const char* processor,int video,int hard_drive,int weight,int battery_life,double price,int quantity);
    Computer();
    Computer(const Computer& other);
    Computer& operator=(const Computer& other);
    ~Computer();
    size_t getId() const;
    const char* getBrand() const;
    int getWeigth() const;
    int getHardDrive() const;
    int getBatteryLife() const;
    double getPrice() const;
    int getVideo() const;
    const char* getProcessor() const;
    int getQuantity() const;
    
    void setQuantity(int quantity);
    void setBrand(const char* brand);
    void setProcessor(const char* processor);
    
    void printComputer() const;
    
    
    private:
    void free();
    void copyFrom(const Computer& other);

};
size_t Computer::currentId = 0;

#pragma once
class ComputerStore{
   char* name = nullptr;
   Computer* computers = nullptr;
   int size = 0;
   
   public:
   ComputerStore();
   ComputerStore(const char* name);
   ComputerStore(const ComputerStore& other);
   ComputerStore& operator=(const ComputerStore& other);
   ~ComputerStore();
   void addComputer(const Computer& other);
   void print() const;
   void buyComputer(const char* brand, double money, int quantity);
   void printFilter() const;
   
   private:
   void free();
   void copyFrom(const ComputerStore& other);
    
};

#pragma once
class ConsultantUtils{
    public:
  bool static isGoodForGaming(const Computer& other);
  bool static isGoodForTravel(const Computer& other);
  
};


#include <iostream>
#include "Computer.h"
#include "ComputerStore.h"
#include "ConsultantUtils.h"
#include <cstring>

void Computer::setBrand(const char* brand){
    if(brand == nullptr){
        return;
    }
    if(brand == this->brand){
        return;
    }
    delete[] this->brand;
    this->brand = new char[strlen(brand) + 1];
    strcpy(this->brand, brand);

}
    void Computer::setProcessor(const char* processor){
        if(processor == nullptr){
        return;
    }
    if(processor == this->processor){
        return;
    }
    delete[] this->processor;
    this->processor = new char[strlen(processor) + 1];
    strcpy(this->processor, processor);
    }
Computer::Computer(const char* brand,const char* processor,int video,int hard_drive,int weight,int battery_life,double price,int quantity)
{
    setBrand(brand);
    setProcessor(processor);
    this->video=video;
    this->hard_drive = hard_drive;
    this->weight = weight;
    this->battery_life = battery_life;
    this->price = price;
    this->quantity = quantity;
    serial_number = currentId++;
}
    Computer::Computer() : serial_number(currentId++){};
    Computer::Computer(const Computer& other){
        copyFrom(other);
    }
    void Computer::copyFrom(const Computer& other){
    setBrand(other.brand);
    setProcessor(other.processor);
     this->video=other.video;
    this->hard_drive = other.hard_drive;
    this->weight = other.weight;
    this->battery_life = other.battery_life;
    this->price = other.price;
    this->quantity = other.quantity;
    serial_number = currentId++;
    }
    
    Computer& Computer::operator=(const Computer& other){
        
        if(this != &other){
            free();
            copyFrom(other);
        }
        return *this;
    }
    
    Computer::~Computer(){
        free();
    }
    size_t Computer::getId() const{
        return serial_number;
    }
    const char* Computer::getBrand() const{
        return brand;
    }
    int Computer::getVideo() const{
        return video;
    }
    const char* Computer::getProcessor() const{
        return processor;
    }
    int Computer::getWeigth() const{
        return weight;
    }
    int Computer::getHardDrive() const{
        return hard_drive;
    }
    int Computer::getBatteryLife() const{
        return battery_life;
    }
    double Computer::getPrice() const{
        return price;
    }
    int Computer::getQuantity() const{
        return quantity;
    }
    
    void Computer::setQuantity(int quantity){
        this->quantity = quantity;
    }
    
    void Computer::free(){
        delete[] brand;
        delete[] processor;
        brand = nullptr;
        processor = nullptr;
    }
    
    
      ComputerStore::ComputerStore() = default;
      ComputerStore::ComputerStore(const char* name)
      {
      if(name == nullptr){
          return;
      }
      if(name == this->name){
          return;
      }
      this->name = new char[strlen(name) + 1];
      strcpy(this->name, name);
      }
  ComputerStore::ComputerStore(const ComputerStore& other){
      copyFrom(other);
  }
  ComputerStore& ComputerStore::operator=(const ComputerStore& other){
      if(this!=&other){
          free();
          copyFrom(other);
      }
      return *this;
  }
  ComputerStore::~ComputerStore(){
      free();
  }
    void ComputerStore::free(){
        delete[] computers;
        delete[] name;
        name = nullptr;
        computers = nullptr;
    }
    void ComputerStore::copyFrom(const ComputerStore& other){
        if(other.name == nullptr || other.name == name){
            return;
        }
        delete[] name;
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
        if(other.computers == nullptr||computers == other.computers){
            return;
        }
        size = other.size;
        delete[] computers;
        computers = new Computer[size];
        for(int i = 0;i<size;i++){
            computers[i] = other.computers[i];
        }
    }
  void ComputerStore::addComputer(const Computer& other){
      Computer* newcomps = new Computer[size+1];
      for(int i = 0;i<size;i++){
          newcomps[i] = computers[i];
      }
      newcomps[size] = other;
      delete[] computers;
      computers = newcomps;
      size++;
  }
   
  void ComputerStore::print() const{
     
      std::cout<<"Computer store "<<this->name<<" has "<<size<<" computers."<<'\n';
      for(int  i = 0;i<size;i++){
          computers[i].printComputer();
      }
  }
   void ComputerStore::buyComputer(const char* brand, double money, int quantity){
       bool flag = false;
      for(int i = 0;i<size;i++){
          if(strcmp(brand, computers[i].getBrand()) == 0){
              flag = true;
              if(computers[i].getPrice() > money){
                  throw std::logic_error ("Error");
                  std::cerr<<"You cant buy!You dont have the money.";
              }
              else{
                  if(quantity > computers[i].getQuantity()){
                      std::cerr<<"You cant buy this quantity.";
                      computers[i].setQuantity(0);
                  }
                  else{
                  computers[i].setQuantity(computers[i].getQuantity()- quantity);
              }
          }
      }
      }
      if(!flag){
          std::cerr<<"No brand!";
      }
   }
  
  void Computer::printComputer() const{
      std::cout<<brand<<' '<<quantity<<'\n';
  }
  void ComputerStore::printFilter() const{
      std::cout<<"Computers for sale: "<<'\n';
      for(int i = 0;i<size;i++){
          if(computers[i].getQuantity() != 0){
              computers[i].printComputer();
          }
      }
      std::cout<<"Gaming: "<<'\n';
      for(int i = 0;i<size;i++){
          if(ConsultantUtils::isGoodForGaming(computers[i])){
              computers[i].printComputer();
          }
      }
       
      std::cout<<"Travel: "<<'\n';
      for(int i = 0;i<size;i++){
          if(ConsultantUtils::isGoodForTravel(computers[i])){
              computers[i].printComputer();
          }
      }
  }
  bool ConsultantUtils::isGoodForGaming(const Computer& other){
      if(other.getHardDrive() >= 512){
          
          int video = other.getVideo();
          //std::cout<<other.getVideo();
          if(video == 3060 || video == 3070 || video == 3080 || video == 3090){
              
              if(strcmp("i7", other.getProcessor()) == 0 || strcmp("i5", other.getProcessor())){
                  return 1;
              }
              else{
                  return 0;
              }
          }
          else{
             return 0;
          }
     }
      else{
          return 0;
      }
  }
  bool ConsultantUtils::isGoodForTravel(const Computer& other){
      return(other.getWeigth() <= 2.5 && other.getBatteryLife() >= 6);
  }
int main()
{
    //zad 1
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

    //zad 2
     Point p = {1, 2};
    Accomodation a(1, "lili", Type::Villa,p ,23.4,true, 9);
    
    Point p1 = {2, 3};
    Accomodation a1(2, "lili1", Type::Villa,p ,67.4,true, 9);
    
    Point p2 = {1, 8};
    Accomodation a2(3, "lili2", Type::Villa,p ,90.4,true, 9);

AirBnB b;
b.addPlace(a);
b.addPlace(a1);
b.removePlace(90);
b.print();
Point p8 = {0, 0};
std::cout<<b.profit()<<'\n';
Point y1 = b.closestLocation(p8);
b.makeReservationById(1, 9);
std::cout<<y1.x<<' '<<y1.y;

    //zad 3
    Computer c1;
    Computer c2;
    Computer c3("lili", "i7", 3060, 512, 2, 9, 5.7, 6);
    std::cout<<c3.getVideo();
    ComputerStore s("kjskjs");
    //s.addComputer(c3);
   // s.buyComputer("lolo", 1, 90);
    //std::cout<<c3.getBrand();
    c3.setBrand("lolo");
   // std::cout<<c3.getBrand();
    Computer c4 = c3;
    s.addComputer(c3);
    //s.buyComputer("lolo", 90, 1);
    s.printFilter();
   // c4.setBrand("looo");
   // std::cout<<c4.getBrand();
    //std::cout<<c4.getId();
    //c3.printComputer();
   // s.print();
    // std::cout<<c3.getBrand();
    // std::cout<<c1.getId()<<c2.getId();
    // std::cout<<"Hello World";
    return 0;
}

