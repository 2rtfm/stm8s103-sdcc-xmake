#ifndef __STM8S_GPIO_INLINE_H
#define __STM8S_GPIO_INLINE_H

#include "stm8s_gpio.h"

/**
 * @brief  Deinitializes the GPIOx peripheral registers to their default reset
 * values.
 * @param  GPIOx: Select the GPIO peripheral number (x = A to I).
 * @retval None
 */
inline void GPIO_DeInit_inline(GPIO_TypeDef *GPIOx) {
  GPIOx->ODR = GPIO_ODR_RESET_VALUE; /* Reset Output Data Register */
  GPIOx->DDR = GPIO_DDR_RESET_VALUE; /* Reset Data Direction Register */
  GPIOx->CR1 = GPIO_CR1_RESET_VALUE; /* Reset Control Register 1 */
  GPIOx->CR2 = GPIO_CR2_RESET_VALUE; /* Reset Control Register 2 */
}

/**
 * @brief  Initializes the GPIOx according to the specified parameters.
 * @param  GPIOx : Select the GPIO peripheral number (x = A to I).
 * @param  GPIO_Pin : This parameter contains the pin number, it can be any
 * value of the @ref GPIO_Pin_TypeDef enumeration.
 * @param  GPIO_Mode : This parameter can be a value of the
 *         @ref GPIO_Mode_TypeDef enumeration.
 * @retval None
 */

inline void GPIO_Init_inline(GPIO_TypeDef *GPIOx, GPIO_Pin_TypeDef GPIO_Pin,
                             GPIO_Mode_TypeDef GPIO_Mode) {
  /*----------------------*/
  /* Check the parameters */
  /*----------------------*/

  assert_param(IS_GPIO_MODE_OK(GPIO_Mode));
  assert_param(IS_GPIO_PIN_OK(GPIO_Pin));

  /* Reset corresponding bit to GPIO_Pin in CR2 register */
  GPIOx->CR2 &= (uint8_t)(~(GPIO_Pin));

  /*-----------------------------*/
  /* Input/Output mode selection */
  /*-----------------------------*/

  if ((((uint8_t)(GPIO_Mode)) & (uint8_t)0x80) !=
      (uint8_t)0x00) /* Output mode */
  {
    if ((((uint8_t)(GPIO_Mode)) & (uint8_t)0x10) !=
        (uint8_t)0x00) /* High level */
    {
      GPIOx->ODR |= (uint8_t)GPIO_Pin;
    } else /* Low level */
    {
      GPIOx->ODR &= (uint8_t)(~(GPIO_Pin));
    }
    /* Set Output mode */
    GPIOx->DDR |= (uint8_t)GPIO_Pin;
  } else /* Input mode */
  {
    /* Set Input mode */
    GPIOx->DDR &= (uint8_t)(~(GPIO_Pin));
  }

  /*------------------------------------------------------------------------*/
  /* Pull-Up/Float (Input) or Push-Pull/Open-Drain (Output) modes selection */
  /*------------------------------------------------------------------------*/

  if ((((uint8_t)(GPIO_Mode)) & (uint8_t)0x40) !=
      (uint8_t)0x00) /* Pull-Up or Push-Pull */
  {
    GPIOx->CR1 |= (uint8_t)GPIO_Pin;
  } else /* Float or Open-Drain */
  {
    GPIOx->CR1 &= (uint8_t)(~(GPIO_Pin));
  }

  /*-----------------------------------------------------*/
  /* Interrupt (Input) or Slope (Output) modes selection */
  /*-----------------------------------------------------*/

  if ((((uint8_t)(GPIO_Mode)) & (uint8_t)0x20) !=
      (uint8_t)0x00) /* Interrupt or Slow slope */
  {
    GPIOx->CR2 |= (uint8_t)GPIO_Pin;
  } else /* No external interrupt or No slope control */
  {
    GPIOx->CR2 &= (uint8_t)(~(GPIO_Pin));
  }
}

/**
 * @brief  Writes data to the specified GPIO data port.
 * @note   The port must be configured in output mode.
 * @param  GPIOx : Select the GPIO peripheral number (x = A to I).
 * @param  PortVal : Specifies the value to be written to the port output
 *         data register.
 * @retval None
 */
