/*
    ChibiOS - Copyright (C)   3006..2018 Giovanni Di Sirio

    Licensed under the Apache License, Version   3.0 (the "License");
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
 * @file    TIMv1/hal_pwm_lld.h
 * @brief   AIR32 PWM subsystem low level driver header.
 *
 * @addtogroup PWM
 * @{
 */

#ifndef HAL_PWM_LLD_H
#define HAL_PWM_LLD_H

#if HAL_USE_PWM || defined(__DOXYGEN__)

#include "air32_tim.h"

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @brief   Number of PWM channels per PWM driver.
 */
#define PWM_CHANNELS                            AIR32_TIM_MAX_CHANNELS

/**
 * @name    AIR32-specific PWM complementary output mode macros
 * @{
 */
/**
 * @brief   Complementary output modes mask.
 * @note    This is an AIR32-specific setting.
 */
#define PWM_COMPLEMENTARY_OUTPUT_MASK           0xF0

/**
 * @brief   Complementary output not driven.
 * @note    This is an AIR32-specific setting.
 */
#define PWM_COMPLEMENTARY_OUTPUT_DISABLED       0x00

/**
 * @brief   Complementary output, active is logic level one.
 * @note    This is an AIR32-specific setting.
 * @note    This setting is only available if the timer supports the
 *          BDTR register.
 */
#define PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH    0x10

/**
 * @brief   Complementary output, active is logic level zero.
 * @note    This is an AIR32-specific setting.
 * @note    This setting is only available if the timer supports the
 *          BDTR register.
 */
