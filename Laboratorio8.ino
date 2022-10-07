/*
* Los temporizadores ESP32 PWM nos permiten configurar el ancho del temporizador (máximo 20 bits). De este modo
 * la duración del "tick" del temporizador es (pulse_period/2**timer_width), y la ecuación para pulse_high_width
 * (la parte del ciclo (20 ms en nuestro caso) en la que la señal es alta) se convierte en:
 *
 * pulse_high_width = recuento * tick_length
 * = cuenta * (pulse_period/2**timer_width)
 *
 * y cuenta = (pulse_high_width / (pulse_period/2**timer_width))
 *
 * Por ejemplo, si queremos un pulse_high_width de 1500us, establecemos pulse_period en 20ms (20000us)
 * (este valor se establece en la llamada ledcSetup) y count (utilizado en la llamada ledcWrite) para
 * 1500/(20000/65655), o 4924. Este es el valor que escribimos en el temporizador en la llamada ledcWrite.
 *
 * Como ejemplo concreto, supongamos que queremos barrer repetidamente cuatro servos Tower Pro SG90
 * de 0 a 180 grados. El rango de ancho de pulso publicado para el SG90 es 500-2400us. De este modo,
 * debemos variar el conteo usado en ledcWrite de 1638 a 7864.
 * 
 */

 // Valores ajustados para el SG90
 #define COUNT_LOW 1638
 #define COUNT_HIGH 7864
 #define TIMER_WIDTH 16
 int i;
// Los pines PWM GPIO recomendados en el ESP32 incluyen 2,4,12-19,21-23,25-27,32-33
void setup() {
   ledcSetup(1, 50, TIMER_WIDTH); // canal 1, 50 Hz, 16-bit width
   ledcAttachPin(26, 1);   // GPIO 22 asignado al canal 1
   ledcSetup(2, 50, TIMER_WIDTH); // canal 2, 50 Hz, 16-bit width
   ledcAttachPin(25, 2);   // GPIO 19 asignado al canal 2
   }

void loop() {
   for (i=COUNT_LOW ; i < COUNT_HIGH ; i=i+100)
   {
      ledcWrite(1, i);       //  servo 1
      delay(20);
   }  
   for (i=COUNT_HIGH ; i > COUNT_LOW ; i=i-100)
   {
      ledcWrite(1, i);       // servo 1
      delay(20);
   }
   for (i=COUNT_LOW ; i < COUNT_HIGH ; i=i+100)
   {
      ledcWrite(2, i);       //  servo 2
      delay(20);
   }  
   for (i=COUNT_HIGH ; i > COUNT_LOW ; i=i-100)
   {
      ledcWrite(2, i);       //  servo 2
      delay(20);
   }
}
