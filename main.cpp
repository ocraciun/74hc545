#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"

#include "hc545.h"

#define CLOCK_PIN 2 // GP2
#define DATA_PIN 3 // GP3
#define LATCH_PIN 6 // GP6

#define SPI_INSTANCE spi0
#define BAUND_RATE 48000

int main()
{
  stdio_init_all();

  hc545 shiftRegister{DATA_PIN, CLOCK_PIN, LATCH_PIN, SPI_INSTANCE, BAUND_RATE};

  sleep_ms(250);
  uint8_t *buffer = new uint8_t[1] {0x01};
  int dir = 1;
  while(1)
  {
    if (buffer[0] == 0x00 || buffer[0] == 0xFF) {
      dir = !dir;
    }

    if (dir) {
      buffer[0] = buffer[0] << 1 | 0x01;
    }

    if (!dir) {
      buffer[0] = buffer[0] << 1;
    }

    shiftRegister.shift_out(buffer, 1);
    sleep_ms(250);
  }
}
