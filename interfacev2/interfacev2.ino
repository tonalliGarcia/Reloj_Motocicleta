#include <Wire.h>
#include <RTClib.h>
#include <TFT.h>
#include <SPI.h>

// Pines para la pantalla TFT
#define cs   10
#define dc   9
#define rst  8

// Inicializa la pantalla TFT
TFT TFTscreen = TFT(cs, dc, rst);

// Inicializa el RTC DS1307
RTC_DS1307 rtc;

// Definir los días de la semana
//char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
char daysOfTheWeek[7][12] = {"Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado"};

void setup() {
  // Inicia la comunicación serial
  Serial.begin(57600);

  // Inicializa la pantalla TFT
  TFTscreen.begin();
  TFTscreen.setRotation(0);  // Ajusta la orientación
  TFTscreen.background(0, 0, 0);  // Fondo negro

  // Verifica si el RTC está conectado
  if (!rtc.begin()) {
    Serial.println("No se pudo encontrar el RTC");
    while (1);  // Se queda en bucle si no se encuentra el RTC
  }

  // Si el RTC no está corriendo, se ajusta la hora al tiempo actual de compilación
  if (!rtc.isrunning()) {
    Serial.println("RTC no está corriendo, ajustando el tiempo.");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  // Configura la pantalla inicial
  TFTscreen.stroke(255, 255, 255);
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop() {
  // Obtiene la hora actual del RTC
  DateTime now = rtc.now();

  // Limpia la pantalla antes de actualizar los datos
  TFTscreen.background(0, 0, 0);

  // *** Mostrar el día de la semana ***
  TFTscreen.setTextSize(2);
  TFTscreen.stroke(0, 255, 255);  // Color cian para el día de la semana
  TFTscreen.text(daysOfTheWeek[now.dayOfTheWeek()], 30, 10);  // Centrado en la parte superior

  // *** Mostrar la fecha en formato DD/MM/YYYY ***
  TFTscreen.setTextSize(2);  // Tamaño de texto más grande para la fecha
  TFTscreen.stroke(255, 255, 0);  // Color amarillo para la fecha
  
  char dateBuffer[11];  // Buffer para la fecha
  sprintf(dateBuffer, "%02d/%02d/%04d", now.day(), now.month(), now.year());
  TFTscreen.text(dateBuffer, 5, 30);  // Posicionado en la parte media-superior

  // *** Mostrar la palabra TIME ***
  TFTscreen.setTextSize(1);  // Tamaño de texto más pequeño
  TFTscreen.stroke(255, 0, 255);  // Color rosado para el texto "TIME"
  TFTscreen.text("TIME", 50, 60);  // Centrado

  // *** Mostrar la hora en formato HH:MM:SS ***
  TFTscreen.setTextSize(2);  // Tamaño del texto para la hora
  TFTscreen.stroke(0, 255, 0);  // Color verde para la hora
  
  char timeBuffer[9];  // Buffer para la hora
  sprintf(timeBuffer, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
  TFTscreen.text(timeBuffer, 20, 80);  // Mostrar la hora

  // *** Mostrar la palabra TEMPERATURE ***
  TFTscreen.setTextSize(1);  // Tamaño de texto más pequeño
  TFTscreen.stroke(255, 0, 0);  // Color rojo para el texto "TEMPERATURE"
  TFTscreen.text("TEMPERATURE", 20, 110);  // Posicionado bajo la hora

  // *** Mostrar la temperatura (simulada por ahora) ***
  TFTscreen.setTextSize(2);  // Tamaño de texto para la temperatura
  TFTscreen.stroke(255, 255, 255);  // Color blanco para la temperatura
  
  float temperature = 24.50;  // Simulando una temperatura de 24.50°C
  char tempBuffer[10];  // Buffer para la temperatura
  sprintf(tempBuffer, "%.2f C", temperature);
  TFTscreen.text(tempBuffer, 20, 130);  // Mostrar la temperatura

  // Pausa de un segundo para actualizar
  delay(1000);
}
