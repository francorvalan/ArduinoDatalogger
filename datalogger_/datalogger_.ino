// intento 15/01/2022

#include <RTClib.h>  //Libreria para el reloj
#include <SD.h> // Libreria para tarjeta sd
#include <OneWire.h> // Libreria para el sensor 
#include <DallasTemperature.h> // Libreria para el sensor 

OneWire ourWire(9); //entrada del sensor en el arduino mega
DallasTemperature ds18b20(&ourWire); // declaracion nombre del sensor

//OneWire oneWireObjeto(pinDatosDQ);
//DallasTemperature sensorDS18B20(&oneWireObjeto);
//********** Direcciones de sensores ************//
DeviceAddress address1 = {0x28, 0xF8, 0xA7, 0x7B, 0x7, 0x0, 0x0, 0xE9};
DeviceAddress address2 = {0x28, 0xC4, 0x89, 0x7A, 0x7, 0x0, 0x0, 0xAC};
DeviceAddress address3 = {0x28, 0x7, 0x2D, 0x7C, 0x7, 0x0, 0x0, 0x4F};
//**********************************************//

const int CS=10; // chip select de la tarjeta sd

/************config de reloj****************/
RTC_DS3231 RTC; // delacarion de tipo de reloj
byte lastminute = 0; // variable para almacenar el ultimo minuto
DateTime now; // variable de fecha completa
unsigned int year; 
byte month, day, hour, minute, second;
//****************************************//

float t1; // Variables 
float t2; // de
float t3; // temperatura

 void setup(){
    Serial.begin(9600); // inicio puerto serie
    RTC.begin(); // inicio reloj
    ds18b20.begin(); // inicio sensores
    // *** compruebo si hay tarjeta insertada ****//
    if(!SD.begin(CS)){
        Serial.println("No se pudo inicializar SD"); // Escribimos por pantalla
        return;
        }  
    /////////////////////////////////////////////////

    //// obtengo fecha y hora
    now = RTC.now();  
    year = now.year ();
    month = now.month ();
    day = now.day ();
    hour = now.hour ();
    minute = now.minute ();
    second = now.second ();
    ///////////

    // obtengo temperaturas y las guardo en variables
    ds18b20.requestTemperatures();   
    t1=ds18b20.getTempCByIndex(0);
    t2=ds18b20.getTempCByIndex(1);
    t3=ds18b20.getTempCByIndex(2);
    
    grabar(); // llamo a la funcion grabar
    
}

// ===== CONFIGURACIÓN =====
const byte intervaloMinutos = 1; // Intervalo de grabación
// =========================

void loop() {
    now = RTC.now();
    year = now.year();
    month = now.month();
    day = now.day();
    hour = now.hour();
    minute = now.minute();
    second = now.second(); 

    // Leer temperaturas
    ds18b20.requestTemperatures();   
    t1 = ds18b20.getTempCByIndex(0);
    t2 = ds18b20.getTempCByIndex(1);
    t3 = ds18b20.getTempCByIndex(2);
  
    // Comparar si cambió el intervalo de grabación y si coincide con el intervalo
    if (now.minute() != lastminute) {
        if ((now.minute() % intervaloMinutos) == 0) {
            grabar();
            lastminute = now.minute();
        }
    }

    // Comprobar tarjeta SD (opcional)
    if (!SD.begin(CS)) {
        Serial.println("No se pudo inicializar");
        return;
    }
    Serial.println("Inicialización exitosa");
    
    // Pequeña pausa para no saturar el bucle
    delay(500); 
}