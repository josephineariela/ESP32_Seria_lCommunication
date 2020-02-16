
#include <HardwareSerial.h>

HardwareSerial MySerial(1);
 
#define RXD2 16
#define TXD2 17
char a[100], sendWord[15], ActTemp[5],ActHum[5], ActLight[8], ActMoist[5];
int i, end_word, end_temp, end_hum, end_light, end_moist;
int j=0;
float ActTemp_float, ActHum_float, ActLight_float, ActMoist_float;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  MySerial.begin(9600, SERIAL_8N1, RXD2, TXD2);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (MySerial.available()>0){
    for (i=0; i< 100; i++){
        a[i] = MySerial.read();
        if (a[i] == 118){ //end_word = v
          end_word = i;
        }else if(a[i] == 119){ //end_temp = w
          end_temp = i;
        }else if(a[i] == 120){ //end_hum = x
          end_hum = i;
        }else if(a[i] == 121){ //end_light = y
          end_light = i;
        }else if(a[i] == 122){ //end_light = z
          end_moist = i;
        } 
    }  
    
    //Save "Sending New Data..." in char of array sendWord[]
    for (i=0; i<end_word; i++){
      sendWord[i] = char(a[i]);
//      Serial.print(sendWord[i]);
    }
    
    //Save ActTemp data in char of array and in float
    for (i=end_word+1; i<end_temp; i++){
      if (j < 6){
        ActTemp[j] = char(a[i]);
//        Serial.print(ActTemp[j]);
        j++;
      }
//      ActTemp[i] = char(a[i]);
//      Serial.print(ActTemp[i]);
    }
    ActTemp_float = atof(ActTemp);
    Serial.println();
    Serial.print("ActTemp : ");
    Serial.print(ActTemp_float);
    j = 0;
    
    //Save ActHum data in char of array and in float
    for (i=end_temp+1; i<end_hum; i++){
      if (j < 6){
        ActHum[j] = char(a[i]);
//        Serial.print(ActHum[j]);
        j++;
      }
//      ActHum[i] = char(a[i]);
//      Serial.print(ActHum[i]);
    }
    ActHum_float = atof(ActHum);
    Serial.println();
    Serial.print("ActHum : ");
    Serial.print(ActHum_float);
    j = 0;

    //Save ActLight data in char of array and in float
    for (i=end_hum+1; i<end_light; i++){
      if (j < 9){
        ActLight[j] = char(a[i]);
//        Serial.print(ActLight[j]);
        j++;
      }
//      ActLight[i] = char(a[i]);
//      Serial.print(ActLight[i]);
    }
    ActLight_float = atof(ActLight);
    Serial.println();
    Serial.print("ActLight : ");
    Serial.print(ActLight_float);
    j = 0;
    
    //Save ActMoist data in char of array and in float
    for (i=end_light+1; i<end_moist; i++){
      if (j < 6){
        ActMoist[j] = char(a[i]);
//        Serial.print(ActMoist[j]);
        j++;
      }
//      ActMoist[i] = char(a[i]);
//      Serial.print(ActMoist[i]);
    }
    ActMoist_float = atof(ActMoist);
    Serial.println();
    Serial.print("ActMoist : ");
    Serial.print(ActMoist_float);
    j = 0;
    
    Serial.println();
  }
}
