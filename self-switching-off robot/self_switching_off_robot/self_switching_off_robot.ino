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
  Servo mainservo;
  Servo doorservo;
  Servo lostservo;
  
  int clockPin = 13;  // Pin connected to SH_CP 
  int latchPin = 12;  // Pin connected to ST_CP 
  int dataPin = 11;   // Pin connected to DS 
  
  int count = 0;
  int led[8];
  int frame = 0;
  int r=500, l=0, u=0, s=0;
  
  long z;
  unsigned long timepg;
  
  int incorrect[8];  
  int smile[8];
  int minismile[8];
  int kiss[8];
  int angry1[8];
  int angry2[8];
  int angry3[8];
  int unlike[8];
  int cry[8];

  
  int emo1[8];
  int emo2[8];
  int emo3[8];
  int emo4[8];
  int emo5[8];
  
  void setup() 
  {
    // Serial begin on baud rate 9600 //
    Serial.begin(9600);
    randomSeed(analogRead(0));
    // Set Servo //
    mainservo.attach(9);
    doorservo.attach(10);
    // Set pin input //
    pinMode(8 , INPUT_PULLUP);
    // Set pin output //
    pinMode(latchPin, OUTPUT);  
    pinMode(clockPin, OUTPUT);  
    pinMode(dataPin, OUTPUT);
    mainservo.write(0);
    
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
    minismile[2] =  B01100110;
    minismile[3] =  B01100110;
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
    
    //  โกรษ นิด ๆ   //
    angry1[0] =  B01000010;
    angry1[1] =  B00100100;
    angry1[2] =  B00011000;
    angry1[3] =  B01100110;
    angry1[4] =  B01100110;
    angry1[5] =  B00000000;
    angry1[6] =  B00111100;
    angry1[7] =  B00000000; 
    
    //  โกรษ มาก  //
    angry2[0] =  B01000010;
    angry2[1] =  B00100100;
    angry2[2] =  B00011000;
    angry2[3] =  B01100110;
    angry2[4] =  B01100110;
    angry2[5] =  B00000000;
    angry2[6] =  B00111100;
    angry2[7] =  B01000010; 
   
    //  โกรษ มาก ๆ  //
    angry3[0] =  B00000000;
    angry3[1] =  B11100111;
    angry3[2] =  B00000000;
    angry3[3] =  B01100110;
    angry3[4] =  B01100110;
    angry3[5] =  B00000000;
    angry3[6] =  B00111100;
    angry3[7] =  B01000010;  
    
    //  ร้องไห้   //
    cry[0] =  B10000001;
    cry[1] =  B01000010;
    cry[2] =  B00100100;
    cry[3] =  B01000010;
    cry[4] =  B10000001;
    cry[5] =  B00000000;
    cry[6] =  B00111100;
    cry[7] =  B01000010;

    //  ไม่ชอบ  //
    unlike[0] =  B00000000;
    unlike[1] =  B00000000;
    unlike[2] =  B01100110;
    unlike[3] =  B01100110;
    unlike[4] =  B00000000;
    unlike[5] =  B00000000;
    unlike[6] =  B01111110;
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
    //  Big eye  //
    emo4[0] =  B00000000;        
    emo4[1] =  B01000010;
    emo4[2] =  B10100101;
    emo4[3] =  B10100101;
    emo4[4] =  B10100101;
    emo4[5] =  B01000010;
    emo4[6] =  B00000000;
    emo4[7] =  B00111100;
    //  smile eye  //
    emo5[0] =  B00000000;        
    emo5[1] =  B00000000;
    emo5[2] =  B00000000;
    emo5[3] =  B11100111;
    emo5[4] =  B00000000;
    emo5[5] =  B00000000;
    emo5[6] =  B00000000;
    emo5[7] =  B00111100;
    u=1;
  }
  
  
  void loop() 
  {
    
  if(u==1){  
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
      if(frame > 8) frame=0;
    }
  }
  
  if(u==2){  
    if(millis()-timepg > 500) {
      timepg = millis(); 
      frame++;
      if(frame == 1 ) screenInput(emo4);     
      if(frame == 2 ) screenInput(emo5);  
      if(frame == 3 ) screenInput(emo4);
      if(frame == 4 ) screenInput(emo5);  
      if(frame == 5 ) screenInput(emo4);
      if(frame == 6 ) screenInput(emo5);
      if(frame == 7 ) screenInput(emo4);
      if(frame > 7){ frame=0;}  
    }
  }
  
  if(u==3 ){
  screenInput(smile);
  }
  if(u==4 ){
  screenInput(minismile);
  }
  if(u==5 ){
  screenInput(cry);
  }



  /*********** Working ***********/
    if(digitalRead(8) == 0){
      step1(); 
      u++;
    }
    else{
      mainservo.write(0);
      doorservo.write(10);
    }
    
    // show dot matrix //
    screenUpdate();
    
  } // End loop //
  
  void step1()
  {
      doorservo.write(90);
      mainservo.write(150);
      
      r = r-100; 
      for(int k=0; k<r; k++){
        screenInput(angry2);
        screenUpdate();
      }
      if(r == 0){
        r = 100;
        l = 1;
      }
      if(l == 1){
        mainservo.write(120);
        for(int k=0; k<1000; k++){
          screenInput(angry3);
          screenUpdate();
        }
        mainservo.write(150);
        l=2;
        r=500;
      }
      if(l == 2){
        screenInput(angry3);
        screenUpdate();
        if(u>5) u=0;
        mainservo.write(0);
        doorservo.write(10);
        l=3;
      }
      while(l == 3){
        step2();
      }
    frame = 0;
  }
  
  void step2()
  {
   
     if(digitalRead(8) == 0){
      doorservo.write(90);
      mainservo.write(150);
      z = random(300);
      
      for(int k=0; k<z; k++){
        screenInput(angry2);
        screenUpdate();
      }
      
      if(z > 250){
      mainservo.write(120);
      doorservo.write(90);
      
      for(int k=0; k<1000; k++){
        screenInput(minismile);
        screenUpdate();
      }
      doorservo.write(10);
      mainservo.write(150);
      z=0;
      }  
    }
    else if(digitalRead(8) == 1){
      screenInput(angry2);
      screenUpdate();
      mainservo.write(0);
      doorservo.write(10);
    }
    
  }
  
  /************************ Dot Matrix Display ****************************/
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
