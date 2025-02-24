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
 * @file    DMAv1/air32_dma.h
 * @brief   DMA helper driver header.
 * @note    This driver uses the new naming convention used for the AIR32F10x
 *          so the "DMA channels" are referred as "DMA streams".
 *
 * @addtogroup AIR32_DMA
 * @{
 */

#ifndef AIR32_DMA_H
#define AIR32_DMA_H

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @brief   DMA capability.
 * @details if @p TRUE then the DMA is able of burst transfers, FIFOs,
 *          scatter gather and other advanced features.
 */
#define AIR32_DMA_ADVANCED          FALSE

/**
 * @brief   Total number of DMA streams.
 * @details This is the total number of streams among all the DMA units.
 */
#define AIR32_DMA_STREAMS           (AIR32_DMA1_NUM_CHANNELS +              \
                                     AIR32_DMA2_NUM_CHANNELS)

/**
 * @brief   Mask of the ISR bits passed to the DMA callback functions.
 */
#define AIR32_DMA_ISR_MASK          0x0E

/**
 * @brief   Returns the request line associated to the specified stream.
 * @note    In some AIR32 manuals the request line is named confusingly
 *          channel.
 *
 * @param[in] id        the unique numeric stream identifier
 * @param[in] c         a stream/request association word, one request per
 *                      nibble
 * @return              Returns the request associated to the stream.
 */
#define AIR32_DMA_GETCHANNEL(id, c)                                         \
  (((uint32_t)(c) >> (((uint32_t)(id) % (uint32_t)AIR32_DMA1_NUM_CHANNELS) * 4U)) & 15U)

/**
 * @brief   Checks if a DMA priority is within the valid range.
 * @param[in] prio      DMA priority
 *
 * @retval              The check result.
 * @retval false        invalid DMA priority.
 * @retval true         correct DMA priority.
 */
#define AIR32_DMA_IS_VALID_PRIORITY(prio) (((prio) >= 0U) && ((prio) <= 3U))

#if (AIR32_DMA_SUPPORTS_DMAMUX == FALSE) || defined(_DOXYGEN__)
/**
 * @brief   Checks if a DMA stream id is within the valid range.
 *
 * @param[in] id        DMA stream id
 * @retval              The check result.
 * @retval false        invalid DMA channel.
 * @retval true         correct DMA channel.
 */
#define AIR32_DMA_IS_VALID_STREAM(id) (((id) >= 0U) &&                      \
                                       ((id) < AIR32_DMA_STREAMS))
#else /* AIR32_DMA_SUPPORTS_DMAMUX == FALSE */
#if AIR32_DMA2_NUM_CHANNELS > 0
#define AIR32_DMA_IS_VALID_STREAM(id) (((id) >= 0U) &&                      \
                                       ((id) <= (AIR32_DMA_STREAMS + 2)))
#else
#define AIR32_DMA_IS_VALID_STREAM(id) (((id) >= 0U) &&                      \
                                       ((id) <= (AIR32_DMA_STREAMS + 1)))
#endif
#endif /* AIR32_DMA_SUPPORTS_DMAMUX == FALSE */

/**
 * @brief   Returns an unique numeric identifier for a DMA stream.
 *
 * @param[in] dma       the DMA unit number
 * @param[in] stream    the stream number
 * @return              An unique numeric stream identifier.
 */
#define AIR32_DMA_STREAM_ID(dma, stream)                                    \
  ((((dma) - 1) * AIR32_DMA1_NUM_CHANNELS) + ((stream) - 1))

/**
 * @brief   Returns a DMA stream identifier mask.
 *
 *
 * @param[in] dma       the DMA unit number
 * @param[in] stream    the stream number
 * @return              A DMA stream identifier mask.
 */
#define AIR32_DMA_STREAM_ID_MSK(dma, stream)                                \
  (1U << AIR32_DMA_STREAM_ID(dma, stream))

