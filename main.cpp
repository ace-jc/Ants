#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <Windows.h>

#define array_width 20
#define array_height 20
#define ant_hill_rock 10 // 1 part per ant_hill_rock is rock in ant hill
#define food_amt 100 // 1 part per food_amt is food
#define slow_release_amt 150

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
    int horizontal_pos; // horizontal position on the board
    int vertical_pos; // vertical position on the board
    int worker_id; // internal worker identifier

public:
    Abstract_ants(){
        internal_hungry = 50 + (rand() % 10);
        internal_pheromone = 0;
        scared_level = 20 + (rand() % 10);
        horizontal_pos = 0;
        vertical_pos = 0;
        worker_id = 0;
    }

    void set_position(int hori, int vert){
        this->horizontal_pos = hori;
        this->vertical_pos = vert;
    }

    void set_id(int id_set_num){
        this->worker_id = id_set_num;
    }

    int get_horizontal(){
        return this->horizontal_pos;
    }

    int get_vertical(){
        return this->vertical_pos;
    }
};

/*
    This is a specific type of ant. It is a worker ant.
*/
class Worker: public Abstract_ants{
    bool finding_food; // to stop reading pheromone release its own, and find home pheromone
    int food_being_carried; // food carried by worker ant
    int food_slow_release_amt;
    int home_slow_release_amt;

public:
    Worker(){
        finding_food = true;
        food_being_carried = 0;
        food_slow_release_amt = 0;
        home_slow_release_amt = slow_release_amt;
    }

    void set_food_carry(int amt){
        // sets the amount of food being carried
        this->food_being_carried = amt;
    }

    int current_food_being_carried(){
        return this->food_being_carried;
    }

    char ant_letter(){
        return 'W';
    }

    void not_finding_food(){
        this->food_slow_release_amt = slow_release_amt;
        this->home_slow_release_amt = 0;
        this->finding_food = false;
    }

    void is_finding_food(){
        this->food_slow_release_amt = 0;
        this->home_slow_release_amt = slow_release_amt;
        this->finding_food = true;
    }

    int food_amt_and_reduce(){
        int temp = this->food_slow_release_amt;
        if(this->food_slow_release_amt > 0){ // only reduce if positive
            this->food_slow_release_amt -= 1;
        }
        return temp;
    }

    int home_amt_and_reduce(){
        int temp = this->home_slow_release_amt;
        if(this->home_slow_release_amt > 0){ // only reduce if positive
            this->home_slow_release_amt -= 1;
        }
        return temp;
    }

    bool finding_food_status(){
        return finding_food;
    }

    Worker return_itself(){
        return *this;
    }
};

/*
    The containers class will hold the information pertaining to the array
    grid. Each grid block contains a container which contains several different
    piece of information about the simulation.
*/
class Containers{
private:
    char state; //for display on the board
    int pheromone_food; // food pheromone level of the block at given moment
    int pheromone_home;// home pheromone level of the block at given moment
    int food_block;
    bool entrance;
    int leaf_for_pickup;


public:
    Containers(){
        // Constructor
        this->state = '.';
        this->pheromone_food = 0;
        this->pheromone_home = 0;
        this->food_block = 0;
        this->entrance = false;
        this->leaf_for_pickup = 0;
    }

    int current_leaf_for_pickup(){
        return this->leaf_for_pickup;
    }

    void add_leaf_for_pickup(int amt){
        this->leaf_for_pickup += amt;
    }

    void set_entrance_true(){
        this->entrance = true;
    }

    bool entrance_status(){
        return this->entrance;
    }

    void set_pheromone_home_amt(int amt){
        this->pheromone_home = amt;
    }

    void set_pheromone_food_amt(int amt){
        this->pheromone_food = amt;
    }

    void set_food(int incoming_food){
        this->food_block = incoming_food;
    }

    int current_food(){
        // returns the current food in the block
        return this->food_block;
    }

    void get_food(){
        this->food_block--;
        if(!this->food_block){ // food is zero
            this->set_state('.');
            this->pheromone_food = 0;
        }
    }

    void set_state(char incoming_char){
        // method to help set the state of the container when ants are removed
        this->state = incoming_char;
    }

    int current_pheromone_food(){
        // returns the current pheromone food amount
        return this->pheromone_food;
    }

    int current_pheromone_home(){
        // returns the current pheromone home amount
        return this->pheromone_home;
    }

    void sets_pheromone(int incoming_food_amt, int incoming_home_amt){
        // sets the pheromone level by amount currently set at worker
        this->pheromone_food += incoming_food_amt;
        this->pheromone_home += incoming_home_amt;
    }

    void decrease_pheromone_food(){
        // decreases the pheromone level by one when called
        if(this->pheromone_food){ //only if positive decrease
            this->pheromone_food--;
        }
    }

