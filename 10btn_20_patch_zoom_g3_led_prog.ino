/*
 * Código criado para ZOOM G3/G3x provavelmente funcional na linha G1on e MS.
 * 10 pedais, pisando uma vez vem um patch, pisando novamente no mesmo pedal vem outro, totalizando 20.
 * Criado por Alcimar Ramos
 * https://youtube.com/c/alcimarramos
 * https://www.instagram.com/alcimar_ramos
 */

/* Bibliotecas utilizadas */
#include <MIDI.h>
#include <Usb.h>
#include <usbhub.h>
#include <usbh_midi.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

/* Definindo nome para os pinos de entrada, onde ficam os botões */ 
#define pino2 2   /*  pedal patch1 */
#define pino3 3   /*  pedal patch2 */
#define pino4 4   /*  pedal patch3 */
#define pino5 5   /*  pedal patch4 */
#define pino6 6   /*  pedal patch5 */
#define pino7 A0  /*  pedal patch6 */
#define pino8 A1  /*  pedal patch7 */
#define pino9 A2  /*  pedal patch8 */
#define pino10 A3 /*  pedal patch9 */
#define pino11 A4 /*  pedal patch10*/

/* Pino onde liga o DIN dos LEDs */
#define PIN 7

/* Numero de leds */
#define NUMPIXELS 10

Adafruit_NeoPixel pixels=Adafruit_NeoPixel(NUMPIXELS,PIN,NEO_GRB+NEO_KHZ800);

//Definindo comunicação Midi USB
USB Usb; 
USBH_MIDI Midi(&Usb);

/* Variáveis recebendo patches do Banco A */
byte patchA0 = 0x00;
byte patchA1 = 0x01;
byte patchA2 = 0x02;
byte patchA3 = 0x03;
byte patchA4 = 0x04;
byte patchA5 = 0x05;
byte patchA6 = 0x06;
byte patchA7 = 0x07;
byte patchA8 = 0x08;
byte patchA9 = 0x09;

/* Variáveis recebendo patches do Banco B */
byte patchB0 = 0x0A;
byte patchB1 = 0x0B;
byte patchB2 = 0x0C;
byte patchB3 = 0x0D;
byte patchB4 = 0x0E;
byte patchB5 = 0x0F;
byte patchB6 = 0x10;
byte patchB7 = 0x11;
byte patchB8 = 0x12;
byte patchB9 = 0x13;

/* Variáveis recebendo patches do Banco C */
byte patchC0 = 0x14;
byte patchC1 = 0x15;
byte patchC2 = 0x16;
byte patchC3 = 0x17;
byte patchC4 = 0x18;
byte patchC5 = 0x19;
byte patchC6 = 0x1A;
byte patchC7 = 0x1B;
byte patchC8 = 0x1C;
byte patchC9 = 0x1D;

/* Variáveis recebendo patches do Banco D */
byte patchD0 = 0x1E;
byte patchD1 = 0x1F;
byte patchD2 = 0x20;
byte patchD3 = 0x21;
byte patchD4 = 0x22;
byte patchD5 = 0x23;
byte patchD6 = 0x24;
byte patchD7 = 0x25;
byte patchD8 = 0x26;
byte patchD9 = 0x27;

//Variáveis que receberão valores 0 ou 1 para  o mudança dos 2 patches em único pedal
int valorPedal1;
int valorPedal2;
int valorPedal3;
int valorPedal4;
int valorPedal5;
int valorPedal6;
int valorPedal7;
int valorPedal8;
int valorPedal9;
int valorPedal10;

/* Variáveis que receberão  o acionamento dos botões nos pinos de entrada */
int pedal1;
int pedal2;
int pedal3;
int pedal4;
int pedal5;
int pedal6;
int pedal7;
int pedal8;
int pedal9;
int pedal10;
int i = 0;
int bank = 0;
int espera = 333; /* Tempo em ms até poder enviar o comando novamente */

void setup() {

/* Definindo pinos de entrada */
  pinMode(pino2, INPUT_PULLUP);
  pinMode(pino3, INPUT_PULLUP);
  pinMode(pino4, INPUT_PULLUP);
  pinMode(pino5, INPUT_PULLUP);
  pinMode(pino6, INPUT_PULLUP);
  pinMode(pino7, INPUT_PULLUP);
  pinMode(pino8, INPUT_PULLUP);
  pinMode(pino9, INPUT_PULLUP);
  pinMode(pino10, INPUT_PULLUP);
  pinMode(pino11, INPUT_PULLUP);

  pixels.begin();
  pixels.setBrightness(50);
  apagaLed();

  Serial.begin(115200); /* inicia comunicação serial e define a velocidade */
  iniciar();
}


