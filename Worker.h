


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
    Worker(){
        finding_food = true;
        food_being_carried = 0;
        food_pheromone = 0; // initially looking for food
        home_pheromone = home_pheromone_amt; // initially at home
        trail_length = trail_length_amt;
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
        // leaving a trail of food pheromones
        this->food_pheromone = food_pheromone_amt;
        this->finding_food = false;
        this->trail_length = trail_length_amt;
        this->home_pheromone = 0;
    }

    void is_finding_food(){
        // leaving a trail of home pheromones
        this->home_pheromone = home_pheromone_amt;
        this->finding_food = true;
        this->trail_length = trail_length_amt;
        this->food_pheromone = 0;
    }

    void reduce_trail_length(){
        this->trail_length -= 1;
    }

    void touched_food(){
        this->trail_length = trail_length_amt;
        this->food_pheromone = food_pheromone_amt;
    }

    void touched_home(){
        this->trail_length = trail_length_amt;
        this->home_pheromone = home_pheromone_amt;
    }

    int worker_food_amt(){
        if(trail_length > 0){
            return this->food_pheromone;
        }
        else{
            return 0;
        }

    }

    int worker_home_amt(){
        if(trail_length > 0){
            return this->home_pheromone;
        }
        else{
            return 0;
        }
    }

    bool finding_food_status(){
        return finding_food;
    }

    Worker return_itself(){
        return *this;
    }
};