    void decrease_pheromone_home(){
        // decreases the pheromone level by one when called
        if(this->pheromone_home){ //only decrease if positive
            this->pheromone_home--;
        }
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
//    vector<Worker> workers_list; //  will contain all of the active workers
    vector<Worker *> workers_list;
    int frame_count;

public:
    //constructor
    World(){
        create_ant_hill();
        frame_count = 0;
    }

    void create_ant_hill(){
        for(int i=0; i<array_width; i++){
            for(int j=0; j<array_height; j++){
                if(j == (array_width/4*3) && (i == (array_width/2) || i == ((array_width/2)+1))){
                    // setting entrance of the ant hill with high pheromone amount
                    container_world[i][j].set_pheromone_home_amt(100000000);
                    container_world[i][j].set_entrance_true();
                }
                if(j == (array_width/4*3) && !(i == (array_width/2) || i == ((array_width/2)+1))){
                    // creating the barrier to the exit and the entrance
                    // set to 3/4 with and entrance in near middle
                    container_world[i][j].set_state('R');
                }
                if(j > (array_width/4*3)){
                    // creating rocks inside of the ant hill
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
                        container_world[i][j].set_pheromone_food_amt(100000000); // setting the pheromone attractiveness of food to max
                    }
                }
            }
        }
    }

    void print(){
        for(int i=0; i<array_width; i++){
            for(int j=0; j<array_height; j++){
                cout << container_world[i][j].current_state();
            }
            cout << endl;
        }
        cout << "frame count: " << frame_count << endl;
        statistics();
    }

    void statistics(){
        vector<Worker *>::iterator iter;
        int food_workers_carry = 0;
        int food_on_plants = 0;
        int pickup_at_home = 0;
        int total_food_pheromone = 0;
        int total_home_pheromone = 0;

        for(int i=0; i<array_width; i++){
            for(int j=0; j<array_height; j++){
                food_on_plants += container_world[i][j].current_food(); // calculating total food on plants
                pickup_at_home += container_world[i][j].current_leaf_for_pickup(); // leafs at home needing to be picked up
                if(container_world[i][j].current_state() != 'F'){
                    total_food_pheromone += container_world[i][j].current_pheromone_food(); // total current food pheromone
                }
                if(!container_world[i][j].entrance_status()){
                    total_home_pheromone += container_world[i][j].current_pheromone_home(); // total current home pheromone
                }

            }
        }

        for(iter = workers_list.begin(); iter!=workers_list.end(); iter++){
            food_workers_carry += (*iter)->current_food_being_carried();
        }

        cout << "Total Workers: " << workers_list.size() << endl;
        cout << "Total food carried by workers: " << food_workers_carry << endl;
        cout << "Food delivered home: " << pickup_at_home << endl;
        cout << endl;
        cout << "Total food pheromone on map: " << total_food_pheromone << endl;
        cout << "Total home pheromone on map: " << total_home_pheromone << endl;
        cout << "Food on plants: " << food_on_plants << endl;
    }

    void add_workers(int num){
        // to set internal unique worker id
        int internal_worker_id = 0;

        // adding workers to array and map
        for(int i=0; i<num; i++){
            Worker *worker_ptr; // create a worker pointer
            worker_ptr = new Worker; // create a worker in the heap and save the pointer

            // set the position of the worker internally to each worker
            worker_ptr->set_position((array_width/4*3), (array_width/2));
            // set worker id internal to worker
            worker_ptr->set_id(internal_worker_id);

            // adding worker to the list of workers maintained in the world
            workers_list.push_back(worker_ptr);
            // increase worker id for next worker
            internal_worker_id++;
        }
    }

    void tick(){
        // clear frames of any old worker positions
        for(int i=0; i<array_width; i++){
            for(int j=0; j<array_height; j++){
                if(container_world[i][j].current_state() == 'W'){
                    container_world[i][j].set_state('.');
                }
            }
        }

        // increase the frame number
        frame_count++;
        // will cause the board to move forward one tick for all participants
        vector<Worker *>::iterator iter;
        for(iter = workers_list.begin(); iter!=workers_list.end(); iter++){
            // iteration of worker list
            if((*iter)->finding_food_status()){
                // ant is looking for food here
                one_block_from(iter, 'F');
            }
            else{
                // ant is looking for home while carrying food and chasing home pheromones
                one_block_from(iter, 'H');
            }

            // setting 'W' on containers that contain a worker
            container_world[(*iter)->get_vertical()][(*iter)->get_horizontal()].set_state('W');
        }

        // will decrease the pheromone amounts across the board
        // essentially a type of decay
        for(int i=0; i<array_width; i++){
            for(int j=0; j<array_height; j++){
                container_world[i][j].decrease_pheromone_food();
                container_world[i][j].decrease_pheromone_home();
            }
        }
    }

