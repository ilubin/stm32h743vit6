#include "user_camera.h"
#include "user_tim.h"
#include "user_i2c.h"

Camera_HandleTypeDef hcamera;
extern I2C_HandleTypeDef hi2c1;

uint8_t OV2640_Allow_Size[OV2640_NUM_Allow_Size] = {
  FRAMESIZE_CIF,      // 352x288
  FRAMESIZE_SIF,      // 352x240
  FRAMESIZE_QQVGA,    // 160x120
  FRAMESIZE_128X64,   // 128x64
  FRAMESIZE_QVGA,     // 320x240
  FRAMESIZE_VGA,      // 640x480
  FRAMESIZE_HVGA,     // 480x320
  FRAMESIZE_WVGA2,    // 752x480
  FRAMESIZE_SVGA,     // 800x600
  FRAMESIZE_XGA,      // 1024x768
  FRAMESIZE_SXGA,     // 1280x1024
  FRAMESIZE_UXGA,     // 1600x1200
};

uint8_t OV2640_RGB565_Regs[][2] = {
  { BANK_SEL, BANK_SEL_DSP },
  { REG_RESET,   REG_RESET_DVP},
  { IMAGE_MODE, IMAGE_MODE_RGB565 },
  { 0xD7,     0x03 },
  { 0xE1,     0x77 },
  { REG_RESET,    0x00 },
  {0, 0},
};

uint8_t OV2640_JPEG_Regs[][2] = {
  {BANK_SEL,      BANK_SEL_DSP},
  {REG_RESET,         REG_RESET_DVP},
  {IMAGE_MODE,    IMAGE_MODE_JPEG_EN | IMAGE_MODE_RGB565},
  {0xd7,          0x03},
  {0xe1,          0x77},
  {REG_RESET,         0x00},
  {0,             0},
};

uint8_t OV2640_YUYV_Regs[][2] = {
  {BANK_SEL,      BANK_SEL_DSP},
  {REG_RESET,     REG_RESET_DVP},
  { IMAGE_MODE, IMAGE_MODE_YUV422 },
  { 0xd7, 0x03 },
  { 0x33, 0xa0 },
  { 0xe5, 0x1f },
  { 0xe1, 0x67 },
  { REG_RESET,  0x00 },
  {0,             0},
};

