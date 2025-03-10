

#include <iostream>
#include <fstream>

//zad 1
constexpr size_t MAX_SIZE = 1024;
constexpr char DELIMITER = '\n';

void write_sum_in_file(std::ofstream& file) {
    int a, b, c;
    std::cin >> a >> b >> c;
    int sum = a + b + c;
    int p = a * b * c;


    file.open("results.txt");

    if (!file.is_open())
    {
        std::cout << "Error in creating file!" << std::endl;

        return;
    }
    file << sum << '\n';
    file << p << '\n';

    file.close();

}
int char_array_to_int(char ar[]) {
    int i = 0;
    int number = 0;
    while (ar[i] != '\0') {
        number = number * 10 + (ar[i] - '0');
        i++;
    }
    return number;
}
void print_diff(std::ifstream& file) {
    file.open("results.txt");

    if (!file.is_open())
    {
        std::cout << "Error in creating file!" << std::endl;

        return;
    }
    char buff[MAX_SIZE + 1];
    file.getline(buff, MAX_SIZE + 1, DELIMITER);
    int diff = char_array_to_int(buff);
    file.getline(buff, MAX_SIZE + 1, DELIMITER);
    diff -= char_array_to_int(buff);
    std::cout << diff;
    file.close();
}

//zad 2
int const MAX_SIZE_R = 25;
struct Pair {
    int a;
    int b;
};
struct Relation {
    Pair* pairs;
    int size_relation;
};
void writeRelationToFile(std::ofstream& file, Relation R) {
    file.open("relation.txt");
    if (!file.is_open()) {
        return;
    }
    for (int i = 0;i < R.size_relation;i++) {
        file << "<" << R.pairs[i].a << "," << R.pairs[i].b << ">" << '\n';
    }
    file.close();
}
void create_relation(Relation& R, int size) {
    R.size_relation = size;
    R.pairs = new Pair[size];
    for (int i = 0;i < size;i++) {
        std::cin >> R.pairs[i].a >> R.pairs[i].b;
    }
}
//finding the first number of the pair
int number_one(char* buffer) {
    int n1 = 0;
    buffer++;
    while (*buffer != ',') {
        n1 = 10 * n1 + (*buffer - '0');
        buffer++;
    }
    return n1;
}
//the second one
int number_two(char* buffer) {
    int n = 0;
    while (*buffer != ',') buffer++;
    buffer++;
    while (*buffer != '>') {
      
        n = 10 * n + (*buffer - '0');
        buffer++;
    }
    return n;
}

void readRelationFromFile(std::ifstream& file, Relation& R) {
    file.open("relation.txt");
    if (!file.is_open()) {
        return;
    }
    char buffer[MAX_SIZE];
    int n1 = 0;
    int n2 = 0;
    
    int n;
    //int i = 0;
  while (!file.eof()) {
        file.getline(buffer, MAX_SIZE + 1, DELIMITER);
        
        std::cout << number_one(buffer)<<' ';
      
        std::cout << number_two(buffer)<<'\n';

        //if we want to create a Relation with the pairs from the file
      /*  R.pairs[i].a = number_one(buffer);
        R.pairs[i].b = number_one(buffer);
        i++;*/
    }
}
void addPairToRelation(Relation& r, Pair p) {
    Pair* pairs = new Pair[r.size_relation];
    for (int i = 0;i < r.size_relation;i++) {
        pairs[i] = r.pairs[i];
    }
    r.pairs = new Pair[r.size_relation + 1];
    for (int i = 0;i < r.size_relation;i++) {
        r.pairs[i] = pairs[i];
    }
    r.pairs[r.size_relation] = p;
    r.size_relation = r.size_relation + 1;

    /*for (int i = 0;i < r.size_relation;i++) {
        std::cout << r.pairs[i].a << r.pairs[i].b << '\n';
    }*/
}
void swap_pairs(Pair& a, Pair& b) {
    Pair h = a;
    a = b;
    b = h;
}
bool is_bigger_pair(Pair p1, Pair p2) {
    if (p1.a < p2.a) {
        return 0;
    }
    else {
        if (p1.a == p2.a) {
            if (p1.b < p2.b) {
                return 0;
            }
            else {
                return 1;
            }
        }
        return 1;
    }
}
void lexicographic_order(Relation& R) {
    int size = R.size_relation;
    for (int i = 0;i < size - 1;i++) {
        int minidx = i;
        for (int j = i + 1;j < size;j++) {
            if (is_bigger_pair(R.pairs[i], R.pairs[j])){
                minidx = j;
            }
        }
        if (minidx != i) {
            swap_pairs(R.pairs[i], R.pairs[minidx]);
        }
    }

   /* for (int i = 0;i < size;i++) {
        std::cout << R.pairs[i].a << R.pairs[i].b << '\n';
    }*/
}
bool num_in_array(int ar[], int& len, int n) {
    for (int i = 0;i < len;i++) {
        if (ar[i] == n) {
            return 1;
        }
    }
    return 0;
}
bool pair_in_array(Pair pairs[], int& len, Pair p) {
    for (int i = 0;i < len;i++) {
        if (pairs[i].a == p.a && pairs[i].b == p.b) {
            return 1;
        }
    }
    return 0;
}