#define PWM_COMPLEMENTARY_OUTPUT_ACTIVE_LOW     0x20
/** @} */

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    Configuration options
 * @{
 */
/**
 * @brief   PWMD1 driver enable switch.
 * @details If set to @p TRUE the support for PWMD1 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(AIR32_PWM_USE_TIM1) || defined(__DOXYGEN__)
#define AIR32_PWM_USE_TIM1                  FALSE
#endif

/**
 * @brief   PWMD2 driver enable switch.
 * @details If set to @p TRUE the support for PWMD2 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(AIR32_PWM_USE_TIM2) || defined(__DOXYGEN__)
#define AIR32_PWM_USE_TIM2                  FALSE
#endif

/**
 * @brief   PWMD3 driver enable switch.
 * @details If set to @p TRUE the support for PWMD3 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(AIR32_PWM_USE_TIM3) || defined(__DOXYGEN__)
#define AIR32_PWM_USE_TIM3                  FALSE
#endif

/**
 * @brief   PWMD4 driver enable switch.
 * @details If set to @p TRUE the support for PWMD4 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(AIR32_PWM_USE_TIM4) || defined(__DOXYGEN__)
#define AIR32_PWM_USE_TIM4                  FALSE
#endif

/**
 * @brief   PWMD5 driver enable switch.
 * @details If set to @p TRUE the support for PWMD5 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(AIR32_PWM_USE_TIM5) || defined(__DOXYGEN__)
#define AIR32_PWM_USE_TIM5                  FALSE
#endif

/**
 * @brief   PWMD8 driver enable switch.
 * @details If set to @p TRUE the support for PWMD8 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(AIR32_PWM_USE_TIM8) || defined(__DOXYGEN__)
#define AIR32_PWM_USE_TIM8                  FALSE
#endif

/**
 * @brief   PWMD9 driver enable switch.
 * @details If set to @p TRUE the support for PWMD9 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(AIR32_PWM_USE_TIM9) || defined(__DOXYGEN__)
#define AIR32_PWM_USE_TIM9                  FALSE
#endif

/**
 * @brief   PWMD10 driver enable switch.
 * @details If set to @p TRUE the support for PWMD10 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(AIR32_PWM_USE_TIM10) || defined(__DOXYGEN__)
#define AIR32_PWM_USE_TIM10                 FALSE
#endif

/**
 * @brief   PWMD11 driver enable switch.
 * @details If set to @p TRUE the support for PWMD11 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(AIR32_PWM_USE_TIM11) || defined(__DOXYGEN__)
#define AIR32_PWM_USE_TIM11                 FALSE
#endif

/**
 * @brief   PWMD12 driver enable switch.
 * @details If set to @p TRUE the support for PWMD12 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(AIR32_PWM_USE_TIM12) || defined(__DOXYGEN__)
#define AIR32_PWM_USE_TIM12                 FALSE
#endif

/**
 * @brief   PWMD13 driver enable switch.
 * @details If set to @p TRUE the support for PWMD13 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(AIR32_PWM_USE_TIM13) || defined(__DOXYGEN__)
#define AIR32_PWM_USE_TIM13                 FALSE
#endif

/**
 * @brief   PWMD14 driver enable switch.
 * @details If set to @p TRUE the support for PWMD14 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(AIR32_PWM_USE_TIM14) || defined(__DOXYGEN__)
#define AIR32_PWM_USE_TIM14                 FALSE
#endif

/**
 * @brief   PWMD1 interrupt priority level setting.
 */
#if !defined(AIR32_PWM_TIM1_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define AIR32_PWM_TIM1_IRQ_PRIORITY          3
#endif

/**
 * @brief   PWMD2 interrupt priority level setting.
 */
#if !defined(AIR32_PWM_TIM2_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define AIR32_PWM_TIM2_IRQ_PRIORITY          3
#endif

/**
 * @brief   PWMD3 interrupt priority level setting.
 */
#if !defined(AIR32_PWM_TIM3_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define AIR32_PWM_TIM3_IRQ_PRIORITY          3
#endif

/**
 * @brief   PWMD4 interrupt priority level setting.
 */
#if !defined(AIR32_PWM_TIM4_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define AIR32_PWM_TIM4_IRQ_PRIORITY          3
#endif

/**
 * @brief   PWMD5 interrupt priority level setting.
 */
#if !defined(AIR32_PWM_TIM5_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define AIR32_PWM_TIM5_IRQ_PRIORITY          3
#endif

/**
 * @brief   PWMD8 interrupt priority level setting.
 */
#if !defined(AIR32_PWM_TIM8_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define AIR32_PWM_TIM8_IRQ_PRIORITY          3
#endif

/**
 * @brief   PWMD9 interrupt priority level setting.
 */
#if !defined(AIR32_PWM_TIM9_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define AIR32_PWM_TIM9_IRQ_PRIORITY          3
#endif

/**
 * @brief   PWMD10 interrupt priority level setting.
 */
#if !defined(AIR32_PWM_TIM10_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define AIR32_PWM_TIM10_IRQ_PRIORITY         3
#endif

/**
 * @brief   PWMD11 interrupt priority level setting.
 */
#if !defined(AIR32_PWM_TIM11_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define AIR32_PWM_TIM11_IRQ_PRIORITY         3
#endif

/**
 * @brief   PWMD12 interrupt priority level setting.
 */
#if !defined(AIR32_PWM_TIM12_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define AIR32_PWM_TIM12_IRQ_PRIORITY         3
#endif

/**
 * @brief   PWMD13 interrupt priority level setting.
 */
#if !defined(AIR32_PWM_TIM13_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define AIR32_PWM_TIM13_IRQ_PRIORITY         3
#endif

/**
 * @brief   PWMD14 interrupt priority level setting.
 */
#if !defined(AIR32_PWM_TIM14_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define AIR32_PWM_TIM14_IRQ_PRIORITY         3
#endif
/** @} */

/*===========================================================================*/
/* Configuration checks.                                                     */
/*===========================================================================*/

#if !defined(AIR32_HAS_TIM1)
#define AIR32_HAS_TIM1                      FALSE
#endif

#if !defined(AIR32_HAS_TIM2)
#define AIR32_HAS_TIM2                      FALSE
#endif

#if !defined(AIR32_HAS_TIM3)
#define AIR32_HAS_TIM3                      FALSE
#endif

#if !defined(AIR32_HAS_TIM4)
#define AIR32_HAS_TIM4                      FALSE
#endif

#if !defined(AIR32_HAS_TIM5)
#define AIR32_HAS_TIM5                      FALSE
#endif

#if !defined(AIR32_HAS_TIM8)
#define AIR32_HAS_TIM8                      FALSE
#endif

#if !defined(AIR32_HAS_TIM9)
#define AIR32_HAS_TIM9                      FALSE
#endif

#if !defined(AIR32_HAS_TIM10)
#define AIR32_HAS_TIM10                     FALSE
#endif

#if !defined(AIR32_HAS_TIM11)
#define AIR32_HAS_TIM11                     FALSE
#endif

#if !defined(AIR32_HAS_TIM12)
#define AIR32_HAS_TIM12                     FALSE
#endif

#if !defined(AIR32_HAS_TIM13)
#define AIR32_HAS_TIM13                     FALSE
#endif

#if !defined(AIR32_HAS_TIM14)
#define AIR32_HAS_TIM14                     FALSE
#endif

#if AIR32_PWM_USE_TIM1 && !AIR32_HAS_TIM1
#error "TIM1 not present in the selected device"
#endif

#if AIR32_PWM_USE_TIM2 && !AIR32_HAS_TIM2
#error "TIM2 not present in the selected device"
#endif

#if AIR32_PWM_USE_TIM3 && !AIR32_HAS_TIM3
#error "TIM3 not present in the selected device"
#endif

#if AIR32_PWM_USE_TIM4 && !AIR32_HAS_TIM4
#error "TIM4 not present in the selected device"
#endif

#if AIR32_PWM_USE_TIM5 && !AIR32_HAS_TIM5
#error "TIM5 not present in the selected device"
#endif

#if AIR32_PWM_USE_TIM8 && !AIR32_HAS_TIM8
#error "TIM8 not present in the selected device"
#endif

#if AIR32_PWM_USE_TIM9 && !AIR32_HAS_TIM9
#error "TIM9 not present in the selected device"
#endif

#if AIR32_PWM_USE_TIM10 && !AIR32_HAS_TIM10
#error "TIM10 not present in the selected device"
#endif

#if AIR32_PWM_USE_TIM11 && !AIR32_HAS_TIM11
#error "TIM11 not present in the selected device"
#endif

#if AIR32_PWM_USE_TIM12 && !AIR32_HAS_TIM12
#error "TIM12 not present in the selected device"
#endif

#if AIR32_PWM_USE_TIM13 && !AIR32_HAS_TIM13
#error "TIM13 not present in the selected device"
#endif

#if AIR32_PWM_USE_TIM14 && !AIR32_HAS_TIM14
#error "TIM14 not present in the selected device"
#endif

#if !AIR32_PWM_USE_TIM1  && !AIR32_PWM_USE_TIM2  &&                         \
    !AIR32_PWM_USE_TIM3  && !AIR32_PWM_USE_TIM4  &&                         \
    !AIR32_PWM_USE_TIM5  && !AIR32_PWM_USE_TIM8  &&                         \
    !AIR32_PWM_USE_TIM9  && !AIR32_PWM_USE_TIM10 &&                         \
    !AIR32_PWM_USE_TIM11 && !AIR32_PWM_USE_TIM12 &&                         \
    !AIR32_PWM_USE_TIM13 && !AIR32_PWM_USE_TIM14                         
#error "PWM driver activated but no TIM peripheral assigned"
#endif

/* Checks on allocation of TIMx units.*/
#if AIR32_PWM_USE_TIM1
#if defined(AIR32_TIM1_IS_USED)
#error "PWMD1 requires TIM1 but the timer is already used"
#else
#define AIR32_TIM1_IS_USED
#endif
#endif

#if AIR32_PWM_USE_TIM2
#if defined(AIR32_TIM2_IS_USED)
#error "PWMD2 requires TIM2 but the timer is already used"
#else
#define AIR32_TIM2_IS_USED
#endif
#endif

#if AIR32_PWM_USE_TIM3
#if defined(AIR32_TIM3_IS_USED)
#error "PWMD3 requires TIM3 but the timer is already used"
#else
#define AIR32_TIM3_IS_USED
#endif
#endif

#if AIR32_PWM_USE_TIM4
#if defined(AIR32_TIM4_IS_USED)
#error "PWMD4 requires TIM4 but the timer is already used"
#else
#define AIR32_TIM4_IS_USED
#endif
#endif

#if AIR32_PWM_USE_TIM5
#if defined(AIR32_TIM5_IS_USED)
#error "PWMD5 requires TIM5 but the timer is already used"
#else
#define AIR32_TIM5_IS_USED
#endif
#endif

#if AIR32_PWM_USE_TIM8
#if defined(AIR32_TIM8_IS_USED)
#error "PWMD8 requires TIM8 but the timer is already used"
#else
#define AIR32_TIM8_IS_USED
#endif
#endif

#if AIR32_PWM_USE_TIM9
#if defined(AIR32_TIM9_IS_USED)
#error "PWMD9 requires TIM9 but the timer is already used"
#else
#define AIR32_TIM9_IS_USED
#endif
#endif

#if AIR32_PWM_USE_TIM10
#if defined(AIR32_TIM10_IS_USED)
#error "PWMD10 requires TIM10 but the timer is already used"
#else
#define AIR32_TIM10_IS_USED
#endif
#endif

#if AIR32_PWM_USE_TIM11
#if defined(AIR32_TIM11_IS_USED)
#error "PWMD11 requires TIM11 but the timer is already used"
#else
#define AIR32_TIM11_IS_USED
#endif
#endif

#if AIR32_PWM_USE_TIM12
#if defined(AIR32_TIM12_IS_USED)
#error "PWMD12 requires TIM12 but the timer is already used"
#else
#define AIR32_TIM12_IS_USED
#endif
#endif

#if AIR32_PWM_USE_TIM13
#if defined(AIR32_TIM13_IS_USED)
#error "PWMD13 requires TIM13 but the timer is already used"
#else
#define AIR32_TIM13_IS_USED
#endif
#endif

#if AIR32_PWM_USE_TIM14
#if defined(AIR32_TIM14_IS_USED)
#error "PWMD14 requires TIM14 but the timer is already used"
#else
#define AIR32_TIM14_IS_USED
#endif
#endif

/* IRQ priority checks.*/
#if AIR32_PWM_USE_TIM1 && !defined(AIR32_TIM1_SUPPRESS_ISR) &&              \
    !OSAL_IRQ_IS_VALID_PRIORITY(AIR32_PWM_TIM1_IRQ_PRIORITY)
#error "Invalid IRQ priority assigned to TIM1"
#endif

#if AIR32_PWM_USE_TIM2 && !defined(AIR32_TIM2_SUPPRESS_ISR) &&              \
    !OSAL_IRQ_IS_VALID_PRIORITY(AIR32_PWM_TIM2_IRQ_PRIORITY)
#error "Invalid IRQ priority assigned to TIM2"
#endif

#if AIR32_PWM_USE_TIM3 && !defined(AIR32_TIM3_SUPPRESS_ISR) &&              \
    !OSAL_IRQ_IS_VALID_PRIORITY(AIR32_PWM_TIM3_IRQ_PRIORITY)
#error "Invalid IRQ priority assigned to TIM3"
#endif

#if AIR32_PWM_USE_TIM4 && !defined(AIR32_TIM4_SUPPRESS_ISR) &&              \
    !OSAL_IRQ_IS_VALID_PRIORITY(AIR32_PWM_TIM4_IRQ_PRIORITY)
#error "Invalid IRQ priority assigned to TIM4"
#endif

#if AIR32_PWM_USE_TIM5 && !defined(AIR32_TIM5_SUPPRESS_ISR) &&              \
    !OSAL_IRQ_IS_VALID_PRIORITY(AIR32_PWM_TIM5_IRQ_PRIORITY)
#error "Invalid IRQ priority assigned to TIM5"
#endif

#if AIR32_PWM_USE_TIM8 && !defined(AIR32_TIM8_SUPPRESS_ISR) &&              \
    !OSAL_IRQ_IS_VALID_PRIORITY(AIR32_PWM_TIM8_IRQ_PRIORITY)
#error "Invalid IRQ priority assigned to TIM8"
#endif

#if AIR32_PWM_USE_TIM9 && !defined(AIR32_TIM9_SUPPRESS_ISR) &&              \
    !OSAL_IRQ_IS_VALID_PRIORITY(AIR32_PWM_TIM9_IRQ_PRIORITY)
#error "Invalid IRQ priority assigned to TIM9"
#endif

#if AIR32_PWM_USE_TIM10 && !defined(AIR32_TIM10_SUPPRESS_ISR) &&            \
    !OSAL_IRQ_IS_VALID_PRIORITY(AIR32_PWM_TIM10_IRQ_PRIORITY)
#error "Invalid IRQ priority assigned to TIM10"
#endif

#if AIR32_PWM_USE_TIM11 && !defined(AIR32_TIM11_SUPPRESS_ISR) &&            \
    !OSAL_IRQ_IS_VALID_PRIORITY(AIR32_PWM_TIM11_IRQ_PRIORITY)
#error "Invalid IRQ priority assigned to TIM11"
#endif

#if AIR32_PWM_USE_TIM12 && !defined(AIR32_TIM12_SUPPRESS_ISR) &&            \
    !OSAL_IRQ_IS_VALID_PRIORITY(AIR32_PWM_TIM12_IRQ_PRIORITY)
#error "Invalid IRQ priority assigned to TIM12"
#endif

#if AIR32_PWM_USE_TIM13 && !defined(AIR32_TIM13_SUPPRESS_ISR) &&            \
    !OSAL_IRQ_IS_VALID_PRIORITY(AIR32_PWM_TIM13_IRQ_PRIORITY)
#error "Invalid IRQ priority assigned to TIM13"
#endif

#if AIR32_PWM_USE_TIM14 && !defined(AIR32_TIM14_SUPPRESS_ISR) &&            \
    !OSAL_IRQ_IS_VALID_PRIORITY(AIR32_PWM_TIM14_IRQ_PRIORITY)
#error "Invalid IRQ priority assigned to TIM14"
#endif

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief   Type of a PWM mode.
 */
typedef uint32_t pwmmode_t;

/**
 * @brief   Type of a PWM channel.
 */
typedef uint8_t pwmchannel_t;

/**
 * @brief   Type of a channels mask.
 */
typedef uint32_t pwmchnmsk_t;

/**
 * @brief   Type of a PWM counter.
 */
typedef uint32_t pwmcnt_t;

/**
 * @brief   Type of a PWM driver channel configuration structure.
 */
typedef struct {
  /**
   * @brief Channel active logic level.
   */
  pwmmode_t                 mode;
  /**
   * @brief Channel callback pointer.
   * @note  This callback is invoked on the channel compare event. If set to
   *        @p NULL then the callback is disabled.
   */
  pwmcallback_t             callback;
  /* End of the mandatory fields.*/
} PWMChannelConfig;

/**
 * @brief   Type of a PWM driver configuration structure.
 */
typedef struct {
  /**
   * @brief   Timer clock in Hz.
   * @note    The low level can use assertions in order to catch invalid
   *          frequency specifications.
   */
  uint32_t                  frequency;
  /**
   * @brief   PWM period in ticks.
   * @note    The low level can use assertions in order to catch invalid
   *          period specifications.
   */
  pwmcnt_t                  period;
  /**
   * @brief Periodic callback pointer.
   * @note  This callback is invoked on PWM counter reset. If set to
   *        @p NULL then the callback is disabled.
   */
  pwmcallback_t             callback;
  /**
   * @brief Channels configurations.
   */
  PWMChannelConfig          channels[PWM_CHANNELS];
  /* End of the mandatory fields.*/
  /**
   * @brief TIM CR2 register initialization data.
   * @note  The value of this field should normally be equal to zero.
   */
  uint32_t                  cr2;
  /**
   * @brief TIM BDTR (break & dead-time) register initialization data.
   * @note  The value of this field should normally be equal to zero.
   */                                                                     \
   uint32_t                 bdtr;
   /**
    * @brief TIM DIER register initialization data.
    * @note  The value of this field should normally be equal to zero.
    * @note  Only the DMA-related bits can be specified in this field.
    */
   uint32_t                 dier;
} PWMConfig;

/**
 * @brief   Structure representing a PWM driver.
 */
struct PWMDriver {
  /**
   * @brief Driver state.
   */
  pwmstate_t                state;
  /**
   * @brief Current driver configuration data.
   */
  const PWMConfig           *config;
  /**
   * @brief   Current PWM period in ticks.
   */
  pwmcnt_t                  period;
  /**
   * @brief   Mask of the enabled channels.
   */
  pwmchnmsk_t               enabled;
  /**
   * @brief   Number of channels in this instance.
   */
  pwmchannel_t              channels;
#if defined(PWM_DRIVER_EXT_FIELDS)
  PWM_DRIVER_EXT_FIELDS
#endif
  /* End of the mandatory fields.*/
  /**
   * @brief Timer base clock.
   */
  uint32_t                  clock;
  /**
   * @brief Presence of BDTR register.
   */
  bool                      has_bdtr;
  /**
   * @brief Pointer to the TIMx registers block.
   */
  air32_tim_t               *tim;
};

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/**
 * @brief   Changes the period the PWM peripheral.
 * @details This function changes the period of a PWM unit that has already
 *          been activated using @p pwmStart().
 * @pre     The PWM unit must have been activated using @p pwmStart().
 * @post    The PWM unit period is changed to the new value.
 * @note    The function has effect at the next cycle start.
 * @note    If a period is specified that is shorter than the pulse width
 *          programmed in one of the channels then the behavior is not
 *          guaranteed.
 *
 * @param[in] pwmp      pointer to a @p PWMDriver object
 * @param[in] period    new cycle time in ticks
 *
 * @notapi
 */
#define pwm_lld_change_period(pwmp, period)                                 \
  ((pwmp)->tim->ARR = ((period) - 1))

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#if AIR32_PWM_USE_TIM1 && !defined(__DOXYGEN__)
extern PWMDriver PWMD1;
#endif

#if AIR32_PWM_USE_TIM2 && !defined(__DOXYGEN__)
extern PWMDriver PWMD2;
#endif

#if AIR32_PWM_USE_TIM3 && !defined(__DOXYGEN__)
extern PWMDriver PWMD3;
#endif

#if AIR32_PWM_USE_TIM4 && !defined(__DOXYGEN__)
extern PWMDriver PWMD4;
#endif

#if AIR32_PWM_USE_TIM5 && !defined(__DOXYGEN__)
extern PWMDriver PWMD5;
#endif

#if AIR32_PWM_USE_TIM8 && !defined(__DOXYGEN__)
extern PWMDriver PWMD8;
#endif

#if AIR32_PWM_USE_TIM9 && !defined(__DOXYGEN__)
extern PWMDriver PWMD9;
#endif

#if AIR32_PWM_USE_TIM10 && !defined(__DOXYGEN__)
extern PWMDriver PWMD10;
#endif

#if AIR32_PWM_USE_TIM11 && !defined(__DOXYGEN__)
extern PWMDriver PWMD11;
#endif

#if AIR32_PWM_USE_TIM12 && !defined(__DOXYGEN__)
extern PWMDriver PWMD12;
#endif

#if AIR32_PWM_USE_TIM13 && !defined(__DOXYGEN__)
extern PWMDriver PWMD13;
#endif

#if AIR32_PWM_USE_TIM14 && !defined(__DOXYGEN__)
extern PWMDriver PWMD14;
#endif

#ifdef __cplusplus
extern "C" {
#endif
  void pwm_lld_init(void);
  void pwm_lld_start(PWMDriver *pwmp);
  void pwm_lld_stop(PWMDriver *pwmp);
  void pwm_lld_enable_channel(PWMDriver *pwmp,
                              pwmchannel_t channel,
                              pwmcnt_t width);
  void pwm_lld_disable_channel(PWMDriver *pwmp, pwmchannel_t channel);
  void pwm_lld_enable_periodic_notification(PWMDriver *pwmp);
  void pwm_lld_disable_periodic_notification(PWMDriver *pwmp);
  void pwm_lld_enable_channel_notification(PWMDriver *pwmp,
                                           pwmchannel_t channel);
  void pwm_lld_disable_channel_notification(PWMDriver *pwmp,
                                            pwmchannel_t channel);
  void pwm_lld_serve_interrupt(PWMDriver *pwmp);
#ifdef __cplusplus
}
#endif

#endif /* HAL_USE_PWM */

#endif /* HAL_PWM_LLD_H */

/** @} */
