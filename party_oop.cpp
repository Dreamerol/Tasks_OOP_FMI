
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#pragma warning (disable:4996)

constexpr int MAX_SIZE = 1024 + 1;
constexpr int MAX_COUNT_BALOONS = 1024;
constexpr int MAX_COUNT_CHOCOLATES = 256;
constexpr int MAX_COUNT_DRINKS = 512;


enum class Color {
	White,
	Red,
	Green,
	Default,
};

class Baloon {
	double price;
	Color color;


public:
	Baloon() : price(0), color(Color::Default) {};

	Baloon(double price_, Color color_) {
		setPrice(price_);
		setColor(color_);
	}
	double getPrice() const {
		return price;
	}
	Color getColor() const {
		return color;
	}
	void setColor(Color color) {
		this->color = color;
	}

	void setPrice(double price) {
		if (price < 0) {
			return;
		}
		this->price = price;
	}

};
enum class Flavour {
	Mint,
	Caramel,
	Peanuts,
	Default,
};

bool same_words(const char* str1, const char* str2) {
	while ((*str1) || (*str2)) {
		if ((*str1) != (*str2)) {
			return 0;
		}
		str1++;
		str2++;
	}
	return 1;
}
class Chocolate {
	double price;
	char mark[MAX_SIZE];
	Flavour flavour;

public:

	Chocolate() : price(0), mark(""), flavour(Flavour::Default) {};

	Chocolate(double price_, const char* mark_, Flavour flavour_) {
		setPrice(price_);
		setMark(mark_);
		setFlavour(flavour_);
	}

	double getPrice() const {
		return price;
	}
	const char* getMark() const {
		return mark;
	}
	Flavour getFlavour() const {
		return flavour;
	}
	void setPrice(double price) {
		if (price < 0) {
			this->price = 0;
			return;
		}
		this->price = price;
	}

	void setMark(const char* new_name) {
		//std::cout<<1;
		// std::cout<<new_name<<' ';
		if (new_name == nullptr || strlen(new_name) > MAX_SIZE) {
			return;
		}
		strcpy(this->mark, new_name);

	}

	void setFlavour(Flavour flavour) {
		this->flavour = flavour;
	}
	void read_from_console() {
		std::cout << "Price: ";
		double price_;
		std::cin >> price_;
		setPrice(price_);
		std::cin.ignore();
		std::cout << "Mark: ";
		char buffer[MAX_SIZE];
		std::cin.getline(buffer, MAX_SIZE);
		setMark(buffer);

		std::cout << "Flavour: ";
		char flavour_[MAX_SIZE];
		std::cin.getline(flavour_, MAX_SIZE);

		if (same_words(flavour_, "Caramel")) {
			setFlavour(Flavour::Caramel);
		}
		else if (same_words(flavour_, "Mint")) {
			setFlavour(Flavour::Mint);
		}
		else if (same_words(flavour_, "Peanuts")) {
			setFlavour(Flavour::Peanuts);
		}
		else {
			setFlavour(Flavour::Default);
		}

	}
	void print() {
		std::cout << mark << " has price of " << price << " dollars with flavour of ";
		if (flavour == Flavour::Caramel) {
			std::cout << "caramel";
		}
		else if (flavour == Flavour::Mint) {
			std::cout << "mint";
		}
		else if (flavour == Flavour::Peanuts) {
			std::cout << "peanuts";
		}
		std::cout << '\n';

	}
};
Color color_transformator(char buffer[]) {
	if(same_words(buffer, "white")) {
		return Color::White;
	}
	else if(same_words(buffer, "red")) {
		return Color::Red;
	}
	else if(same_words(buffer, "green")) {
		return Color::Green;
	}
	else {
		return Color::Default;
	}
}
Flavour flavour_transformator(char buffer[]) {
	if(same_words(buffer, "caramel")) {
		return Flavour::Caramel;
	}
	else if(same_words(buffer, "mint")) {
		return Flavour::Mint;
	}
	else if(same_words(buffer, "peanuts")) {
		return Flavour::Peanuts;
	}
	else {
		return Flavour::Default;
	}
}
class Drink {
	double price;
	char name[128];

public:
	Drink() : price(0), name("") {}
	Drink(double price_, const char* name_) {
		setPrice(price_);
		setName(name_);
	}

