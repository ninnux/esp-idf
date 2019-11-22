/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#include "array.pb-c.h"



int test () 
{
  Tutorial__Array array = TUTORIAL__ARRAY__INIT;
  Tutorial__Myset **sets;
  void *buf;
  unsigned len,i;
  // malloc per puntatori
  sets = malloc (sizeof (Tutorial__Myset *)); //one insert at once

  //definisco i set per l'array 
  array.n_sets = 1;
  array.sets =sets;

  //creo il primo  set
  sets[0]=malloc(sizeof(Tutorial__Myset));
  tutorial__myset__init (sets[0]);
  // riempio il set di dati 
  sets[0]->timestamp=1574244029;

  // definisco le entries per il set
  Tutorial__Entry **entries;
  entries = malloc (sizeof (Tutorial__Entry *)*3); //one insert at once
  sets[0]->n_entries=1;
  sets[0]->entries=entries;

  // riempio le entries di dati
  entries[0]=malloc(sizeof(Tutorial__Entry));
  tutorial__entry__init (entries[0]);
  entries[0]->key=malloc(sizeof(char)*4);
  sprintf(entries[0]->key,"temp");
  entries[0]->value=10;



  //impacchetto tutto
  len = tutorial__array__get_packed_size (&array); // This is the calculated packing length
  printf("len:%d",len);
  buf = malloc (len);                     // Allocate memory
  tutorial__array__pack (&array, buf);             // Pack msg, including submessages
  //via!!
  //fprintf(stderr,"Writing %d serialized bytes\n",len); // See the length of message
  //fwrite (buf, len, 1, stdout);           // Write to stdout to allow direct command line piping
  //sprintf(output,buf);

  //dealloco  
  free(sets[0]); 
  free(entries[0]); 
  free(sets); 
  free(entries); 
  return 0;
}

void app_main()
{
    printf("Hello world!\n");

    //char* message;
    //message=malloc(sizeof(char)*70); 
    test();

    for (int i = 10; i >= 0; i--) {
        printf("Restarting in %d seconds...\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    printf("Restarting now.\n");
    fflush(stdout);
    esp_restart();
}
