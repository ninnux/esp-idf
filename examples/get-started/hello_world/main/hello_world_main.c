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

//int insert_values(unsigned char** buffer){
//
//  /// inserimento singolo a rotazione
//  Ninux__Sensordata *sensordata2;
//  Ninux__Sensordata *psensordata2 = &sensordata2;
//  sensordata_deserialize(psensordata2,(unsigned char*) *buffer);
//  Ninux__Myset *set3;
//  set3= malloc (sizeof (Ninux__Myset)); //one insert at once
//  sensordata_add_set(sensordata2,set3,555555);
//  sensordata_add_entry(sensordata2,set3,"temp",55);
//  sensordata_add_entry(sensordata2,set3,"pres",5555);
//  sensordata_add_entry(sensordata2,set3,"humi",55);
//  sensordata_print_all(sensordata2);
//  sensordata_serialize(sensordata2,(uint8_t**) buffer);
//  printf("mio buffer: %s\n",*buffer);
//  printf("lunghezza buf:%d\n",strlen((char*)*buffer));
//  /////////////
//  return 0;
//}

int insert_values2(unsigned char** buffer, int timestamp, char** keys,int* values, int len, int* size){

  /// inserimento singolo a rotazione
  Ninux__Sensordata *sensordata2;
  sensordata2=malloc(sizeof(Ninux__Sensordata));
  Ninux__Sensordata **psensordata2 = &sensordata2;
  //sensordata_deserialize(psensordata2,(unsigned char*) *buffer);
  printf("deserializzo %d bytes\n",*size);
  //sensordata2=ninux__sensordata__unpack(NULL,*size,buffer);/// FUNZIONA
  sensordata_deserialize2_size(psensordata2, buffer,size);
  printf("size:%d\n",*size);
  Ninux__Myset *set3;
  set3= malloc (sizeof (Ninux__Myset)); //one insert at once
  sensordata_add_set(sensordata2,set3,timestamp);
  int i;
  for(i=0; i<len;i++){
  	sensordata_add_entry(sensordata2,set3,keys[i],values[i]);
  }
  sensordata_print_all(sensordata2);
  //sensordata_serialize(sensordata2,(uint8_t**) buffer);
  printf("size buf:%d\n",*size);
  sensordata_serialize2_size(sensordata2, buffer,size);
  //printf("mio buffer: %s\n",*buffer);
  //printf("lunghezza buf:%d\n",strlen((char*)*buffer));
  /////////////
  return 0;
}
int test4(){

  // inizializzazione
  Ninux__Sensordata sensordata = NINUX__SENSORDATA__INIT;
  sensordata_init(&sensordata);
  char* buffer;
  sensordata_serialize2_size(&sensordata,(uint8_t**) rtc_buffer,&rtc_buffer_len);
  ///////


  //printf("mio buffer: %s\n",buffer);
  //printf("lunghezza buf:%d\n",strlen((char*)buffer));

  	//insert_values(&buffer);
        char* keys[]={"temp","hum","wind","pres"}; 
        int values[]={22,78,23,1013};
  	insert_values2(&rtc_buffer,12334234,keys,values,4,&rtc_buffer_len);
	//keys[0]="temp";
        //values[0]=33;
        printf("fine primo inserimento\n");
        printf("%s\n",rtc_buffer);
        char* keys2[]={"temp","hum","wind","pres"}; 
        int values2[]={25,80,35,999};
  	insert_values2(&rtc_buffer,4444444,keys2,values2,4,&rtc_buffer_len);
        char* keys3[]={"temp","hum","wind","pres"}; 
        int values3[]={250,800,350,9999};
  	insert_values2(&rtc_buffer,5555555,keys3,values3,4,&rtc_buffer_len);

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