void reflexive_closing(Relation& R) {
    int size = R.size_relation;
    int* nums = new int[2 * size];
    int k = 0;
    for (int i = 0;i < size;i++) {

        if (!num_in_array(nums, k, R.pairs[i].a)) {
            nums[k++] = R.pairs[i].a;
        }
        if (!num_in_array(nums, k, R.pairs[i].b)) {
            nums[k++] = R.pairs[i].b;
        }

    }
    Pair* p = new Pair[size];
    for (int i = 0;i < size;i++) {
        p[i] = R.pairs[i];
    }
    R.pairs = new Pair[size + k];

    for (int i = 0;i < size;i++) {
        R.pairs[i] = p[i];
    }
    int len = size;
    for (int i = 0;i < k;i++) {
        int a = nums[i];
        Pair rp = { a, a };
        if (!pair_in_array(R.pairs, len, rp)) {
            R.pairs[len++] = rp;
        }
    }

    R.size_relation = len;

    //for (int i = 0;i < R.size_relation;i++) {
    //    std::cout << R.pairs[i].a << R.pairs[i].b << '\n';
    //}
    delete[] p;
   /* for (int y = 0;y < k;y++) {
        std::cout << nums[y];
    }*/
}
void symmetric_closing(Relation& R) {
    int size = R.size_relation;
    int count = 0;
    for (int i = 0;i < size;i++) {
        Pair sp = { R.pairs[i].b, R.pairs[i].a };
        if (!pair_in_array(R.pairs, size, sp))
        {
                count++;
        }
        
    }

    Pair* p = new Pair[size];

    for (int i = 0;i < size;i++) {
        p[i] = R.pairs[i];
    }

    R.pairs = new Pair[size + count];
    for (int i = 0;i < size;i++) {
        R.pairs[i] = p[i];
    }
    int len = size;
    for (int i = 0;i < size;i++) {
        Pair sp = { R.pairs[i].b, R.pairs[i].a };
        if (!pair_in_array(R.pairs, size, sp))
        {
            R.pairs[len++] = sp;
        }

    }
    R.size_relation = size + count;
    for (int u = 0;u < R.size_relation;u++) {
        std::cout << R.pairs[u].a << R.pairs[u].b << '\n';
    }
    delete[] p;
}

void transitive_closing(Relation& R) {
    int count = 0;
    int size = R.size_relation;
    for (int i = 0;i < size - 1;i++) {
        for (int j = i + 1;j < size;j++) {
            if (R.pairs[i].b == R.pairs[j].a) {
                count++;
            }
        }
    }
    //std::cout << count;
    Pair* pairs = new Pair[size];
    for (int i = 0;i < size;i++) {
        pairs[i] = R.pairs[i];
    }
    R.pairs = new Pair[size + count];
    for (int i = 0;i < size;i++) {
        R.pairs[i] = pairs[i];
    }
    int l = size;
    for (int i = 0;i < size - 1;i++) {
        for (int j = i + 1;j < size;j++) {
            if (R.pairs[i].b == R.pairs[j].a) {
                Pair p = { R.pairs[i].a, R.pairs[j].b };
                R.pairs[l++] = p;
            }
        }
    }
    R.size_relation = l;
   /* for (int i = 0;i < l;i++) {
        std::cout << R.pairs[i].a << R.pairs[i].b << '\n';
    }
    */

}
//zad 3