/**
 * @brief   Checks if a DMA stream unique identifier belongs to a mask.
 *
 * @param[in] id        the stream numeric identifier
 * @param[in] mask      the stream numeric identifiers mask
 *
 * @retval              The check result.
 * @retval false        id does not belong to the mask.
 * @retval true         id belongs to the mask.
 */
#define AIR32_DMA_IS_VALID_ID(id, mask) (((1U << (id)) & (mask)))

#if (AIR32_DMA_SUPPORTS_DMAMUX == TRUE) || defined(_DOXYGEN__)
/**
 * @name    Special stream identifiers
 * @{
 */
#define AIR32_DMA_STREAM_ID_ANY         AIR32_DMA_STREAMS
#define AIR32_DMA_STREAM_ID_ANY_DMA1    (AIR32_DMA_STREAM_ID_ANY + 1)
#if AIR32_DMA2_NUM_CHANNELS > 0
#define AIR32_DMA_STREAM_ID_ANY_DMA2    (AIR32_DMA_STREAM_ID_ANY_DMA1 + 1)
#endif
/** @} */
#endif

/**
 * @name    DMA streams identifiers
 * @{
 */
/**
 * @brief   Returns a pointer to a air32_dma_stream_t structure.
 *
 * @param[in] id        the stream numeric identifier
 * @return              A pointer to the air32_dma_stream_t constant structure
 *                      associated to the DMA stream.
 */
#define AIR32_DMA_STREAM(id)        (&_air32_dma_streams[id])

#if AIR32_DMA1_NUM_CHANNELS > 0
#define AIR32_DMA1_STREAM1          AIR32_DMA_STREAM(0)
#endif
#if AIR32_DMA1_NUM_CHANNELS > 1
#define AIR32_DMA1_STREAM2          AIR32_DMA_STREAM(1)
#endif
#if AIR32_DMA1_NUM_CHANNELS > 2
#define AIR32_DMA1_STREAM3          AIR32_DMA_STREAM(2)
#endif
#if AIR32_DMA1_NUM_CHANNELS > 3
#define AIR32_DMA1_STREAM4          AIR32_DMA_STREAM(3)
#endif
#if AIR32_DMA1_NUM_CHANNELS > 4
#define AIR32_DMA1_STREAM5          AIR32_DMA_STREAM(4)
#endif
#if AIR32_DMA1_NUM_CHANNELS > 5
#define AIR32_DMA1_STREAM6          AIR32_DMA_STREAM(5)
#endif
#if AIR32_DMA1_NUM_CHANNELS > 6
#define AIR32_DMA1_STREAM7          AIR32_DMA_STREAM(6)
#endif
#if AIR32_DMA1_NUM_CHANNELS > 7
#define AIR32_DMA1_STREAM8          AIR32_DMA_STREAM(7)
#endif
#if AIR32_DMA2_NUM_CHANNELS > 0
#define AIR32_DMA2_STREAM1          AIR32_DMA_STREAM(AIR32_DMA1_NUM_CHANNELS + 0)
#endif
#if AIR32_DMA2_NUM_CHANNELS > 1
#define AIR32_DMA2_STREAM2          AIR32_DMA_STREAM(AIR32_DMA1_NUM_CHANNELS + 1)
#endif
#if AIR32_DMA2_NUM_CHANNELS > 2
#define AIR32_DMA2_STREAM3          AIR32_DMA_STREAM(AIR32_DMA1_NUM_CHANNELS + 2)
#endif
#if AIR32_DMA2_NUM_CHANNELS > 3
#define AIR32_DMA2_STREAM4          AIR32_DMA_STREAM(AIR32_DMA1_NUM_CHANNELS + 3)
#endif
#if AIR32_DMA2_NUM_CHANNELS > 4
#define AIR32_DMA2_STREAM5          AIR32_DMA_STREAM(AIR32_DMA1_NUM_CHANNELS + 4)
#endif
#if AIR32_DMA2_NUM_CHANNELS > 5
#define AIR32_DMA2_STREAM6          AIR32_DMA_STREAM(AIR32_DMA1_NUM_CHANNELS + 5)
#endif
#if AIR32_DMA2_NUM_CHANNELS > 6
#define AIR32_DMA2_STREAM7          AIR32_DMA_STREAM(AIR32_DMA1_NUM_CHANNELS + 6)
#endif
#if AIR32_DMA2_NUM_CHANNELS > 7
#define AIR32_DMA2_STREAM8          AIR32_DMA_STREAM(AIR32_DMA1_NUM_CHANNELS + 7)
#endif
/** @} */

