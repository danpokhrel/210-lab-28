// COMSC-210 | Lab 28 | Dan Pokhrel
#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <string>
#include <algorithm>
#include <random>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void duplicate(list<Goat> &trip);
void fill(list<Goat> &trip);
void find_goat(list<Goat> &trip);
void make_black(list<Goat> &trip);
void shuffle_trip(list<Goat> &trip);

void display_trip(list<Goat> trip);
int main_menu();

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    int age;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(tmp);
    }
    
    // Goat Manager 3001 Engine
    int sel = main_menu();
    while (sel != 12) {
        switch (sel) {
            case 1:
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors);
                break;
            case 2:    
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            case 3:    
                cout << "Displaying goat data.\n";
                display_trip(trip);
                break;
            case 4:
                duplicate(trip);
                break;
            case 5:
                fill(trip);
                break;
            case 6:
                find_goat(trip);
                break;
            case 7:
                make_black(trip);
                break;
            case 8:
                shuffle_trip(trip);
            default:
                cout << "Invalid selection.\n";
                break;
        }
        sel = main_menu();
    }
    

    return 0;
}

int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Duplicate all goats\n";
    cout << "[5] Make goats same\n";
    cout << "[6] Find goat\n";
    cout << "[7] Make all goats black\n";
    cout << "[8] Shuffle trip\n";
    cout << "[9] \n";
    cout << "[10]\n";
    cout << "[11]\n";
    cout << "[12] Quit\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice; cin.ignore();
    while (choice < 1 || choice > 12) {
        cout << "Invalid, again --> ";
        cin >> choice; cin.ignore();
    }
    return choice;
}

void shuffle_trip(list<Goat> &trip){
    shuffle(trip.begin(), trip.end(), default_random_engine());
    display_trip(trip);
}

void make_black(list<Goat> &trip){
    for_each(trip.begin(), trip.end(), [](Goat &goat){ goat.set_color("Black"); });
    display_trip(trip);
}

void find_goat(list<Goat> &trip){
    cout << "\nName: ";
    string name; getline(cin, name);

    auto it = find_if(trip.begin(), trip.end(), [name](const Goat &goat){ return goat.get_name() == name; });
    if (it == trip.end()){
        cout << "Goat not found.\n\n";
        return;
    }

    cout << it->get_name() << " (" << it->get_age() << ", " << it->get_color() << ")\n\n";
}

void fill(list<Goat> &trip){
    fill(trip.begin(), trip.end(), Goat("Joe", 10, "White"));
    display_trip(trip);
}

void duplicate(list<Goat> &trip){
    list<Goat> trip2(trip.size());
    copy(trip.begin(), trip.end(), trip2.begin());
    trip.merge(trip2);

    display_trip(trip);
}

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(list<Goat> trp) {
    int i = 1;
    for (auto gt: trp)
        cout << "\t" 
             << "[" << i++ << "] "
             << gt.get_name() 
             << " (" << gt.get_age() 
             << ", " << gt.get_color() << ")\n";
}

int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 || input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}