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

//zad 3


#include <iostream>
#include <cstring>
#pragma warning (disable:4996)
constexpr int MAX_USERS_COUNT = 20;
constexpr int MAX_PRODUCTS_COUNT = 20;
constexpr int MAX_PRICES_COUNT = 20;
enum class State {
    OK,
    NegativeBalance,
    NegativeQuantity,
    NegativePrice,
    UserFull,
    ProductFull,
    PriceFull,
    UserNotFound,
    ProductNotFound,
    ShortOnMoney,
    NotEnoughItems,
    updateQuantity,
};
class User{
    size_t id;
    char* name;
    double balance;
    public:
    User() : id(0), name(nullptr), balance(0){};
    User(size_t id, const char* name, double balance){
        setID(id);
        setBalance(balance);
        setName(name);
    }
    
    double getBalance() const{
        return balance;
    }
    size_t getID() const{
        return id;
    }
    const char* getName() const{
        return name;
    }
    void setID(size_t id){
        if(id < 1){
            return;
        }
        this->id = id;
    }
    void setBalance(double balance){
        if(balance < 1){
            return;
        }
        this->balance = balance;
    }
    void setName(const char* name){
        if(name ==nullptr){
            return;
        }
        if(this->name == name){
            return;
        }
        if(this->name != nullptr){
            delete[] this->name;
        }
        strcpy(this->name, name);
        
    }
    
    bool hasMoney(double arg){
        return (balance > arg);
    }
    //State
    void copyFrom(const User &other){
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        this->id = other.id;
        this->balance = other.balance;
    }
    void free(){
        if(this->name == nullptr){
            return;
        }
        delete[] this->name;
        this->name = nullptr;
    }
    User(const User& other){
        copyFrom(other);
    }
    User& operator = (const User& other){
        if(this != &other){
            free();
            copyFrom(other);
        }
        return *this;
    }
    ~User(){
        free();
    }
    State factor(){
        if(balance < 0){
            return State::NegativeBalance;
        }
    }
};

class Product{
    char* name;
    size_t ownerId;
    size_t quantity;
    size_t productId;
    public:
    Product() : name(nullptr), ownerId(0), quantity(0), productId(0){};
    Product(const char* name, size_t ownerId, size_t quantity, size_t productId){
        setName(name);
        setOwnerId(ownerId);
        setQuantity(quantity);
        setProductId(productId);
    }
     char* getName() const{
        return name;
    }
    // size_t getProductId() const{
    //     return productId;
    
    Product(const Product& other){
        copyFrom(other);
    }
    Product& operator = (const Product& other){
        if(this !=&other){
            free();
            copyFrom(other);
        }
        return *this;
    }
    size_t getProductId() const{
        return productId;
    }
    size_t getOwnerId() const{
        return ownerId;
    }
    size_t getQuantity() const{
        return quantity;
    }
    State updateQuantity(int amount){
        if(quantity - amount < 0){
            return State::NegativeQuantity;
        }
        quantity -= amount;
    }
    void setOwnerId(size_t ownedId){
        if(ownedId < 1){
            return;
        }
        this->ownerId = ownerId;
    }
    void setQuantity(size_t quantity){
        
        this->quantity = quantity;
    }
    void setProductId(size_t productId){
        if(productId < 1){
            return;
        }
        this->productId = productId;
    }
    void setName(const char* name){
        if(name == nullptr){
            return;
        }
        if(this->name == name){
            return;
        }
        if(this->name != nullptr){
            delete[] this->name;
        }
        strcpy(this->name, name);
        
        
    }
    void copyFrom(const Product& other){
        this->ownerId = other.ownerId;
        this->productId = other.productId;
        this->quantity = other.quantity;
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, name);
    }
    
    void free(){
        if(name == nullptr){
            return;
        }
        delete[] name;
        name =  nullptr;
    }
   
    ~Product(){
        free();
    }

};

class Price{
    size_t productId;
    double price;
    
    public:
    Price() : productId(0), price(0){};
    Price(size_t productId, double price){
        setProductId(productId);
        setPrice(price);
    }
    size_t getId() const{
        return productId;
    }
    double getPrice() const{
        return price;
    }
    void setPrice(double price){
        if(price < 0){
            return;
        }
        this->price = price;
    }
    void setProductId(size_t productId){
        if(productId == 0){
            return;
        }
        this->productId = productId;
    }
    State updatePrice(double amount) {
        if(price + amount < 0){
            return State::NegativePrice;
        }
        price = price + amount;
    }
};
class UsersDatabase{
    User users[MAX_USERS_COUNT];
    size_t size;
    public:
    UsersDatabase() : size(0), users(){};
    size_t getSize() const{
        return size;
    }
    const User* getUsers() const{
        return users;
    }
    State addUser(User user){
        if(size + 1 > MAX_USERS_COUNT){
            return State::UserFull;
        }
        users[size++] = user;
    }
    bool hasEnoughMoney(int id,double money){
        for(int i = 0;i<size;i++){
            if(users[i].getID() == id){
                return (users[i].getBalance() >= money);
                    
                
            }
        }
    }
    bool existUser(int id){
        for(int i = 0;i<size;i++){
            if(users[i].getID() == id){
                return 1;
                    
                }
            }
        
        return 0;
    }
};
class ProductsDatabase{
    Product* products;
    size_t size;
    
    public:
    ProductsDatabase() : size(0), products(nullptr){};
    