/**
 * @name    CR register constants common to all DMA types
 * @{
 */
#define AIR32_DMA_CCR_RESET_VALUE   0x00000000U
#define AIR32_DMA_CR_EN             DMA_CCR1_EN
#define AIR32_DMA_CR_TEIE           DMA_CCR1_TEIE
#define AIR32_DMA_CR_HTIE           DMA_CCR1_HTIE
#define AIR32_DMA_CR_TCIE           DMA_CCR1_TCIE
#define AIR32_DMA_CR_DIR_MASK       (DMA_CCR1_DIR | DMA_CCR1_MEM2MEM)
#define AIR32_DMA_CR_DIR_P2M        0U
#define AIR32_DMA_CR_DIR_M2P        DMA_CCR1_DIR
#define AIR32_DMA_CR_DIR_M2M        DMA_CCR1_MEM2MEM
#define AIR32_DMA_CR_CIRC           DMA_CCR1_CIRC
#define AIR32_DMA_CR_PINC           DMA_CCR1_PINC
#define AIR32_DMA_CR_MINC           DMA_CCR1_MINC
#define AIR32_DMA_CR_PSIZE_MASK     DMA_CCR1_PSIZE
#define AIR32_DMA_CR_PSIZE_BYTE     0U
#define AIR32_DMA_CR_PSIZE_HWORD    DMA_CCR1_PSIZE_0
#define AIR32_DMA_CR_PSIZE_WORD     DMA_CCR1_PSIZE_1
#define AIR32_DMA_CR_MSIZE_MASK     DMA_CCR1_MSIZE
#define AIR32_DMA_CR_MSIZE_BYTE     0U
#define AIR32_DMA_CR_MSIZE_HWORD    DMA_CCR1_MSIZE_0
#define AIR32_DMA_CR_MSIZE_WORD     DMA_CCR1_MSIZE_1
#define AIR32_DMA_CR_SIZE_MASK      (AIR32_DMA_CR_PSIZE_MASK |              \
                                     AIR32_DMA_CR_MSIZE_MASK)
#define AIR32_DMA_CR_PL_MASK        DMA_CCR1_PL
#define AIR32_DMA_CR_PL(n)          ((n) << 12U)
/** @} */

/**
 * @name    Request line selector macro
 * @{
 */
#if AIR32_DMA_SUPPORTS_CSELR || defined(__DOXYGEN__)
#define AIR32_DMA_CR_CHSEL_MASK     (15U << 16U)
#define AIR32_DMA_CR_CHSEL(n)       ((n) << 16U)
#else
#define AIR32_DMA_CR_CHSEL_MASK     0U
#define AIR32_DMA_CR_CHSEL(n)       0U
#endif
/** @} */

/**
 * @name    CR register constants only found in enhanced DMA
 * @{
 */
#define AIR32_DMA_CR_DMEIE          0U  /**< @brief Ignored by normal DMA.  */
/** @} */

/**
 * @name    Status flags passed to the ISR callbacks
 * @{
 */
