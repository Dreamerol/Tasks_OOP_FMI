//zad 1
#pragma once

class String
{
	char* str;
	size_t len;

public:
	String(const char*);

	String();
	String(const String&);
	String& operator=(const String&);
	~String();

	char& at(size_t);
	size_t getLength() const;
	const char* c_str() const;

	void print(std::ostream&) const;

private:
	void copyFrom(const String&);
	void free();
};

std::ostream& operator<<(std::ostream& os, const String& rhs);

#pragma once

class Ticket{
String name;
double price=0;

public:
Ticket() = default;
  Ticket(String name, double price);
  void setPrice(double price);
  void setName(String name);
  void print() const;
  String getName() const;
};
#pragma once
class StudentTicket : public Ticket{
    public:
    StudentTicket() = default;;
  StudentTicket(String name, double price);
  
    
};
#pragma once

class GroupTicket : public Ticket{
    public:
  GroupTicket(String name, double price);
  
    
};
#include <iostream>

#pragma warning(disable:4996)

#include "String.h"
#include <cstring>
#include "Ticket.h"
#include "StudentTicket.h"
#include "GroupTicket.h"



String::String(const char* str) : str(nullptr), len(0)
{
if (str == nullptr)
{
str = "";
}
this->len = strlen(str);
this->str = new char[this->len + 1];
strcpy(this->str, str);

}

String::String() : String("") {}

String::String(const String& other)
{
copyFrom(other);
}

String& String::operator=(const String& other)
{
if (this != &other)
{
free();
copyFrom(other);
}

return *this;
}

String::~String()
{
free();
}

char& String::at(size_t index)
{
// TODO: Fix this
if (index >= this->len)
{
return this->str[len - 1];
}

return this->str[index];
}

size_t String::getLength() const
{
return this->len;
}

void String::copyFrom(const String& other)
{
    this->len = other.len;
this->str = new char[other.len + 1];
strcpy(this->str, other.str);
}

void String::free()
{
delete[] str;
str = nullptr;
len = 0;
}

const char* String::c_str() const
{
return str;
}

void String::print(std::ostream& out) const
{
out << str;
}

std::ostream& operator<<(std::ostream& os, const String& rhs)
{
	os << rhs.c_str();
	return os;
}

    Ticket::Ticket(String name, double price) {
        this->price = price;
        this->name = name;
    }
    void Ticket::setPrice(double price) {
        this->price = price;
    }
   /* double getPrice() const {
        return price;
    }*/

    void Ticket::print() const{
        std::cout <<"Name: "<< name << '\n'<<"Price: "<< price << '\n';
    }

    String Ticket::getName() const{
        return name;
    }
    void Ticket::setName(String name){
        this->name = name;
    }
    StudentTicket::StudentTicket(String name, double price) : Ticket(name, price)
    {
         setPrice(price / 2);
        // setName(name);
       
    }

// class GroupTicket: public Ticket {
    GroupTicket::GroupTicket(String name, double price) : Ticket(name, price){
        setPrice(0.8 * price);
    }
// };
//zad 2
#pragma once
class Carpart{
  
  size_t id=0;
  static int currentId;
  char* description=nullptr;
  char* name=nullptr;
  
  public:
  const char* getName() const;
  const char* getDescription() const;
  size_t getId() const;
  
  void setName(const char* name);
  void setDescription(const char* description);
  
  virtual void print(std::ostream& os) const = 0;
  Carpart();
  Carpart(const char* name, const char* description);
  virtual ~Carpart();
  Carpart(const Carpart& other);
  Carpart& operator=(const Carpart& other);
  
  private:
  void free();
  void copyFrom(const Carpart& other);
};

int Carpart::currentId = 1;
std::ostream& operator<<(std::ostream& os, const Carpart& other);

#pragma once
class Tire : public Carpart{
    int width=0;
    int profile=0;
    int diameter=0;
    
    public:
    Tire();
    Tire(const char* name,const char* description, int width, int profile, int diameter);
    void setWidth(int w);
    void setProfile(int p);
    void setDiameter(int d);
    virtual void print(std::ostream& os) const override;
};

