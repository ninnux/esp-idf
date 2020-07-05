/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#include "ninux_sensordata_pb.h"

char rtc_buffer[1024];
int rtc_buffer_len=0;

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

  char* keys4[]={"temp","batt"}; 
  int values4[]={250,42};
  sensordata_insert_values2(&rtc_buffer,666666,keys4,values4,2,&rtc_buffer_len);
  
  sensordata_print_all2(&rtc_buffer,&rtc_buffer_len);
  //sensordata_free(&sensordata);
  //sensordata_free(&sensordata2);
  return 0;
}


void app_main()
{
    printf("Hello world!\n");

    test4();

    for (int i = 10; i >= 0; i--) {
        printf("Restarting in %d seconds...\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    //free(message);
    printf("Restarting now.\n");
    fflush(stdout);
    esp_restart();
}