void loop() {
/*
Aqui a brincadeira começa rsrsrs
Algumas funções foram definidas em um arquivo separado gerando uma guia chamada "func" , visando a organização do código.
*/

//Variáveis que recebem  o acionamento dos botões nos pinos de entrada

   pedal1 = digitalRead(pino2);
   pedal2 = digitalRead(pino3);
   pedal3 = digitalRead(pino4);
   pedal4 = digitalRead(pino5);
   pedal5 = digitalRead(pino6);
   pedal6 = digitalRead(pino7);
   pedal7 = digitalRead(pino8);
   pedal8 = digitalRead(pino9);
   pedal9 = digitalRead(pino10);
   pedal10 = digitalRead(pino11);


  //////////////////// PEDAL 1 ////////////////////
  if ( pedal1 == LOW ) { /*----------------------- Se o pedal 1 for pressionado */
      valorPedal1 = !valorPedal1; /*-------------- Valor do pedal inverte sempre que é acionado entre 0 e 1 */
      
      if ( pedal1 == LOW && valorPedal1 == 1 ){
      SendMIDI(patchA1); /*----------------------- Envia o patch A1 */
      led1on(); /*-------------------------------- Liga o Led do pedal */
      delay(espera); /*--------------------------- Tempo até poder enciar o comando novamente */ 
      }
      
      else if ( pedal1 == LOW && valorPedal1 == 0 ){
      SendMIDI(patchB1); /*----------------------- Envia o patch B1 */
      led1on_(); /*------------------------------- Liga o Led do pedal */
      delay(espera); /*--------------------------- Tempo até poder enciar o comando novamente */ 
      }
    valorPedaloff1(); /*-------------------------- Zera o valor dos outros pedais */
  }

  //////////////////// PEDAL 2 ////////////////////
  if ( pedal2 == LOW ) { /*----------------------- Se o pedal 1 for pressionado */
      valorPedal2 = !valorPedal2; /*-------------- Valor do pedal inverte sempre que é acionado entre 0 e 1 */
      
      if ( pedal2 == LOW && valorPedal2 == 1 ){
      SendMIDI(patchA2); /*----------------------- Envia o patch A2 */
      led2on(); /*-------------------------------- Liga o Led do pedal */
      delay(espera); /*--------------------------- Tempo até poder enciar o comando novamente */ 
      }
      
      else if ( pedal2 == LOW && valorPedal1 == 0 ){
      SendMIDI(patchB2); /*----------------------- Envia o patch B2 */
      led2on_(); /*------------------------------- Liga o Led do pedal */
      delay(espera); /*--------------------------- Tempo até poder enciar o comando novamente */ 
      }
    valorPedaloff2(); /*-------------------------- Zera o valor dos outros pedais */
  }

  //////////////////// PEDAL 3 ////////////////////
  if ( pedal3 == LOW ) { /*----------------------- Se o pedal 1 for pressionado */
      valorPedal3 = !valorPedal3; /*-------------- Valor do pedal inverte sempre que é acionado entre 0 e 1 */
      
      if ( pedal3 == LOW && valorPedal3 == 1 ){
      SendMIDI(patchA3); /*----------------------- Envia o patch A3 */
      led3on(); /*-------------------------------- Liga o Led do pedal */
      delay(espera); /*--------------------------- Tempo até poder enciar o comando novamente */ 
      }
      
      else if ( pedal3 == LOW && valorPedal3 == 0 ){
      SendMIDI(patchB3); /*----------------------- Envia o patch B3 */
      led3on_(); /*------------------------------- Liga o Led do pedal */
      delay(espera); /*--------------------------- Tempo até poder enciar o comando novamente */ 
      }
    valorPedaloff3(); /*-------------------------- Zera o valor dos outros pedais */
  }

  //////////////////// PEDAL 4 ////////////////////
  if ( pedal4 == LOW ) { /*----------------------- Se o pedal 1 for pressionado */
      valorPedal4 = !valorPedal4; /*-------------- Valor do pedal inverte sempre que é acionado entre 0 e 1 */
      
      if ( pedal4 == LOW && valorPedal4 == 1 ){
      SendMIDI(patchA4); /*----------------------- Envia o patch A4 */
      led4on(); /*-------------------------------- Liga o Led do pedal */
      delay(espera); /*--------------------------- Tempo até poder enciar o comando novamente */ 
      }
      
      else if ( pedal4 == LOW && valorPedal4 == 0 ){
      SendMIDI(patchB4); /*----------------------- Envia o patch B4 */
      led4on_(); /*------------------------------- Liga o Led do pedal */
      delay(espera); /*--------------------------- Tempo até poder enciar o comando novamente */ 
      }
    valorPedaloff4(); /*-------------------------- Zera o valor dos outros pedais */
  }

  //////////////////// PEDAL 5 ////////////////////
  if ( pedal5 == LOW ) { /*----------------------- Se o pedal 1 for pressionado */
      valorPedal5 = !valorPedal5; /*-------------- Valor do pedal inverte sempre que é acionado entre 0 e 1 */
      
      if ( pedal5 == LOW && valorPedal5 == 1 ){
      SendMIDI(patchA5); /*----------------------- Envia o patch A5 */
      led5on(); /*-------------------------------- Liga o Led do pedal */
      delay(espera); /*--------------------------- Tempo até poder enciar o comando novamente */ 
      }
      
      else if ( pedal5 == LOW && valorPedal5 == 0 ){
      SendMIDI(patchB5); /*----------------------- Envia o patch B5 */
      led5on_(); /*------------------------------- Liga o Led do pedal */
      delay(espera); /*--------------------------- Tempo até poder enciar o comando novamente */ 
      }
    valorPedaloff5(); /*-------------------------- Zera o valor dos outros pedais */
  }

  //////////////////// PEDAL 6 ////////////////////
  if ( pedal6 == LOW ) { /*----------------------- Se o pedal 1 for pressionado */
      valorPedal6 = !valorPedal6; /*-------------- Valor do pedal inverte sempre que é acionado entre 0 e 1 */
      
      if ( pedal6 == LOW && valorPedal6 == 1 ){
      SendMIDI(patchA6); /*------------------------ Envia o patch A6 */
      led10on(); /*-------------------------------- Liga o Led do pedal */
      delay(espera); /*---------------------------- Tempo até poder enciar o comando novamente */ 
      }
      
      else if ( pedal6 == LOW && valorPedal6 == 0 ){
      SendMIDI(patchB6); /*------------------------ Envia o patch B6 */
      led10on_(); /*------------------------------- Liga o Led do pedal */
      delay(espera); /*---------------------------- Tempo até poder enciar o comando novamente */ 
      }
    valorPedaloff6(); /*-------------------------- Zera o valor dos outros pedais */
  }

  //////////////////// PEDAL 7 ////////////////////
  if ( pedal7 == LOW ) { /*----------------------- Se o pedal 1 for pressionado */
      valorPedal7 = !valorPedal7; /*-------------- Valor do pedal inverte sempre que é acionado entre 0 e 1 */
      
      if ( pedal7 == LOW && valorPedal7 == 1 ){
      SendMIDI(patchA7); /*----------------------- Envia o patch A7 */
      led9on(); /*-------------------------------- Liga o Led do pedal */
      delay(espera); /*--------------------------- Tempo até poder enciar o comando novamente */ 
      }
      
      else if ( pedal7 == LOW && valorPedal7 == 0 ){
      SendMIDI(patchB7); /*----------------------- Envia o patch B7 */
      led9on_(); /*------------------------------- Liga o Led do pedal */
      delay(espera); /*--------------------------- Tempo até poder enciar o comando novamente */ 
      }
    valorPedaloff7(); /*-------------------------- Zera o valor dos outros pedais */
  }

  //////////////////// PEDAL 8 ////////////////////
  if ( pedal8 == LOW ) { /*----------------------- Se o pedal 1 for pressionado */
      valorPedal8 = !valorPedal8; /*-------------- Valor do pedal inverte sempre que é acionado entre 0 e 1 */
      
      if ( pedal8 == LOW && valorPedal8 == 1 ){
      SendMIDI(patchA8); /*----------------------- Envia o patch A8 */
      led8on(); /*-------------------------------- Liga o Led do pedal */
      delay(espera); /*--------------------------- Tempo até poder enciar o comando novamente */ 
      }
      
      else if ( pedal8 == LOW && valorPedal8 == 0 ){
      SendMIDI(patchB8); /*----------------------- Envia o patch B8 */
      led8on_(); /*------------------------------- Liga o Led do pedal */
      delay(espera); /*--------------------------- Tempo até poder enciar o comando novamente */ 
      }
    valorPedaloff8(); /*-------------------------- Zera o valor dos outros pedais */
  }

  //////////////////// PEDAL 9 ////////////////////
  if ( pedal9 == LOW ) { /*----------------------- Se o pedal 1 for pressionado */
      valorPedal9 = !valorPedal9; /*-------------- Valor do pedal inverte sempre que é acionado entre 0 e 1 */
      
      if ( pedal9 == LOW && valorPedal9 == 1 ){
      SendMIDI(patchA9); /*----------------------- Envia o patch A9 */
      led7on(); /*-------------------------------- Liga o Led do pedal */
      delay(espera); /*--------------------------- Tempo até poder enciar o comando novamente */ 
      }
      
      else if ( pedal9 == LOW && valorPedal9 == 0 ){
      SendMIDI(patchB9); /*----------------------- Envia o patch B9 */
      led7on_(); /*------------------------------- Liga o Led do pedal */
      delay(espera); /*--------------------------- Tempo até poder enciar o comando novamente */ 
      }
    valorPedaloff9(); /*-------------------------- Zera o valor dos outros pedais */
  }

  //////////////////// PEDAL 10 ////////////////////
  if ( pedal10 == LOW ) { /*---------------------- Se o pedal 1 for pressionado */
      valorPedal10 = !valorPedal10; /*------------ Valor do pedal inverte sempre que é acionado entre 0 e 1 */
      
      if ( pedal10 == LOW && valorPedal10 == 1 ){
      SendMIDI(patchA0); /*----------------------- Envia o patch A0 */
      led6on(); /*-------------------------------- Liga o Led do pedal */
      delay(espera); /*--------------------------- Tempo até poder enciar o comando novamente */ 
      }
      
      else if ( pedal10 == LOW && valorPedal10 == 0 ){
      SendMIDI(patchB0); /*----------------------- Envia o patch B0 */
      led6on_(); /*------------------------------- Liga o Led do pedal */
      delay(espera); /*--------------------------- Tempo até poder enciar o comando novamente */ 
      }
    valorPedaloff10(); /*------------------------- Zera o valor dos outros pedais */
  }

}


