//TextLCD
#include "mbed.h"
#include "uLCD_4DGL.h"

uLCD_4DGL uLCD(p28, p27, p29); // create a global lcd object

int main() {
    //Create a timer for displaying elapsed time
    Timer t;
    t.start();
    uLCD.printf("\hello");
    while(1){
        uLCD.locate(0, 3); // Where to display the time
        uLCD.printf("%f", t.read()); // Display the time
    }
}
