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
int main()
{
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
}