/* --------------------------------------------------------------------- */
/* ****************************** FUNÇÔES ****************************** */
/* --------------------------------------------------------------------- */


void SendMIDI(byte number) { /* Função para enviar os comandos Midi */
  Usb.Task();                /* Iniciando tarefa Midi */
  byte Message[2];           /* Construindo mensagem midi (2 bytes) */
  Message[0] = 0xC0;         /* 0xC0 para Program Change */
  Message[1] = number;       /* Number é o program/patch */
  Midi.SendData(Message);    /* Envia a mensagem */
  delay(10);
}

void iniciar(){
  if (Usb.Init() == -1) { /* Testa se o USB foi conectado e aguarda conectar */
    while (1);
  }
  while (Usb.getUsbTaskState() != USB_STATE_RUNNING) {
    Usb.Task(); /* se USB iniciou, continue */
  }
  for (int i = 0; i < 4; i++) { /* forçando os 4 primeiros comandos enviados pra pedaleira que são ignorados */
    SendMIDI(patchA1);
    delay(200);
  }
  led1on(); //Acende o Led 1
}

/* Acende o Led 1 e apaga os demais */
void led1on() {
  pixels.setPixelColor(9, pixels.Color(255,0,0));
  pixels.setPixelColor(8, pixels.Color(0, 0, 0));
  pixels.setPixelColor(7, pixels.Color(0, 0, 0));
  pixels.setPixelColor(6, pixels.Color(0, 0, 0));
  pixels.setPixelColor(5, pixels.Color(0, 0, 0));
  pixels.setPixelColor(4, pixels.Color(0, 0, 0));
  pixels.setPixelColor(3, pixels.Color(0, 0, 0));
  pixels.setPixelColor(2, pixels.Color(0, 0, 0));
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
}
  
