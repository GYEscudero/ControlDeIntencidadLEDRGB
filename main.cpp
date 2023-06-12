/*********************************************
 *********************************************
 **                                         **
 **   Programa que reAliza la programación  **
 **   de un Arduino UNO para  controlar la  **
 **   intencidad de iluminacion de   leds,  **
 **   mediante un  control   remoto  y  de  **
 **   forma  manual  con   potenciometros,  **
 **   haciando  este   cambio mediante  un  **
 **   interruptor.                          **
 **                                         **
 **   Autor: Gerson Yaser Escudero.         **
 **   Fecha: 11 de Junio 2023.              **
 **   Dispositivo: Arduino UNO.             **
 **                                         **
 *********************************************
 *********************************************/

#include <Arduino.h>
#include <IRremote.h> /* Libreria para el protocolo IR (Comunicacion infrarojo 
                         del control remonto y ArduinoUNO) */
#include "pines.h"    /* Libreria para configurar pines */

/* Directivas de preprocesamiento */
/* Teclas control Remoto */
#define UNO 0x9716BE3F
#define DOS 0x3D9AE3F7
#define TRES 0X6182021B
#define REGRESAR 0x97483BFB
#define MAS 0xE5CFBD7F
#define MENOS 0xA3C8EDDB

/* Protocolo para la función que indica que pines son entrada o salida */
void pines_configuracion(int *LEDAZUL, int *LEDVERDE, int *LEDROJO, int *INTERRUPTOR_MANUAL);

/* Variables para definir los  pines de losLEDS */
int LED_AZUL = 5;
int LED_VERDE = 6;
int LED_ROJO = 9;

int BRILLO = 0; /* Variable Auxiliar */

/* Variables para la intensidad de los LEDS */
int BRILLO_AZUL = 177;  /* El convertidor analogico es de 255 niveles */
int BRILLO_VERDE = 177; /* la mitad aproximada seria 177, arrojaria un */
int BRILLO_ROJO = 177;  /* Un nivel nedio de intensidad. */

int INTERRUPTOR = 2; /* Variable para hacer  cambio de control manual a remoto */

/* Variables para definir los  pines de los Potenciometros */
int POT_UNO = A0;   /* Se conectaran a las entradas analogicas */
int POT_DOS = A1;   /* Los potenciometros  */
int POT_TRES = A2;

int BRILLO_POT = 0; /* Variable Auxiliar */

int SENSOR = 11;         /* Pin de entrada al Arduino, sensor infrarrojo -> Arduino */
IRrecv irrecv(SENSOR);  /* Objeto de la libreria  "<IRremote.h>" receptor del sensor 
                           el cual va conectado al PIN 11 del Arduino*/
decode_results codigo;  /* Objeto de la libreria  "<IRremote.h>" decodifica la señal del
                           transmisor en el control remoto al precionar un botón, dando 
                           el sinonimo de "codigo" y almacenando la trama del botón que se
                           preciona */
/*-------------------------------------------------------------------------------------------*/
void setup ()     /* Función donde se inicializa la configuracion de los pines
                     y configuracion de funcionamiento para trabajar 
                     con nuestro Arduino UNO */
{ /* Inicio de la funcion setup */
  Serial.begin(9600);   /* Inicializacion de interfaz con la computadora y ArduinoUNO
                           para visualiar los datos  en la computadora que vaya captando 
                           el Arduino a una velocidad de 9600 bps  */
  irrecv.enableIRIn();  /* Inicializa recepcion de datos de la libreria <IRremote.h> */

  pines_configuracion(&LED_AZUL, &LED_VERDE, &LED_ROJO, &INTERRUPTOR); /* Llamado a la funcion que 
                                                                          configura Los pines */ 
} /* Fin de la función setup */