uint8_t OV2640_Slow_Regs[][2] = {
  {0xff, 0x01},
  {0x12, 0x80},
  {0xff, 0x00},
  {0x2c, 0xff},
  {0x2e, 0xdf},
  {0xff, 0x01},
  {0x3c, 0x32},
  {0x11, 0x00}, // clk div 0
  {0x09, 0x02},
  {0x04, 0xD8}, //0x88
  {0x13, 0xe5},
  {0x14, 0x48},
  {0x2c, 0x0c},
  {0x33, 0x78},
  {0x3a, 0x33},
  {0x3b, 0xfb},
  {0x3e, 0x00},
  {0x43, 0x11},
  {0x16, 0x10},
  {0x39, 0x92},
  {0x35, 0xda},
  {0x22, 0x1a},
  {0x37, 0xc3},
  {0x23, 0x00},
  {0x34, 0xc0},
  {0x36, 0x1a},
  {0x06, 0x88},
  {0x07, 0xc0},
  {0x0d, 0x87},
  {0x0e, 0x41},
  {0x4c, 0x00},
  {0x48, 0x00},
  {0x5b, 0x00},
  {0x42, 0x03},
  {0x4a, 0x81},
  {0x21, 0x99},
  {0x24, 0x40},
  {0x25, 0x38},
  {0x26, 0x82},
  {0x5c, 0x00},
  {0x63, 0x00},
  {0x46, 0x22},
  {0x0c, 0x3c},
  {0x61, 0x70},
  {0x62, 0x80},
  {0x7c, 0x05},
  {0x20, 0x80},
  {0x28, 0x30},
  {0x6c, 0x00},
  {0x6d, 0x80},
  {0x6e, 0x00},
  {0x70, 0x02},
  {0x71, 0x94},
  {0x73, 0xc1},
  {0x3d, 0x34},
  {0x5a, 0x57},
  {0x12, 0x40},
  {0x17, 0x11},
  {0x18, 0x43},
  {0x19, 0x00},
  {0x1a, 0x4b},
  {0x32, 0x09},
  {0x37, 0xc0},
  {0x4f, 0xca},
  {0x50, 0xa8},
  {0x5a, 0x23},
  {0x6d, 0x00},
  {0x3d, 0x38},
  {0xff, 0x00},
  {0xe5, 0x7f},
  {0xf9, 0xc0},
  {0x41, 0x24},
  {0xe0, 0x14},
  {0x76, 0xff},
  {0x33, 0xa0},
  {0x42, 0x20},
  {0x43, 0x18},
  {0x4c, 0x00},
  {0x87, 0xd5},
  {0x88, 0x3f},
  {0xd7, 0x03},
  {0xd9, 0x10},
  {0xd3, 0x82},
  {0xc8, 0x08},
  {0xc9, 0x80},
  {0x7c, 0x00},
  {0x7d, 0x00},
  {0x7c, 0x03},
  {0x7d, 0x48},
  {0x7d, 0x48},
  {0x7c, 0x08},
  {0x7d, 0x20},
  {0x7d, 0x10},
  {0x7d, 0x0e},
  {0x90, 0x00},
  {0x91, 0x0e},
  {0x91, 0x1a},
  {0x91, 0x31},
  {0x91, 0x5a},
  {0x91, 0x69},
  {0x91, 0x75},
  {0x91, 0x7e},
  {0x91, 0x88},
  {0x91, 0x8f},
  {0x91, 0x96},
  {0x91, 0xa3},
  {0x91, 0xaf},
  {0x91, 0xc4},
  {0x91, 0xd7},
  {0x91, 0xe8},
  {0x91, 0x20},
  {0x92, 0x00},
  {0x93, 0x06},
  {0x93, 0xe3},
  {0x93, 0x05},
  {0x93, 0x05},
  {0x93, 0x00},
  {0x93, 0x04},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x96, 0x00},
  {0x97, 0x08},
  {0x97, 0x19},
  {0x97, 0x02},
  {0x97, 0x0c},
  {0x97, 0x24},
  {0x97, 0x30},
  {0x97, 0x28},
  {0x97, 0x26},
  {0x97, 0x02},
  {0x97, 0x98},
  {0x97, 0x80},
  {0x97, 0x00},
  {0x97, 0x00},
  {0xc3, 0xed},
  {0xa4, 0x00},
  {0xa8, 0x00},
  {0xc5, 0x11},
  {0xc6, 0x51},
  {0xbf, 0x80},
  {0xc7, 0x10},
  {0xb6, 0x66},
  {0xb8, 0xa5},
  {0xb7, 0x64},
  {0xb9, 0x7c},
  {0xb3, 0xaf},
  {0xb4, 0x97},
  {0xb5, 0xff},
  {0xb0, 0xc5},
  {0xb1, 0x94},
  {0xb2, 0x0f},
  {0xc4, 0x5c},
  {0xc0, 0x64},
  {0xc1, 0x4b},
  {0x8c, 0x00},
  {0x86, 0x3d},
  {0x50, 0x00},
  {0x51, 0xc8},
  {0x52, 0x96},
  {0x53, 0x00},
  {0x54, 0x00},
  {0x55, 0x00},
  {0x5a, 0xc8},
  {0x5b, 0x96},
  {0x5c, 0x00},
  {0xd3, 0x02},
  {0xc3, 0xed},
  {0x7f, 0x00},
  {0xda, 0x08},
  {0xe5, 0x1f},
  {0xe1, 0x67},
  {0xe0, 0x00},
  {0xdd, 0x7f},
  {0x05, 0x00},
  {0xff, 0x00},
  {0xe0, 0x04},
  {0x5a, 0x50},
  {0x5b, 0x3c},
  {0x5c, 0x00},
  {0xe0, 0x00},
  {0x00, 0x00},
};