void led1on_() {
  pixels.setPixelColor(9, pixels.Color(0, 255,0));
  pixels.setPixelColor(8, pixels.Color(0, 0, 0));
  pixels.setPixelColor(7, pixels.Color(0, 0, 0));
  pixels.setPixelColor(6, pixels.Color(0, 0, 0));
  pixels.setPixelColor(5, pixels.Color(0, 0, 0));
  pixels.setPixelColor(4, pixels.Color(0, 0, 0));
  pixels.setPixelColor(3, pixels.Color(0, 0, 0));
  pixels.setPixelColor(2, pixels.Color(0, 0, 0));
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
}

/* Acende o Led 2 e apaga os demais */
void led2on() {
  pixels.setPixelColor(9, pixels.Color(0, 0,0));
  pixels.setPixelColor(8, pixels.Color(255, 0, 0));
  pixels.setPixelColor(7, pixels.Color(0, 0, 0));
  pixels.setPixelColor(6, pixels.Color(0, 0, 0));
  pixels.setPixelColor(5, pixels.Color(0, 0, 0));
  pixels.setPixelColor(4, pixels.Color(0, 0, 0));
  pixels.setPixelColor(3, pixels.Color(0, 0, 0));
  pixels.setPixelColor(2, pixels.Color(0, 0, 0));
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
}

