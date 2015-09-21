
#ifndef WORKER_H
#define WORKER_H

/*
    This is a specific type of ant. It is a worker ant.
*/
class Worker: public Abstract_ants{
    bool finding_food; // to stop reading pheromone release its own, and find home pheromone
    int food_being_carried; // food carried by worker ant
    int food_pheromone;
    int home_pheromone;
    int trail_length;

public:
    Worker();

    void set_food_carry(int amt);

    int current_food_being_carried();

    char ant_letter();

    void not_finding_food();

    void is_finding_food();

    void reduce_trail_length();

    void touched_food();

    void touched_home();

    int worker_food_amt();

    int worker_home_amt();

    bool finding_food_status();

    Worker return_itself(){
        return *this;
    }
};

#endif