#include <iostream>
#include <cstring>
constexpr int MAX_LEN = 30;
class Student {
    char* name=nullptr;//big4
    int* grades=nullptr;//big4
    int gradesCount=0;
    char moto[MAX_LEN]=" ";

public:
    Student() = default;

    Student(const char* name, const int* grades, int gradesCount, const char* moto) {
        setName(name);
        setGrades(grades);
        setGradesCount(gradesCount);
        setMoto(moto);
       
    }
    void setName(const char* name) {
        if (name == nullptr) {
            return;
        }
        if (this->name != nullptr) {
            delete[] this->name;
        }
        if (this->name == name) {
            return;
        }
        //za zadelena pamet
        int len = strlen(name);
        this->name = new char[len + 1];
        strcpy(this->name, name);


    }
    void setGrades(const int* grades) {
        if (grades == nullptr) {
            return;
        }
        delete[] this->grades;
        this->grades = nullptr;

        this->grades = new int[gradesCount];
        this->gradesCount = gradesCount;

        for (int i = 0; i < this->gradesCount; i++) {
            this->grades[i] = grades[i];
        }
    }
    void setMoto(const char* name) {
        if (strlen(moto) > 31) {
            return;
        }
        strcpy(this->moto, moto);
    }
    void setGradesCount(int gradesCount) {
        this->gradesCount = gradesCount;
    }
    void free_Name() {
        if (this->name == nullptr) {
            return;
        }
        delete[] this->name;
        this->name = nullptr;
    }
    void free_Grades() {
        if (this->grades == nullptr) {
            return;
        }
        delete[] this->grades;
        this->grades = nullptr;
    }
    void free() {
        free_Name();
        free_Grades();
    }
    int getGradesCount() const{
        return gradesCount;
    }
    const char* getName() const {
        return name;
    }
    int* getGrades() const {
        return grades;
    }
    const char* getMoto() const {
        return moto;
    }
    Student(const Student& other) {
        copyFrom(other);
    }
    Student& operator = (const Student& other) {
        if (this != &other) {
            free();
            copyFrom(other);
        }
        return *this;
    }

    void copyFrom(const Student& other) {
        setName(other.name);
        setGrades(other.grades);
        setGradesCount(other.gradesCount);
        setMoto(other.moto);
    }
    void write_in_binary_file(const char* filename){
        std::ofstream file(filename, std::ios::binary);
        if(!file){
            return;
        }
        int len = strlen(this->name);
        file.write((const char*)&len, sizeof(int));
        file.write((const char*)&this->name, sizeof(char) * len);
        // for(int i = 0;i<len;i++){
        //     file.write((const char*)&this->name[i], sizeof(char));
        // }
        file.write((const char*)&this->gradesCount, sizeof(int));
        file.write((const char*)&this->grades, sizeof(int) * this->gradesCount);
        
        file.write((const char*)&this->moto, MAX_LEN);
        
        file.close();
    }
    
    Student& read_from_binary_file(const char* filename){
        std::ifstream file(filename, std::ios::binary);
        if(!file){
            return;
        }
        Student student;
        int len;
        file.read((char*)&len, sizeof(int));
        const char* name;
        file.read((char*)&name, sizeof(char) * len);
        student.setName(name);
        // for(int i = 0;i<len;i++){
        //     file.write((const char*)&this->name[i], sizeof(char));
        // }
        int count;
        file.read((char*)&count, sizeof(int));
        int* grades;
        file.read((char*)&grades, sizeof(int) * this->gradesCount);
        student.setGrades(grades);
        student.setGradesCount(count);
        
        const char* moto;
        file.read((char*)&moto, MAX_LEN);
        
        student.setMoto(moto);
        
        file.close();
        return student;
    }
};
class School{
    Student* students=nullptr;
    int count=0;
    
    School() = default();
    School(Student* students, int count){
        setCount(count);
        setStudents(students);
    }
    School(const &School other){
        copyFrom(other);
    }
    void setCount(int count){
        if(count < 0){
            return;
        }
        this->count = count;
    }
    void setStudents(Student* students){
        if(students == nullptr){
            return;
        }
        if(this->students == students){
            return;
        }
        if(this->students != nullptr){
            delete[] students;
            students = nullptr;
        }
        students = new Student[this->count];
        for(int i = 0;i<count;i++){
            this->students[i] = students[i];
        }
        
    }
    School& operator = (const School& other){
        if(this != &other){
            free();
            copyFrom(other);
        }
        return *this;
    }
    
    ~School(){
        free();
    }
    void write_in_binary_file_school(const char* filename){
        std::ofstream file(filename, std::ios::binary);
        if(!file){
            return;
        }
        file.write((const char*)&count, sizeof(int));
        
        for(int i = 0;i<count;i++){
            students[i].write_in_binary_file(filename);
        }
        
        file.close();
    }
    void read_in_binary_file_school(const char* filename){
        std::ifstream file(filename, std::ios::binary);
        if(!file){
            return;
        }
        if(students != nullptr){
            delete[] students;
        }
        int counter;
        file.write((const char*)&counter, sizeof(int));
        students = new Student[counter];
        
        for(int i = 0;i<counter;i++){
            Student s = students[i].read_from_binary_file(filename);
            students[i] = s;
        }
        
        file.close();
        
        file.close();
    }
    private:
    void free(){
        if(students == nullptr){
            return;
        }
        delete[] students;
        students = nullptr;
    }
    void copyFrom(const School& other){
        this->count = other.count;
        
        setStudents(other.students);
    }
}
int main()
{
  //  std::cout << "Hello World!\n";
}