void led2on_() {
  pixels.setPixelColor(9, pixels.Color(0, 0,0));
  pixels.setPixelColor(8, pixels.Color(0, 255, 0));
  pixels.setPixelColor(7, pixels.Color(0, 0, 0));
  pixels.setPixelColor(6, pixels.Color(0, 0, 0));
  pixels.setPixelColor(5, pixels.Color(0, 0, 0));
  pixels.setPixelColor(4, pixels.Color(0, 0, 0));
  pixels.setPixelColor(3, pixels.Color(0, 0, 0));
  pixels.setPixelColor(2, pixels.Color(0, 0, 0));
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
}

/* Acende o Led 3 e apaga os demais */
void led3on() {
  pixels.setPixelColor(9, pixels.Color(0, 0,0));
  pixels.setPixelColor(8, pixels.Color(0, 0, 0));
  pixels.setPixelColor(7, pixels.Color(255, 0, 0));
  pixels.setPixelColor(6, pixels.Color(0, 0, 0));
  pixels.setPixelColor(5, pixels.Color(0, 0, 0));
  pixels.setPixelColor(4, pixels.Color(0, 0, 0));
  pixels.setPixelColor(3, pixels.Color(0, 0, 0));
  pixels.setPixelColor(2, pixels.Color(0, 0, 0));
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
  }
  
void led3on_() {
  pixels.setPixelColor(9, pixels.Color(0, 0,0));
  pixels.setPixelColor(8, pixels.Color(0, 0, 0));
  pixels.setPixelColor(7, pixels.Color(0, 255, 0));
  pixels.setPixelColor(6, pixels.Color(0, 0, 0));
  pixels.setPixelColor(5, pixels.Color(0, 0, 0));
  pixels.setPixelColor(4, pixels.Color(0, 0, 0));
  pixels.setPixelColor(3, pixels.Color(0, 0, 0));
  pixels.setPixelColor(2, pixels.Color(0, 0, 0));
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
}

/* Acende o Led 4 e apaga os demais */
void led4on() {
  pixels.setPixelColor(9, pixels.Color(0, 0,0));
  pixels.setPixelColor(8, pixels.Color(0, 0, 0));
  pixels.setPixelColor(7, pixels.Color(0, 0, 0));
  pixels.setPixelColor(6, pixels.Color(255, 0, 0));
  pixels.setPixelColor(5, pixels.Color(0, 0, 0));
  pixels.setPixelColor(4, pixels.Color(0, 0, 0));
  pixels.setPixelColor(3, pixels.Color(0, 0, 0));
  pixels.setPixelColor(2, pixels.Color(0, 0, 0));
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
}
  
void led4on_() {
  pixels.setPixelColor(9, pixels.Color(0, 0,0));
  pixels.setPixelColor(8, pixels.Color(0, 0, 0));
  pixels.setPixelColor(7, pixels.Color(0, 0, 0));
  pixels.setPixelColor(6, pixels.Color(0, 255, 0));
  pixels.setPixelColor(5, pixels.Color(0, 0, 0));
  pixels.setPixelColor(4, pixels.Color(0, 0, 0));
  pixels.setPixelColor(3, pixels.Color(0, 0, 0));
  pixels.setPixelColor(2, pixels.Color(0, 0, 0));
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
}

