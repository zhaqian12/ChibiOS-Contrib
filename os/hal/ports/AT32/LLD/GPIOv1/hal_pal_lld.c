/*
    Copyright (C) Zhaqian

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
 * @file    GPIOv1/hal_pal_lld.c
 * @brief   AT32 PAL low level driver code.
 *
 * @addtogroup PAL
 * @{
 */

#include "hal.h"

#if HAL_USE_PAL || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

#define APB2_EN_MASK  (CRM_APB2EN_GPIOAEN | CRM_APB2EN_GPIOBEN |  \
                       CRM_APB2EN_GPIODEN | CRM_APB2EN_IOMUXEN)

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

#if (PAL_USE_WAIT == TRUE) || (PAL_USE_CALLBACKS == TRUE) || defined(__DOXYGEN__)
/**
 * @brief   Event records for the 16 GPIO EXINT channels.
 */
palevent_t _pal_events[16];
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

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   AT32 I/O ports configuration.
 * @details Ports A-D(E, F, G) clocks enabled, IOMUX clock enabled.
 *
 * @param[in] config    the AT32 ports configuration
 *
 * @notapi
 */
void _pal_lld_init(const PALConfig *config) {

#if PAL_USE_CALLBACKS || PAL_USE_WAIT || defined(__DOXYGEN__)
  unsigned i;

  for (i = 0; i < 16; i++) {
    _pal_init_event(i);
  }
#endif

  /*
   * Enables the GPIO related clocks.
   */
  crmEnableAPB2(APB2_EN_MASK, true);
#if AT32_HAS_GPIOC || defined(__DOXYGEN__)
  crmEnableAPB2(CRM_APB2EN_GPIOCEN, true);
#endif
#if AT32_HAS_GPIOE || defined(__DOXYGEN__)
  crmEnableAPB2(CRM_APB2EN_GPIOEEN, true);
#endif
#if AT32_HAS_GPIOF || defined(__DOXYGEN__)
  crmEnableAPB2(CRM_APB2EN_GPIOFEN, true);
#endif
#if AT32_HAS_GPIOG || defined(__DOXYGEN__)
  crmEnableAPB2(CRM_APB2EN_GPIOGEN, true);
#endif

  /*
   * Initial GPIO setup.
   */
  GPIOA->ODT = config->PAData.odt;
  GPIOA->CFGHR = config->PAData.cfghr;
  GPIOA->CFGLR = config->PAData.cfglr;
#if AT32_GPIO_HAS_HDRV || defined(__DOXYGEN__)
  GPIOA->HDRV = config->PAData.hdrv;
#endif

  GPIOB->ODT = config->PBData.odt;
  GPIOB->CFGHR = config->PBData.cfghr;
  GPIOB->CFGLR = config->PBData.cfglr;
#if AT32_GPIO_HAS_HDRV || defined(__DOXYGEN__)
  GPIOB->HDRV = config->PBData.hdrv;
#endif

#if AT32_HAS_GPIOC || defined(__DOXYGEN__)
  GPIOC->ODT = config->PCData.odt;
  GPIOC->CFGHR = config->PCData.cfghr;
  GPIOC->CFGLR = config->PCData.cfglr;
#if AT32_GPIO_HAS_HDRV || defined(__DOXYGEN__)
  GPIOC->HDRV = config->PCData.hdrv;
#endif
#endif

  GPIOD->ODT = config->PDData.odt;
  GPIOD->CFGHR = config->PDData.cfghr;
  GPIOD->CFGLR = config->PDData.cfglr;
#if AT32_GPIO_HAS_HDRV || defined(__DOXYGEN__)
  GPIOD->HDRV = config->PDData.hdrv;
#endif

#if AT32_HAS_GPIOE || defined(__DOXYGEN__)
  GPIOE->ODT = config->PEData.odt;
  GPIOE->CFGHR = config->PEData.cfghr;
  GPIOE->CFGLR = config->PEData.cfglr;
#if AT32_GPIO_HAS_HDRV || defined(__DOXYGEN__)
  GPIOE->HDRV = config->PEData.hdrv;
#endif
#endif

#if AT32_HAS_GPIOF || defined(__DOXYGEN__)
  GPIOF->ODT = config->PFData.odt;
  GPIOF->CFGHR = config->PFData.cfghr;
  GPIOF->CFGLR = config->PFData.cfglr;
#if AT32_GPIO_HAS_HDRV || defined(__DOXYGEN__)
  GPIOF->HDRV = config->PFData.hdrv;
#endif
#endif

#if AT32_HAS_GPIOG || defined(__DOXYGEN__)
  GPIOG->ODT = config->PGData.odt;
  GPIOG->CFGHR = config->PGData.cfghr;
  GPIOG->CFGLR = config->PGData.cfglr;
#if AT32_GPIO_HAS_HDRV || defined(__DOXYGEN__)
  GPIOG->HDRV = config->PGData.hdrv;
#endif
#endif
}

