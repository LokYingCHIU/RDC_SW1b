/**
 * user.c
 * 
 * This is where you'll write your code.
 * 
 * You may create files and include them here 
 * and whatnot.
 */

#include "user.h"
#include "emulator.h"
#include "qdbmp.h"


extern uint64_t iter;   //  This variable keeps track of how many times loop() was run.
                        //  Feel free to use it.

#define PI 3.1415926
#define INIT 1 //不知這樣會不會比較好?
//#define Camera 5

void setup(void)
{
    //  Initialise your program here.
    //  This function will be called once before loop().

    //  You will probably want to start out by initialising some components.
    emwrite(INIT, 5);      //  Initialises the camera.
    emwrite(INIT, 6);      //  Initialises the magnetic sensors.
    emwrite(INIT, 7);
    emwrite(INIT, 15);      //  Initialises the IR sensors.
    emwrite(INIT, 16); 
    emwrite(INIT, 100);    //  Initialises the left wheel motor.
    emwrite(INIT, 101);    //  Initialises the right wheel motor. 


    emwrite(2, 5, 0, -30, 0.0);  // Position the camera at an offset of (0, 20) cm and with no angular offset.
    emwrite(2, 6, 25, -30, PI/2);  // Position the magnetic sensor 1 at an offset of (0, 20) cm and with no angular offset.
    emwrite(2, 7, -25, -30, -PI/2);  // Position the magnetic sensor 2 at an offset of (0, 20) cm and with no angular offset.
    emwrite(2, 100, 20, -40, PI*(3/2));  // Position the left wheel 1 at an offset of (0, -40) cm and with no angular offset.
    emwrite(2, 101, -20, -40, PI*(3/2));  // Position the right wheel 1 at an offset of (0, 40) cm and with no angular offset.

    //  N.B. You can only initialise and configure components within this function.
    //       (Of course, you can still call another function which does the init.)
}

void loop(void)
{
    //  This function will be called continuously, and spaced out by approximately the same amount of time.

    //  Write your code in here.
    //  N.B. Your program will timeout if no emwrite() output is provided within ~500ms.

    //////// TASK0: move
    emwrite(3, 100, 0, 10.0);
    emwrite(3, 101, 0, 10.0);
    //////// TASK1: start, scan color
    //////// TASK2: take the basket
    //////// TASK3: scan the basket color
    //////// TASK4: take the ball
    //emwrite(10, );
    //////// TASK5: seperate the balls
    //////// TASK6: go to the cornor
    //////// TASK7: place the basket
    //emwrite(10, 3);
    //////// TASK8: take tennis ball
    //////// TASK9: throw the ball
    //emwrite(11);

    emwrite(0); //  This will output a WAIT command -- which basically does nothing.
}