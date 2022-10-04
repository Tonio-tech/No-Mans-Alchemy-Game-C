#include "Game.h"
#include "Ship.h" // do i need this?
#include "Material.h"


Game::Game() {
    string name;

    GameTitle();

    cout << endl;

    // load materials
    LoadMaterials();

    // ask for name of ship and set the name
    cout << "What is the name of your ship? " << endl;
    getline(cin, name);
    m_myShip.SetName(name);

    //copies materials
    for(int i = 0; i < PROJ2_SIZE; i++) {
        m_myShip.AddMaterial(m_materials[i]); 
    }
}

void Game::LoadMaterials() {
    fstream dataFile;
    string data;

    string name;
    string type;
    string material1;
    string material2;

    dataFile.open(PROJ2_DATA);

    if(dataFile.is_open()) {

    // do a for loop with the pattern being name, type, material1, material2
        for(int i = 0; i < PROJ2_SIZE; i++) {
            getline(dataFile, name, ',');
            getline(dataFile, type, ',');
            getline(dataFile, material1, ',');
            getline(dataFile, material2);
            m_materials[i] = Material(name, type, material1, material2, 0);

            // if(m_materials[i].m_type == "raw") {
            // m_materials[i].m_quantity = 100;
            // }
        }

        cout << PROJ2_SIZE << " materials loaded." << endl;
    }

    dataFile.close();
}

void Game::StartGame() {
    int choice;
    // keep playing until the hit quit or until they get the highest ship rank
    do {
        choice = MainMenu();
    } while(choice != 5 && m_myShip.GetRank() != 'S');

    if(choice == 5) {
        cout << "Thanks for playing!" << endl;
    }
}

void Game::DisplayMaterials() {
    int counter = 1;

    // list will start at one and wil display the material name and quantity
    for(int i = 0; i < PROJ2_SIZE; i++) {
        cout << counter << ".  " << m_myShip.GetMaterial(i).m_name << " " << m_myShip.GetMaterial(i).m_quantity << endl;
        counter++;
    }
    cout << endl;
}

int Game::MainMenu() {
    int choice;
    
    // print out the menu and unless they hit 5 or get ship rank S, keep going
    cout << endl;
    do{
        cout << "What would you like to do?" << endl;
        cout << "1. Display your Ship's Materials \n" 
             << "2. Search for Raw Materials \n"
             << "3. Attempt to Merge Materials \n"
             << "4. See Score \n"
             << "5. Quit \n" << endl;

        cin >> choice;

        if(choice == ONE) {
            DisplayMaterials();
        }

        if(choice == TWO) {
            SearchMaterials();
        }

        if(choice == THREE) {
            CombineMaterials();
        }

        if(choice == FOUR) {
            CalcScore();
        }

    } while(choice != 5 && m_myShip.GetRank() != 'S');

    return choice;
}

void Game::SearchMaterials() {
    int rawMaterialsSize = 0;

    // randomly search throught the materials labeled "raw" and pick anyone and then increase its quantity
    for(int i = 0; i < PROJ2_SIZE; i++) {
        if(m_myShip.GetMaterial(i).m_type == "raw") {
            rawMaterialsSize++;
        }
    }

    int randNum = rand() % rawMaterialsSize + 0;

    cout << "You found " << m_myShip.GetMaterial(randNum).m_name << "!" << endl;
    m_myShip.IncrementQuantity(m_myShip.GetMaterial(randNum)); 
}

void Game::CombineMaterials() {
    int choice1 = 0; 
    int choice2 = 0; 
    int index = 0;

    // ask for the material twice, then check if its in the list
    cout << "Which materials would you like to merge?" << endl
            << "To list known materials enter -1" << endl;

    cin >> choice1;
    RequestMaterial(choice1);
    

    cout << "Which materials would you like to merge?" << endl
            << "To list known materials enter -1" << endl;

    cin >> choice2;
    RequestMaterial(choice2);

    // valgrind -s --track-origins=yes ./proj2

    // check if they have enough materials
    if(m_myShip.CheckQuantity(m_materials[choice1], m_materials[choice2]) == false) {
        cout << "You do not have enough " << m_materials[choice1].m_name << " or " << m_materials[choice2].m_name
            << " to attempt that merge." << endl;
        return;
    } else {
        index = SearchRecipes(m_myShip.GetMaterial(choice1).m_name, m_myShip.GetMaterial(choice2).m_name);
    }

    // once the item is made, increase the made item, decreased the materials
    if(index != -1) {
        if(m_myShip.GetMaterial(index).m_type != "unique") {
            cout << m_myShip.GetMaterial(choice1).m_name << " combined with " << m_myShip.GetMaterial(choice2).m_name
                    << " to make " << m_myShip.GetMaterial(index).m_name << "." << endl;
            m_myShip.IncrementQuantity(m_myShip.GetMaterial(index));
            m_myShip.DecrementQuantity(m_myShip.GetMaterial(choice1));
            m_myShip.DecrementQuantity(m_myShip.GetMaterial(choice2));
            cout << endl;
        }

        if(m_myShip.GetMaterial(index).m_type == "unique") {
            //ok so once u have one unique item you rank increases, if u have 4, you win the game
            if(m_myShip.GetMaterial(index).m_quantity != 1) {
                cout << m_myShip.GetMaterial(choice1).m_name << " combined with " << m_myShip.GetMaterial(choice2).m_name
                    << " to make " << m_myShip.GetMaterial(index).m_name << "." << endl;
                m_myShip.IncrementQuantity(m_myShip.GetMaterial(index));
                m_myShip.DecrementQuantity(m_myShip.GetMaterial(choice1));
                m_myShip.DecrementQuantity(m_myShip.GetMaterial(choice2));
                m_myShip.IncRank();
                cout << endl;
            } else {
                cout << "You have already made this unique item!" << endl;
            }
        }
    } else {
        cout << "These materials cannot merge" << endl;
        cout << endl;
    }
}

void Game::RequestMaterial(int &choice) {
    while(choice == -1) {
        DisplayMaterials();
        cout << "Which materials would you like to merge?" << endl
            << "To list known materials enter -1" << endl;
        cin >> choice;
    }
    while(choice < 0 || choice > PROJ2_SIZE) {
        cout << "That number is not in the materials list." << endl;
        cout << "Which materials would you like to merge?" << endl
            << "To list known materials enter -1" << endl;
        cin >> choice;
    }
    choice = choice - 1;
    
}

int Game::SearchRecipes(string material1, string material2) {
    
    for(int i = 0; i < PROJ2_SIZE; i++) {
        if(material1 == m_myShip.GetMaterial(i).m_material1 || material1 == m_myShip.GetMaterial(i).m_material2) {
            if(material2 == m_myShip.GetMaterial(i).m_material2 || material2 == m_myShip.GetMaterial(i).m_material1) {
                return i;
            }
        } 
    }
    return -1;
}

void Game::CalcScore() {
    cout << "***The Ship***" << endl;
    cout << "The Great Ship " << m_myShip.GetName() << endl;
    cout << "Ship Rank: " << m_myShip.GetRank() << endl;
}