#include "user_tim.h"

TIM_HandleTypeDef htim5;
TIM_HandleTypeDef htim6;
TIM_HandleTypeDef htim7;

void MX_TIM6_Init(void)
{
	SET_BIT(RCC->APB1LENR, RCC_APB1LENR_TIM6EN);
}
//us����ʱ ʵ����������1us����ʱ��1us��ʱ---ʵ��ֵ1.67us
void delay_us(uint16_t us)
{
    //ʱ�ӷ�Ƶ 240MHz��ʱ��Դ APB1 ��Ƶ��10M
	TIM6->PSC = (24 - 1);
	//����ֵ���� 10M ÿ��һ������ʱ��Ϊ0.1us ���Գ���10
	TIM6->ARR = us * 10;
	//���³�ʼ����ʱ�������������ɼĴ��������¼�,ȷ��Ԥ��Ƶֵ�����ã���ʱ��ʱ�������øո�д���Ԥ��Ƶֵ������˴������£���ô��ʱ����Ҫ�ȴ��´θ����¼��ĵ����Ż����¼���Ԥ��Ƶֵ
	TIM6->EGR |= (1<<0);
	//������±�־λ,��λ�ڷ��������¼�ʱͨ��Ӳ���� 1,����Ҫͨ���������
	TIM6->SR = 0;
	//CR1��bit3(OPM)��һ,�������ڷ�����һ�����¼�ʱֹͣ����,������ģʽ
	TIM6->CR1 |= (1<<3);
	//CR1��bit0(CEN)��һ,������ʱ����ʼ����
	TIM6->CR1 |= (1<<0);
	//�ȴ������¼�����,��������ֵ�������Զ���װ�ؼĴ�����ʱ��,����������¼�,��ʱ��ʱʱ���ѵ�
	while((TIM6->SR & 0x01)==0);
	//������±�־λ,��λ�ڷ��������¼�ʱͨ��Ӳ���� 1,����Ҫͨ���������
	TIM6->SR &= ~(1<<0);
}

//��������1msʱ
void delay_ms(uint16_t ms)
{
    //ʱ�ӷ�Ƶ 240MHz��ʱ��Դ APB1 ��Ƶ�� 40Khz
	TIM6->PSC = (6000 - 1);
	//(1 / 40000) * 40 = 0.001s = 1ms
	TIM6->ARR = ms*40;
	//���³�ʼ����ʱ�������������ɼĴ��������¼�,ȷ��Ԥ��Ƶֵ�����ã���ʱ��ʱ�������øո�д���Ԥ��Ƶֵ������˴������£���ô��ʱ����Ҫ�ȴ��´θ����¼��ĵ����Ż����¼���Ԥ��Ƶֵ
	TIM6->EGR |= (1<<0);
	//������±�־λ,��λ�ڷ��������¼�ʱͨ��Ӳ���� 1,����Ҫͨ���������
	TIM6->SR = 0;
	//CR1��bit3(OPM)��һ,�������ڷ�����һ�����¼�ʱֹͣ����,������ģʽ
	TIM6->CR1 |= (1<<3);
	//CR1��bit0(CEN)��һ,������ʱ����ʼ����
	TIM6->CR1 |= (1<<0);
	//�ȴ������¼�����,��������ֵ�������Զ���װ�ؼĴ�����ʱ��,����������¼�,��ʱ��ʱʱ���ѵ�
	while((TIM6->SR & 0x01)==0);
	//������±�־λ,��λ�ڷ��������¼�ʱͨ��Ӳ���� 1,����Ҫͨ���������
	TIM6->SR &= ~(1<<0);
}

/* TIM5 init function */
void MX_TIM5_Init(void)
{

  /* USER CODE BEGIN TIM5_Init 0 */

  /* USER CODE END TIM5_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
//  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM5_Init 1 */

  /* USER CODE END TIM5_Init 1 */
  htim5.Instance = TIM5;
  htim5.Init.Prescaler = 23;
  htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim5.Init.Period = 10000;
  htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim5) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim5, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim5) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