//int const MAX_SIZE = 1024 + 1;
struct Color {
    int red;
    int green;
    int blue;
};
void create_file(std::ofstream& file) {
    file.open("color_codes.txt");
    if (!file.is_open()) {
        return;
    }
    char b[] = "12465237|12465480|13465277";
    file << b;
    file.close();
}
int count_nums(char* code) {
    int count = 0;
    while (*code != '\0') {
        if (*code == '|') {
            count++;

        }
        code++;
    }
    return count + 1;
}
long* codes(char* text, int count) {
    int o = 0;
    long num = 0;
    long* nums = new long[count];
    while (*text) {

        while (*text != '\0' && *text != '|') {
            num = num * 10 + ((*text) - '0');

            text++;


        }
        nums[o++] = num;
        //std::cout<<num<<' ';
        num = 0;
        text++;



    }
    return nums;
}
int color_code(int R, int G, int B) {
    return (R * 65536) + (G * 256) + B;
}
//we create a function to find the exact number for the colors
void find_colors(Color& color, long num) {
    for (int i = 0;i < 255;i++) {
        for (int j = 0;j < 255;j++) {
            for (int h = 0;h < 255;h++) {
                if (color_code(i, j, h) == num) {
                    color.red = i;
                    color.green = j;
                    color.blue = h;
                    return;
                }
            }
        }
    }
    std::cout << "Colors not found!";
}
int size_of_color_array(std::ifstream& file) {
    file.open("color_codes.txt");
    if (!file.is_open()) {
        std::cout << "Cannot open the file!";
        return 0;
    }

    char buffer[MAX_SIZE];
    file.getline(buffer, MAX_SIZE, '\n');

    int count = count_nums(buffer);
    file.close();
    return count;
}
//we return an array of object of the struct Color
Color* transform_in_color(std::ifstream& file) {
    file.open("color_codes.txt");
    if (!file.is_open()) {
        std::cout << "Cannot open the file!";
        return 0;
    }

    char buffer[MAX_SIZE];
    file.getline(buffer, MAX_SIZE, '\n');

    int count = count_nums(buffer);

    Color* colors = new Color[count];
    long* nums = new long[count];
    nums = codes(buffer, count);
    for (int i = 0;i < count;i++) {
        find_colors(colors[i], nums[i]);

    }
    for (int i = 0;i < count;i++) {
        std::cout << colors[i].red << ' ' << colors[i].green << ' ' << colors[i].blue << '\n';
    }
    file.close();
    return colors;

}
//we get an array of colors and put their color codes in a file, called color_codes_1.txt
void write_in_file(std::ofstream& file, Color* colors, int size) {
    file.open("color_codes_1.txt");
    if (!file.is_open()) {
        return;
    }
    for (int i = 0;i < size;i++) {
        file << color_code(colors[i].red, colors[i].green, colors[i].blue);
        if (i != size - 1) {
            file << '|';
        }
    }
    file.close();

}
void write_in_file_only_red_colors(std::ofstream& file, Color* colors, int size) {
    file.open("red.txt");
    if (!file.is_open()) {
        return;
    }
    int count = 0;
    for (int i = 0;i < size;i++) {
        if (colors[i].red > 255) count++;
    }
    int l = 0;
    for (int i = 0;i < size;i++) {
        if (colors[i].red > 255) {
            file << color_code(colors[i].red, colors[i].green, colors[i].blue);
            l++;
            if (l < count) {
                file << '|';
            }
        }

    }
    file.close();

}
//zad 4
int len(const char* text) {
    int i = 0;
    while (*text != '\0') {
        text++;
        i++;
    }
    return i;
}
char* get_etiket(char* buffer, const char sub[]) {
    if (buffer == nullptr) {
        return 0;
    }
    //char title[MAX_SIZE];

    int size = len(buffer) - len(sub);
    char* word = new char[size];
    int idx = 0;
    buffer = buffer + len(sub);
    // std::cout<<len(sub);
    do {
        word[idx++] = *(buffer);
        buffer++;
    } while (*buffer != '\0');
    word[idx - 1] = '\0';

    // while(word[o]) std::cout<<word[o++];
    // for(int i = 0;i<idx;i++){
    //     std::cout<<word[i];

    // }
  //  std::cout<<'\n';

    return word;
}
void create_copy(std::ifstream& file, std::ofstream& copy_file) {
    file.open("shablon.txt");

    if (!file.is_open()) {
        return;
    }



    char buffer[MAX_SIZE];

    file.getline(buffer, MAX_SIZE, '\n');


    const char t[] = "title ";
    char* title = get_etiket(buffer, t);

    file.getline(buffer, MAX_SIZE, '\n');

    const char r[] = "recipient_name ";
    char* recipient_name = get_etiket(buffer, r);

    file.getline(buffer, MAX_SIZE, '\n');

    const char m[] = "message ";
    char* message = get_etiket(buffer, m);

    file.getline(buffer, MAX_SIZE, '\n');

    const char s[] = "sender_name ";
    char* sender_name = get_etiket(buffer, s);

    file.close();

    copy_file.open("shablon_copy.txt");
    if (!copy_file.is_open()) {
        return;
    }
    //std::cout<<
    copy_file << "Dear, " << title << ' ' << recipient_name << '.' << '\n';


    copy_file << message << '\n';
    copy_file << '\n';
    copy_file << "Sincerely," << '\n';
    copy_file << sender_name;

    delete[] title;
    delete[] recipient_name;
    delete[] sender_name;
    delete[] message;

    copy_file.close();
}

