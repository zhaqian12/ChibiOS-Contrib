ifeq ($(USE_SMART_BUILD),yes)
ifneq ($(findstring HAL_USE_I2S TRUE,$(HALCONF)),)
PLATFORMSRC_CONTRIB += $(CHIBIOS_CONTRIB)/os/hal/ports/AT32/LLD/SPIv1/hal_i2s_lld.c
endif
ifneq ($(findstring HAL_USE_SPI TRUE,$(HALCONF)),)
PLATFORMSRC_CONTRIB += $(CHIBIOS_CONTRIB)/os/hal/ports/AT32/LLD/SPIv1/hal_spi_v2_lld.c
endif
else
PLATFORMSRC_CONTRIB += $(CHIBIOS_CONTRIB)/os/hal/ports/AT32/LLD/SPIv1/hal_i2s_lld.c
PLATFORMSRC_CONTRIB += $(CHIBIOS_CONTRIB)/os/hal/ports/AT32/LLD/SPIv1/hal_spi_v2_lld.c
endif

PLATFORMINC_CONTRIB += $(CHIBIOS_CONTRIB)/os/hal/ports/AT32/LLD/SPIv1
