#ifndef __STM8S_RST_INLINE_H
#define __STM8S_RST_INLINE_H

#include "stm8s_rst.h"

/**
 * @brief   Checks whether the specified RST flag is set or not.
 * @param   RST_Flag : specify the reset flag to check.
 *          This parameter can be a value of @ref RST_Flag_TypeDef.
 * @retval  FlagStatus: status of the given RST flag.
 */
inline FlagStatus RST_GetFlagStatus_inline(RST_Flag_TypeDef RST_Flag) {
  /* Check the parameters */
  assert_param(IS_RST_FLAG_OK(RST_Flag));

  /* Get flag status */
  return ((FlagStatus)(((uint8_t)(RST->SR & RST_Flag) == (uint8_t)0x00) ? RESET
                                                                        : SET));
}

/**
 * @brief  Clears the specified RST flag.
 * @param  RST_Flag : specify the reset flag to clear.
 *         This parameter can be a value of @ref RST_Flag_TypeDef.
 * @retval None
 */
inline void RST_ClearFlag_inline(RST_Flag_TypeDef RST_Flag) {
  /* Check the parameters */
  assert_param(IS_RST_FLAG_OK(RST_Flag));

  RST->SR = (uint8_t)RST_Flag;
}

#endif
