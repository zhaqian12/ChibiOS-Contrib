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
 * @file    TIMv1/hal_pwm_lld.c
 * @brief   AIR32 PWM subsystem low level driver header.
 *
 * @addtogroup PWM
 * @{
 */

#include "hal.h"

#if HAL_USE_PWM || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/**
 * @brief   PWMD1 driver identifier.
 * @note    The driver PWMD1 allocates the complex timer TIM1 when enabled.
 */
#if AIR32_PWM_USE_TIM1 || defined(__DOXYGEN__)
PWMDriver PWMD1;
#endif

/**
 * @brief   PWMD2 driver identifier.
 * @note    The driver PWMD2 allocates the timer TIM2 when enabled.
 */
#if AIR32_PWM_USE_TIM2 || defined(__DOXYGEN__)
PWMDriver PWMD2;
#endif

/**
 * @brief   PWMD3 driver identifier.
 * @note    The driver PWMD3 allocates the timer TIM3 when enabled.
 */
#if AIR32_PWM_USE_TIM3 || defined(__DOXYGEN__)
PWMDriver PWMD3;
#endif

/**
 * @brief   PWMD4 driver identifier.
 * @note    The driver PWMD4 allocates the timer TIM4 when enabled.
 */
#if AIR32_PWM_USE_TIM4 || defined(__DOXYGEN__)
PWMDriver PWMD4;
#endif

/**
 * @brief   PWMD5 driver identifier.
 * @note    The driver PWMD5 allocates the timer TIM5 when enabled.
 */
#if AIR32_PWM_USE_TIM5 || defined(__DOXYGEN__)
PWMDriver PWMD5;
#endif

/**
 * @brief   PWMD8 driver identifier.
 * @note    The driver PWMD8 allocates the timer TIM8 when enabled.
 */
#if AIR32_PWM_USE_TIM8 || defined(__DOXYGEN__)
PWMDriver PWMD8;
#endif

/**
 * @brief   PWMD9 driver identifier.
 * @note    The driver PWMD9 allocates the timer TIM9 when enabled.
 */
#if AIR32_PWM_USE_TIM9 || defined(__DOXYGEN__)
PWMDriver PWMD9;
#endif

/**
 * @brief   PWMD10 driver identifier.
 * @note    The driver PWMD10 allocates the timer TIM10 when enabled.
 */
#if AIR32_PWM_USE_TIM10 || defined(__DOXYGEN__)
PWMDriver PWMD10;
#endif

/**
 * @brief   PWMD11 driver identifier.
 * @note    The driver PWMD11 allocates the timer TIM11 when enabled.
 */
#if AIR32_PWM_USE_TIM11 || defined(__DOXYGEN__)
PWMDriver PWMD11;
#endif

/**
 * @brief   PWMD12 driver identifier.
 * @note    The driver PWMD12 allocates the timer TIM12 when enabled.
 */
#if AIR32_PWM_USE_TIM12 || defined(__DOXYGEN__)
PWMDriver PWMD12;
#endif

/**
 * @brief   PWMD13 driver identifier.
 * @note    The driver PWMD13 allocates the timer TIM13 when enabled.
 */
#if AIR32_PWM_USE_TIM13 || defined(__DOXYGEN__)
PWMDriver PWMD13;
#endif

/**
 * @brief   PWMD14 driver identifier.
 * @note    The driver PWMD14 allocates the timer TIM14 when enabled.
 */
#if AIR32_PWM_USE_TIM14 || defined(__DOXYGEN__)
PWMDriver PWMD14;
#endif

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

#if AIR32_PWM_USE_TIM1 || defined(__DOXYGEN__)
#if !defined(AIR32_TIM1_SUPPRESS_ISR)
#if !defined(AIR32_TIM1_UP_HANDLER)
#error "AIR32_TIM1_UP_HANDLER not defined"
#endif
/**
 * @brief   TIM1 update interrupt handler.
 * @note    It is assumed that this interrupt is only activated if the callback
 *          pointer is not equal to @p NULL in order to not perform an extra
 *          check in a potentially critical interrupt handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(AIR32_TIM1_UP_HANDLER) {

  OSAL_IRQ_PROLOGUE();

  pwm_lld_serve_interrupt(&PWMD1);

  OSAL_IRQ_EPILOGUE();
}

#if !defined(AIR32_TIM1_CC_HANDLER)
#error "AIR32_TIM1_CC_HANDLER not defined"
#endif
/**
 * @brief   TIM1 compare interrupt handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(AIR32_TIM1_CC_HANDLER) {

  OSAL_IRQ_PROLOGUE();

  pwm_lld_serve_interrupt(&PWMD1);

  OSAL_IRQ_EPILOGUE();
}
#endif /* !defined(AIR32_TIM1_SUPPRESS_ISR) */
#endif /* AIR32_PWM_USE_TIM1 */

#if AIR32_PWM_USE_TIM2 || defined(__DOXYGEN__)
#if !defined(AIR32_TIM2_SUPPRESS_ISR)
#if !defined(AIR32_TIM2_HANDLER)
#error "AIR32_TIM2_HANDLER not defined"
#endif
/**
 * @brief   TIM2 interrupt handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(AIR32_TIM2_HANDLER) {

  OSAL_IRQ_PROLOGUE();

  pwm_lld_serve_interrupt(&PWMD2);

  OSAL_IRQ_EPILOGUE();
}
#endif /* !defined(AIR32_TIM2_SUPPRESS_ISR) */
#endif /* AIR32_PWM_USE_TIM2 */

#if AIR32_PWM_USE_TIM3 || defined(__DOXYGEN__)
#if !defined(AIR32_TIM3_SUPPRESS_ISR)
#if !defined(AIR32_TIM3_HANDLER)
#error "AIR32_TIM3_HANDLER not defined"
#endif
/**
 * @brief   TIM3 interrupt handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(AIR32_TIM3_HANDLER) {

  OSAL_IRQ_PROLOGUE();

  pwm_lld_serve_interrupt(&PWMD3);

  OSAL_IRQ_EPILOGUE();
}
#endif /* !defined(AIR32_TIM3_SUPPRESS_ISR) */
#endif /* AIR32_PWM_USE_TIM3 */

#if AIR32_PWM_USE_TIM4 || defined(__DOXYGEN__)
#if !defined(AIR32_TIM4_SUPPRESS_ISR)
#if !defined(AIR32_TIM4_HANDLER)
#error "AIR32_TIM4_HANDLER not defined"
#endif
/**
 * @brief   TIM4 interrupt handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(AIR32_TIM4_HANDLER) {

  OSAL_IRQ_PROLOGUE();

  pwm_lld_serve_interrupt(&PWMD4);

  OSAL_IRQ_EPILOGUE();
}
#endif /* !defined(AIR32_TIM4_SUPPRESS_ISR) */
#endif /* AIR32_PWM_USE_TIM4 */

#if AIR32_PWM_USE_TIM5 || defined(__DOXYGEN__)
#if !defined(AIR32_TIM5_SUPPRESS_ISR)
#if !defined(AIR32_TIM5_HANDLER)
#error "AIR32_TIM5_HANDLER not defined"
#endif
/**
 * @brief   TIM5 interrupt handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(AIR32_TIM5_HANDLER) {

  OSAL_IRQ_PROLOGUE();

  pwm_lld_serve_interrupt(&PWMD5);

  OSAL_IRQ_EPILOGUE();
}
#endif /* !defined(AIR32_TIM5_SUPPRESS_ISR) */
#endif /* AIR32_PWM_USE_TIM5 */

#if AIR32_PWM_USE_TIM8 || defined(__DOXYGEN__)
#if !defined(AIR32_TIM8_SUPPRESS_ISR)
#if !defined(AIR32_TIM8_UP_HANDLER)
#error "AIR32_TIM8_UP_HANDLER not defined"
#endif
/**
 * @brief   TIM8 update interrupt handler.
 * @note    It is assumed that this interrupt is only activated if the callback
 *          pointer is not equal to @p NULL in order to not perform an extra
 *          check in a potentially critical interrupt handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(AIR32_TIM8_UP_HANDLER) {

  OSAL_IRQ_PROLOGUE();

  pwm_lld_serve_interrupt(&PWMD8);

  OSAL_IRQ_EPILOGUE();
}

#if !defined(AIR32_TIM8_CC_HANDLER)
#error "AIR32_TIM8_CC_HANDLER not defined"
#endif
/**
 * @brief   TIM8 compare interrupt handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(AIR32_TIM8_CC_HANDLER) {

  OSAL_IRQ_PROLOGUE();

  pwm_lld_serve_interrupt(&PWMD8);

  OSAL_IRQ_EPILOGUE();
}
#endif /* !defined(AIR32_TIM8_SUPPRESS_ISR) */
#endif /* AIR32_PWM_USE_TIM8 */

#if AIR32_PWM_USE_TIM9 || defined(__DOXYGEN__)
#if !defined(AIR32_TIM9_SUPPRESS_ISR)
#error "TIM9 ISR not defined by platform"
#endif /* !defined(AIR32_TIM9_SUPPRESS_ISR) */
#endif /* AIR32_PWM_USE_TIM9 */

#if AIR32_PWM_USE_TIM10 || defined(__DOXYGEN__)
#if !defined(AIR32_TIM10_SUPPRESS_ISR)
#error "TIM10 ISR not defined by platform"
#endif /* !defined(AIR32_TIM10_SUPPRESS_ISR) */
#endif /* AIR32_PWM_USE_TIM10 */

#if AIR32_PWM_USE_TIM11 || defined(__DOXYGEN__)
#if !defined(AIR32_TIM11_SUPPRESS_ISR)
#error "TIM11 ISR not defined by platform"
#endif /* !defined(AIR32_TIM11_SUPPRESS_ISR) */
#endif /* AIR32_PWM_USE_TIM11 */

#if AIR32_PWM_USE_TIM12 || defined(__DOXYGEN__)
#if !defined(AIR32_TIM12_SUPPRESS_ISR)
#error "TIM12 ISR not defined by platform"
#endif /* !defined(AIR32_TIM12_SUPPRESS_ISR) */
#endif /* AIR32_PWM_USE_TIM12 */

#if AIR32_PWM_USE_TIM13 || defined(__DOXYGEN__)
#if !defined(AIR32_TIM13_SUPPRESS_ISR)
#error "TIM13 ISR not defined by platform"
#endif /* !defined(AIR32_TIM13_SUPPRESS_ISR) */
#endif /* AIR32_PWM_USE_TIM13 */

#if AIR32_PWM_USE_TIM14 || defined(__DOXYGEN__)
#if !defined(AIR32_TIM14_SUPPRESS_ISR)
#error "TIM14 ISR not defined by platform"
#endif /* !defined(AIR32_TIM14_SUPPRESS_ISR) */
#endif /* AIR32_PWM_USE_TIM14 */

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Low level PWM driver initialization.
 *
 * @notapi
 */
void pwm_lld_init(void) {

#if AIR32_PWM_USE_TIM1
  /* Driver initialization.*/
  pwmObjectInit(&PWMD1);
  PWMD1.channels = AIR32_TIM1_CHANNELS;
  PWMD1.tim = AIR32_TIM1;
  PWMD1.has_bdtr = true;
#endif

#if AIR32_PWM_USE_TIM2
  /* Driver initialization.*/
  pwmObjectInit(&PWMD2);
  PWMD2.channels = AIR32_TIM2_CHANNELS;
  PWMD2.tim = AIR32_TIM2;
  PWMD2.has_bdtr = false;
#endif

#if AIR32_PWM_USE_TIM3
  /* Driver initialization.*/
  pwmObjectInit(&PWMD3);
  PWMD3.channels = AIR32_TIM3_CHANNELS;
  PWMD3.tim = AIR32_TIM3;
  PWMD3.has_bdtr = false;
#endif

#if AIR32_PWM_USE_TIM4
  /* Driver initialization.*/
  pwmObjectInit(&PWMD4);
  PWMD4.channels = AIR32_TIM4_CHANNELS;
  PWMD4.tim = AIR32_TIM4;
  PWMD4.has_bdtr = false;
#endif

#if AIR32_PWM_USE_TIM5
  /* Driver initialization.*/
  pwmObjectInit(&PWMD5);
  PWMD5.channels = AIR32_TIM5_CHANNELS;
  PWMD5.tim = AIR32_TIM5;
  PWMD5.has_bdtr = false;
#endif

#if AIR32_PWM_USE_TIM8
  /* Driver initialization.*/
  pwmObjectInit(&PWMD8);
  PWMD8.channels = AIR32_TIM8_CHANNELS;
  PWMD8.tim = AIR32_TIM8;
  PWMD8.has_bdtr = true;
#endif

#if AIR32_PWM_USE_TIM9
  /* Driver initialization.*/
  pwmObjectInit(&PWMD9);
  PWMD9.channels = AIR32_TIM9_CHANNELS;
  PWMD9.tim = AIR32_TIM9;
  PWMD9.has_bdtr = false;
#endif

#if AIR32_PWM_USE_TIM10
  /* Driver initialization.*/
  pwmObjectInit(&PWMD10);
  PWMD10.channels = AIR32_TIM10_CHANNELS;
  PWMD10.tim = AIR32_TIM10;
  PWMD10.has_bdtr = false;
#endif

#if AIR32_PWM_USE_TIM11
  /* Driver initialization.*/
  pwmObjectInit(&PWMD11);
  PWMD11.channels = AIR32_TIM11_CHANNELS;
  PWMD11.tim = AIR32_TIM11;
  PWMD11.has_bdtr = false;
#endif

#if AIR32_PWM_USE_TIM12
  /* Driver initialization.*/
  pwmObjectInit(&PWMD12);
  PWMD12.channels = AIR32_TIM12_CHANNELS;
  PWMD12.tim = AIR32_TIM12;
  PWMD12.has_bdtr = false;
#endif

#if AIR32_PWM_USE_TIM13
  /* Driver initialization.*/
  pwmObjectInit(&PWMD13);
  PWMD13.channels = AIR32_TIM13_CHANNELS;
  PWMD13.tim = AIR32_TIM13;
  PWMD13.has_bdtr = false;
#endif

#if AIR32_PWM_USE_TIM14
  /* Driver initialization.*/
  pwmObjectInit(&PWMD14);
  PWMD14.channels = AIR32_TIM14_CHANNELS;
  PWMD14.tim = AIR32_TIM14;
  PWMD14.has_bdtr = false;
#endif
}

/**
 * @brief   Configures and activates the PWM peripheral.
 * @note    Starting a driver that is already in the @p PWM_READY state
 *          disables all the active channels.
 *
 * @param[in] pwmp      pointer to a @p PWMDriver object
 *
 * @notapi
 */
void pwm_lld_start(PWMDriver *pwmp) {
  uint32_t psc;
  uint32_t ccer;

  if (pwmp->state == PWM_STOP) {
    /* Clock activation and timer reset.*/
#if AIR32_PWM_USE_TIM1
    if (&PWMD1 == pwmp) {
      rccEnableTIM1(true);
      rccResetTIM1();
#if !defined(AIR32_TIM1_SUPPRESS_ISR)
      nvicEnableVector(AIR32_TIM1_UP_NUMBER, AIR32_PWM_TIM1_IRQ_PRIORITY);
      nvicEnableVector(AIR32_TIM1_CC_NUMBER, AIR32_PWM_TIM1_IRQ_PRIORITY);
#endif
#if defined(AIR32_TIM1CLK)
      pwmp->clock = AIR32_TIM1CLK;
#else
      pwmp->clock = AIR32_TIMCLK2;
#endif
    }
#endif

#if AIR32_PWM_USE_TIM2
    if (&PWMD2 == pwmp) {
      rccEnableTIM2(true);
      rccResetTIM2();
#if !defined(AIR32_TIM2_SUPPRESS_ISR)
      nvicEnableVector(AIR32_TIM2_NUMBER, AIR32_PWM_TIM2_IRQ_PRIORITY);
#endif
#if defined(AIR32_TIM2CLK)
      pwmp->clock = AIR32_TIM2CLK;
#else
      pwmp->clock = AIR32_TIMCLK1;
#endif
    }
#endif

#if AIR32_PWM_USE_TIM3
    if (&PWMD3 == pwmp) {
      rccEnableTIM3(true);
      rccResetTIM3();
#if !defined(AIR32_TIM3_SUPPRESS_ISR)
      nvicEnableVector(AIR32_TIM3_NUMBER, AIR32_PWM_TIM3_IRQ_PRIORITY);
#endif
#if defined(AIR32_TIM3CLK)
      pwmp->clock = AIR32_TIM3CLK;
#else
      pwmp->clock = AIR32_TIMCLK1;
#endif
    }
#endif

#if AIR32_PWM_USE_TIM4
    if (&PWMD4 == pwmp) {
      rccEnableTIM4(true);
      rccResetTIM4();
#if !defined(AIR32_TIM4_SUPPRESS_ISR)
      nvicEnableVector(AIR32_TIM4_NUMBER, AIR32_PWM_TIM4_IRQ_PRIORITY);
#endif
#if defined(AIR32_TIM4CLK)
      pwmp->clock = AIR32_TIM4CLK;
#else
      pwmp->clock = AIR32_TIMCLK1;
#endif
    }
#endif

#if AIR32_PWM_USE_TIM5
    if (&PWMD5 == pwmp) {
      rccEnableTIM5(true);
      rccResetTIM5();
#if !defined(AIR32_TIM5_SUPPRESS_ISR)
      nvicEnableVector(AIR32_TIM5_NUMBER, AIR32_PWM_TIM5_IRQ_PRIORITY);
#endif
#if defined(AIR32_TIM5CLK)
      pwmp->clock = AIR32_TIM5CLK;
#else
      pwmp->clock = AIR32_TIMCLK1;
#endif
    }
#endif

#if AIR32_PWM_USE_TIM8
    if (&PWMD8 == pwmp) {
      rccEnableTIM8(true);
      rccResetTIM8();
#if !defined(AIR32_TIM8_SUPPRESS_ISR)
      nvicEnableVector(AIR32_TIM8_UP_NUMBER, AIR32_PWM_TIM8_IRQ_PRIORITY);
      nvicEnableVector(AIR32_TIM8_CC_NUMBER, AIR32_PWM_TIM8_IRQ_PRIORITY);
#endif
#if defined(AIR32_TIM8CLK)
      pwmp->clock = AIR32_TIM8CLK;
#else
      pwmp->clock = AIR32_TIMCLK2;
#endif
    }
#endif

#if AIR32_PWM_USE_TIM9
    if (&PWMD9 == pwmp) {
      rccEnableTIM9(true);
      rccResetTIM9();
#if defined(AIR32_TIM9CLK)
      pwmp->clock = AIR32_TIM9CLK;
#else
      pwmp->clock = AIR32_TIMCLK2;
#endif
    }
#endif

#if AIR32_PWM_USE_TIM10
    if (&PWMD10 == pwmp) {
      rccEnableTIM10(true);
      rccResetTIM10();
#if defined(AIR32_TIM10CLK)
      pwmp->clock = AIR32_TIM10CLK;
#else
      pwmp->clock = AIR32_TIMCLK2;
#endif
    }
#endif

#if AIR32_PWM_USE_TIM11
    if (&PWMD11 == pwmp) {
      rccEnableTIM11(true);
      rccResetTIM11();
#if defined(AIR32_TIM11CLK)
      pwmp->clock = AIR32_TIM11CLK;
#else
      pwmp->clock = AIR32_TIMCLK2;
#endif
    }
#endif

#if AIR32_PWM_USE_TIM12
    if (&PWMD12 == pwmp) {
      rccEnableTIM12(true);
      rccResetTIM12();
#if defined(AIR32_TIM12CLK)
      pwmp->clock = AIR32_TIM12CLK;
#else
      pwmp->clock = AIR32_TIMCLK1;
#endif
    }
#endif

#if AIR32_PWM_USE_TIM13
    if (&PWMD13 == pwmp) {
      rccEnableTIM13(true);
      rccResetTIM13();
#if defined(AIR32_TIM13CLK)
      pwmp->clock = AIR32_TIM13CLK;
#else
      pwmp->clock = AIR32_TIMCLK1;
#endif
    }
#endif

#if AIR32_PWM_USE_TIM14
    if (&PWMD14 == pwmp) {
      rccEnableTIM14(true);
      rccResetTIM14();
#if defined(AIR32_TIM14CLK)
      pwmp->clock = AIR32_TIM14CLK;
#else
      pwmp->clock = AIR32_TIMCLK1;
#endif
    }
#endif


    /* All channels configured in PWM1 mode with preload enabled and will
       stay that way until the driver is stopped.*/
    pwmp->tim->CCMR1 = AIR32_TIM_CCMR1_OC1M(6) | AIR32_TIM_CCMR1_OC1PE |
                       AIR32_TIM_CCMR1_OC2M(6) | AIR32_TIM_CCMR1_OC2PE;
    pwmp->tim->CCMR2 = AIR32_TIM_CCMR2_OC3M(6) | AIR32_TIM_CCMR2_OC3PE |
                       AIR32_TIM_CCMR2_OC4M(6) | AIR32_TIM_CCMR2_OC4PE;
#if AIR32_TIM_MAX_CHANNELS > 4
    pwmp->tim->CCMR3 = AIR32_TIM_CCMR3_OC5M(6) | AIR32_TIM_CCMR3_OC5PE |
                       AIR32_TIM_CCMR3_OC6M(6) | AIR32_TIM_CCMR3_OC6PE;
#endif
  }
  else {
    /* Driver re-configuration scenario, it must be stopped first.*/
    pwmp->tim->CR1    = 0;                  /* Timer disabled.              */
    pwmp->tim->CCR[0] = 0;                  /* Comparator 1 disabled.       */
    pwmp->tim->CCR[1] = 0;                  /* Comparator 2 disabled.       */
    pwmp->tim->CCR[2] = 0;                  /* Comparator 3 disabled.       */
    pwmp->tim->CCR[3] = 0;                  /* Comparator 4 disabled.       */
#if AIR32_TIM_MAX_CHANNELS > 4
    if (pwmp->channels > 4) {
      pwmp->tim->CCXR[0] = 0;               /* Comparator 5 disabled.       */
      pwmp->tim->CCXR[1] = 0;               /* Comparator 6 disabled.       */
    }
#endif
    pwmp->tim->CNT  = 0;                    /* Counter reset to zero.       */
  }

  /* Timer configuration.*/
  psc = (pwmp->clock / pwmp->config->frequency) - 1;
  osalDbgAssert((psc <= 0xFFFF) &&
                ((psc + 1) * pwmp->config->frequency) == pwmp->clock,
                "invalid frequency");
  pwmp->tim->PSC  = psc;
  pwmp->tim->ARR  = pwmp->period - 1;
  pwmp->tim->CR2  = pwmp->config->cr2;

  /* Output enables and polarities setup.*/
  ccer = 0;
  switch (pwmp->config->channels[0].mode & PWM_OUTPUT_MASK) {
  case PWM_OUTPUT_ACTIVE_LOW:
    ccer |= AIR32_TIM_CCER_CC1P;
    /* Falls through.*/
  case PWM_OUTPUT_ACTIVE_HIGH:
    ccer |= AIR32_TIM_CCER_CC1E;
    /* Falls through.*/
  default:
    ;
  }
  switch (pwmp->config->channels[1].mode & PWM_OUTPUT_MASK) {
  case PWM_OUTPUT_ACTIVE_LOW:
    ccer |= AIR32_TIM_CCER_CC2P;
    /* Falls through.*/
  case PWM_OUTPUT_ACTIVE_HIGH:
    ccer |= AIR32_TIM_CCER_CC2E;
    /* Falls through.*/
  default:
    ;
  }
  switch (pwmp->config->channels[2].mode & PWM_OUTPUT_MASK) {
  case PWM_OUTPUT_ACTIVE_LOW:
    ccer |= AIR32_TIM_CCER_CC3P;
    /* Falls through.*/
  case PWM_OUTPUT_ACTIVE_HIGH:
    ccer |= AIR32_TIM_CCER_CC3E;
    /* Falls through.*/
  default:
    ;
  }
  switch (pwmp->config->channels[3].mode & PWM_OUTPUT_MASK) {
  case PWM_OUTPUT_ACTIVE_LOW:
    ccer |= AIR32_TIM_CCER_CC4P;
    /* Falls through.*/
  case PWM_OUTPUT_ACTIVE_HIGH:
    ccer |= AIR32_TIM_CCER_CC4E;
    /* Falls through.*/
  default:
    ;
  }
  if (pwmp->has_bdtr) {
    switch (pwmp->config->channels[0].mode & PWM_COMPLEMENTARY_OUTPUT_MASK) {
    case PWM_COMPLEMENTARY_OUTPUT_ACTIVE_LOW:
      ccer |= AIR32_TIM_CCER_CC1NP;
      /* Falls through.*/
    case PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH:
      ccer |= AIR32_TIM_CCER_CC1NE;
      /* Falls through.*/
    default:
      ;
    }
    switch (pwmp->config->channels[1].mode & PWM_COMPLEMENTARY_OUTPUT_MASK) {
    case PWM_COMPLEMENTARY_OUTPUT_ACTIVE_LOW:
      ccer |= AIR32_TIM_CCER_CC2NP;
      /* Falls through.*/
    case PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH:
      ccer |= AIR32_TIM_CCER_CC2NE;
      /* Falls through.*/
    default:
      ;
    }
    switch (pwmp->config->channels[2].mode & PWM_COMPLEMENTARY_OUTPUT_MASK) {
    case PWM_COMPLEMENTARY_OUTPUT_ACTIVE_LOW:
      ccer |= AIR32_TIM_CCER_CC3NP;
      /* Falls through.*/
    case PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH:
      ccer |= AIR32_TIM_CCER_CC3NE;
      /* Falls through.*/
    default:
      ;
    }
    switch (pwmp->config->channels[3].mode & PWM_COMPLEMENTARY_OUTPUT_MASK) {
    case PWM_COMPLEMENTARY_OUTPUT_ACTIVE_LOW:
      ccer |= AIR32_TIM_CCER_CC4NP;
      /* Falls through.*/
    case PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH:
      ccer |= AIR32_TIM_CCER_CC4NE;
      /* Falls through.*/
    default:
      ;
    }
  }

  pwmp->tim->CCER  = ccer;
  pwmp->tim->EGR   = AIR32_TIM_EGR_UG;      /* Update event.                */
  pwmp->tim->SR    = 0;                     /* Clear pending IRQs.          */
  pwmp->tim->DIER  = pwmp->config->dier &   /* DMA-related DIER settings.   */
                     ~AIR32_TIM_DIER_IRQ_MASK;
  if (pwmp->has_bdtr) {
    pwmp->tim->BDTR  = pwmp->config->bdtr | AIR32_TIM_BDTR_MOE;
  }
  /* Timer configured and started.*/
  pwmp->tim->CR1   = AIR32_TIM_CR1_ARPE | AIR32_TIM_CR1_URS |
                     AIR32_TIM_CR1_CEN;
}

/**
 * @brief   Deactivates the PWM peripheral.
 *
 * @param[in] pwmp      pointer to a @p PWMDriver object
 *
 * @notapi
 */
void pwm_lld_stop(PWMDriver *pwmp) {

  /* If in ready state then disables the PWM clock.*/
  if (pwmp->state == PWM_READY) {
    pwmp->tim->CR1  = 0;                    /* Timer disabled.              */
    pwmp->tim->DIER = 0;                    /* All IRQs disabled.           */
    pwmp->tim->SR   = 0;                    /* Clear eventual pending IRQs. */
    if (pwmp->has_bdtr) {
      pwmp->tim->BDTR  = 0;
    }

#if AIR32_PWM_USE_TIM1
    if (&PWMD1 == pwmp) {
#if !defined(AIR32_TIM1_SUPPRESS_ISR)
      nvicDisableVector(AIR32_TIM1_UP_NUMBER);
      nvicDisableVector(AIR32_TIM1_CC_NUMBER);
#endif
      rccDisableTIM1();
    }
#endif

#if AIR32_PWM_USE_TIM2
    if (&PWMD2 == pwmp) {
#if !defined(AIR32_TIM2_SUPPRESS_ISR)
      nvicDisableVector(AIR32_TIM2_NUMBER);
#endif
      rccDisableTIM2();
    }
#endif

#if AIR32_PWM_USE_TIM3
    if (&PWMD3 == pwmp) {
#if !defined(AIR32_TIM3_SUPPRESS_ISR)
      nvicDisableVector(AIR32_TIM3_NUMBER);
#endif
      rccDisableTIM3();
    }
#endif

#if AIR32_PWM_USE_TIM4
    if (&PWMD4 == pwmp) {
#if !defined(AIR32_TIM4_SUPPRESS_ISR)
      nvicDisableVector(AIR32_TIM4_NUMBER);
#endif
      rccDisableTIM4();
    }
#endif

#if AIR32_PWM_USE_TIM5
    if (&PWMD5 == pwmp) {
#if !defined(AIR32_TIM5_SUPPRESS_ISR)
      nvicDisableVector(AIR32_TIM5_NUMBER);
#endif
      rccDisableTIM5();
    }
#endif

#if AIR32_PWM_USE_TIM8
    if (&PWMD8 == pwmp) {
#if !defined(AIR32_TIM8_SUPPRESS_ISR)
      nvicDisableVector(AIR32_TIM8_UP_NUMBER);
      nvicDisableVector(AIR32_TIM8_CC_NUMBER);
#endif
      rccDisableTIM8();
    }
#endif

#if AIR32_PWM_USE_TIM9
    if (&PWMD9 == pwmp) {
      rccDisableTIM9();
    }
#endif

#if AIR32_PWM_USE_TIM10
    if (&PWMD10 == pwmp) {
      rccDisableTIM10();
    }
#endif

#if AIR32_PWM_USE_TIM11
    if (&PWMD11 == pwmp) {
      rccDisableTIM11();
    }
#endif

#if AIR32_PWM_USE_TIM12
    if (&PWMD12 == pwmp) {
      rccDisableTIM12();
    }
#endif

#if AIR32_PWM_USE_TIM13
    if (&PWMD13 == pwmp) {
      rccDisableTIM13();
    }
#endif

#if AIR32_PWM_USE_TIM14
    if (&PWMD14 == pwmp) {
      rccDisableTIM14();
    }
#endif
  }
}

/**
 * @brief   Enables a PWM channel.
 * @pre     The PWM unit must have been activated using @p pwmStart().
 * @post    The channel is active using the specified configuration.
 * @note    The function has effect at the next cycle start.
 * @note    Channel notification is not enabled.
 *
 * @param[in] pwmp      pointer to a @p PWMDriver object
 * @param[in] channel   PWM channel identifier (0...channels-1)
 * @param[in] width     PWM pulse width as clock pulses number
 *
 * @notapi
 */
void pwm_lld_enable_channel(PWMDriver *pwmp,
                            pwmchannel_t channel,
                            pwmcnt_t width) {

  /* Changing channel duty cycle on the fly.*/
#if AIR32_TIM_MAX_CHANNELS <= 4
  pwmp->tim->CCR[channel] = width;
#else
  if (channel < 4)
    pwmp->tim->CCR[channel] = width;
  else
    pwmp->tim->CCXR[channel - 4] = width;
#endif
}

/**
 * @brief   Disables a PWM channel and its notification.
 * @pre     The PWM unit must have been activated using @p pwmStart().
 * @post    The channel is disabled and its output line returned to the
 *          idle state.
 * @note    The function has effect at the next cycle start.
 *
 * @param[in] pwmp      pointer to a @p PWMDriver object
 * @param[in] channel   PWM channel identifier (0...channels-1)
 *
 * @notapi
 */
void pwm_lld_disable_channel(PWMDriver *pwmp, pwmchannel_t channel) {

#if AIR32_TIM_MAX_CHANNELS <= 4
  pwmp->tim->CCR[channel] = 0;
  pwmp->tim->DIER &= ~(2 << channel);
#else
  if (channel < 4) {
    pwmp->tim->CCR[channel] = 0;
    pwmp->tim->DIER &= ~(2 << channel);
  }
  else
    pwmp->tim->CCXR[channel - 4] = 0;
#endif
}

/**
 * @brief   Enables the periodic activation edge notification.
 * @pre     The PWM unit must have been activated using @p pwmStart().
 * @note    If the notification is already enabled then the call has no effect.
 *
 * @param[in] pwmp      pointer to a @p PWMDriver object
 *
 * @notapi
 */
void pwm_lld_enable_periodic_notification(PWMDriver *pwmp) {
  uint32_t dier = pwmp->tim->DIER;

  /* If the IRQ is not already enabled care must be taken to clear it,
     it is probably already pending because the timer is running.*/
  if ((dier & AIR32_TIM_DIER_UIE) == 0) {
    pwmp->tim->SR   = ~AIR32_TIM_SR_UIF;
    pwmp->tim->DIER = dier | AIR32_TIM_DIER_UIE;
  }
}

/**
 * @brief   Disables the periodic activation edge notification.
 * @pre     The PWM unit must have been activated using @p pwmStart().
 * @note    If the notification is already disabled then the call has no effect.
 *
 * @param[in] pwmp      pointer to a @p PWMDriver object
 *
 * @notapi
 */
void pwm_lld_disable_periodic_notification(PWMDriver *pwmp) {

  pwmp->tim->DIER &= ~AIR32_TIM_DIER_UIE;
}

/**
 * @brief   Enables a channel de-activation edge notification.
 * @pre     The PWM unit must have been activated using @p pwmStart().
 * @pre     The channel must have been activated using @p pwmEnableChannel().
 * @note    If the notification is already enabled then the call has no effect.
 *
 * @param[in] pwmp      pointer to a @p PWMDriver object
 * @param[in] channel   PWM channel identifier (0...channels-1)
 *
 * @notapi
 */
void pwm_lld_enable_channel_notification(PWMDriver *pwmp,
                                         pwmchannel_t channel) {
  uint32_t dier = pwmp->tim->DIER;

#if AIR32_TIM_MAX_CHANNELS > 4
  /* Channels 4 and 5 do not support callbacks.*/
  osalDbgAssert(channel < 4, "callback not supported");
#endif

  /* If the IRQ is not already enabled care must be taken to clear it,
     it is probably already pending because the timer is running.*/
  if ((dier & (2 << channel)) == 0) {
    pwmp->tim->SR   = ~(2 << channel);
    pwmp->tim->DIER = dier | (2 << channel);
  }
}

/**
 * @brief   Disables a channel de-activation edge notification.
 * @pre     The PWM unit must have been activated using @p pwmStart().
 * @pre     The channel must have been activated using @p pwmEnableChannel().
 * @note    If the notification is already disabled then the call has no effect.
 *
 * @param[in] pwmp      pointer to a @p PWMDriver object
 * @param[in] channel   PWM channel identifier (0...channels-1)
 *
 * @notapi
 */
void pwm_lld_disable_channel_notification(PWMDriver *pwmp,
                                          pwmchannel_t channel) {

  pwmp->tim->DIER &= ~(2 << channel);
}

/**
 * @brief   Common TIM2...TIM5,TIM9 IRQ handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @param[in] pwmp      pointer to a @p PWMDriver object
 *
 * @notapi
 */
void pwm_lld_serve_interrupt(PWMDriver *pwmp) {
  uint32_t sr;

  sr  = pwmp->tim->SR;
  sr &= pwmp->tim->DIER & AIR32_TIM_DIER_IRQ_MASK;
  pwmp->tim->SR = ~sr;
  if (((sr & AIR32_TIM_SR_CC1IF) != 0) &&
      (pwmp->config->channels[0].callback != NULL))
    pwmp->config->channels[0].callback(pwmp);
  if (((sr & AIR32_TIM_SR_CC2IF) != 0) &&
      (pwmp->config->channels[1].callback != NULL))
    pwmp->config->channels[1].callback(pwmp);
  if (((sr & AIR32_TIM_SR_CC3IF) != 0) &&
      (pwmp->config->channels[2].callback != NULL))
    pwmp->config->channels[2].callback(pwmp);
  if (((sr & AIR32_TIM_SR_CC4IF) != 0) &&
      (pwmp->config->channels[3].callback != NULL))
    pwmp->config->channels[3].callback(pwmp);
  if (((sr & AIR32_TIM_SR_UIF) != 0) && (pwmp->config->callback != NULL))
    pwmp->config->callback(pwmp);
}

#endif /* HAL_USE_PWM */

/** @} */