//zad 5
enum class Type
{ TV, SMARTPHONE, LAPTOP, PC, CAMERA };
size_t const MAX_SIZE_32 = 32;
size_t const MAX_SIZE_100 = 100;
struct Device {
    char name[MAX_SIZE_32];
    int quantity;
    double price;
    Type type_of_device;
    char deliver[MAX_SIZE_32];

};
struct Warehouse {
    Device devices[MAX_SIZE_100];
    char owner[MAX_SIZE_32];
    int number_of_devices;
};
Device create_device() {
    Device device;
    std::cout << "Name: "<<'\n';
    std::cin.ignore();
    std::cin.getline(device.name, MAX_SIZE_32);
    
    std::cout << "Quantity: ";
    std::cin >> device.quantity;
   
    std::cout << "Price: ";
    std::cin >> device.price;

    int t;
    std::cout << "Type: ";
    std::cin >> t;
    if (t < 0 || t > 4) {
        std::cout << "Invalid number - it must be between 0 and 4.";
        //return 0;
    }
    device.type_of_device = Type(t);
    
    std::cout << "Deliver: ";
    std::cin.ignore();
    std::cin.getline(device.deliver, MAX_SIZE_32);

    return device;
}
Warehouse create_warehouse() {
    std::cout << "Number of devices in warehouse: ";
    int number;
    std::cin >> number;
    if (number < 0|| number > 100) {
        std::cout << "Invalid number.";
    }
    Warehouse warehouse;
    std::cout << "Owner name: ";
    std::cin.ignore();
    std::cin.getline(warehouse.owner, MAX_SIZE_32);
    
    warehouse.number_of_devices = number;
    for (int i = 0;i < number;i++) {
        Device device = create_device();
        warehouse.devices[i] = device;
    }
    //std::cin.getline(warehouse.owner, MAX_SIZE_32);
    return warehouse;
}
//Sort functions for price
void swap_devices(Device& a, Device& b) {
    Device h = a;
    a = b;
    b = h;
}
void sort_devices_by_price(Warehouse& warehouse) {
    int size = warehouse.number_of_devices;
    for (int i = 0;i < size - 1;i++) {
        int minidx = i;
        for (int j = i + 1;j < size;j++) {
            if (warehouse.devices[i].price > warehouse.devices[j].price) {
                minidx = j;
            }
        }
        if (minidx != i) {
            swap_devices(warehouse.devices[minidx], warehouse.devices[i]);
        }
    }
    //finding the lowest and the highest price of a device in the warehouse
    /*Device min_price = warehouse.devices[0];
    Device max_price = warehouse.devices[size - 1];*/

    for (int i = 0;i < size;i++) {
        std::cout << warehouse.devices[i].price << ' ';
    }

}
void sort_devices_by_price_decreasing(Warehouse& warehouse) {
    int size = warehouse.number_of_devices;
    for (int i = 0;i < size - 1;i++) {
        int minidx = i;
        for (int j = i + 1;j < size;j++) {
            if (warehouse.devices[i].price < warehouse.devices[j].price) {
                minidx = j;
            }
        }
        if (minidx != i) {
            swap_devices(warehouse.devices[minidx], warehouse.devices[i]);
        }
    }
    

    for (int i = 0;i < size;i++) {
        std::cout << warehouse.devices[i].price << ' ';
    }

}
//functions finding the object with min and max price
Device min_price_device(Warehouse& warehouse) {
    sort_devices_by_price(warehouse);
    return warehouse.devices[0];
}
Device max_price_device(Warehouse& warehouse) {
    sort_devices_by_price(warehouse);
    return warehouse.devices[warehouse.number_of_devices - 1];
}
//Sort function for quantity
void sort_devices_by_quantity(Warehouse& warehouse) {
    int size = warehouse.number_of_devices;
    for (int i = 0;i < size - 1;i++) {
        int minidx = i;
        for (int j = i + 1;j < size;j++) {
            if (warehouse.devices[i].quantity > warehouse.devices[j].quantity) {
                minidx = j;
            }
        }
        if (minidx != i) {
            swap_devices(warehouse.devices[minidx], warehouse.devices[i]);
        }
    }
    for (int i = 0;i < size;i++) {
        std::cout << warehouse.devices[i].quantity << ' ';
    }

}
void sort_devices_by_quantity_decreasing(Warehouse& warehouse) {
    int size = warehouse.number_of_devices;
    for (int i = 0;i < size - 1;i++) {
        int minidx = i;
        for (int j = i + 1;j < size;j++) {
            if (warehouse.devices[i].quantity < warehouse.devices[j].quantity) {
                minidx = j;
            }
        }
        if (minidx != i) {
            swap_devices(warehouse.devices[minidx], warehouse.devices[i]);
        }
    }
 /*   for (int i = 0;i < size;i++) {
        std::cout << warehouse.devices[i].quantity << ' ';
    }*/

}
void print_type_device(Device d) {
    if (d.type_of_device == Type::TV) {
        std::cout << "TV";
    }
    else if (d.type_of_device == Type::PC) {
        std::cout << "PC";
    }
    else if (d.type_of_device == Type::CAMERA) {
        std::cout << "CAMERA";
    }
    else if (d.type_of_device == Type::LAPTOP) {
        std::cout << "LAPTOP";
    }
    else if (d.type_of_device == Type::SMARTPHONE) {
        std::cout << "SMARTPHONE";
    }
}
void print_device_info(Device d) {
    std::cout << "The device ";
    print_type_device(d);
    std::cout << " "<<d.name<< " has price "<<d.price<<"."<<'\n';
    std::cout << "Its quantity is " << d.quantity << " and it is delivered by " << d.deliver << '.'<<'\n';

}
void print_info_warehouse(Warehouse warehouse) {
    std::cout << "The owner of the warehouse is " << warehouse.owner <<'.'<<'\n';
    std::cout << "It has " << warehouse.number_of_devices <<" devices."<<'\n';
    for (int i = 0;i < warehouse.number_of_devices;i++) {
        print_device_info(warehouse.devices[i]);
    }

}
void write_all_products_in_file_of_type(int type, Warehouse w, std::ofstream& file) {
    file.open("type_device.txt");
    if (!file.is_open()) {
        std::cerr << "Cannot open the file.";
    }
    switch (type)
    {
    case 0: file << "TV"<<'\n';break;
    case 1: file << "SMARTPHONE" << '\n';break;
    case 2: file << "LAPTOP" << '\n';break;
    case 3: file << "PC" << '\n';break;
    case 4: file << "CAMERA" << '\n';break;
 

    }
    for (int i = 0;i < w.number_of_devices;i++) {
        if (w.devices[i].type_of_device == Type(type)) {
            
            file << "The device ";
            //print_type_device(d);
            file << w.devices[i].name << " has price " << w.devices[i].price << "." << '\n';
            file << "Its quantity is " << w.devices[i].quantity << " and it is delivered by " << w.devices[i].deliver << '.' << '\n';
        }

    }
    file.close();
   
}
int main()
{
    Device d;
    //d = create_device();
    //std::cout << d.name;
    //print_device_info(d);
    Warehouse w;
    w = create_warehouse();
    //print_info_warehouse(w);
    //sort_devices_by_price(w);
    int type = 2;
    std::ofstream v;
    write_all_products_in_file_of_type(type, w, v);
    /*std::ifstream file;
    std::ofstream file1;
    create_copy(file, file1);*/

    /*std::ofstream file;
    write_sum_in_file(file);
    std::ifstream file1;
    print_diff(file1);*/

    //Relation r;
   //create_relation(r, 5);
    //lexicographic_order(r);
   //reflexive_closing(r);
   //transitive_closing(r);
    
  /*  Pair p = { 3, 5 };
    Pair t = { 3, 3 };
    std::cout << is_bigger_pair(p, t);*/

   /* std::ofstream file;
    writeRelationToFile(file, r);

    std::ifstream file1;
    readRelationFromFile(file1);*/
   // addPairToRelation(r, p);
    return 0;
}
