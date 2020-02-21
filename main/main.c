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
#include "esp_log.h"

#include "components/component-funsparkRE/funsparkRE.h"
#include "components/component-menu/menu.h"

RE_t re;
void app_main()
{
    menuMain();

    re.i2c_address = RE_i2c_addr;
    re.sda_pin = 18;
    re.scl_pin = 23;

	ESP_ERROR_CHECK(RE_initialize(&re));
    xTaskCreate(Task_RE_Check_Diff,"task",5000,NULL,10,NULL);
    while (1)
    {
        vTaskDelay(100 / portTICK_RATE_MS);
    }
    
}
