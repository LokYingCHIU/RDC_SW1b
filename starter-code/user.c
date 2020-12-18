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

void setup(void)
{
    //  Initialise your program here.
    //  This function will be called once before loop().

    //  You will probably want to start out by initialising some components.
    emwrite(1, 5); // Initialise the camera.
    emwrite(2, 5, -10, -10, -80.15);  // Position the camera at an offset of (0, 20) cm and with no angular offset.
    emwrite(1, 100); // Initialise the left motor.
    emwrite(1, 101); // right motor
    emwrite(1, 6); // mag sensor
    emwrite(2, 6, -20, -40);
    emwrite(1, 7); // mag sesor
    emwrite(2, 7, 20, -40);
    emwrite(1, 15); // IR
    emwrite(2, 15, 12.5, -40, 2*pi);
    emwrite(1, 16); // IR
    emwrite(2, 16, -12.5, -40, 2*pi);

    //  N.B. You can only initialise and configure components within this function.
    //       (Of course, you can still call another function which does the init.)
}

void loop(void)
{
    //  This function will be called continuously, and spaced out by approximately the same amount of time.

    //  Write your code in here.
    //  N.B. Your program will timeout if no emwrite() output is provided within ~500ms.
  
    if(iter==1||iter==2){
        //emwrite(0);
        scan_color();
    }

    emwrite(0); //  This will output a WAIT command -- which basically does nothing.
}
