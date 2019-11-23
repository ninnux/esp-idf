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


int myarray_init(Tutorial__Array *array, Tutorial__Myset **sets){
  array->n_sets = 0;
  array->sets=sets;
  return 0;
}

int myarray_add_set(Tutorial__Array *array, Tutorial__Myset **sets, Tutorial__Entry **entries, int timestamp){
//int myarray_add_set(Tutorial__Array *array, int timestamp){
  array->n_sets+=1;
  int setindex=0;
  setindex=array->n_sets-1;
  sets = realloc (sets,sizeof (Tutorial__Myset *)* 1); //one insert at once
  sets[setindex]=malloc(sizeof(Tutorial__Myset));
  tutorial__myset__init (sets[setindex]);
  sets[setindex]->timestamp=timestamp;
  entries = malloc (sizeof (Tutorial__Entry *)); //one insert at once
  sets[setindex]->n_entries=0;
  sets[setindex]->entries=entries;
  return 0;
}

//int myarray_add_entry(Tutorial__Array *array, Tutorial__Myset **sets, Tutorial__Entry **entries, char* key, int value){
int myarray_add_entry(Tutorial__Array *array, Tutorial__Myset **sets, char* key, int value){
  int setindex=array->n_sets-1;
  Tutorial__Entry **entries;
  entries=sets[setindex]->entries;
  int setentries=sets[setindex]->n_entries+=1;
  printf("setentries:%d\n",setentries);
  entries=realloc(entries,sizeof (Tutorial__Entry *)* setentries); //one insert at once
  entries[setentries-1]=malloc(sizeof(Tutorial__Entry));
  tutorial__entry__init (entries[setentries-1]);
  entries[setentries-1]->key=malloc(sizeof(char)*5);
  sprintf(entries[setentries-1]->key,"%s",key);
  entries[setentries-1]->value=value;
  sets[setindex]->entries=entries;
  return 0;
}

int impacchetto(Tutorial__Array *array){
  int len=0;
  uint8_t* buf;
  len = tutorial__array__get_packed_size (array); // This is the calculated packing length
  printf("Writing %d serialized bytes\n",len); // See the length of message
  buf = malloc (len);                     // Allocate memory
  tutorial__array__pack (array, buf);             // Pack msg, including submessages
  printf("buf:%s",(char*)buf);   
  return 0;
}

int test4(){
  Tutorial__Array array = TUTORIAL__ARRAY__INIT;
  Tutorial__Myset **sets;
  Tutorial__Entry **entries;
  sets = malloc (sizeof (Tutorial__Myset *)); //one insert at once
  myarray_init(&array,sets);
  entries = malloc (sizeof (Tutorial__Entry *));
  myarray_add_set(&array,(Tutorial__Myset**)sets,entries,1574244029);
  //myarray_add_entry(&array,sets, entries, "temp",19);
  myarray_add_entry(&array,sets,"temp",19);
  myarray_add_entry(&array,sets,"pres",1013);
  myarray_add_entry(&array,sets,"batt",42);
  myarray_add_entry(&array,sets,"wind",223);
  impacchetto(&array);
  //int len=0;
  //uint8_t* buf;
  //len = tutorial__array__get_packed_size (&array); // This is the calculated packing length
  //printf("Writing %d serialized bytes\n",len); // See the length of message
  //buf = malloc (len);                     // Allocate memory
  //tutorial__array__pack (&array, buf);             // Pack msg, including submessages
  //printf("buf:%s",(char*)buf);   
  return 0;
}

