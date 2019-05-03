// variables pour le capteur de temperature
float Temperature;
int Rref = 15000;
int B = 3950;
double valeurAnalog = 0;
double Rt = 0;
double V = 0;

//variable du capteur de courant
float Courant_Raspberry;

//variables des boutons de la table de nuit
const int btn_1 = 3;
const int btn_2 = 4;
const int btn_3 = 5;
const int btn_4 = 6;

//pins des relais
const int relay_0 = 2;
const int relay_1 = 9;
const int relay_2 = 10;
const int relay_3 = 11;
const int relay_4 = 12;

//états des relais
int st_relay_0 = 0;
int st_relay_1 = 0;
int st_relay_2 = 0;
int st_relay_3 = 0;
int st_relay_4 = 0;

int btn_1_now = 0 ;
int btn_1_prev = btn_1_now ;
int btn_2_now = 0 ;
int btn_2_prev = btn_2_now ;
int btn_3_now = 0 ;
int btn_3_prev = btn_3_now ;
int btn_4_now = 0 ;
int btn_4_prev = btn_4_now ;


String portSerie = "";

//variables pour niveau de batterie
float pourcentage_bat_1 = 0;
float pourcentage_bat_2 = 0;
float t1 = 0;
float t2 = 0;


void setup() {
  Serial.begin(9600);
  pinMode(btn_1, INPUT);
  pinMode(btn_2, INPUT);
  pinMode(btn_3, INPUT);
  pinMode(btn_4, INPUT);

  pinMode(relay_0, OUTPUT);
  pinMode(relay_1, OUTPUT);
  pinMode(relay_2, OUTPUT);
  pinMode(relay_3, OUTPUT);
  pinMode(relay_4, OUTPUT);

  //initialisation des relais a 0
  digitalWrite(relay_0, HIGH);
  digitalWrite(relay_1, HIGH);
  digitalWrite(relay_2, HIGH);
  digitalWrite(relay_3, HIGH);
  digitalWrite(relay_4, HIGH);
}

void loop() {


  //calcul du courant
  Courant_Raspberry=-((analogRead(2)-512)*5)/(1024*0.185);
  Serial.print("{\"Courant_Raspberry\":");  
  Serial.print(Courant_Raspberry);
  Serial.print(",");


  
  //calcul de la temperature
  valeurAnalog = analogRead(3);
  V=(valeurAnalog / 1024) *5;
  Rt = ((75000)/V)-Rref;
  Temperature = (1/((log(Rt/10000)/B)+(1/(25+273.15))))-273.15;
  Serial.print("\"température\":");  
  Serial.print(Temperature);
  Serial.print(",");
  



  //calcul du niveau de batterie
  t1 = analogRead(5);
  t2 = analogRead(4);
  pourcentage_bat_1 = t1*5/1024 ;
  pourcentage_bat_2 = t2*5/1024 ;
  
  Serial.print("\"pourcentage_batterie_1\":");  
  Serial.print(pourcentage_bat_1);
  Serial.print(",");
  
  Serial.print("\"pourcentage_batterie_2\":");  
  Serial.print(pourcentage_bat_2);
  Serial.print(",");


  //gestion des relais
  portSerie = Serial.readString();
  
  if (((portSerie == "SW1") or (not(btn_1_prev) and btn_1_now))and st_relay_1==0)
    {digitalWrite(relay_1, LOW);
    st_relay_1 = 1;}
  else if (((portSerie == "SW1") or (not(btn_1_prev) and btn_1_now))and st_relay_1)
    {digitalWrite(relay_1, HIGH);
    st_relay_1 = 0 ;}
      
  if (((portSerie == "SW2") or (not(btn_2_prev) and btn_2_now))and st_relay_2==0)
    {digitalWrite(relay_2, LOW);
    st_relay_2 = 1;}
  else if (((portSerie == "SW2") or (not(btn_2_prev) and btn_2_now))and st_relay_2)
    {digitalWrite(relay_2, HIGH);
    st_relay_2 = 0;}

  if (((portSerie == "SW3") or (not(btn_3_prev) and btn_3_now))and st_relay_3==0)
    {
    digitalWrite(relay_3, LOW);
    st_relay_3 = 1;}
  else if (((portSerie == "SW3") or (not(btn_3_prev) and btn_3_now))and st_relay_3)
    {
    digitalWrite(relay_3, HIGH);
    st_relay_3 = 0;}
      
  if (portSerie == "SW4" and st_relay_4==0)
    {digitalWrite(relay_4, LOW);
    st_relay_4 = 1;}
  else if (portSerie == "SW4" and st_relay_4)
    {digitalWrite(relay_4, HIGH); 
    st_relay_4 = 0;}
    
  if (((portSerie == "SW0") or (not(btn_4_prev) and btn_4_now))and st_relay_0==0)
    {digitalWrite(relay_0, LOW);
    st_relay_0 = 1;}
  else if (((portSerie == "SW0") or (not(btn_4_prev) and btn_4_now))and st_relay_0)
    {digitalWrite(relay_0, HIGH); 
    st_relay_0 = 0;}

  Serial.print("\"etat_relais_1\":");  
  Serial.print(st_relay_1);
  Serial.print(",");
  
  Serial.print("\"etat_relais_2\":");  
  Serial.print(st_relay_2);
  Serial.print(",");
  
  Serial.print("\"etat_relais_3\":");  
  Serial.print(st_relay_3);
  Serial.print(",");
  
  Serial.print("\"etat_relais_4\":");  
  Serial.print(st_relay_4);
  Serial.println("}");


  // 4 machines a etats
  btn_1_prev = btn_1_now ;
  btn_1_now = digitalRead(btn_1) ;
  btn_2_prev = btn_2_now ;
  btn_2_now = digitalRead(btn_2) ;
  btn_3_prev = btn_3_now ;
  btn_3_now = digitalRead(btn_3) ;
  btn_4_prev = btn_4_now ;
  btn_4_now = digitalRead(btn_4) ;
      
}
