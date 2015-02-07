// Daniel Loo
// Software Engineering Design
// 2/1/2015

#include "mbed.h"
#include "Speaker.h"
#include "PinDetect.h"
#include "uLCD_4DGL.h"
// setup builtin LEDs
DigitalOut myLed1(LED1);
DigitalOut myLed2(LED2);
DigitalOut myLed3(LED3);
DigitalOut myLed4(LED4);
// setup pushbuttons for debounced interrupt use
PinDetect pb1(p23);
PinDetect pb2(p24);
PinDetect pb3(p25);
PinDetect pb4(p26);

// setup LCD
uLCD_4DGL uLCD(p28, p27, p29); // create a global lcd object

//moving include down here allows use in uLCD in Robot class draw and erase member functions
//easier for now than passing a new uLCD_4DGL object argument to the class
#include "Robot.h"

// setup instance of new Speaker class, mySpeaker using pin 21
// the pin must be a PWM output pin
Speaker mySpeaker(p21);

// pushbutton status - need volatile for safe interrupt R/W
volatile int pbStatus = 0;

// Callback routine is interrupt activated by a debounced pb1 hit
void pb1_hit_callback (void)
{
    // CODE HERE WILL RUN WHEN INTERUPT IS GENERATED
    pbStatus = pbStatus | 0x01;

}
// Callback routine is interrupt activated by a debounced pb2 hit
void pb2_hit_callback (void)
{
    // CODE HERE WILL RUN WHEN INTERUPT IS GENERATED
    pbStatus = pbStatus | 0x02;
}
// Callback routine is interrupt activated by a debounced pb3 hit
void pb3_hit_callback (void)
{
    // CODE HERE WILL RUN WHEN INTERUPT IS GENERATED
    pbStatus = pbStatus | 0x04;
}
// Callback routine is interrupt activated by a debounced pb4 hit
void pb4_hit_callback (void)
{
    // CODE HERE WILL RUN WHEN INTERUPT IS GENERATED
    pbStatus = pbStatus | 0x08;
}

// main program
int main()
{
    uLCD.printf("\nmyRobot!\nDaniel");
//setup four SPST push buttons
    pb1.mode(PullUp); //add internal pullup resistor
    pb2.mode(PullUp);
    pb3.mode(PullUp);
    pb4.mode(PullUp);
    // need a small delay for initial pullup to take effect due to capacitance
    wait(.01);
    // Setup Interrupt callback functions for each pb hit
    pb1.attach_deasserted(&pb1_hit_callback);
    pb2.attach_deasserted(&pb2_hit_callback);
    pb3.attach_deasserted(&pb3_hit_callback);
    pb4.attach_deasserted(&pb4_hit_callback);
    // Start sampling the pb inputs using interrupts
    pb1.setSampleFrequency();
    pb2.setSampleFrequency();
    pb3.setSampleFrequency();
    pb4.setSampleFrequency();
// pushbuttons are all now setup with pullups and running with a software decounce filter

// use modified robot class to move and display robot's new location on LCD
    Robot myRobot;

    myRobot.draw(); //initial robot display in center of LCD
//main loop to control and display robot
    while(1) {
        //check pushbutton status for new input
        switch (pbStatus) {
                //move forward
            case 0x01 :
                myLed1 = 1;
                pbStatus = 0;
                mySpeaker.PlayNote(200.0,0.1,0.8);
                myRobot.erase();
                myRobot.moveForward(1);
                myRobot.draw();
                break;
                //move backwards
            case 0x02 :
                myLed2 = 1;
                pbStatus = 0;
                mySpeaker.PlayNote(400.0,0.1,0.8);
                myRobot.erase();
                myRobot.moveBackward(1);
                myRobot.draw();
                break;
                //move left
            case 0x04 :
                myLed3 = 1;
                pbStatus = 0;
                mySpeaker.PlayNote(600.0,0.1,0.8);
                myRobot.erase();
                myRobot.moveLeft(1);
                myRobot.draw();
                break;
                //move right
            case 0x08 :
                myLed4 = 1;
                pbStatus = 0;
                mySpeaker.PlayNote(800.0,0.1,0.8);
                myRobot.erase();
                myRobot.moveRight(1);
                myRobot.draw();
                break;
                //no pb or multiple pbs hit
            default :
                //myLed1 = 0; //comment this out if want blinking to return (line 132)
                myLed2 = 0;
                myLed3 = 0;
                myLed4 = 0;
                pbStatus = 0;
        } //end switch
        myLed1 = !myLed1; //blink to show loop is still running
        wait(.05);
    } //end while
} //end main
