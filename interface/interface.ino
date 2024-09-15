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
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Variables para guardar valores anteriores
int lastSecond = -1;
int lastMinute = -1;
int lastHour = -1;
int lastDayOfWeek = -1;
int lastDay = -1;
int lastMonth = -1;
int lastYear = -1;

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

  // Dibujar la estructura estática de la pantalla (Día, Fecha, "TIME", "TEMPERATURE")
  drawStaticElements();
}

void loop() {
  // Obtiene la hora actual del RTC
  DateTime now = rtc.now();

  // Actualiza la fecha si ha cambiado el día
  if (now.dayOfTheWeek() != lastDayOfWeek || now.day() != lastDay || now.month() != lastMonth || now.year() != lastYear) {
    updateDate(now);
    lastDayOfWeek = now.dayOfTheWeek();
    lastDay = now.day();
    lastMonth = now.month();
    lastYear = now.year();
  }

  // Actualiza la hora solo si el segundo ha cambiado
  if (now.second() != lastSecond) {
    updateTime(now);
    lastSecond = now.second();
  }

  // Actualiza la temperatura si es necesario (puedes agregar sensor real aquí)
  updateTemperature();
  
  delay(100);  // Pequeño retardo para evitar sobrecarga de dibujo
}

// Función para dibujar los elementos que no cambian
void drawStaticElements() {
  // *** Mostrar la palabra TIME ***
  TFTscreen.setTextSize(1);  // Tamaño de texto más pequeño
  TFTscreen.stroke(255, 0, 255);  // Color rosado para el texto "TIME"
  TFTscreen.text("TIME", 50, 60);  // Centrado

  // *** Mostrar la palabra TEMPERATURE ***
  TFTscreen.setTextSize(1);  // Tamaño de texto más pequeño
  TFTscreen.stroke(255, 0, 0);  // Color rojo para el texto "TEMPERATURE"
  TFTscreen.text("TEMPERATURE", 20, 110);  // Posicionado bajo la hora
}

// Función para actualizar la fecha sin redibujar todo
void updateDate(DateTime now) {
  // *** Mostrar el día de la semana ***
  TFTscreen.setTextSize(2);
  TFTscreen.stroke(0, 255, 255);  // Color cian para el día de la semana
  TFTscreen.fill(0, 0, 0);  // Fondo negro para borrar el texto anterior
  TFTscreen.text(daysOfTheWeek[now.dayOfTheWeek()], 30, 10);  // Centrado en la parte superior

  // *** Actualizar la fecha en formato DD/MM/YYYY ***
  TFTscreen.setTextSize(2);  // Tamaño del texto para la fecha
  TFTscreen.stroke(255, 255, 0);  // Color amarillo para la fecha
  char dateBuffer[11];  // Buffer para la fecha
  sprintf(dateBuffer, "%02d/%02d/%04d", now.day(), now.month(), now.year());
  TFTscreen.text(dateBuffer, 20, 40);  // Mostrar la fecha
}

// Función para actualizar la hora sin redibujar todo
void updateTime(DateTime now) {
  char timeBuffer[9];  // Buffer para la hora

  // Solo actualiza los minutos y la hora si han cambiado
  if (now.minute() != lastMinute || now.hour() != lastHour) {
    // *** Actualizar la hora en formato HH:MM ***
    TFTscreen.setTextSize(2);  // Tamaño del texto para la hora
    TFTscreen.stroke(0, 255, 0);  // Color verde para la hora 0,255,0
    TFTscreen.fill(0, 0, 0);  // Borrar toda la región de la hora
    TFTscreen.rect(20, 80, 110, 30, 0);  // Borrar el área de hora y segundos antes de dibujar
    sprintf(timeBuffer, "%02d:%02d:", now.hour(), now.minute());
    TFTscreen.text(timeBuffer, 20, 80);  // Mostrar la hora

    lastMinute = now.minute();
    lastHour = now.hour();
  }

  // Borra los segundos antes de dibujar los nuevos
  TFTscreen.fill(0, 0, 0);  // Fondo negro para borrar
  TFTscreen.rect(100, 80, 30, 20, 0);  // Borra la región de los segundos antes de actualizar

  // *** Actualizar los segundos ***
  TFTscreen.setTextSize(2);
  TFTscreen.stroke(0, 255, 0);  // Color verde para los segundos 0,255,0
  sprintf(timeBuffer, "%02d", now.second());
  TFTscreen.text(timeBuffer, 100, 80);  // Actualiza solo los segundos
}

// Función para actualizar la temperatura (simulada)
void updateTemperature() {
  TFTscreen.setTextSize(2);  // Tamaño de texto para la temperatura
  TFTscreen.stroke(255, 255, 255);  // Color blanco para la temperatura
  TFTscreen.fill(0, 0, 0);  // Borrar solo la parte de la temperatura
  float temperature = 24.50;  // Simulando una temperatura de 24.50°C
  char tempBuffer[10];  // Buffer para la temperatura
  sprintf(tempBuffer, "%.2f C", temperature);
  TFTscreen.text(tempBuffer, 20, 130);  // Mostrar la temperatura
}
