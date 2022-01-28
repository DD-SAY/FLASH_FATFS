#ifndef __FLASH_H
#define __FLASH_H
#include "spi.h"
#include "stm32f4xx.h"

#define	W25Q64_CHIP_SELECT_PORT	GPIOA
#define	W25Q64_CHIP_SELECT_PIN	GPIO_PIN_15

#define ManufactDeviceID_CMD    0x90
#define READ_STATU_REGISTER_1   0x05
#define READ_STATU_REGISTER_2   0x35
#define READ_DATA_CMD            0x03
#define WRITE_ENABLE_CMD        0x06
#define WRITE_DISABLE_CMD        0x04
#define SECTOR_ERASE_CMD        0x20
#define CHIP_ERASE_CMD            0xc7
#define PAGE_PROGRAM_CMD        0x02

uint16_t W25QXX_ReadID(void);
int W25QXX_Read(uint8_t* buffer, uint32_t start_addr, uint16_t nbytes);
void W25QXX_Write_Enable(void);
void W25QXX_Write_Disable(void);
void W25QXX_Erase_Sector(uint32_t sector_addr);
void W25QXX_Page_Program(uint8_t* dat, uint32_t WriteAddr, uint16_t nbytes);
void vW25qx_writeSector(uint8_t *p,uint32_t addr,uint16_t num);
#endif