inline void GPIO_Write_inline(GPIO_TypeDef *GPIOx, uint8_t PortVal) {
  GPIOx->ODR = PortVal;
}

/**
 * @brief  Writes high level to the specified GPIO pins.
 * @note   The port must be configured in output mode.
 * @param  GPIOx : Select the GPIO peripheral number (x = A to I).
 * @param  PortPins : Specifies the pins to be turned high to the port output.
 *         data register.
 * @retval None
 */
inline void GPIO_WriteHigh_inline(GPIO_TypeDef *GPIOx,
                                  GPIO_Pin_TypeDef PortPins) {
  GPIOx->ODR |= (uint8_t)PortPins;
}

/**
 * @brief  Writes low level to the specified GPIO pins.
 * @note   The port must be configured in output mode.
 * @param  GPIOx : Select the GPIO peripheral number (x = A to I).
 * @param  PortPins : Specifies the pins to be turned low to the port output.
 *         data register.
 * @retval None
 */
inline void GPIO_WriteLow_inline(GPIO_TypeDef *GPIOx,
                                 GPIO_Pin_TypeDef PortPins) {
  GPIOx->ODR &= (uint8_t)(~PortPins);
}

/**
 * @brief  Writes reverse level to the specified GPIO pins.
 * @note   The port must be configured in output mode.
 * @param  GPIOx : Select the GPIO peripheral number (x = A to I).
 * @param  PortPins : Specifies the pins to be reversed to the port output.
 *         data register.
 * @retval None
 */
inline void GPIO_WriteReverse_inline(GPIO_TypeDef *GPIOx,
                                     GPIO_Pin_TypeDef PortPins) {
  GPIOx->ODR ^= (uint8_t)PortPins;
}

/**
 * @brief  Reads the specified GPIO output data port.
 * @note   The port must be configured in input mode.
 * @param  GPIOx : Select the GPIO peripheral number (x = A to I).
 * @retval GPIO output data port value.
 */
inline uint8_t GPIO_ReadOutputData_inline(GPIO_TypeDef *GPIOx) {
  return ((uint8_t)GPIOx->ODR);
}

/**
 * @brief  Reads the specified GPIO input data port.
 * @note   The port must be configured in input mode.
 * @param  GPIOx : Select the GPIO peripheral number (x = A to I).
 * @retval GPIO input data port value.
 */
inline uint8_t GPIO_ReadInputData_inline(GPIO_TypeDef *GPIOx) {
  return ((uint8_t)GPIOx->IDR);
}

/**
 * @brief  Reads the specified GPIO input data pin.
 * @param  GPIOx : Select the GPIO peripheral number (x = A to I).
 * @param  GPIO_Pin : Specifies the pin number.
 * @retval BitStatus : GPIO input pin status.
 */
inline BitStatus GPIO_ReadInputPin_inline(GPIO_TypeDef *GPIOx,
                                          GPIO_Pin_TypeDef GPIO_Pin) {
  return ((BitStatus)(GPIOx->IDR & (uint8_t)GPIO_Pin));
}

/**
 * @brief  Configures the external pull-up on GPIOx pins.
 * @param  GPIOx : Select the GPIO peripheral number (x = A to I).
 * @param  GPIO_Pin : Specifies the pin number
 * @param  NewState : The new state of the pull up pin.
 * @retval None
 */
inline void GPIO_ExternalPullUpConfig_inline(GPIO_TypeDef *GPIOx,
                                             GPIO_Pin_TypeDef GPIO_Pin,
                                             FunctionalState NewState) {
  /* Check the parameters */
  assert_param(IS_GPIO_PIN_OK(GPIO_Pin));
  assert_param(IS_FUNCTIONALSTATE_OK(NewState));

  if (NewState != DISABLE) /* External Pull-Up Set*/
  {
    GPIOx->CR1 |= (uint8_t)GPIO_Pin;
  } else /* External Pull-Up Reset*/
  {
    GPIOx->CR1 &= (uint8_t)(~(GPIO_Pin));
  }
}

#endif
