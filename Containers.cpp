
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include "Containers.h"

Containers::Containers(){
    // Constructor
    this->state = '.';
    this->pheromone_food = 0;
    this->pheromone_home = 0;
    this->food_block = 0;
    this->entrance = false;
    this->leaf_for_pickup = 0;
}

int Containers::current_leaf_for_pickup(){
    return this->leaf_for_pickup;
}

void Containers::add_leaf_for_pickup(int amt){
    this->leaf_for_pickup += amt;
}

void Containers::set_entrance_true(){
    this->entrance = true;
}

bool Containers::entrance_status(){
    return this->entrance;
}

void Containers::set_pheromone_home_amt(int amt){
    this->pheromone_home = amt;
}

void Containers::set_pheromone_food_amt(int amt){
    this->pheromone_food = amt;
}

void Containers::set_food(int incoming_food){
    this->food_block = incoming_food;
}

int Containers::current_food(){
    // returns the current food in the block
    return this->food_block;
}

void Containers::get_food(){
    this->food_block--;
    if(!this->food_block){ // food is zero
        this->set_state('.');
        this->pheromone_food = 0;
    }
}

void Containers::set_state(char incoming_char){
    // method to help set the state of the container when ants are removed
    this->state = incoming_char;
}

int Containers::current_pheromone_food(){
    // returns the current pheromone food amount
    return this->pheromone_food;
}

int Containers::current_pheromone_home(){
    // returns the current pheromone home amount
    return this->pheromone_home;
}

void Containers::sets_pheromone(int incoming_food_amt, int incoming_home_amt){
    // sets the pheromone level by amount currently set at worker
    this->pheromone_food += incoming_food_amt;
    this->pheromone_home += incoming_home_amt;
}

void Containers::decrease_pheromone_food(){
    // decreases the pheromone level by one when called
    if(this->pheromone_food){ //only if positive decrease
        this->pheromone_food--;
    }
}

void Containers::decrease_pheromone_home(){
    // decreases the pheromone level by one when called
    if(this->pheromone_home){ //only decrease if positive
        this->pheromone_home--;
    }
}

char Containers::current_state(){
    // returns the state of the given container
    return this->state;
}