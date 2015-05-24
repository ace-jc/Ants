#include <iostream>
#include <stdlib.h>
#include <time.h>

#define array_size 70
#define ant_hill_entry 35 // also includes entry minus 1
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

    Containers(){
        // Constructor
        state = '.';
        pheromone_level = 0;
        worker = NULL;
    }

    void set_state(char incoming_char){
        // method to help set the state of the container when ants are removed
        state = incoming_char;
    }

    void set_worker(Worker incoming_worker){
        // sets the worker address to the given worker
        worker = &incoming_worker;
        state = incoming_worker.ant_letter();
    }

    void remove_worker(){
        // removes the worker and sets it to null
        worker = NULL;
        state = '.';
    }

    void increase_pheromone(){
        // increases the pheromone level by one when called
        pheromone_level++;
    }
};


/*
    This is the world which will contain all of the board and will display
    the current world.
*/
class World{
    //variables
    char **world_vars;



public:
    //constructor
    World(){
        cout << "\t\t\tA 70x70 Ant World" << endl << endl;
        create_world_helper(); //creating world given size
    }

    void add_element(Worker ant){
        // to help position the ant on the board
        int x = 0;
        int y = 0;
        do{
            x = rand()%array_size;
            y = rand()%array_size;
        }while(world_vars[x][y] != '.');
        ant.set_positions(x, y);
        world_vars[x][y] = ant.ant_letter(); // added
    }

    void print(){
        for(int i=0; i<array_size; i++){
            for(int j=0; j<array_size; j++){
                cout << world_vars[i][j];
            }
            cout << endl;
        }
    }

    void create_ant_hill(){
        for(int i=0; i<array_size; i++){
            for(int j=0; j<array_size; j++){
                if(j == 49 && i != ant_hill_entry-1 && i != ant_hill_entry){
                    world_vars[i][j] = 'R';
                }
                if(j > 49){ // Randomly placing rock inside of nest
                    int temp = rand()%ant_hill_rock; //percent of rocks in any hill
                    if(temp == 0){ // defines that a rock should be present at the rate given above
                        world_vars[i][j] = 'R';
                    }
                }
//                if(j < 49){ // Randomly placing rock inside of nest
//                    int temp = rand()%food_amt; //percent of rocks in any hill
//                    if(temp == 0){ // defines that a rock should be present at the rate given above
//                        world_vars[i][j] = 'F';
//                    }
//                }
            }
        }
    }

private:
    void create_world_helper(){
        world_vars = (char **) calloc(array_size, sizeof(int *));
        for(int i=0; i<array_size; i++){
            world_vars[i] = (char *) calloc(array_size, sizeof(char));
        }

        // Setting all values to '.' period for nothing
        for(int i=0; i<array_size; i++){
            for(int j=0; j<array_size; j++){
                world_vars[i][j] = '.';
            }
        }
    }
};




/*
    This is the main program for the simulation
*/
int main()
{
    srand(time(NULL)); // sets up rand
    World the_world; // creates the world
    the_world.create_ant_hill(); // adds the ant hill to the right of the map

    the_world.print();

    // Makes workers and adds them to a random place in the map
    Worker w;
    Worker x;
    Worker z;
    the_world.add_element(w);
    the_world.add_element(x);
    the_world.add_element(z);

    cout << endl;

    the_world.print();

    return 0;
}


