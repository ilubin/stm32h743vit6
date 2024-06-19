#ifndef __USER_DCMI_H
#define __USER_DCMI_H

#include "main.h"

extern DCMI_HandleTypeDef hdcmi;

void MX_DCMI_Init(void);
void HAL_DCMI_FrameEventCallback(DCMI_HandleTypeDef *hdcmi);

#endif