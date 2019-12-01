/* Deep sleep wake up example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_sleep.h"
#include "esp_log.h"
#include "esp32/ulp.h"
#include "driver/touch_pad.h"
#include "driver/adc.h"
#include "driver/rtc_io.h"
#include "soc/rtc_cntl_reg.h"
#include "soc/sens_reg.h"
#include "soc/rtc.h"

static RTC_DATA_ATTR struct timeval sleep_enter_time;
RTC_DATA_ATTR int counter=0;


#include "ninux_sensordata_pb.h"

RTC_DATA_ATTR char rtc_buffer[1024];
RTC_DATA_ATTR int rtc_buffer_len=0;

int test4(){

  sensordata_init2(&rtc_buffer,&rtc_buffer_len);

  //insert_values(&buffer);
  char* keys[]={"temp","hum","wind","pres"}; 
  int values[]={22,78,23,1013};
  sensordata_insert_values2(&rtc_buffer,12334234,keys,values,4,&rtc_buffer_len);
  sensordata_print_all2(&rtc_buffer,&rtc_buffer_len);

  //keys[0]="temp";
  //values[0]=33;
  printf("fine primo inserimento\n");
  printf("%s\n",rtc_buffer);

  char* keys2[]={"temp","hum","wind","pres"}; 
  int values2[]={25,80,35,999};
  sensordata_insert_values2(&rtc_buffer,4444444,keys2,values2,4,&rtc_buffer_len);

  char* keys3[]={"temp","hum","wind","pres"}; 
  int values3[]={250,800,350,9999};
  sensordata_insert_values2(&rtc_buffer,5555555,keys3,values3,4,&rtc_buffer_len);

  
  sensordata_print_all2(&rtc_buffer,&rtc_buffer_len);
  //sensordata_free(&sensordata);
  //sensordata_free(&sensordata2);
  return 0;
}

void app_main()
{
    struct timeval now;
    gettimeofday(&now, NULL);
    int sleep_time_ms = (now.tv_sec - sleep_enter_time.tv_sec) * 1000 + (now.tv_usec - sleep_enter_time.tv_usec) / 1000;

    switch (esp_sleep_get_wakeup_cause()) {
        case ESP_SLEEP_WAKEUP_EXT1: {
            uint64_t wakeup_pin_mask = esp_sleep_get_ext1_wakeup_status();
            if (wakeup_pin_mask != 0) {
                int pin = __builtin_ffsll(wakeup_pin_mask) - 1;
                printf("Wake up from GPIO %d\n", pin);
            } else {
                printf("Wake up from GPIO\n");
            }
            break;
        }
        case ESP_SLEEP_WAKEUP_TIMER: {
            printf("Wake up from timer. Time spent in deep sleep: %dms\n", sleep_time_ms);
  	    char* keys4[]={"temp","batt"}; 
  	    int values4[]={250,42};
  	    sensordata_insert_values2(&rtc_buffer,counter*1111111,keys4,values4,2,&rtc_buffer_len);
	    if(counter%2==0){
  	    	char* keys4[]={"wind","dire"}; 
  	    	int values4[]={50,180};
  	    	sensordata_insert_values2(&rtc_buffer,counter*1111111,keys4,values4,2,&rtc_buffer_len);
	    }
	    if(counter==5){
  	    	bzero(rtc_buffer,rtc_buffer_len);
                rtc_buffer_len=0;
	    }


  	    sensordata_print_all2(&rtc_buffer,&rtc_buffer_len);
            break;
        }
        case ESP_SLEEP_WAKEUP_UNDEFINED:
        default:{
            printf("Not a deep sleep reset\n");
	   // test4();
  	    sensordata_init2(&rtc_buffer,&rtc_buffer_len);
        }

    }


    vTaskDelay(1000 / portTICK_PERIOD_MS);

    const int wakeup_time_sec = 10;
    printf("Enabling timer wakeup, %ds\n", wakeup_time_sec);
    esp_sleep_enable_timer_wakeup(wakeup_time_sec * 1000000);

    //const int ext_wakeup_pin_1 = 25;
    //const uint64_t ext_wakeup_pin_1_mask = 1ULL << ext_wakeup_pin_1;
    //const int ext_wakeup_pin_2 = 26;
    //const uint64_t ext_wakeup_pin_2_mask = 1ULL << ext_wakeup_pin_2;

    //printf("Enabling EXT1 wakeup on pins GPIO%d, GPIO%d\n", ext_wakeup_pin_1, ext_wakeup_pin_2);
    //esp_sleep_enable_ext1_wakeup(ext_wakeup_pin_1_mask | ext_wakeup_pin_2_mask, ESP_EXT1_WAKEUP_ANY_HIGH);





    // Isolate GPIO12 pin from external circuits. This is needed for modules
    // which have an external pull-up resistor on GPIO12 (such as ESP32-WROVER)
    // to minimize current consumption.
    rtc_gpio_isolate(GPIO_NUM_12);

    rtc_gpio_init(GPIO_NUM_27);
    rtc_gpio_pullup_en(GPIO_NUM_27);
    rtc_gpio_pulldown_dis(GPIO_NUM_27);
    //rtc_gpio_hold_en(GPIO_NUM_5);
    printf("Entering deep sleep\n");
    gettimeofday(&sleep_enter_time, NULL);

    printf("counter=%d\n",counter);
    counter++;
    esp_deep_sleep_start();
}