#pragma once
class Engine : public Carpart{
  size_t horsepower=0;
  public:
  
  void setHP(int hp);
  Engine(const char* name, const char* desc, size_t hp);
  virtual void print(std::ostream& os) const override;
  
  
};

#pragma once
class Battery : public Carpart{
  size_t capacity=0;
  char* batteryId=nullptr;
  
  public:
  Battery();
  Battery(const char* name, const char* desc, size_t cap, const char* id);
  void setId(const char* id);
  Battery(const Battery& other);
  Battery& operator=(const Battery& other);
  ~Battery();
  virtual void print(std::ostream& os) const override;
  private:
  void free();
  void copyFrom(const Battery& other);
};

#pragma once
class insufficient_fuel_error : public std::logic_error{
    public:
    explicit insufficient_fuel_error(const char* msg);
    
};
class FuelTank{
    double amount;
    double capacity;
    
    public:
    double getAmount() const;
    FuelTank(double capacity);
    void useFuel(double amount);
    void fillFuel(double amount);
    
    
};
#pragma once
const double RACE_DISTANCE = 0.4;
class Car{

FuelTank tank;
Engine engine;
Tire tires[4];
Battery battery;
double distance;
double weight;

public:
void setTires(Tire* tires);
Car(
Engine& engine,
Tire* tires,
Battery& Battery,
double distance,
double weight, double capacity);

const FuelTank& getFT() const;
void drive(double km);
double getDistance() const;
};

Car* dragRace(Car* car1, Car* car2);



#include <iostream>
#include "CarPart.h"
#include "Tire.h"
#include "Engine.h"
#include "Battery.h"
#include "FuelTank.h"
#include "Car.h"
#include <fstream>
#include <cstring>

 const char* Carpart::getName() const{
    return name;
};
  const char* Carpart::getDescription() const{
      return description;
  }
  size_t Carpart::getId() const{
      return id;
  }
  
  void Carpart::setName(const char* name){
      if(name == nullptr){
          return;
      }
      if(name == this->name){
          return;
      }
      if(this->name != nullptr){
          delete[] this->name;
      }
      this->name = new char[strlen(name) + 1];
      strcpy(this->name, name);
  }
  void Carpart::setDescription(const char* description){
      if(description == nullptr){
          return;
      }
      if(description == this->description){
          return;
      }
      if(this->description != nullptr){
          delete[] this->description;
      }
      this->description = new char[strlen(description) + 1];
      strcpy(this->description, description);
  }
  
  Carpart::Carpart() = default;
  Carpart::Carpart(const char* name, const char* description){
      id = currentId++;
      setName(name);
      setDescription(description);
  }
  Carpart::~Carpart(){
      free();
  }
  Carpart::Carpart(const Carpart& other){
      copyFrom(other);
  }
  Carpart& Carpart::operator=(const Carpart& other){
      if(this!=&other){
          free();
          copyFrom(other);
      }
      return *this;
  }
  
  
  void Carpart::free(){
      delete[] name;
      delete[] description;
      name = nullptr;
      description = nullptr;
  }
  void Carpart::copyFrom(const Carpart& other){
      setName(other.name);
      setDescription(other.description);
      id = other.id;
  }
  
std::ostream& operator<<(std::ostream& os, const Carpart& other){
    other.print(os);
    return os;
}