	void setPrice(double price) {
		if (price < 0) {
			return;
		}
		this->price = price;
	}

	void setName(const char* name) {

		if (name == nullptr || strlen(name) > MAX_SIZE) {

			return;
		}
		strcpy(this->name, name);
	}

	double getPrice() const {
		return price;
	}

	const char* getName() const {
		return name;
	}
};
int lines_count(const char* filename) {
	int count = 0;
	std::ifstream file;
	file.open(filename);
	if(!file.is_open()) {
		return 0;
	}
	while(!file.eof()) {
		char buffer[MAX_SIZE];
		file.getline(buffer, MAX_SIZE);
		count++;
	}
	return count;

}
void add_element(Baloon* baloons, Baloon& element,int baloons_count) {
	Baloon* helper = new Baloon[baloons_count];
	for(int i = 0; i<baloons_count; i++) {
		helper[i] = baloons[i];
	}
	baloons_count++;
	baloons = new Baloon[baloons_count];

	for(int i = 0; i<baloons_count-1; i++) {
		baloons[i] = helper[i];
	}
	baloons[baloons_count-1] = element;
	delete[] helper;
}
class Client{
    char name[MAX_SIZE];
    const char* filename;
  
    
    public:
    Client() : name(""), filename(nullptr)
    {}
    Client(const char* filename) : filename(filename) {}
    // Client(const char* name, const char* filename){
    //     setName(name);
    //     setFilename(filename);
    // }
    const char* getFilename() const{
        return filename;
    }
  
    const char* getName() const{
        return name;
    }
    
    void setName(const char* name){
        if(name == nullptr || strlen(name) > MAX_SIZE){
            return;
        }
        strcpy(this->name, name);
    }
    
};
class Party {
	Baloon* baloons;
	Chocolate* chocolates;
	Drink* drinks;
    Client* clients;
    
	int baloons_count;
	int chocolates_count;
	int drinks_count;
	int clients_count;

    double profit;
public:
	Party() : baloons(nullptr), chocolates(nullptr), drinks(nullptr), clients(nullptr), baloons_count(0), chocolates_count(0), drinks_count(0), clients_count(0) {};
    double getProfit() const{
        return profit;
    }
    void add_client(Client client){
        // if(client == nullptr){
        //     return;
        // }
        
        Client* helper = new Client[clients_count];
        for(int i = 0;i<clients_count;i++){
            helper[i] = clients[i];
        }
        clients = new Client[clients_count+1];
        for(int i = 0;i<clients_count;i++){
            clients[i] = helper[i];
        }
        
        clients[clients_count++] = client;
        
       
        delete[] helper;
        
        
    }
	void create_baloons_list(const char* filename) {
		int lines = lines_count(filename);
		//std::cout<<lines;
		baloons = new Baloon[lines];
		std::ifstream file;
		file.open(filename);
		// file.seekg(0, std::ios::beg);
		if(!file) {
			return;
		}
		for(int i = 0; i<lines; i++) {

			char buffer[MAX_SIZE];
			file.getline(buffer, MAX_SIZE);
			//std::cout<<buffer<<' ';
			std::stringstream ss(buffer);
			char buffer1[MAX_SIZE];
			ss.getline(buffer1, MAX_SIZE, '-');//DELIMITER = '-'
			//std::cout<<buffer1<<' ';
			baloons[i].setColor(color_transformator(buffer1));

			// ss.ignore();
			double price;
			ss >> price;
			//std::cout<<price<<' ';
			baloons[i].setPrice(price);

		}
		//   for(int i=0;i<lines;i++){
		//       std::cout<<baloons[i].getPrice()<<'\n';
		//   }
		baloons_count = lines;
		file.close();
	}

