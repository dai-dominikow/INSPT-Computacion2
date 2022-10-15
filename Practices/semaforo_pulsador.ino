//Daiana Dominikow - 2020

//los pines
int contador =0;
int rojo = 12; 
int amarillo = 11;
int verde = 10;
int boton = 7;
int pulsador;

void setup() {

pinMode(rojo , OUTPUT ); 
pinMode(amarillo , OUTPUT ); 
pinMode(verde , OUTPUT ); 
pinMode(boton , INPUT ); //pulsador

}

void loop(){
  
  if (digitalRead(boton)){
    digitalWrite(amarillo,HIGH);
    delay(2000);
    digitalWrite(amarillo,LOW);
    digitalWrite(verde,LOW);
    digitalWrite(rojo,HIGH);
    delay(5000);
  } else {
    digitalWrite(verde,HIGH);
    digitalWrite(rojo,LOW);
    digitalWrite(amarillo,LOW);
  }
  
}