Tire::Tire(const char* name,const char* description, int width, int profile, int diameter): Carpart(name, description) {
    setWidth(width);
    setProfile(profile);
    setDiameter(diameter);
};
    void Tire::setWidth(int w){
        if(w < 155||w > 365){
            return;
        }
        width = w;
    }
    void Tire::setProfile(int p){
        if(p<30 || p > 80){
            return;
        }
        profile = p;
    }
    void Tire::setDiameter(int d){
        if(d < 13 || d > 21){
            return;
        }
        diameter = d;
    }
    void Tire::print(std::ostream& os) const{
        os<<getId()<<" by " <<getName()<< '-'<<getDescription()<<'-'<< width<<'/'<<profile<<'R'<<diameter<<'\n';
    }
    
    void Engine::setHP(int hp){
        if(hp < 0){
            return;
        }
        horsepower = hp;
    }
  Engine::Engine(const char* name, const char* desc, size_t hp):Carpart(name, desc){
      setHP(hp);
  }
   void Engine::print(std::ostream& os) const{
    os << getId()<< " by " <<getName()<< "-" <<getDescription()<<"-" <<horsepower<< " hp"<<'\n'; 
   }
   
    Battery::Battery() = default;
  Battery::Battery(const char* name, const char* desc, size_t cap, const char* id): Carpart(name, desc){
      setId(id);
      capacity = cap;
  }
  void Battery::setId(const char* id){
      if(id == nullptr){
          return;
      }
      if(id == batteryId){
          return;
      }
      free();
      batteryId = new char[strlen(id) + 1];
      strcpy(batteryId, id);
  }
  Battery::Battery(const Battery& other) : Carpart(other){
      copyFrom(other);
  }
  Battery& Battery::operator=(const Battery& other){
      if(this!=&other){
          Carpart::operator=(other);
          free();
          copyFrom(other);
      }
      return *this;
  }
  Battery::~Battery(){
      free();
  }
   void Battery::print(std::ostream& os) const{
       os << getId()<< " by" <<getName()<< "-" <<getDescription()<< "–" << capacity <<"Ah"<<'\n';
   }
 
  void Battery::free(){
      delete[] this->batteryId;
      batteryId = nullptr;
  }
  void Battery::copyFrom(const Battery& other){ 
      
      capacity = other.capacity;
      if(batteryId != nullptr){
          free();
      }
      batteryId = new char[strlen(other.batteryId)+1];
      strcpy(batteryId, other.batteryId);
  }
  
    insufficient_fuel_error::insufficient_fuel_error(const char* msg) : std::logic_error(msg){};
    
    FuelTank::FuelTank(double capacity) : capacity(capacity), amount(capacity){};
    void FuelTank::useFuel(double amount){
        if(amount > this->amount){
            throw insufficient_fuel_error("Not enough fuel!");
        }
        this->amount -= amount;
    }
    void FuelTank::fillFuel(double amount){
        if(amount + this->amount > this->capacity){
            this->amount = this->capacity;
        }
        else{
        this->amount += amount;
        }
    }
Tire::Tire() = default;

// Car::Car(Engine& engine, Tire* tires, Battery& battery, double distance, double weight, double tankCapacity)
//     : engine(engine), battery(battery), distance(distance), weight(weight), tank(tankCapacity) {
//     // Set the tires array by copying the provided tires into the car's tires array
//     for (int i = 0; i < 4; ++i) {
//         this->tires[i] = tires[i];
//     }
// }
Car::Car(
Engine& engine,Tire* tires,Battery& battery,double distance,double weight, double capacity) :  
engine(engine), battery(battery), 
distance(distance), 
weight(weight), tank(capacity)
{
    //std::cout<<'l';
   // setTires(tires);
    if(tires == nullptr){
        return;
    }
    if(this->tires == tires){
        return;
    }

    for(int i = 0;i<4;i++){
        this->tires[i] = tires[i];
    }
}
// void Car::setTires(Tire* tires){
   
// }
const FuelTank& Car::getFT() const{
    return tank;
}
void Car::drive(double km){
    try{
    this->tank.useFuel(km);
      this->distance += km;  
    }
    catch(const insufficient_fuel_error& e){
        std::cerr<<e.what()<<'\n';
    }
}

 double FuelTank::getAmount() const{
     return amount;
 }
bool notEnoughFuelForRace(Car* car){
    return(car->getFT().getAmount() < RACE_DISTANCE);
}

Car* dragRace(Car* car1, Car* car2){
    if(notEnoughFuelForRace(car1) && notEnoughFuelForRace(car2)){
        return nullptr;
    }
    else if(notEnoughFuelForRace(car2)){
        return car1;
    }
    else if(notEnoughFuelForRace(car1)){
        return car2;
    }
    else{
        if(car1->getFT().getAmount() > car2->getFT().getAmount()){
            return car1;
        }
        else{
            return car2;
        }
    }
}
double Car::getDistance() const{
    return distance;
}