	void add_baloons(const char* filename) {
		int lines = lines_count(filename);
		//std::cout<<lines;
		if(lines+baloons_count > MAX_COUNT_BALOONS){
		    std::cout<<"You cannot add more baloons!";
		    return;
		}
		Baloon* helper = new Baloon[lines+baloons_count];

		for(int i=0; i<baloons_count; i++) {
			helper[i] = baloons[i];
		}
		int len = baloons_count;
		baloons_count = baloons_count + lines;
		baloons = new Baloon[baloons_count];
		for(int i=0; i<baloons_count; i++) {
			baloons[i] = helper[i];
		}
		std::ifstream file;
		file.open(filename);

		if(!file) {
			delete[] helper;
			return;
		}
		for(int i = 0; i<lines; i++) {

			char buffer[MAX_SIZE];
			file.getline(buffer, MAX_SIZE);
			//std::cout<<buffer<<' ';
			std::stringstream ss(buffer);
			char buffer1[MAX_SIZE];
			ss.getline(buffer1, MAX_SIZE, '-');//DELIMITER = '-'
			//std::cout<<buffer1<<' ';
			baloons[i+len].setColor(color_transformator(buffer1));

			// ss.ignore();
			double price;
			ss >> price;
			//std::cout<<price<<' ';
			baloons[i+len].setPrice(price);

		}
		for(int i=0; i<baloons_count; i++) {
			std::cout<<baloons[i].getPrice()<<'\n';
		}
		file.close();
		delete[] helper;
	}
	bool baloon_is_there(Color color) {
		for(int i=0; i<baloons_count; i++) {
			if(baloons[i].getColor() == color) {
				return 1;
			}
		}
		return 0;

	}
	void remove_baloon_by_color(Color color) {
		int count = 0;
		if(baloon_is_there(color)) {
			for(int i = 0; i<baloons_count; i++) {
				if(baloons[i].getColor() == color) {
					count++;
				}
			}
		}
		else {
			return;
		}

		Baloon* helper = new Baloon[baloons_count];

		for(int i = 0; i < baloons_count; i++) {
			helper[i] = baloons[i];
		}

		// baloons_count = baloons_count - count;
		baloons = new Baloon[baloons_count - count];
		int l = 0;
		for(int i=0; i<baloons_count; i++) {
			if(helper[i].getColor() == color) {
				continue;
			}
			baloons[l++] = helper[i];
		}
		delete[] helper;
		baloons_count = baloons_count - count;
		//   for(int i = 0;i<baloons_count;i++){
		//       std::cout<<baloons[i].getPrice()<<' ';
		//   }

	}

	//---------------------------------------------------------------------------
	void create_chocolates_list(const char* filename) {
		int lines = lines_count(filename);

		chocolates = new Chocolate[lines];
		std::ifstream file;
		file.open(filename);

		if(!file) {
			return;
		}
		for(int i = 0; i<lines; i++) {

			char buffer[MAX_SIZE];
			file.getline(buffer, MAX_SIZE);

			std::stringstream ss(buffer);
			char buffer1[MAX_SIZE];
			ss.getline(buffer1, MAX_SIZE, '-');//DELIMITER = '-'

			chocolates[i].setFlavour(flavour_transformator(buffer1));

			ss.getline(buffer1, MAX_SIZE, '-');//DELIMITER = '-'

			chocolates[i].setMark(buffer1);


			double price;
			ss >> price;

			//std::cout<<buffer<<' ';
			chocolates[i].setPrice(price);

		}
		//for(int i=0;i<lines;i++){
		//    std::cout<<chocolates[i].getMark()<<'\n';
		//}
		chocolates_count = lines;
		file.close();
	}