#define AIR32_DMA_ISR_FEIF          0U
#define AIR32_DMA_ISR_DMEIF         0U
#define AIR32_DMA_ISR_TEIF          DMA_ISR_TEIF1
#define AIR32_DMA_ISR_HTIF          DMA_ISR_HTIF1
#define AIR32_DMA_ISR_TCIF          DMA_ISR_TCIF1
/** @} */

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

#if !defined(AIR32_DMA_SUPPORTS_DMAMUX)
#error "AIR32_DMA_SUPPORTS_DMAMUX not defined in registry"
#endif

#if !defined(AIR32_DMA_SUPPORTS_CSELR)
#error "AIR32_DMA_SUPPORTS_CSELR not defined in registry"
#endif

#if AIR32_DMA_SUPPORTS_DMAMUX && AIR32_DMA_SUPPORTS_CSELR
#error "AIR32_DMA_SUPPORTS_DMAMUX and AIR32_DMA_SUPPORTS_CSELR both TRUE"
#endif

#if !defined(AIR32_DMA1_NUM_CHANNELS)
#error "AIR32_DMA1_NUM_CHANNELS not defined in registry"
#endif

#if !defined(AIR32_DMA2_NUM_CHANNELS)
#error "AIR32_DMA2_NUM_CHANNELS not defined in registry"
#endif

#if (AIR32_DMA1_NUM_CHANNELS < 0) || (AIR32_DMA1_NUM_CHANNELS > 8)
#error "unsupported channels configuration"
#endif

#if (AIR32_DMA2_NUM_CHANNELS < 0) || (AIR32_DMA2_NUM_CHANNELS > 8)
#error "unsupported channels configuration"
#endif

#if (AIR32_DMA_SUPPORTS_DMAMUX == TRUE) || defined(__DOXYGEN__)
#include "air32_dmamux.h"
#endif

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief   Type of a DMA callback.
 *
 * @param[in] p         parameter for the registered function
 * @param[in] flags     pre-shifted content of the ISR register, the bits
 *                      are aligned to bit zero
 */
typedef void (*air32_dmaisr_t)(void *p, uint32_t flags);

/**
 * @brief   AIR32 DMA stream descriptor structure.
 */
typedef struct {
  DMA_TypeDef           *dma;           /**< @brief Associated DMA.         */
  DMA_Channel_TypeDef   *channel;       /**< @brief Associated DMA channel. */
  uint32_t              cmask;          /**< @brief Mask of streams sharing
                                             the same ISR.                  */
#if (AIR32_DMA_SUPPORTS_CSELR == TRUE) || defined(__DOXYGEN__)
  volatile uint32_t     *cselr;         /**< @brief Associated CSELR reg.   */
#elif AIR32_DMA_SUPPORTS_DMAMUX == TRUE
  DMAMUX_Channel_TypeDef *mux;          /**< @brief Associated DMA mux.     */
#else
  uint8_t               dummy;          /**< @brief Filler.                 */
#endif
  uint8_t               shift;          /**< @brief Bit offset in ISR, IFCR
                                             and CSELR registers.           */
  uint8_t               selfindex;      /**< @brief Index to self in array. */
  uint8_t               vector;         /**< @brief Associated IRQ vector.  */
} air32_dma_stream_t;

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/**
 * @name    Macro Functions
 * @{
 */
/**
 * @brief   Associates a peripheral data register to a DMA stream.
 * @note    This function can be invoked in both ISR or thread context.
 * @pre     The stream must have been allocated using @p dmaStreamAlloc().
 * @post    After use the stream can be released using @p dmaStreamRelease().
 *
 * @param[in] dmastp    pointer to a air32_dma_stream_t structure
 * @param[in] addr      value to be written in the CPAR register
 *
 * @special
 */
#define dmaStreamSetPeripheral(dmastp, addr) {                              \
  (dmastp)->channel->CPAR = (uint32_t)(addr);                               \
}

