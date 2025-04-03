#include <iostream>
#include <cstring>
#include <fstream>

constexpr int MAX_LEN = 30;
class Student {
	char* name=nullptr;//big4
	int* grades=nullptr;//big4
	int gradesCount=0;
	char moto[MAX_LEN]="";

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
	void setMoto(const char* moto) {

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
	int getGradesCount() const {
		return gradesCount;
	}
	const char* getName() const {
		return name;
	}
	int* getGrades() const {
		return grades;
	}
	const char* getMoto() const {
		std::cout<<moto;
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
		setGradesCount(other.gradesCount);
		setGrades(other.grades);

		setMoto(other.moto);
	}
	void write_in_binary_file(std::ofstream& file) {
	   
		
		int len = strlen(this->name);
		
		file.write((const char*)&len, sizeof(int));

		file.write((const char*)this->name, sizeof(char) * len);
		// for(int i = 0; i<len; i++) {
		// 	file.write((const char*)&this->name[i], sizeof(char));

		// }
		
		file.write((const char*)&this->gradesCount, sizeof(int));
		file.write((const char*)this->grades, sizeof(int) * this->gradesCount));
		// for(int i = 0; i<this->gradesCount; i++) {
		// 	file.write((const char*)&this->grades[i], sizeof(int));
		// }


		file.write((const char*)&this->moto, MAX_LEN);

		file.close();
	}

	void read_from_binary_file(std::ifstream& file) {

		free();
		int len;
		file.read((char*)&len, sizeof(int));
//		std::cout<<len<<' ';


		char* name = new char[len+1];
		//name[len] = '\0';
		file.read((char*)name, sizeof(char) * (len));
        //std::cout<<name;
		setName(name);
		// // for(int i = 0;i<len;i++){
		// //     file.write((const char*)&this->name[i], sizeof(char));
		// // }
		int count;
		file.read((char*)&count, sizeof(int));
	//	std::cout<<count<<' ';
		int* grades=new int[count];
		file.read((char*)&this->grades, sizeof(int) * count);

		// for(int i=0; i<count; i++) {
		// 	int grade;
		// 	file.read((char*)&grade, sizeof(int));
		// 	//std::cout<<grade<<' ';
		// 	grades[i] = grade;
		// }
		
                setGradesCount(count);
		setGrades(grades);
		file.read((char*)&this->moto, MAX_LEN);

		file.close();

		for(int i=0; i<gradesCount; i++) {
			std::cout<<this->grades[i]<<' ';
		}

		std::cout<<this->moto<<' ';
		std::cout<<this->name<<' ';

	}
};
class School {
	Student* students=nullptr;
	int count=0;


public:
	School() = default;
	School(Student* students, int count) {
		setCount(count);
		setStudents(students);
	}
	School(const School& other) {
		copyFrom(other);
	}
	void setCount(int count) {
		if(count < 0) {
			return;
		}
		this->count = count;
	}
	void setStudents(Student* students) {
		if(students == nullptr) {
			return;
		}
		if(this->students == students) {
			return;
		}
		if(this->students != nullptr) {
			delete[] students;
			students = nullptr;
		}

		this->students = new Student[this->count];
		for(int i = 0; i<count; i++) {
			this->students[i] = students[i];
		}

	}
	School& operator = (const School& other) {
		if(this != &other) {
			free();
			copyFrom(other);
		}
		return *this;
	}

	~School() {
		free();
	}
	void write_in_binary_file_school(const char* filename) {
		std::ofstream file(filename, std::ios::binary|std::ios::app);
		if(!file) {
			return;
		}
 		file.write((const char*)&this->count, sizeof(int));
 		//std::cout<<this->count;

		for(int i = 0; i<this->count; i++) {
		   
		    
			students[i].write_in_binary_file(file);
		}
       // students[0].write_in_binary_file(filename);

		file.close();
	}
	void read_in_binary_file_school(const char* filename) {
		std::ifstream file(filename,std::ios::binary);
		if(!file) {
			return;
		}
		if(students != nullptr) {
			delete[] students;
		}
  		int counter;
  		file.read((char*)&counter, sizeof(int));
  		this->count = counter;
  		std::cout<<counter<<' ';
 		students = new Student[counter];

		for(int i = 0; i<2; i++) {
		    
			students[i].read_from_binary_file(file);

		}
    

		file.close();
	}
private:
	void free() {
		if(students == nullptr) {
			return;
		}
		delete[] students;
		students = nullptr;
	}
	void copyFrom(const School& other) {
		this->count = other.count;

		setStudents(other.students);
	}
// 	public:
// 	void print(){
// 	    for(int i = 0;i<this->count;i++){
// 	        std::cout<<students[i].getName();
// 	    }
// 	}
};
int main()
{
	School so;
	Student* students = new Student[2];
	Student s1;
	s1.setName("veli");
	s1.setMoto("");
	//  std::cout<<s1.getName();
	s1.setMoto("lolo");

	int* grades = new int[3];
	grades[0] = 2;
	grades[1] = 3;
	grades[2] = 5;

	s1.setGradesCount(3);
	s1.setGrades(grades);
	// for(int i = 0;i<3;i++){
	//     std::cout<<s1.getGrades()[i]<<' ';
	// }
	// std::cout<<' '<<s1.getMoto()<<' ';
	//s1.setGradesCount(3);
	
	Student s2;
	s2.setName("lilii");
	s2.setMoto("");
	//  std::cout<<s1.getName();
	s2.setMoto("popoipoi");

	grades = new int[4];
	grades[0] = 2;
	grades[1] = 3;
	grades[2] = 4;
	grades[3] = 9;

	s2.setGradesCount(3);
	s2.setGrades(grades);
	students[0] = s1;
	students[1] = s2;
	// students[1] = s1;


// 	students[0].write_in_binary_file("lo.bin");
// 	students[0].read_from_binary_file("lo.bin");


// 	std::cout<<students[0].getMoto();
	so.setCount(2);

	so.setStudents(students);
// 	for(int i = 0; i<1; i++) {
// 		std::cout<<students[i].getMoto();
// 	}
   // so.print();
 	so.write_in_binary_file_school("school.bin");
 	so.read_in_binary_file_school("school.bin");
	//  std::cout << "Hello World!\n";
}
