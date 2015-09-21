/** @file Worker.cpp
 *  @brief Implementation methods of Worker class
 */

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include "Worker.h"

using namespace std;

Worker::Worker(){
    finding_food = true;
    food_being_carried = 0;
    food_pheromone = 0; // initially looking for food
    home_pheromone = home_pheromone_amt; // initially at home
    trail_length = trail_length_amt;
}

void Worker::set_food_carry(int amt){
    // sets the amount of food being carried
    this->food_being_carried = amt;
}

int Worker::current_food_being_carried(){
    return this->food_being_carried;
}

char Worker::ant_letter(){
    return 'W';
}

void Worker::not_finding_food(){
    // leaving a trail of food pheromones
    this->food_pheromone = food_pheromone_amt;
    this->finding_food = false;
    this->trail_length = trail_length_amt;
    this->home_pheromone = 0;
}

void Worker::is_finding_food(){
    // leaving a trail of home pheromones
    this->home_pheromone = home_pheromone_amt;
    this->finding_food = true;
    this->trail_length = trail_length_amt;
    this->food_pheromone = 0;
}

void Worker::reduce_trail_length(){
    this->trail_length -= 1;
}

void Worker::touched_food(){
    this->trail_length = trail_length_amt;
    this->food_pheromone = food_pheromone_amt;
}

void Worker::touched_home(){
    this->trail_length = trail_length_amt;
    this->home_pheromone = home_pheromone_amt;
}

int Worker::worker_food_amt(){
    if(trail_length > 0){
        return this->food_pheromone;
    }
    else{
        return 0;
    }

}

int Worker::worker_home_amt(){
    if(trail_length > 0){
        return this->home_pheromone;
    }
    else{
        return 0;
    }
}

bool Worker::finding_food_status(){
    return finding_food;
}

Worker Worker::return_itself(){
    return *this;
}