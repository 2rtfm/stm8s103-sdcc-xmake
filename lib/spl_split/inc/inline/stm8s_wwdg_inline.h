#ifndef __STM8S_WWDG_INLINE_H
#define __STM8S_WWDG_INLINE_H

#include "private/stm8s_wwdg_private.h"
#include "stm8s_wwdg.h"

/**
 * @brief  Initializes the WWDG peripheral.
 *         This function set Window Register = WindowValue, Counter Register
 *         according to Counter and \b ENABLE \b WWDG
 * @param  Counter : WWDG counter value
 * @param  WindowValue : specifies the WWDG Window Register, range is 0x00 to
 * 0x7F.
 * @retval None
 */
inline void WWDG_Init_inline(uint8_t Counter, uint8_t WindowValue) {
  /* Check the parameters */
  assert_param(IS_WWDG_WINDOWLIMITVALUE_OK(WindowValue));

  WWDG->WR = WWDG_WR_RESET_VALUE;
  WWDG->CR = (uint8_t)((uint8_t)(WWDG_CR_WDGA | WWDG_CR_T6) | (uint8_t)Counter);
  WWDG->WR =
      (uint8_t)((uint8_t)(~WWDG_CR_WDGA) & (uint8_t)(WWDG_CR_T6 | WindowValue));
}

/**
 * @brief  Refreshes the WWDG peripheral.
 * @param  Counter :  WWDG Counter Value
 *         This parameter must be a number between 0x40 and 0x7F.
 * @retval None
 */
inline void WWDG_SetCounter_inline(uint8_t Counter) {
  /* Check the parameters */
  assert_param(IS_WWDG_COUNTERVALUE_OK(Counter));

  /* Write to T[6:0] bits to configure the counter value, no need to do
  a read-modify-write; writing a 0 to WDGA bit does nothing */
  WWDG->CR = (uint8_t)(Counter & (uint8_t)BIT_MASK);
}

/**
 * @brief Gets the WWDG Counter Value.
 *        This value could be used to check if WWDG is in the window, where
 *        refresh is allowed.
 * @param  None
 * @retval WWDG Counter Value
 */
inline uint8_t WWDG_GetCounter_inline(void) { return (WWDG->CR); }

/**
 * @brief  Generates immediate WWDG RESET.
 * @param  None
 * @retval None
 */
inline void WWDG_SWReset_inline(void) {
  WWDG->CR = WWDG_CR_WDGA; /* Activate WWDG, with clearing T6 */
}

/**
 * @brief  Sets the WWDG window value.
 * @param  WindowValue: specifies the window value to be compared to the
 *         downcounter.
 *         This parameter value must be lower than 0x80.
 * @retval None
 */
inline void WWDG_SetWindowValue_inline(uint8_t WindowValue) {
  /* Check the parameters */
  assert_param(IS_WWDG_WINDOWLIMITVALUE_OK(WindowValue));

  WWDG->WR =
      (uint8_t)((uint8_t)(~WWDG_CR_WDGA) & (uint8_t)(WWDG_CR_T6 | WindowValue));
}

#endif