/**
 * @brief   Associates a memory destination to a DMA stream.
 * @note    This function can be invoked in both ISR or thread context.
 * @pre     The stream must have been allocated using @p dmaStreamAlloc().
 * @post    After use the stream can be released using @p dmaStreamRelease().
 *
 * @param[in] dmastp    pointer to a air32_dma_stream_t structure
 * @param[in] addr      value to be written in the CMAR register
 *
 * @special
 */
#define dmaStreamSetMemory0(dmastp, addr) {                                 \
  (dmastp)->channel->CMAR = (uint32_t)(addr);                               \
}

/**
 * @brief   Sets the number of transfers to be performed.
 * @note    This function can be invoked in both ISR or thread context.
 * @pre     The stream must have been allocated using @p dmaStreamAlloc().
 * @post    After use the stream can be released using @p dmaStreamRelease().
 *
 * @param[in] dmastp    pointer to a air32_dma_stream_t structure
 * @param[in] size      value to be written in the CNDTR register
 *
 * @special
 */
#define dmaStreamSetTransactionSize(dmastp, size) {                         \
  (dmastp)->channel->CNDTR = (uint32_t)(size);                              \
}

/**
 * @brief   Returns the number of transfers to be performed.
 * @note    This function can be invoked in both ISR or thread context.
 * @pre     The stream must have been allocated using @p dmaStreamAlloc().
 * @post    After use the stream can be released using @p dmaStreamRelease().
 *
 * @param[in] dmastp    pointer to a air32_dma_stream_t structure
 * @return              The number of transfers to be performed.
 *
 * @special
 */
#define dmaStreamGetTransactionSize(dmastp) ((size_t)((dmastp)->channel->CNDTR))

/**
 * @brief   Programs the stream mode settings.
 * @note    This function can be invoked in both ISR or thread context.
 * @pre     The stream must have been allocated using @p dmaStreamAlloc().
 * @post    After use the stream can be released using @p dmaStreamRelease().
 *
 * @param[in] dmastp    pointer to a air32_dma_stream_t structure
 * @param[in] mode      value to be written in the CCR register
 *
 * @special
 */
#if AIR32_DMA_SUPPORTS_CSELR || defined(__DOXYGEN__)
#define dmaStreamSetMode(dmastp, mode) {                                    \
  uint32_t cselr = *(dmastp)->cselr;                                        \
  cselr &= ~(0x0000000FU << (dmastp)->shift);                               \
  cselr |=  (((uint32_t)(mode) >> 16U) << (dmastp)->shift);                 \
  *(dmastp)->cselr = cselr;                                                 \
  (dmastp)->channel->CCR  = (uint32_t)(mode);                               \
}
#else
#define dmaStreamSetMode(dmastp, mode) {                                    \
  (dmastp)->channel->CCR  = (uint32_t)(mode);                               \
}
#endif

/**
 * @brief   DMA stream enable.
 * @note    This function can be invoked in both ISR or thread context.
 * @pre     The stream must have been allocated using @p dmaStreamAlloc().
 * @post    After use the stream can be released using @p dmaStreamRelease().
 *
 * @param[in] dmastp    pointer to a air32_dma_stream_t structure
 *
 * @special
 */
#define dmaStreamEnable(dmastp) {                                           \
  (dmastp)->channel->CCR |= AIR32_DMA_CR_EN;                                \
}

/**
 * @brief   DMA stream disable.
 * @details The function disables the specified stream and then clears any
 *          pending interrupt.
 * @note    This function can be invoked in both ISR or thread context.
 * @note    Interrupts enabling flags are set to zero after this call, see
 *          bug 3607518.
 * @pre     The stream must have been allocated using @p dmaStreamAlloc().
 * @post    After use the stream can be released using @p dmaStreamRelease().
 *
 * @param[in] dmastp    pointer to a air32_dma_stream_t structure
 *
 * @special
 */
