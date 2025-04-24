//zad 1
#pragma once
class String{
  char* str;
  size_t len;
  
  public:
  String();
  String(const String& other);
  String(const char* str);
  String& operator=(const String& other);
  ~String();
  
  char& at(size_t idx);
  size_t getLength() const;
  
  const char* c_str() const;
  void print(std::ostream&) const;
  private:
  void free();
  void copyFrom(const String& other);
    
};
 #pragma once
 class Order{
    char* restaurant;
    size_t count;
    String* products;
    
    public:
    Order();
    const char* getName() const;
    void setName(const char* name);
    Order(const char* restaurant);
    const char* getrestaurantName() const;
//    String* getProducts() const;
    Order& operator=(const Order& other);
    Order(const Order& other);
    ~Order();
    Order& operator=(Order&& other) noexcept;
    Order(Order&& other) noexcept;
    void addProduct(const String& other);
    int calculateTime() const;
    size_t getCount() const;
    String* getProducts() const;
    private:
    void free();
    void copyFrom(const Order& other);
    void moveFrom(Order&& other);
 };
class Restaurant{
  char name[25];
  String* products;
  int size;
  
  public:
  Restaurant();
  Restaurant(int size);
  Restaurant(const Restaurant& other);
  Restaurant& operator=(const Restaurant& other);
  Restaurant(Restaurant&& other) noexcept;
  Restaurant& operator=(Restaurant&& other) noexcept;
  ~Restaurant();
  const char* getRestaurantName() const;
  String* getProducts() const;
  void setName(const char* name);
  void addProduct(const String& product);
  void getDelivery(const Order& other);
  bool isinthere(const String&);
   void printProducts() const;
  
  private:
  void free();
  void copyFrom(const Restaurant& other);
  void moveFrom(Restaurant&& other);
    
};
class Foodpanda{
  Restaurant* restaurants;
  int size;
  
  public:
  Foodpanda(int size);
  Foodpanda();
  Foodpanda& operator=(const Foodpanda& other);
  Foodpanda& operator=(Foodpanda&& other);
  Foodpanda(const Foodpanda& other);
  Foodpanda(Foodpanda&& other);
  ~Foodpanda();
  void addProduct(const char* restaurant_name, const String& other);
  void addRestaurant(const Restaurant& other);
  void addOrder(const char* restaurant_name, const Order& other);
  Restaurant* getRestaurants() const;
  int isinthere(const char* restaurant_name);
  
  private:
  void free();
  void copyFrom(const Foodpanda& other);
  void moveFrom(Foodpanda&& other);
};

#include <cstring>
#pragma warning (disable:4996)
#include <iostream>
#include "String.h"
#include "Order.h"
#include "Restaurant.h"
#include "Foodpanda.h"

 String::String() : str(nullptr), len(0){};
  String::String(const String& other){
      copyFrom(other);
  }
  String& String::operator=(const String& other){
      if(this != &other){
          free();
          copyFrom(other);
      }
      return *this;
  }
  String::~String(){
      free();
  }
  String::String(const char* str){
      if(str == nullptr){
          return;
      }
      if(this->str == str){
          return;
      }
    //   if(this->str != nullptr){
    //       delete[] str;
    //   }
      this->len = strlen(str);
      this->str = new char[strlen(str)+1];
      strcpy(this->str, str);
  }
  char& String::at(size_t idx){
      if(idx>=this->len){
          return this->str[len-1];
      }
      return this->str[idx];
  }
  size_t String::getLength() const{
      return len;
  }
  
  const char* String::c_str() const{
      return str;
  }
  void String::print(std::ostream& os) const{
      os << str;
  }
  
  void String::free(){
      delete[] str;
      str = nullptr;
      len = 0;
  }
  void String::copyFrom(const String& other){
      if(other.str == nullptr || other.str == str){
          return;
      }
      if(str != nullptr){
          delete[] str; 
      }
      len = other.len;
      str = new char[other.len+1];
      strcpy(str, other.str);
  }

//--------------------------------------------------------------------------------------------------------------

//  Order::Order(const char* restaurant){
//      this->restaurant = new char[strlen(restaurant)+1];
//      strcpy(this->restaurant, restaurant);
     
//  }
const char* Order::getName() const{
    return restaurant;
}
String* Order::getProducts() const{
      return products;
  }
