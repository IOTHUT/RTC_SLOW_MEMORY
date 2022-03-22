#include <Arduino.h>


#define TIME_TO_WAKEUP  3000        //tempo para o ESP entrar no modo DeepSleep [ms]
#define TIME_TO_SLEEP   3000        //tempo para o ESP sair do modo DeepSleep [ms]
#define uS_TO_MS_FACTOR 1000        //fator de conversar de us para ms 



RTC_DATA_ATTR unsigned int loop_counter_rtc = 0x00;         //variavel para contagem de incremento no void loop
              unsigned int loop_counter_without_rtc = 0x00;     



void setup(){
  Serial.begin(115200);
  
  //---- debug ----
  Serial.println();
  Serial.println("System --> Init");                                             
  Serial.println("setup com rtc --> " + String(loop_counter_rtc));         
  Serial.println("setup sem rtc --> " + String(loop_counter_without_rtc)); 
  //---- debug ----

  esp_sleep_enable_timer_wakeup(TIME_TO_WAKEUP * uS_TO_MS_FACTOR); //configura wakeup timer
  delay(1000);
}


void loop(){

  static short int loop_count_aux = 0x00;           //contador auxiliar
  static short int loop_count_sleep_aux = 0x00;     //contador para entrar em modo DeepSleep

  loop_count_aux++;                                 //incrementa contador auxiliar
  loop_count_sleep_aux++;                           //incrementa contador para DeepSleep


  if(loop_count_aux >= 1000){                       //se atingiu 1 segundo
    loop_count_aux = 0x00;                          //zera contagem
    loop_counter_rtc++;                             //incrementa variavel armazenada no RTC
    loop_counter_without_rtc++;                     //incrementa variavel não armazenada no RTC


    Serial.println("com rtc --> " + String(loop_counter_rtc));         //debug
    Serial.println("sem rtc --> " + String(loop_counter_without_rtc)); //debug
  }


  if(loop_count_sleep_aux >= TIME_TO_SLEEP){       //se contagem atingiu tempo determinado...
    Serial.println();
    Serial.println("System --> Sleeping...");      //debug
    esp_deep_sleep_start();                        //entra em modo DeepSleep
  }
  delay(1);
}



