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


uint8_t buffer[1024];

int insert_values(unsigned char** buffer){

  /// inserimento singolo a rotazione
  Ninux__Sensordata *sensordata2;
  Ninux__Sensordata *psensordata2 = &sensordata2;
  sensordata_deserialize(psensordata2,(unsigned char*) *buffer);
  Ninux__Myset *set3;
  set3= malloc (sizeof (Ninux__Myset)); //one insert at once
  sensordata_add_set(sensordata2,set3,555555);
  sensordata_add_entry(sensordata2,set3,"temp",55);
  sensordata_add_entry(sensordata2,set3,"pres",5555);
  sensordata_add_entry(sensordata2,set3,"humi",55);
  sensordata_print_all(sensordata2);
  sensordata_serialize(sensordata2,(uint8_t**) buffer);
  printf("mio buffer: %s\n",*buffer);
  printf("lunghezza buf:%d\n",strlen((char*)*buffer));
  /////////////
  return 0;
}

int insert_values2(unsigned char** buffer, int timestamp, char** keys,int* values, int len){

  /// inserimento singolo a rotazione
  Ninux__Sensordata *sensordata2;
  Ninux__Sensordata *psensordata2 = &sensordata2;
  sensordata_deserialize(psensordata2,(unsigned char*) *buffer);
  Ninux__Myset *set3;
  set3= malloc (sizeof (Ninux__Myset)); //one insert at once
  sensordata_add_set(sensordata2,set3,timestamp);
  int i;
  for(i=0; i<len;i++){
  	sensordata_add_entry(sensordata2,set3,keys[i],values[i]);
  }
  sensordata_print_all(sensordata2);
  sensordata_serialize2(sensordata2,(uint8_t**) *buffer);
  printf("mio buffer: %s\n",*buffer);
  printf("lunghezza buf:%d\n",strlen((char*)*buffer));
  /////////////
  return 0;
}
int test4(){

  // inizializzazione
  Ninux__Sensordata sensordata = NINUX__SENSORDATA__INIT;
  sensordata_init(&sensordata);
  //char* buffer;
  sensordata_serialize(&sensordata,(uint8_t**) &buffer);
  ///////


  //printf("mio buffer: %s\n",buffer);
  //printf("lunghezza buf:%d\n",strlen((char*)buffer));

  	//insert_values(&buffer);
        char* keys[]={"temp","hum","wind","pres"}; 
        int values[]={22,78,23,1013};
  	insert_values2(&buffer,12334234,keys,values,4);
	keys[0]="temp";
        values[0]=33;
  	insert_values2(&buffer,3333333,keys,values,4);

  ///// inserimento singolo a rotazione
  //Ninux__Sensordata *sensordata2;
  //Ninux__Sensordata *psensordata2 = &sensordata2;
  //sensordata_deserialize(psensordata2,(unsigned char*) buffer);
  //Ninux__Myset *set3;
  //set3= malloc (sizeof (Ninux__Myset)); //one insert at once
  //sensordata_add_set(sensordata2,set3,555555);
  //sensordata_add_entry(sensordata2,set3,"temp",55);
  //sensordata_add_entry(sensordata2,set3,"pres",5555);
  //sensordata_print_all(sensordata2);
  //sensordata_serialize(sensordata2,(uint8_t**) &buffer);
  //printf("mio buffer: %s\n",buffer);
  //printf("lunghezza buf:%d\n",strlen((char*)buffer));
  ///////////////

  
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
