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

<<<<<<< Updated upstream

void app_main()
{
    printf("Hello world!\n");

    /* Print chip information */
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    printf("This is ESP32 chip with %d CPU cores, WiFi%s%s, ",
            chip_info.cores,
            (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
            (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

    printf("silicon revision %d, ", chip_info.revision);

    printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    for (int i = 10; i >= 0; i--) {
        printf("Restarting in %d seconds...\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    printf("Restarting now.\n");
    fflush(stdout);
    esp_restart();
=======
#include "components/component-funsparkRE/funsparkRE.h"
#include "components/component-lcd/driver/include/lcd_driver.h"
#include "components/component-lcd/listview/include/listview.h"
#include "components/component-lcd/esp32-i2c-lcd1602/include/i2c-lcd1602.h"

static const char *TAG = "I2C_RE";
RE_t re;
void app_main()
{
    re.i2c_address = RE_i2c_addr;
    re.sda_pin = 18;
    re.scl_pin = 23;

    char *menuItems[7];
    menuItems[0] = "Music";
    menuItems[1] = "Recorder";
    menuItems[2] = "Equalizer";
    menuItems[3] = "Radio";
    menuItems[4] = "Timer";
    menuItems[5] = "Settings";
    menuItems[6] = "Files";
    menuItems[7] = "Credits";

    int menuItemsSize = sizeof(menuItems)/sizeof(menuItems[0]);

	ESP_ERROR_CHECK(RE_initialize(&re));
    xTaskCreate(Task_RE_Check_Diff,"task",5000,NULL,10,NULL);
    while (1)
    {
        ESP_LOGV(TAG,"%d",data);
        vTaskDelay(100 / portTICK_RATE_MS);
    }

    xTaskCreate(&setup_lcd, "setup_lcd", 4096, NULL, 5, NULL);
    init_menu_list(menuItems,lcd_info);

    //scroll_up(menuItems,lcd_info);
    
>>>>>>> Stashed changes
}
