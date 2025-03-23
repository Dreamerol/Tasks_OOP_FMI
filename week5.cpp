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

//zad 2

constexpr double EPSILON = 1e-10;
double abs(double num){
    if(num < 0){
        return -num;
    }
    else{
        return num;
    }
}
class NumberSeries{
    double a_0=0;
    double(*predicate)(double)=nullptr;
    double* nums=nullptr;
    int count=1;
    
    public:

    NumberSeries():a_0(0), predicate(nullptr), nums(nullptr), count(0){};
    NumberSeries(double a_0,double(*predicate)(double)){
        this->a_0=a_0;
        this->predicate=predicate;
        this->nums = new double[1];
        nums[0] = a_0;
        this->count = 1;
    }
    
    
    void copyFrom(const NumberSeries& other){
        this->a_0 =other.a_0;
        this->predicate = other.predicate;
        if(this->nums != nullptr){
            delete[] this->nums;
        }
        this->nums = new double[other.count];
        for(int i=0;i<other.count;i++){
            this->nums[i] = other.nums[i];
        }
        this->count = other.count;
    }
    NumberSeries(const NumberSeries& other){
        copyFrom(other);
    }
    NumberSeries& operator=(const NumberSeries& other){
        if(this != &other){
            free();
            copyFrom(other);
        }
        return *this;
    }
    void free(){
        if(nums == nullptr){
            return;
        }
        this->predicate = nullptr;
        this->count = 0;
        this->nums = nullptr;
        delete[] nums;
    }
    
    ~NumberSeries(){
        free();
    }
    int getCount() const{
        return count;
    }
    double getA_0() const{
        return a_0;
    }
    void setA_0(double a_0){
        this->a_0 = a_0;
    }
    void setPredicate(double(*predicate)(double)){
        this->predicate = predicate;
    }
    
    
    double i_number(int i){
        if(i <=count){
            return nums[i];
        } 
        double* helper = new double[count];
        for(int i = 0;i<count;i++){
            helper[i] = nums[i];
        }
        delete[] nums;
        nums = new double[i+1];
        for(int i = 0;i<count;i++){
            nums[i] = helper[i];
        }
        delete[] helper;
        double a_helper = nums[count-1];
        double num=0;
        for(int j = 0;j<i;j++){
             num = predicate(a_helper);
            a_helper = num;
            nums[j+count] = num;
            
        }
        count = i+1;
        return num;
    }
    bool isDecreasing(){
        for(int  i = 0;i<count-1;i++){
            if(nums[i] < nums[i+1]){
                return 0;
            }
        }
        return 1;
    }
    bool isIncreasing(){
        
     for(int i = 0;i<count-1;i++){
            if(nums[i] > nums[i+1]){
                return 0;
            }
        }
        return 1;
    }
    double find_lim(){
    double a_helper = nums[count-1];
       double lim = 0;
        while(true){
        lim = predicate(a_helper);
       
            if(abs(a_helper-lim)<EPSILON){
                return lim;
            }
            a_helper = lim;
        }
        
    }
    bool number_in_series(double number){
        if(number > a_0 && isDecreasing()){
            return 0;
        }
        else if(number < find_lim() && isDecreasing()){
            return 0;
        }
        else if(number < a_0 && isIncreasing()){
            return 0;
        }
        else if(number > find_lim() && isIncreasing()){
            return 0;
        }
        for(int i = 0;i<count;i++){
            if(abs(nums[i] - number)<EPSILON){
                return 1;
            }
        }
        double a_helper = nums[count-1];
        while(true){
            double num = predicate(a_helper);
            a_helper = num;
            if(abs(num - number)<EPSILON){
                return 1;
            }
        }
        return 0;
    }
    void print(){
        for(int i = 0;i<count;i++){
            std::cout<<nums[i]<<' ';
        }
    }
    
};
double g(double a){
    return a/2 + 1;
}


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

    double a_0 = 7;
    NumberSeries n(a_0, g);
   // std::cout<<n.i_number(5);
 // n.i_number(10);
    // NumberSeries n(a_0, g);
//  n.print();
  //std::cout<<n.find_lim();
std::cout<<n.number_in_series(10101);
}
