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
Penguin p(78);
p.visualize();

	return 0;
}
