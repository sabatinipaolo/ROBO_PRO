#include <Arduino.h>
#include "robot.h"
#define PWM_MIN 120

Robot r;


float pwm [ 255 ];
float minimo [ 255 ];
float maximo [ 255 ] ;
float medio [ 255 ];

void stampa(int j,int pwm)
        {Serial.print( pwm );
        Serial.print( " , " );
        SerialUSB.print( minimo[j] );
        Serial.print( " , " );
        Serial.print( medio[j] );
        Serial.print( " , " );
        Serial.print( maximo[j] );
        Serial.println( " , " );}


void setup()
{

  Serial.begin(115200);
  while (!Serial1)
    ;
  Serial.println("Starting program ");    
  
  for (int i = 10; i>0;i--){
        Serial.print("inizio misura tra ");
        Serial.println(i);
        delay(333);
    };


    
for (int index_m=0;index_m<1;index_m++){
    
    Motore &m = r.motori[index_m];

    Serial.println("==============================");
    Serial.println( index_m );
    Serial.println("==============================");
    
    for (int j = 0, pwm = PWM_MIN;
         pwm <= 255;
         j++, pwm += 5)
    {
    
        m.muovi( pwm ); 
        delay(5000);

        minimo[j]=10000; maximo[j]=-10000; medio[j]=0;
        int n_misure = 0;
        while (n_misure <= 10)
        {
            if (m._rpm_valida)
             {
                float rpm= m._rpm;
                if (rpm <minimo[j]) minimo[j]=rpm;
                if (rpm >maximo[j]) maximo[j]=rpm;    
                medio[j]+=rpm;
                n_misure ++; 

                delay(11);
             };
        };

        medio[j] /= n_misure;

        stampa(j,pwm);
        
        m.stop();
        delay(500);



    }
}

}

void loop(){
  
for (int index_m=0;index_m<1;index_m++){
    
    Motore &m = r.motori[index_m];

    Serial.println("============VIUALIZZO==================");
    Serial.println( index_m );
    Serial.println("============VIUALIZZO==================");
    
    for (int j = 0, pwm = PWM_MIN;
         pwm <= 255;
         j++, pwm += 5)
    {
 
        stampa(j,pwm);
        
        m.stop();
        delay(500);



    }
}
}