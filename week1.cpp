// week1pracOOP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
//zad 1
namespace MatrixNS {
	int** create_matrix(int N, int M) {
		if (N < 1 || M < 1) {
			return 0;
		}
		int** matrix = new int* [N];
		for (int i = 0;i < N;i++) {
			matrix[i] = new int[M];
		}
		return matrix;
	}
	int** read_matrix(int N, int M) {
		if (N < 1 || M < 1) {
			return 0;
		}
		int** matrix = create_matrix(N, M);
		for (int i = 0;i < N;i++) {
			for (int j = 0;j < M;j++) {
				std::cin >> matrix[i][j];
			}
		}
		return matrix;

	}
	int** transpose_matrix(int N, int M, int** ar) {
		if (ar == nullptr) {
			return 0;
		}
		int** transposed_matrix = create_matrix(M, N);
		for (int i = 0;i < M;i++) {
			for (int j = 0;j < N;j++) {
				transposed_matrix[i][j] = ar[j][i];
			}
		}

		return transposed_matrix;
	}
	void print_matrix(int N, int M, int** ar) {
		for (int i = 0;i < N;i++) {
			for (int j = 0;j < M;j++) {
				std::cout << ar[i][j] << ' ';
			}
			std::cout << '\n';
		}
	}
	int** swap_rows(int row1, int row2, int N, int M, int** ar) {

		if (row1 > M - 1 || row2 > M - 1 || row1 < 0 || row2 < 0) {
			std::cout << "Not a valid input for N or M";
			return 0;
		}
		if (ar == nullptr) {
			return 0;
		}

		int** matrix = create_matrix(N, M);
		for (int i = 0;i < N;i++) {
			if (i == row1) {
				for (int j = 0;j < M;j++) {
					matrix[i][j] = ar[row2][j];

				}
			}
			else if (i == row2) {
				for (int j = 0;j < M;j++) {
					matrix[i][j] = ar[row1][j];

				}
			}
			else {
				for (int j = 0;j < M;j++) {
					matrix[i][j] = ar[i][j];

				}
			}




		}
		print_matrix(N, M, matrix);
		return matrix;

	}
}
void delete_matrix(int** matrix) {
	for (int i = 0;i < N;i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}
//zad 2
namespace Complex_Numbers {
	struct Complex_Number {
		double real_part;
		double imaginary_part;
	};

	Complex_Number sum(Complex_Number& a, Complex_Number& b) {
		return Complex_Number{ a.real_part + b.real_part, a.imaginary_part + b.imaginary_part };
	}

	Complex_Number multiplication(Complex_Number& a, Complex_Number& b) {
		return Complex_Number{ a.real_part * b.real_part - a.imaginary_part * b.imaginary_part ,
			a.real_part * b.imaginary_part + a.imaginary_part * b.real_part };
	}
	Complex_Number division(Complex_Number& a, Complex_Number& b) {
		return Complex_Number{ (a.real_part * b.real_part + a.imaginary_part * b.imaginary_part) / (b.imaginary_part * b.imaginary_part + a.real_part * a.real_part)  ,
			(a.imaginary_part * b.real_part - a.real_part * b.imaginary_part) / (b.imaginary_part * b.imaginary_part + a.real_part * a.real_part) };
	}
	double absvalue(double num) {
		if (num < 0) {
			return -num;
		}
		else {
			return num;
		}
	}
	void print_Complex_Number(Complex_Number& a) {
		std::cout << a.real_part;
		if (a.imaginary_part > 0) {
			std::cout << " + ";
		}
		else std::cout << " - ";
		std::cout << absvalue(a.imaginary_part) << 'i';
	}
	bool is_real_number(Complex_Number a) {
		return(a.imaginary_part == 0);
	}
}
//zad 3
namespace Triangles {
	struct Point {
		double x;
		double y;
	};
	struct Triangle {
		Point A;
		Point B;
		Point C;
		double AB_side;
		double BC_side;
		double AC_side;

		double area;

	};
	double absvalue(double num) {
		if (num < 0) {
			return -num;
		}
		else {
			return num;
		}
	}
	void calculate_sides_and_area(Triangle& triangle) {
		triangle.AB_side = sqrt((triangle.A.x - triangle.B.x) * (triangle.A.x - triangle.B.x) + (triangle.A.y - triangle.B.y) * (triangle.A.y - triangle.B.y));
		triangle.BC_side = sqrt((triangle.B.x - triangle.C.x) * (triangle.B.x - triangle.C.x) + (triangle.B.y - triangle.C.y) * (triangle.B.y - triangle.C.y));
		triangle.AC_side = sqrt((triangle.A.x - triangle.C.x) * (triangle.A.x - triangle.C.x) + (triangle.A.y - triangle.C.y) * (triangle.A.y - triangle.C.y));

		//I validate if the triangle can exist - if (a + b < c) - it is not a triangle
		if (triangle.AB_side + triangle.BC_side < triangle.AC_side) {
			std::cout << "This traingle cannot exist!";
			return;
		}
		else if (triangle.AB_side + triangle.AC_side < triangle.BC_side) {
			std::cout << "This traingle cannot exist!";
			return;
		}
		else if (triangle.AC_side + triangle.BC_side < triangle.AB_side) {
			std::cout << "This traingle cannot exist!";
			return;
		}
		//I use the cosinus formula for finding the area of the triangle
		double cos = (triangle.AB_side * triangle.AB_side + triangle.AC_side * triangle.AC_side - triangle.BC_side * triangle.BC_side) / (2 * triangle.AB_side * triangle.BC_side);
		double sin = sqrt(1 - cos * cos);//I find the sin of the angle between the rwo sides and then use the formula: S = a.b.sin(alpha)/2; 

		//By multiplying the two sides and the sinus of the angle between them
		triangle.area = triangle.AB_side * triangle.AC_side * sin / 2;



	}
	void swap_triangles(Triangle& one, Triangle& two) {

		Triangle help = one;
		one = two;
		two = help;
	}
	void sort_traingles_by_area(int N, Triangle triangles[]) {
		for (int i = 0;i < N;i++) {
			calculate_sides_and_area(triangles[i]);

		}
		//I decided to use the Selection Sort method
		for (int i = 0;i < N - 1;i++) {
			int minidx = i;
			for (int j = i + 1;j < N;j++) {
				if (triangles[i].area > triangles[j].area) {
					minidx = j;
				}
			}
			if (minidx != i) {
				swap_triangles(triangles[i], triangles[minidx]);
			}
		}
		//I print the sorted areas
		for (int i = 0;i < N;i++) {
			std::cout << triangles[i].area << ' ';
		}
		//printing the identificators of the sorted triangles
		for (int i = 0;i < N;i++) {
			std::cout << "Triangle " << i << '\n';
			std::cout << "Point A: ";
			std::cout << triangles[i].A.x<<' '<<triangles[i].A.y << '\n';
			std::cout << "Point B: ";
			std::cout << triangles[i].B.x << ' ' << triangles[i].A.y << '\n';
			std::cout << "Point C: ";
			std::cout << triangles[i].A.x << ' ' << triangles[i].A.y << '\n';
		}
	}

}
//zad 4
int const MAX_LEN = 100;
	enum class Major {
		SoftwareEngineering,
		InformationSystems,
		ComputerScience,
		AppliedMathematics,
		Mathematics,
		Informatics,

	};
	struct Student {
		double grade;
		char fn[MAX_LEN];
		char name[MAX_LEN];
		Major major;

    };
	struct Group {
		Student* students;
		double average_grade;
		int students_count;

	};
	Group write_students_group() {
		Group group;
		int N;
		std::cin >> N;

		group.average_grade = 0;
		group.students_count = N;
		group.students = new Student[N];

		for (int i = 0;i < N;i++) {
			std::cout << "Enter grade of student " << i+1 << '\n';
			std::cin >> group.students[i].grade;
			std::cin.ignore();
			std::cout << "Enter faculty number of student " << i+1 << '\n';
			std::cin.getline(group.students[i].fn, MAX_LEN);
			std::cout << "Enter name of student " << i+1 << '\n';
			std::cin.getline(group.students[i].name, MAX_LEN);
			std::cout << "Enter major(from 0 to 5) of student " << i+1 << '\n';
			int major;
			std::cin >> major;
			group.students[i].major = Major(major);
			std::cout << '\n';
		}
		
		double avg = 0;
		for (int i = 0;i < N;i++) {
			avg += group.students[i].grade;
		}
		group.average_grade = avg / N;
		return group;

		//std::cout << group.average_grade;
		/*for (int i = 0;i < N;i++) {
			std::cout << group.students[i].grade << " " << group.students[i].fn << ' ' << group.students[i].name;
			int major;

		}*/
		
		/*for (int i = 0;i < N;i++) {
			std::cout << group.students[i].grade <<" "<< group.students[i].fn <<' '<< group.students[i].name;
		
		}*/
		
	}
	int number_of_students_having_scholarship(Group group, double minimal_grade) {
		int count = 0;
		for (int i = 0;i < group.students_count;i++) {
			if (group.students[i].grade >= minimal_grade) {
				count++;
			}
		}
		return count;
	}
	void swap_students(Student& a, Student& b) {
		Student help = a;
		a = b;
		b = help;
	}
	void print_students_getting_scholarship(Group group, double minimal_grade) {
		int number_of_students_with_scholarship = number_of_students_having_scholarship(group, minimal_grade);
	
		for (int i = 0;i < group.students_count - 1;i++) {
			int maxidx = i;
			for (int j = i + 1;j < group.students_count;j++) {
				if (group.students[i].grade < group.students[j].grade) {
					maxidx = j;
				}
			}
			if (maxidx != i) {
				swap_students(group.students[i], group.students[maxidx]);
			}
		}
		for (int i = 0;i < number_of_students_with_scholarship;i++) {
			std::cout << group.students[i].name << '\n';
		}
		
	}
	int len(char* str) {
		int count = 0;
		while (*str != '\0') {
			str++;
			count++;
		}
		return count;
	}
	bool are_the_same(char* str1, char* str2) {
		int size = len(str1);
		for (int i = 0;i < size;i++) {
			if (str1[i] != str2[i]) {
				return 0;
			}
		}
		return 1;
	}
	int lexicographic(char* str1, char* str2) {
		if (str1 == nullptr || str2 == nullptr) {
			return -999;
		}
		while (*str1 && *str2) {
			if (*str1 != *str2) {
				return (*str1 - *str2);
			}
			str1++;
			str2++;
		}
		return 0;
	}
	void sort_fn(Group group) {
		int n = group.students_count;
		for (int i = 0;i < n - 1;i++) {
			int maxidx = i;
			for (int j = i + 1;j < n;j++) {
				if (lexicographic(group.students[i].fn, group.students[j].fn) > 0) {
					maxidx = j;
				}
			}
			if (maxidx != i) {
				swap_students(group.students[maxidx], group.students[i]);
			}
		}
	}
	bool is_student_in_group(Group group, char* fn) {
		sort_fn(group);//we sort the students by faculty numbers

		/*for (int i = 0;i < group.students_count;i++) {
			std::cout << group.students[i].fn<<' ';
		}*/
		for (int i = 0;i < group.students_count;i++) {
			if (are_the_same(group.students[i].fn, fn)) {
				return 1;
			}
		}
		return 0;
	}
	//We create all the groups from the faculty
	Group* create_groups_faculty(int number_of_groups) {
		Group* groups = new Group[number_of_groups];
		for (int i = 0;i < number_of_groups;i++) {
			groups[i] = write_students_group();

		}
		return groups;
	}
	//Function that finds the student from all the groups
	bool find_student_in_faculty(char* fn, Group groups[], int number_of_groups) {
		for (int i = 0;i < number_of_groups;i++) {
			if (is_student_in_group(groups[i], fn)) {
				return 1;
			}
		
		}
			
		return 0;
	}
	//zad 5
	struct Point {
		double x;
		double y;

	};

	void read_point(Point& point) {
		std::cin >> point.x >> point.y;
	}

	void print_point(Point p) {
		std::cout << "X: " << p.x<<'\n';
		std::cout << "Y: " << p.y;
	}
	double distance_from_center(Point p) {
		return sqrt(p.x * p.x + p.y * p.y);
	}
	double distance_between_two_points(Point p1, Point p2) {
		return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
	}

	void is_in_circle(double r, Point p) {
		double d = distance_from_center(p);
		if (d < r) {
			std::cout << "The point is in the circle";
		}
		else if (d == r) {
			std::cout << "The point is on the contour";
		}
		else {
			std::cout << "The point is out of the circle";
		}
	}
	void in_which_quadrant(Point p) {
		if (p.x > 0 && p.y > 0) {
			std::cout << "I quadrant";
		}
		else if (p.x < 0 && p.y > 0) {
			std::cout << "II quadrant";
		}
		else if (p.x < 0 && p.y < 0) {
			std::cout << "III quadrant";
		}
		else if (p.y < 0 && p.x > 0) {
			std::cout << "IV quadrant";
		}
		else if (p.x == 0) {
			std::cout << "On the Ordinate";
		}
		else if (p.y == 0) {
			std::cout << "On the Abcisa";
		}
		else {
			std::cout << "Is on the center";
		}


	}

	//zad 6
	enum class Position
	{
		Software_Engineer, 
		Senior_Software_Engineer,
		Engineer_Manager,
		Lead_Software_Engineer,
	};

	struct Worker {
		char name[MAX_LEN];
		Position position;
		double salary;
		int grade;
	};

	Worker create_worker() {
		Worker worker;
		std::cout << "Name: "<<'\n';
		std::cin.ignore();
		std::cin.getline(worker.name, MAX_LEN);
		std::cout << "Position: "<<'\n';
		int pos;
		std::cin >> pos;
		worker.position = Position(pos);
		std::cout << "Salary: "<<'\n';
		std::cin >> worker.salary;
		std::cout << "Grade: "<<'\n';
		std::cin >> worker.grade;

		return worker;

	}

	void position(Worker w) {
		if (w.position == Position::Software_Engineer) {
			std::cout << "Software Engneer";
		}
		else if(w.position == Position::Senior_Software_Engineer){
			std::cout << "Senior Software Engineer";
		}
		else if (w.position == Position::Engineer_Manager) {
			std::cout << "Engineer Manager";
		}
		else if (w.position == Position::Lead_Software_Engineer) {
			std::cout << "Lead Software Engineer";
		}
	}
	void print_worker_info(Worker worker) {
	
		std::cout << "Worker " << worker.name<<" is ";
		position(worker);
		std::cout<< ".He earns " << worker.salary << " dollars and he has grade " << worker.grade << '.';
	}


	struct Firm {
		Worker* workers;
		size_t number_of_workers;
		double average_salary;
	};


	Firm create_firm() {

		Firm firm;
		int N;
		std::cin >> N;

		firm.number_of_workers = N;
		firm.average_salary = 0;

		firm.workers = new Worker[N];

		for (int i = 0;i < N;i++) {

			firm.workers[i] = create_worker();
		}

		double sum = 0;

		for (int i = 0;i < firm.number_of_workers;i++) {
			sum += firm.workers[i].salary;
		}
		firm.average_salary = sum / firm.number_of_workers;

		return firm;
	}

	//I find the number of employees with higher than average salaries
	int higher_salaries(Firm firm) {
		int count = 0;
		for (int i = 0;i < firm.number_of_workers;i++) {
			if (firm.workers[i].salary > firm.average_salary) {
				count++;
			}
		}
		return count;
	}
	Worker* above_avg_salary(Firm firm) {
		int count = higher_salaries(firm);
		Worker* workers = new Worker[count];
		int idx = 0;
		for (int i = 0;i < firm.number_of_workers;i++) {
			if (firm.workers[i].salary > firm.average_salary) {
				workers[idx++] = firm.workers[i];
			}
		}
		return workers;
	}
	void swap_workers(Worker& a, Worker& b) {
		Worker help = a;
		a = b;
		b = help;
	}
	void sort_names(Firm firm) {
		int n = higher_salaries(firm);
		Worker* workers = above_avg_salary(firm);
		for (int i = 0;i < n - 1;i++) {
			int maxidx = i;
			for (int j = i + 1;j < n;j++) {
				if (lexicographic(firm.workers[i].name, firm.workers[j].name) > 0) {
					maxidx = j;
				}
			}
			if (maxidx != i) {
				swap_workers(firm.workers[maxidx], firm.workers[i]);
			}
		}
		for (int i = 0;i < n;i++) {
			std::cout << workers[i].name << '\n';
		}
	}
	//Finding the number of specialists using the integer pos to access the obj from the enum class
	//I use the integer variable pos to refer to the different types of engineers
	int number_of_specialists(Firm firm, int pos) {
		int count = 0;
		for (int i = 0;i < firm.number_of_workers;i++) {
			if (firm.workers[i].position == Position(pos)) {
				count++;
			}
		}
		return count;
	}
	Worker* workers_specialists(Firm firm, int pos) {
		int count = number_of_specialists(firm, pos);
		Worker* workers = new Worker[count];
		int idx = 0;
		for (int i = 0;i < firm.number_of_workers;i++) {
			if (firm.workers[i].position == Position(pos)) {
				workers[idx++] = firm.workers[i];
			}
		}
		return workers;
	}

	//I sort the workers from each different engineering group by grade
	void sort_by_grade(Firm firm, int pos) {
		int n = number_of_specialists(firm, pos);
		//If there are no specialist from this type of engineers we just leave the function
		if (n == 0) {
			return;
		}
		Worker* workers = workers_specialists(firm, pos);
		for (int i = 0;i < n - 1;i++) {
			int maxidx = i;
			for (int j = i + 1;j < n;j++) {
				if (firm.workers[i].grade > firm.workers[j].grade) {
					maxidx = j;
				}
			}
			if (maxidx != i) {
				swap_workers(firm.workers[maxidx], firm.workers[i]);
			}
		}
		//I print the workers with min and max grade from every group
		position(workers[0]);//I print the type of the engineer
		std::cout << '\n';
		std::cout << workers[0].name << " with min grade: " << workers[0].grade << '\n';//the first element from the array will be the worker with
		//minimal grade, because we have already sorted the array;
		std::cout << workers[n - 1].name << " with max grade: " << workers[n - 1].grade << '\n';

	}

	//Here I decided to print the max and min grade of an employee from each position group
	//I create a loop from 0 to 3 - so to find the min and max grade from every group where 0 - Software Engineer, 1 - Senior Software Engineer 
	//and etc.
	int const ENUM_ENGINEER_SIZE = 4;

	void print_maxes_mins(Firm firm) {

		for (int i = 0;i < ENUM_ENGINEER_SIZE;i++) {
			sort_by_grade(firm, i);
		}
	}
	//zad 7
	int const MAX_LEN_GRAPH = 10;

	struct Rib {
		char startPoint[MAX_LEN_GRAPH];//етикет на начален връх и съответно на краен
		char endPoint[MAX_LEN_GRAPH];
	};

	struct Oriented_Graph {
		Rib* ribs;
		int E;
		int V;
	};
	Rib create_rib() {

		Rib rib;
		std::cin.ignore();
		std::cout << "Starting point: " << '\n';
		std::cin.getline(rib.startPoint, MAX_LEN_GRAPH);
		std::cout << "Ending point: " << '\n';
		std::cin.getline(rib.endPoint, MAX_LEN_GRAPH);
	
		return rib;
	}
	//ако етикетите на върховете са с едни и същи имена
	bool are_the_same(char* str1, char* str2) {

		while (((*str1) != '\0') && ((*str2) != '\0')) {

			if (*str1 != *str2) {

				return 0;
			}

			str1++;
			str2++;
		}

		return 1;
	}

	//ако съответното ребро е вече в графа
	bool rib_in_array(Rib* ribs, int& E, Rib rib) {
		for (int i = 0;i < E;i++) {

			if (are_the_same(rib.startPoint, ribs[i].startPoint) && are_the_same(rib.endPoint, ribs[i].endPoint)) {

				return 1;
			}
		}

		return 0;
	}
//взимаме уникланите върхове
	bool point_in_array(char** points, int& len, char* point) {
		for (int i = 0;i < len;i++) {

			if (are_the_same(points[i], point)) {

				return 1;
			}
		}

		return 0;
	}

	Oriented_Graph create_graph() {
		Oriented_Graph graph;
		int E;
		std::cin >> E;

		graph.ribs = new Rib[E];
		int idx = 0;
		for (int i = 0;i < E;i++) {

			Rib rib = create_rib();
			//Ако началото на и краят съвпадат или ако реброто е вече в списъка с ребра
			//ако потребителят се опита да добави примка
			if (are_the_same(rib.startPoint, rib.endPoint)) {

				continue;
			}
			//Ако това ребро е вече добавено в графа
			if (rib_in_array(graph.ribs, idx, rib)) {
				continue;
			}

			graph.ribs[idx++] = rib;
		}

		graph.E = idx; // Броят на ребрата, които не образуват примки и не се повтарят

		
		int len = 0;
		char** points = new char*[2 * idx];//Максималният брой ребра - 2 пъти броя на ребрата
		//Намираме броя върхове
		for (int i = 0;i < idx;i++) {
			//Проверяваме за всеки връх - било то начален или краен на реброто дали се намира в 
			//в листа ни с върхове, и ако не го добавяме - накрая броят на ребрата съответства на 
			//размера на масива от уникални върхове
			if (!point_in_array(points, len, graph.ribs[i].startPoint)) {
				points[len++] = graph.ribs[i].startPoint;
			}
			if (!point_in_array(points, len, graph.ribs[i].endPoint)) {
				points[len++] = graph.ribs[i].endPoint;
			}

		}
		//we remove the dynamic memory, when we don't need it anymore
		// for(int i = 0;i<len;i++){
		//     delete[] points[i];
		// }
		// delete[] points;

		graph.V = len;
		//std::cout<<graph.V;
		return graph;
	}

	//we just delete the graph
	// void delete_graph(Oriented_Graph g){
	//     g.V = 0;//зануляваме броя на върховете и ребрата
	//     g.E = 0;
	//     g.ribs = nullptr;
	//   // delete g;
	// }

	int len(char str[]) {
		int i = 0;
		while (str[i] != '\0') {
			i++;
		}
		return i;
	}
	void strcopy(char str[], char str1[]) {
		for (int i = 0;i < len(str1);i++) {
			str[i] = str1[i];
		}
	}

	void add_rib(char startPoint[], char endPoint[], Oriented_Graph& graph) {
		Rib rib;
		//Присвояваме на обекта rib съответните подадени имена за върхове
		strcopy(rib.startPoint, startPoint);
		strcopy(rib.endPoint, endPoint);

		Rib* ribs = new Rib[graph.V];
		for (int i = 0;i < graph.E;i++) {
			ribs[i] = graph.ribs[i];
		}

		graph.ribs = new Rib[graph.E + 1];
		for (int i = 0;i < graph.E;i++) {
			graph.ribs[i] = ribs[i];
		}

		graph.ribs[graph.E] = rib;
		//ребрата се увеличават с едно
		graph.E = graph.E + 1;

	}
	void stepeni_izhod_vhod(Oriented_Graph graph, char point[]) {
		int vhod = 0;
		int izhod = 0;
		for (int i = 0;i < graph.E;i++) {
			//ако името съвпада с началната точка- значи от него излиза ребро
			if (are_the_same(point, graph.ribs[i].startPoint)) {
				izhod++;
			}
			//ако съвпада с крайната точка - нзачи в него влиза ребро
			else if (are_the_same(point, graph.ribs[i].endPoint)) {
				vhod++;
			}
		}
		std::cout << "Stepen na vhoda: " << vhod << '\n';
		std::cout << "Stepen na izhoda: " << izhod << '\n';

	}
	bool is_full_graph(Oriented_Graph g) {
		return (g.V * (g.V - 1) == g.E);
	}

	void delete_rib(Oriented_Graph& graph, Rib rib) {
		//Ако реброто не ев графа - нямаме какво да трием
		if (!rib_in_array(graph.ribs, graph.E, rib)) {
			std::cout << "This rib is not on the graph!";
			return;
		}

		Rib* ribs = new Rib[graph.E];
		for (int i = 0;i < graph.E;i++) {
			ribs[i] = graph.ribs[i];
		}

		graph.ribs = new Rib[graph.E - 1];
		int idx = 0;
		for (int i = 0;i < graph.E;i++) {
			//като намерим реброто, което искаме да премахнем - итерираме без да добавим съответното ребро към списъка с ребра
			if (are_the_same(ribs[i].startPoint, rib.startPoint) && are_the_same(ribs[i].endPoint, rib.endPoint)) {

				continue;
			}
			graph.ribs[idx++] = ribs[i];
		}
		//Ребрата ни са с едно по-малко, тъй като сме премахнали вече едно
		graph.E = graph.E - 1;
		delete[] ribs;
		/*for (int i = 0;i < graph.E;i++) {
			std::cout << graph.ribs[i].startPoint << graph.ribs[i].endPoint << '\n';
		}*/
	}

	int main()
	{
	
		/*Oriented_Graph g = create_graph();
		Rib rib = { "a", "r" };
		delete_rib(g, rib);*/

		//stepeni_izhod_vhod(g, "a");
	  //   for(int i = 0;i<g.V-1;i++){
	  //       std::cout<<g.ribs[i].startPoint;
	  //   }
	  //   add_rib("a", "p", g);
	  //   std::cout<<g.E;
	  //   for(int i = 0;i<g.E+1;i++){
	  //       std::cout<<g.ribs[i].startPoint;
	  //   }
	  //   char s[] = "e";
	  //   char d[] = "d";

	  // std::cout<<are_the_same(s, d);

		//Worker w = create_worker();
		//Firm f = create_firm();
		//std::cout<<f.average_salary;
		//print_maxes_mins(f);
		/*Worker w = create_worker();
		std::cout << w.name;*/
		//Firm f = create_firm();
		
		//print_worker_info(w);
		//Group one = write_students_group();
		
		//std::cout << number_of_students_having_scholarship(one, 2.30);
		//print_students_getting_scholarship(one, 2.50);
		//char e[] = "aoko";
		/*char d[] = "lolo";
		std::cout << lexicographic(e, d);*/
		//std::cout << is_student_in_group(one, e);
	
		/*Group* groups = create_groups_faculty(3);
		char i[] = "aaa";
		std::cout << find_student_in_faculty(i, groups, 3);*/
		//delete[] groups;

		/*Point a = { 11, 2 };
		std::cout << distance_from_center(a)<<' ';
		Point b = { 1, 2 };
		std::cout << distance_between_two_points(a, b)<<' ';
		in_which_quadrant( a);*/

		/*Triangle one = { {1, 2}, {2, 3}, {1, 3} };
		Triangle two = { {1, 2}, {3, 3}, {1, 4} };
		
		Triangle tr[2] = { one, two };
		sort_traingles_by_area(2, tr);*/

		//Complex_Number a = { 1, 2 };
		//Complex_Number b = { 3, 4 };

		//Complex_Number c = multiplication(a, b);
		////std::cout << c.imaginary_part;
		//print_Complex_Number(c);

		//int N = 3;
		//int M = 3;
		//int** ar = read_matrix(N, M);
		////transpose_matrix(N, M, ar);
		//swap_rows(1, 2, N, M, ar);
		return 0;
	}

int main(){
return 0;
}
	
