//zad 2


#include <iostream>
#include <cstring>
#pragma warning (disable:4996)
// Мощност на процесора (число тип double)
// Модел на видео картата (масив от символи)
// Мощност на захранването (цяло число)
// Количество RAM памет (цяло число)
// Методи за промяна на компонентите на компютъра
// Функция, която изписва на стандартния изход какъв тип е компютъра (PC, лаптоп или геймърска конзола)
// Функция, която връща с какви периферни устройства може да се свързва компютъра.

class Computer{
  double powerProcessor=0;
  char* videocard=nullptr;
  int powerBattery=0;
  int RAM=0;
  
  public:
  Computer() = default;
  ~Computer(){
      free();
  }
  Computer(const Computer& other){
      copyFrom(other);
  }
  Computer& operator=(const Computer& other){
      if(this!=&other){
          free();
          copyFrom(other);
      }
      return *this;
  }
  Computer(double powerProcessor,
  const char* videocard,
  int powerBattery,
  int RAM) {
   setRAM(RAM);
   setPowerProcessor(powerProcessor);
   setVideoCard(videocard);
   setPowerBattery(powerBattery);
  }
  
  void setPowerProcessor(double power){
      powerProcessor = power;
  }
  
  void setVideoCard(const char* video){
      if(video == nullptr){
          return;
      }
      if(video == videocard){
          return;
      }
      delete[] videocard;
      videocard = new char[strlen(video)+1];
      strcpy(videocard, video);
  }
  
  void setRAM(int r){
      RAM = r;
  }
  
  void setPowerBattery(int b){
      powerBattery = b;
  }
  
  virtual void printType() const = 0;
  virtual void canConnectWith() const = 0;
  
  private:
  void free(){
      delete[] videocard;
      videocard = nullptr;
  }
  void copyFrom(const Computer& other){
      setPowerBattery(other.powerBattery);
      setRAM(other.RAM);
      setPowerProcessor(other.powerProcessor);
      setVideoCard(other.videocard);
  }
};
class PC : public Computer{
  public:
  PC(double powerProcessor,const char* videocard,int powerBattery,int RAM) : Computer(powerProcessor, videocard, powerBattery, RAM){};
  void printType() const override{
      std::cout<<"PC"<<'\n';
  }  
  void canConnectWith() const override{
      std::cout<<"Mouse, Keyboard, Microphone, Headphones"<<'\n';
  }
};
  class GamingConsole : public Computer{
  public:
  GamingConsole(double powerProcessor,const char* videocard,int powerBattery,int RAM) : Computer(powerProcessor, videocard, powerBattery, RAM){};
  void printType() const override{
      std::cout<<"GamingConsole"<<'\n';
  }  
  void canConnectWith() const override{
      std::cout<<"Screen, Joystick"<<'\n';
  }
  };
  class Laptop : public Computer{
  public:
  Laptop(double powerProcessor,const char* videocard,int powerBattery,int RAM) : Computer(powerProcessor, videocard, powerBattery, RAM){};
  void printType() const override{
      std::cout<<"Laptop"<<'\n';
  }  
  void canConnectWith() const override{
      std::cout<<"Mousepad, Keyboard, Screen"<<'\n';
  }
};

//zad 4


#include <iostream>
const int PENGUIN_POINTS = 50;
const int PACMAN_POINTS = 150;
const int COMPUTER_BOY = 500;
const int SQUIDWARD = 1000;
const int SYLVESTER = 1500;

class Prize {
	double price;
	int points;

public:
	virtual void visualize() const  = 0;
	Prize(double price, int points) {
		this->price = price;
		this->points = points;
	}
	int getPoints() const {
		return points;
	}
	double getPrice() const {
		return price;
	}

};
class Pacman : public Prize {
public:
	Pacman(double price) : Prize(price, PACMAN_POINTS) {};
	void visualize() const override{
		std::cout<<"PACMAN "<<getPoints()<< ' '<<getPrice()<<'\n';
	}
};

class Sylvester : public Prize {
public:
	Sylvester(double price) : Prize(price, SYLVESTER) {};
	void visualize()const override{
		std::cout<<"SYLVESTER "<<getPoints()<< ' '<<getPrice()<<'\n';
	}
};

class Computer_boy : public Prize {
public:
Computer_boy(double price) : Prize(price, COMPUTER_BOY) {};
	void visualize() const override{
		std::cout<<"COMPUTER_BOY "<<getPoints()<< ' '<<getPrice()<<'\n';
	}
};

class Squidward : public Prize {
public:
	Squidward(double price) : Prize(price, SQUIDWARD) {};
	void visualize() const override{
		std::cout<<"SQUIDWARD "<<getPoints()<< ' '<<getPrice()<<'\n';
	}
};
class Penguin : public Prize {
public:
	Penguin(double price) : Prize(price, PENGUIN_POINTS) {};
	void visualize() const override{
		std::cout<<"PENGUIN "<<getPoints()<< ' '<<getPrice()<<'\n';
	}
};
int main()
{
Laptop lap(23, "kjks", 2, 787);
    lap.printType();
    lap.canConnectWith();
  //std::cout<<"Hello World";
	
Penguin p(78);
p.visualize();

	return 0;
}
