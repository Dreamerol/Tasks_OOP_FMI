#include <iostream>
#include <cstring>
#pragma warning (disable:4996)

//zad1
constexpr int MAX_SIZE = 1024 + 1;
class Waffle {

    char* mark = nullptr;
    double kilos = 0;
    double price_by_kg = 0;
    double price_client = 0;
    int count_waffles = 0;
public:
    Waffle() : mark(nullptr), kilos(0), price_by_kg(0), price_client(0), count_waffles(0) {};
    Waffle(const char* mark, double kilos, double price_by_kg, double price_client, int count) {
        setMark(mark);
        setKilos(kilos);
        setPriceByKg(price_by_kg);
        setPriceClient(price_client);
        setCount(count);

    }
    void free() {
        if (mark == nullptr) {
            return;
        }
        delete[] mark;
        mark = nullptr;
    }
    void copyFrom(const Waffle& other) {
        mark = new char[strlen(other.getMark()) + 1];
        strcpy(this->mark, other.mark);
        kilos = other.kilos;
        price_by_kg = other.price_by_kg;
        price_client = other.price_client;
        count_waffles = other.count_waffles;
    }


    Waffle& operator = (const Waffle& other) {
        if (this != &other) {
            free();
            copyFrom(other);
        }
        return *this;
    }
    Waffle(const Waffle& other) {
        copyFrom(other);
    };




    double getKilos() const {
        return kilos;
    }
    double getPriceByKg() const {
        return price_by_kg;
    }
    double getPriceClient() const {
        return price_client;
    }
    const char* getMark() const {
        return mark;
    }
    int getWafflesCount() const{
        return count_waffles;
    }
    void setMark(const char* mark) {
        if (mark == nullptr) {
            return;
        }
        if (this->mark == mark) {
            return;
        }
        if (this->mark != nullptr) {
            delete[] this->mark;
        }
        this->mark = new char[strlen(mark) + 1];
        strcpy(this->mark, mark);
    }

    void setKilos(double kilos) {
        if (kilos < 0) {

            return;
        }
        this->kilos = kilos;
    }
    void setPriceByKg(double price_by_kg) {
        if (price_by_kg < 0) {
            return;
        }
        this->price_by_kg = price_by_kg;
    }
    void setPriceClient(double current_profit) {
        if(current_profit < 0){
            return;
        }
        this->price_client = current_profit;
      

    }
    void setCount(int count){
        if(count < 0){
            std::cerr<<"There are no waffles from this mark.";
        }
        count_waffles = count;
    }
    ~Waffle() {
        free();
    }
};
bool same_words(const char* word1, const char* word2){
    if(word1 == nullptr || word2 == nullptr){
        return 0;
    }
    while((*word1) || (*word2)){
        if((*word1) != (*word2)){
            return 0;
        }
        word1++;
        word2++;
    }
    return 1;
}
class Shop {
    Waffle* waffles = nullptr;
    int max_count = 0;
    double profit = 0;
    double expenses = 0;
    int count = 0;

public:



    Shop() = default;
   
    void free() {
        if (this->waffles == nullptr) {
            return;
        }
        delete[] this->waffles;
        this->waffles = nullptr;
    }
    void copyFrom(const Shop& other) {
        this->waffles = new Waffle[other.count];
        for (int i = 0; i < other.count; i++) {
            this->waffles[i] = other.waffles[i];
        }
        this->max_count = other.max_count;
        this->profit = other.profit;
        this->expenses = other.expenses;

    }
    Shop& operator= (const Shop& other) {
        if (this != &other) {
            free();
            copyFrom(other);
        }
        return *this;

    }
    
    void sell_waffle(const char* mark){
     
        for(int i = 0;i<count;i++){
            if(same_words(waffles[i].getMark(), mark)){
                profit += waffles[i].getPriceByKg() * waffles[i].getKilos();
                waffles[i].setCount(waffles[i].getWafflesCount() - 1);
                
            }
        }
        
        
    }
    
     void sell_n_waffles(const char* mark, int n){
     
        for(int i = 0;i<count;i++){
            if(same_words(waffles[i].getMark(), mark)){
                waffles[i].setCount(waffles[i].getWafflesCount() - n);
                double current_profit = waffles[i].getPriceByKg() * waffles[i].getKilos() * n;
                profit += current_profit;
                waffles[i].setPriceClient(waffles[i].getPriceClient() + current_profit);
            
            }
        }
        
    }
    
    int count_of_waffle(const char* mark){
        for(int i = 0;i<count;i++){
            if(same_words(waffles[i].getMark(), mark)){
                
                return waffles[i].getWafflesCount();

            }
        }
    }
    void add_waffle(Waffle waffle){
        Waffle* helper = new Waffle[count];
        for(int i = 0;i<count;i++){
            helper[i] = waffles[i];
        }
        waffles = new Waffle[count+1];
        for(int i = 0;i<count;i++){
            waffles[i] = helper[i];
        }
        waffles[count]=waffle;
        count++;
    }
    double Getprofit() const{
        return profit;
    }
    ~Shop() {
        free();
    }
    void print_waffles(){
        for(int i = 0;i<count;i++){
            std::cout<<waffles[i].getMark()<<' '<<waffles[i].getWafflesCount()<<'\n';
        }
    }

};
int main()
{
    
    Shop s;
    Waffle w("moreni", 10, 2.3, 0, 10);
  //  w.setCount(100);
  //  std::cout<<w.getWafflesCount();
    s.add_waffle(w);
    s.print_waffles();
    s.sell_waffle("moreni");
   std::cout<< s.Getprofit();
 //  std::cout<<s.count_of_waffle("moreni");
    //std::cout << "Hello World!\n";
  //  std::cout<<same_words("kiki", "kiki");
}
