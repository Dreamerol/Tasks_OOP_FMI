

#include <iostream>
#include <fstream>
struct Block{
    int16_t next;
    int16_t textlen;
    char symbol;
};

void print_sentence(std::ifstream& ifs){
if(!ifs){
      return;
  }
  
  int curidx = 0;
  while(true){
      Block b;
       ifs.seekg(curidx * sizeof(Block), std::ios::beg);
       ifs.read((char*)&b, sizeof(Block));
       if(b.next == -1){
           break;
       }
       curidx = b.next;
       std::cout<<b.symbol;
  }
  ifs.close();
    
}
int main()
{
    
  Block b1 = {4, 3, 'a'};
  Block b2 = {0, 6, 'b'};
  Block b3 = {5, 3, 'c'};
  Block b4 = {3, 5, 'd'};
  Block b5 = {2, 2, 'f'};
  Block b6 = {-1, 8, 'l'};
  
  std::ofstream file("blocks.bin", std::ios::binary);
  
  if(!file){
      return 0;
  }
  
  file.write((const char*)&b1, sizeof(Block));
  file.write((const char*)&b2, sizeof(Block));
  file.write((const char*)&b3, sizeof(Block));
  file.write((const char*)&b4, sizeof(Block));
  file.write((const char*)&b5, sizeof(Block));
  file.write((const char*)&b6, sizeof(Block));
  
  file.close();
  
  std::ifstream ifs("blocks.bin", std::ios::binary);
  print_sentence(ifs);
  
  return 0;

    
}
