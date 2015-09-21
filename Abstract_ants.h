/** @file Abstract_ants.h
 *  @brief Definition of Abstract_ants class
 */

#ifndef ABSTRACT_ANTS_H
#define ABSTRACT_ANTS_H

using namespace std;

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
    Abstract_ants();

    bool is_previous_position(int hori, int vert);

    void set_position(int hori, int vert);

    void set_id(int id_set_num);

    int get_horizontal();

    int get_vertical();
};

#endif