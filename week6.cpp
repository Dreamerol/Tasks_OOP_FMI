// week6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//zad 1
#include <iostream>
#include <cstring>
#pragma warning(disable:4996)
constexpr int MAX_LEN_EFFECT = 100;
constexpr int MAX_LEN_NAME = 25;
enum class Type_Card {
    trap,
    buff,
    spell,
    Default,
};
class Monster_Card {
    char* name;
    size_t points_attack;
    size_t points_defense;

public:
    Monster_Card() : name(nullptr), points_attack(0), points_defense(0) {};
    Monster_Card(const char* name, size_t points_attack, size_t points_defense) {
        setName(name);
        setPointsAttack(points_attack);
        setPointsDefense(points_defense);
    }
    void setName(const char* name) {
        if (name == nullptr) {
            return;
        }
        if (name == this->name) {
            return;
        }
        if (this->name != nullptr) {
            delete[] this->name;
        }
        strcpy(this->name, name);
    }
    void setPointsAttack(size_t points_attack) {
        if (points_attack < 0) {
            return;
        }
        this->points_attack = points_attack;
    }
    void setPointsDefense(size_t points_defense) {
        if (points_defense < 0) {
            return;
        }
        this->points_defense = points_defense;
    }
    size_t getPointsAttack() const {
        return points_attack;
    }
    size_t getPointsDefense() const {
        return points_defense;
    }
    const char* getName() const {
        return name;
    }
    Monster_Card(const Monster_Card& other) {
        copyFrom(other);
    }

    Monster_Card& operator=(const Monster_Card& other) {
        if (this != &other) {
            free();
            copyFrom(other);
        }
        return *this;
    }

    ~Monster_Card() {
        free();
    }

private:
    void free() {
        if (this->name == nullptr) {
            return;
        }
        delete[] this->name;
        this->name = nullptr;
    }
    void copyFrom(const Monster_Card& other) {
        this->points_attack = other.points_attack;
        this->points_defense = other.points_defense;
        this->name = new char[strlen(other.name) + 1];
        setName(other.name);

    }

};
class Magic_Card {
    Type_Card type_card;
    char name[MAX_LEN_NAME];
    char effect[MAX_LEN_EFFECT];

public:
    Magic_Card() : type_card(Type_Card::Default), name(""), effect("") {};

    Magic_Card(Type_Card card, const char* name, const char* effect) {
        setEffect(effect);
        setName(name);
        setTypeCard(card);
    }
    const char* getName() const {
        return this->name;
    }
    const char* getEffect() const {
        return this->effect;
    }
    Type_Card getTypeCard() const {
        return this->type_card;
    }

    void setName(const char* name) {
        if (name == nullptr) {
            return;
        }
        if (strlen(name) > MAX_LEN_NAME) {
            return;
        }
        strcpy(this->name, name);
    }

    void setEffect(const char* effect) {
        if (effect == nullptr) {
            return;
        }
        if (strlen(effect) > MAX_LEN_EFFECT) {
            return;
        }
        strcpy(this->effect, effect);
    }

    void setTypeCard(Type_Card card) {
        this->type_card = card;
    }


};
class Deck {
    Magic_Card magic_cards[20];
    Monster_Card monster_cards[20];
    size_t monster_cards_count=0;
    size_t magic_cards_count=0;
    
public:
    size_t getMonsterCardsCount() const {
        return monster_cards_count;

    }
    size_t getMagicCardsCount() const {
        return magic_cards_count;

    }
    void addMagicCard(const Magic_Card& card) {
        if (magic_cards_count + 1 > 20) {
            return;
        }
        magic_cards[magic_cards_count++] = card;
    }
    void addMonsterCard(const Monster_Card& card) {
        if (monster_cards_count + 1 > 20) {
            return;
        }
        monster_cards[monster_cards_count++] = card;
    }
    void new_magic_card_by_idx(const Magic_Card& card, size_t idx) {
        if (idx < 0 || idx >= magic_cards_count|| idx >= 20) {
            return;
        }
        magic_cards[idx] = card;
    }
    void new_monster_card_by_idx(const Monster_Card& card, size_t idx) {
        if (idx < 0 || idx >= monster_cards_count ||idx >= 20) {
            return;
        }
        //check if the card is there

        monster_cards[idx] = card;
    }
    
