/**
 ******************************************************************************
 * @file    stm8s_flash_ReadByte.c
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
 * @brief  Reads any byte from flash memory
 * @note   PointerAttr define is declared in the stm8s.h file to select if
 *         the pointer will be declared as near (2 bytes) or far (3 bytes).
 * @param  Address : Address to read
 * @retval Value of the byte
 */
uint8_t FLASH_ReadByte(uint32_t Address) {
  /* Check parameter */
  assert_param(IS_FLASH_ADDRESS_OK(Address));

  /* Read byte */
  return (*(PointerAttr uint8_t *)(MemoryAddressCast)Address);
}

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
