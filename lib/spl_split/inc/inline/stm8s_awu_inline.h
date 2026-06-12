#ifndef __STM8S_AWU_INLINE_H
#define __STM8S_AWU_INLINE_H

#include "private/stm8s_awu_private.h"
#include "stm8s_awu.h"

/**
 * @addtogroup AWU_Public_Functions
 * @{
 */

/**
 * @brief  Deinitializes the AWU peripheral registers to their default reset
 * values.
 * @param  None
 * @retval None
 */
inline void AWU_DeInit_inline(void) {
  AWU->CSR = AWU_CSR_RESET_VALUE;
  AWU->APR = AWU_APR_RESET_VALUE;
  AWU->TBR = AWU_TBR_RESET_VALUE;
}

/**
 * @brief  Initializes the AWU peripheral according to the specified parameters.
 * @param   AWU_TimeBase : Time base selection (interval between AWU
 * interrupts). can be one of the values of @ref AWU_Timebase_TypeDef.
 * @retval None
 * @par Required preconditions:
 * The LS RC calibration must be performed before calling this function.
 */
inline void AWU_Init_inline(AWU_Timebase_TypeDef AWU_TimeBase) {
  /* Check parameter */
  assert_param(IS_AWU_TIMEBASE_OK(AWU_TimeBase));

  /* Enable the AWU peripheral */
  AWU->CSR |= AWU_CSR_AWUEN;

  /* Set the TimeBase */
  AWU->TBR &= (uint8_t)(~AWU_TBR_AWUTB);
  AWU->TBR |= TBR_Array[(uint8_t)AWU_TimeBase];

  /* Set the APR divider */
  AWU->APR &= (uint8_t)(~AWU_APR_APR);
  AWU->APR |= APR_Array[(uint8_t)AWU_TimeBase];
}

/**
 * @brief  Enable or disable the AWU peripheral.
 * @param   NewState Indicates the new state of the AWU peripheral.
 * @retval None
 * @par Required preconditions:
 * Initialisation of AWU and LS RC calibration must be done before.
 */
inline void AWU_Cmd_inline(FunctionalState NewState) {
  if (NewState != DISABLE) {
    /* Enable the AWU peripheral */
    AWU->CSR |= AWU_CSR_AWUEN;
  } else {
    /* Disable the AWU peripheral */
    AWU->CSR &= (uint8_t)(~AWU_CSR_AWUEN);
  }
}

/**
 * @brief  Update APR register with the measured LSI frequency.
 * @par Note on the APR calculation:
 * A is the integer part of lsifreqkhz/4 and x the decimal part.
 * x <= A/(1+2A) is equivalent to A >= x(1+2A) and also to 4A >= 4x(1+2A) [F1]
 * but we know that A + x = lsifreqkhz/4 ==> 4x = lsifreqkhz-4A
 * so [F1] can be written :
 * 4A >= (lsifreqkhz-4A)(1+2A)
 * @param   LSIFreqHz Low Speed RC frequency measured by timer (in Hz).
 * @retval None
 * @par Required preconditions:
 * - AWU must be disabled to avoid unwanted interrupts.
 */
inline void AWU_LSICalibrationConfig_inline(uint32_t LSIFreqHz) {
  uint16_t lsifreqkhz = 0x0;
  uint16_t A = 0x0;

  /* Check parameter */
  assert_param(IS_LSI_FREQUENCY_OK(LSIFreqHz));

  lsifreqkhz = (uint16_t)(LSIFreqHz / 1000); /* Converts value in kHz */

  /* Calculation of AWU calibration value */

  A = (uint16_t)(lsifreqkhz >> 2U); /* Division by 4, keep integer part only */

  if ((4U * A) >= ((lsifreqkhz - (4U * A)) * (1U + (2U * A)))) {
    AWU->APR = (uint8_t)(A - 2U);
  } else {
    AWU->APR = (uint8_t)(A - 1U);
  }
}

/**
 * @brief  Configures AWU in Idle mode to reduce power consumption.
 * @param  None
 * @retval None
 */
inline void AWU_IdleModeEnable_inline(void) {
  /* Disable AWU peripheral */
  AWU->CSR &= (uint8_t)(~AWU_CSR_AWUEN);

  /* No AWU timebase */
  AWU->TBR = (uint8_t)(~AWU_TBR_AWUTB);
}

/**
 * @brief  Returns status of the AWU peripheral flag.
 * @param  None
 * @retval FlagStatus : Status of the AWU flag.
 * This parameter can be any of the @ref FlagStatus enumeration.
 */
inline FlagStatus AWU_GetFlagStatus_inline(void) {
  return ((FlagStatus)(((uint8_t)(AWU->CSR & AWU_CSR_AWUF) == (uint8_t)0x00)
                           ? RESET
                           : SET));
}

#endif