	void add_chocolates(const char* filename) {
		int lines = lines_count(filename);
		if(lines+chocolates_count > MAX_COUNT_CHOCOLATES){
		    std::cout<<"You cannot add more chocolates";
		    return;
		}
		//	std::cout<<lines;
		Chocolate* helper = new Chocolate[chocolates_count];

		for(int i=0; i<chocolates_count; i++) {
			helper[i] = chocolates[i];
		}
		int len = chocolates_count;

		chocolates = new Chocolate[chocolates_count+lines];
		for(int i=0; i<chocolates_count; i++) {
			chocolates[i] = helper[i];
		}
		std::ifstream file;
		file.open(filename);

		if(!file) {
			delete[] helper;
			return;
		}
		for(int i = 0; i<lines; i++) {

			char buffer[MAX_SIZE];
			file.getline(buffer, MAX_SIZE);
			//std::cout<<buffer<<' ';
			std::stringstream ss(buffer);
			char buffer1[MAX_SIZE];
			ss.getline(buffer1, MAX_SIZE, '-');//DELIMITER = '-'
			//std::cout<<buffer1<<' ';
			chocolates[i+len].setFlavour(flavour_transformator(buffer1));

			ss.getline(buffer1, MAX_SIZE, '-');
			chocolates[i+len].setMark(buffer1);
			// ss.ignore();
			double price;
			ss >> price;
			//std::cout<<price<<' ';
			chocolates[i+len].setPrice(price);

		}
		chocolates_count = chocolates_count + lines;
// 		for(int i=0; i<chocolates_count; i++) {
// 			std::cout<<chocolates[i].getPrice()<<'\n';
// 		}
		file.close();
		delete[] helper;
	}
	bool chocolate_is_there(Flavour flavour, const char* mark) {
		for(int i=0; i<chocolates_count; i++) {
			if(chocolates[i].getFlavour() == flavour && same_words(chocolates[i].getMark(), mark)) {
				return 1;
			}
		}
		return 0;

	}
	bool isthere(Flavour flavour, const char* mark, int i) {
	   // std::cout<<mark<<' ';
		return((chocolates[i].getFlavour() == flavour) && (same_words(chocolates[i].getMark(), mark)));
	}
	void remove_chocolate_by_flavour(Flavour flavour, const char* mark) {
		int count = 0;

 		if(chocolate_is_there(flavour, mark)) {
 		   
			for(int i = 0; i<chocolates_count; i++) {
				if(isthere(flavour, mark, i)) {
					count++;
				}
			}
		
		}
		else {
			return;
		}


 		Chocolate* helper = new Chocolate[chocolates_count];

		for(int i = 0; i < chocolates_count; i++) {
			helper[i] = chocolates[i];
		}
        

 		chocolates = new Chocolate[chocolates_count - count];
 	
		int l = 0;
		for(int i=0; i<chocolates_count; i++) {
	
			if(helper[i].getFlavour() == flavour && same_words(helper[i].getMark(), mark)) {
			    
				continue;
			}
			chocolates[l++] = helper[i];
		}
 		delete[] helper;
		chocolates_count = chocolates_count - count;
// 		for(int i = 0;i<chocolates_count;i++){
// 		    std::cout<<chocolates[i].getMark()<<' ';
// 		}


	}
	//--------------------------------------------------
	void create_drinks_list(const char* filename) {
		int lines = lines_count(filename);
		//std::cout<<lines;
		drinks = new Drink[lines];
		std::ifstream file;
		file.open(filename);
		// file.seekg(0, std::ios::beg);
		if(!file) {
			return;
		}
		for(int i = 0; i<lines; i++) {

			char buffer[MAX_SIZE];
			file.getline(buffer, MAX_SIZE);
			//std::cout<<buffer<<' ';
			std::stringstream ss(buffer);
			char buffer1[MAX_SIZE];
			ss.getline(buffer1, MAX_SIZE, '-');//DELIMITER = '-'

			//std::cout<<buffer1<<' ';
			drinks[i].setName(buffer1);


			// ss.ignore();
			double price;
			ss >> price;
			//std::cout<<price<<' ';
			drinks[i].setPrice(price);

		}
		//for(int i=0;i<lines;i++){
		//    std::cout<<drinks[i].getPrice()<<'\n';
		//}
		drinks_count = lines;
		file.close();
	}

