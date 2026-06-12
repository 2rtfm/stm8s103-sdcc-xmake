/**
 ******************************************************************************
 * @file    stm8s_flash_GetFlagStatus.c
 * @author  MCD Application Team
 * @version V2.3.0
 * @date    16-June-2017
 * @brief   This file contains all the functions for the FLASH peripheral.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
 *
 * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *        http://www.st.com/software_license_agreement_liberty_v2
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "private/stm8s_flash_private.h"
#include "stm8s_flash.h"

/** @addtogroup STM8S_StdPeriph_Driver
 * @{
 */

/** @addtogroup FLASH_Public_functions
 * @{
 */

/**
 * @brief  Checks whether the specified SPI flag is set or not.
 * @param  FLASH_FLAG : Specifies the flag to check.
 *         This parameter can be any of the @ref FLASH_Flag_TypeDef enumeration.
 * @retval FlagStatus : Indicates the state of FLASH_FLAG.
 *         This parameter can be any of the @ref FlagStatus enumeration.
 * @note   This function can clear the EOP, WR_PG_DIS flags in the IAPSR
 * register.
 */
FlagStatus FLASH_GetFlagStatus(FLASH_Flag_TypeDef FLASH_FLAG) {
  FlagStatus status = RESET;
  /* Check parameters */
  assert_param(IS_FLASH_FLAGS_OK(FLASH_FLAG));

  /* Check the status of the specified FLASH flag */
  if ((FLASH->IAPSR & (uint8_t)FLASH_FLAG) != (uint8_t)RESET) {
    status = SET; /* FLASH_FLAG is set */
  } else {
    status = RESET; /* FLASH_FLAG is reset*/
  }

  /* Return the FLASH_FLAG status */
  return status;
}

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
