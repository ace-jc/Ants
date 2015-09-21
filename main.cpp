/** @file main.cpp
 *  @brief Intial program file
 */

// --------
// includes
// --------
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include "Abstract_ants.h"
#include "Worker.h"
#include "Containers.h"
#include "World.h"


// -----------------------------
// define prepocessor directives
// -----------------------------
#define ant_hill_rock 10 // 1 part per ant_hill_rock is rock in ant hill
#define food_amt 100 // 1 part per food_amt is food


using namespace std;

// ----
// Main
// ----
int main(){
    // This is the main function for the simulation

    // Application function loop
    const int worker_ants = 50;
    srand(time(NULL)); // sets up rand

    cout << "\t\t\tA " << array_width << "x" << array_height <<" Ant World" << endl;
    // creates the world in the heap and assigns the pointer to its location
    World *world_ptr = new World(); 
    // adds num workers to the world
    world_ptr->add_workers(worker_ants); 
    // prints the world
    world_ptr->print(); 
    sleep(2);
    system("cls");


    int time_tick = 10000;
    while(time_tick){
        world_ptr->tick();
        time_tick--;
        world_ptr->print(); // prints the world

        struct timespec tim, tim2;
        tim.tv_sec = 0;
        tim.tv_nsec = 80000000;
        nanosleep(&tim , &tim2);
        system("cls");
    }

    cout << "\t\t\tA " << array_width << "x" << array_height <<" Ant World" << " - HALTED POSITION!!!" << endl;
    world_ptr->print(); // prints the world

    return 0;
}