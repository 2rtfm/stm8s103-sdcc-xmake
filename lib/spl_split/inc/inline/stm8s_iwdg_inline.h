#ifndef __STM8S_IWDG_INLINE_H
#define __STM8S_IWDG_INLINE_H

#include "stm8s_iwdg.h"

/**
 * @brief  Enables or disables write access to Prescaler and Reload registers.
 * @param  IWDG_WriteAccess : New state of write access to Prescaler and Reload
 *         registers.  This parameter can be a value of @ref
 * IWDG_WriteAccess_TypeDef.
 * @retval None
 */
inline void
IWDG_WriteAccessCmd_inline(IWDG_WriteAccess_TypeDef IWDG_WriteAccess) {
  /* Check the parameters */
  assert_param(IS_IWDG_WRITEACCESS_MODE_OK(IWDG_WriteAccess));

  IWDG->KR = (uint8_t)IWDG_WriteAccess; /* Write Access */
}

/**
 * @brief  Sets IWDG Prescaler value.
 * @note   Write access should be enabled
 * @param  IWDG_Prescaler : Specifies the IWDG Prescaler value.
 *         This parameter can be a value of @ref IWDG_Prescaler_TypeDef.
 * @retval None
 */
inline void IWDG_SetPrescaler_inline(IWDG_Prescaler_TypeDef IWDG_Prescaler) {
  /* Check the parameters */
  assert_param(IS_IWDG_PRESCALER_OK(IWDG_Prescaler));

  IWDG->PR = (uint8_t)IWDG_Prescaler;
}

/**
 * @brief  Sets IWDG Reload value.
 * @note   Write access should be enabled
 * @param  IWDG_Reload : Reload register value.
 *         This parameter must be a number between 0 and 0xFF.
 * @retval None
 */
inline void IWDG_SetReload_inline(uint8_t IWDG_Reload) {
  IWDG->RLR = IWDG_Reload;
}

/**
 * @brief  Reloads IWDG counter
 * @note   Write access should be enabled
 * @param  None
 * @retval None
 */
inline void IWDG_ReloadCounter_inline(void) { IWDG->KR = IWDG_KEY_REFRESH; }

/**
 * @brief  Enables IWDG.
 * @param  None
 * @retval None
 */
inline void IWDG_Enable_inline(void) { IWDG->KR = IWDG_KEY_ENABLE; }

#endif
