#include <iostream>
#include <fstream>

//zad 1
int* create_array(int n) {
    int* ar = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> ar[i];
    }
    return ar;
}
void write_in_file(filename, int* ar, int n){
std::ofstream file(filename, std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        return -1;
    }
    file.write((const char*)&n, sizeof(int));
    file.write((const char*) ar, sizeof(int) * n);
    delete[] a;
    file.close();

}
void read(filename, int n){
    int* b = new int[n];

    std::ifstream file1(filename, std::ios::in | std::ios::binary);
    if (!file1.is_open()) {
        return -1;
    }
    file1.read((char*)&n, sizeof(int));
    file1.read((char*)b, sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        std::cout << b[i]<< ' ';
    }

    file1.close();

    delete[] b;
}
//zad 2
struct StudentС{
    int id;
    char name[50];
    double grade;
    
};
StudentС create_student(){
    StudentС student;
    std::cout<<"Student ID: ";
    std::cin>>student.id;
    std::cout<<"Student name: ";
    std::cin.ignore();
    std::cin.getline(student.name, 50);
    
    std::cout<<"Student's grade: ";
    std::cin>>student.grade;
    return student;
}
bool unique_student_id(StudentС* students, int& len, int id){
    for(int i = 0;i<len;i++){
        if(students[i].id == id){
            return 0;
        }
    }
    return 1;
}
StudentС* students_data(int N){
    
    StudentС* students = new StudentС[N];
    int len = 0;
    for(int i = 0;i<N;i++){
        StudentС current_student = create_student();
        students[i] = current_student;

        //checks if the student's id is already in the list
        if(unique_student_id(students, len, current_student.id)){
         students[len++] = current_student;
            
        }
    }
    for(int i = 0;i<len;i++){
        std::cout<<students[i].name<<' ';
    }
    return students;
    
}
void write_students_in_binaryfile(const char* filename, int N){
    std::ofstream file(filename, std::ios::binary);
    if(!file){
        std::cerr<<"Cannot create a file!";
        return;
    }
    
    StudentС* students = students_data(N);
    for(int i = 0;i<N;i++){
        file.write((char*)&students[i], sizeof(StudentС));
    }
    file.close();
    
}

void read_students_in_binaryfile(const char* filename, int N){
    std::ifstream file(filename, std::ios::binary);
    if(!file){
        std::cerr<<"Cannot create a file!";
        return;
    }
    
    StudentС* students = new StudentС[N];
    for(int i = 0;i<N;i++){
        file.read((char*)&students[i], sizeof(StudentС));
        std::cout<<students[i].name<<'\n';
    }
    file.close();
    
}
void swap_students(StudentС& a, StudentС& b){
    StudentС h = a;
    a = b;
    b = h;
}
double const EPSILON = 1e-9;
bool is_bigger_grade(double a, double b){
    if((a - b) > EPSILON){
        return 1;
    }
    return 0;
}
bool is_smaller_grade(double a, double b){
    if((b - a) > EPSILON){
        return 1;
    }
    return 0;
}
void sortbygrade(StudentС* students, bool(*predicate) (double,double), int N){
    for(int i = 0;i<N-1;i++){
        int minidx = i;
        for(int j = i+1;j<N;j++){
            if(predicate(students[i].grade, students[j].grade)){
                minidx = j;
            }
        }
        if(minidx != i){
            swap_students(students[i], students[minidx]);
        }
        
    }
    for(int i = 0;i<N;i++){
        std::cout<<students[i].name<<'\n';
    }
}
bool bigger_id(int a, int b){
    if( a>b){
        return 1;
    }
    return 0;
}
void sortbygrade(StudentС* students, bool(*predicate) (int,int), int N){
    for(int i = 0;i<N-1;i++){
        int minidx = i;
        for(int j = i+1;j<N;j++){
            if(predicate(students[i].id, students[j].id)){
                minidx = j;
            }
        }
        if(minidx != i){
            swap_students(students[i], students[minidx]);
        }
        
    }
    for(int i = 0;i<N;i++){
        std::cout<<students[i].name<<'\n';
    }
}
void free_matrix(StudentС* students){
    delete[] students;
    
}

//zad 3
enum class Pizza_type 
{
	Margarita,
	Kalcone,
	Vurata,
};
enum class Pizza_size {
	S,
	L,
	M,
};

