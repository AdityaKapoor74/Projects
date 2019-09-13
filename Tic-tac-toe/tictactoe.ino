#include <Adafruit_NeoPixel.h>

// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip0)
Adafruit_NeoPixel strip0 = Adafruit_NeoPixel(9, 2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(9, 3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(9, 4, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(9, 5, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip4 = Adafruit_NeoPixel(9, 6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip5 = Adafruit_NeoPixel(9, 7, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip6 = Adafruit_NeoPixel(9, 8, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip7 = Adafruit_NeoPixel(9, 9, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip8 = Adafruit_NeoPixel(9, 13, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel strip9 = Adafruit_NeoPixel(10, 11, NEO_GRB + NEO_KHZ800);

const uint32_t red = strip0.Color(255, 0, 0);
const uint32_t turq = strip0.Color(0, 255, 255);
const uint32_t pink = strip0.Color(255, 51, 153);
const uint32_t blue = strip0.Color(0, 0, 255);
const uint32_t orange = strip0.Color(255, 128, 0);
const uint32_t green = strip0.Color(0, 255, 0);
const uint32_t white = strip0.Color(255, 255, 255);
const uint32_t yellow = strip0.Color(255, 255, 0);
const uint32_t purple = strip0.Color(153, 0, 153);

String incoming;
String replay;
String winner;
int counter;
int score1;
int score2;
int matrix1[3][3];
int matrix2[3][3];

void setup() {
  //Strip setup
  pinMode(12,INPUT);
  strip0.begin();
  strip1.begin();
  strip2.begin();
  strip3.begin();
  strip4.begin();
  strip5.begin();
  strip6.begin();
  strip7.begin();
  strip8.begin();

  counter = 1;
  score1 = 0;
  score2 = 0;
  //UART setup
  Serial.begin(9600);
  Serial.setTimeout(20);
  clearAll();

  for(int i=0;i<3;i++)
  {
    for(int j=0;j<3;j++)
    {
      matrix1[i][j]=0;
      matrix2[i][j]=0;
    }
  }
  replay="Yes";
}

void loop()
{
  if(replay.startsWith("No")){
    digitalWrite(12,LOW);
  }
  while (Serial.available() > 0)
  {
    incoming = Serial.readString();
    Serial.println(incoming);
  }

  if(incoming.startsWith("reset"))
  {
    clearAll();
    counter=1;
  }
  if (counter % 2 == 0)
  {
    if (incoming.startsWith("1") && matrix2[0][0]!=1)
    {
      Serial.println("top-left");
      colorWipe(strip0.Color(255, 0, 0), 50,2,0);
      colorWipe(strip1.Color(255, 0, 0), 50,2,1);
      colorWipe(strip2.Color(255, 0, 0), 50,2,2);
      matrix1[0][0]=1;
    }
    else if (incoming.startsWith("2") && matrix2[0][1]!=1)
    {
      Serial.println("top-middle");
      colorWipe(strip0.Color(255, 0, 0), 50,1,0);
      colorWipe(strip1.Color(255, 0, 0), 50,1,1);
      colorWipe(strip2.Color(255, 0, 0), 50,1,2);
      matrix1[0][1]=1;
    }
    else if (incoming.startsWith("3") && matrix2[0][2]!=1)
    {
      Serial.println("top-right");
      colorWipe(strip0.Color(255, 0, 0), 50,0,0);
      colorWipe(strip1.Color(255, 0, 0), 50,0,1);
      colorWipe(strip2.Color(255, 0, 0), 50,0,2);
      matrix1[0][2]=1;
    }
    else if (incoming.startsWith("4") && matrix2[1][0]!=1)
    {
      Serial.println("middle-left");
      colorWipe(strip3.Color(255, 0, 0), 50,2,3);
      colorWipe(strip4.Color(255, 0, 0), 50,2,4);
      colorWipe(strip5.Color(255, 0, 0), 50,2,5);
      matrix1[1][0]=1;
    }
    else if (incoming.startsWith("5") && matrix2[1][1]!=1)
    {
      Serial.println("middle-middle");
      colorWipe(strip3.Color(255, 0, 0), 50,1,3);
      colorWipe(strip4.Color(255, 0, 0), 50,1,4);
      colorWipe(strip5.Color(255, 0, 0), 50,1,5);
      matrix1[1][1]=1;
    }
    else if (incoming.startsWith("6") && matrix2[1][2]!=1)
    {
      Serial.println("middle-right");
      colorWipe(strip3.Color(255, 0, 0), 50,0,3);
      colorWipe(strip4.Color(255, 0, 0), 50,0,4);
      colorWipe(strip5.Color(255, 0, 0), 50,0,5);
      matrix1[1][2]=1;
    }
    else if (incoming.startsWith("7") && matrix2[2][0]!=1)
    {
      Serial.println("bottom-left");
      colorWipe(strip6.Color(255, 0, 0), 50,2,6);
      colorWipe(strip7.Color(255, 0, 0), 50,2,7);
      colorWipe(strip8.Color(255, 0, 0), 50,2,8);
      matrix1[2][0]=1;
    }
    else if (incoming.startsWith("8") && matrix2[2][1]!=1)
    {
      Serial.println("bottom-middle");
      colorWipe(strip6.Color(255, 0, 0), 50,1,6);
      colorWipe(strip7.Color(255, 0, 0), 50,1,7);
      colorWipe(strip8.Color(255, 0, 0), 50,1,8);
      matrix1[2][1]=1;
    }
    else if (incoming.startsWith("9") && matrix2[2][2]!=1)
    {
      Serial.println("bottom-right");
      colorWipe(strip6.Color(255, 0, 0), 50,0,6);
      colorWipe(strip7.Color(255, 0, 0), 50,0,7);
      colorWipe(strip8.Color(255, 0, 0), 50,0,8);
      matrix1[2][2]=1;
    }
    else 
    {
      counter--;
    }
    winner=whoWon(1);
  }
  else
  {
    if (incoming.startsWith("1") && matrix1[0][0]!=1)
    {
      Serial.println("top-left");
      colorWipe(strip0.Color(0, 0, 255), 50,2,0);
      colorWipe(strip1.Color(0, 0, 255), 50,2,1);
      colorWipe(strip2.Color(0, 0, 255), 50,2,2);
      matrix2[0][0]=1;
    }
    else if (incoming.startsWith("2") && matrix1[0][1]!=1)
    {
      Serial.println("top-middle");
      colorWipe(strip0.Color(0, 0, 255), 50,1,0);
      colorWipe(strip1.Color(0, 0, 255), 50,1,1);
      colorWipe(strip2.Color(0, 0, 255), 50,1,2);
      matrix2[0][1]=1;
    }
    else if (incoming.startsWith("3") && matrix1[0][2]!=1)
    {
      Serial.println("top-right");
      colorWipe(strip0.Color(0, 0, 255), 50,0,0);
      colorWipe(strip1.Color(0, 0, 255), 50,0,1);
      colorWipe(strip2.Color(0, 0, 255), 50,0,2);
      matrix2[0][2]=1;
    }
    else if (incoming.startsWith("4") && matrix1[1][0]!=1)
    {
      Serial.println("middle-left");
      colorWipe(strip3.Color(0, 0, 255), 50,2,3);
      colorWipe(strip4.Color(0, 0, 255), 50,2,4);
      colorWipe(strip5.Color(0, 0, 255), 50,2,5);
      matrix2[1][0]=1;
    }
    else if (incoming.startsWith("5") && matrix1[1][1]!=1)
    {
      Serial.println("middle-middle");
      colorWipe(strip3.Color(0, 0, 255), 50,1,3);
      colorWipe(strip4.Color(0, 0, 255), 50,1,4);
      colorWipe(strip5.Color(0, 0, 255), 50,1,5);
      matrix2[1][1]=1;
    }
    else if (incoming.startsWith("6") && matrix1[1][2]!=1)
    {
      Serial.println("middle-right");
      colorWipe(strip3.Color(0, 0, 255), 50,0,3);
      colorWipe(strip4.Color(0, 0, 255), 50,0,4);
      colorWipe(strip5.Color(0, 0, 255), 50,0,5);
      matrix2[1][2]=1;
    }
    else if (incoming.startsWith("7") && matrix1[2][0]!=1)
    {
      Serial.println("bottom-left");
      colorWipe(strip6.Color(0, 0, 255), 50,2,6);
      colorWipe(strip7.Color(0, 0, 255), 50,2,7);
      colorWipe(strip8.Color(0, 0, 255), 50,2,8);
      matrix2[2][0]=1;
    }
    else if (incoming.startsWith("8") && matrix1[2][1]!=1)
    {
      Serial.println("bottom-middle");
      colorWipe(strip6.Color(0, 0, 255), 50,1,6);
      colorWipe(strip7.Color(0, 0, 255), 50,1,7);
      colorWipe(strip8.Color(0, 0, 255), 50,1,8);
      matrix2[2][1]=1;
    }
    else if (incoming.startsWith("9") && matrix1[2][2]!=1)
    {
      Serial.println("bottom-right");
      colorWipe(strip6.Color(0, 0, 255), 50,0,6);
      colorWipe(strip7.Color(0, 0, 255), 50,0,7);
      colorWipe(strip8.Color(0, 0, 255), 50,0,8);
      matrix2[2][2]=1;
    }
    else
    {
      counter--;
    }
    winner=whoWon(2);
  }

  if(winner.startsWith("Player1"))
  {
    entireBoard(strip0.Color(255, 0, 0));
    score1++;
    Serial.println("Score of Player 1");
    Serial.println(score1);
    Serial.println("Score of Player 2");
    Serial.println(score2);
    delay(1000);
    clearAll();
    resetMatrix();
    counter=0;
    Serial.println("Do you want to play again?");
    while(Serial.available()>0)
    {
      replay=Serial.readString();
      Serial.println(replay);
    }
  }
  else if(winner.startsWith("Player2"))
  {
    entireBoard(blue);
    score2++;
    Serial.println("Score of Player 1");
    Serial.println(score1);
    Serial.println("Score of Player 2");
    Serial.println(score2);
    delay(1000);
    clearAll();
    resetMatrix();
    counter=0;
    Serial.println("Do you want to play again?");
    while(Serial.available()>0)
    {
      replay=Serial.readString();
      Serial.println(replay);
      if(replay.startsWith("yes")|| replay.startsWith("no"))
        continue;
    }
  }
  
  if(counter==9)
  {
    Serial.println("Noobs");
    entireBoard(green);
    delay(1000);
    clearAll();
    resetMatrix();
    while(Serial.available()>0)
    {
      replay=Serial.readString();
      Serial.println(replay);
    }
  }
  
  counter++;

  delay(5000);

}

void entireBoard(uint8_t colour)
{
  for(uint16_t i=0; i<strip0.numPixels(); i++) {
      strip0.setPixelColor(i, colour);
      strip0.show();
      delay(50);
  }
  for(uint16_t i=0; i<strip1.numPixels(); i++) {
      strip1.setPixelColor(i, colour);
      strip1.show();
      delay(50);
  }
  for(uint16_t i=0; i<strip2.numPixels(); i++) {
      strip2.setPixelColor(i, colour);
      strip2.show();
      delay(50);
  }
  for(uint16_t i=0; i<strip3.numPixels(); i++) {
      strip3.setPixelColor(i, colour);
      strip3.show();
      delay(50);
  }
  for(uint16_t i=0; i<strip4.numPixels(); i++) {
      strip4.setPixelColor(i, colour);
      strip4.show();
      delay(50);
  }
  for(uint16_t i=0; i<strip5.numPixels(); i++) {
      strip5.setPixelColor(i, colour);
      strip5.show();
      delay(50);
  }
  for(uint16_t i=0; i<strip6.numPixels(); i++) {
      strip6.setPixelColor(i, colour);
      strip6.show();
      delay(50);
  }
  for(uint16_t i=0; i<strip7.numPixels(); i++) {
      strip7.setPixelColor(i, colour);
      strip7.show();
      delay(50);
  }
  for(uint16_t i=0; i<strip8.numPixels(); i++) {
      strip8.setPixelColor(i, colour);
      strip8.show();
      delay(50);
  }
  delay(1000);
}
void colorWipe(uint32_t colour, uint8_t wait,uint8_t pixel,uint8_t strip) {
  switch (strip)
  {
    case 0:
      strip0.setPixelColor(pixel, colour);
      strip0.show();
      break;
    case 1:
      strip1.setPixelColor(pixel, colour);
      strip1.show();
      break;
    case 2:
      strip2.setPixelColor(pixel, colour);
      strip2.show();
      break;
    case 3:
      strip3.setPixelColor(pixel, colour);
      strip3.show();
      break;
    case 4:
      strip4.setPixelColor(pixel, colour);
      strip4.show();
      break;
    case 5:
      strip5.setPixelColor(pixel, colour);
      strip5.show();
      break;
    case 6:
      strip6.setPixelColor(pixel, colour);
      strip6.show();
      break;
    case 7:
      strip7.setPixelColor(pixel, colour);
      strip7.show();
      break;
    case 8:
      strip8.setPixelColor(pixel, colour);
      strip8.show();
      break;
}
}

void clearAll() {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      setBox(i, j, 0);
    };
  };
}

void setBox(int strip, int pixel, uint32_t colour) {
  switch (strip)
  {
    case 0:
      strip0.setPixelColor(pixel, colour);
      strip0.show();
      break;
    case 1:
      strip1.setPixelColor(pixel, colour);
      strip1.show();
      break;
    case 2:
      strip2.setPixelColor(pixel, colour);
      strip2.show();
      break;
    case 3:
      strip3.setPixelColor(pixel, colour);
      strip3.show();
      break;
    case 4:
      strip4.setPixelColor(pixel, colour);
      strip4.show();
      break;
    case 5:
      strip5.setPixelColor(pixel, colour);
      strip5.show();
      break;
    case 6:
      strip6.setPixelColor(pixel, colour);
      strip6.show();
      break;
    case 7:
      strip7.setPixelColor(pixel, colour);
      strip7.show();
      break;
    case 8:
      strip8.setPixelColor(pixel, colour);
      strip8.show();
      break;
  }

}

void resetMatrix()
{
  
  for(int i=0;i<3;i++)
  {
    for(int j=0;j<3;j++)
    {
      matrix1[i][j]=0;
      matrix2[i][j]=0;
    }
  }
}

String whoWon(int num)
{
  if(num==1)
  {
    if(matrix1[0][0]==1 && matrix1[0][1]==1 && matrix1[0][2]==1)
      return "Player1";
    else if(matrix1[1][0]==1 && matrix1[1][1]==1 && matrix1[1][2]==1)
      return "Player1";
    else if(matrix1[2][0]==1 && matrix1[2][1]==1 && matrix1[2][2]==1)
      return "Player1";
    else if(matrix1[0][0]==1 && matrix1[1][0]==1 && matrix1[2][0]==1)
      return "Player1";
    else if(matrix1[0][1]==1 && matrix1[1][1]==1 && matrix1[2][1]==1)
      return "Player1";
    else if(matrix1[0][2]==1 && matrix1[1][2]==1 && matrix1[2][2]==1)
      return "Player1";
    else if(matrix1[0][0]==1 && matrix1[1][1]==1 && matrix1[2][2]==1)
      return "Player1";
    else if(matrix1[0][2]==1 && matrix1[1][1]==1 && matrix1[2][0]==1)
      return "Player1";
  }
  else if(num==2)
  {
    if(matrix2[0][0]==1 && matrix2[0][1]==1 && matrix2[0][2]==1)
      return "Player2";
    else if(matrix2[1][0]==1 && matrix2[1][1]==1 && matrix2[1][2]==1)
      return "Player2";
    else if(matrix2[2][0]==1 && matrix2[2][1]==1 && matrix2[2][2]==1)
      return "Player2";
    else if(matrix2[0][0]==1 && matrix2[1][0]==1 && matrix2[2][0]==1)
      return "Player2";
    else if(matrix2[0][1]==1 && matrix2[1][1]==1 && matrix2[2][1]==1)
      return "Player2";
    else if(matrix2[0][2]==1 && matrix2[1][2]==1 && matrix2[2][2]==1)
      return "Player2";
    else if(matrix2[0][0]==1 && matrix2[1][1]==1 && matrix2[2][2]==1)
      return "Player2";
    else if(matrix2[0][2]==1 && matrix2[1][1]==1 && matrix2[2][0]==1)
      return "Player2";
  }
  return "None";
}
