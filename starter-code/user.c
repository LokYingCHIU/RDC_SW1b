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

//only updated something i 100% done, didn't post things i am dealing with/still thinking:)

int color=0;
void scan_color(){
    BMP* bmp;
    emwrite(4, 5);
    if(iter==2){
        if (emread_camera(&bmp)){
            //BMP* bmp = emread_camera(&bmp);
            UCHAR r,g,b;
            int width = BMP_GetWidth(bmp);
            int height = BMP_GetHeight(bmp);
            for (int i = 20;i<height;i++){
                for (int j = 20;j<width;j++){
                    BMP_GetPixelRGB(bmp, i,j, &r, &g, &b);
                    //emdebug("%d %d %d\n", (int)r, (int)g, (int)b);
                    if (((int)r<5)&&((int)g<5)&&((int)b>170)){
                        color = 1; //blue
                    }
                    else if (((int)r>170)&&((int)g<5)&&((int)b>5)){
                        color = 2; //red
                    }
                }
            }
            emdebug("the color is %d",color);
            //BMP_WriteFile(bmp, "C:\\Users\\Nicole Lui\\Desktop\\HKUST\\RT\\RDC\\Emulator-Release-1.1.0\\Emulator-Release-1.1.0\\images\\out.bmp");
            //emdebug("%s\n",BMP_GetErrorDescription());
            BMP_Free(bmp);  // Free bmp after usage. 
        }
    }
}

float pi = 3.14159265359;

void setup(void)
{
    //  Initialise your program here.
    //  This function will be called once before loop().
    //  You will probably want to start out by initialising some components.
    emwrite(1, 5); // Initialise the camera.
    //emwrite(2, 5, -10, -10, -80.15);  // Position the camera at an offset of (0, 20) cm and with no angular offset.
    emwrite(2, 5, 0, 0, 1.57);
    emwrite(1, 100); // Initialise the left motor.
    emwrite(1, 101); // right motor
    emwrite(1, 6); // mag sensor
    emwrite(2, 6, -15, -40);
    emwrite(1, 7); // mag sesor
    emwrite(2, 7, 15, -40);
    emwrite(1, 15); // IR
    emwrite(2, 15, -12, -40, 2*pi);
    emwrite(1, 16); // IR
    emwrite(2, 16, 12, -40, 2*pi);
    emwrite(1, 10); //line sensor
    emwrite(2, 10, -25, -40);
    emwrite(1, 11); //line sensor
    emwrite(2, 11, 25, -40);
    emwrite(1, 200); //grabbing mech
    emwrite(2, 200, 28, -40, 0);
    emwrite(1, 201); //throwing mech
    emwrite(2, 201, -53, 40, 0);

    /*
    emwrite(3, 20, 0, 24.0); // Set wheel motor 0 voltage to 24V.
    emwrite(3, 21, 0, 12.0); // Set wheel motor 1 voltage to 12V.
    emwrite(4, 5); // Request camera input on the next iteration.

    emwrite(10, 0); // Release the grabber.
    emwrite(10, 1); // Grab a tennis ball.

    emwrite(11); // Throw the ball.*/

    //  N.B. You can only initialise and configure components within this function.
    //       (Of course, you can still call another function which does the init.)
}

bool is_data_requested = false;
bool stop = false;
int num_of_turn = 0;
int num_of_true = 0;

void loop(void)
{
    //  This function will be called continuously, and spaced out by approximately the same amount of time.

    //  Write your code in here.
    //  N.B. Your program will timeout if no emwrite() output is provided within ~500ms.
  
    if(iter==1||iter==2){
        //emwrite(0);
        scan_color();
    }
  
    else{    
        if(is_data_requested){
            int magid = 6; int magid2 = 7; int turns = 0;         ////Magnetic Sensor
            int magvalue, magvalue2;
            if(emread_magnetic_sensor(&magid, &magvalue)){ 
                if(emread_magnetic_sensor(&magid2, &magvalue2)){
                    emdebug("%d %d\n", magvalue, magvalue2);
                    if((magvalue<130)&&(magvalue2>=130)){      //check turn right?
                        emwrite(3, 100, 0, 20.0);
                        emwrite(3, 101, 0, -20.0);
                        if((magvalue>=130)&&(magvalue2<130)){
                            emwrite(3, 100, 0, -20.0);
                            emwrite(3, 101, 0, 20.0);
                        }
                    }
                    else if((magvalue>=100)&&(magvalue2<100)){  //check trun left?
                        emwrite(3, 100, 0, -20.0);
                        emwrite(3, 101, 0, 20.0);
                        if((magvalue<100)&&(magvalue2>=100)){
                            emwrite(3, 100, 0, -20.0);
                            emwrite(3, 101, 0, 20.0);
                        }
                    }
                    else if((magvalue>=100)&&(magvalue2>=100)){  //check during turning
                        if(magvalue>magvalue2){
                            emwrite(3, 100, 0, 20.0);
                            emwrite(3, 101, 0, 0.0);
                            num_of_turn += 1;
                        }
                        else if(magvalue2>magvalue){
                            emwrite(3, 100, 0, 0.0);
                            emwrite(3, 101, 0, 20.0);
                            num_of_turn += 1;
                        }
                    }
                    else{
                        emwrite(3, 100, 0, 24.0);
                        emwrite(3, 101, 0, 24.0);
                    }
                    if(num_of_turn>21 && turns==0){       //after turning
                        if(abs(magvalue-magvalue2)>30){
                            if(magvalue>magvalue2){
                                emwrite(3, 100, 0, -24.0);
                                emwrite(3, 101, 0, 24.0);
                            }
                            else if(magvalue2>magvalue){
                                emwrite(3, 100, 0, 24.0);
                                emwrite(3, 101, 0, -24.0);
                            }
                        }
                        else{
                            emwrite(3, 100, 0, 24.0);
                            emwrite(3, 101, 0, 24.0);
                        }
                    } 
                  
                    int irid = 15, irid2 = 16;                   ////IR Sensor
                    int irvalue, irvalue2;
                    bool grab_basket;
                    if(emread_ir_sensor(&irid, &irvalue)){
                        if(emread_ir_sensor(&irid2, &irvalue2)){
                            emdebug("%d %d\n", irvalue,irvalue2);
                            if(irvalue+irvalue2==4201474){
                                if(num_of_true<45){
                                    emwrite(3, 100, 0, 24.0);
                                    emwrite(3, 101, 0, 24.0);
                                    num_of_true += 1;
                                }
                                else{
                                    emwrite(3, 100, 0, 0.0);
                                    emwrite(3, 101, 0, 0.0);
                                    emwrite(10, 3);
                                    bool grab_basket = true;
                                    turns += 1;
                                    emwrite(3, 100, 0, -20.0);
                                    emwrite(3, 101, 0, 20.0);
                                }
                            }
                        }
                    }
                }
            }
        }
        emwrite(4, 6);
        emwrite(4, 7);
        emwrite(4, 15);
        emwrite(4, 16);
        is_data_requested = true;
    }
  
    //emwrite(0); //  This will output a WAIT command -- which basically does nothing.
}