	void add_drinks(const char* filename) {
		int lines = lines_count(filename);
		if(lines+drinks_count > MAX_COUNT_DRINKS){
		    std::cout<<"You cannot add more drinks";
		    return;
		}
		
		Drink* helper = new Drink[drinks_count];
		

		for(int i=0; i<drinks_count; i++) {
			helper[i] = drinks[i];
		}
		int len = drinks_count;

		drinks = new Drink[drinks_count+lines];
		for(int i=0; i<drinks_count; i++) {
			drinks[i] = helper[i];
		}
		std::ifstream file;
		file.open(filename);

		if(!file) {
			delete[] helper;
			return;
		}
		for(int i = 0; i<lines; i++) {

			char buffer[MAX_SIZE];
			file.getline(buffer, MAX_SIZE);
			//std::cout<<buffer<<' ';
			std::stringstream ss(buffer);
			char buffer1[MAX_SIZE];
			ss.getline(buffer1, MAX_SIZE, '-');//DELIMITER = '-'
			//std::cout<<buffer1<<' ';
			drinks[i+len].setName(buffer1);

			// ss.ignore();
			double price;
			ss >> price;
			//std::cout<<price<<' ';
			drinks[i+len].setPrice(price);

		}
		drinks_count = drinks_count + lines;
// 		for(int i=0; i<drinks_count; i++) {
// 			std::cout<<drinks[i].getPrice()<<'\n';
// 		}
		file.close();
		delete[] helper;
	}

	bool drink_is_there(const char* name) {
		for(int i=0; i<drinks_count; i++) {
			if(same_words(drinks[i].getName(), name)) {
				return 1;
			}
		}
		return 0;

	}
	void remove_drink_by_name(const char* name) {
		int count = 0;
		if(drink_is_there(name)) {
			for(int i = 0; i<drinks_count; i++) {
				if(same_words(drinks[i].getName(), name)) {
					count++;
				}
			}
		}
		else {
			return;
		}


		Drink* helper = new Drink[drinks_count];

		for(int i = 0; i < drinks_count; i++) {
			helper[i] = drinks[i];
			//std::cout<<drinks[i].getPrice()<<' ';
		}

		// baloons_count = baloons_count - count;
		//	std::cout<<drinks_count<<' ';
		drinks = new Drink[drinks_count - count];
		int l = 0;

		//std::cout<<drinks[0].getName();
		for(int i=0; i<drinks_count; i++) {
			if(same_words(helper[i].getName(), name)) {
				//  std::cout<<i<<'\n';
				continue;
			}
			drinks[l++] = helper[i];
		}
		delete[] helper;

		drinks_count = drinks_count - count;
		for(int  i =0; i<drinks_count; i++) {
			std::cout<<drinks[i].getPrice()<<' ';
		}

	}
	double price_by_name(const char* name) {
		if(name == nullptr) {
			return 0;
		}
		for(int i = 0; i<drinks_count; i++) {

			if(same_words(drinks[i].getName(), name)) {
				return drinks[i].getPrice();
			}
		}
		return 0;
	}
	double price_by_flavour_name(const char* name,  char* flavour) {
		if(name == nullptr||flavour == nullptr) {
			return 0;
		}
		for(int i = 0; i<chocolates_count; i++) {
			if(same_words(chocolates[i].getMark(), name)&&(flavour_transformator(flavour)==chocolates[i].getFlavour())) {
				return chocolates[i].getPrice();
			}
		}
		return 0;
	}
	double price_by_color(char* color) {
		if(color == nullptr) {
			return 0;
		}
		for(int i = 0; i<baloons_count; i++) {
			if(color_transformator(color)==baloons[i].getColor()) {
				return baloons[i].getPrice();
			}
		}
		return 0;
	}

