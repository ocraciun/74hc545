#include "hc545.h"

// Convert bcd value to decimal value
static inline uint8_t bcd_decimal(uint8_t val)
{
    return ((val & 0xF0) >> 4) * 10 + (val & 0x0F);
}

// Convert decimal value to bcd value
static inline uint8_t decimal_bcd(uint8_t val)
{
  return (val / 10 << 4) | (val % 10);
}

hc545::hc545(uint LATCH_PIN, spi_inst_t *SPI_INSTANCE)
  : SPI_INSTANCE {SPI_INSTANCE}
  , LATCH_PIN {LATCH_PIN}
{

}

hc545::hc545(uint DATA_PIN, uint CLK_PIN, uint LATCH_PIN, spi_inst_t *SPI_INSTANCE, uint BAUD_RATE)
  : DATA_PIN {DATA_PIN}
  , CLK_PIN {CLK_PIN}
  , LATCH_PIN {LATCH_PIN}
  , BAUD_RATE {BAUD_RATE}
  , SPI_INSTANCE {SPI_INSTANCE}
{
  spi_init(SPI_INSTANCE, BAUD_RATE);
  gpio_set_function(DATA_PIN, GPIO_FUNC_SPI);
  gpio_set_function(CLK_PIN, GPIO_FUNC_SPI);
  gpio_init(LATCH_PIN);
  gpio_set_dir(LATCH_PIN, GPIO_OUT);
  gpio_put(LATCH_PIN, 0);
}

hc545::~hc545()
{

}

int hc545::shift_out(uint8_t *buffer, size_t size)
{
  // Set latch pin low to begin shift operation
  gpio_put(LATCH_PIN, 0);
  // Send the data to the shift register
  int len = spi_write_blocking(SPI_INSTANCE, buffer, size);
  // Set latch pin high to store the data in the shift register
  gpio_put(LATCH_PIN, 1);

  return len;
}
