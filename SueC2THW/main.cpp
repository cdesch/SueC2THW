//
//  main.cpp
//  SueC2THW
//
//  Created by cj on 4/27/15.
//  Copyright (c) 2015 KickinEspresso. All rights reserved.
//

#include <iostream>
#include "string.h"
#include <cassert>
#include <algorithm>
using namespace std;


class Animal{
    
protected:
    string name;
    string species;
    int birthYear;
    int weight;
public:
    Animal(){
        this->name = "";
        this->species = "";
        this->birthYear = 0;
        this->weight = 0;
    }
    
    Animal(string name, string species, int birthYear, int weight){
        this->name = name;
        this->species = species;
        this->birthYear = birthYear;
        this->weight = weight;
    }
    
    //setters and getters
    string getName() const { return this->name;};
    string getSpecies() const { return this->species;};
    int getBirthYear() const { return this->birthYear;};
    int getWeight() const { return this->weight;};
    
    void setName(string name){this->name = name;};
    void setSpecies(string species){this->species = species;};
    void setBirthYear(int birthYear){this->birthYear = birthYear;};
    void setWeight(int weight){this->weight = weight;};
    
    bool operator==(const Animal& object){
        return (this->getName() == object.getName()) ? true : false;
    }

};

template<class Element>
class Farm{
    
protected:
    string name;
    string owner;
    string location;
    int size;
    Element* items;
    
public:
    Farm(){
        this->name = "";
        this->owner = "";
        this->location = "";
        this->size = 0;
    }
    
    Farm(string name, string owner, string location){
        this->name = name;
        this->owner = owner;
        this->location = location;
        this->size = 0;
    }
    
    //setters and getters
    string getName(){ return this->name;};
    string getOwner(){ return this->owner;};
    string getLocation(){ return this->location;};
    int getSize(){ return this->size;};
    
    void setName(string name){this->name = name;};
    void setOwner(string owner){this->owner = owner;};
    void setLocation(string location){this->location = location;};
    
    void addAnimal(string name, string species, int birthYear, int weight){
        Animal* animal = new Animal( name,  species,  birthYear,  weight);
        this->addItem(animal);
    }
    
    void addItem(Element* item){
        //Copy the existing array or initialize it if the size is 0
        if(this->size == 0){
            this->items = new Element[this->size++];
        }else{
            Element* newItemsArray = new Element[this->size + 1];
            copy(this->items, this->items + min(this->size, this->size + 1), newItemsArray);
            delete[] this->items;
            this->items = newItemsArray;
            this->size++;
        }
        //Add the item
        this->items[this->size-1] = *item;
    }
    
    void removeItem(Element* item){
        if(this->size > 0){
            //TODO: Should find the element before removing it. If the element is not in the array the remove will fail: newItemsArray, this->size, data loss

            Element* newItemsArray = new Element[this->size - 1];
            remove_copy(this->items, this->items + this->size, newItemsArray, *item);
            delete[] this->items;
            this->items = newItemsArray;
            this->size--;
        }else{
            cout << "Nothing in the array to remove" << endl;
        }
    }
    
    int count(string speciesType){
        int count = 0;
        for (int i = 0; i < this->size; i++){
            Animal* animal  = & this->items[i];
            if (animal->getSpecies() == speciesType) count ++;
        }
        return count;
    }

};

string nameOf(Farm<Animal>* farm){
    return (farm) ? farm->getName() : "";
}

void testCase(){
    Farm<Animal>* browns = new Farm<Animal>("Circle-K", "Mr Brown", "Ohio");
    Farm<Animal>* als = new Farm<Animal>("Al’s Piggery", "Mr Brown", "Ohio");
    Farm<Animal>* mcds = new Farm<Animal>("EIEIOK Corral", "Mrs McDonald", "New Mexico");
    Farm<Animal>* joes = new Farm<Animal>("Disneyland", "Joe Disney", "Mozambique");
    
    mcds->addAnimal("Dolly", "Sheep", 1981, 140);
    als->addAnimal("Sue", "Pig", 2009, 56);
    joes->addAnimal("Bessy", "Cow", 2011, 522);
    als->addAnimal("Brenda", "Cow", 2008, 490);
    mcds->addAnimal("Mootilda", "Cow", 2010, 577);
    browns->addAnimal("Xerxes", "Chicken", 2014, 7);
    als->addAnimal("Typhoid Mary", "Chicken", 2013, 8);
    browns->addAnimal("Clucky", "Chicken", 2013, 6);
    als->addAnimal("Oinky", "Pig", 2008, 94);
    browns->addAnimal("Neddy", "Horse",  2005, 450);
    mcds->addAnimal("Snorty", "Horse", 1991, 555);
    // etc.
    cout << nameOf(mcds) << " has " << mcds->count("Cow")  << " cows\n";
    cout << nameOf(browns) << " has " << browns->count("Chicken")  << " chickens\n";
    
    Animal* Mootilda = new Animal("Mootilda", "Cow", 2010, 577);
    Animal* Snorty = new Animal("Snorty", "Horse", 1991, 555);
    assert(*Mootilda == *Mootilda);
    assert(!(*Mootilda == *Snorty));
    
    mcds->removeItem(Mootilda);
    cout << nameOf(mcds) << " has " << mcds->count("Cow")  << " cows\n";
}


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    testCase();
    return 0;
}
