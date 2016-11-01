#include "Communications.h"
#include "Timers.h"
#include "MotorControler.h"
#include "PinDef.h"
#include "UART.h"
#include "FastTransfer.h"

int throttleOut = 0, brakeOut = 0;
bool pendingSend = false;
bool portClosed = true;
//static bool started=false;

int receiveArray[20];

void commSafety();
void updateComms() {
    checkCommDirection();
    
    //If a new packet has arrived
    if (receiveData()) {
        
//        static bool carActive = false; 
//        //If the packet says that the car should be active
//        //INDICATOR ^= 1;
//        if (receiveArray[OUTPUT_ACTIVE]||carActive) {
//            //if we havent made a record of this being active yet
//            if(!carActive){
//                //reset the bootTimer to 0
//                ClearBootTime();   
//                //Enable the motor
//                MotorEnable();
//                //Store a flag that the car has been processed as active
//                carActive=receiveArray[OUTPUT_ACTIVE];
//            }
//            else if(receiveArray[OUTPUT_ACTIVE]){
//                //flag for timerOverride after timer completes
//                
////                //if bootTime has completed before now and the car is supposed to be active
////                if(((bootTime>5000)||started) && carActive){
////                    //Note that we have finished boot
////                    started=true;
//                    //if the current output is not what we received, set it correctly 
//                
//                    if (throttleOut != receiveArray[THROTTLE_OUTPUT]) {
//                        //INDICATOR ^= 1;
//                        throttleOut = receiveArray[THROTTLE_OUTPUT];
//                        SetMotor(throttleOut, forward);
//                   }
//                        
//                    //if the current output is not what we received, set it correctly 
//                    if (brakeOut != receiveArray[BRAKE_OUTPUT]) {
//                        brakeOut = receiveArray[BRAKE_OUTPUT];
//                        SetRegen(brakeOut);
//                    }
//                //}
//            }
//        }
        //else carActive is false
//        else{
//            //if brake is non-zero, wipe it
//            if(brakeOut!=0){
//                brakeOut = 0;
//                SetRegen(0);
//            }
//            //if throttle is non-zero, wipe it
//            if(throttleOut != 0){
//                throttleOut=0;
//                SetMotor(0,1);
//            }
//            //Turn of motor contoller
//            MotorDisable();
//            carActive=false;
//            //Relay control.
//            //LATAbits.LATA0=0;
//            ClearBootTime();  
//            
//        }
        ClearTalkTime();
        //ClearSafetyTime();
        pendingSend = true;
    }
    
    
    //Control the RS485 Direction pin based on time and sending
    if (pendingSend && portClosed && GetTalkTime() > 5) {
        ClearTalkTime();
        portClosed = false;
        RS485_1_Port = TALK;
        
    }
    
    
    //Respond to the ECU when the portHas been open for a short time
    if (pendingSend && GetTalkTime() > 1 && !portClosed) {
        ClearTalkTime();
        respondECU();
        pendingSend = false;
    }
    
    
    //Provide safety timer
    commSafety();
}

//If the safety timer overruns 200 then shut off outputs and set DACs to 0
void commSafety() {
    if (GetSafetyTime() > 1000) {
        SetMotor(0, 1);
        SetRegen(0);
        //Motor controller 12V
        //LATAbits.LATA10=0;
        //Relay for DAC
        //LATAbits.LATA0=0;
    }
}
//Shoot a packet to the ECU
void respondECU() {
    ToSend(RESPONSE_ADDRESS, MCS_ADDRESS);
    sendData(ECU_ADDRESS);
    ClearTalkTime();
}

void checkCommDirection() {
    //you have finished send and time has elapsed.. start listen
    if (GetTXStall() && (GetTalkTime() > 5) && (RS485_1_Port == TALK)) {
        RS485_1_Port = LISTEN;
        portClosed = true;
    }
}

void CommStartup(){
    UART_init();
    begin(receiveArray, sizeof (receiveArray), MCS_ADDRESS, false, Send_put, Receive_get, Receive_available, Receive_peek);
}