    void remove_monster_card(int idx) {
        if (idx < 0 || idx >=monster_cards_count) {
            return;
        }
        Monster_Card* cards_helper = new Monster_Card[monster_cards_count - 1];
        int l = 0;
        for (int i = 0;i < monster_cards_count;i++) {
            if (i == idx) {
                continue;
            }
            cards_helper[l++] = monster_cards[i];
        }
        monster_cards_count--;
        for (int i = 0;i < monster_cards_count;i++) {
            monster_cards[i] = cards_helper[i];
        }

        delete[] cards_helper;
    }
    void remove_magic_card(int idx) {
        if (idx < 0 || idx >= magic_cards_count) {
            return;
        }
        Magic_Card* cards_helper = new Magic_Card[magic_cards_count - 1];
        int l = 0;
        for (int i = 0;i < magic_cards_count;i++) {
            if (i == idx) {
                continue;
            }
            cards_helper[l++] = magic_cards[i];
        }
        magic_cards_count--;
        for (int i = 0;i < magic_cards_count;i++) {
            magic_cards[i] = cards_helper[i];
        }

        delete[] cards_helper;
    }
};

class Duelist {
    char* name=nullptr;
    Deck deck;

public:
    Duelist() = default;
    Duelist(const char* name, Deck d) {
        setDeck(d);
        setName(name);
    }
    void setDeck(Deck d) {
        deck = d;
    }
    void setName(const char* name) {
        if (name == nullptr) {
            return;
        }
        if (this->name == name) {
            return;
        }
        if (this->name != nullptr) {
            delete[] this->name;
        }
        strcpy(this->name, name);
        
    }

    Duelist(const Duelist& other) {
        copyFrom(other);
    }
    Duelist& operator=(const Duelist& other) {
        if (this != &other) {
            free();
            copyFrom(other);
        }
        return *this;
    }
    ~Duelist() {
        free();
    }

    void addMagicCardDuelist(Magic_Card& card) {
        this->deck.addMagicCard(card);
    }
    void addMagicCardByIdx(Magic_Card& card, int idx) {
        this->deck.new_magic_card_by_idx(card, idx);
    }
    void removeMagicCardByIdx(Magic_Card& card, int idx) {
        this->deck.remove_magic_card(idx);
    }
    void addMonsterCardDuelist(Monster_Card& card) {
        this->deck.addMonsterCard(card);
    }
    void addMonsterCardByIdx(Monster_Card& card, int idx) {
        this->deck.new_monster_card_by_idx(card, idx);
    }
    void removeMonsterCardByIdx(Monster_Card& card, int idx) {
        this->deck.remove_monster_card(idx);
    }
    private:
        void copyFrom(const Duelist& other) {
            setName(other.name);
            deck = other.deck;
        }

        void free() {
            if (name == nullptr) {
                return;
            }
            delete[] this->name;
            this->name = nullptr;
        }

};

//zad 2


