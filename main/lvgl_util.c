#include <stdio.h>
#include <stdbool.h>
#include "lvgl_util.h"

#include "encoder_util.h"

extern int enc_diff();
extern bool sw_press();

lv_group_t *group;

TaskHandle_t guiTask;

SemaphoreHandle_t lvgl_initialized;

static void lv_tick_task(void *arg) {
    (void) arg;

    lv_tick_inc(LV_TICK_PERIOD_MS);
}

static void my_encoder_read( lv_indev_drv_t * indev_driver, lv_indev_data_t * data )
{
    data->enc_diff = enc_diff();
    data->state = (sw_press()? LV_INDEV_STATE_PRESSED: LV_INDEV_STATE_RELEASED);
}
    

static void init_lvgl(void* parameter)
{
    lv_init();
    lvgl_driver_init();

    lv_color_t* buf1 = heap_caps_malloc(DISP_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_DMA);
    assert(buf1 != NULL);

    static lv_disp_draw_buf_t disp_buf;
    lv_disp_draw_buf_init(&disp_buf, buf1, NULL, DISP_BUF_SIZE);

    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.flush_cb = disp_driver_flush;
    disp_drv.rounder_cb = disp_driver_rounder;
    disp_drv.set_px_cb = disp_driver_set_px;
    disp_drv.hor_res = LV_HOR_RES_MAX;
    disp_drv.ver_res = LV_VER_RES_MAX;
    disp_drv.rotated = LV_DISP_ROT_NONE;
    disp_drv.antialiasing = true;
    disp_drv.screen_transp = false;
    disp_drv.draw_buf = &disp_buf;

    lv_disp_drv_register(&disp_drv);

    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_ENCODER;
    indev_drv.read_cb = my_encoder_read;
    lv_indev_t* indev_encoder = lv_indev_drv_register(&indev_drv);

    group = lv_group_create();
    lv_group_set_default(group);
    lv_indev_set_group(indev_encoder, group);

    const esp_timer_create_args_t periodic_timer_args = {
        .callback = &lv_tick_task,
        .name = "periodic_gui"
    };
    esp_timer_handle_t periodic_timer;
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, LV_TICK_PERIOD_MS * 1000));

    xSemaphoreGive(lvgl_initialized);

    while (true) {
        /* Delay 1 tick (assumes FreeRTOS tick is 10ms */
        vTaskDelay(pdMS_TO_TICKS(1));
        lv_timer_handler();
    }

    free(buf1);
    vTaskDelete(NULL);
}

void initialize_lvgl()
{
    lvgl_initialized = xSemaphoreCreateBinary();
    xTaskCreate(
        (TaskFunction_t)init_lvgl,
        "gui",
        1024 * 16,
        NULL,
        0,
        &guiTask
    );
    xSemaphoreTake(lvgl_initialized, portMAX_DELAY);
}