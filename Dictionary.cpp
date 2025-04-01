class Dictionary{
    Word* words=nullptr;
    int size=0;
    int capacity=10;
    
    public:
    void lexicographicOrder();
    void swap(Word& a, Word& b);
    bool are_the_same(const char* word1, const char* word2);
    Dictionary() = default;
    Dictionary(const Dictionary& other);
    Dictionary& operator = (const Dictionary& other);
    ~Dictionary();
    Word* getWords() const;
    void setWords(Word* words);
    void add_word(Word word);
    bool wordInDictionary(Word word);
    Word& getWordByIndex() const;
    void read_from_file(const char* filename);
    void write_in_file(const char* filename);
    
    private:
    void free();
    void copyFrom(const Dictionary& other);
    void reSize();
};

class Word{
  char* word=nullptr;
  public:
  Word() = default;
  Word(const char* word);
  Word(const Word& other);
  Word& operator=(const Word& other);
  ~Word();
  const char* getWord() const;
  int getLen() const;
  void setWord(const char* word);
  
  private:
  void free();
  void copyFrom(const Word& other);
};



#include "Word.h"
#include "Dictionary.h"

#include <fstream>
#include <cstring>
#include <iostream>

Word::Word(const char* word){
    setWord(word);
}
Word::Word(const Word& other){
    copyFrom(other);
}
Word& Word::operator=(const Word& other){
    if(this != &other){
        free();
        copyFrom(other);
    }
    return *this;
}
Word::~Word(){
    free();
}
const char* Word::getWord() const{
      return word;
  }
void Word::setWord(const char* word){
      if(word == nullptr){
          return;
      }
      if(this->word == word){
          return;
      }
      delete[] this->word;
      this->word = new char[strlen(word) + 1];
      strcpy(this->word, word);
}
void Word::copyFrom(const Word& other){
    this->word = new char[strlen(other.getWord()) + 1];
    strcpy(this->word, other.word);
}
void Word::free(){
    if(this->word == nullptr){
        return;
    }
    delete[] this->word;
    this->word = nullptr;
}
int Word::getLen() const{
    return strlen(word);
}
Dictionary::Dictionary(const Dictionary& other){
    copyFrom(other);
}
    Dictionary& Dictionary::operator = (const Dictionary& other){
        if(this!=&other){
            free();
            
            copyFrom(other);
        }
        return *this;
    }
    Dictionary::~Dictionary(){
        free();
    }
    Word* Dictionary::getWords() const{
        return words;
    }
    void Dictionary::setWords(Word* words, int size){
        this->size = size;
        if(this->words != nullptr){
            delete[] this->words;
        }
        this->words = new Word[size];
        for(int i = 0;i<size;i++){
            this->words[i] = words[i];
        }
    }
    void Dictionary::add_word(const Word& word){
        if(wordInDictionary(word)){
            return;
        }
        if(size + 1 > capacity){
            reSize();
        }
        std::cout<<word.getWord();
        words[this->size++] = word;
        
        
    }
    void Dictionary::swap_words(Word& a, Word& b){
        Word h = a;
        a = b;
        b = h;
    }
    int compare(const char* word1, const char* word2){
        if(word1 == nullptr || word2 == nullptr){
            return -129;
        }
        while(*word1 || *word2){
            if((*word1) != (*word2)){
                return (*word1 - *word2);
            }
            word1++;
            word2++;
        }
        return 0;
    }
    void Dictionary::lexicographicOrder(){
        for(int i = 0;i<size-1;i++){
            int minidx = i;
            for(int j = i+1;j<size;j++){
                if(compare(words[i].getWord(), words[j].getWord()) > 0){
                    minidx = j;
                }
            }
            if(minidx != i){
                swap_words(words[i], words[minidx]);
            }
        }
    }
    bool Dictionary::are_the_same(const char* word1, const char* word2){
        while(*word1 || *word2){
            if(*word1 != *word2){
                return 0;
            }
            word1++;
            word2++;
        }
        return 1;
    }
    bool Dictionary::wordInDictionary(Word word){
        for(int i = 0;i<size;i++){
            if(are_the_same(word.getWord(), words[i].getWord())){
                return 1;
            }
        }
        return 0;
    }
    Word* Dictionary::getWordByIndex(int idx) const{
        if(idx < 0 || idx > size -1){
            return nullptr;
        }
        return &this->words[idx];
    }
    void Dictionary::read_from_file(const char* filename){
        std::ifstream file(filename, std::ios::binary);
        if(!file){
            return;
        }
        file.read((char*)&this->size, sizeof(int));
        delete[] words;
        this->words = new Word[this->size];
        for(int i = 0;i<size;i++){
            int len;
            file.read((char*)&len, sizeof(int));
            const char* word = new char[len+1];
            words[i].setWord(word);
            for(int j = 0;j<words[i].getLen();j++){
                file.read((char*)&words[i].getWord()[j], sizeof(char));
            }
        }
        file.close();
    }
    void Dictionary::print(){
        for(int i = 0;i<this->size;i++){
            std::cout<<words[i].getWord()<<' ';
        }
    }
    void Dictionary::write_in_file(const char* filename){
        std::ofstream file(filename, std::ios::binary);
        if(!file){
            return;
        }
        file.write((const char*)&this->size, sizeof(int));
        for(int i = 0;i<size;i++){
            int l = words[i].getLen();
            file.write((const char*)&l, sizeof(int));
            for(int j = 0;j<words[i].getLen();j++){
                file.write((const char*)&words[i].getWord()[j], sizeof(char));
            }
        }
        file.close();
    }
    
    
    void Dictionary::free(){
        if(words == nullptr){
            return;
        }
        delete[] words;
        words = nullptr;
    }
    void Dictionary::copyFrom(const Dictionary& other){
        this->size = other.size;
        this->capacity = other.capacity;
        this->words = new Word[this->size];
        for(int i = 0;i<this->size;i++){
            this->words[i] = other.words[i];
        }
        
    };
    void Dictionary::reSize(){
        if(this->size >= this->capacity){
            Word* helper = new Word[this->capacity *= 2];
            for(int i = 0;i<size;i++){
                helper[i] = this->words[i];
            }
            delete[] this->words;
            this->words = helper;
        }
    }
int main()
{
    Word w1;
    w1.setWord("jshhs");
    Word w2;
    w2.setWord("abcd");
    Word w3;
    w3.setWord("lxklx");
    Word w4;
    w4.setWord("lolo");
 
    Dictionary di;
    di.add_word(w1);
    di.add_word(w2);
    di.add_word(w3);
    
    di.add_word(w4);
    di.lexicographicOrder();
    di.print();

    return 0;
}