	double get_bill(const char* filename) {
		std::ifstream file;
		bool flag = true;
		file.open(filename);
		if(!file.is_open()) {
			return 0;

		}
// 	for(int i = 0;i<drinks_count;i++){
// 	    std::cout<<drinks[i].getName()<<' ';
// 	}
		char buffer[MAX_SIZE];
		double bill = 0;
		while(!file.eof()) {
			if(flag) {

				file.getline(buffer, MAX_SIZE);

			}
			//std::cout<<buffer<<'\n';
			if(same_words(buffer, "Drinks:")) {

				//   for(int i = 0;i<drinks_count;i++){

				//       std::cout<<drinks[i].getPrice()<<' ';
				//   }
				flag = false;
				while((!same_words(buffer, "Chocolates:")&&(!same_words(buffer, "Baloons:")&&(!file.eof())))) {
					file.getline(buffer, MAX_SIZE);

					std::stringstream ss(buffer);
					char name[MAX_SIZE];
					ss.getline(name, MAX_SIZE, '-');
					int count;
					ss >> count;

					bill += count * price_by_name(name);

				}
			}
			else if((same_words(buffer, "Chocolates:"))) {
				flag = false;

				while((!same_words(buffer, "Drinks:")&&(!same_words(buffer, "Baloons:")&&(!file.eof())))) {
					file.getline(buffer, MAX_SIZE);
					std::stringstream ss(buffer);
					char name[MAX_SIZE];
					ss.getline(name, MAX_SIZE, '-');
					char flavour[MAX_SIZE];
					ss.getline(flavour, MAX_SIZE, '-');
					int count;
					ss >> count;
					bill += count * price_by_flavour_name(name, flavour);

				}
			}
			else if(same_words(buffer, "Baloons:")) {

				flag = false;
				while((!same_words(buffer, "Chocolates:")&&(!same_words(buffer, "Drinks:")&&(!file.eof())))) {
					file.getline(buffer, MAX_SIZE);
					//   	std::cout<<buffer<<'\n';
					std::stringstream ss(buffer);
					char color[MAX_SIZE];
					ss.getline(color, MAX_SIZE, '-');
					int count;
					ss >> count;
					bill += count * price_by_color(color);

				}
			}



		}
		file.close();
		return bill;
	}
    double calculate_profit(){
        for(int i = 0;i<clients_count;i++){
           // std::cout<<clients[i].getFilename()<<' ';
            profit += get_bill(clients[i].getFilename());
        }
        return profit;
    }
    void save_in_binary_file(const char* filename){
        std::ofstream file;
        file.open(filename, std::ios::binary);
        if(!file){
            return;
        }
        file.write((const char*)&clients_count, sizeof(int));
        for(int i=0;i<clients_count;i++){
            file.write((const char*)&clients[i], sizeof(Client));
        }
        file.close();
    }
	~Party() {
		delete[] chocolates;
		delete[] drinks;
		delete[] baloons;
		delete[] clients;
		
		clients = nullptr;
		chocolates = nullptr;
		drinks = nullptr;
		baloons = nullptr;
	}

};


int main()
{
	// Chocolate c;
	// c.setPrice(67);
	// std::cout<<c.getPrice();
	//  d.setName("djhjdgd");
//    std::cout<<d.getName()<<'\n';
	Party p;
	
	p.create_baloons_list("baloons.txt");
 	p.create_drinks_list("drinks.txt");
 	p.create_chocolates_list("chocolates.txt");
// 	p.add_chocolates("chocolates1.txt");
// 	p.remove_chocolate_by_flavour(Flavour::Mint, "lindt");
	//p.add_drinks("drinks1.txt");
	//Drink d;

//	p.remove_drink_by_name("lolo");
	//p.add_baloons("baloons1.txt");
	//p.remove_baloon_by_color(Color::Red);
Client c1("popo.txt");
c1.setName("jisjs");
//std::cout<<c1.getName();
//std::cout<<c1.getFilename();
p.add_client(c1);
 Client c2("balooni.txt");
 c2.setName("skjss");
 p.add_client(c2);
std::cout<<p.calculate_profit();
p.save_in_binary_file("money.dat");
//std::cout<<p.get_bill("popo.txt");
// {
//     Drink d(2.3, "jjjss");
//     //d.setPrice(90);
//     std::cout<<d.getName();=
	// Baloon b(11, Color::Red);
	//std::cout<<b.getPrice();
	//b.setPrice(788);
	// std::cout<<b.getPrice();
	// char b[100];
	//char c[] = "hghaga";
	// strcpy(b, "ffttt");
	//std::cout<<b;
	/* Chocolate c(89, "haaa", Flavour::Caramel);
	 c.print();*/
	/*c.read_from_console();
	std::cout << c.getMark();
	std::cout << c.getPrice();*/
	// c.setMark("siuiush");
	// std::cout<<c.getMark();
	//c.read_from_console();
	// std::cout<<c.getMark();


	return 0;
}