/* Acende o Led 5 e apaga os demais */
void led5on() {
  pixels.setPixelColor(9, pixels.Color(0, 0,0));
  pixels.setPixelColor(8, pixels.Color(0, 0, 0));
  pixels.setPixelColor(7, pixels.Color(0, 0, 0));
  pixels.setPixelColor(6, pixels.Color(0, 0, 0));
  pixels.setPixelColor(5, pixels.Color(255, 0, 0));
  pixels.setPixelColor(4, pixels.Color(0, 0, 0));
  pixels.setPixelColor(3, pixels.Color(0, 0, 0));
  pixels.setPixelColor(2, pixels.Color(0, 0, 0));
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
}

void led5on_() {
  pixels.setPixelColor(9, pixels.Color(0, 0,0));
  pixels.setPixelColor(8, pixels.Color(0, 0, 0));
  pixels.setPixelColor(7, pixels.Color(0, 0, 0));
  pixels.setPixelColor(6, pixels.Color(0, 0, 0));
  pixels.setPixelColor(5, pixels.Color(0, 255, 0));
  pixels.setPixelColor(4, pixels.Color(0, 0, 0));
  pixels.setPixelColor(3, pixels.Color(0, 0, 0));
  pixels.setPixelColor(2, pixels.Color(0, 0, 0));
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
  delay (70);
}

/* Acende o Led 6 e apaga os demais */
void led6on() {
  pixels.setPixelColor(9, pixels.Color(0, 0,0));
  pixels.setPixelColor(8, pixels.Color(0, 0, 0));
  pixels.setPixelColor(7, pixels.Color(0, 0, 0));
  pixels.setPixelColor(6, pixels.Color(0, 0, 0));
  pixels.setPixelColor(5, pixels.Color(0, 0, 0));
  pixels.setPixelColor(4, pixels.Color(255, 0, 0));
  pixels.setPixelColor(3, pixels.Color(0, 0, 0));
  pixels.setPixelColor(2, pixels.Color(0, 0, 0));
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
  }
  
  void led6on_() {
  pixels.setPixelColor(9, pixels.Color(0, 0,0));
  pixels.setPixelColor(8, pixels.Color(0, 0, 0));
  pixels.setPixelColor(7, pixels.Color(0, 0, 0));
  pixels.setPixelColor(6, pixels.Color(0, 0, 0));
  pixels.setPixelColor(5, pixels.Color(0, 0, 0));
  pixels.setPixelColor(4, pixels.Color(0, 255, 0));
  pixels.setPixelColor(3, pixels.Color(0, 0, 0));
  pixels.setPixelColor(2, pixels.Color(0, 0, 0));
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
  delay (70);
}

/* Acende o Led 7 e apaga os demais */
  void led7on() {
  pixels.setPixelColor(9, pixels.Color(0, 0,0));
  pixels.setPixelColor(8, pixels.Color(0, 0, 0));
  pixels.setPixelColor(7, pixels.Color(0, 0, 0));
  pixels.setPixelColor(6, pixels.Color(0, 0, 0));
  pixels.setPixelColor(5, pixels.Color(0, 0, 0));
  pixels.setPixelColor(4, pixels.Color(0, 0, 0));
  pixels.setPixelColor(3, pixels.Color(255, 0, 0));
  pixels.setPixelColor(2, pixels.Color(0, 0, 0));
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
}

  void led7on_() {
  pixels.setPixelColor(9, pixels.Color(0, 0,0));
  pixels.setPixelColor(8, pixels.Color(0, 0, 0));
  pixels.setPixelColor(7, pixels.Color(0, 0, 0));
  pixels.setPixelColor(6, pixels.Color(0, 0, 0));
  pixels.setPixelColor(5, pixels.Color(0, 0, 0));
  pixels.setPixelColor(4, pixels.Color(0, 0, 0));
  pixels.setPixelColor(3, pixels.Color(0, 255, 0));
  pixels.setPixelColor(2, pixels.Color(0, 0, 0));
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
}

