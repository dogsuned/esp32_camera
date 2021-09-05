#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include <pthread.h>

#define LED_GPIO    GPIO_NUM_33

void led_handle(void)
{
    int status = 0;

    gpio_reset_pin(LED_GPIO);
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);
    while (1) {
        gpio_set_level(LED_GPIO, status);
        status ^= 1;
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

int app_led_init(void)
{
    int ret;
    pthread_t tid;
    pthread_attr_t attr = {.stacksize = 1024 * 4};

    ret = pthread_create(&tid, &attr, led_handle, NULL);
    if (ret) {
        printf("led thread create failed\n");
        return -1;
    }

    pthread_join(tid, NULL);
    printf("led task start\n");

    return 0;
}
