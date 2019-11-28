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

int test4(){

  // inizializzazione
  Ninux__Sensordata sensordata = NINUX__SENSORDATA__INIT;
  sensordata_init(&sensordata);
  char* buffer;
  sensordata_serialize(&sensordata,(uint8_t**) &buffer);
  ///////


  //printf("mio buffer: %s\n",buffer);
  //printf("lunghezza buf:%d\n",strlen((char*)buffer));

  /// inserimento singolo a rotazione
  Ninux__Sensordata *sensordata2;
  Ninux__Sensordata *psensordata2 = &sensordata2;
  sensordata_deserialize(psensordata2,(unsigned char*) buffer);
  Ninux__Myset *set3;
  set3= malloc (sizeof (Ninux__Myset)); //one insert at once
  sensordata_add_set(sensordata2,set3,555555);
  sensordata_add_entry(sensordata2,set3,"temp",55);
  sensordata_add_entry(sensordata2,set3,"pres",5555);
  sensordata_print_all(sensordata2);
  sensordata_serialize(sensordata2,(uint8_t**) &buffer);
  printf("mio buffer: %s\n",buffer);
  printf("lunghezza buf:%d\n",strlen((char*)buffer));
  /////////////

  /// inserimento singolo a rotazione
  Ninux__Sensordata *sensordata3;
  Ninux__Sensordata *psensordata3 = &sensordata3;
  sensordata_deserialize(psensordata3,(unsigned char*) buffer);
  Ninux__Myset *set4;
  set4= malloc (sizeof (Ninux__Myset)); //one insert at once
  sensordata_add_set(sensordata3,set4,333333);
  sensordata_add_entry(sensordata3,set4,"temp",33);
  sensordata_add_entry(sensordata3,set4,"pres",3333);
  sensordata_print_all(sensordata3);
  sensordata_serialize(sensordata3,(uint8_t**) &buffer);
  printf("mio buffer: %s\n",buffer);
  printf("lunghezza buf:%d\n",strlen((char*)buffer));
  /////////////

  /// inserimento singolo a rotazione
  Ninux__Sensordata *sensordata4;
  Ninux__Sensordata *psensordata4 = &sensordata4;
  sensordata_deserialize(psensordata4,(unsigned char*) buffer);
  Ninux__Myset *set5;
  set5= malloc (sizeof (Ninux__Myset)); //one insert at once
  sensordata_add_set(sensordata4,set5,444444);
  sensordata_add_entry(sensordata4,set5,"temp",44);
  sensordata_add_entry(sensordata4,set5,"pres",4444);
  sensordata_print_all(sensordata4);
  sensordata_serialize(sensordata4,(uint8_t**) &buffer);
  printf("mio buffer: %s\n",buffer);
  printf("lunghezza buf:%d\n",strlen((char*)buffer));
  /////////////
  
  //sensordata_free(&sensordata);
  //sensordata_free(&sensordata2);
  return 0;
}


void app_main()
{
    printf("Hello world!\n");

    //char* message;
    //message=malloc(sizeof(char)*70); 

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