//zad 3
#pragma once

class String
{
	char* str;
	size_t len;

public:
	String(const char*);

	String();
	String(const String&);
	String& operator=(const String&);
	~String();

	char& at(size_t);
	size_t getLength() const;
	const char* c_str() const;

	void print(std::ostream&) const;

private:
	void copyFrom(const String&);
	void free();
};

std::ostream& operator<<(std::ostream& os, const String& rhs);
bool operator<(const String& rhs,const String& lhs);
bool operator>(const String& rhs,const String& lhs);

#pragma once
enum class SortByAttribute{
    Fn,
    Name,
    Course
};
class Student{
   String name;
   unsigned fn=0;
   unsigned course=0;
   public:
   Student();
   Student(String name, unsigned fn, unsigned course);
   const String& getName() const;
unsigned getFn() const;
unsigned getCourse() const;
};
#pragma once
class StudentDB{
  Student* students=nullptr;
  int count=0;
  int capacity=8;
  public:
  StudentDB();
  void setStudents(Student* students);
  explicit StudentDB(int capacity);
  StudentDB(Student* students, int count);
  ~StudentDB();
  int getCount() const;
  Student* getStudents() const;
  int getCapacity() const;
  void setCount(int);
  //void setStudents(Student* students);
  StudentDB& operator=(const StudentDB& other);
  StudentDB(const StudentDB& other);
  void add(const Student& student);
  void remove(unsigned fn);
  Student* find(unsigned fn);
  void display() const;
  bool isInDatabase(unsigned fn) const;
  int findIdx(unsigned fn) const;
  private:
  void copyFrom(const StudentDB& other);
  void free();
  void resize();
};
#pragma once
class SortedStudentDB: public StudentDB{
    public:
    SortedStudentDB(Student* students, int count);
    SortedStudentDB(const StudentDB& other);
    void sortBy(SortByAttribute atr);
};

#pragma once
class FilteredStudentDB: public StudentDB{
    public:
    FilteredStudentDB(Student* students, int count);
    FilteredStudentDB(const StudentDB& other);
    void filter(bool (*func)(Student&));
    void limit(int N);
};



#include <iostream>
#include <cstring>
#include "String.h"
#include "Student.h"
#include "StudentDB.h"
#include "SortedStudentDB.h"
#include "FilteredStudentDB.h"

String::String(const char* str) : str(nullptr), len(0)
{
if (str == nullptr)
{
str = "";
}
this->len = strlen(str);
this->str = new char[this->len + 1];
strcpy(this->str, str);

}

String::String() : String("") {}

String::String(const String& other)
{
copyFrom(other);
}

String& String::operator=(const String& other)
{
if (this != &other)
{
free();
copyFrom(other);
}

return *this;
}

String::~String()
{
free();
}
bool operator>(const String& lhs,const String& rhs){
    return(strcmp(lhs.c_str(), rhs.c_str()) > 0);
}
bool operator<(const String& lhs,const String& rhs){
    return(strcmp(lhs.c_str(), rhs.c_str()) < 0);
}
char& String::at(size_t index)
{
// TODO: Fix this
if (index >= this->len)
{
return this->str[len - 1];
}

return this->str[index];
}

size_t String::getLength() const
{
return this->len;
}

void String::copyFrom(const String& other)
{
    this->len = other.len;
this->str = new char[other.len + 1];
strcpy(this->str, other.str);
}

void String::free()
{
delete[] str;
str = nullptr;
len = 0;
}

const char* String::c_str() const
{
return str;
}

void String::print(std::ostream& out) const
{
out << str;
}

std::ostream& operator<<(std::ostream& os, const String& rhs)
{
	os << rhs.c_str();
	return os;
}

