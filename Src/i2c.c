/**
  ******************************************************************************
  * File Name          : I2C.c
  * Description        : This file provides code for the configuration
  *                      of the I2C instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "i2c.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

I2C_HandleTypeDef hi2c1;

/* I2C1 init function */
void MX_I2C1_Init(void)
{

  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_I2C_MspInit(I2C_HandleTypeDef* i2cHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(i2cHandle->Instance==I2C1)
  {
  /* USER CODE BEGIN I2C1_MspInit 0 */

  /* USER CODE END I2C1_MspInit 0 */
  
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**I2C1 GPIO Configuration    
    PB6     ------> I2C1_SCL
    PB7     ------> I2C1_SDA 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* I2C1 clock enable */
    __HAL_RCC_I2C1_CLK_ENABLE();
  /* USER CODE BEGIN I2C1_MspInit 1 */

  /* USER CODE END I2C1_MspInit 1 */
  }
}

void HAL_I2C_MspDeInit(I2C_HandleTypeDef* i2cHandle)
{

  if(i2cHandle->Instance==I2C1)
  {
  /* USER CODE BEGIN I2C1_MspDeInit 0 */

  /* USER CODE END I2C1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_I2C1_CLK_DISABLE();
  
    /**I2C1 GPIO Configuration    
    PB6     ------> I2C1_SCL
    PB7     ------> I2C1_SDA 
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6|GPIO_PIN_7);

  /* USER CODE BEGIN I2C1_MspDeInit 1 */

  /* USER CODE END I2C1_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */
/**
  * @brief  Manages error callback by re-initializing I2C.
  * @param  Addr: I2C Address
  * @retval None
  */
//static void I2Cx_Error(uint8_t Addr)
//{
//	/* �ָ�I2C�Ĵ���ΪĬ��ֵ */
//	HAL_I2C_DeInit(&hi2c1); 
//	/* ���³�ʼ��I2C���� */
//	MX_I2C1_Init();
//	HAL_I2C_MspDeInit(&hi2c1);
//	
//}
///**
//  * @brief  д�Ĵ����������ṩ���ϲ�Ľӿ�
//	* @param  slave_addr: �ӻ���ַ
//	* @param 	reg_addr:�Ĵ�����ַ
//	* @param len��д��ĳ���
//	*	@param data_ptr:ָ��Ҫд�������
//  * @retval ����Ϊ0��������Ϊ��0
//  */
//int Sensors_I2C_WriteRegister(unsigned char slave_addr,
//                                        unsigned char reg_addr,
//                                        unsigned short len, 
//                                        unsigned char *data_ptr)
//{
//	HAL_StatusTypeDef status = HAL_OK;
//	status = HAL_I2C_Mem_Write(&hi2c1, slave_addr, reg_addr, I2C_MEMADD_SIZE_8BIT,data_ptr, len,I2Cx_FLAG_TIMEOUT); 
//	/* ���ͨѶ״̬ */
//	if(status != HAL_OK)
//	{
//		/* ���߳������� */
//		I2Cx_Error(slave_addr);
//	}
//	while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY)
//	{
//		
//	}
//	/* ���SENSOR�Ƿ����������һ�ζ�д���� */
//	while (HAL_I2C_IsDeviceReady(&hi2c1, slave_addr, I2Cx_FLAG_TIMEOUT, I2Cx_FLAG_TIMEOUT) == HAL_TIMEOUT);
//	
//	/* �ȴ�������� */
//	while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY)
//	{
//		
//	}
//	return status;
//}

///**
//  * @brief  ���Ĵ����������ṩ���ϲ�Ľӿ�
//	* @param  slave_addr: �ӻ���ַ
//	* @param 	reg_addr:�Ĵ�����ַ
//	* @param len��Ҫ��ȡ�ĳ���
//	*	@param data_ptr:ָ��Ҫ�洢���ݵ�ָ��
//  * @retval ����Ϊ0��������Ϊ��0
//  */
//int Sensors_I2C_ReadRegister(unsigned char slave_addr,
//                                       unsigned char reg_addr,
//                                       unsigned short len, 
//                                       unsigned char *data_ptr)
//{
//	HAL_StatusTypeDef status = HAL_OK;
//	status =HAL_I2C_Mem_Read(&hi2c1,slave_addr,reg_addr,I2C_MEMADD_SIZE_8BIT,data_ptr,len,I2Cx_FLAG_TIMEOUT);    
//	/* ���ͨѶ״̬ */
//	if(status != HAL_OK)
//	{
//		/* ���߳������� */
//		I2Cx_Error(slave_addr);
//	}
//	while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY)
//	{
//		
//	}
//	/* ���SENSOR�Ƿ����������һ�ζ�д���� */
//	while (HAL_I2C_IsDeviceReady(&hi2c1, slave_addr, I2Cx_FLAG_TIMEOUT, I2Cx_FLAG_TIMEOUT) == HAL_TIMEOUT);
//	/* �ȴ�������� */
//	while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY)
//	{
//		
//	}
//	return status;
//}

/* USER CODE BEGIN 1 */
int Sensors_I2C_WriteRegister(unsigned char slave_addr,
                                        unsigned char reg_addr,
                                       unsigned short len, 
                                        unsigned char *data_ptr)
{
	return HAL_I2C_Mem_Write(&hi2c1, slave_addr, reg_addr, I2C_MEMADD_SIZE_8BIT,data_ptr, len,I2Cx_FLAG_TIMEOUT); 
}

int Sensors_I2C_ReadRegister(unsigned char slave_addr,
                                      unsigned char reg_addr,
                                       unsigned short len, 
                                       unsigned char *data_ptr)
{
	return HAL_I2C_Mem_Read(&hi2c1,slave_addr,reg_addr,I2C_MEMADD_SIZE_8BIT,data_ptr,len,I2Cx_FLAG_TIMEOUT);    
}
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/