//  sConfigOC.OCMode = TIM_OCMODE_PWM1;
//  sConfigOC.Pulse = 10000;
//  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
//  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
//  if (HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  sConfigOC.Pulse = 5000;
//  if (HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  if (HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  if (HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
//  {
//    Error_Handler();
//  }
  /* USER CODE BEGIN TIM5_Init 2 */

  /* USER CODE END TIM5_Init 2 */
  HAL_TIM_MspPostInit(&htim5);

}

/* TIM6 init function */
void MX_TIM6_Init_Backup(void)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 6000 - 1;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 1000;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_OnePulse_Init(&htim6, TIM_OPMODE_SINGLE) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
}

void MX_TIM7_Init(void)
{

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  
  htim7.Instance = TIM7;
  htim7.Init.Prescaler = 0;
  htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim7.Init.Period = 65535;
  htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim7) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_OnePulse_Init(&htim7, TIM_OPMODE_SINGLE) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM5)
  {
  /* USER CODE BEGIN TIM5_MspInit 0 */

  /* USER CODE END TIM5_MspInit 0 */
    /* TIM5 clock enable */
    __HAL_RCC_TIM5_CLK_ENABLE();
  /* USER CODE BEGIN TIM5_MspInit 1 */

  /* USER CODE END TIM5_MspInit 1 */
  }
  else if(tim_baseHandle->Instance==TIM6)
  {
  /* USER CODE BEGIN TIM6_MspInit 0 */

  /* USER CODE END TIM6_MspInit 0 */
    /* TIM6 clock enable */
    __HAL_RCC_TIM6_CLK_ENABLE();

    /* TIM6 interrupt Init */
    HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
  /* USER CODE BEGIN TIM6_MspInit 1 */

  /* USER CODE END TIM6_MspInit 1 */
  }
  else if(tim_baseHandle->Instance==TIM7)
  {
    /* USER CODE BEGIN TIM7_MspInit 0 */
    
    /* USER CODE END TIM7_MspInit 0 */
    /* TIM7 clock enable */
    __HAL_RCC_TIM7_CLK_ENABLE();
    /* USER CODE BEGIN TIM7_MspInit 1 */
    
    /* USER CODE END TIM7_MspInit 1 */
  }
}
void HAL_TIM_MspPostInit(TIM_HandleTypeDef* timHandle)
{

//  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(timHandle->Instance==TIM5)
  {
  /* USER CODE BEGIN TIM5_MspPostInit 0 */

  /* USER CODE END TIM5_MspPostInit 0 */

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**TIM5 GPIO Configuration
    PA0     ------> TIM5_CH1
    PA1     ------> TIM5_CH2
    PA2     ------> TIM5_CH3
    PA3     ------> TIM5_CH4
    */
//    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
//    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//    GPIO_InitStruct.Alternate = GPIO_AF2_TIM5;
//    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN TIM5_MspPostInit 1 */

  /* USER CODE END TIM5_MspPostInit 1 */
  }

}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM5)
  {
  /* USER CODE BEGIN TIM5_MspDeInit 0 */

  /* USER CODE END TIM5_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM5_CLK_DISABLE();
  /* USER CODE BEGIN TIM5_MspDeInit 1 */

  /* USER CODE END TIM5_MspDeInit 1 */
  }
  else if(tim_baseHandle->Instance==TIM6)
  {
  /* USER CODE BEGIN TIM6_MspDeInit 0 */

  /* USER CODE END TIM6_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM6_CLK_DISABLE();

    /* TIM6 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM6_DAC_IRQn);
  /* USER CODE BEGIN TIM6_MspDeInit 1 */

  /* USER CODE END TIM6_MspDeInit 1 */
  }
  else if(tim_baseHandle->Instance==TIM7)
  {
    /* USER CODE BEGIN TIM7_MspDeInit 0 */
    
    /* USER CODE END TIM7_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM7_CLK_DISABLE();
    /* USER CODE BEGIN TIM7_MspDeInit 1 */
    
    /* USER CODE END TIM7_MspDeInit 1 */
  }
}