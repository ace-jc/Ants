


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