#include <iostream>
class Town {
    int id;

public:
    Town() : id(0) {};
    Town(int id) {
        setId(id);
    }
    void setId(int id) {
        if (id < 0) {
            return;
        }
        this->id = id;
    }
    int getId() const {
        return id;
    }
};
class Way {
    Town* towns = nullptr;
    int number_of_towns = 0;

public:
    Way() = default;
    Way(Town* towns, int n) {
        setTownsCount(n);
        setTowns(towns);
    }
    void setTownsCount(int n) {
        number_of_towns = n;
    }
    void setTowns(Town* towns) {
        if (towns == nullptr) {
            return;
        }
        if (towns == this->towns) {
            return;
        }
        if (towns != nullptr) {
            delete[] towns;
        }
        this->towns = new Town[number_of_towns];
        for (int i = 0;i < number_of_towns;i++) {
            this->towns[i] = towns[i];
        }
    }
    Way(const Way& other) {
        copyFrom(other);
    }
    Way& operator = (const Way& other) {
        if (this != &other) {
            free();
            copyFrom(other);
        }
        return *this;
    }
    ~Way() {
        free();
    }
    int getTownsCount() const {
        return number_of_towns;
    }
    void addTown(Town t) {
        Town* helper = new Town[number_of_towns];
        for (int i = 0;i < number_of_towns;i++) {
            helper[i] = towns[i];
        }
        towns = new Town[number_of_towns + 1];
        for (int i = 0;i < number_of_towns;i++) {
            towns[i] = helper[i];
        }
        towns[number_of_towns++] = t;
        delete[] helper;
    }
    int removeIdx(int id) {
        for (int i = 0;i < number_of_towns;i++) {
            if (towns[i].getId() == id) {
                return i;
            }
        }
        return -1;
    }
    bool townInWay(int id) {
        for (int i = 0;i < number_of_towns;i++) {
            if (towns[i].getId() == id) {
                return 1;
            }
        }
        return 0;
    }
    void removeTown(int id) {
        int idx = removeIdx(id);
        if (idx == -1) {
            return;
        }
        Town* helper = new Town[number_of_towns];
        for (int i = 0;i < number_of_towns;i++) {
            helper[i] = towns[i];
        }
        towns = new Town[number_of_towns - 1];
        int l = 0;
        for (int i = 0;i < number_of_towns;i++) {
            if (i == idx) {
                return;
            }
            towns[l++] = helper[i];
        }
        delete[] helper;

    }
    void union_ways(Town* towns1, int number_of_towns1) {
        Town* helper = new Town[number_of_towns];
        for (int i = 0;i < number_of_towns;i++) {
            helper[i] = towns[i];
        }
        towns = new Town[number_of_towns + number_of_towns1];
        for (int i = 0;i < number_of_towns;i++) {
            towns[i] = helper[i];
        }
        for (int j = 0;j < number_of_towns1;j++) {
            towns[number_of_towns + j] = towns1[j];
        }
        delete[] helper;
    }
    void section_ways(Town* towns1, int number_of_towns1) {
        int count = 0;
        for (int i = 0;i < number_of_towns;i++) {
            for (int j = 0;j < number_of_towns1;j++) {
                if (towns[i].getId() == towns1[j].getId()) {
                    count++;
                }
            }
        }
        Town* helper = new Town[count];
        int l = 0;
        for (int i = 0;i < number_of_towns;i++) {
            for (int j = 0;j < number_of_towns1;j++) {
                if (towns[i].getId() == towns1[j].getId()) {
                    helper[l++] = towns[i];
                }
            }
        }
        towns = new Town[count];
        for (int i = 0;i < count;i++) {
            towns[i] = helper[i];
        }
        delete[] helper;
    }
    bool towns_in_two_ways(Town* towns1, int number_of_towns1) {
        int count = 0;
        for (int i = 0;i < number_of_towns;i++) {
            for (int j = 0;j < number_of_towns1;j++) {
                if (towns[i].getId() == towns1[j].getId()) {
                    return 1;
                }
            }
        }
        return 0;
    }
    void swap(Town& a, Town& b) {
        Town help = a;
        a = b;
        b = help;
    }
    void SelectionSort() {
        for (int i = 0;i < number_of_towns - 1;i++) {
            int minidx = i;
            for (int j = 0;j < number_of_towns;j++) {
                if (towns[i].getId() > towns[j].getId()) {
                    minidx = j;
                }
            }
            if (minidx != i) {
                swap(towns[minidx], towns[i]);
            }
        }
    }
    bool town_in_way(Town town) {
        SelectionSort();
        for (int i = 0;i < number_of_towns;i++) {
            if (town.getId() == towns[i].getId()) {
                return 1;
            }
        }
        return 0;
    }
    int* array_ids() {
        int* array = new int[number_of_towns];
        for (int i = 0;i < number_of_towns;i++) {
            array[i] = towns[i].getId();
        }
        return array;
    }
    bool any_towns() {
        return (number_of_towns > 0);
    }
private:
    void free() {
        if (towns == nullptr) {
            return;
        }
        delete[] towns;
        towns = nullptr;
    }
    void copyFrom(const Way& other) {
        setTownsCount(other.number_of_towns);
        setTowns(other.towns);
    }

};

int main()
{

}

