#include "temperature.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/spi_master.h"
#include "esp_log.h"

#include "sdkconfig.h"

#define TAG "temperature"

/* spi definitions */
#define PIN_NUM_MOSI 	CONFIG_PIN_NUM_MOSI
#define PIN_NUM_MISO 	CONFIG_PIN_NUM_MISO
#define PIN_NUM_CLK  	CONFIG_PIN_NUM_CLK
#define PIN_NUM_CS   	CONFIG_PIN_NUM_CS
#define SPI_DEVICE		VSPI_HOST

#define DMA_CHAN    2

float temperature = 0.0f;

void temp_task(void * pvParams) {
  spi_device_handle_t spi = (spi_device_handle_t) pvParams;

  uint16_t data;
  spi_transaction_t tM = {
    .tx_buffer = NULL,
    .rx_buffer = &data,
    .length = 16,
    .rxlength = 16,
  };

  for (;;) {
    spi_device_acquire_bus(spi, portMAX_DELAY);
    spi_device_transmit(spi, &tM);
    spi_device_release_bus(spi);

    int16_t res = (int16_t) SPI_SWAP_DATA_RX(data, 16);


    if (res & (1 << 2))
      ESP_LOGE(TAG, "Sensor is not connected\n");
    else {
      res >>= 3;
      temperature = res * 0.25;
      printf("SPI res = %d temp=%f\n", res, temperature);
    }

    vTaskDelay(pdMS_TO_TICKS(1000));
  }

}

/* SPI Config */
spi_device_handle_t spi_init(void) {
  spi_device_handle_t spi;
  esp_err_t ret;
  spi_bus_config_t buscfg = {
    .miso_io_num = PIN_NUM_MISO,
    .sclk_io_num = PIN_NUM_CLK,
    .quadwp_io_num = -1,
    .quadhd_io_num = -1,
    .max_transfer_sz = 1
  };

  //Initialize the SPI bus
  ret = spi_bus_initialize(VSPI_HOST, &buscfg, DMA_CHAN);
  ESP_ERROR_CHECK(ret);

  spi_device_interface_config_t devCfg={
    .mode = 0,
    .clock_speed_hz = 5*1000*100,
    .spics_io_num=5,
    .queue_size=7
  };

  ret = spi_bus_add_device(VSPI_HOST, &devCfg, &spi);
  ESP_ERROR_CHECK(ret);

  return spi;
}

void initialize_temperature(void)
{
    spi_device_handle_t spi;
    spi = spi_init();
    xTaskCreate(
        (TaskFunction_t)temp_task,
        "temp_task",
        1024 * 4,
        spi,
        5,
        NULL
    );
}
