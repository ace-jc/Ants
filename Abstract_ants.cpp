/** @file Abstract_ants.cpp
 *  @brief Implementation methods of Abstract_ants class
 */

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include "Abstract_ants.h"

using namespace std;

Abstract_ants::Abstract_ants(){
    internal_pheromone = 0;
    scared_level = 20 + (rand() % 10);
    horizontal_pos = 0;
    vertical_pos = 0;
    worker_id = 0;
}

bool Abstract_ants::is_previous_position(int hori, int vert){
    //create and iterator for the previous positions check
    vector<int>::iterator position_iter;
    vector<int>::iterator position_iter2;
    for(position_iter = this->last_horizontal_positions.begin(); position_iter!=last_horizontal_positions.end(); position_iter++){
        for(position_iter2 = this->last_vertical_positions.begin(); position_iter2!=last_vertical_positions.end(); position_iter2++){
            // over each horizontal position
            if((*position_iter == hori) && (*position_iter2 == vert)){
//                    cout << "Returning True" << endl;
                return true;
            }
        }
    }
//        cout << "Returning False" << endl;
    return false;
}


void Abstract_ants::set_position(int hori, int vert){
    // saving current position
    this->horizontal_pos = hori;
    this->vertical_pos = vert;

    // saving previous positions
    if(last_horizontal_positions.size() > 3){ // keeping a memory of the last three positions
        this->last_horizontal_positions.erase(last_horizontal_positions.begin()); // erase the first element horizontally
        this->last_vertical_positions.erase(last_vertical_positions.begin()); // erase the first element vertically
    }
    this->last_horizontal_positions.push_back(hori);
    this->last_vertical_positions.push_back(vert);
}

void Abstract_ants::set_id(int id_set_num){
    this->worker_id = id_set_num;
}

int Abstract_ants::get_horizontal(){
    return this->horizontal_pos;
}

int Abstract_ants::get_vertical(){
    return this->vertical_pos;
}