/**
 * @brief   Pads mode setup.
 * @details This function programs a pads group belonging to the same port
 *          with the specified mode.
 * @note    @p PAL_MODE_UNCONNECTED is implemented as push pull output at 2MHz.
 * @note    Writing on pads programmed as pull-up or pull-down has the side
 *          effect to modify the resistor setting because the output latched
 *          data is used for the resistor selection.
 *
 * @param[in] port      the port identifier
 * @param[in] mask      the group mask
 * @param[in] mode      the mode
 *
 * @notapi
 */
void _pal_lld_setgroupmode(ioportid_t port,
                           ioportmask_t mask,
                           iomode_t mode) {
  static const uint8_t cfgtab[] = {
    4,          /* PAL_MODE_RESET, implemented as input.*/
    2,          /* PAL_MODE_UNCONNECTED, implemented as push pull output 2MHz.*/
    4,          /* PAL_MODE_INPUT */
    8,          /* PAL_MODE_INPUT_PULLUP */
    8,          /* PAL_MODE_INPUT_PULLDOWN */
    0,          /* PAL_MODE_INPUT_ANALOG */
    3,          /* PAL_MODE_OUTPUT_PUSHPULL, 50MHz.*/
    7,          /* PAL_MODE_OUTPUT_OPENDRAIN, 50MHz.*/
    8,          /* Reserved.*/
    8,          /* Reserved.*/
    8,          /* Reserved.*/
    8,          /* Reserved.*/
    8,          /* Reserved.*/
    8,          /* Reserved.*/
    8,          /* Reserved.*/
    8,          /* Reserved.*/
    0xB,        /* PAL_MODE_AT32_ALTERNATE_PUSHPULL, 50MHz.*/
    0xF,        /* PAL_MODE_AT32_ALTERNATE_OPENDRAIN, 50MHz.*/
  };
  uint32_t mh, ml, cfghr, cfglr, cfg;
  unsigned i;
  if (mode == PAL_MODE_INPUT_PULLUP)
    port->SCR = mask;
  else if (mode == PAL_MODE_INPUT_PULLDOWN)
    port->CLR = mask;
  cfg = cfgtab[mode];
  mh = ml = cfghr = cfglr = 0;
  for (i = 0; i < 8; i++) {
    ml <<= 4;
    mh <<= 4;
    cfglr <<= 4;
    cfghr <<= 4;
    if ((mask & 0x0080) == 0)
      ml |= 0xf;
    else
      cfglr |= cfg;
    if ((mask & 0x8000) == 0)
      mh |= 0xf;
    else
      cfghr |= cfg;
    mask <<= 1;
  }
  port->CFGHR = (port->CFGHR & mh) | cfghr;
  port->CFGLR = (port->CFGLR & ml) | cfglr;
}

#if PAL_USE_CALLBACKS || PAL_USE_WAIT || defined(__DOXYGEN__)
/**
 * @brief   Pad event enable.
 * @note    Programming an unknown or unsupported mode is silently ignored.
 *
 * @param[in] port      port identifier
 * @param[in] pad       pad number within the port
 * @param[in] mode      pad event mode
 *
 * @notapi
 */