Student::Student() = default; //gets the default constructor of String
Student::Student(String name, unsigned fn, unsigned course){
    this->name = name;
    this->fn = fn;
    this->course = course;
}
const String& Student::getName() const{
    return name;
}
unsigned Student::getFn() const{
    return fn;
}
unsigned Student::getCourse() const{
    return course;
}
StudentDB::StudentDB(Student* students, int count){
  setCount(count);
  setStudents(students);
}
void StudentDB::setCount(int count){
    this->count = count;
}
 void StudentDB::setStudents(Student* students){
    if(students == nullptr){
        return;
    }
    if(this->students == students){
        return;
    }
    free();
    this->students = new Student[count];
    for(int i = 0;i<count;i++){
        this->students[i] = students[i];
    }
}

 StudentDB::StudentDB() : StudentDB(10){};
  StudentDB::~StudentDB(){
      free();
  }
  StudentDB& StudentDB::operator=(const StudentDB& other){
      if(this != &other){
          free();
          copyFrom(other);
      }
      return *this;
  }
  StudentDB::StudentDB(const StudentDB& other){
      copyFrom(other);
  }
  void StudentDB::add(const Student& student){
      if(count == capacity){
          resize();
      }
      students[count++] = student;

  }
  int StudentDB::findIdx(unsigned fn) const{
      for(int i = 0;i<count;i++){
          if(students[i].getFn() == fn){
              return i;
          }
      }
      return -1;
  }
   void error(bool el){
      if(!el){
          throw std::logic_error("It is not there!");
      }
  }
  void StudentDB::remove(unsigned fn){
      try{
          error(isInDatabase(fn));
      }
      catch(std::logic_error& e){
          std::cerr<<e.what()<<'\n';
      }
      catch(std::exception& e){
          std::cerr<<e.what()<<'\n';
      }
      catch(...){
          std::cout<<"Unknown exception!";
      }
      
      int idx = findIdx(fn);
      int l = 0;
      Student* newStudents = new Student[capacity];
      for(int i =0;i<count;i++){
          if(idx == i){
              continue;
          }
          newStudents[l++] = students[i];
      }
      count--;
      delete[] students;
      students = newStudents;
  }
  bool StudentDB::isInDatabase(unsigned fn) const{
      for(int i = 0;i<count;i++){
          if(fn == students[i].getFn()){
              return 1;
          }
      }
      return 0;
  }
 
  Student* StudentDB::find(unsigned fn){
      try{
          error(isInDatabase(fn));
      }
      catch(std::logic_error& e){
          delete[] students;
          std::cerr<<e.what()<<'\n';
      }
      catch(std::exception& e){
          std::cerr<<e.what()<<'\n';
      }
      catch(...){
          std::cout<<"Unknown exception!";
      }
      
      for(int i = 0;i<count;i++){
          if(fn == students[i].getFn()){
              return &students[i];
          }
      }
      return nullptr;
  }
  void StudentDB::display() const{
      for(int i = 0;i<count;i++){
          std::cout<<students[i].getName()<<' '<<students[i].getFn()<<' '<<students[i].getCourse()<<'\n';
      }
  }
  
   StudentDB::StudentDB(int capacity){
      students = new Student[capacity];
      this->capacity = capacity;
  }
  void StudentDB::copyFrom(const StudentDB& other){
      this->count = other.count;
      students = new Student[count];
      for(int i = 0;i<count;i++){
          students[i] = other.students[i];
      }
  }
  void StudentDB::free(){
      delete[] students;
      students = nullptr;
  }
  void StudentDB::resize(){
      Student* newStudents = new Student[this->capacity*2];
      this->capacity *= 2;
      for(int i = 0;i<count;i++){
          newStudents[i] = students[i];
      }
     delete[] students;
     students = newStudents;
  }
    int StudentDB::getCount() const{
        return count;
    }
  Student* StudentDB::getStudents() const{
      return students;
  }
  void swap(Student& a, Student& b){
      Student help = a;
      a = b;
      b = help;
  }
  int getAtrInteger(SortByAttribute atr, Student& student){
      if(atr==SortByAttribute::Fn){
          return student.getFn();
      }
      else if(atr==SortByAttribute::Course){
    
          return student.getCourse();
      }
      else{
          return -1;
      }
  }
  
  SortedStudentDB::SortedStudentDB(Student* students, int count) : StudentDB(students, count){};
  SortedStudentDB::SortedStudentDB(const StudentDB& other) : StudentDB(other){};
  void SortedStudentDB::sortBy(SortByAttribute atr){
      bool condition;
      for(int i = 0;i<getCount()-1;i++){
          int minidx = i;
          for(int j = i+1;j<getCount();j++){
              if(atr == SortByAttribute::Name){
                  condition = (getStudents()[j].getName() < getStudents()[minidx].getName());
              }
              else{
                  condition = getAtrInteger(atr, getStudents()[j]) < getAtrInteger(atr, getStudents()[minidx]);
              }
              if(condition){
                  minidx = j;
              
                  
            }
          }
          if(minidx != i){
              swap(getStudents()[i], getStudents()[minidx]);
              
          }
      }
  }
