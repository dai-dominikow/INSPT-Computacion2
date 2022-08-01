
#include <Servo.h>
#include <LiquidCrystal.h>

Servo puerta;
//sintaxis: LiquidCrystal(rs, enable, d4, d5, d6, d7)
//si rw no está conectado a tierra: LiquidCrystal(rs, rw, enable, d4, d5, d6, d7)

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // en lugar de escribir los pines, anteriormente los asigné a variables para mas prolijidad

int pos = 0; //posición inicial de la paleta del servo
int trig=10; //pin digital 
int echo=6; //pin digital
int led_lleno=7;
int led_vacio=8;
int distancia=20;
int duracion;
int delaysensor=1000;
//long delaysensor=3600000;//la idea era que cada una hora sense el nivel del comedero
float v_sonido=0.034; 


void setup() {
puerta.attach(9); // asigna la señal del servo al 9no pin, podría haber declarado como variable este nro.

pinMode(led_lleno,OUTPUT); //salida
pinMode(led_vacio,OUTPUT); //salida
pinMode(trig,OUTPUT); // sale señal
pinMode(echo,INPUT);  // entra señal
Serial.begin(19200); // el 19200 es la velocidad de transmision en bits por segundo

lcd.begin(16,2); // le dá dimensiones a la pantalla LCD
lcd.print("HOLA MARTA!"); // imprime por pantalla LCD

}

//cálculo de la distancia en base al tiempo que mide el sensor ultrasónico desde que sale hasta que vuelve el pulso
long calculaDistancia(int duracion){
long d;
d=(duracion*v_sonido/2); 
 return d;
  }




void loop() {


  //Sensor
  digitalWrite(trig,LOW);
  delayMicroseconds(4);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10); //cuanto dura el pulso que manda el TRIG 
  digitalWrite(trig,LOW);
  duracion=pulseIn(echo,HIGH); // asigna a duración el tiempo medido por el pin ECHO
  distancia = calculaDistancia(duracion); //llama la función que calcula la distancia 
  
  
  Serial.println("DISTANCIA: ");
  Serial.println(calculaDistancia(duracion));
  
// se supone que el nivel del comedero está  a 20 cm del sensor
// o sea, si sensa una distancia mayor a 20 cm, el comedero está vacío
  
  if (distancia>20){
    digitalWrite(led_vacio,HIGH);
    digitalWrite(led_lleno,LOW);
    lcd.setCursor(4,1);
   lcd.print("SIRVIENDO");
    delay(1000);
 for (pos=0;pos<=90;pos++){
      puerta.write(pos);//para que se ubique a diferentes ángulos.
      delay(20);
 }
  for (pos=90;pos>=0;pos--){
    puerta.write(pos);//para que se vuelva.
    delay(10);
  }
 
  }
  else {
    lcd.setCursor(0,1);
    lcd.print("COMEDERO LLENO");
    delay(1000);
    digitalWrite(led_lleno,HIGH);
    digitalWrite(led_vacio,LOW);
    puerta.write(0);
  }
  
        
  delay(delaysensor); 
  lcd.clear();

}