void Order::setName(const char* name){
    if(name == nullptr){
        return;
    }
    if(name == this->restaurant){
        return;
    }
    if(this->restaurant != nullptr){
        delete[] this->restaurant;
    }
    this->restaurant = new char[strlen(name)+1];
    strcpy(this->restaurant, name);
}
 Order::Order(): restaurant(nullptr), products(nullptr), count(0){};
     Order& Order::operator=(const Order& other){
         if(this!=&other){
             free();
             copyFrom(other);
         }
         return *this;
     }
     Order::Order(const Order& other){
         copyFrom(other);
     }
     Order::~Order(){
         free();
     }
     void Order::addProduct(const String& other){
         String* newProducts = new String[count+1];
         for(int i = 0;i<count;i++){
             newProducts[i] = products[i];
         }
         newProducts[count++] = other;
         delete[] products;
         products = newProducts;
     }
     int Order::calculateTime() const{
         int timeDelivery = count;
         for(int i = 0;i<count;i++){
             timeDelivery += products[i].getLength();
         }
         return timeDelivery;
     }
     size_t Order::getCount() const{
         return count;
     }    
     Order::Order(Order&& other) noexcept{
         moveFrom(std::move(other));
     }
     Order& Order::operator=(Order&& other) noexcept{
         if(this!=&other){
             free();
             moveFrom(std::move(other));
         }
         return *this;
     }
     void Order::moveFrom(Order&& other){
         restaurant = other.restaurant;
         products = other.products;
         
         other.products = nullptr;
         other.restaurant = nullptr;
         
         count = std::move(other.count);
         other.count = 0;
     }    
     void Order::free(){
         delete[] products;
         delete[] restaurant;
         restaurant = nullptr;
         products = nullptr;
         count = 0;
     }
     void Order::copyFrom(const Order& other){
         count = other.count;
         products = new String[count];
         for(int i = 0;i<count;i++){
             products[i] = other.products[i];
         }
         restaurant = new char[strlen(other.restaurant) + 1];
         strcpy(restaurant, other.restaurant);
     }
     
     
       Restaurant::Restaurant() : name(""), products(nullptr), size(0){};
       void Restaurant::setName(const char* name){
           if(strlen(name) > 25){
               return;
           }
           strcpy(this->name, name);
       }
  Restaurant::Restaurant(int size){
      products = new String[size];
      this->size = size;
  }
  Restaurant::Restaurant(const Restaurant& other){
      copyFrom(other);
  }
  Restaurant& Restaurant::operator=(const Restaurant& other){
      if(this!=&other){
             free();
             copyFrom(other);
         }
         return *this;
  }
  Restaurant::Restaurant(Restaurant&& other) noexcept{
      moveFrom(std::move(other));
  }
  Restaurant& Restaurant::operator=(Restaurant&& other) noexcept{
      if(this!=&other){
             free();
             moveFrom(std::move(other));
         }
         return *this;
  }
  Restaurant::~Restaurant(){
      free();
  }
  void Restaurant::addProduct(const String& product){
      
      String* newProducts = new String[size+1];
         for(int i = 0;i<size;i++){
             newProducts[i] = products[i];
         }
         newProducts[size++] = product;
         delete[] products;
         products = newProducts;
        //  std::cout<<size;
        //  for(int i = 0;i<size;i++){
        //      std::cout<<products[i].c_str()<<' ';
        //  }
     }
  
  bool Restaurant::isinthere(const String& product){
      for(int i = 0;i<size;i++){
          if((strcmp(products[i].c_str(), product.c_str()) == 0) && product.getLength() == products[i].getLength()){
              return 1;
          }
      }
      return 0;
  }
  const char* Restaurant::getRestaurantName() const{
      return name;
  }
  String* Restaurant::getProducts() const{
      return products;
  }
  void Restaurant::getDelivery(const Order& order){
      if(strcmp(order.getName(), name) != 0){
          std::cerr<<"Invalid restaurant!"<<'\n';
      }
      for(int i = 0;i<order.getCount();i++)
      if(!isinthere(order.getProducts()[i])){
          std::cerr<<"Not a valid product!"<<'\n';
      }
  }
  
  
  void Restaurant::free(){
      delete[] products;
      products = nullptr;
  }
  void Restaurant::copyFrom(const Restaurant& other){
      size = other.size;
      if(strlen(other.name) > 25){
          return;
      }
      strcpy(name, other.name);
      products = new String[size];
      for(int i = 0;i<size;i++){
          products[i] = other.products[i];
      }
  }
  void Restaurant::moveFrom(Restaurant&& other){
      products = other.products;
      other.products = nullptr;
      strcpy(name, std::move(other.name));
  }
  void Restaurant::printProducts() const{
      
      for(int i = 0;i<size;i++){
          std::cout<<products[i].c_str()<<'\n';
      }
  }
  
  
  Foodpanda::Foodpanda(int size){
      restaurants = new Restaurant[size];
  }
   Foodpanda::Foodpanda(): restaurants(nullptr), size(0){};
  Foodpanda& Foodpanda::operator=(const Foodpanda& other){
         if(this!=&other){
             free();
             copyFrom(other);
         }
         return *this;
  }
  Foodpanda& Foodpanda::operator=(Foodpanda&& other){
      if(this!=&other){
             free();
             moveFrom(std::move(other));
         }
         return *this;
      
  }
  Foodpanda::Foodpanda(const Foodpanda& other){
      copyFrom(other);
  }
  Foodpanda::Foodpanda(Foodpanda&& other){
      moveFrom(std::move(other));
  }
  Foodpanda::~Foodpanda(){
      free();
  }
  void Foodpanda::addProduct(const char* restaurant_name, const String& other){
      bool flag = false;
      for(int i = 0;i<size;i++){
          if(strcmp(restaurant_name, restaurants[i].getRestaurantName()) == 0){
             
              restaurants[i].addProduct(other);
              flag = true;
          }
      }
      if(!flag){
          free();
          std::cerr<<"Invalid Restaurant name!"<<'\n';
      }
  }
  void Foodpanda::addRestaurant(const Restaurant& other){
      Restaurant* newRestaurants = new Restaurant[size+1];
         for(int i = 0;i<size;i++){
             newRestaurants[i] = restaurants[i];
         }
         newRestaurants[size++] = other;
         delete[] restaurants;
         restaurants = newRestaurants;
     }
  
  
  int Foodpanda::isinthere(const char* restaurant_name){
      for(int i = 0;i<size;i++){
          if(strcmp(restaurants[i].getRestaurantName(),restaurant_name)==0){
              return i;
          }
      }
      return -1;
  }
  void Foodpanda::addOrder(const char* restaurant_name, const Order& other){
      int idx = isinthere(restaurant_name);
      if(idx == -1){
          //throw std::logic_error("Not a valid name!");
          std::cerr<<"Not a valid name!"<<'\n';
          return;
      }
      restaurants[idx].getDelivery(other);
      
  }
  
 
  void Foodpanda::free(){
      delete[] restaurants;
      restaurants = nullptr;
  }
  void Foodpanda::copyFrom(const Foodpanda& other){
      size = other.size;
      restaurants = new Restaurant[size];
      for(int i = 0;i<size;i++){
          restaurants[i] = other.restaurants[i];
      }
  }
  void Foodpanda::moveFrom(Foodpanda&& other){
      restaurants = other.restaurants;
      other.restaurants = nullptr;
      size = std::move(other.size);
      other.size = 0;
  }
  Restaurant* Foodpanda::getRestaurants() const{
      return restaurants;
  }
