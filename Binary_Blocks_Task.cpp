

#include <iostream>
#include <fstream>
#include <sstream>
struct Block{
    int16_t next;
    int16_t textlen;
    char symbol;
};


int count_blocks(std::ifstream& ifs){
   
   if(!ifs){
       
      return 0;
   }
  
  int curidx = 0;
  int count = 0;
  while(true){
      
      Block b;
      count++;
       ifs.seekg(curidx * sizeof(Block), std::ios::beg);
       ifs.read((char*)&b, sizeof(Block));
       if(b.next == -1){
           break;
       }
       curidx = b.next;
       
  }
  ifs.close();
  return count;
    
}
void print_sentence(std::ifstream& ifs, std::stringstream& ss, Block* blocks){
if(!ifs){
    
      return;
  }
  ifs.seekg(0, std::ios::beg);
  int curidx = 0;
  int i =0;
  while(true){
      Block b;
       ifs.seekg(curidx * sizeof(Block), std::ios::beg);
       ifs.read((char*)&b, sizeof(Block));
       if(b.next == -1){
           break;
       }
       blocks[i] = b;
       curidx = b.next;
       i++;
       //ss<<b.symbol;
  }
  for(int j = 0;j<i;j++){
      ss << blocks[j].symbol;
  }
  std::cout<<ss.str().c_str();
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
  std::stringstream ss("");
 int count = count_blocks(ifs);
 std::cout<<count;
  ifs.close();
  
 Block* blocks = new Block[count];
 std::ifstream ifs1("blocks.bin", std::ios::binary);
  print_sentence(ifs1, ss, blocks);
  ifs1.close();
  delete[] blocks;
  return 0;

    
}
