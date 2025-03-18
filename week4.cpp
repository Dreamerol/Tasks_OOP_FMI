#include <iostream>
#pragma warning (disable : 4996)
#include <cstring>
#include <fstream>
#include <sstream>
//zad3
constexpr int MAX_SIZE = 64;
constexpr int MAX_LEN = 1024 + 1;
constexpr char DELIMITER = '\n';
constexpr int MAX_GAMES_COUNT = 50;
bool is_Cheaper(double price1, double price2){
    return(price1 > price2);
}
bool is_more_Expensive(double price1, double price2){
    return(price1 < price2);
}

bool are_the_same(const char* word1, const char* word2){
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
class Game{
   char title[MAX_SIZE]{'\0'};
   double price = 0;
   bool isAvailable = false;
   
   
   public: 
   Game(){};
   
   
   Game(double price){
       this->price = price;
   };
   
   
   //converting constructor
   Game(char title[]){
       if(title == nullptr||strlen(title) > MAX_SIZE){
            return;
       }
       
        strcpy(this->title, title);
   };
   
   Game(double price, char title[], bool isAvailable){
    //   this->price= price;
    //   strcpy(this->title, title);
    //   this->isAvailable = isAvailable;
    setPrice(price);
    setTitle(title);
    setIsAvailable(isAvailable);
   };
   
   
   double getPrice() const{
       return price;
   }
   
   const char* getTitle() const{
       return title;
   }
   
   bool getIsAvailable() const{
       return isAvailable;
   }
   
   void setPrice(double price){
       if(price < 0){
           this->price = 0;
       }
       this->price = price;
   }
   
   void setTitle(char title[]){
       if(title == nullptr || strlen(title)> MAX_SIZE){
           return;
       }
       strcpy(this->title, title);
   }
   void setIsAvailable(bool isAvailable){
       this->isAvailable = isAvailable;
   }
   
   bool isFree(){
       return (this->price == 0);
   }
   
   void print(){
       std::cout<<"The game "<<title<<" is "<<price<<" dollars and ";
       if(isAvailable){
           std::cout<<"is available!";
       }
       else{
           std::cout<<"is not available!";
       }
       std::cout<<'\n';
   }
//   Game(double price){
//       this->price = price;
//   }
};

void swap_games(Game& g1, Game& g2){
    Game h= g1;
    g1= g2;
    g2= h;
}
void SelectionSort(int n,bool (*predicate)(double, double), Game* games){
    for(int i =0;i<n-1;i++){
        int min_idx = i;
        for(int j=i+1;j<n;j++){
            if(predicate(games[i].getPrice(), games[j].getPrice())){
                min_idx = j;
            }
        }
        if(min_idx != i){
            swap_games(games[i], games[min_idx]);
        }
    }
}
class GamePlatform{
    Game* games;
    int games_count = 0;
   // const char* filename;
    
    GamePlatform(int games_count){
        this->games_count;
    }
    
    public:
    
    GamePlatform(const char* filename){
        read_from_file(filename);
    }
    void setGamesCount(int games_count){
        if(games_count < 0){
            return;
        }
        this->games_count = games_count;
    }
    int getGamesCount() const{
        return games_count;
    }
    
    // void addGame(Game& game){
    //     if(game == nullptr){
    //         return;
    //     }
    //     if()
    // }
    
    void print_games(){
        for(int i = 0;i<games_count;i++){
            games[i].print();
        }
    }
    void print_game_by_idx(int idx){
        if(idx < 0 || idx > games_count- 1){
            return;
        }
        games[idx].print();
    }
    
    void print_cheapest_or_most_expensive(bool (*predicate)(double, double)){
        SelectionSort(games_count, predicate, games);
        games[0].print();
    }
    
    void print_free_games(){
        SelectionSort(games_count, is_Cheaper, games);
        int i = 0;
        while(games[i].getPrice() == 0){
            games[i++].print();
        }
    }
    
    void save_in_file(const char* filename){
        std::ofstream file;
        file.open(filename);
        
        if(!file.is_open()){
            return;
        }
        
        for(int i = 0;i<games_count;i++){
         
            file << games[i].getTitle()<<" "<<games[i].getPrice()<<" "<<games[i].getIsAvailable()<<'\n';
       
       
        }
        file.close();
    }
    
    void read_from_file(const char* filename){
        std::ifstream file;
        file.open(filename);
        
        if(!file.is_open()){
            return;
        }
        int count = 0;
        while(!file.eof()){
            char buffer[MAX_LEN];
            file.getline(buffer, MAX_LEN, DELIMITER);
            count++;
        }
        games = new Game[count];
        games_count = count;
        file.seekg(0, std::ios::beg);
        int i = 0;
        while(!file.eof()){
            char buffer[MAX_LEN];
            file.getline(buffer, MAX_LEN, DELIMITER);
            std::stringstream ss(buffer);
            char title_[MAX_LEN];
            ss >> title_;
            double price;
            ss >> price;
            bool isAvailable;
            ss >> isAvailable;
            
            games[i].setTitle(title_);
            games[i].setPrice(price);
            games[i].setIsAvailable(isAvailable);
            
            i++;
        }
        
        file.close();
    
        for(int i = 0;i<games_count;i++){
            games[i].print();
        }
        
    }
    
    void add_game(Game& game){
        if(games_count == MAX_GAMES_COUNT){
            std::cout<<"No space!";
            return;
        };
        Game* games_helper = new Game[games_count];
        for(int i = 0;i<games_count;i++){
            games_helper[i] = games[i];
        }
        games_count++;
        games = new Game[games_count];
        
        for(int i = 0;i<games_count-1;i++){
            games[i] = games_helper[i];
        }
        games[games_count-1] = game;
        delete[] games_helper;
    }
    
    void delete_game(Game& game){
        int idx = 0;
        for(int i = 0;i<games_count;i++){
            if(game.getPrice() == games[i].getPrice() && game.getIsAvailable() == games[i].getIsAvailable() && are_the_same(game.getTitle(), games[i].getTitle())){
                idx = i;
                //std::cout<<idx;
            }
        }
        
        int l = 0;
        
        Game* games_helper = new Game[games_count];
        for(int i = 0;i<games_count;i++){
            games_helper[i] = games[i];
        }
        
      //  games_count--;
        games = new Game[games_count-1];
        
        for(int i=0;i<games_count;i++){
            if(i == idx){
                i++;
                continue;
            }
            games[l] = games_helper[i];
            l++;
        }
        games_count--;
        delete[] games_helper;
    }
    
    
    ~GamePlatform(){
        delete[] games;
    }
    
};
int main(){
    
    GamePlatform gamep("games.txt");
  
    Game g(12, "snkjs", 0);
    gamep.add_game(g);
      gamep.save_in_file("games1.txt");
      gamep.delete_game(g);
      gamep.save_in_file("games2.txt");
      
  //  Game g(12, "snkjs", 0);
    //std::cout<<g.getTitle();
    //gamep.print_free_games();
    //gamep.print_cheapest_or_most_expensive(is_more_Expensive);
    // gamep.print_game_by_idx(0);
    // Game game(0.0, "hajaa", 0);
     //std::cout<<game.isFree();
     
     //game.print();
//     Game game1("sbhs");
//   std::cout<< game.getPrice();
//   std::cout<<game1.getTitle();
    return 0;
}