    size_t getSize() const{
        return size;
    }
    Product* getProducts() const{
        return products;
    }
    
    State addProduct(const char* name,int id,int prodID,int quantity){
      if(size+1 > MAX_PRODUCTS_COUNT) {
          return State::ProductFull;
      } 
      Product product(name, id, prodID, quantity);
      products[size++] = product;
    } 
    size_t itemsOwned(size_t id,size_t productID){
        for(int i=0;i<size;i++){
            if(products[i].getOwnerId() == id && products[i].getProductId() == productID){
                return products[i].getQuantity();
            }
        }
    } 
    State update(size_t id,size_t productID,size_t quantity_new){
        for(int i=0;i<size;i++){
            if(products[i].getOwnerId() == id && products[i].getProductId() == productID){
                 if(products[i].getQuantity() - quantity_new < 0){
                     return State::NegativeQuantity;
                 }
                 products[i].setQuantity(products[i].getQuantity() - quantity_new);
                 return State::updateQuantity;
            }
        }
    }
    bool existProduct(size_t productID){
        for(int i = 0;i<size;i++){
            if(products[i].getProductId() == productID){
                return 1;
            }
        }
        return 0;
    }
    
};
class PricesDatabase{
    Price* prices;
    size_t size;
    
    public:
    PricesDatabase() : size(0), prices(nullptr){};
    int getSize() const{
        return size;
    }
    
    State addPrice(Price price){
        if(size + 1 > MAX_PRICES_COUNT){
            return State::PriceFull;
        }
        prices[size++] = price;
    }
    double getPrice(int id){
        for(int i = 0;i<size;i++){
            if(prices[i].getId() == id){
                return prices[i].getPrice();
            }
        }
    }
    Price* getPrices() const{
        return prices;
    }
    
};

class SalesSystem{
    UsersDatabase users;
    PricesDatabase prices;
    ProductsDatabase products;
    
    public:
    SalesSystem() : users(), prices(), products(){};
    void addUserinSystem(User user){
        users.addUser(user);
    }
    State addProductInSystem(Product product){
        bool flag = false;
        const User* arr = users.getUsers();
        for(int i = 0;i<users.getSize();i++){
            if(arr[i].getID() == product.getOwnerId()){
                products.addProduct(product.getName(), product.getOwnerId(), product.getProductId(), product.getQuantity());
                flag = true;
            }
        }
        if(!flag){
            return State::UserNotFound;
        }
        
    }
    State addPriceInSystem(Price price){
        bool flag = false;
        Product* arr = products.getProducts();
        for(int i = 0;i<products.getSize();i++){
            if(arr[i].getProductId() == price.getId()){
                prices.addPrice(price);
                flag = true;
            }
        }
        if(!flag){
            return State::ProductNotFound;
        }
        
    }
    bool user_in_database(size_t id){
       const User* arr = users.getUsers();
        for(int i= 0;i<users.getSize();i++){
            if(arr[i].getID() == id){
                return 1;
            }
        }
        return 0;
    }
    double getPriceByProductId(size_t productID){
        for(int i = 0;i<prices.getSize();i++){
            if(prices.getPrices()[i].getId() == productID){
                return prices.getPrices()[i].getPrice();
            }
        }
    }
    Product getProductByProductIdSeller(size_t productID, size_t idFrom){
        for(int i = 0;i<products.getSize();i++){
            if(products.getProducts()[i].getProductId() == productID && products.getProducts()[i].getOwnerId()==idFrom){
                return products.getProducts()[i];
            }
        }
    }
    Product getProductByProductIdClient(size_t productID, size_t idTo){
        for(int i = 0;i<products.getSize();i++){
            if(products.getProducts()[i].getProductId() == productID && products.getProducts()[i].getOwnerId()==idTo){
                return products.getProducts()[i];
            }
        }
    }
    State sell(size_t idFrom, size_t idTo, size_t productID, size_t quantity){
        const Product* arr = products.getProducts();
        bool flag = false;
        for(int i = 0;i<products.getSize();i++){
            if(arr[i].getProductId() == productID){
                flag = true;
            }
        }
        if(!flag){
            return State::ProductNotFound;
        }
        
        Product product_seller = getProductByProductIdSeller(productID, idFrom);
        Product product_client = getProductByProductIdClient(productID, idTo);
       
            
            if(!user_in_database(idFrom)){
                return State::UserNotFound;
            }
            else if(!user_in_database(idTo)){
                return State::UserNotFound;
            }
            else{
                User user_seller = users.getUsers()[idFrom];
                User user_client = users.getUsers()[idTo];
                if(user_client.getBalance() <= 0){
                    return State::ShortOnMoney;
                }
                else if(quantity> product_seller.getQuantity()){
                    return State::NotEnoughItems;
                }
                product_seller.setQuantity(product_seller.getQuantity() - quantity);
                product_client.setQuantity(product_client.getQuantity() + quantity);
                
                user_seller.setBalance(user_seller.getBalance() + quantity * getPriceByProductId(productID));
                user_client.setBalance(user_client.getBalance() - quantity * getPriceByProductId(productID));
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

    double a_0 = 7;
    NumberSeries n(a_0, g);
   // std::cout<<n.i_number(5);
 // n.i_number(10);
    // NumberSeries n(a_0, g);
//  n.print();
  //std::cout<<n.find_lim();
std::cout<<n.number_in_series(10101);
}