//zad 2
#pragma once
class Pixel{
  int red=0;
  int green=0;
  int blue=0;
  
  public:
  Pixel();
  void turnNegative();
  void turnBlack();
  void turnWhite();
  void turnGray();
  double sumGrayscale();
  void setRed(int r);
  void setGreen(int g);
  void setBlue(int b);
    int getRed() const;
    int getGreen() const;
    int getBlue() const;
  Pixel(int r, int g, int b);
  void printPixel() const;
  
};

#pragma once
class Picture{
 
  Pixel** pixels=nullptr;
  int height=0;
  int length=0;
  bool isRemoved = false;
  bool isMonochrome=false;
  
  
  public:
  friend void filterPrim(Picture& other,const char* filter);
  bool getIsRemoved() const;
  void setIsMonochrome(bool m);
  Picture(Pixel** pixels, int h, int l);
  void setIsRemoved(bool removed);
  Picture();
  Picture(const Picture& other);
  Picture(Picture&& other) noexcept;
   Picture& operator=(Picture&& other) noexcept;
  Picture& operator=(const Picture& other);
  ~Picture();
  void GrayScale();
  void Negative();
  void Monochrome();
  void printPixels() const;
  
  private:
  void free();
  void copyFrom(const Picture& other);
  void moveFrom(Picture&& other);
};

