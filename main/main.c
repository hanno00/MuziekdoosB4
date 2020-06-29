#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_log.h"
#include "esp_wifi.h"
#include "nvs_flash.h"
#include "sdkconfig.h"
#include "board.h"

#include "radio.h"

 static const char *TAG = "MAIN";

// Example on how to use radio
void app_main(void)
{
    // standard bootup
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    tcpip_adapter_init();
    esp_log_level_set("*", ESP_LOG_INFO);
    esp_log_level_set(TAG, ESP_LOG_DEBUG);
    //start radio
    radio_init();
    radio_start();
    int time = 0;
    while (1)
    {
        ESP_LOGW(TAG, "[XX] PROGRAM IS RUNNING FOR: %d MIN!", time);
        vTaskDelay(15000 / portTICK_RATE_MS);
        time = time + 1;
        if(time == 1){
            radio_switch_station("https://20873.live.streamtheworld.com/TLPSTR09.mp3");
        }
    }
    radio_stop();
    radio_deinit();
    while (1)
    {
    }
}
