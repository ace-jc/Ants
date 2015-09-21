#ifndef CONTAINERS_H
#define CONTAINERS_H


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

        int current_leaf_for_pickup();

        void add_leaf_for_pickup(int amt);

        void set_entrance_true();

        bool entrance_status();

        void set_pheromone_home_amt(int amt);

        void set_pheromone_food_amt(int amt);

        void set_food(int incoming_food);

        int current_food();

        void get_food();

        void set_state(char incoming_char);

        int current_pheromone_food();

        int current_pheromone_home();

        void sets_pheromone(int incoming_food_amt, int incoming_home_amt);

        void decrease_pheromone_food();

        void decrease_pheromone_home();

        char current_state();
};

#endif