struct Pizza {

	Pizza_type pizza_type;
	Pizza_size pizza_size;
	double price;
};
struct Delivery {
	char name[50];
	char tel_number[20];
	char address[100];
	double price;
	int number_pizzas;
	

};
Pizza create_pizza() {
	Pizza pizza;
	std::cout<<"Type of pizza: ";
	int pizza_type;
	std::cin>> pizza_type;
	pizza.pizza_type = Pizza_type(pizza_type);

	std::cout<<"Size: ";
	int pizza_size;
	std::cin>>pizza_size;
	pizza.pizza_size = Pizza_size(pizza_size);
	
	std::cout<<"Price: ";
	std::cin>>pizza.price;
	return pizza;

}
Delivery create_delivery(int N) {
	Delivery delivery;
	std::cout<<"Name: ";
	std::cin.ignore();
	std::cin.getline(delivery.name, 50);

	std::cout<<"Tel number: ";
	std::cin.ignore();
	std::cin.getline(delivery.tel_number, 20);

	std::cout<<"Address: ";
	std::cin.ignore();
	std::cin.getline(delivery.address, 100);

	delivery.number_pizzas = N;
	Pizza* pizzas = new Pizza[N];

	for(int i = 0; i<N; i++) {
		Pizza p = create_pizza();
		pizzas[i] = p;
	}
	double price = 0;
	for(int i = 0; i<N; i++) {
		
		price += pizzas[i].price;
	}
	delivery.price = price;
	return delivery;

}
int closer_address(char* a, char* b){
    if(a == nullptr || b == nullptr){
        return 0;
    }
    while((*a) == (*b)){
        a++;
        b++;
    }
    return (*a) - (*b);
    
}
void delivery_swap(Delivery& A, Delivery& B) {
	Delivery H = A;
	A = B;
	B = H;
}
void sortbyaddress(Delivery* deliveries, int n) {
	for(int i = 0; i<n-1; i++) {
		int minidx = i;
		for(int j = i+1; j<n; j++) {
			if(closer_address(deliveries[i].address, deliveries[j].address) > 0){
			    minidx = j;
			}
		}
		if(i != minidx){
		    delivery_swap(deliveries[i], deliveries[minidx]);
		}
}
    for(int i = 0;i<n;i++){
        std::cout<<deliveries[i].address<<' '<<deliveries[i].tel_number<<'\n';
    }
}
void write_in_file(std::ofstream& file, int M){
    file.open("pizza.bin",std::ios::out |std::ios::binary);
    if(!file.is_open()){
        return;
    }
    Delivery* deliveries = new Delivery[M];
    for(int i = 0;i<M;i++){
    int N;
	std::cout<<"Number of pizzas: ";
	std::cin>>N;
	 deliveries[i] = create_delivery(N);
    }
    
    sortbyaddress(deliveries, M);
    file.write((const char*)deliveries, M * sizeof(Delivery));
    file.close();
}
void read_from_file(std::ifstream& file, int M){
    file.open("pizza.bin", std::ios::in | std::ios::binary);
    if(!file.is_open()){
        return;
    }
    Delivery* deliveries = new Delivery[M];
    file.read((char*)deliveries, M * sizeof(Delivery));
    for(int i = 0;i<M;i++){
        std::cout<<deliveries[i].name<<'\n';
    }
    file.close();
}
//zad 4
struct Record{
  uint64_t next;
  char user_data[504];
};
void print_record(Record r){
    std::cout<<r.next<<' '<<r.user_data<<'\n';
}
void print(const char* filename){
    
    std::ifstream file(filename, std::ios::in|std::ios::binary);
    if(!file){
        return;
    }
    
    file.seekg(0, std::ios::end);//from the end of the file -  positions moved
    
    size_t filesize = file.tellg();
    file.seekg(0, std::ios::beg);
    
    
    size_t NumRecords = filesize / sizeof(Record);
 
    int curr_idx = 0;
    while(true){
        Record current;
        file.seekg(curr_idx * sizeof(Record), std::ios::beg);
        file.read((char*)&current, sizeof(Record));
        std::cout<<current.next<<' ';
        if(current.next == 0){
            break;
        }
        print_record(current);
        curr_idx = current.next;
    }
    
    
}
