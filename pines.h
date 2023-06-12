#include <Arduino.h>

/* Funcion que configura el uso de determindos pines */
void pines_configuracion(int *LEDAZUL, int *LEDVERDE, int *LEDROJO, int *INTERRUPTOR_MANUAL)
{
    /* Configuración de pines */ 
    pinMode(*LEDAZUL, OUTPUT);
    pinMode(*LEDVERDE, OUTPUT);
    pinMode(*LEDROJO, OUTPUT);
    pinMode(*INTERRUPTOR_MANUAL, INPUT);
}
  
  