/* Acende o Led 8 e apaga os demais */
  void led8on() {
  pixels.setPixelColor(9, pixels.Color(0, 0,0));
  pixels.setPixelColor(8, pixels.Color(0, 0, 0));
  pixels.setPixelColor(7, pixels.Color(0, 0, 0));
  pixels.setPixelColor(6, pixels.Color(0, 0, 0));
  pixels.setPixelColor(5, pixels.Color(0, 0, 0));
  pixels.setPixelColor(4, pixels.Color(0, 0, 0));
  pixels.setPixelColor(3, pixels.Color(0, 0, 0));
  pixels.setPixelColor(2, pixels.Color(255, 0, 0));
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
}

  void led8on_() {
  pixels.setPixelColor(9, pixels.Color(0, 0,0));
  pixels.setPixelColor(8, pixels.Color(0, 0, 0));
  pixels.setPixelColor(7, pixels.Color(0, 0, 0));
  pixels.setPixelColor(6, pixels.Color(0, 0, 0));
  pixels.setPixelColor(5, pixels.Color(0, 0, 0));
  pixels.setPixelColor(4, pixels.Color(0, 0, 0));
  pixels.setPixelColor(3, pixels.Color(0, 0, 0));
  pixels.setPixelColor(2, pixels.Color(0, 255, 0));
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
}

/* Acende o Led 9 e apaga os demais */
  void led9on() {
  pixels.setPixelColor(9, pixels.Color(0, 0,0));
  pixels.setPixelColor(8, pixels.Color(0, 0, 0));
  pixels.setPixelColor(7, pixels.Color(0, 0, 0));
  pixels.setPixelColor(6, pixels.Color(0, 0, 0));
  pixels.setPixelColor(5, pixels.Color(0, 0, 0));
  pixels.setPixelColor(4, pixels.Color(0, 0, 0));
  pixels.setPixelColor(3, pixels.Color(0, 0, 0));
  pixels.setPixelColor(2, pixels.Color(0, 0, 0));
  pixels.setPixelColor(1, pixels.Color(255, 0, 0));
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
}

  void led9on_() {
  pixels.setPixelColor(9, pixels.Color(0, 0,0));
  pixels.setPixelColor(8, pixels.Color(0, 0, 0));
  pixels.setPixelColor(7, pixels.Color(0, 0, 0));
  pixels.setPixelColor(6, pixels.Color(0, 0, 0));
  pixels.setPixelColor(5, pixels.Color(0, 0, 0));
  pixels.setPixelColor(4, pixels.Color(0, 0, 0));
  pixels.setPixelColor(3, pixels.Color(0, 0, 0));
  pixels.setPixelColor(2, pixels.Color(0, 0, 0));
  pixels.setPixelColor(1, pixels.Color(0, 255, 0));
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
}

/* Acende o Led 10 e apaga os demais */
  void led10on() {
  pixels.setPixelColor(9, pixels.Color(0, 0,0));
  pixels.setPixelColor(8, pixels.Color(0, 0, 0));
  pixels.setPixelColor(7, pixels.Color(0, 0, 0));
  pixels.setPixelColor(6, pixels.Color(0, 0, 0));
  pixels.setPixelColor(5, pixels.Color(0, 0, 0));
  pixels.setPixelColor(4, pixels.Color(0, 0, 0));
  pixels.setPixelColor(3, pixels.Color(0, 0, 0));
  pixels.setPixelColor(2, pixels.Color(0, 0, 0));
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(0, pixels.Color(255, 0, 0));
  pixels.show();
}

  void led10on_() {
  pixels.setPixelColor(9, pixels.Color(0, 0,0));
  pixels.setPixelColor(8, pixels.Color(0, 0, 0));
  pixels.setPixelColor(7, pixels.Color(0, 0, 0));
  pixels.setPixelColor(6, pixels.Color(0, 0, 0));
  pixels.setPixelColor(5, pixels.Color(0, 0, 0));
  pixels.setPixelColor(4, pixels.Color(0, 0, 0));
  pixels.setPixelColor(3, pixels.Color(0, 0, 0));
  pixels.setPixelColor(2, pixels.Color(0, 0, 0));
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(0, pixels.Color(0, 255, 0));
  pixels.show();
}

  void ledsoff() {
  pixels.setPixelColor(9, pixels.Color(0, 0,0));
  pixels.setPixelColor(8, pixels.Color(0, 0, 0));
  pixels.setPixelColor(7, pixels.Color(0, 0, 0));
  pixels.setPixelColor(6, pixels.Color(0, 0, 0));
  pixels.setPixelColor(5, pixels.Color(0, 0, 0));
  pixels.setPixelColor(4, pixels.Color(0, 0, 0));
  pixels.setPixelColor(3, pixels.Color(0, 0, 0));
  pixels.setPixelColor(2, pixels.Color(0, 0, 0));
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
  delay (70);
}

