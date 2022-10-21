#ifndef __SPI_H
#define __SPI_H

#include <stdint.h>
#include "board.h"

//#define SPI_DMA
#define	_SPI    SPI1

#define CMD_READ_STATUS_REG1				0x05
#define CMD_READ_STATUS_REG2				0x35

void SpiInit();
void SpiDeinit();
void SpiSendRecv(uint8_t *buf_tx, uint8_t *buf_rx, uint16_t len);
void SpiBreak();
void SpiSetPrescaler(uint32_t value);
uint8_t SpiIsReady();

//void Dma_tx_IrqHandler(void);
//void Dma_rx_IrqHandler(void);
void Spi_IrqHandler(void);

#endif
