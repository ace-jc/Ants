/** @file Abstract_ants.h
 *  @brief Implementation details of functions in
 */
#ifndef ABSTRACT_ANTS_H
#define ABSTRACT_ANTS_H

#include "Abstract_ants.h"
#include "Worker.h"
#include "Containers.h"
#include "World.h"
/*
    This is an abstract data type that will handle all types of ant
    variables.
*/
class Abstract_ants{
protected:
    //Variables
    int internal_pheromone; // what this ant releases
    int scared_level; // to create more soldiers
    int horizontal_pos; // horizontal position on the board
    int vertical_pos; // vertical position on the board
    int worker_id; // internal worker identifier
    vector<int> last_horizontal_positions; // storing previous positions to avoid
    vector<int> last_vertical_positions; // storing previous positions to avoid

public:
    Abstract_ants(){
        internal_pheromone = 0;
        scared_level = 20 + (rand() % 10);
        horizontal_pos = 0;
        vertical_pos = 0;
        worker_id = 0;
    }

    bool is_previous_position(int hori, int vert){
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


    void set_position(int hori, int vert){
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

#endif