uint8_t OV2640_SVGA_Regs[][2] = {
  { BANK_SEL, BANK_SEL_SENSOR },
  /* DSP input image resoultion and window size control */
  { COM7,    COM7_RES_SVGA},
  { COM1,    0x0F }, /* UXGA=0x0F, SVGA=0x0A, CIF=0x06 */
  { REG32,   0x09 }, /* UXGA=0x36, SVGA/CIF=0x09 */
  
  { HSTART,  0x11 }, /* UXGA=0x11, SVGA/CIF=0x11 */
  { HSTOP,   0x43 }, /* UXGA=0x75, SVGA/CIF=0x43 */
  
  { VSTART,  0x00 }, /* UXGA=0x01, SVGA/CIF=0x00 */
  { VSTOP,   0x4b }, /* UXGA=0x97, SVGA/CIF=0x4b */
  { 0x3d,    0x38 }, /* UXGA=0x34, SVGA/CIF=0x38 */
  
  { 0x35,    0xda },
  { 0x22,    0x1a },
  { 0x37,    0xc3 },
  { 0x34,    0xc0 },
  { 0x06,    0x88 },
  { 0x0d,    0x87 },
  { 0x0e,    0x41 },
  { 0x42,    0x03 },
  
  /* Set DSP input image size and offset.
  The sensor output image can be scaled with OUTW/OUTH */
  { BANK_SEL, BANK_SEL_DSP },
  { R_BYPASS, R_BYPASS_DSP_BYPAS },
  
  { REG_RESET,   REG_RESET_DVP },
  { HSIZE8,  (SVGA_HSIZE>>3)}, /* Image Horizontal Size HSIZE[10:3] */
  { VSIZE8,  (SVGA_VSIZE>>3)}, /* Image Vertiacl Size VSIZE[10:3] */
  
  /* {HSIZE[11], HSIZE[2:0], VSIZE[2:0]} */
  { SIZEL,   ((SVGA_HSIZE>>6)&0x40) | ((SVGA_HSIZE&0x7)<<3) | (SVGA_VSIZE&0x7)},
  
  { XOFFL,   0x00 }, /* OFFSET_X[7:0] */
  { YOFFL,   0x00 }, /* OFFSET_Y[7:0] */
  { HSIZE,   ((SVGA_HSIZE>>2)&0xFF) }, /* H_SIZE[7:0]= HSIZE/4 */
  { VSIZE,   ((SVGA_VSIZE>>2)&0xFF) }, /* V_SIZE[7:0]= VSIZE/4 */
  
  /* V_SIZE[8]/OFFSET_Y[10:8]/H_SIZE[8]/OFFSET_X[10:8] */
  { VHYX,    ((SVGA_VSIZE>>3)&0x80) | ((SVGA_HSIZE>>7)&0x08) },
  { TEST,    (SVGA_HSIZE>>4)&0x80}, /* H_SIZE[9] */
  
  { CTRL2,   CTRL2_DCW_EN | CTRL2_SDE_EN |
    CTRL2_UV_AVG_EN | CTRL2_CMX_EN | CTRL2_UV_ADJ_EN },
    
    /* H_DIVIDER/V_DIVIDER */
    { CTRLI,   CTRLI_LP_DP | 0x00},
    /* DVP prescalar */
    { R_DVP_SP, R_DVP_SP_AUTO_MODE},
    
    { R_BYPASS, R_BYPASS_DSP_EN },
    { REG_RESET,    0x00 },
    {0, 0},
};