    void one_block_from(vector<Worker *>::iterator iter, char food_or_home){
        //food_or_home sets the ant for food if 'F' or home if 'H'
        int new_horizontal = (*iter)->get_horizontal(); // current horizontal position
        int new_vertical = (*iter)->get_vertical(); // current vertical position
        int temp_horizontal_position = new_horizontal;
        int temp_vertical_position = new_vertical;
        int upper_temp_horizontal = new_horizontal;
        int upper_temp_vertical = new_vertical;
        vector<int> horizontal_possible_moves;
        vector<int> vertical_possible_moves;
        vector<int> no_trail_horizontal_possible_moves;
        vector<int> no_trail_vertical_possible_moves;

        // moving the center of the ant to the upper right hand side of square for analysis
        // also creating an upper bound to check for corner cases
        temp_horizontal_position -= 1;
        temp_vertical_position -= 1;
        upper_temp_horizontal += 1;
        upper_temp_vertical += 1;

        //checking for out of bounds
        if(temp_horizontal_position < 0){ // horizontally
            temp_horizontal_position = 0;
        }
        if(temp_vertical_position < 0){ // and vertically
            temp_vertical_position = 0;
        }
        if(upper_temp_horizontal >= array_width){
            upper_temp_horizontal = (array_width-1);
        }
        if(upper_temp_vertical >= array_height){
            upper_temp_vertical = (array_height-1);
        }

        for(int j=temp_horizontal_position; j<=upper_temp_horizontal; j++){
            for(int k=temp_vertical_position; k<=upper_temp_vertical; k++){
                char temp_state = container_world[k][j].current_state();
                if(temp_state != 'R'){
                    if(container_world[k][j].current_state() == 'F'){
                        //I'm looking for food and I've found food within one block
                        container_world[k][j].get_food(); // reduce the container food by one, pheromone set to zero, state set to '.'
                        (*iter)->set_food_carry(1); // ant picks up the one unit of food
                        (*iter)->not_finding_food(); // no longer looking for food, instead looking for home
                        return;
                    }
                    if((food_or_home == 'H') && container_world[k][j].entrance_status()){
                        // I'm looking for the entrance and it is found one block away from current position
                        (*iter)->set_food_carry(0); // ant is now not carrying food
                        container_world[k][j].add_leaf_for_pickup(1); // leaf for pickup is added to the entrance container
                        (*iter)->is_finding_food(); // sets finding food to true
                        return;
                    }

                    // at this point there was no food or home and move must be made
                    if((food_or_home == 'F') && (container_world[k][j].current_pheromone_food() > 0)){
                        // looking for food and found a positive food pheromone, saving it to horizontal_possible_moves
                        horizontal_possible_moves.push_back(j);
                        vertical_possible_moves.push_back(k);
                    }
                    if((food_or_home == 'H') && (container_world[k][j].current_pheromone_home() > 0)){
                        // looking for home and found a positive home pheromone, saving it to horizontal_possible_moves
                        horizontal_possible_moves.push_back(j);
                        vertical_possible_moves.push_back(k);
                    }

                    // no pheromones were found
                    if((food_or_home == 'F') && (container_world[k][j].current_pheromone_food() == 0)){
                        no_trail_horizontal_possible_moves.push_back(j);
                        no_trail_vertical_possible_moves.push_back(k);
                    }
                    if((food_or_home == 'H') && (container_world[k][j].current_pheromone_home() == 0)){
                        no_trail_horizontal_possible_moves.push_back(j);
                        no_trail_vertical_possible_moves.push_back(k);
                    }
                }
            }
        }

        // following food or home pheromone
        int size_of_possible_moves = horizontal_possible_moves.size();
        if(size_of_possible_moves > 0){
            // randomly selecting one of the possible moves following a trail
            int random_value = rand()%size_of_possible_moves;
            // new horizontal is one of the possible values
            new_horizontal = horizontal_possible_moves.at(random_value);
            // new vertical is one of the possible values
            new_vertical = vertical_possible_moves.at(random_value);
        }
        else{
            // randomly selecting one of the possible moves not following a trail
            size_of_possible_moves = no_trail_horizontal_possible_moves.size();
            // randomly selecting one of the possible moves
            int random_value = rand()%size_of_possible_moves;
            // new horizontal is one of the possible values
            new_horizontal = no_trail_horizontal_possible_moves.at(random_value);
            // new vertical is one of the possible values
            new_vertical = no_trail_vertical_possible_moves.at(random_value);
        }

        // this is where the worker actually moves to a new container
        if(container_world[new_vertical][new_horizontal].current_state() == '.'){
            // save the current new position internally to the worker
            (*iter)->set_position(new_horizontal, new_vertical);

            //sets pheromone food amount on the new position
            container_world[new_vertical][new_horizontal].sets_pheromone((*iter)->food_amt_and_reduce() , (*iter)->home_amt_and_reduce());
        }
    }
};


/*
    This is the main program for the simulation
*/
int main(){
    const int worker_ants = 5;
    srand(time(NULL)); // sets up rand

    cout << "\t\t\tA " << array_width << "x" << array_height <<" Ant World" << endl;
    World *world_ptr = new World(); // creates the world in the heap and assigns the pointer to its location
    world_ptr->add_workers(worker_ants); // adds num workers to the world
    world_ptr->print(); // prints the world
    Sleep(2000);
    system("cls");


    int time_tick = 1000;
    while(time_tick){
        world_ptr->tick();
        world_ptr->print(); // prints the world
        time_tick--;
        Sleep(100);
        system("cls");
    }

    cout << "\t\t\tA " << array_width << "x" << array_height <<" Ant World" << " - HALTED POSITION!!!" << endl;
    world_ptr->print(); // prints the world

    return 0;
}


