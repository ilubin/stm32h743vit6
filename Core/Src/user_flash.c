#include "user_flash.h"
#include "user_spi.h"
#include "user_tim.h"

#define USE_SPI

#ifdef USE_QSPI
extern QSPI_HandleTypeDef hqspi;

void W25QXX_FLASH_Read_ID(uint8_t *data){
  
  	QSPI_CommandTypeDef qspi_cmd;
	
    qspi_cmd.Instruction 		 	= CMD_RDID;
    qspi_cmd.InstructionMode    	= QSPI_INSTRUCTION_1_LINE;
    
    qspi_cmd.Address            	= 0x000000;
    qspi_cmd.AddressSize        	= QSPI_ADDRESS_24_BITS;
    qspi_cmd.AddressMode        	= QSPI_ADDRESS_NONE;
    
    qspi_cmd.AlternateBytes 	 	= 0x00;
    qspi_cmd.AlternateBytesSize 	= QSPI_ALTERNATE_BYTES_8_BITS;
    qspi_cmd.AlternateByteMode 	    = QSPI_ALTERNATE_BYTES_NONE;
    
    qspi_cmd.DummyCycles        	= 0;
    
	qspi_cmd.DataMode 			 	= QSPI_DATA_1_LINE;
	qspi_cmd.NbData             	= 3;
    
	qspi_cmd.DdrMode        	    = QSPI_DDR_MODE_DISABLE;
	qspi_cmd.DdrHoldHalfCycle       = QSPI_DDR_HHC_ANALOG_DELAY;
	qspi_cmd.SIOOMode           	= QSPI_SIOO_INST_EVERY_CMD;
	
	if (HAL_QSPI_Command(&hqspi, &qspi_cmd, HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
      Error_Handler();
	}
    if (HAL_QSPI_Receive(&hqspi, data, HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
      Error_Handler();
	}
}

static void W25QXX_FLASH_Wait_Busy(void){
  uint8_t temp[1] = {0};
  do{
    W25QXX_FLASH_Read_Status_Reg(FLASH_SR1, temp);
  }while((temp[0] & 0x01) != 0x00);
}

static void W25QXX_FLASH_Enable_Write(void){
    
  	QSPI_CommandTypeDef qspi_cmd;
	
    qspi_cmd.Instruction 		 	= CMD_WREN;
    qspi_cmd.InstructionMode    	= QSPI_INSTRUCTION_1_LINE;
    
    qspi_cmd.Address            	= 0x000000;
    qspi_cmd.AddressSize        	= QSPI_ADDRESS_24_BITS;
    qspi_cmd.AddressMode        	= QSPI_ADDRESS_NONE;
    
    qspi_cmd.AlternateBytes 	 	= 0x00;
    qspi_cmd.AlternateBytesSize 	= QSPI_ALTERNATE_BYTES_8_BITS;
    qspi_cmd.AlternateByteMode 	    = QSPI_ALTERNATE_BYTES_NONE;
    
    qspi_cmd.DummyCycles        	= 0;
    
	qspi_cmd.DataMode 			 	= QSPI_DATA_NONE;
	qspi_cmd.NbData             	= 0;
    
	qspi_cmd.DdrMode        	    = QSPI_DDR_MODE_DISABLE;
	qspi_cmd.DdrHoldHalfCycle       = QSPI_DDR_HHC_ANALOG_DELAY;
	qspi_cmd.SIOOMode           	= QSPI_SIOO_INST_EVERY_CMD;
	
	if (HAL_QSPI_Command(&hqspi, &qspi_cmd, HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
      Error_Handler();
	}
}

//static void W25QXX_FLASH_Disable_Write(void){
//    
//  	QSPI_CommandTypeDef qspi_cmd;
//	
//    qspi_cmd.Instruction 		 	= CMD_WRDI;
//    qspi_cmd.InstructionMode    	= QSPI_INSTRUCTION_1_LINE;
//    
//    qspi_cmd.Address            	= 0x000000;
//    qspi_cmd.AddressSize        	= QSPI_ADDRESS_24_BITS;
//    qspi_cmd.AddressMode        	= QSPI_ADDRESS_NONE;
//    
//    qspi_cmd.AlternateBytes 	 	= 0x00;
//    qspi_cmd.AlternateBytesSize 	= QSPI_ALTERNATE_BYTES_8_BITS;
//    qspi_cmd.AlternateByteMode 	    = QSPI_ALTERNATE_BYTES_NONE;
//    
//    qspi_cmd.DummyCycles        	= 0;
//    
//	qspi_cmd.DataMode 			 	= QSPI_DATA_NONE;
//	qspi_cmd.NbData             	= 0;
//    
//	qspi_cmd.DdrMode        	    = QSPI_DDR_MODE_DISABLE;
//	qspi_cmd.DdrHoldHalfCycle       = QSPI_DDR_HHC_ANALOG_DELAY;
//	qspi_cmd.SIOOMode           	= QSPI_SIOO_INST_EVERY_CMD;
//	
//	if (HAL_QSPI_Command(&hqspi, &qspi_cmd, HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
//	{
//      Error_Handler();
//	}
//}

static void W25QXX_FLASH_Read_Status_Reg(uint8_t reg_channel, uint8_t *data){
  
  QSPI_CommandTypeDef qspi_cmd;
  
  switch(reg_channel){
  case FLASH_SR1:
    qspi_cmd.Instruction 		 	= CMD_RDSR1;
    break;
  case FLASH_SR2:
    qspi_cmd.Instruction 		 	= CMD_RDSR2;
    break;
  case FLASH_SR3:
    qspi_cmd.Instruction 		 	= CMD_RDSR3;
    break;
  default:
    Error_Handler();
    break;
  }
  qspi_cmd.InstructionMode    	= QSPI_INSTRUCTION_1_LINE;
  
  qspi_cmd.Address            	= 0x000000;
  qspi_cmd.AddressSize        	= QSPI_ADDRESS_24_BITS;
  qspi_cmd.AddressMode        	= QSPI_ADDRESS_NONE;
  
  qspi_cmd.AlternateBytes 	 	= 0x00;
  qspi_cmd.AlternateBytesSize 	= QSPI_ALTERNATE_BYTES_8_BITS;
  qspi_cmd.AlternateByteMode 	= QSPI_ALTERNATE_BYTES_NONE;
  
  qspi_cmd.DummyCycles        	= 0;
  
  qspi_cmd.DataMode 			= QSPI_DATA_1_LINE;
  qspi_cmd.NbData             	= 1;
  
  qspi_cmd.DdrMode        	    = QSPI_DDR_MODE_DISABLE;
  qspi_cmd.DdrHoldHalfCycle     = QSPI_DDR_HHC_ANALOG_DELAY;
  qspi_cmd.SIOOMode           	= QSPI_SIOO_INST_EVERY_CMD;
  
  if (HAL_QSPI_Command(&hqspi, &qspi_cmd, HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_QSPI_Receive(&hqspi, data, HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    Error_Handler();
  }
}

static void W25QXX_FLASH_Write_Status_Reg(uint8_t reg_channel, uint8_t *data){
  
  QSPI_CommandTypeDef qspi_cmd;
   
  switch(reg_channel){
  case FLASH_SR1:
    qspi_cmd.Instruction 		 	= CMD_WRSR1;
    break;
  case FLASH_SR2:
    qspi_cmd.Instruction 		 	= CMD_WRSR2;
    break;
  case FLASH_SR3:
    qspi_cmd.Instruction 		 	= CMD_WRSR3;
    break;
  default:
    Error_Handler();
    break;
  }
  qspi_cmd.InstructionMode    	= QSPI_INSTRUCTION_1_LINE;
  
  qspi_cmd.Address            	= 0x000000;
  qspi_cmd.AddressSize        	= QSPI_ADDRESS_24_BITS;
  qspi_cmd.AddressMode        	= QSPI_ADDRESS_NONE;
  
  qspi_cmd.AlternateBytes 	 	= 0x00;
  qspi_cmd.AlternateBytesSize 	= QSPI_ALTERNATE_BYTES_8_BITS;
  qspi_cmd.AlternateByteMode 	= QSPI_ALTERNATE_BYTES_NONE;
  
  qspi_cmd.DummyCycles        	= 0;
  
  qspi_cmd.DataMode 			= QSPI_DATA_1_LINE;
  qspi_cmd.NbData             	= 1;
  
  qspi_cmd.DdrMode        	    = QSPI_DDR_MODE_DISABLE;
  qspi_cmd.DdrHoldHalfCycle     = QSPI_DDR_HHC_ANALOG_DELAY;
  qspi_cmd.SIOOMode           	= QSPI_SIOO_INST_EVERY_CMD;
  
  W25QXX_FLASH_Enable_Write();
  if (HAL_QSPI_Command(&hqspi, &qspi_cmd, HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_QSPI_Transmit(&hqspi, data, HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    Error_Handler();
  }
  W25QXX_FLASH_Wait_Busy();
}

void W25QXX_FLASH_Enable_QSPI(void){
  uint8_t temp[2] = {0}, write_count = 0;
  W25QXX_FLASH_Read_Status_Reg(FLASH_SR2, temp);
  if((temp[0] & FLASH_QE_BIT) == 0x02){
    //Do Nothing
  }
  else{
    temp[1] = temp[0] | FLASH_QE_BIT;
    //����QE
    do{
      W25QXX_FLASH_Write_Status_Reg(FLASH_SR2, temp + 1);
      W25QXX_FLASH_Read_Status_Reg(FLASH_SR2, temp);
      write_count++;
      if(write_count >= 3){
        Error_Handler();
        break;
      }
    }while(((temp[0] & FLASH_QE_BIT) != 0x02));
  }
}

void W25QXX_FLASH_Erase_Sector(uint32_t sector_num){
  
  QSPI_CommandTypeDef qspi_cmd;
  
  qspi_cmd.Instruction 		 	= CMD_SE;
  qspi_cmd.InstructionMode    	= QSPI_INSTRUCTION_1_LINE;
  
  qspi_cmd.Address            	= W25QXX_FLASH_START_ADDRESS + sector_num * FLASH_SECTOR_SIZE;
  qspi_cmd.AddressSize        	= QSPI_ADDRESS_24_BITS;
  qspi_cmd.AddressMode        	= QSPI_ADDRESS_1_LINE;
  
  qspi_cmd.AlternateBytes 	 	= 0x00;
  qspi_cmd.AlternateBytesSize 	= QSPI_ALTERNATE_BYTES_8_BITS;
  qspi_cmd.AlternateByteMode 	= QSPI_ALTERNATE_BYTES_NONE;
  
  qspi_cmd.DummyCycles        	= 0;
  
  qspi_cmd.DataMode 		    = QSPI_DATA_NONE;
  qspi_cmd.NbData             	= 0;
  
  qspi_cmd.DdrMode        	    = QSPI_DDR_MODE_DISABLE;
  qspi_cmd.DdrHoldHalfCycle     = QSPI_DDR_HHC_ANALOG_DELAY;
  qspi_cmd.SIOOMode           	= QSPI_SIOO_INST_EVERY_CMD;
  
  if(sector_num > (W25QXX_FLASH_SECTOR_AMOUNT - 1)){
    Error_Handler();
  }
  else{
    W25QXX_FLASH_Enable_Write();
    if (HAL_QSPI_Command(&hqspi, &qspi_cmd, HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      Error_Handler();
    }
    W25QXX_FLASH_Wait_Busy();
  }
}

void W25QXX_FLASH_Erase_Block(uint8_t block_num){
  
  QSPI_CommandTypeDef qspi_cmd;
  
  qspi_cmd.Instruction 		 	= CMD_64KB_BE;
  qspi_cmd.InstructionMode    	= QSPI_INSTRUCTION_1_LINE;
  
  qspi_cmd.Address            	= W25QXX_FLASH_START_ADDRESS + block_num * W25QXX_FLASH_BLOCK_SIZE;
  qspi_cmd.AddressSize        	= QSPI_ADDRESS_24_BITS;
  qspi_cmd.AddressMode        	= QSPI_ADDRESS_1_LINE;
  
  qspi_cmd.AlternateBytes 	 	= 0x00;
  qspi_cmd.AlternateBytesSize 	= QSPI_ALTERNATE_BYTES_8_BITS;
  qspi_cmd.AlternateByteMode 	= QSPI_ALTERNATE_BYTES_NONE;
  
  qspi_cmd.DummyCycles        	= 0;
  
  qspi_cmd.DataMode 		    = QSPI_DATA_NONE;
  qspi_cmd.NbData             	= 0;
  
  qspi_cmd.DdrMode        	    = QSPI_DDR_MODE_DISABLE;
  qspi_cmd.DdrHoldHalfCycle     = QSPI_DDR_HHC_ANALOG_DELAY;
  qspi_cmd.SIOOMode           	= QSPI_SIOO_INST_EVERY_CMD;
  
  if(block_num > (W25QXX_FLASH_BLOCK_AMOUNT - 1)){
    Error_Handler();
  }
  else{
    W25QXX_FLASH_Enable_Write();
    if (HAL_QSPI_Command(&hqspi, &qspi_cmd, HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      Error_Handler();
    }
    W25QXX_FLASH_Wait_Busy();
  }
}

void W25QXX_FLASH_Erase_Chip(void){
    
  QSPI_CommandTypeDef qspi_cmd;
  
  qspi_cmd.Instruction 		 	= CMD_CE;
  qspi_cmd.InstructionMode    	= QSPI_INSTRUCTION_1_LINE;
  
  qspi_cmd.Address            	= W25QXX_FLASH_START_ADDRESS;
  qspi_cmd.AddressSize        	= QSPI_ADDRESS_24_BITS;
  qspi_cmd.AddressMode        	= QSPI_ADDRESS_NONE;
  
  qspi_cmd.AlternateBytes 	 	= 0x00;
  qspi_cmd.AlternateBytesSize 	= QSPI_ALTERNATE_BYTES_8_BITS;
  qspi_cmd.AlternateByteMode 	= QSPI_ALTERNATE_BYTES_NONE;
  
  qspi_cmd.DummyCycles        	= 0;
  
  qspi_cmd.DataMode 		    = QSPI_DATA_NONE;
  qspi_cmd.NbData             	= 0;
  
  qspi_cmd.DdrMode        	    = QSPI_DDR_MODE_DISABLE;
  qspi_cmd.DdrHoldHalfCycle     = QSPI_DDR_HHC_ANALOG_DELAY;
  qspi_cmd.SIOOMode           	= QSPI_SIOO_INST_EVERY_CMD;
  
  W25QXX_FLASH_Enable_Write();
  if (HAL_QSPI_Command(&hqspi, &qspi_cmd, HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    Error_Handler();
  }
  W25QXX_FLASH_Wait_Busy();
}

void W25QXX_FLASH_Read_Data(uint8_t *data, uint32_t address, uint32_t length){
    
  QSPI_CommandTypeDef qspi_cmd;
  
  qspi_cmd.Instruction 		 	= CMD_QUAD_IO_READ;
  qspi_cmd.InstructionMode    	= QSPI_INSTRUCTION_1_LINE;
  
  qspi_cmd.Address            	= W25QXX_FLASH_START_ADDRESS + address;
  qspi_cmd.AddressSize        	= QSPI_ADDRESS_24_BITS;
  qspi_cmd.AddressMode        	= QSPI_ADDRESS_4_LINES;
  
  qspi_cmd.AlternateBytes 	 	= 0x00;
  qspi_cmd.AlternateBytesSize 	= QSPI_ALTERNATE_BYTES_8_BITS;
  qspi_cmd.AlternateByteMode 	= QSPI_ALTERNATE_BYTES_4_LINES;
  
  qspi_cmd.DummyCycles        	= 4;
  
  qspi_cmd.DataMode 			= QSPI_DATA_4_LINES;
  qspi_cmd.NbData             	= length;
  
  qspi_cmd.DdrMode        	    = QSPI_DDR_MODE_DISABLE;
  qspi_cmd.DdrHoldHalfCycle     = QSPI_DDR_HHC_ANALOG_DELAY;
  qspi_cmd.SIOOMode           	= QSPI_SIOO_INST_EVERY_CMD;
  
  if((W25QXX_FLASH_START_ADDRESS + address + length - 1) > W25QXX_FLASH_END_ADDRESS){
    Error_Handler();
  }
  else{
    if (HAL_QSPI_Command(&hqspi, &qspi_cmd, HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      Error_Handler();
    }
    if (HAL_QSPI_Receive(&hqspi, data, HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      Error_Handler();
    }
  }
}

static void W25QXX_FLASH_Write_Page_Data(uint8_t *data, uint32_t address, uint32_t length){
    
  QSPI_CommandTypeDef qspi_cmd;
  
  qspi_cmd.Instruction 		 	= CMD_QUAD_PP;
  qspi_cmd.InstructionMode    	= QSPI_INSTRUCTION_1_LINE;
  
  qspi_cmd.Address            	= W25QXX_FLASH_START_ADDRESS + address;
  qspi_cmd.AddressSize        	= QSPI_ADDRESS_24_BITS;
  qspi_cmd.AddressMode        	= QSPI_ADDRESS_1_LINE;
  
  qspi_cmd.AlternateBytes 	 	= 0x00;
  qspi_cmd.AlternateBytesSize 	= QSPI_ALTERNATE_BYTES_8_BITS;
  qspi_cmd.AlternateByteMode 	= QSPI_ALTERNATE_BYTES_NONE;
  
  qspi_cmd.DummyCycles        	= 0;
  
  qspi_cmd.DataMode 			= QSPI_DATA_4_LINES;
  qspi_cmd.NbData             	= length;
  
  qspi_cmd.DdrMode        	    = QSPI_DDR_MODE_DISABLE;
  qspi_cmd.DdrHoldHalfCycle     = QSPI_DDR_HHC_ANALOG_DELAY;
  qspi_cmd.SIOOMode           	= QSPI_SIOO_INST_EVERY_CMD;
  
  if(((W25QXX_FLASH_START_ADDRESS + address + length - 1) >> 8) > ((W25QXX_FLASH_START_ADDRESS + address) >> 8)){
    Error_Handler();
  }
  else{
    W25QXX_FLASH_Enable_Write();
    if (HAL_QSPI_Command(&hqspi, &qspi_cmd, HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      Error_Handler();
    }
    if (HAL_QSPI_Transmit(&hqspi, data, HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      Error_Handler();
    }
    W25QXX_FLASH_Wait_Busy();
  }
}

void W25QXX_FLASH_Write_Data(uint8_t *data, uint32_t address, uint32_t length){
  uint32_t length_temp = 0;
  if((W25QXX_FLASH_START_ADDRESS + address + length - 1) > W25QXX_FLASH_END_ADDRESS){
    Error_Handler();
  }
  else{
    length_temp = W25QXX_FLASH_PAGE_SIZE - (address % W25QXX_FLASH_PAGE_SIZE);
    if(length <= length_temp){
      length_temp = length;
    }
    while(1){
      W25QXX_FLASH_Write_Page_Data(data, address, length_temp);
      if(length == length_temp){
        break;
      }
      else{
        data = data + length_temp;
        address = address + length_temp;
        length = length - length_temp;
        
        if(length > W25QXX_FLASH_PAGE_SIZE){
          length_temp = W25QXX_FLASH_PAGE_SIZE;
        }
        else{
          length_temp = length;
        }
      }
    }
  }
}
#endif

#ifdef USE_SPI
extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi4;

void W25QXX_FLASH_Read_ID(uint8_t *data){
  uint8_t temp[1] = {0};
  temp[0] = CMD_RDID;
  FLASH_CS_Low();
  HAL_SPI_Transmit(&hspi4,temp,1,HAL_SPI_TIMEOUT_DEFAULT_VALUE);
  HAL_SPI_Receive(&hspi4,data,3,HAL_SPI_TIMEOUT_DEFAULT_VALUE);
  FLASH_CS_High();
}

static void W25QXX_FLASH_Wait_Busy(void){
  uint8_t temp[1] = {0};
  do{
    W25QXX_FLASH_Read_Status_Reg(FLASH_SR1, temp);
  }while((temp[0] & 0x01) != 0x00);
}

static void W25QXX_FLASH_Enable_Write(void){
  uint8_t temp[1] = {0};
  temp[0] = CMD_WREN;
  FLASH_CS_Low();
  HAL_SPI_Transmit(&hspi4,temp,1,HAL_SPI_TIMEOUT_DEFAULT_VALUE);
  FLASH_CS_High();
}

//static void W25QXX_FLASH_Disable_Write(void){
//    
//  	QSPI_CommandTypeDef qspi_cmd;
//	
//    qspi_cmd.Instruction 		 	= CMD_WRDI;
//    qspi_cmd.InstructionMode    	= QSPI_INSTRUCTION_1_LINE;
//    
//    qspi_cmd.Address            	= 0x000000;
//    qspi_cmd.AddressSize        	= QSPI_ADDRESS_24_BITS;
//    qspi_cmd.AddressMode        	= QSPI_ADDRESS_NONE;
//    
//    qspi_cmd.AlternateBytes 	 	= 0x00;
//    qspi_cmd.AlternateBytesSize 	= QSPI_ALTERNATE_BYTES_8_BITS;
//    qspi_cmd.AlternateByteMode 	    = QSPI_ALTERNATE_BYTES_NONE;
//    
//    qspi_cmd.DummyCycles        	= 0;
//    
//	qspi_cmd.DataMode 			 	= QSPI_DATA_NONE;
//	qspi_cmd.NbData             	= 0;
//    
//	qspi_cmd.DdrMode        	    = QSPI_DDR_MODE_DISABLE;
//	qspi_cmd.DdrHoldHalfCycle       = QSPI_DDR_HHC_ANALOG_DELAY;
//	qspi_cmd.SIOOMode           	= QSPI_SIOO_INST_EVERY_CMD;
//	
//	if (HAL_QSPI_Command(&hqspi, &qspi_cmd, HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
//	{
//      Error_Handler();
//	}
//}

static void W25QXX_FLASH_Read_Status_Reg(uint8_t reg_channel, uint8_t *data){
 
  uint8_t temp[1] = {0};
  
  switch(reg_channel){
  case FLASH_SR1:
    temp[0] 		 	= CMD_RDSR1;
    break;
  case FLASH_SR2:
    temp[0] 		 	= CMD_RDSR2;
    break;
  case FLASH_SR3:
    temp[0] 		 	= CMD_RDSR3;
    break;
  default:
    Error_Handler();
    break;
  }
  FLASH_CS_Low();
  HAL_SPI_Transmit(&hspi4,temp,1,HAL_SPI_TIMEOUT_DEFAULT_VALUE);
  HAL_SPI_Receive(&hspi4,data,1,HAL_SPI_TIMEOUT_DEFAULT_VALUE);
  FLASH_CS_High();
}

static void W25QXX_FLASH_Write_Status_Reg(uint8_t reg_channel, uint8_t *data){
  
  uint8_t temp[2] = {0};
   
  switch(reg_channel){
  case FLASH_SR1:
    temp[0] 		 	= CMD_WRSR1;
    break;
  case FLASH_SR2:
    temp[0] 		 	= CMD_WRSR2;
    break;
  case FLASH_SR3:
    temp[0] 		 	= CMD_WRSR3;
    break;
  default:
    Error_Handler();
    break;
  }
  temp[1] = *data;
  
  W25QXX_FLASH_Enable_Write();
  FLASH_CS_Low();
  HAL_SPI_Transmit(&hspi4,temp,2,HAL_SPI_TIMEOUT_DEFAULT_VALUE);
  FLASH_CS_High();
  W25QXX_FLASH_Wait_Busy();
}

void W25QXX_FLASH_Enable_QSPI(void){
  uint8_t temp[2] = {0}, write_count = 0;
  W25QXX_FLASH_Read_Status_Reg(FLASH_SR2, temp);
  if((temp[0] & FLASH_QE_BIT) == 0x02){
    //Do Nothing
  }
  else{
    temp[1] = temp[0] | FLASH_QE_BIT;
    //����QE
    do{
      W25QXX_FLASH_Write_Status_Reg(FLASH_SR2, temp + 1);
      W25QXX_FLASH_Read_Status_Reg(FLASH_SR2, temp);
      write_count++;
      if(write_count >= 3){
        Error_Handler();
        break;
      }
    }while(((temp[0] & FLASH_QE_BIT) != 0x02));
  }
}

void W25QXX_FLASH_Erase_Sector(uint32_t sector_num){
  
  uint8_t temp[4] = {0};
  uint32_t address = 0;
  temp[0] = CMD_SE;
  address = W25QXX_FLASH_START_ADDRESS + sector_num * FLASH_SECTOR_SIZE;
  temp[1] = address >> 16;
  temp[2] = address >> 8;
  temp[3] = address & 0xFF;
  
  if(sector_num > (W25QXX_FLASH_SECTOR_AMOUNT - 1)){
    Error_Handler();
  }
  else{
    W25QXX_FLASH_Enable_Write();
    FLASH_CS_Low();
    if (HAL_SPI_Transmit(&hspi4,temp,4,HAL_SPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      Error_Handler();
    }
    FLASH_CS_High();
    W25QXX_FLASH_Wait_Busy();
  }
}

void W25QXX_FLASH_Erase_Block(uint8_t block_num){
  
  uint8_t temp[4] = {0};
  uint32_t address = 0;
  temp[0] = CMD_64KB_BE;
  address = W25QXX_FLASH_START_ADDRESS + block_num * W25QXX_FLASH_BLOCK_SIZE;
  temp[1] = address >> 16;
  temp[2] = address >> 8;
  temp[3] = address & 0xFF;
  
  if(block_num > (W25QXX_FLASH_BLOCK_AMOUNT - 1)){
    Error_Handler();
  }
  else{
    W25QXX_FLASH_Enable_Write();
    FLASH_CS_Low();
    if (HAL_SPI_Transmit(&hspi4,temp,4,HAL_SPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      Error_Handler();
    }
    FLASH_CS_High();
    W25QXX_FLASH_Wait_Busy();
  }
}

void W25QXX_FLASH_Erase_Chip(void){
  
  uint8_t temp[1] = {0};
  temp[0] = CMD_CE;
  
  W25QXX_FLASH_Enable_Write();
  FLASH_CS_Low();
  if (HAL_SPI_Transmit(&hspi4,temp,1,HAL_SPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    Error_Handler();
  }
  FLASH_CS_High();
  W25QXX_FLASH_Wait_Busy();
}

void W25QXX_FLASH_Read_Data(uint8_t *data, uint32_t address, uint32_t length){
  
  uint8_t temp[5] = {0};
  temp[0] = CMD_FAST_READ;
  temp[1] = address >> 16;
  temp[2] = address >> 8;
  temp[3] = address & 0xFF;
  temp[4] = 0;
  
  if((W25QXX_FLASH_START_ADDRESS + address + length - 1) > W25QXX_FLASH_END_ADDRESS){
    Error_Handler();
  }
  else{
    FLASH_CS_Low();
    if (HAL_SPI_Transmit(&hspi4,temp,5,HAL_SPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      Error_Handler();
    }
    while(1){
      if (HAL_SPI_Receive(&hspi4,data,length,HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
      {
        Error_Handler();
      }
      if(length > 65535){
        length = length - 65535;
        data = data + 65535;
      }
      else{
        break;
      }
    }
    FLASH_CS_High();
  }
}

static void W25QXX_FLASH_Write_Page_Data(uint8_t *data, uint32_t address, uint32_t length){
  
  uint8_t temp[4] = {0};
  temp[0] = CMD_PP;
  temp[1] = address >> 16;
  temp[2] = address >> 8;
  temp[3] = address & 0xFF;
  
  if(((W25QXX_FLASH_START_ADDRESS + address + length - 1) >> 8) > ((W25QXX_FLASH_START_ADDRESS + address) >> 8)){
    Error_Handler();
  }
  else{
    W25QXX_FLASH_Enable_Write();
    FLASH_CS_Low();
    if (HAL_SPI_Transmit(&hspi4,temp,4,HAL_SPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      Error_Handler();
    }
    if (HAL_SPI_Transmit(&hspi4,data,length,HAL_SPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      Error_Handler();
    }
    FLASH_CS_High();
    W25QXX_FLASH_Wait_Busy();
  }
}

void W25QXX_FLASH_Write_Data(uint8_t *data, uint32_t address, uint32_t length){
  uint32_t length_temp = 0;
  if((W25QXX_FLASH_START_ADDRESS + address + length - 1) > W25QXX_FLASH_END_ADDRESS){
    Error_Handler();
  }
  else{
    length_temp = W25QXX_FLASH_PAGE_SIZE - (address % W25QXX_FLASH_PAGE_SIZE);
    if(length <= length_temp){
      length_temp = length;
    }
    while(1){
      W25QXX_FLASH_Write_Page_Data(data, address, length_temp);
      if(length == length_temp){
        break;
      }
      else{
        data = data + length_temp;
        address = address + length_temp;
        length = length - length_temp;
        
        if(length > W25QXX_FLASH_PAGE_SIZE){
          length_temp = W25QXX_FLASH_PAGE_SIZE;
        }
        else{
          length_temp = length;
        }
      }
    }
  }
}
#endif