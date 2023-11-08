#ifndef __HC545_H
#define __HC545_H

#include "pico/stdlib.h"
#include "hardware/spi.h"

class hc545
{
private:
  spi_inst_t *SPI_INSTANCE{NULL};
  uint LATCH_PIN{NULL};
  uint DATA_PIN{NULL};
  uint CLK_PIN{NULL};
  uint BAUD_RATE{NULL};
public:
  /**
   * Constructor for an already initialized SPI instance
  */
  hc545(uint LATCH_PIN, spi_inst_t *SPI_INSTANCE = spi0);

  /**
   * Constructor that will initialize the SPI instance
   * Default SPI_INSTANCE is spi0
   * Default BAUD_RATE is 48000
  */
  hc545(uint DATA_PIN, uint CLK_PIN, uint LATCH_PIN, spi_inst_t *SPI_INSTANCE = spi0, uint BAUD_RATE = 48000);

  ~hc545();
  /**
   * Shifts data into hc545 register and
   * latch it to the outputs
   * @param buffer data to be shifted
   * @param size length of buffer
   * @returns number of bytes written
  */
  int shift_out(uint8_t *buffer, size_t size);
};

#endif
