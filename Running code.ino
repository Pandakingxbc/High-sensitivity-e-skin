int readLine[4] = {2, 3, 4, 5};
int scanning[4] = {8, 6, 7, 14};
int LED[3] = {21,22,23};
void setup() {

  for(int i = 0; i < 4; i++){
  pinMode(scanning[i], OUTPUT);

  }


  for(int i = 0; i < 4; i++){
     pinMode(readLine[i], INPUT);
     
  }
  Serial.begin(14400);
}

int readOut[4][4];

void loop() {
  // put your main code here, to run repeatedly:
    for(int i = 0; i < 4; i++){
        digitalWrite(scanning[i], LOW);
       // analogWrite(scanning[i], 0);
        delay(10);
        for(int j = 0; j < 4; j++){
        readOut[i][j] = analogRead(readLine[j]);
        }
       //  analogWrite(scanning[i], 76);
        digitalWrite(scanning[i], HIGH);
        
     }
     // realize the LED light function according to the detecting sensor array data
     float threshold = 0.2;
     int x1 = 1;
     int y1 = 1;
     // design three LED that can reflect the force suitation of two locations
     int x2 = 2;
     int y2 = 2;
     
     int x3 = 0;
     int y3 = 0; 

     bool result1 = checkMatrixValue(readOut, threshold, x1, y1);
     bool result2 = checkMatrixValue(readOut, threshold, x2, y2);
     bool result3 = checkMatrixValue(readOut, threshold, x3, y3);
    if(result1){
      digitalWrite(LED[0], HIGH);

    }
    else{
      digitalWrite(LED[0], LOW);

    }

    if(result2){
       digitalWrite(LED[1], HIGH);

    }
    else{
       digitalWrite(LED[1], LOW);

    }

    if(result3){
       digitalWrite(LED[2], HIGH);

    }
    else{
       digitalWrite(LED[2], LOW);

    }    

    for(int i = 0; i < 4; i++){
    for(int j = 2; j >= 0; j--){
    float pressure = map(readOut[i][j], 0, 4095 , 0, 5*4096);
    pressure /= 4096.0;
    if(pressure <= 1.26){
     Serial.print(0, 2);
     Serial.print("   ");
    }
    else{
    pressure = pressure - 1.26;
    Serial.print(pressure*1.96, 2);
    Serial.print(" ");
    }
    }
    Serial.println();
    }
    Serial.println("----------");
    delay(100);
}




bool checkMatrixValue(int matrix[4][4], float threshold, int x, int y){

float pressure = map(matrix[x][y], 0, 4095, 0, 5*4096);
pressure /= 4096.0;

if(pressure >= threshold){
   return true;

}

return false;


} 


