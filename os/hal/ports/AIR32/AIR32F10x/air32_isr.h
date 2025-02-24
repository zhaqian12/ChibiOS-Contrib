/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/**
 * @file    AIR32F10x/air32_isr.h
 * @brief   AIR32F10x ISR handler header.
 *
 * @addtogroup AIR32F1xx_ISR
 * @{
 */

#ifndef AIR32_ISR_H
#define AIR32_ISR_H

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @name    ISR names and numbers remapping
 * @{
 */
/*
 * CAN units.
 */
#define AIR32_CAN1_TX_HANDLER       Vector8C
#define AIR32_CAN1_RX0_HANDLER      Vector90
#define AIR32_CAN1_RX1_HANDLER      Vector94
#define AIR32_CAN1_SCE_HANDLER      Vector98

#define AIR32_CAN1_TX_NUMBER        19
#define AIR32_CAN1_RX0_NUMBER       20
#define AIR32_CAN1_RX1_NUMBER       21
#define AIR32_CAN1_SCE_NUMBER       22

/*
 * I2C units.
 */
#define AIR32_I2C1_EVENT_HANDLER    VectorBC
#define AIR32_I2C1_ERROR_HANDLER    VectorC0
#define AIR32_I2C1_EVENT_NUMBER     31
#define AIR32_I2C1_ERROR_NUMBER     32

#define AIR32_I2C2_EVENT_HANDLER    VectorC4
#define AIR32_I2C2_ERROR_HANDLER    VectorC8
#define AIR32_I2C2_EVENT_NUMBER     33
#define AIR32_I2C2_ERROR_NUMBER     34

/*
 * SDIO unit.
 */
#define AIR32_SDIO_HANDLER          Vector104

#define AIR32_SDIO_NUMBER           49

/*
 * TIM units.
 */
#define AIR32_TIM1_UP_HANDLER       VectorA4
#define AIR32_TIM1_CC_HANDLER       VectorAC
#define AIR32_TIM2_HANDLER          VectorB0
#define AIR32_TIM3_HANDLER          VectorB4
#define AIR32_TIM4_HANDLER          VectorB8
#define AIR32_TIM5_HANDLER          Vector108
#define AIR32_TIM6_HANDLER          Vector118
#define AIR32_TIM7_HANDLER          Vector11C
#define AIR32_TIM8_UP_HANDLER       VectorF0
#define AIR32_TIM8_CC_HANDLER       VectorF8
#define AIR32_TIM9_HANDLER          VectorA0 /* Note: same as AIR32_TIM1_BRK */
#define AIR32_TIM10_HANDLER         VectorA4 /* Note: same as AIR32_TIM1_UP */
#define AIR32_TIM11_HANDLER         VectorA8 /* Note: same as AIR32_TIM1_TRG_COM */
#define AIR32_TIM12_HANDLER         VectorEC /* Note: same as AIR32_TIM8_BRK */
#define AIR32_TIM13_HANDLER         VectorF0 /* Note: same as AIR32_TIM8_UP */
#define AIR32_TIM14_HANDLER         VectorF4 /* Note: same as AIR32_TIM8_TRG_COM */

#define AIR32_TIM1_UP_NUMBER        25
#define AIR32_TIM1_CC_NUMBER        27
#define AIR32_TIM2_NUMBER           28
#define AIR32_TIM3_NUMBER           29
#define AIR32_TIM4_NUMBER           30
#define AIR32_TIM5_NUMBER           50
#define AIR32_TIM6_NUMBER           54
#define AIR32_TIM7_NUMBER           55
#define AIR32_TIM8_UP_NUMBER        44
#define AIR32_TIM8_CC_NUMBER        46
#define AIR32_TIM9_NUMBER           24 /* Note: same as AIR32_TIM1_BRK */
#define AIR32_TIM10_NUMBER          25 /* Note: same as AIR32_TIM1_UP */
#define AIR32_TIM11_NUMBER          26 /* Note: same as AIR32_TIM1_TRG_COM */
#define AIR32_TIM12_NUMBER          43 /* Note: same as AIR32_TIM8_BRK */
#define AIR32_TIM13_NUMBER          44 /* Note: same as AIR32_TIM8_UP */
#define AIR32_TIM14_NUMBER          45 /* Note: same as AIR32_TIM8_TRG_COM */

/*
 * USART units.
 */
#define AIR32_USART1_HANDLER        VectorD4
#define AIR32_USART2_HANDLER        VectorD8
#define AIR32_USART3_HANDLER        VectorDC
#define AIR32_UART4_HANDLER         Vector110
#define AIR32_UART5_HANDLER         Vector114

#define AIR32_USART1_NUMBER         37
#define AIR32_USART2_NUMBER         38
#define AIR32_USART3_NUMBER         39
#define AIR32_UART4_NUMBER          52
#define AIR32_UART5_NUMBER          53

/*
 * USB units.
 */
#define AIR32_USB1_HP_HANDLER       Vector8C
#define AIR32_USB1_LP_HANDLER       Vector90

#define AIR32_USB1_HP_NUMBER        19
#define AIR32_USB1_LP_NUMBER        20

/*
 * RTC unit
 */
#define AIR32_RTC1_HANDLER          Vector4C

#define AIR32_RTC1_NUMBER           3
/** @} */

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    Configuration options
 * @{
 */
/**
 * @brief   EXTI0 interrupt priority level setting.
 */
#if !defined(AIR32_IRQ_EXTI0_PRIORITY) || defined(__DOXYGEN__)
#define AIR32_IRQ_EXTI0_PRIORITY            3
#endif

/**
 * @brief   EXTI1 interrupt priority level setting.
 */
#if !defined(AIR32_IRQ_EXTI1_PRIORITY) || defined(__DOXYGEN__)
#define AIR32_IRQ_EXTI1_PRIORITY            3
#endif

/**
 * @brief   EXTI2 interrupt priority level setting.
 */
#if !defined(AIR32_IRQ_EXTI2_PRIORITY) || defined(__DOXYGEN__)
#define AIR32_IRQ_EXTI2_PRIORITY            3
#endif

/**
 * @brief   EXTI3 interrupt priority level setting.
 */
#if !defined(AIR32_IRQ_EXTI3_PRIORITY) || defined(__DOXYGEN__)
#define AIR32_IRQ_EXTI3_PRIORITY            3
#endif

/**
 * @brief   EXTI4 interrupt priority level setting.
 */
#if !defined(AIR32_IRQ_EXTI4_PRIORITY) || defined(__DOXYGEN__)
#define AIR32_IRQ_EXTI4_PRIORITY            3
#endif

/**
 * @brief   EXTI9..5 interrupt priority level setting.
 */
#if !defined(AIR32_IRQ_EXTI5_9_PRIORITY) || defined(__DOXYGEN__)
#define AIR32_IRQ_EXTI5_9_PRIORITY          3
#endif

/**
 * @brief   EXTI15..10 interrupt priority level setting.
 */
#if !defined(AIR32_IRQ_EXTI10_15_PRIORITY) || defined(__DOXYGEN__)
#define AIR32_IRQ_EXTI10_15_PRIORITY        3
#endif
/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
  void irqInit(void);
  void irqDeinit(void);
#ifdef __cplusplus
}
#endif

#endif /* AIR32_ISR_H */

/** @} */
