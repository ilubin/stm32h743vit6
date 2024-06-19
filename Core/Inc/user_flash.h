#ifndef __USER_FLASH_H
#define __USER_FLASH_H

#include "main.h"

#define FLASH_SR1           (1)
#define FLASH_SR2           (2)
#define FLASH_SR3           (3)

#define FLASH_QE_BIT        (0x02)

/*FLASHœ‡πÿøÿ÷∆√¸¡Ó*/
#define CMD_WREN            (0x06)      /* Write enable command */
#define CMD_WRDI            (0x04)      /* Write disable command */

#define CMD_WRSR1           (0x01)      /* Write Status/Configuration register1 command */
#define CMD_WRSR2           (0x31)      /* Write Status/Configuration register2 command */
#define CMD_WRSR3           (0x11)      /* Write Status/Configuration register3 command */

#define CMD_RDSR1           (0x05)      /* Read Status Register1 command */
#define CMD_RDSR2           (0x35)      /* Read Status Register2 command */
#define CMD_RDSR3           (0x15)      /* Read Status Register3 command */

#define CMD_READ	        (0x03)      /*Read Data Bytes (READ) */
#define CMD_FAST_READ	    (0x0B)      /*Read Data Bytes at Higher Speed (Fast Read) (0BH)*/
#define CMD_DUAL_FAST_READ  (0X3B)      /*Dual Output Fast Read (3BH)*/
#define CMD_QUAD_FAST_READ	(0x6B)	    /*Quad Output Fast Read (6BH)*/
#define CMD_DUAL_IO_READ	(0xBB)	    /*Dual I/O Fast Read (BBH)*/
#define CMD_QUAD_IO_READ	(0xEB)	    /*Quad I/O Fast Read (EBH)*/
#define CMD_BURST_WRAP		(0x77)	    /*Set Burst with Wrap (77H)*/

#define CMD_PP		        (0x02)	    /*Page Program (PP) (02H)*/
#define CMD_QUAD_PP	        (0x32)	    /*Quad Page Program (PP) (32H)*/
#define CMD_SE		        (0x20)	    /*Sector Erase (SE) (20H)*/
#define CMD_32KB_BE	        (0x52)	    /*32KB Block Erase (BE) (52H)*/
#define CMD_64KB_BE	        (0xD8)	    /*64KB Block Erase (BE) (D8H)*/
#define CMD_CE		        (0x60)	    /*Chip Erase (CE) (60/C7H)*/

#define CMD_REMS	        (0x90)	    /* Read Manufacture ID/ Device ID (REMS)  */
#define CMD_RDID	        (0x9F)	    /* Read Identification (RDID) (9FH)  */
#define CMD_RDUID	        (0x4B)	    /* Read Unique ID (4BH)  */

#define CMD_ESR		        (0x44)	    /* Erase Security Registers (44H)  */
#define CMD_PSR		        (0x42)	    /* Program Security Registers (42H)  */
#define CMD_RSR		        (0x48)	    /* Read Security Registers (48H)  */

#define CMD_RESET_EN	    (0X66)	    /*Enable Reset (66H) and Reset (99H)*/
#define CMD_RESET	        (0X99)

#define	CMD_PES		        (0x75)	    /*Program/Erase Suspend (PES) (75H)*/
#define CMD_PER		        (0x7A)	    /*Program/Erase Resume (PER) (7AH)*/
#define CMD_DP		        (0xB9)	    /*Deep Power-Down (DP) (B9H)*/
#define CMD_RDI		        (0xAB)	    /*Release from Deep Power-Down and Read Device ID (RDI) (ABH)*/

#define CMD_RSFDP	        (0x5A)	    /*Read Serial Flash Discoverable Parameter (5AH)*/

#define W25QXX_FLASH_BLOCK_SIZE	0x010000    //64KBytes
#define W25QXX_FLASH_SECTOR_SIZE	0x001000    //4KBytes
#define W25QXX_FLASH_PAGE_SIZE		0x000100    //256Bytes

#define W25QXX_FLASH_START_ADDRESS	0x000000

#define USE_W25Q64

#ifdef  USE_W25Q64
#define W25QXX_FLASH_END_ADDRESS	0x7FFFFF
#define W25QXX_FLASH_BLOCK_AMOUNT	128         //0~127
#define W25QXX_FLASH_SECTOR_AMOUNT	2048        //0~2047
#endif

#ifdef  USE_W25Q128
#define W25QXX_FLASH_END_ADDRESS	0xFFFFFF
#define W25QXX_FLASH_BLOCK_AMOUNT	256         //0~255
#define W25QXX_FLASH_SECTOR_AMOUNT	4096        //0~4095
#endif

#define FLASH_CS_High()             HAL_GPIO_WritePin(FLASH_CS_GPIO_Port, FLASH_CS_Pin, GPIO_PIN_SET)
#define FLASH_CS_Low()              HAL_GPIO_WritePin(FLASH_CS_GPIO_Port, FLASH_CS_Pin, GPIO_PIN_RESET)

void W25QXX_FLASH_Read_ID(uint8_t *data);
static void FLASH_Wait_Busy(void);
static void W25QXX_FLASH_Enable_Write(void);
static void W25QXX_FLASH_Disable_Write(void);
static void W25QXX_FLASH_Read_Status_Reg(uint8_t reg_channel, uint8_t *data);
static void W25QXX_FLASH_Write_Status_Reg(uint8_t reg_channel, uint8_t *data);
void W25QXX_FLASH_Enable_QSPI(void);
void W25QXX_FLASH_Erase_Sector(uint32_t sector_num);
void W25QXX_FLASH_Erase_Block(uint8_t block_num);
void W25QXX_FLASH_Erase_Chip(void);
void W25QXX_FLASH_Read_Data(uint8_t *data, uint32_t address, uint32_t length);
void W25QXX_FLASH_Write_Data(uint8_t *data, uint32_t address, uint32_t length);

#endif