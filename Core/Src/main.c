/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "fatfs.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "flash.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
extern char USERPath[4];
		int r;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
FATFS   fs;            /* FATFS 文件系统对象 */
FRESULT fr;         /* FATFS API 返回值 */
FIL     fd;         /* FATFS 文件对象    */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void mount_disk(void)
{
  uint8_t res = f_mount(&fs, USERPath, 0);
  if (res != FR_OK)
  {
    printf("FAILED: %d\n",res);
   return;
 }
  printf("MOUNT OK\n");
}
 
void format_disk(void)
{
  uint8_t res = 0;
	char buffer[1024];
  printf("PROCESSING...\n");
  res = f_mkfs(USERPath, 1, 4096,buffer,2);

  if (res == FR_OK)
  {
    printf("OK!\n");
  }
  else
  {
    printf("failed with: %d\n",res);
  }
}
 
void create_file(void)
{
  FIL file;
  FIL *pf = &file;
  uint8_t res;
	
  res = f_open(pf, "0:/test.txt", FA_OPEN_ALWAYS | FA_WRITE);
  if (res == FR_OK)
  {
    printf("creat ok\n"); 				
  }
  else
  {
    printf("creat failed\n");
    printf("error code: %d\n",res);	
  }
  
  f_printf(pf, "hello fatfs!\n");
  
  res = f_close(pf);
    if (res != FR_OK)
    {
      printf("close file error\n");
      printf("error code: %d\n",res);				
    }
}
 
void get_disk_info(void)
{
	FATFS fs;
	FATFS *fls = &fs;
	FRESULT res;
	DWORD fre_clust;	
 
	res = f_getfree("/",&fre_clust,&fls);         /* Get Number of Free Clusters */
	if (res == FR_OK) 
	{
	                                             /* Print free space in unit of MB (assuming 4096 bytes/sector) */
        printf("%d KB Total Drive Space.\n"
               "%d KB Available Space.\n",
               ((fls->n_fatent-2)*fls->csize)*4,(fre_clust*fls->csize)*4);
	}
	else
	{
		printf("get disk info error\n");
		printf("error code: %d\n",res);
	}																									   
}
 
void read_file(void)
{
  FIL file;
  FRESULT res;
  UINT bw;
  uint8_t rbuf[100] = {0};
  
  res = f_open(&file, "0:/test.txt", FA_READ);
  if (res != FR_OK)
  {
    printf("open error: %d\n",res);
    return;
  }
  f_read(&file, rbuf, 20, &bw);
  printf("%s\n", rbuf);
  
  res = f_close(&file);
  if (res != FR_OK)
  {
     printf("close file error\n");
     printf("error code: %d\n",res);				
  }
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
		uint16_t device_id;
		uint8_t read_buf[10] = {0};
		uint8_t write_buf[10] = {0};
		int i;

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  MX_FATFS_Init();
  /* USER CODE BEGIN 2 */
//    printf("W25Q64 SPI Flash Test By Mculover666\r\n");
//    device_id = W25QXX_ReadID();
//    printf("W25Q64 Device ID is 0x%04x\r\n", device_id);

//    /* 为了验证，首先读取要写入地址处的数据 */
//    printf("-------- read data before write -----------\r\n");
//    W25QXX_Read(read_buf, 0, 10);

//    for (i = 0;i < 10;i++) {
//        printf("[0x%08x]:0x%02x\r\n", i, *(read_buf+i));
//    }

//    /* 擦除该扇区 */
//    printf("-------- erase sector 0 -----------\r\n");
//    W25QXX_Erase_Sector(0);

//    /* 再次读数据 */
//    printf("-------- read data after erase -----------\r\n");
//    W25QXX_Read(read_buf, 0, 10);
//    for (i = 0;i < 10;i++) {
//        printf("[0x%08x]:0x%02x\r\n", i, *(read_buf+i));
//    }

//    /* 写数据 */
//    printf("-------- write data -----------\r\n");
//    for (i = 0; i < 10;i++) {
//        write_buf[i] = i;
//    }
//    W25QXX_Page_Program(write_buf, 0, 10);

//    /* 再次读数据 */
//    printf("-------- read data after write -----------\r\n");
//    W25QXX_Read(read_buf, 0, 10);
//    for (i = 0;i < 10;i++) {
//        printf("[0x%08x]:0x%02x\r\n", i, *(read_buf+i));}
//W25QXX_Erase_Sector(0);
mount_disk();
format_disk();

//for(r=0;r<2048;r++)
// W25QXX_Erase_Sector(r);
 
create_file();
	get_disk_info();
		read_file();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
