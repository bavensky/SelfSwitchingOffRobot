  /*******************************************************************************
   * Project  : IC Shift Register 74HC595                                        *
   * Compiler : Arduino 1.5.2                                                    *
   * Board    : Arduino DUE                                                      *
   * Device   : 8X8 dot matrix display module                                    *
   *          : Servo motor                                                      *
   * Link     : http://myfunnyelectronics.blogspot.in/2014/04/blog-post.html     * 
   * Author   : Bavensky :3                                                      *
   * E-Mail   : Aphirak_Sang-ngenchai@hotmail.com                                *
   * Date     : 14/09/2014 [dd/mm/yyyy]                                          *
   *******************************************************************************/
  #include <Servo.h>
  Servo servo;
  
  int clockPin = 13;  // Pin connected to SH_CP 
  int latchPin = 12;  // Pin connected to ST_CP 
  int dataPin = 11;   // Pin connected to DS 
  
  int buzzer = 0;
  int count = 0;
  int led[8];
  int frame = 0;
  
  int incorrect[8];  
  int smile[8];
  int minismile[8];
  int kiss[8];
  int angry[8];
  int unlike[8];
  
  int emo1[8];
  int emo2[8];
  int emo3[8];
  int emo4[8];
  int emo5[8];
  
  unsigned long timepg;
                
  
  void setup() 
  {
    // Serial begin on baud rate 9600 //
    Serial.begin(9600);
    
    // Set Servo //
    servo.attach(9);
    // Set pin input //
    pinMode(8 , INPUT_PULLUP);
    // Set pin output //
    pinMode(latchPin, OUTPUT);  
    pinMode(clockPin, OUTPUT);  
    pinMode(dataPin, OUTPUT);
    servo.write(0);
    
    //  กากบาท  //
    incorrect[0] =  B10000001;
    incorrect[1] =  B01000010;
    incorrect[2] =  B00100100;
    incorrect[3] =  B00011000;
    incorrect[4] =  B00011000;
    incorrect[5] =  B00100100;
    incorrect[6] =  B01000010;
    incorrect[7] =  B10000001;
    
    //  ยิ้ม  //
    smile[0] =  B01000010;
    smile[1] =  B10100101;
    smile[2] =  B00000000;
    smile[3] =  B01100110;
    smile[4] =  B01100110;
    smile[5] =  B00000000;
    smile[6] =  B01000010;
    smile[7] =  B00111100;
    
    //  ยิ้มมุมปาก  //
    minismile[0] =  B11100111;
    minismile[1] =  B00000000;
    minismile[2] =  B01000010;
    minismile[3] =  B00000000;
    minismile[4] =  B00000000;
    minismile[5] =  B00000010;
    minismile[6] =  B00000100;
    minismile[7] =  B00111000;
    
    //  จูบ  //
    kiss[0] =  B01000010;
    kiss[1] =  B10100101;
    kiss[2] =  B00000000;
    kiss[3] =  B00111000;
    kiss[4] =  B00100000;
    kiss[5] =  B00011000;
    kiss[6] =  B00100000;
    kiss[7] =  B00111000;
    
    //  โกรษ  //
    angry[0] =  B00000000;
    angry[1] =  B11100111;
    angry[2] =  B00000000;
    angry[3] =  B01100110;
    angry[4] =  B01100110;
    angry[5] =  B00000000;
    angry[6] =  B00111100;
    angry[7] =  B01000010; 
    
    //  ไม่ชอบ  //
    unlike[0] =  B00000000;
    unlike[1] =  B01100110;
    unlike[2] =  B01100110;
    unlike[3] =  B00000000;
    unlike[4] =  B00000000;
    unlike[5] =  B01111110;
    unlike[6] =  B00000000;
    unlike[7] =  B00000000;										

    //  อีโมชั่น   //
    //  C  //
    emo1[0] =  B01111110;        
    emo1[1] =  B01000010;
    emo1[2] =  B01000010;
    emo1[3] =  B01000000;
    emo1[4] =  B01000000;
    emo1[5] =  B01000010;
    emo1[6] =  B01000010;
    emo1[7] =  B01111110;
    //  M  //
    emo2[0] =  B10000001;
    emo2[1] =  B11000011;
    emo2[2] =  B10100101;
    emo2[3] =  B10011001;
    emo2[4] =  B10011001;
    emo2[5] =  B10000001;
    emo2[6] =  B10000001;
    emo2[7] =  B10000001;
    //  X  //
    emo3[0] =  B00000000;        
    emo3[1] =  B00000000;
    emo3[2] =  B00000000;
    emo3[3] =  B00000000;
    emo3[4] =  B00000000;
    emo3[5] =  B00000000;
    emo3[6] =  B00000000;
    emo3[7] =  B00000000;

  }
  
  
  void loop() 
  {
    
    if(millis()-timepg > 500) {
      timepg = millis(); 
      frame++;

      if(frame == 1 ) screenInput(emo1);  // C
      if(frame == 2 ) screenInput(emo3);  // X
      if(frame == 3 ) screenInput(emo2);  // M
      if(frame == 4 ) screenInput(emo3);  // X
      if(frame == 5 ) screenInput(emo2);  // M
      if(frame == 6 ) screenInput(emo3);  // X
      if(frame == 7 ) screenInput(emo1);  // C
      if(frame == 8 ) screenInput(emo3);  // X
     
      if (frame > 8) frame = 0;
      
    }
    
    if(digitalRead(8) == 0){
      screenInput(angry);
      servo.write(150);
      frame = 0;
    }
    else{
      servo.write(0);
    }
    
    
    // show dot matrix //
    screenUpdate();
    
  }
  
  
  /******  Input information *****/
  void screenInput(int data[8])
  {
      for(int i=0; i<=7; i++)
      {
        led[i] = data[i];
      }
  }
  
  /****** Show to dot martix *****/
  void screenUpdate() 
  {
    uint8_t row = B00000001;
    for (byte k = 0; k < 9; k++) 
    {
      // Open up the latch ready to receive data
      digitalWrite(latchPin, LOW);
      shiftIt(~row );
      shiftIt(led[k] ); 
      // Close the latch, sending the data in the registers out to the matrix
      digitalWrite(latchPin, HIGH);
      row = row << 1;
    }
  }
  
  void shiftIt(byte dataOut) 
  {
    // Shift out 8 bits LSB first,on rising edge of clock
    boolean pinState;
    //clear shift register read for sending data
    digitalWrite(dataPin, LOW);
    // for each bit in dataOut send out a bit
    for (int i=0; i<8; i++) {
      //set clockPin to LOW prior to sending bit
      digitalWrite(clockPin, LOW);
      // if the value of DataOut and (logical AND) a bitmask
      // are true, set pinState to 1 (HIGH)
      if ( dataOut & (1<<i) ){
        pinState = HIGH;
      }
      else {
        pinState = LOW;
      }
      //sets dataPin to HIGH or LOW depending on pinState
      digitalWrite(dataPin, pinState);
      //send bit out on rising edge of clock
      digitalWrite(clockPin, HIGH);
      digitalWrite(dataPin, LOW);
    }
    //stop shifting
    digitalWrite(clockPin, LOW);
  }

