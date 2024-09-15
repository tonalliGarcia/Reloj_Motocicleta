#include <TFT.h>    // Incluye la biblioteca para manejar la pantalla TFT
#include <SPI.h>    // Incluye la biblioteca para la comunicación SPI

// Definición de los pines utilizados para la pantalla TFT
#define cs 10   // Pin de selección de chip (CS)
#define dc 9    // Pin de control de datos (DC)
#define rst 8   // Pin de reinicio (RST)

// Crea una instancia del objeto TFT con los pines definidos
TFT TFTscreen = TFT(cs, dc, rst);

void setup() {
  // Inicializa la pantalla TFT
  TFTscreen.begin();

  // Configura la orientación de la pantalla en 270 grados
  TFTscreen.setRotation(270);

  // Establece el color de fondo de la pantalla a negro
  TFTscreen.background(0,0,0);

  // Configura el color del trazo a blanco y dibuja texto en la pantalla
  TFTscreen.stroke(255,255,255);
  TFTscreen.text("Hello", 20, 20); // Dibuja "Hello" en la posición (20,20)

  // Cambia el tamaño del texto y dibuja el texto centrado en la pantalla
  TFTscreen.textSize(2);
  TFTscreen.text("Hello", TFTscreen.width()/2, 20); // Dibuja "Hello" centrado en la parte superior

  // Configura el color del trazo a rojo y dibuja un círculo en la pantalla
  TFTscreen.stroke(255,0,0);
  TFTscreen.circle(TFTscreen.width()/2, 64, 22); // Dibuja un círculo rojo en la posición (ancho/2, 64) con radio 22

  // Configura el color de relleno a azul y dibuja un rectángulo en la pantalla
  TFTscreen.fill(0,0,255);
  TFTscreen.noStroke(); // Desactiva el trazo de contorno
  TFTscreen.rect(50, 50, 30, 30); // Dibuja un rectángulo azul en la posición (50,50) con tamaño 30x30

  // Pausa el programa durante 1000 milisegundos (1 segundo)
  delay(1000);
}

void loop() {
  // Primer bucle: Dibuja líneas horizontales y texto en movimiento hacia arriba
  for(int i = 90; i > -135; i += 5) {
    TFTscreen.stroke(0,0,255); // Configura el color del trazo a azul
    TFTscreen.line(0, i, TFTscreen.width()/4, i); // Dibuja una línea horizontal azul
    TFTscreen.text("Hello", TFTscreen.width()/4, i); // Dibuja el texto "Hello" en la misma posición que la línea
    delay(100); // Pausa durante 100 milisegundos

    // Limpia la pantalla en la posición de la línea
    TFTscreen.stroke(0,0,0); // Configura el color del trazo a negro
    TFTscreen.line(0, i, TFTscreen.width(), i); // Dibuja una línea horizontal negra
    TFTscreen.text("Hello", TFTscreen.width()/4, i); // Dibuja el texto "Hello" en la misma posición que la línea
  }

  // Segundo bucle: Dibuja líneas horizontales y texto en movimiento hacia abajo
  for(int i = 135; i >= 90; i -= 5) {
    TFTscreen.stroke(255,0,0); // Configura el color del trazo a rojo
    TFTscreen.line(0, i, TFTscreen.width(), i); // Dibuja una línea horizontal roja
    TFTscreen.text("Hello", TFTscreen.width()/4, i); // Dibuja el texto "Hello" en la misma posición que la línea
    delay(100); // Pausa durante 100 milisegundos

    // Limpia la pantalla en la posición de la línea
    TFTscreen.stroke(0,0,0); // Configura el color del trazo a negro
    TFTscreen.line(0, i, TFTscreen.width(), i); // Dibuja una línea horizontal negra
    TFTscreen.text("Hello", TFTscreen.width()/4, i); // Dibuja el texto "Hello" en la misma posición que la línea
  }
}