#define dmaStreamDisable(dmastp) {                                          \
  (dmastp)->channel->CCR &= ~(AIR32_DMA_CR_TCIE | AIR32_DMA_CR_HTIE |       \
                              AIR32_DMA_CR_TEIE | AIR32_DMA_CR_EN);         \
  dmaStreamClearInterrupt(dmastp);                                          \
}

/**
 * @brief   DMA stream interrupt sources clear.
 * @note    This function can be invoked in both ISR or thread context.
 * @pre     The stream must have been allocated using @p dmaStreamAlloc().
 * @post    After use the stream can be released using @p dmaStreamRelease().
 *
 * @param[in] dmastp    pointer to a air32_dma_stream_t structure
 *
 * @special
 */
#define dmaStreamClearInterrupt(dmastp) {                                   \
  (dmastp)->dma->IFCR = AIR32_DMA_ISR_MASK << (dmastp)->shift;              \
}

/**
 * @brief   Starts a memory to memory operation using the specified stream.
 * @note    The default transfer data mode is "byte to byte" but it can be
 *          changed by specifying extra options in the @p mode parameter.
 * @pre     The stream must have been allocated using @p dmaStreamAlloc().
 * @post    After use the stream can be released using @p dmaStreamRelease().
 *
 * @param[in] dmastp    pointer to a air32_dma_stream_t structure
 * @param[in] mode      value to be written in the CCR register, this value
 *                      is implicitly ORed with:
 *                      - @p AIR32_DMA_CR_MINC
 *                      - @p AIR32_DMA_CR_PINC
 *                      - @p AIR32_DMA_CR_DIR_M2M
 *                      - @p AIR32_DMA_CR_EN
 *                      .
 * @param[in] src       source address
 * @param[in] dst       destination address
 * @param[in] n         number of data units to copy
 */
#define dmaStartMemCopy(dmastp, mode, src, dst, n) {                        \
  dmaStreamSetPeripheral(dmastp, src);                                      \
  dmaStreamSetMemory0(dmastp, dst);                                         \
  dmaStreamSetTransactionSize(dmastp, n);                                   \
  dmaStreamSetMode(dmastp, (mode) |                                         \
                           AIR32_DMA_CR_MINC | AIR32_DMA_CR_PINC |          \
                           AIR32_DMA_CR_DIR_M2M | AIR32_DMA_CR_EN);         \
}

/**
 * @brief   Polled wait for DMA transfer end.
 * @pre     The stream must have been allocated using @p dmaStreamAlloc().
 * @post    After use the stream can be released using @p dmaStreamRelease().
 *
 * @param[in] dmastp    pointer to a air32_dma_stream_t structure
 */
#define dmaWaitCompletion(dmastp) {                                         \
  while ((dmastp)->channel->CNDTR > 0U)                                     \
    ;                                                                       \
  dmaStreamDisable(dmastp);                                                 \
}
/** @} */

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#if !defined(__DOXYGEN__)
extern const air32_dma_stream_t _air32_dma_streams[AIR32_DMA_STREAMS];
#endif

#ifdef __cplusplus
extern "C" {
#endif
  void dmaInit(void);
  const air32_dma_stream_t *dmaStreamAllocI(uint32_t id,
                                            uint32_t priority,
                                            air32_dmaisr_t func,
                                            void *param);
  const air32_dma_stream_t *dmaStreamAlloc(uint32_t id,
                                           uint32_t priority,
                                           air32_dmaisr_t func,
                                           void *param);
  void dmaStreamFreeI(const air32_dma_stream_t *dmastp);
  void dmaStreamFree(const air32_dma_stream_t *dmastp);
  void dmaServeInterrupt(const air32_dma_stream_t *dmastp);
#if AIR32_DMA_SUPPORTS_DMAMUX == TRUE
  void dmaSetRequestSource(const air32_dma_stream_t *dmastp, uint32_t per);
#endif
#ifdef __cplusplus
}
#endif

#endif /* AIR32_DMA_H */

/** @} */
