#include "mbed.h"
#include "uLCD_4DGL.h"
//Print temperature from TMP36 analog temperature sensor
//Setup a new class for TMP36 sensor
class TMP36
{
public:
 TMP36(PinName pin);
 TMP36();
 operator float ();
 float read();
private:
//class sets up the AnalogIn pin
 AnalogIn _pin;
};
TMP36::TMP36(PinName pin) : _pin(pin)
{
// _pin(pin) means pass pin to the AnalogIn constructor
}
float TMP36::read()
{
//convert sensor reading to temperature in degrees C
 return ((_pin.read()*3.3)-0.500)*100.0;
}
//overload of float conversion (avoids needing to type .read() in equations)
TMP36::operator float ()
{
//convert sensor reading to temperature in degrees C
 return ((_pin.read()*3.3)-0.500)*100.0;
}
//use the new class to set p15 to analog input to read and convert TMP36 sensor's
//voltage output
TMP36 myTMP36(p15);
//also setting unused analog input pins to digital outputs reduces A/D noise
DigitalOut P16(p16);
DigitalOut P17(p17);
DigitalOut P18(p18);
DigitalOut P19(p19);
DigitalOut P20(p20);
uLCD_4DGL uLCD(p28, p27, p29); // create a global lcd object
int main()
{
 float tempC, tempF;
 while(1) {
 tempC = myTMP36.read();
 //convert to degrees F
 tempF = (9.0*tempC)/5.0 + 32.0;
 //print current temp
uLCD.locate(2,2);
 uLCD.printf("%5.2F C %5.2F F \n\r", tempC, tempF);
 wait(.5);
 }
}