uint8_t OV2640_UXGA_Regs[][2] = {
  { BANK_SEL, BANK_SEL_SENSOR },
  /* DSP input image resoultion and window size control */
  { COM7,    COM7_RES_UXGA},
  { COM1,    0x0F }, /* UXGA=0x0F, SVGA=0x0A, CIF=0x06 */
  { REG32,   0x36 }, /* UXGA=0x36, SVGA/CIF=0x09 */
  
  { HSTART,  0x11 }, /* UXGA=0x11, SVGA/CIF=0x11 */
  { HSTOP,   0x75 }, /* UXGA=0x75, SVGA/CIF=0x43 */
  
  { VSTART,  0x01 }, /* UXGA=0x01, SVGA/CIF=0x00 */
  { VSTOP,   0x97 }, /* UXGA=0x97, SVGA/CIF=0x4b */
  { 0x3d,    0x34 }, /* UXGA=0x34, SVGA/CIF=0x38 */
  
  { 0x35,    0x88 },
  { 0x22,    0x0a },
  { 0x37,    0x40 },
  { 0x34,    0xa0 },
  { 0x06,    0x02 },
  { 0x0d,    0xb7 },
  { 0x0e,    0x01 },
  { 0x42,    0x83 },
  
  /* Set DSP input image size and offset.
  The sensor output image can be scaled with OUTW/OUTH */
  { BANK_SEL, BANK_SEL_DSP },
  { R_BYPASS, R_BYPASS_DSP_BYPAS },
  
  { REG_RESET,   REG_RESET_DVP },
  { HSIZE8,  (UXGA_HSIZE>>3)}, /* Image Horizontal Size HSIZE[10:3] */
  { VSIZE8,  (UXGA_VSIZE>>3)}, /* Image Vertiacl Size VSIZE[10:3] */
  
  /* {HSIZE[11], HSIZE[2:0], VSIZE[2:0]} */
  { SIZEL,   ((UXGA_HSIZE>>6)&0x40) | ((UXGA_HSIZE&0x7)<<3) | (UXGA_VSIZE&0x7)},
  
  { XOFFL,   0x00 }, /* OFFSET_X[7:0] */
  { YOFFL,   0x00 }, /* OFFSET_Y[7:0] */
  { HSIZE,   ((UXGA_HSIZE>>2)&0xFF) }, /* H_SIZE[7:0] real/4 */
  { VSIZE,   ((UXGA_VSIZE>>2)&0xFF) }, /* V_SIZE[7:0] real/4 */
  
  /* V_SIZE[8]/OFFSET_Y[10:8]/H_SIZE[8]/OFFSET_X[10:8] */
  { VHYX,    ((UXGA_VSIZE>>3)&0x80) | ((UXGA_HSIZE>>7)&0x08) },
  { TEST,    (UXGA_HSIZE>>4)&0x80}, /* H_SIZE[9] */
  
  { CTRL2,   CTRL2_DCW_EN | CTRL2_SDE_EN |
    CTRL2_UV_AVG_EN | CTRL2_CMX_EN | CTRL2_UV_ADJ_EN },
    
    /* H_DIVIDER/V_DIVIDER */
    { CTRLI,   CTRLI_LP_DP | 0x00},
    /* DVP prescalar */
    { R_DVP_SP, R_DVP_SP_AUTO_MODE | 0x04},
    
    { R_BYPASS, R_BYPASS_DSP_EN },
    { REG_RESET,    0x00 },
    {0, 0},
};

