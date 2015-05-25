#include <iostream>
#include <stdlib.h>
#include <time.h>

#define array_width 70
#define array_height 70
#define ant_hill_rock 10 // 1 part per ant_hill_rock is rock in ant hill
#define food_amt 500 // 1 part per food_amt is food

using namespace std;

/*
    This is an abstract data type that will handle all types of ant
    variables.
*/
class Abstract_ants{
protected:
    //Variables
    int internal_hungry; // to help create more minima and media workers
    int internal_pheromone; // what this ant releases
    int scared_level; // to create more soldiers
    int external_pheromone; // what this ant is reading to find food
    bool carrying_food; // to stop reading pheromone and release its own

    int location_x;
    int location_y;

public:
    Abstract_ants(){
        internal_hungry = 50 + (rand() % 10);
        internal_pheromone = 0;
        scared_level = 20 + (rand() % 10);
        external_pheromone = 0;
        carrying_food = false;
        location_x = 0;
        location_y = 0;
    }

    char ant_letter(){
        return 'X'; // to be overridden by specific ant types
    }

    void set_positions(int val_x, int val_y){
        location_x = val_x;
        location_y = val_y;
    }
};

/*
    This is a specific type of ant. It is a worker ant.
*/
class Worker: public Abstract_ants{
    bool is_carrying_leaves = false;

public:
    Worker(){
        //nothing yet
    }

    char ant_letter(){
        return 'W';
    }
};

/*
    The containers class will hold the information pertaining to the array
    grid. Each grid block contains a container which contains several different
    piece of information about the simulation.
*/
class Containers{
public:
    char state; //for display on the board
    int pheromone_level; // pheromone level of the block at given moment
    Worker *worker; // will be a pointer to a worker in the given container
    int food_block;

    Containers(){
        // Constructor
        this->state = '.';
        this->pheromone_level = 0;
        this->food_block = 0;
        this->worker = NULL;
    }

    void set_food(int incoming_food){
        this->food_block = incoming_food;
    }

    void get_food(){
        this->food_block--;
        if(!this->food_block){ // food is zero
            this->set_state('.');
        }
    }

    void set_state(char incoming_char){
        // method to help set the state of the container when ants are removed
        this->state = incoming_char;
    }

    void set_worker(Worker incoming_worker){
        // sets the worker address to the given worker
        this->worker = &incoming_worker;
        this->state = incoming_worker.ant_letter();
    }

    void remove_worker(){
        // removes the worker and sets it to null
        this->worker = NULL;
        this->state = '.';
    }

    void increase_pheromone(){
        // increases the pheromone level by one when called
        this->pheromone_level++;
    }

    char current_state(){
        // returns the state of the given container
        return this->state;
    }
};


/*
    This is the world which will contain all of the board and will display
    the current world.
*/
class World{
    //variables
    Containers container_world[array_width][array_height];

public:
    //constructor
    World(){
        cout << "\t\t\tA 70x70 Ant World" << endl << endl;
        create_ant_hill();
    }

    void print(){
        for(int i=0; i<array_width; i++){
            for(int j=0; j<array_height; j++){
                cout << container_world[i][j].current_state();
            }
            cout << endl;
        }
    }

    void create_ant_hill(){
        for(int i=0; i<array_width; i++){
            for(int j=0; j<array_height; j++){
                if(j == (array_width/4*3) && !(i == (array_width/2) || i == ((array_width/2)+1))){
                    // creating the barrier to the exit and the entrance
                    // set to 3/4 with and entrance in near middle
                    container_world[i][j].set_state('R');
                }
                if(j > (array_width/4*3)){
                    int tmp = rand()%ant_hill_rock;
                    if(tmp == 0){
                        container_world[i][j].set_state('R');
                    }
                }
                if(j < (array_width/4*3)){
                    int tmp = rand()%food_amt; // food amount in part per food_amt defined above
                    if(tmp == 0){
                        container_world[i][j].set_food((rand()%50)+1); // set food between 1 and 50
                        container_world[i][j].set_state('F');
                    }
                }
            }
        }
    }
};




/*
    This is the main program for the simulation
*/
int main(){
    srand(time(NULL)); // sets up rand
    World the_world; // creates the world
    the_world.print(); // prints the world

    return 0;
}


