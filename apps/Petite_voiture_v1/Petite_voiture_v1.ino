/*
Code arduino pour le demonstrateur de Kirrk by Mobioos. 
Version 19/09/2019 
Fonctionnalités présente: 
- Controle de l'alimentation de la radio 
- Controle de l'alimentation des 4 feux indépendant
- Controle de l'ouverture du coffre et de la LED associée, ainsi qu'une fermeture autoatmique au bout de 10 secondes. 

*/


#define PIN_Servo 1
#define PIN_Feux_Ar_D 2
#define PIN_Feux_Ar_G 3
#define PIN_Feux_Av_D 4
#define PIN_Feux_Av_G 5
#define PIN_LED_Coffre_R 6      //Doit être un pin PWM pour faire varier la luminosité 
#define PIN_LED_Coffre_G 7      //Doit être un pin PWM pour faire varier la luminosité 
#define PIN_LED_Coffre_B 8      //Doit être un pin PWM pour faire varier la luminosité
#define PIN_LED_Dessous_R 6      //Doit être un pin PWM pour faire varier la luminosité 
#define PIN_LED_Dessous_G 7      //Doit être un pin PWM pour faire varier la luminosité 
#define PIN_LED_Dessous_B 8      //Doit être un pin PWM pour faire varier la luminosité
#define PIN_Radio 9      

long TimerCoffre = 0 ;
bool CoffreOuvert = false ;


void setup() {
  pinMode(PIN_Servo,OUTPUT);
  pinMode(PIN_Feux_Ar_D,OUTPUT);
  pinMode(PIN_Feux_Ar_G,OUTPUT);
  pinMode(PIN_Feux_Av_D,OUTPUT);
  pinMode(PIN_Feux_Av_G,OUTPUT);
  pinMode(PIN_LED_Coffre_R,OUTPUT);
  pinMode(PIN_LED_Coffre_G,OUTPUT);
  pinMode(PIN_LED_Coffre_B,OUTPUT);
  pinMode(PIN_Radio,OUTPUT);
  
  digitalWrite(PIN_Radio,HIGH);  //De base la radio est allumée. 
  
}

void loop() {
  
  
  
  
  
  // Si le timer du coffre est révolut et qu'il est ouvert --> le fermer: 
  if ( ( millis() > TimerCoffre ) && CoffreOuvert) {
    Ouverture_Coffre(false);
  }
    
}





void Ouverture_Coffre(bool Open){
  if (Open){
    CoffreOuvert = true ;
    
    // Lancer le timeur : 
    TimerCoffre = millis() + 10000 ;    //Le coffre se referme 10 secondes aprés ouverture. 
    
    // Change la couleur à Vert : 
    digitalWrite(PIN_LED_Coffre_G,HIGH);
    digitalWrite(PIN_LED_Coffre_R,LOW);
    digitalWrite(PIN_LED_Coffre_B,LOW);
    
    // Mettre le servo à X° : 
    
    
  }
  else {
    CoffreOuvert = false ;
    
    // Change la couleur à Rouge : 
    digitalWrite(PIN_LED_Coffre_G,LOW);
    digitalWrite(PIN_LED_Coffre_R,HIGH);
    digitalWrite(PIN_LED_Coffre_B,LOW);
    
    // Mettre le servo à X° : 
    
  }
}



void Radio_On(bool ON){
  if (ON){
    digitalWrite(PIN_Radio,HIGH); 
  }
  else {
    digitalWrite(PIN_Radio,LOW); 
  }
}



void Controle_Feux (bool Av_G, bool Av_D, bool Ar_D, bool Ar_G){
  if (Av_G){
    digitalWrite(PIN_Feux_Av_G,HIGH); 
  }
  else {
    digitalWrite(PIN_Feux_Av_G,LOW); 
  }
  
  if (Av_D){
    digitalWrite(PIN_Feux_Av_D,HIGH); 
  }
  else {
    digitalWrite(PIN_Feux_Av_D,LOW); 
  }
  
  if (Ar_D){
    digitalWrite(PIN_Feux_Ar_D,HIGH); 
  }
  else {
    digitalWrite(PIN_Feux_Ar_D,LOW); 
  }
  
  if (Ar_G){
    digitalWrite(PIN_Feux_Ar_G,HIGH); 
  }
  else {
    digitalWrite(PIN_Feux_Ar_G,LOW); 
  }
}
