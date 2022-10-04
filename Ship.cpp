/*
File Name: Ship.cpp
Assignent Name: CMSC 202 Project 2 - No Man's Alchemy
Author's Name: Toni Olafunmiloye
Date: March 13, 2021
Section: 53
Email: oolafun1@umbc.edu
Description: Ship.cpp handles the Ship.h functions, setting up the qualities of the ship (name, rank, materials)
*/


#include "Ship.h"
#include "Material.h"


// Name: Ship() - Default Constructor
// Desc: Used to build a new Player Ship
// Preconditions - Requires default values
// Postconditions - Creates a new Player Ship

Ship::Ship() {
    
    SetName("Player-Ship");
    m_shipRank = 'D';
    m_numMaterials = 0;
}


// Name: Ship(name) - Overloaded constructor
// Desc - Used to build a new Player Ship
// Preconditions - Requires name
// Postconditions - Creates a new Player Ship

Ship::Ship(string name) {
    SetName(name);
}


// Name: GetName()
// Desc - Getter for the Player Ship's name
// Preconditions - Player Ship exists
// Postconditions - Returns the name of the Player Ship

string Ship::GetName() {
    return m_shipName;
}


// Name: SetName(string)
// Desc - Allows the user to change the name of the Player Ship
// Preconditions - Player Ship exists
// Postconditions - Sets name of Player Ship
void Ship::SetName(string name) {
    m_shipName = name;
}


// Name: CheckMaterial(Material)
// Desc - Checks to see if the Ship has a material
// Preconditions - Ship already has materials
// Postconditions - Returns index of material if the Ship has it else -1

int Ship::CheckMaterial(Material material) {
    // loop through the list to see if it has the material, if so return the index
    for(int i = 0; i < PROJ2_SIZE; i++) {
        if(material.m_name == m_myMaterials[i].m_name) {
            return i;
        }
        
    } return -1;
}


// Name: AddMaterial(string)
// Desc - Inserts a material into the Ship's list of materials
// Preconditions - Ship exists
// Postconditions - Add a material to the Ship's m_myMaterials with a quantity of 1

void Ship::AddMaterial(Material material) {
    // check if the material in is the list, if not, add it in
    int value = CheckMaterial(material);
    if(value == -1){
        m_myMaterials[m_numMaterials] = material;
        m_numMaterials++;
    }
}


// Name: IncrementQuantity(Material)
// Desc - Adds quantity to list of materials the Ship knows
// Preconditions - Ship exists
// Postconditions - Increases quantity of material for the Ship

void Ship::IncrementQuantity(Material material) {
    int index = CheckMaterial(material);
    if(index >= 0)
        m_myMaterials[index].m_quantity++;
        
    
}


// Name: DecrementQuantity(Material)
// Desc - Reduces quantity from the Ship's inventory with true, if no quantity false
// Preconditions - A Ship exists
// Postconditions - Reduces quantity of material for the Ship

bool Ship::DecrementQuantity(Material material) {
    int index = CheckMaterial(material);
    if(index >= 0) {
        if(m_myMaterials[index].m_quantity > 0) {
            m_myMaterials[index].m_quantity--;
            return true;
        } else {
            return false;
        }
    } else {
            return false;
        }
    
}


// Name: CheckQuantity(Material)
// Desc - Checks to see if quantity of two merge materials are available
// Preconditions - Ship exists with materials
// Postconditions - Returns true if both are available (including two of same material)

bool Ship::CheckQuantity(Material material1, Material material2) {
    // first check if the materials are even in the list
    int index1 = CheckMaterial(material1);
    int index2 = CheckMaterial(material2);

    if(index1 == -1 || index2 == -1) {
        return false;
    }
    
    // if its in the list, and both quantities are greater than 1, then both materials can be used
    if(m_myMaterials[index1].m_quantity > 0) {
        if(m_myMaterials[index2].m_quantity > 0) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}


// Name: GetMaterial(int)
// Desc - Checks to see if the Ship has any materials
// Preconditions - The Ship already has materials
// Postconditions - Returns material at specific index

Material Ship::GetMaterial(int i) {
    return m_myMaterials[i];
}


// Name: IncRank()
// Desc - Increments the rank of the ship to the next rank.
// Preconditions - Ship exists and has a rank
// Postconditions - m_shipRank will move to the next character

void Ship::IncRank() {
    // ok so when this function is called, itll check the shiprank and whatever letter is next is what it'll change the rank to
    switch (m_shipRank) {
        case 'D':
            m_shipRank = 'C';
            break;
        case 'C':
            m_shipRank = 'B';
            break;
        case 'B':
            m_shipRank = 'A';
            break;
        case 'A':
            m_shipRank = 'S';
            cout << endl;
            cout << "Congratulations! You've reached the ultimate ship rank! You Won!" << endl;
            cout << "Ship Rank: " << GetRank() << endl;
            break;
    }
}


// Name: GetRank()
// Desc - Checks to see what the current ship's rank is
// Preconditions - The ship exists
// Postconditions - Returns the character indicating the rank of the ship

char Ship::GetRank() {
    return m_shipRank;
}

