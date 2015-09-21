



#ifndef Abstract_ants_h
#define Abstract_ants_h

#ifndef Worker_h
#define Worker_h

#ifndef Containers_h
#define Containers_h

#ifndef World_h
#define World_h

// ----
// Main
// ----
int main(){
    // This is the main function for the simulation
    // Calling Runants control loop
    void Runants();

    return 0;
}




// -------
// Runants
// -------
void Runants(){
    // Application function loop
    const int worker_ants = 50;
    srand(time(NULL)); // sets up rand

    cout << "\t\t\tA " << array_width << "x" << array_height <<" Ant World" << endl;
    World *world_ptr = new World(); // creates the world in the heap and assigns the pointer to its location
    world_ptr->add_workers(worker_ants); // adds num workers to the world
    world_ptr->print(); // prints the world
    sleep(2);
    system("cls");


    int time_tick = 10000;
    while(time_tick){
        world_ptr->tick();
        time_tick--;
        world_ptr->print(); // prints the world

        struct timespec tim, tim2;
        tim.tv_sec = 0;
        tim.tv_nsec = 20000000;

        if(nanosleep(&tim , &tim2) < 0 )   
        {
            cout << "Nano sleep system call failed \n" << endl;
            return -1;
        }

        system("cls");
    }

    cout << "\t\t\tA " << array_width << "x" << array_height <<" Ant World" << " - HALTED POSITION!!!" << endl;
    world_ptr->print(); // prints the world

};