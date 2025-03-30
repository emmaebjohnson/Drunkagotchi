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

void battle_ui(lv_display_t *disp, int type) {
    init_wifi();
    esp_now_init();

    lv_obj_t *scr = lv_display_get_screen_active(disp);
    lv_obj_clean(scr);

    message_text = lv_label_create(scr);
    lv_label_set_text(message_text, type == 0 ? "Sending..." : "Waiting for message...");
    lv_obj_align(message_text, LV_ALIGN_CENTER, 0, 0);

    if (type == 0) {
        init_esp_now_sender();
        lv_timer_create(send_message, 2000, NULL);  // Corrected function pointer
    } else {
        init_esp_now_receiver();
    }
}