//Zera os valores todos os pedais
void valorPedaloff() {
     valorPedal1 = 0;
     valorPedal2 = 0;
     valorPedal3 = 0;
     valorPedal4 = 0;
     valorPedal5 = 0;
     valorPedal6 = 0;
     valorPedal7 = 0;
     valorPedal8 = 0;
     valorPedal9 = 0;
     valorPedal10 = 0;
    }

//Zera os valores todos os pedais exceto o Pedal 1
void valorPedaloff1() {
     valorPedal2 = 0;
     valorPedal3 = 0;
     valorPedal4 = 0;
     valorPedal5 = 0;
     valorPedal6 = 0;
     valorPedal7 = 0;
     valorPedal8 = 0;
     valorPedal9 = 0;
     valorPedal10 = 0;
    }

//Zera os valores todos os pedais exceto o Pedal 2
void valorPedaloff2() {
     valorPedal1 = 0;
     valorPedal3 = 0;
     valorPedal4 = 0;
     valorPedal5 = 0;
     valorPedal6 = 0;
     valorPedal7 = 0;
     valorPedal8 = 0;
     valorPedal9 = 0;
     valorPedal10 = 0;
    }

//Zera os valores todos os pedais exceto o Pedal 3
void valorPedaloff3() {
     valorPedal1 = 0;
     valorPedal2 = 0;
     valorPedal4 = 0;
     valorPedal5 = 0;
     valorPedal6 = 0;
     valorPedal7 = 0;
     valorPedal8 = 0;
     valorPedal9 = 0;
     valorPedal10 = 0;
    }

//Zera os valores todos os pedais exceto o Pedal 4
void valorPedaloff4() {
     valorPedal1 = 0;
     valorPedal2 = 0;
     valorPedal3 = 0;
     valorPedal5 = 0;
     valorPedal6 = 0;
     valorPedal7 = 0;
     valorPedal8 = 0;
     valorPedal9 = 0;
     valorPedal10 = 0;
    }

//Zera os valores todos os pedais exceto o Pedal 5
void valorPedaloff5() {
     valorPedal1 = 0;
     valorPedal2 = 0;
     valorPedal3 = 0;
     valorPedal4 = 0;
     valorPedal6 = 0;
     valorPedal7 = 0;
     valorPedal8 = 0;
     valorPedal9 = 0;
     valorPedal10 = 0;
    }

//Zera os valores todos os pedais exceto o Pedal 6
void valorPedaloff6() {
     valorPedal1 = 0;
     valorPedal2 = 0;
     valorPedal3 = 0;
     valorPedal4 = 0;
     valorPedal5 = 0;
     valorPedal7 = 0;
     valorPedal8 = 0;
     valorPedal9 = 0;
     valorPedal10 = 0;
    }

//Zera os valores todos os pedais exceto o Pedal 7
void valorPedaloff7() {
     valorPedal1 = 0;
     valorPedal2 = 0;
     valorPedal3 = 0;
     valorPedal4 = 0;
     valorPedal5 = 0;
     valorPedal6 = 0;
     valorPedal8 = 0;
     valorPedal9 = 0;
     valorPedal10 = 0;
    }

//Zera os valores todos os pedais exceto o Pedal 8
void valorPedaloff8() {
     valorPedal1 = 0;
     valorPedal2 = 0;
     valorPedal3 = 0;
     valorPedal4 = 0;
     valorPedal5 = 0;
     valorPedal6 = 0;
     valorPedal7 = 0;
     valorPedal9 = 0;
     valorPedal10 = 0;
    }

//Zera os valores todos os pedais exceto o Pedal 9
void valorPedaloff9() {
     valorPedal1 = 0;
     valorPedal2 = 0;
     valorPedal3 = 0;
     valorPedal4 = 0;
     valorPedal5 = 0;
     valorPedal6 = 0;
     valorPedal7 = 0;
     valorPedal8 = 0;
     valorPedal10 = 0;
    }

//Zera os valores todos os pedais exceto o Pedal 10
void valorPedaloff10() {
     valorPedal1 = 0;
     valorPedal2 = 0;
     valorPedal3 = 0;
     valorPedal4 = 0;
     valorPedal5 = 0;
     valorPedal6 = 0;
     valorPedal7 = 0;
     valorPedal8 = 0;
     valorPedal9 = 0;
    }

/* Função que apaga todos os Leds */
void apagaLed() {
  for (int i = 0; i <= 10 ; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    pixels.show();
  }
}