uint16_t OV2640_DVP_Cam_Resolution[][2] = {
  {0, 0},
  // C/SIF Resolutions
  {88, 72},	/* QQCIF     */
  {176, 144}, /* QCIF      */
  {352, 288}, /* CIF       */
  {88, 60},	/* QQSIF     */
  {176, 120}, /* QSIF      */
  {352, 240}, /* SIF       */
  // VGA Resolutions
  {40, 30},	/* QQQQVGA   */
  {80, 60},	/* QQQVGA    */
  {160, 120}, /* QQVGA     */
  {320, 240}, /* QVGA      */
  {640, 480}, /* VGA       */
  {60, 40},	/* HQQQVGA   */
  {120, 80},	/* HQQVGA    */
  {240, 160}, /* HQVGA     */
  {480, 320}, /* HVGA      */
  // FFT Resolutions
  {64, 32},	/* 64x32     */
  {64, 64},	/* 64x64     */
  {128, 64},	/* 128x64    */
  {128, 128}, /* 128x64    */
  // Other
  {128, 160},	  /* LCD       */
  {128, 160},	  /* QQVGA2    */
  {720, 480},	  /* WVGA      */
  {752, 480},	  /* WVGA2     */
  {800, 600},	  /* SVGA      */
  {1024, 768},  /* XGA       */
  {1280, 1024}, /* SXGA      */
  {1600, 1200}, /* UXGA      */
  {1280, 720},  /* 720P      */
  {1920, 1080}, /* 1080P     */
  {1280, 960},  /* 960P      */
  {2592, 1944}, /* 5MP       */
};

static void Camera_Write_Reg(uint8_t reg, uint8_t data)
{
  HAL_I2C_Mem_Write(&hi2c1, OV2640_ADDR, reg, I2C_MEMADD_SIZE_8BIT, &data, 1, HAL_I2C_TIMEOUT_DEFAULT_VALUE);
  while(HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY);
}

static uint8_t Camera_Read_Reg(uint8_t reg)
{
  uint8_t data = 0;
  HAL_I2C_Mem_Read(&hi2c1, OV2640_ADDR, reg, I2C_MEMADD_SIZE_8BIT, &data, 1, HAL_I2C_TIMEOUT_DEFAULT_VALUE);
  while(HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY);
  return data;
}

static void Camera_Write_Sensor_Regs(uint8_t (*regs)[2])
{
  uint32_t i = 0;
  for (i = 0; regs[i][0]; i++) {
    Camera_Write_Reg(regs[i][0], regs[i][1]);
  }
}

static void Camera_Reset()
{
  delay_ms(100);
  Camera_Write_Reg(BANK_SEL, BANK_SEL_SENSOR);
  Camera_Write_Reg(COM7, COM7_SRST);
  delay_ms(5);
  Camera_Write_Sensor_Regs(OV2640_Slow_Regs);
  delay_ms(30);
}

static void Camera_Set_Framesize(uint8_t framesize)
{
  uint8_t cbar = 0, qsreg = 0, com7 = 0;
  
  Camera_Write_Reg(BANK_SEL, BANK_SEL_SENSOR);
  cbar = Camera_Read_Reg(COM7) & COM7_COLOR_BAR;
  Camera_Write_Reg(BANK_SEL, BANK_SEL_DSP);
  qsreg = Camera_Read_Reg(QS);
  
  uint16_t w = OV2640_DVP_Cam_Resolution[framesize][0];
  uint16_t h = OV2640_DVP_Cam_Resolution[framesize][1];
  uint8_t (*regs)[2];
  
  if (w <= OV2640_DVP_Cam_Resolution[FRAMESIZE_SVGA][0]) regs = OV2640_SVGA_Regs;
  else regs = OV2640_UXGA_Regs;
  
  Camera_Write_Reg(BANK_SEL, BANK_SEL_DSP);
  Camera_Write_Reg(R_BYPASS, R_BYPASS_DSP_BYPAS);
  
  Camera_Write_Reg(ZMOW, (w>>2)&0xFF);
  Camera_Write_Reg(ZMOH, (h>>2)&0xFF);
  Camera_Write_Reg(ZMHH, ((h>>8)&0x04)|((w>>10)&0x03));
  
  Camera_Write_Reg(BANK_SEL, BANK_SEL_SENSOR);
  
  Camera_Write_Sensor_Regs(regs);
  
  Camera_Write_Reg(BANK_SEL, BANK_SEL_SENSOR);
  com7 = Camera_Read_Reg(COM7) | cbar;
  Camera_Write_Reg(COM7, com7);
  
  Camera_Write_Reg(BANK_SEL, BANK_SEL_DSP);
  Camera_Write_Reg(QS, qsreg);
  
  Camera_Write_Reg(R_BYPASS, R_BYPASS_DSP_EN);
}

