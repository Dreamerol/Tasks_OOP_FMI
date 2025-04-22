
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