#pragma once
class Gallery{
    Picture* pictures = nullptr;
    int count = 0;
    
    public:
    Gallery();
    Gallery(const Gallery& other);
    Gallery& operator=(const Gallery& other);
    ~Gallery();
    void addPicture(const Picture& other);
    void removePictureByIdx(int idx);
    void filterByIdx(int idx, const char* filter);
    void filterAllPictures(const char* filter);
    Picture& operator[](int idx);
    void printPictures() const;
    
    
    private:
    void free();
    void copyFrom(const Gallery& other);
    
    
    
};

#include <iostream>
#include "Pixel.h"
#include "Picture.h"
#include "Gallery.h"
#include <cstring>
Pixel::Pixel(int r, int g, int b) {
	this->red = r;
	this->blue = b;
	this->green = g;
}
void Pixel::printPixel() const {
	std::cout<<'('<<red<<", "<<green<<", "<<blue<<')'<<'\n';
}
void Pixel::turnWhite() {
	red = 0;
	green = 0;
	blue = 0;
}
void Pixel::turnBlack() {
	red = 255;
	green = 255;
	blue = 255;
}
void Pixel::turnNegative() {
	red = 255 - red;
	green = 255 - green;
	blue = 255 - blue;
}
void Pixel::setRed(int r) {
    if(r < 0 || r > 255){
        return;
    }
	red = r;
}
void Pixel::setGreen(int g) {
    if(g<0||g>255){
        return;
    }
	green = g;
}
void Pixel::setBlue(int b) {
    if(b<0||b> 255){
        return;
    }
	blue = b;
}
int Pixel::getRed() const {
	return red;
}
Pixel::Pixel() = default;
int Pixel::getGreen() const {
	return green;
}
int Pixel::getBlue() const {
	return blue;
}
void Pixel::turnGray() {
	red *= 0.299;
	green*=0.587;
	blue*=0.114;
}
double Pixel::sumGrayscale() {
	return 0.299*red + 0.587*green+ 0.114*blue;
}
Picture::Picture() = default;
Picture::Picture(const Picture& other) {
	copyFrom(other);
}
Picture::Picture(Picture&& other) noexcept {
	moveFrom(std::move(other));
}
Picture& Picture::operator=(Picture&& other) noexcept {
	if(this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}
Picture& Picture::operator=(const Picture& other) {
	if(this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

Picture::~Picture() {
	free();
}
  void Picture::GrayScale(){
      if(isMonochrome){
          return;
      }
      for(int i = 0;i<height;i++){
          for(int j = 0;j<length;j++){
              pixels[i][j].turnGray();
          }
      }
  }
  void Picture::Negative(){
      for(int i = 0;i<height;i++){
          for(int j = 0;j<length;j++){
              pixels[i][j].turnNegative();
          }
      }
  }
  void Picture::setIsMonochrome(bool m){
      isMonochrome = m;
  }
  void Picture::Monochrome(){
      if(isMonochrome){
          return;
      }
        for(int i = 0;i<height;i++){
          for(int j = 0;j<length;j++){
              if(pixels[i][j].sumGrayscale() <= 128){
                  pixels[i][j].turnWhite();
              }
              else{
                  pixels[i][j].turnBlack();
              }

          }
      }
      setIsMonochrome(true);
  }
  Picture::Picture(Pixel** p, int h, int l){
      height = h;
      length = l;
      pixels = p;
  }
  void Picture::printPixels() const{
      for(int i = 0;i<height;i++){
          for(int j = 0;j<length;j++){
              pixels[i][j].printPixel();
          }
      }
  }

void Picture::free() {
	for(int i=0; i<height; i++) {
		delete[] pixels[i];
	}
	delete[] pixels;
	pixels = nullptr;
}
void Picture::copyFrom(const Picture& other) {
	height = other.height;
	length = other.length;
	pixels = new Pixel*[height];
	for(int i = 0; i<height; i++) {
		pixels[i] = new Pixel[length];
	}
	for(int i = 0; i<height; i++) {
		for(int j = 0; j<length; j++) {
			pixels[i][j] = other.pixels[i][j];
		}
	}
}
void Picture::moveFrom(Picture&& other) {
	height = (std::move(other.height));
	length = (std::move(other.length));
	pixels = other.pixels;

	other.pixels = nullptr;
}
bool Picture::getIsRemoved() const{
    return isRemoved;
}

 Gallery::Gallery() = default;
Gallery::Gallery(const Gallery& other){
    copyFrom(other);
}
Gallery& Gallery::operator=(const Gallery& other){
    if(this != &other){
        free();
        copyFrom(other);
    }
    return *this;
}
Gallery::~Gallery(){
    free();
}
void Gallery::addPicture(const Picture& other){
    Picture* newpictures = new Picture[count+1];
    for(int i = 0;i<count;i++){
        newpictures[i] = pictures[i];
    }
    newpictures[count++] = other;
    delete[] pictures;
    pictures = newpictures;
}
void Gallery::removePictureByIdx(int idx){
    if(idx < 0 || idx >= count){
        std::cerr<<"Invalid idx!";
    }

    pictures[idx].setIsRemoved(true);


}
void Picture::setIsRemoved(bool removed){
    isRemoved = removed;
}
void filterPrim(Picture& other,const char* filter){
    if(strcmp(filter, "GrayScale") == 0){
        other.GrayScale();
    }
    else if(strcmp(filter, "Monochrome")==0){
        other.Monochrome();
    }
    else if(strcmp(filter, "Negative")==0){
        other.Negative();
    }
}
void Gallery::filterByIdx(int idx, const char* filter){
    if(0 > idx || idx >= count){
        std::cerr<<"Invalid idx!";
    }
    if(pictures[idx].getIsRemoved()){
        std::cerr<<"This picture is not in our gallery!";
    }
    filterPrim(pictures[idx], filter);
}
void Gallery::filterAllPictures(const char* filter){
    for(int i = 0;i<count;i++){
        if(!pictures[i].getIsRemoved()){
        filterPrim(pictures[i], filter);
	}
    }
}
Picture& Gallery::operator[](int idx){
    if(idx<0||idx>count){
        std::cerr<<"Invalid idx!";
    }
    if(pictures[idx].getIsRemoved()){
        std::cerr<<"This painting is no longer in our gallery!";
    }
    
    return pictures[idx];
}
void Gallery::printPictures() const{
    for(int i = 0;i<count;i++){
        if(!pictures[i].getIsRemoved()){
        pictures[i].printPixels();}
    }
}

void Gallery::free(){
    delete[] pictures;
    pictures = nullptr;
}
void Gallery::copyFrom(const Gallery& other){
    count = other.count;
    pictures = new Picture[count];
    for(int i = 0;i<count;i++){
        pictures[i] = other.pictures[i];
    }
}
int main()
{
	//zad 1
         String str("jhzzz");
  
    Order order;
    order.setName("koko");
    //std::cout<<order.getName();
    String s1("jddd");
    order.addProduct(s1);
    String s2("ishsh");
    //std::cout<<order.calculateTime();
    order.addProduct(s2);
    Restaurant r;
    r.addProduct(s2);
    r.setName("koko");
   // std::cout<<r.getRestaurantName();
    //std::cout<<order.getName();
    r.addProduct(s1);
    
    
    //r.getDelivery(order);
    //std::cout<<str.at(2);
  //  std::cout<<"Hello World";
//r.printProducts();
Foodpanda f;

f.addRestaurant(r);
String s3("lolol");
order.addProduct(s3);
f.addProduct("koko", s3);
//f.addProduct("jddd", s3);
f.addOrder("koko", order);
//f.getRestaurants()[0].printProducts();
	
	//zad 2
	Pixel p(1, 2, 3);
	Pixel p1(22, 33, 44);
	Pixel p2(1, 2, 3);
	Pixel p3(222, 233, 144);
	
	Pixel** lol = new Pixel*[2];
	for(int i = 0;i<2;i++){
	    lol[i] = new Pixel[2];
	}
	lol[0][0] = p;
	lol[0][1] = p1;
	lol[1][0] = p2;
	lol[1][1] = p3;
	Picture pic(lol, 2, 2);
	Picture pic2(lol, 2, 2);
	Gallery gal;
	gal.addPicture(pic);
	gal.addPicture(pic2);
	gal.filterAllPictures("Monochrome");
	//gal.removePictureByIdx(1);
//gal.filterByIdx(0, "Monochrome");
	gal.printPictures();
	//	pic.Monochrome();
		pic.GrayScale();
//	pic.printPixels();
//Picture w = gal[0];
//w.printPixels();
//	p.turnGray();
	//p.printPixel();
	//std::cout<<"Hello World";



	return 0;
}