static void Camera_Set_PixelFormat(pixelformat_t pixelformat)
{
  Camera_Write_Reg(BANK_SEL, BANK_SEL_DSP);
  Camera_Write_Reg(R_BYPASS, R_BYPASS_DSP_BYPAS);
  
  switch (pixelformat) {
  case PIXFORMAT_RGB565:
    Camera_Write_Sensor_Regs(OV2640_RGB565_Regs);
    break;
  case PIXFORMAT_JPEG:
    Camera_Write_Sensor_Regs(OV2640_JPEG_Regs);
    break;
  case PIXFORMAT_YUV422:
    Camera_Write_Sensor_Regs(OV2640_YUYV_Regs);
    break;
  default:
    Camera_Write_Reg(BANK_SEL, BANK_SEL_DSP);
    Camera_Write_Reg(R_BYPASS, R_BYPASS_DSP_EN);
    Error_Handler();
    break;
  }
}

static void Camera_Set_Hflip(uint8_t enable)
{
  uint8_t reg = 0;
  Camera_Write_Reg(BANK_SEL, BANK_SEL_SENSOR);
  reg = Camera_Read_Reg(REG04);
  
  if (!enable) {
    reg |= REG04_HFLIP_IMG;
  }
  else {
    reg &= ~REG04_HFLIP_IMG;
  }
  
  Camera_Write_Reg(REG04, reg);
}

static void Camera_Set_Vflip(uint8_t enable)
{
  uint8_t reg = 0;
  Camera_Write_Reg(BANK_SEL, BANK_SEL_SENSOR);
  reg = Camera_Read_Reg(REG04);
  
  if (!enable) {
    reg |= REG04_VFLIP_IMG | REG04_VREF_EN;
  }
  else {
    reg &= ~(REG04_VFLIP_IMG | REG04_VREF_EN);
  }
  Camera_Write_Reg(REG04, reg);
}

static void Camera_Check_ID(void)
{ 
  uint16_t reg[2] = {0};
  uint8_t temp[4] = {0};
  
  temp[0] = Camera_Read_Reg(OV2640_SENSOR_MIDH);
  temp[1] = Camera_Read_Reg(OV2640_SENSOR_MIDL);
  
  reg[0] = (temp[0] << 8) + temp[1];
  
  if (reg[0] != OV2640_SENSOR_MID)
  {
    Error_Handler();
  }
  
  temp[2] = Camera_Read_Reg(OV2640_SENSOR_PIDH);
  temp[3] = Camera_Read_Reg(OV2640_SENSOR_PIDL);
  
  reg[1] = (temp[2] << 8) + temp[3];
  
  if (reg[1] != OV2640_SENSOR_PID)
  {
    Error_Handler();
  }
}

void Camera_Init(framesize_t framesize)
{
  //  HAL_GPIO_WritePin(GPIOB, DCMI_RES_Pin, GPIO_PIN_RESET);
  //  delay_ms(10);
  //  HAL_GPIO_WritePin(GPIOB, DCMI_PWDN_Pin, GPIO_PIN_RESET);
  //  delay_ms(10);
  //  HAL_GPIO_WritePin(GPIOB, DCMI_RES_Pin, GPIO_PIN_SET);
  Camera_Check_ID();
  Camera_Reset();
  hcamera.framesize = framesize;
  hcamera.pixelformat = PIXFORMAT_RGB565;
  Camera_Set_PixelFormat(hcamera.pixelformat);
  Camera_Set_Framesize(hcamera.framesize);
  Camera_Set_Hflip(1);
  Camera_Set_Vflip(0);
}
