/*
 
  The circuit:
 * LCD RS pin to digital pin 7
 * LCD Enable pin to digital pin 6
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 *  ends to +5V and ground
 *  wiper to LCD VO pin (pin 3)
 * 


*/

// include the library code:
// #include <LiquidCrystal.h>
#include <IRremote.h> 
//#include <IRremoteInt.h>



// initialise
  //LCD
    //const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
    //LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
  //IR Sensor
    int rx_pin = 12;
    int tx_pin = 11;
    int32_t result = 0x0000000;
    int32_t transmitcode = 0x0000000;
    String button="";

void setup() {
  //IR Sensor
    IrReceiver.begin(rx_pin, DISABLE_LED_FEEDBACK); //  Enable receiver so that it would start processing infrared signals
    IrSender.begin(tx_pin, DISABLE_LED_FEEDBACK, USE_DEFAULT_FEEDBACK_LED_PIN);
  //LCD
    // set up the LCD's number of columns and rows:
    //lcd.begin(16, 2);              // Tell it the LCD dimensions
    //lcd.print("Ready to receive"); 

}

void loop() {
      
  if (IrReceiver.decode()) {            //  Decode the button code and put it in "results" variable
    result = IrReceiver.decodedIRData.decodedRawData;
    //lcd.clear();
    //button="";
    //lcd.setCursor(0, 0);  // set the cursor to column 0, line 0  (note: line 1 is the second row, since counting begins with 0)
    //lcd.print("RX:");
    //lcd.print(result, HEX);            //  Print the code as a hexadecimal value to the LCD
    //lcd.print(".");

    if((result) == 0xF00F0707) {  //TV Mute
      //button = "Mute";
      IrSender.sendNECRaw(0xFF003FC0);  //Amp Mute
    }

    if((result) == 0xB6490707) {  //TV Record
      //button = "Aux";
      IrSender.sendNECRaw(0xA35C3FC0);  //Amp Aux
      delay(50);
      IrSender.sendNECRaw(0xF40B31DD); //Audio Switch Input 2
    }

   if((result) == 0xF8070707) {  //TV Vol+
      //button = "Vol+";
      IrSender.sendNECRaw(0xE21D3FC0);  //Amp Vol+
      delay(50);
      IrSender.sendNECRaw(0xE21D3FC0);  //Amp Vol+
    }

   if((result) == 0xF40B0707) {  //TV Vol-
      //button = "Vol-";
      IrSender.sendNECRaw(0xA15E3FC0); //Amp Vol-
      delay(50);
      IrSender.sendNECRaw(0xA15E3FC0); //Amp Vol-
    }
    
    if((result) == 0xF18F9123) { //Chromecast remote Samsung 3 Input change (does not match TV)
      //button = "Input";
      IrSender.sendNECRaw(0xA35C3FC0); //Amp Aux
      delay(50);
      IrSender.sendNECRaw(0xF40B31DD); //Audio Switch Input 2
    }

   if((result) == 0x936C0707) {  //TV RedButton
      //button = "Menu";
      IrSender.sendNECRaw(0xA55A3FC0); //Amp Menu

    }
   


    //lcd.setCursor(0, 1);  // set the cursor to column 0, line 0  (note: line 1 is the second row, since counting begins with 0)
    //lcd.print("TX:");
    //lcd.print(transmitcode, HEX);            //  Print the code as a hexadecimal value to the LCD
    //lcd.print(" ");
    //lcd.print(button);

    transmitcode = 0x0000000;
    IrReceiver.resume();                         //  Continue listening for new signals
  }
}

