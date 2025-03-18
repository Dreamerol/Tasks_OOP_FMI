#include <iostream>
#pragma warning (disable : 4996)
#include <cstring>
#include <fstream>
#include <sstream>
//zad1
constexpr int MAX_AGE = 70;
constexpr int MIN_AGE = 18;
constexpr int LEN = 100;
enum class Subject {
    Default,
    Math,
    BG,
    Geometry,
};
class Teacher {
    char name[LEN]="";
    int age=18;
    double salary=0;
    Subject subject = Subject::Default;

    Teacher() {}
    
    int getAge() const{
        return age;
    }
    void setAge(int value) {
        if (value < MIN_AGE || value > MAX_AGE) {
            return;
        }
        else {
            age = value;
        }
    }
 
    const char* getName() const{
        return name;
    }
    void setName(const char* new_name) {
        if (new_name == nullptr) {
            return;
        }
        if (strlen(new_name) > LEN) {
            return;
        }
        strcpy(name, new_name);
    }
    
    int getSalary() const {
        return salary;
    }
    void setSalary(double value) {
        if (value < 500) {
            return;
        }
        else {
            salary = value;
        }
    }
    

    Subject getSubject(Subject subject) {
        return subject;
    }

    void setSubject(Subject subject) {
        this->subject = subject;
    }

};

//zad2
constexpr int MAX_SIZE = 1024 + 1;
bool points_validator(int points){
    if(points < 0){
        return 0;
    }
    return 1;
}
bool string_validator(char* text){
    if(strlen(text) > MAX_SIZE){
        return 0;
    }
    return 1;
}
class Task{
    char task_description[MAX_SIZE]{'\0'};
    char right_answer;
    int points;
    char password[MAX_SIZE]{'\0'};
    
    public:
    
    Task() = default;
    Task(char text_description[], char right_answer, int points, char password[]){
        
        if(points_validator(points))
        {
        this->points = points;
            
        }
        else{
           this->points = 0; 
        }
        if(string_validator(text_description)){
            strcpy(this->task_description, task_description);
        }
        
        if(string_validator(password)){
            strcpy(this->password, password);
        }
        
        this->right_answer = right_answer;
        
        
    }
    int getPoints() const{
        return points;
    }
    
    char getRightAnswer() const{
        return right_answer;
    }
    
    const char* getTaskDescription() const{
        return task_description;
    }
    bool is_the_same_password(char* word1, char* word2){
        if(word1 == nullptr || word2 == nullptr){
            return 0;
        }
        while((*word1)||(*word2)){
            if((*word1) !=(*word2)){
                return 0;
            }
            word1++;
            word2++;
        }
        return 1;
        
    }
    bool RightPassword(){
       char password[MAX_SIZE];
       std::cout<<"Write password!: ";
       //std::cin.ignore();
       
       std::cin.getline(password, MAX_SIZE);
      
       if(!is_the_same_password(password, this->password)){
           
           return 0;
       }
       
       return 1;
    }
    void setPoints(int points){
        if(points <= 0){
            std::cout<<"Not a valid value for the points!";
            return;
        }
        if(RightPassword()){
        this->points = points;
            
        }
    }
    
    void setPassword(char* new_password){
        if(new_password == nullptr){
            return;
        }
        if(strlen(password) < strlen(new_password)){
            return;
        }
        if(RightPassword()){
        strcpy(password, new_password);
        }
    }
    
    void setTaskDescription(char* new_task_description){
       if(RightPassword()){
       strcpy(task_description, new_task_description);
    }}
    void setRightAnswer(char answer){
        if(RightPassword()){
        right_answer = answer;
    }}
};


class Test{
  Task* tasks=nullptr;
  int number_tasks=0;
  
  public:
  Test(){
      
  };
  Test(int number){
      if(number < 0){
          this->number_tasks = 0;
      }
      this->number_tasks = number;
  }
  int getNumberTasks() const{
      return number_tasks;
  }
  int number_of_tasks(const char* filename){
      std::ifstream file;
      file.open(filename, std::ios::binary);
      if(!file){
          return 0;
      }
      int count = 0;
      Task task;
      while(file.read((char*)&task, sizeof(Task))){
          count++;
      }
      file.close();
      return count;
  }
  void readTasks(const char* filename){
      std::ifstream file;
      file.open(filename, std::ios::binary);
      if(!file){
          return;
      }
      int i = 0;
      this->number_tasks = number_of_tasks(filename);
      
      this->tasks = new Task[number_tasks];
      while(file.read((char*)&tasks[i], sizeof(Task))){
          i++;
      }
      for(int i = 0;i<number_tasks;i++){
          std::cout<<tasks[i].getPoints()<<' ';
      }
      file.close();
      
      
  }
  
  void write_in_binary_file(const char* filename){
      std::ofstream file;
      file.open(filename, std::ios::binary);
      for(int i = 0;i<this->number_tasks;i++){
          file.write((const char*)&this->tasks[i], sizeof(Task));
      }
      file.close();
  }
  int all_points(){
      int points_count = 0;
      for(int i = 0;i<this->number_tasks;i++){
          points_count += tasks[i].getPoints();
      }
      return points_count;
  }
  
  ~Test(){
      delete[] tasks;
  }
};

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