int  StudentDB::getCapacity() const{
      return capacity;
  }
//  void StudentDB::setStudents(Student* students){
//       thu=is->students = students;
//   }
FilteredStudentDB::FilteredStudentDB(Student* students, int count) : StudentDB(students, count){};
FilteredStudentDB::FilteredStudentDB(const StudentDB& other):StudentDB(other){};
    void FilteredStudentDB::filter(bool (*func)(Student&)){
        int l=0;
        Student* newStudents = new Student[getCapacity()];
        for(int i = 0;i<getCount();i++){
            if(func(getStudents()[i])){
                newStudents[l++]=getStudents()[i];
            }
        }
        setStudents(newStudents);
        setCount(l);
    };
void FilteredStudentDB::limit(int N){
        Student* newStudents = new Student[getCapacity()];
        for(int i = 0;i<N;i++){
            newStudents[i] = getStudents()[i];
        }
        
        setStudents(newStudents);
        setCount(N);
    }
bool greaterThan(Student& other){
    return(other.getCourse() > 1);
}
int main()
{
  //zad 1

    String s("jksjs");
    String s2("jaa");
    s = s2;
   //Ticket t(s, 12);
   Ticket t;
   //t.setName(s);
   StudentTicket sd;
   String s1("klkl");
   StudentTicket t2(s1, 23);
   std::cout<<t2.getName().c_str();
   
  // t2.print();
//zad 2
	    Tire tires[4] = {
        Tire("BrandA", "All-season", 200, 55, 16),
        Tire("BrandA", "All-season", 200, 55, 16),
        Tire("BrandA", "All-season", 200, 55, 16),
        Tire("BrandA", "All-season", 200, 55, 16)
    };

    Engine engine("V8", "Turbo", 500);
    Battery battery("Bosch", "12V", 80, "B123");


std::cout << std::endl;

    Car car(engine, tires, battery, 0, 1500, 100); 
    Car car1(engine, tires, battery, 0, 1500, 7); // 100L tank
std::cout << std::endl;

    std::cout << "Fuel before drive: "<<car.getFT().getAmount()<<'\n';
    std::cout << "Distance before drive: " << car.getDistance() << '\n';

    car.drive(8);  // Use 10L

    std::cout << "Fuel after drive: " << car.getFT().getAmount() << '\n';
    std::cout << "Distance after drive: " << car.getDistance() << '\n';
    Car* c1 = &car;
    Car* c2 = &car1;
 Car* winner = dragRace(c1,c2);
 std::cout<<winner->getFT().getAmount();

//zad 3
	  String s1("ksjss");
    String r2("hhh");
    String r3("aaa");
   Student s(s1, 1, 1111);
      Student s2(r2, 233, 1);
         Student s3(r3, 3, 222);
   //std::cout<<s.getName();
    StudentDB school;
    school.add(s);
    school.add(s2);
    school.add(s3);
   // Student* s2 = school.find(1);
  //  std::cout<<s2->getName();
    //school.remove(1);
    //school.display();
    SortedStudentDB school1(school);
    FilteredStudentDB school2(school);
    school1.sortBy(SortByAttribute::Name);
    //school1.display();
    school2.limit(2);
   // school2.filter(greaterThan);
    school2.display();
    return 0;
}
