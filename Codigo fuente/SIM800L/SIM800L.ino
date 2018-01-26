//Módulo de telefonia movil SIM800L
#include "DHT.h";         // Librería del DHT11 (Sensor de temperatura y humedad)

#define DHTPIN 2          // Define el pin de arduino conectado con la salida del sensor
#define DHTTYPE DHT11     // Define el tipo de sensor DTH utilizado


// Configuración del sensor DHT11
DHT dht(DHTPIN, DHTTYPE);

const int LED1 = 3;     // Representa el dispositivo controlado a distancia (como un foco por ejemplo)
const int Puerta1 = 4;  // objeto(1), representa el estado de un objeto tangible, como el estado de una puerta por ejemplo.
                        
int enviar =0;
String Mensaje;

boolean SMS_Open1  = true;
boolean SMS_Closed1  = true;

int hact;
int hant;
int tact;
int tant;

void setup() {
  Serial.begin(19200);
  Serial1.begin(19200);                 //Velocidad de comunicacion con el modulo SIM800L
  dht.begin();
  pinMode(LED1,OUTPUT);                 
  pinMode(Puerta1,INPUT_PULLUP);
  pinMode(8,OUTPUT);                    //Sensor(1) representacion de la salida de un sensor monitoreando el objeto(1).
  Serial1.println("AT+CMGF=1");         // Configurar el módulo en modo de texto
  delay(500);                           //Tiempo de espera para que el modulo se conecte a una red
  Serial1.println("AT+CNMI=2,2,0,0,0"); //Configuracion de la forma como recibir mensajes
  Mensaje.reserve(100);
}

void loop() {
  
  float h = dht.readHumidity(); 
  float t = dht.readTemperature();
  hact=h;                             //lecturas actuales del sensor
  tact=t;                             

  if(tact!=tant || hact!=hant){       //si la lectura actual no coincide con la anterior, 
  Serial.print("Temperatura: ");      //indica un cambio de temperatura o un cambio en la humedad
  Serial.print(String (t));           //por tanto se imprimirá en monitor serie la nueva lectura.
  Serial.print(" C");
  Serial.print(" Humedad: ");
  Serial.print(String (h));
  Serial.println(" %");
                                    
  tant=tact;
  hant=hact;                          //Se actualiza la lectura anterior
  }
  
  //si el SMS recibido contiene "ENCENDER" o "Encender"
    if(Mensaje.indexOf ("ENCENDER") >= 0 || Mensaje.indexOf ("Encender") >= 0) 
    {
      digitalWrite(LED1,HIGH); //Activa dispositivo 
      Mensaje = "";
    }
  
  //si el SMS contiene "APAGAR" o "Apagar"
    if(Mensaje.indexOf ("APAGAR") >= 0 || Mensaje.indexOf ("Apagar") >= 0)
    {
      digitalWrite(LED1,LOW);//Desactiva el dispositivo
      Mensaje = ""; 
    }
  
 // Cuando el sensor esta indicando que la puerta esta abierta:  
   if((digitalRead(Puerta1)  == HIGH) && (digitalRead(8)==LOW)) 
    {
     digitalWrite(8,HIGH);
     SMSPuerta1_Abierta(); //Se envía la notificacion del evento
     SMS_Closed1 = true;
    }
  //Cuando el sensor esta indicando que la puerta se ha cerrado:
    else if ((digitalRead(Puerta1)==LOW) && (digitalRead(8)==HIGH)) 
    {
     digitalWrite(8,LOW);
     SMSPuerta1_Cerrada(); //Se envía la notificacion del evento
     SMS_Open1 = true;
    }

  //Cuando la temperatura sobrepasa el valor límite (30°C)
  if (t > 30.00)
  {
   EnviarSMSTEMP();        
  }
}
//Lo que se escriba en el monitor serie, se trasladará al modulo SIM800L
void serialEvent(){
 if(Serial.available())       
  {
    String text=Serial.readString();
    Serial1.println(text);
  }
}

//Rutina de servicio a la interrupcion para el monitor serie 1
void serialEvent1(){            
  if(Serial1.available() > 0 )
  {
    Mensaje=Serial1.readStringUntil("\n");
    Serial.println("Nuevo Mensaje:");
    Serial.println(Mensaje);
  }
}
    
//Funcion de alerta sobre alta temperatura por SMS
void EnviarSMSTEMP()
{
  if(enviar == 0)
  {
    Serial1.println("AT+CMGF=1");
    delay(200);
    Serial1.println("AT+CMGS=\"+503********\""); //!Ingrese el numero de telefono destino antes de compilar!
    delay(200);
    Serial1.print("Alerta: Se ha detectado una alta temperatura en su habitacion (Temperatura de 30 C)");
    delay(200);
    Serial1.print((char)26);
    delay(200);
    Serial1.println();
    delay(200);
    enviar++;
  }
} 

//Funcion de alerta sobre puerta abierta por SMS
void SMSPuerta1_Abierta() 
{
  if(SMS_Open1 == true)
  {
  Serial1.println("AT+CMGF=1");
  delay(200);
  Serial1.println("AT+CMGS=\"+503********\""); 
  delay(200);
  Serial1.print("Alerta: La puerta pricipal de su residencia se ha abierto");
  delay(200);
  Serial1.print((char)26);
  delay(200);
  Serial1.println("");
  delay(200);
  SMS_Open1 = false;  
  }
}

//Funcion de notificacion de puerta cerrada por SMS
void  SMSPuerta1_Cerrada()
{
 if(SMS_Closed1 == true)
  {
  Serial1.println("AT+CMGF=1");
  delay(200);
  Serial1.println("AT+CMGS=\"+503********\""); 
  delay(200);
  Serial1.print("Su residencia esta segura (Puerta principal cerrada)");
  delay(200);
  Serial1.print((char)26);
  delay(200);
  Serial1.println("");
  delay(200);
  SMS_Closed1 = false;
  }
}