//int test3()
//{
//  int sum=0;
//  Tutorial__Array array = TUTORIAL__ARRAY__INIT;
//  unsigned len,i;
//
//  // malloc per puntatori
//  Tutorial__Myset **sets;
//  sets = malloc (sizeof (Tutorial__Myset *)); //one insert at once
//  sets = realloc (sets,sizeof (Tutorial__Myset *)*2); //one insert at once
//  sum+=sizeof (Tutorial__Myset *)*2;
//  //definisco i set per l'array 
//  array.n_sets = 2;
//  array.sets =sets;
//
//  //creo il primo  set
//  sets[0]=malloc(sizeof(Tutorial__Myset));
//  sum+=sizeof (Tutorial__Myset );
//  tutorial__myset__init (sets[0]);
//  // riempio il set di dati 
//  sets[0]->timestamp=1574244029;
//
//  // definisco le entries per il set
//  Tutorial__Entry **entries;
//  entries = malloc (sizeof (Tutorial__Entry *)*3); //one insert at once
//  sum+=sizeof (Tutorial__Entry *)*3;
//  sets[0]->n_entries=3;
//  sets[0]->entries=entries;
//
//  // riempio le entries di dati
//  entries[0]=malloc(sizeof(Tutorial__Entry));
//  sum+=sizeof (Tutorial__Entry );
//  tutorial__entry__init (entries[0]);
//  entries[0]->key=malloc(sizeof(char)*5);
//  sum+=sizeof (sizeof(char)*5);
//  sprintf(entries[0]->key,"temp");
//  entries[0]->value=10;
//
//  entries[1]=malloc(sizeof(Tutorial__Entry));
//  sum+=sizeof (Tutorial__Entry );
//  tutorial__entry__init (entries[1]);
//  entries[1]->key=malloc(sizeof(char)*5);
//  sum+=sizeof (sizeof(char)*5);
//  sprintf(entries[1]->key,"pres");
//  entries[1]->value=1013;
//
//  entries[2]=malloc(sizeof(Tutorial__Entry));
//  sum+=sizeof (Tutorial__Entry );
//  tutorial__entry__init (entries[2]);
//  entries[2]->key=malloc(sizeof(char)*4);
//  sum+=sizeof (sizeof(char)*4);
//  sprintf(entries[2]->key,"bat");
//  entries[2]->value=42;
//
//  //creo il secondo  set
//  sets[1]=malloc(sizeof(Tutorial__Myset));
//  sum+=sizeof (Tutorial__Myset );
//  tutorial__myset__init (sets[1]);
//  // riempio il set di dati 
//  sets[1]->timestamp=1574244329;
//
//  // definisco le entries per il set
//  Tutorial__Entry **entries2;
//  entries2 = malloc (sizeof (Tutorial__Entry *)*3); //one insert at once
//  sum+=sizeof (Tutorial__Entry *)*3;
//  sets[1]->n_entries=3;
//  sets[1]->entries=entries2;
//
//  // riempio le entries di dati
//  entries2[0]=malloc(sizeof(Tutorial__Entry));
//  sum+=sizeof (Tutorial__Entry );
//  tutorial__entry__init (entries2[0]);
//  entries2[0]->key=malloc(sizeof(char)*5);
//  sum+=sizeof (sizeof(char)*5);
//  sprintf(entries2[0]->key,"temp");
//  entries2[0]->value=10;
//
//  entries2[1]=malloc(sizeof(Tutorial__Entry));
//  sum+=sizeof (Tutorial__Entry );
//  tutorial__entry__init (entries2[1]);
//  entries2[1]->key=malloc(sizeof(char)*5);
//  sum+=sizeof (sizeof(char)*5);
//  sprintf(entries2[1]->key,"pres");
//  entries2[1]->value=1013;
//
//  entries2[2]=malloc(sizeof(Tutorial__Entry));
//  sum+=sizeof (Tutorial__Entry );
//  tutorial__entry__init (entries2[2]);
//  entries2[2]->key=malloc(sizeof(char)*4);
//  sum+=sizeof (sizeof(char)*4);
//  sprintf(entries2[2]->key,"bat");
//  entries2[2]->value=39;
//  
//  //impacchetto tutto
//  len = tutorial__array__get_packed_size (&array); // This is the calculated packing length
//  void *buf;
//  buf = malloc (len);                     // Allocate memory
//  tutorial__array__pack (&array, buf);             // Pack msg, including submessages
//  printf("Writing %d serialized bytes\n",len); // See the length of message
//  printf("sum %d\n",sum); // See the length of message
//  printf("buf:%s",(char*)buf);   
//
//  //dealloco  
//  free(sets[0]); 
//  free(entries[0]); 
//  free(entries[1]); 
//  free(entries[2]); 
//  free(sets[1]); 
//  free(entries2[0]); 
//  free(entries2[1]); 
//  free(sets); 
//  free(entries); 
//  free(entries2); 
//  return 0;
//}


//int test () 
//{
//  Tutorial__Array array = TUTORIAL__ARRAY__INIT;
//  Tutorial__Myset **sets;
//  void *buf;
//  unsigned len,i;
//  // malloc per puntatori
//  sets = malloc (sizeof (Tutorial__Myset *)); //one insert at once
//
//  //definisco i set per l'array 
//  array.n_sets = 1;
//  array.sets =sets;
//
//  //creo il primo  set
//  sets[0]=malloc(sizeof(Tutorial__Myset));
//  tutorial__myset__init (sets[0]);
//  // riempio il set di dati 
//  sets[0]->timestamp=1574244029;
//
//  // definisco le entries per il set
//  Tutorial__Entry **entries;
//  entries = malloc (sizeof (Tutorial__Entry *)); //one insert at once
//  sets[0]->n_entries=1;
//  sets[0]->entries=entries;
//
//// riempio le entries di dati
//  entries[0]=malloc(sizeof(Tutorial__Entry));
//  tutorial__entry__init (entries[0]);
//  entries[0]->key=malloc(sizeof(char)*4);
//  sprintf(entries[0]->key,"temp");
//  entries[0]->value=10;
//
//
//
//  //impacchetto tutto
//  len = tutorial__array__get_packed_size (&array); // This is the calculated packing length
//  printf("len:%d",len);
//  //buf = (uint8_t *) malloc (len);                     // Allocate memory
//  tutorial__array__pack (&array, sbuf);             // Pack msg, including submessages
//  //via!!
//  //fprintf(stderr,"Writing %d serialized bytes\n",len); // See the length of message
//  //fwrite (buf, len, 1, stdout);           // Write to stdout to allow direct command line piping
//  //sprintf(output,buf);
//  printf("Writing %d serialized bytes\n",len); // See the length of message
//  printf("buf:%s",(char*)sbuf);   
//  
//
//  //dealloco  
//  //free(buf);
//  free(sets[0]); 
//  free(entries[0]); 
//  free(sets); 
//  free(entries); 
//  return 0;
//}

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
