#include <DHT.h>                // Biblioteca DHT
#include <SPI.h>                // SSD1396
#include <Wire.h>               // SSD1396
#include <Adafruit_Sensor.h>
#include <WiFi.h>
#include "general.h"


/* Defines do projeto */
#define REED          27    // pin onde o sensor magnetico esta conectado
#define DHTPIN        33    // pin onde dht esta conectado
// #define WindSensor    35    // The pin location of the anemometer sensor

#define DIAMETRO 125       // diametro interno do balde
#define RAIO     6.25      // raio interno do balde
#define VOLUME   3.05      // volume da bascula (em cm3) (1cm3 == 1ml) (1ml == 1000mm3)

#define DHTTYPE DHT11 // DHT 22
DHT dht(DHTPIN, DHTTYPE);

// Broker defines
#define BROKER_ADDRESS    "000.000.0.0 " // "3.133.207.110"
#define BROKER_PORT       8000
#define BROKER_USE_SECURE false


unsigned long lastSend;
unsigned long lastREED;

// Variáveis DHT
float temperatura_lida = 0;
float umidade_lida = 0;

// Variáveis pluviometro:
int val = 0;
int old_val = 0;
volatile unsigned long REEDCOUNT = 0;
float volume_coletado;

// Variable definitions
unsigned int Sample = 0;   // Sample number
unsigned int counter = 0; // magnet counter for sensor
unsigned long RPM = 0;            //Rotações por minuto
float speedwind = 0;             //Velocidade do vento (km/h)
float windspeed = 0;             //Velocidade do vento (m/s)

// Variaveis Anemometro
const float pi = 3.14159265;     //Número de pi
int period = 5000;               //Tempo de medida(miliseconds)
int delaytime = 2000;            //Invervalo entre as amostras (miliseconds)
int radius = 120;                //Raio do anemometro(mm)

volatile unsigned long ContactBounce = 0;

// This is the function that the interrupt calls to increment the turning count
void IRAM_ATTR isr_rain () {
  if ((millis() - ContactBounce) > 0 ) { // debounce the switch contact.
    REEDCOUNT = REEDCOUNT + 1;              // Adiciona 1 à cntagem de pulsos
    // ContactBounce = millis();
    // Serial.println("funcao interrupcao chuva");
  }
}

// void isr_rain() {
//   if (REED == HIGH) {
//     if ((millis() - ContactBounce) > 0 ) { // debounce the switch contact.
//       REEDCOUNT = REEDCOUNT + 1;              // Adiciona 1 à cntagem de pulsos
//       ContactBounce = millis();
//     }
//   }
// }

/*    ME DESCOMENTE PARA TER AS FUNÇÕES DO ANEMOMETRO LIGADAS
void addcount(){
  counter++;
} 

// Measure wind speed
void windvelocity(){
  speedwind = 0;
  windspeed = 0;
  
  counter = 0;  
  attachInterrupt(0, addcount, RISING);
  unsigned long millis();       
  long startTime = millis();
  while(millis() < startTime + period) {
  }
}

//Função para calcular o RPM
void RPMcalc() {
  RPM = ((counter) * 60) / (period / 1000); // Calculate revolutions per minute (RPM)
}

//Velocidade do vento em m/s
void WindSpeed() {
  windspeed = ((4 * pi * radius * RPM) / 60) / 1000; //Calcula a velocidade do vento em m/s
} //end WindSpeed

//Velocidade do vento em km/h
void SpeedWind() {
  speedwind = (((4 * pi * radius * RPM) / 60) / 1000) * 3.6; //Calcula velocidade do vento em km/h
} //end SpeedWind

    MEU COMENTARIO ACABA AQUI  */   

void get_temp(){
    temperatura_lida = dht.readTemperature();

    Serial.print("T: ");                    //ESCREVE O TEXTO NO DISPLAY
    Serial.println(temperatura_lida);
}

void get_umi(){
    umidade_lida = dht.readHumidity();  

    Serial.print("U: ");                    //ESCREVE O TEXTO NO DISPLAY   
    Serial.println(umidade_lida);
}

void get_rain(){
  // isr_rain();
  // float area_recipiente = 3.14159265 * (RAIO * RAIO); // área da seção transversal do recipiente em cm²
  // float volume_por_virada = (VOLUME/area_recipiente);
  // volume_coletad = volume_por_virada * REEDCOUNT * 10;
  volume_coletado = (REEDCOUNT * 0.25) * 10; // volume total coletado em cm³

  Serial.print("Viradas: ");
  Serial.println(REEDCOUNT);

  Serial.print("Chuva: ");
  Serial.print (volume_coletado);
  Serial.println(" mm");

  if(millis() - lastREED > 86400000) { 
    REEDCOUNT = 0;

    lastREED = millis(); 
  }
}

/*
void get_wind(){
    Sample++;
    Serial.print(Sample);
    Serial.print(": Start measurement...");
    windvelocity();
    Serial.println("   finished.");
    Serial.print("Counter: ");
    Serial.print(counter);
  
    RPMcalc();
    Serial.print("RPM: ");
    Serial.println(RPM);

    WindSpeed();
    Serial.print("WindSpeed [m/s]: ");
    Serial.println(windspeed);

    SpeedWind();
    Serial.print("WindSpeed [km/h]: ");
    Serial.println(speedwind);
}
*/

void send_packets(){
  // Crie um array de bytes para armazenar os dados


  // temperatura_lida = 21;
  // umidade_lida = 56;
  // volume_coletado = 21.42;
  // windspeed = 5.24;

  /*FUNÇÃO DE ENVIO PARA O SERVIDOR DO EDUARDO */

  sprintf(strbuf, "{\"version\" : %d, \"temp\" : %.1f, \"umid\" : %.1f, \"anem\" : %.1f, \"pluv\" : %.1f}", 
          FW_VERSION, temperatura_lida, umidade_lida, windspeed, volume_coletado);
  Serial.println(strbuf);
  client.publish(topic_out, strbuf);


};

void setup() {
  Serial.begin(115200);       // velocidade monitor serial

  initSPIFFS();
  
  if (initWiFi()){
    server_config();

    client.setServer(BROKER_ADDRESS, BROKER_PORT);
    client.setCallback(on_message);
    if (client.connect("aquisiton")){
      client.subscribe(topic_in);
    }
    wifi_success = true;
  } 
  else {
    wifi_config();
  }

  /* Inicializa sensor de temperatura e umidade relativa do ar */
  dht.begin();
  Serial.println(mac);

  
  lastSend = 0;
  lastREED = 0;

  // pinMode(WindSensor, INPUT);
  // digitalWrite(WindSensor, HIGH);     //internall pull-up active
  pinMode(REED, INPUT_PULLUP);
  attachInterrupt(REED, isr_rain, FALLING);
}

void loop() {

  // Aquisição de dados dos sensores DHT22 e Pluviometro
  get_temp();
  get_umi();
  get_rain();
  if (client.connected()) // Verifica conexão com broker e calcula tempo para envio da publicação, tempo em ms
  { 
    if(millis() - lastSend > 300000)
    {
      // get_wind();
      Serial.println("Sending packet !!!");
      delay(100);
      
      send_packets(); // Envio de pacotes através da rede WiFi pro broker MQTT

      // sendMessage();  // Envio de mensagem através da rede Mesh
      lastSend = millis();   // Atualiza valor atual do contador de ultimo envio
    }
  } 
  else
  {
    reconnect();
  }
  // mesh.update();  // Update para entrada e saida de nodos na rede Mesh
  client.loop();

}
