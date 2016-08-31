/* 
 * File:   main.c
 * Author: Rick and Zac
 *
 * Created on May 11, 2015, 11:19 PM
 */

#include "Function.h"
#include <stdio.h>
#include "PinDef.h"
#include "Communications.h"
#include "Timers.h"
#include <stdbool.h>
#include <stdlib.h>
#include <xc.h>
#include "ADDRESSING.h"

int main(int argc, char** argv) {
    Setup();
    //printf("Start");
   Start_BMS(1);
   while (1) { 
        updateTimers();
      // Initalize_LT6804b(); FOR TESTING DElETE WHEN FINISHED
//        if (time_get(ADCTM) > 50) {
//            static int counter = 0;
//            if (counter < 4){
//                //ADCReadings[counter]=readADC(counter++);
//            }
//            else counter = 0;
//            ADCTime = 0;
//        }
       ledDebug();
       Run_Mode();
       updateComms();
    }

    return (EXIT_SUCCESS);
}