void loop()   /* Función donde se realizara el codigo a trabajar en el ArduinoUNO */
{ /* Inicio de la funcion loop */
  if (digitalRead(INTERRUPTOR) == LOW) /* Interruptor en Tierra control "Remoto" */
  {
    if (irrecv.decode(&codigo)) /* Si ya se tiene una trama de datos lista transmitida por 
                                  el control remoto se decodifican los datos pasando por 
                                  referencia "codigo" para poder trabajarlo dentro de  
                                  esta función y que determine que codigo corresponde a  
                                  la tecla presionada*/
    {
      Serial.println(codigo.value, HEX); /* Se imprime en el monitor serial que tecla se esta
                                            precionando en un formato Hexdecimal *
      
      /*------------------------------------------
        --Se escoge con que led se va a trabajar--
        ------------------------------------------ */
      switch (codigo.value) /* Inicio del switch - case */
      {
        case UNO: /* Prende primer LED */
          
          analogWrite(LED_AZUL, BRILLO_AZUL);
          BRILLO = 1; /* Variable auxuliar para ajustar Brillo */

          break;

        case DOS: /* Prende segundo LED */
          
          analogWrite(LED_VERDE, BRILLO_VERDE);
          BRILLO = 2; /* Variable auxuliar para ajustar Brillo */

          break;
        
        case TRES: /* Prende tercer LED */
          
          analogWrite(LED_ROJO, BRILLO_ROJO);
          BRILLO = 3; /* Variable auxuliar para ajustar Brillo */

          break;
        
      } /* Fin del switch - case */
      /*------------------------------------------*/

      /*------------------------------------------
        --Setencias para ajustar brillos de LEDS--
        ------------------------------------------ */
      /* Primer LED */
      if (BRILLO ==1) 
      {    
        if (codigo.value == MAS) /* Mas Brillo */
        {
          if (BRILLO_AZUL < 255 )
          {
            BRILLO_AZUL  += 26;
                    
          }
            if (BRILLO_AZUL > 255)
          {
                    
            BRILLO_AZUL  = 255;
          }   
        }
        if (codigo.value == MENOS) /* Menos Brillo */
        {
          if(BRILLO_AZUL > 0 )
          {
            BRILLO_AZUL -= 26;
          }
          if (BRILLO_AZUL < 0)
          {
            BRILLO_AZUL  = 0;
          }
          
        }
        analogWrite(LED_AZUL, BRILLO_AZUL);    
      }
      /* Segundo LED */
      if (BRILLO == 2)
      {    
        if (codigo.value == MAS) /* Mas Brillo */
        {
          if (BRILLO_VERDE < 255 )
          {
            BRILLO_VERDE  += 26;
                    
          }
            if (BRILLO_VERDE > 255)
          {
                    
            BRILLO_VERDE  = 255;
          }   
        }

        if (codigo.value == MENOS)  /* Menos Brillo */
        {
          if(BRILLO_VERDE > 0 )
          {
            BRILLO_VERDE -= 26;
          }
          if (BRILLO_VERDE < 0)
          {
            BRILLO_VERDE  = 0;
          }
        }
        analogWrite(LED_VERDE, BRILLO_VERDE);
      }
      /* Tercer LED */
      if (BRILLO == 3)
      {    
        if (codigo.value == MAS) /* Mas Brillo */
        {
          if (BRILLO_ROJO < 255 )
          {
            BRILLO_ROJO  += 26;
                    
          }
            if (BRILLO_ROJO > 255)
          {
                    
            BRILLO_ROJO  = 255;
          }   
        }
        if (codigo.value == MENOS)  /* Menos Brillo */
        {
          if(BRILLO_ROJO > 0 )
          {
            BRILLO_ROJO -= 26;
          }
          if (BRILLO_ROJO < 0)
          {
            BRILLO_ROJO  = 0;
          }  
        }
        analogWrite(LED_ROJO, BRILLO_ROJO);    
      }
      /* Fin de sentencias para regular brillo de LEDS */
      
      irrecv.resume();  /* Indicamos que despues de recivir un valor se esta listo para recivir 
                          uno nuevo */  
    }
  }

  else /* Interruptor en 5V control "Manual" */
  {
    BRILLO_POT = analogRead(POT_UNO) / 4; /* Se divide entre cuatro ya que el Convertidor */
    analogWrite(LED_AZUL, BRILLO_POT);    /* Digital Analogico de los pines A0,A1,A2 es*/ 
    BRILLO_POT = analogRead(POT_DOS) / 4; /* 1020 y asi se ajusta a los de PWM de 255 */
    analogWrite(LED_VERDE, BRILLO_POT);
    BRILLO_POT = analogRead(POT_TRES) / 4;
    analogWrite(LED_ROJO, BRILLO_POT);
  }  
  delay(100); /* Demora  de 100ms para permitirle tener pausar al programa ya que es muy rapida
                 la ejecucion del programa */
} /* Fin de la función setup */

