
int SERV = 12 ;
int duree;

void setup() {
  pinMode(SERV, OUTPUT);
  Serial.begin(9600);
  Serial.println("Initialisation");
}

void loop() { 
  
     Serial.println("Ouverture");
    for (int duree = 1450 ; duree >= 850 ; duree=duree-20) {
     digitalWrite(SERV, HIGH);
     delayMicroseconds(duree);
     digitalWrite(SERV, LOW);
     delayMicroseconds(20000-duree);
     }
       
    delay(2000);

    Serial.println("Fermeture");
    for (int duree = 850 ; duree <= 1450 ; duree=duree+30) {
     digitalWrite(SERV, HIGH);
     delayMicroseconds(duree);
     digitalWrite(SERV, LOW);
     delayMicroseconds(20000-duree);
     }
   
    delay(2000);
}