void _pal_lld_enablepadevent(ioportid_t port,
                             iopadid_t pad,
                             ioeventmode_t mode) {

  uint32_t padmask, cidx, coff, cmask, portidx;

  /* Mask of the pad.*/
  padmask = 1U << (uint32_t)pad;

  /* Multiple channel setting of the same channel not allowed, first disable
     it. This is done because on AT32 the same channel cannot be mapped on
     multiple ports.*/
  osalDbgAssert(((EXINT->POLCFG1 & padmask) == 0U) &&
                ((EXINT->POLCFG2 & padmask) == 0U), "channel already in use");

  /* Index and mask of the IOMUX EXINTC register to be used.*/
  cidx  = (uint32_t)pad >> 2U;
  coff = ((uint32_t)pad & 3U) * 4U;
  cmask = ~(0xFU << coff);

  /* Port index is obtained assuming that GPIO ports are placed at regular
     0x400 intervals in memory space. So far this is true for all devices.*/
  portidx = (((uint32_t)port - (uint32_t)GPIOA) >> 10U) & 0xFU;

  /* Port selection in IOMUX.*/
  IOMUX->EXINTC[cidx] = (IOMUX->EXINTC[cidx] & cmask) | (portidx << coff);

  /* Programming edge registers.*/
  if (mode & PAL_EVENT_MODE_RISING_EDGE)
    EXINT->POLCFG1 |= padmask;
  else
    EXINT->POLCFG1 &= ~padmask;
  if (mode & PAL_EVENT_MODE_FALLING_EDGE)
    EXINT->POLCFG2 |= padmask;
  else
    EXINT->POLCFG2 &= ~padmask;

  /* Programming interrupt and event registers.*/
  EXINT->INTEN |= padmask;
  EXINT->EVTEN &= ~padmask;
}

/**
 * @brief   Pad event disable.
 * @details This function disables previously programmed event callbacks.
 *
 * @param[in] port      port identifier
 * @param[in] pad       pad number within the port
 *
 * @notapi
 */
void _pal_lld_disablepadevent(ioportid_t port, iopadid_t pad) {
  uint32_t padmask, polcfg1, polcfg2;

  polcfg1 = EXINT->POLCFG1;
  polcfg2 = EXINT->POLCFG2;

  /* Mask of the pad.*/
  padmask = 1U << (uint32_t)pad;

  /* If either RTRS1 or POLCFG21 is enabled then the channel is in use.*/
  if (((polcfg1 | polcfg2) & padmask) != 0U) {
    uint32_t cidx, coff, cport, portidx;

    /* Index and mask of the IOMUX EXINTC register to be used.*/
    cidx  = (uint32_t)pad >> 2U;
    coff = ((uint32_t)pad & 3U) * 4U;

    /* Port index is obtained assuming that GPIO ports are placed at regular
       0x400 intervals in memory space. So far this is true for all devices.*/
    portidx = (((uint32_t)port - (uint32_t)GPIOA) >> 10U) & 0xFU;

    cport = (IOMUX->EXINTC[cidx] >> coff) & 0xFU;

    osalDbgAssert(cport == portidx, "channel mapped on different port");

    /* Disabling channel.*/
    EXINT->INTEN   &= ~padmask;
    EXINT->EVTEN   &= ~padmask;
    EXINT->POLCFG1  = polcfg1 & ~padmask;
    EXINT->POLCFG2  = polcfg2 & ~padmask;
    EXINT->INTSTS   = padmask;

#if PAL_USE_CALLBACKS || PAL_USE_WAIT
  /* Callback cleared and/or thread reset.*/
  _pal_clear_event(pad);
#endif
  }
}
#endif /* PAL_USE_CALLBACKS || PAL_USE_WAIT */

#endif /* HAL_USE_PAL */

/** @} */
