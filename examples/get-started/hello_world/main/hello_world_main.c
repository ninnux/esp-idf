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
  Ninux__Sensordata sensordata = NINUX__SENSORDATA__INIT;
  sensordata_init(&sensordata);


  Ninux__Myset *set0;
  set0= malloc (sizeof (Ninux__Myset)); //one insert at once
 
  sensordata_add_set(&sensordata,set0,1574244029);
  sensordata_add_entry(&sensordata,set0,"temp",19);
  sensordata_add_entry(&sensordata,set0,"pres",1013);
  sensordata_add_entry(&sensordata,set0,"batt",42);
  sensordata_add_entry(&sensordata,set0,"wind",223);

  printf("key: %s\n", set0->entries[set0->n_entries-1]->key);
  printf("key: %s\n", sensordata.sets[sensordata.n_sets-1]->entries[set0->n_entries-1]->key);

  Ninux__Myset *set1;
  set1= malloc (sizeof (Ninux__Myset)); //one insert at once
  sensordata_add_set(&sensordata,set1,1574244329);
  sensordata_add_entry(&sensordata,set1,"batt",42);
  sensordata_add_entry(&sensordata,set1,"wind",223);


  Ninux__Myset *set2;
  set2= malloc (sizeof (Ninux__Myset)); //one insert at once
  sensordata_add_set(&sensordata,set2,1574244629);
  sensordata_add_entry(&sensordata,set2,"temp",19);
  sensordata_add_entry(&sensordata,set2,"pres",1013);


  //sensordata_print_all(&sensordata);

  //impacchetto(&Sensordata);
  char* buffer;
  sensordata_serialize(&sensordata,(uint8_t**) &buffer);
  printf("mio buffer: %s\n",buffer);


  printf("lunghezza buf:%d\n",strlen((char*)buffer));

  Ninux__Sensordata *sensordata2;
  sensordata2 = ninux__sensordata__unpack(NULL,strlen(buffer),(uint8_t*) buffer);

  //printf("n_sets:%d\n",sensordata2->n_sets);
 // sensordata_print_all(sensordata2);

  //Ninux__Sensordata *psensordata2 = &sensordata2;
  //sensordata_deserialize(&psensordata2,(unsigned char*) buffer);
  //sensordata_print_all(&sensordata2);
  Ninux__Myset *set3;
  set3= malloc (sizeof (Ninux__Myset)); //one insert at once
  sensordata_add_set(sensordata2,set3,555555);
  sensordata_add_entry(sensordata2,set3,"temp",55);
  sensordata_add_entry(sensordata2,set3,"pres",5555);
  sensordata_print_all(sensordata2);
  //int i,k;
  //for (i = 0; i < sensordata2->n_sets; i++){
  //    for (k = 0; k < sensordata2->sets[i]->n_entries; k++){
  //            printf ("%d %s %d\n", sensordata2->sets[i]->timestamp,sensordata2->sets[i]->entries[k]->key,sensordata2->sets[i]->entries[k]->value);
  //    }
  //} 
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
