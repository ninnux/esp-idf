/* Simple HTTP + SSL Server Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <esp_wifi.h>
#include <esp_event_loop.h>
#include <esp_log.h>
#include <esp_system.h>
#include <nvs_flash.h>
#include <sys/param.h>

#include <esp_https_server.h>

#include "wpa2/utils/base64.h"
#include "esp32_web_basic_auth.h"

/* A simple example that demonstrates how to create GET and POST
 * handlers for the web server.
 * The examples use simple WiFi configuration that you can set via
 * 'make menuconfig'.
 * If you'd rather not, just change the below entries to strings
 * with the config you want -
 * ie. #define EXAMPLE_WIFI_SSID "mywifissid"
*/
#define EXAMPLE_WIFI_SSID CONFIG_WIFI_SSID
#define EXAMPLE_WIFI_PASS CONFIG_WIFI_PASSWORD


//#define WWW_USER "admin" 
//#define WWW_PASS "pirulipiruli" 
//#define WWW_USER_PASS_BASE64 "bmlubzpwaXBwb3BpcHBv" 

static const char *TAG="APP";
//unsigned char *userpass;
//char *check;


//int mybasic_auth(httpd_req_t *req){
//
//    char*  buf;
//    size_t buf_len;
//    buf_len = httpd_req_get_hdr_value_len(req, "Authorization") + 1;
//    if (buf_len > 1) {
//        buf = malloc(buf_len);
//        if (httpd_req_get_hdr_value_str(req, "Authorization", buf, buf_len) == ESP_OK) {
//	    check=malloc(sizeof(WWW_USER_PASS_BASE64)+6);
//            sprintf(check,"Basic %s",WWW_USER_PASS_BASE64); 
// 	    if(!strncmp(buf,check,strlen(check))){
// 	    //if(!strcmp(buf,"Basic bmlubzpwaXBwb3BpcHBv")){
//                ESP_LOGI(TAG, "%s", "OK");
//    	    	httpd_resp_set_status(req, "200 Ok");
//		return 0;
//	    }else{
//                ESP_LOGI(TAG, "%s", "NO");
//       		httpd_resp_set_status(req, "403 Forbidden");
//	    }	
//        }
//        free(buf);
//        free(check);
//    }else{
//       httpd_resp_set_hdr(req, "WWW-Authenticate", "Basic realm=pippo");
//       ESP_LOGI(TAG, "WWW-Authoicate:%s","culo");
//       httpd_resp_set_status(req, "401 Unauthorized");
//       ESP_LOGI(TAG, "401:%s","culo");
//    }
//    return 1;
//}
//
//
//
//
//int mybasic_auth2(httpd_req_t *req){
//
//    char*  buf;
//    size_t buf_len;
//    size_t base64len;
//    buf_len = httpd_req_get_hdr_value_len(req, "Authorization") + 1;
//    if (buf_len > 1) {
//        buf = malloc(buf_len);
//        if (httpd_req_get_hdr_value_str(req, "Authorization", buf, buf_len) == ESP_OK) {
//            ESP_LOGI(TAG, "%d", strlen(WWW_USER));
//            ESP_LOGI(TAG, "Found header => Authorization: %s", buf);
//	    userpass=malloc(strlen(WWW_USER)+strlen(WWW_PASS)+1);
//	    check=malloc(strlen(WWW_USER)+strlen(WWW_PASS)+7);
//	    sprintf((char*) userpass,"%s:%s",WWW_USER,WWW_PASS);
//            sprintf(check,"Basic %s",base64_encode(userpass,strlen(WWW_USER)+strlen(WWW_PASS)+1,&base64len)); 
//            ESP_LOGI(TAG, "buf: ---%s---", buf);
//            ESP_LOGI(TAG, "check: ---%s---", check);
//            ESP_LOGI(TAG, "check len: ---%d---", base64len);
// 	    if(!strncmp(buf,check,base64len+5)){
// 	    //if(!strcmp(buf,"Basic bmlubzpwaXBwb3BpcHBv")){
//                ESP_LOGI(TAG, "%s", "OK");
//    	    	httpd_resp_set_status(req, "200 Ok");
//		return 0;
//	    }else{
//                ESP_LOGI(TAG, "%s", "NO");
//       		httpd_resp_set_status(req, "403 Forbidden");
//	    }	
//        }
//        free(buf);
//        free(userpass);
//        free(check);
//    }else{
//       httpd_resp_set_hdr(req, "WWW-Authenticate", "Basic realm=pippo");
//       ESP_LOGI(TAG, "WWW-Authoicate:%s","culo");
//       httpd_resp_set_status(req, "401 Unauthorized");
//       ESP_LOGI(TAG, "401:%s","culo");
//    }
//    return 1;
//}

