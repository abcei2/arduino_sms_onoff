
#include <SoftwareSerial.h>

#define SIM800_TX_PIN 3             //SIM800 TX is connected to Arduino D3
#define SIM800_RX_PIN 2             //SIM800 RX is connected to Arduino D2

SoftwareSerial serialSIM800(SIM800_TX_PIN, SIM800_RX_PIN);

boolean command_readed=true;
void setup(void)
{
  pinMode(5, OUTPUT);  //Pin de salida que va al relé y pone el color deseado

  Serial.begin(9600);
  serialSIM800.begin(9600);

  serialSIM800.println(F("AT+CMGF=1"));            //Configuramos el módulo para trabajar con los SMS en modo texto
  delay(500);                                      //Pausa de medio segundo

  serialSIM800.println(F("AT+CNMI=1,2,0,0,0"));
  delay(500);

  while (serialSIM800.available() > 0)
  {
    serialSIM800.read();
    Serial.println(serialSIM800.read());
  }
  Serial.println("DONE SETUP");
}

void loop(void)
{

  if (serialSIM800.available() > 1)
  {

    serialAvailable();
  }
  
}

void serialAvailable()   //Cuando hay algo en el buffer del gsm entra aqui
{
  String command = serialSIM800.readString();
 
  Serial.println(command);
  if(command_readed){
    if(command.indexOf("COMANDO:")>0){
      if(command.indexOf("ON")>0){
        Serial.println("prendasa mierda");
      }else if (command.indexOf("OFF")>0){      
        Serial.println("apague sa mierda");
      }else{
        Serial.println("compa no le entiendo");
      }
    }else{
      Serial.println("compa no conoce la seña?");
    }
        
    
    command_readed=true;
     
  }else{
    if(command.indexOf("+CMT")>0){
      
      Serial.println("a la espera de un comando");
      command_readed=false;    
    }            
  }
  delay(1000);
}



void EnviaSMS() {
  serialSIM800.println("AT+CMGF=1");                 // Activamos la funcion de envio de SMS
  delay(100);                                    // Pequeña pausa
  serialSIM800.println("AT+CMGS=\"+573113444461\"");  // Definimos el numero del destinatario en formato internacional
  delay(100);                                    // Pequeña pausa
  serialSIM800.print("Como diría jose; 'este es un mensaje del inframundo!' (desde arduino)");                 // Definimos el cuerpo del mensaje
  delay(500);                                    // Pequeña pausa
  serialSIM800.print(char(26));                      // Enviamos el equivalente a Control+Z
  delay(100);                                    // Pequeña pausa
  serialSIM800.println("");                          // Enviamos un fin de linea
  delay(100);                                    // Pequeña pausa
}
