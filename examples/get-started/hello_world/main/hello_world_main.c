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


int myarray_init(Tutorial__Array *array){
  //inizializza array con set vuoto
  Tutorial__Myset **sets;
  sets=malloc(sizeof (Tutorial__Myset *));
  array->n_sets = 0;
  array->sets=sets;
  return 0;
}

int myarray_add_set(Tutorial__Array *array, Tutorial__Myset *set, int timestamp){
  //aggiunge un set creato esternamente all'array nella prossima posizione libera
  (array->n_sets)+=1;
  printf("num set:%d\n",array->n_sets);
  array->sets = realloc (array->sets,sizeof (Tutorial__Myset *)* array->n_sets); //one insert at once
  array->sets[array->n_sets-1]=set;
  tutorial__myset__init (array->sets[array->n_sets-1]);
  array->sets[array->n_sets-1]->timestamp=timestamp;
  array->sets[array->n_sets-1]->n_entries=0;
  Tutorial__Entry **entries;
  entries=malloc(sizeof (Tutorial__Entry *));
  array->sets[array->n_sets-1]->entries=entries;
  return 0;
}

int myarray_add_entry(Tutorial__Array *array, Tutorial__Myset *set, char* key, int value){
  //aggiunge un entry al set indicato aggiungendolo alle entries del set
  //printf("l array ha %d sets\n",array->n_sets);
  //printf("il set ha %d entries\n",set->n_entries);
  set->n_entries+=1;
  //printf("il set ha %d entries\n",set->n_entries);
  array->sets[array->n_sets-1]->entries=realloc(set->entries,sizeof (Tutorial__Entry *)* set->n_entries);
  array->sets[array->n_sets-1]->n_entries=set->n_entries;
  array->sets[array->n_sets-1]->entries[set->n_entries-1]=malloc(sizeof(Tutorial__Entry));
  tutorial__entry__init (array->sets[array->n_sets-1]->entries[set->n_entries-1]);
  array->sets[array->n_sets-1]->entries[set->n_entries-1]->key=malloc(sizeof(char)*5);
  sprintf(array->sets[array->n_sets-1]->entries[set->n_entries-1]->key,"%s",key);
  array->sets[array->n_sets-1]->entries[set->n_entries-1]->value=value;
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

int dealloco(Tutorial__Array *array){
  int i,k;
  for(i=0;i<array->n_sets;i++){
	for(k=0;k<array->sets[i]->n_entries;k++){
 	 	free(array->sets[i]->entries[k]);
	}
	free(array->sets[i]->entries);
  }
  free(array->sets);
  return 0;
}


int test4(){
  Tutorial__Array array = TUTORIAL__ARRAY__INIT;
  myarray_init(&array);


  Tutorial__Myset *set0;
  set0= malloc (sizeof (Tutorial__Myset)); //one insert at once
 
  myarray_add_set(&array,set0,1574244029);
  myarray_add_entry(&array,set0,"temp",19);
  myarray_add_entry(&array,set0,"pres",1013);
  myarray_add_entry(&array,set0,"batt",42);
  myarray_add_entry(&array,set0,"wind",223);

  printf("key: %s\n", set0->entries[set0->n_entries-1]->key);
  printf("key: %s\n", array.sets[array.n_sets-1]->entries[set0->n_entries-1]->key);

  Tutorial__Myset *set1;
  set1= malloc (sizeof (Tutorial__Myset)); //one insert at once
  myarray_add_set(&array,set1,1574244329);
  myarray_add_entry(&array,set1,"temp",19);
  myarray_add_entry(&array,set1,"pres",1013);
  myarray_add_entry(&array,set1,"batt",42);
  myarray_add_entry(&array,set1,"wind",223);


  Tutorial__Myset *set2;
  set2= malloc (sizeof (Tutorial__Myset)); //one insert at once
  myarray_add_set(&array,set2,1574244629);
  myarray_add_entry(&array,set2,"temp",19);
  myarray_add_entry(&array,set2,"pres",1013);
  myarray_add_entry(&array,set2,"batt",42);
  myarray_add_entry(&array,set2,"wind",223);


  impacchetto(&array);
  dealloco(&array);
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
