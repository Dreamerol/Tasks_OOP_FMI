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
