/* MQTT publish test
    vTaskDelay(20000 / portTICK_PERIOD_MS);

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "esp_wifi.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "tcpip_adapter.h"
#include "protocol_examples_common.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "esp_log.h"
#include "mqtt_client.h"

static const char *TAG = "PUBLISH_TEST";

static EventGroupHandle_t mqtt_event_group;
const static int CONNECTED_BIT = BIT0;

static esp_mqtt_client_handle_t mqtt_client = NULL;

static char *expected_data = NULL;
static char *actual_data = NULL;
static size_t expected_size = 0;
static size_t expected_published = 0;
static size_t actual_published = 0;
static int qos_test = 0;


#if CONFIG_EXAMPLE_BROKER_CERTIFICATE_OVERRIDDEN == 1
static const uint8_t iot_eclipse_org_pem_start[]  = "-----BEGIN CERTIFICATE-----\n" CONFIG_EXAMPLE_BROKER_CERTIFICATE_OVERRIDE "\n-----END CERTIFICATE-----";
#else
extern const uint8_t iot_eclipse_org_pem_start[]   asm("_binary_iot_eclipse_org_pem_start");
#endif
extern const uint8_t iot_eclipse_org_pem_end[]   asm("_binary_iot_eclipse_org_pem_end");
 
void ninux_mqtt_publish(char* topic, char* data){
         int msg_id;
	 char mqtt_data[512];
 	 char mqtt_topic[512]; 
         bzero(mqtt_data,sizeof(mqtt_data));
         bzero(mqtt_topic,sizeof(mqtt_topic));
         sprintf(mqtt_data,"%s",data);
         sprintf(mqtt_topic,"%s",topic);
         
         esp_mqtt_client_stop(mqtt_client);
         xEventGroupClearBits(mqtt_event_group, CONNECTED_BIT);
         esp_mqtt_client_start(mqtt_client);
         //esp_mqtt_client_set_uri(mqtt_client, CONFIG_EXAMPLE_BROKER_TCP_URI);
         ESP_LOGI(TAG, "Note free memory: %d bytes", esp_get_free_heap_size());
         xEventGroupWaitBits(mqtt_event_group, CONNECTED_BIT, false, true, portMAX_DELAY);
 
         msg_id = esp_mqtt_client_publish(mqtt_client, mqtt_topic, mqtt_data, 0, 0, 0);
}

static esp_err_t mqtt_event_handler(esp_mqtt_event_handle_t event)
{
    esp_mqtt_client_handle_t client = event->client;
    static int msg_id = 0;
    static int actual_len = 0;
    // your_context_t *context = event->context;
    switch (event->event_id) {
    case MQTT_EVENT_CONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
        xEventGroupSetBits(mqtt_event_group, CONNECTED_BIT);
        msg_id = esp_mqtt_client_subscribe(client, CONFIG_EXAMPLE_SUBSCIBE_TOPIC, qos_test);
        ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);

        break;
    case MQTT_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
        break;

    case MQTT_EVENT_SUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_UNSUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_PUBLISHED:
        ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_DATA:
        ESP_LOGI(TAG, "MQTT_EVENT_DATA");
        printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
        printf("DATA=%.*s\r\n", event->data_len, event->data);
        printf("ID=%d, total_len=%d, data_len=%d, current_data_offset=%d\n", event->msg_id, event->total_data_len, event->data_len, event->current_data_offset);
        msg_id = esp_mqtt_client_publish(client,"controllo/feedback/prova", "culo", 4, 0 , 0);
	//ninux_mqtt_publish("controllo/feedback/prova", "culo");
        break;
    case MQTT_EVENT_ERROR:
        ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
        break;
    default:
        ESP_LOGI(TAG, "Other event id:%d", event->event_id);
        break;
    }
    return ESP_OK;
}


static void mqtt_app_start(void)
{
    mqtt_event_group = xEventGroupCreate();
    const esp_mqtt_client_config_t mqtt_cfg = {
	.uri = CONFIG_EXAMPLE_BROKER_TCP_URI,
        .event_handle = mqtt_event_handler,
        .cert_pem = (const char *)iot_eclipse_org_pem_start,
    };

    ESP_LOGI(TAG, "[APP] Free memory: %d bytes", esp_get_free_heap_size());
    mqtt_client = esp_mqtt_client_init(&mqtt_cfg);
}

static void get_string(char *line, size_t size)
{

    int count = 0;
    while (count < size) {
        int c = fgetc(stdin);
        if (c == '\n') {
            line[count] = '\0';
            break;
        } else if (c > 0 && c < 127) {
            line[count] = c;
            ++count;
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}


void app_main()
{
    char line[256];
    char pattern[32];
    char transport[32];
    int repeat = 0;

    ESP_LOGI(TAG, "[APP] Free memory: %d bytes", esp_get_free_heap_size());
    ESP_LOGI(TAG, "[APP] IDF version: %s", esp_get_idf_version());

    esp_log_level_set("*", ESP_LOG_INFO);
    esp_log_level_set("MQTT_CLIENT", ESP_LOG_VERBOSE);
    esp_log_level_set("TRANSPORT_TCP", ESP_LOG_VERBOSE);
    esp_log_level_set("TRANSPORT_SSL", ESP_LOG_VERBOSE);
    esp_log_level_set("TRANSPORT", ESP_LOG_VERBOSE);
    esp_log_level_set("OUTBOX", ESP_LOG_VERBOSE);

    ESP_ERROR_CHECK(nvs_flash_init());
    tcpip_adapter_init();
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    /* This helper function configures Wi-Fi or Ethernet, as selected in menuconfig.
     * Read "Establishing Wi-Fi or Ethernet Connection" section in
     * examples/protocols/README.md for more information about this function.
     */
    ESP_ERROR_CHECK(example_connect());

    mqtt_app_start();
        //esp_mqtt_client_set_uri(mqtt_client, CONFIG_EXAMPLE_BROKER_TCP_URI);
        //xEventGroupClearBits(mqtt_event_group, CONNECTED_BIT);
        esp_mqtt_client_start(mqtt_client);
        //ESP_LOGI(TAG, "Note free memory: %d bytes", esp_get_free_heap_size());
        //xEventGroupWaitBits(mqtt_event_group, CONNECTED_BIT, false, true, portMAX_DELAY);

        //nt msg_id = esp_mqtt_client_publish(mqtt_client, "controllo/culo", "inizio", 6, 0, 0);

    //vTaskDelay(20000 / portTICK_PERIOD_MS);
    //printf("passati i 20 sec\n");
    xEventGroupWaitBits(mqtt_event_group, CONNECTED_BIT, false, true, portMAX_DELAY);
    while (1) {

	////ninux_mqtt_publish("controllo/culo", "culoquadro");
        //esp_mqtt_client_stop(mqtt_client);
        ////esp_mqtt_client_set_uri(mqtt_client, CONFIG_EXAMPLE_BROKER_TCP_URI);
        //xEventGroupClearBits(mqtt_event_group, CONNECTED_BIT);
        //esp_mqtt_client_start(mqtt_client);
        //ESP_LOGI(TAG, "Note free memory: %d bytes", esp_get_free_heap_size());
        //xEventGroupWaitBits(mqtt_event_group, CONNECTED_BIT, false, true, portMAX_DELAY);
        
	int msg_id = esp_mqtt_client_publish(mqtt_client, "controllo/culo", "culoquadro", 10, 0, 0);
	vTaskDelay(10000 / portTICK_PERIOD_MS);
    }
}

