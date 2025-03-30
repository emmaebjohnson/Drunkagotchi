#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <esp_now.h>
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "lvgl.h"
#include "drunkagotchi.h"

static const char *BATTLE_TAG = "ESP_NOW_BATTLE";

typedef struct Message {
    char text[32];
} Message;

Message message;
lv_obj_t *message_text;  // Global LVGL label
esp_now_peer_info_t peerInfo = {};
lv_obj_t *scr = NULL;



// Callback for when data is sent
void onSent(const uint8_t *macAddr, esp_now_send_status_t status) {
    ESP_LOGI(BATTLE_TAG, "Delivery Status: %s", status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");

    if (message_text) {
        lv_label_set_text(message_text, status == ESP_NOW_SEND_SUCCESS ? "Sent!" : "Send Failed");
    }
}

// Callback for when data is received
void onReceive(const esp_now_recv_info_t *recv_info, const uint8_t *incomingData, int len) {
    memcpy(&message, incomingData, sizeof(message));
    ESP_LOGI(BATTLE_TAG, "Received from MAC: %02X:%02X:%02X:%02X:%02X:%02X | Message: %s",
             recv_info->src_addr[0], recv_info->src_addr[1], recv_info->src_addr[2],
             recv_info->src_addr[3], recv_info->src_addr[4], recv_info->src_addr[5],
             message.text);

    if (message_text) {
        lv_label_set_text(message_text, message.text);
    }
}

void init_esp_now_sender() {
    esp_now_register_send_cb(onSent);

    memset(&peerInfo, 0, sizeof(peerInfo));
    memset(peerInfo.peer_addr, 0xFF, 6);  // Broadcast MAC
    peerInfo.channel = 0;
    peerInfo.encrypt = false;
    peerInfo.ifidx = ESP_IF_WIFI_STA;

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        ESP_LOGE(BATTLE_TAG, "Failed to add peer");
    }
}

void init_esp_now_receiver() {
    esp_now_register_recv_cb(onReceive);
}

void init_wifi() {
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());
}

void send_message(lv_timer_t *timer) {
    strcpy(message.text, "Hello from Sender!");
    esp_err_t result = esp_now_send(peerInfo.peer_addr, (uint8_t *)&message, sizeof(message));

    if (message_text) {
        lv_label_set_text(message_text, result == ESP_OK ? "Sending..." : "Send Failed");
    }
}

void wifi_handler(lv_event_t * e) 
{
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_CLICKED) {
        // Get the action selected (from the event data)
        uint32_t action = (uint32_t)lv_event_get_user_data(e);
        LV_LOG_USER("Clicked action: %u", action);

        // Handle actions based on the button clicked
        switch (action) {
            case 0:

                lv_obj_clean(scr);
                message_text = lv_label_create(scr);
                lv_label_set_text(message_text, "Sending...");
                lv_obj_align(message_text, LV_ALIGN_CENTER, 0, 0);
            
                init_esp_now_sender();
                lv_timer_create(send_message, 2000, NULL);  // Corrected function pointer

                break;
            case 1:

                lv_obj_clean(scr);
                message_text = lv_label_create(scr);
                lv_label_set_text(message_text, "Waiting for message...");
                lv_obj_align(message_text, LV_ALIGN_CENTER, 0, 0);
        
                init_esp_now_receiver();

                break;
            default:
                break;
        }
    }
}

void draw_ui(lv_obj_t * parent) {
    // Attack Button
    lv_obj_t * attack_btn = lv_btn_create(parent);
    lv_obj_set_size(attack_btn, 60, 30);
    lv_obj_align(attack_btn, LV_ALIGN_CENTER, -40, 0);
    lv_obj_t * attack_label = lv_label_create(attack_btn);
    lv_label_set_text(attack_label, "ATTACK!");
    lv_obj_center(attack_label);
    
    // Defend Button
    lv_obj_t * defend_btn = lv_btn_create(parent);
    lv_obj_set_size(defend_btn, 60, 30);
    lv_obj_align(defend_btn, LV_ALIGN_CENTER, 40, 0);
    lv_obj_t * defend_label = lv_label_create(defend_btn);
    lv_label_set_text(defend_label, "DEFEND!");
    lv_obj_center(defend_label);
    
    lv_obj_add_event_cb(attack_btn, wifi_handler, LV_EVENT_CLICKED, (void*)0);  
    lv_obj_add_event_cb(defend_btn, wifi_handler, LV_EVENT_CLICKED, (void*)1);
}


void battle_ui(lv_display_t * disp) {
    init_wifi();
    esp_now_init();

    scr = lv_display_get_screen_active(disp);
    lv_obj_clean(scr);

    draw_ui(scr);
}
