//set pins for fingers :5,7,9,13 
int pin_01 = 5;
int pin_02 = 7;
int pin_03 = 9;
int pin_04 = 10;
int pot_output; //Declaring a variable for finger output

//set led pin :2
//int ledPin = 2;

void setup() {
  
  Serial.begin(9600);
  
  // initialize digital ledPin as an output.
//  pinMode(ledPin, OUTPUT);
  // initialize digital finger Pins as an input.
  // configure pins as an input and enable the internal pull-up resistor
  pinMode(pin_01, INPUT_PULLUP);
  pinMode(pin_02, INPUT_PULLUP);
  pinMode(pin_03, INPUT_PULLUP);
  pinMode(pin_04, INPUT_PULLUP);  //reference :: Example code "DigitalInputPullup"
  
}

// the loop function runs over and over again forever
void loop() {
  
  //default state : 1 / HIGH
  //when switch on : 0 / LOW
  int fingerState_1 = digitalRead(pin_01);
  int fingerState_2 = digitalRead(pin_02);
  int fingerState_3 = digitalRead(pin_03);
  int fingerState_4 = digitalRead(pin_04);
  
  
  // Keep in mind the pullup means the pushbutton's
  // logic is inverted. It goes HIGH when it's open,
  // and LOW when it's pressed. Turn on pins when the 
  // button's pressed, and off when it's not:
  
  if(fingerState_1 == 0){ //when finger 1 attaches to Ground -- state value shows 0
    Serial.println("C");
  
  }else if(fingerState_2 == 0){ //when finger 2 attaches    
    Serial.println("D");
  
  }else if(fingerState_3 == 0){ //when finger 3 attaches
    Serial.println("E");
  
  }else if(fingerState_4 == 0){ //when finger 4 attaches
    Serial.println("F");
  
  }else{
    Serial.println("L");
    //when any of fingers not attache to Gound - off LED
  }
//  delay(200);
}