/* An HTTP GET handler */
esp_err_t root_get_handler(httpd_req_t *req)
{
    if(!esp32_web_basic_auth(req)){
    httpd_resp_set_type(req, "text/html");
    httpd_resp_send(req, "<h1>Hello Secure World!</h1>", -1); // -1 = use strlen()
    }else{
    httpd_resp_set_type(req, "text/html");
    httpd_resp_send(req, "<h1>Ciaone!</h1>", -1); // -1 = use strlen()

    }

    return ESP_OK;
}

const httpd_uri_t root = {
    .uri       = "/",
    .method    = HTTP_GET,
    .handler   = root_get_handler
};

/* An HTTP GET handler */
esp_err_t port0_ON_get_handler(httpd_req_t *req)
{
    httpd_resp_set_type(req, "text/html");
    httpd_resp_send(req, "<h1>port0 ON</h1>", -1); // -1 = use strlen()

    return ESP_OK;
}

const httpd_uri_t port0_ON = {
    .uri       = "/0/ON",
    .method    = HTTP_GET,
    .handler   = port0_ON_get_handler
};

httpd_handle_t start_webserver(void)
{
    httpd_handle_t server = NULL;

    // Start the httpd server
    ESP_LOGI(TAG, "Starting server");

    httpd_ssl_config_t conf = HTTPD_SSL_CONFIG_DEFAULT();

    extern const unsigned char cacert_pem_start[] asm("_binary_cacert_pem_start");
    extern const unsigned char cacert_pem_end[]   asm("_binary_cacert_pem_end");
    conf.cacert_pem = cacert_pem_start;
    conf.cacert_len = cacert_pem_end - cacert_pem_start;

    extern const unsigned char prvtkey_pem_start[] asm("_binary_prvtkey_pem_start");
    extern const unsigned char prvtkey_pem_end[]   asm("_binary_prvtkey_pem_end");
    conf.prvtkey_pem = prvtkey_pem_start;
    conf.prvtkey_len = prvtkey_pem_end - prvtkey_pem_start;

    esp_err_t ret = httpd_ssl_start(&server, &conf);
    if (ESP_OK != ret) {
        ESP_LOGI(TAG, "Error starting server!");
        return NULL;
    }

    // Set URI handlers
    ESP_LOGI(TAG, "Registering URI handlers");
    httpd_register_uri_handler(server, &root);
    httpd_register_uri_handler(server, &port0_ON);
    return server;
}

void stop_webserver(httpd_handle_t server)
{
    // Stop the httpd server
    httpd_ssl_stop(server);
}




// ------------------------- application boilerplate ------------------------

static esp_err_t event_handler(void *ctx, system_event_t *event)
{
    httpd_handle_t *server = (httpd_handle_t *) ctx;

    switch(event->event_id) {
    case SYSTEM_EVENT_STA_START:
        ESP_LOGI(TAG, "SYSTEM_EVENT_STA_START");
        ESP_ERROR_CHECK(esp_wifi_connect());
        break;
    case SYSTEM_EVENT_STA_GOT_IP:
        ESP_LOGI(TAG, "SYSTEM_EVENT_STA_GOT_IP");
        ESP_LOGI(TAG, "Got IP: '%s'",
                ip4addr_ntoa(&event->event_info.got_ip.ip_info.ip));

        /* Start the web server */
        if (*server == NULL) {
            *server = start_webserver();
        }
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        ESP_LOGI(TAG, "SYSTEM_EVENT_STA_DISCONNECTED");
        ESP_ERROR_CHECK(esp_wifi_connect());

        /* Stop the web server */
        if (*server) {
            stop_webserver(*server);
            *server = NULL;
        }
        break;
    default:
        break;
    }
    return ESP_OK;
}

static void initialise_wifi(void *arg)
{
    tcpip_adapter_init();
    ESP_ERROR_CHECK(esp_event_loop_init(event_handler, arg));
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
    wifi_config_t wifi_config = {
        .sta = {
            .ssid = EXAMPLE_WIFI_SSID,
            .password = EXAMPLE_WIFI_PASS,
        },
    };
    ESP_LOGI(TAG, "Setting WiFi configuration SSID %s...", wifi_config.sta.ssid);
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());
}

void app_main()
{
    static httpd_handle_t server = NULL;
    ESP_ERROR_CHECK(nvs_flash_init());
    initialise_wifi(&server);
}
