/**
 ******************************************************************************
 * @addtogroup Revolution Revolution configuration files
 * @{
 * @brief Configures the revolution board
 * @{
 *
 * @file       pios_board.c
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2011.
 * @brief      Defines board specific static initializers for hardware for the Revolution board.
 * @see        The GNU Public License (GPL) Version 3
 *
 *****************************************************************************/
/* 
 * This program is free software; you can redistribute it and/or modify 
 * it under the terms of the GNU General Public License as published by 
 * the Free Software Foundation; either version 3 of the License, or 
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License 
 * for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with this program; if not, write to the Free Software Foundation, Inc., 
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include <pios.h>

#include <openpilot.h>
#include <uavobjectsinit.h>
#include "hwsettings.h"
#include "manualcontrolsettings.h"

#include "board_hw_defs.c"

/**
 * Sensor configurations 
 */
#if defined(PIOS_INCLUDE_HMC5883)
#include "pios_hmc5883.h"
static const struct pios_exti_cfg pios_exti_hmc5883_cfg __exti_config = {
	.vector = PIOS_HMC5883_IRQHandler,
	.line = EXTI_Line5,
	.pin = {
		.gpio = GPIOB,
		.init = {
			.GPIO_Pin = GPIO_Pin_5,
			.GPIO_Speed = GPIO_Speed_100MHz,
			.GPIO_Mode = GPIO_Mode_IN,
			.GPIO_OType = GPIO_OType_OD,
			.GPIO_PuPd = GPIO_PuPd_NOPULL,
		},
	},
	.irq = {
		.init = {
			.NVIC_IRQChannel = EXTI9_5_IRQn,
			.NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_LOW,
			.NVIC_IRQChannelSubPriority = 0,
			.NVIC_IRQChannelCmd = ENABLE,
		},
	},
	.exti = {
		.init = {
			.EXTI_Line = EXTI_Line5, // matches above GPIO pin
			.EXTI_Mode = EXTI_Mode_Interrupt,
			.EXTI_Trigger = EXTI_Trigger_Rising,
			.EXTI_LineCmd = ENABLE,
		},
	},
};

static const struct pios_hmc5883_cfg pios_hmc5883_cfg = {
	.exti_cfg = &pios_exti_hmc5883_cfg,
	.M_ODR = PIOS_HMC5883_ODR_75,
	.Meas_Conf = PIOS_HMC5883_MEASCONF_NORMAL,
	.Gain = PIOS_HMC5883_GAIN_1_9,
	.Mode = PIOS_HMC5883_MODE_CONTINUOUS,

};
#endif /* PIOS_INCLUDE_HMC5883 */

/**
 * Configuration for the MS5611 chip
 */
#if defined(PIOS_INCLUDE_MS5611)
#include "pios_ms5611.h"
static const struct pios_ms5611_cfg pios_ms5611_cfg = {
	.oversampling = 1,
};
#endif /* PIOS_INCLUDE_MS5611 */

/**
 * Configuration for the BMA180 chip
 */
#if defined(PIOS_INCLUDE_BMA180)
#include "pios_bma180.h"
static const struct pios_exti_cfg pios_exti_bma180_cfg __exti_config = {
	.vector = PIOS_BMA180_IRQHandler,
	.line = EXTI_Line4,
	.pin = {
		.gpio = GPIOC,
		.init = {
			.GPIO_Pin = GPIO_Pin_4,
			.GPIO_Speed = GPIO_Speed_100MHz,
			.GPIO_Mode = GPIO_Mode_IN,
			.GPIO_OType = GPIO_OType_OD,
			.GPIO_PuPd = GPIO_PuPd_NOPULL,
		},
	},
	.irq = {
		.init = {
			.NVIC_IRQChannel = EXTI4_IRQn,
			.NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_LOW,
			.NVIC_IRQChannelSubPriority = 0,
			.NVIC_IRQChannelCmd = ENABLE,
		},
	},
	.exti = {
		.init = {
			.EXTI_Line = EXTI_Line4, // matches above GPIO pin
			.EXTI_Mode = EXTI_Mode_Interrupt,
			.EXTI_Trigger = EXTI_Trigger_Rising,
			.EXTI_LineCmd = ENABLE,
		},
	},
};
static const struct pios_bma180_cfg pios_bma180_cfg = {
	.exti_cfg = &pios_exti_bma180_cfg,
	.bandwidth = BMA_BW_600HZ,
	.range = BMA_RANGE_8G,
};
#endif /* PIOS_INCLUDE_BMA180 */

/**
 * Configuration for the MPU6000 chip
 */
#if defined(PIOS_INCLUDE_MPU6000)
#include "pios_mpu6000.h"
static const struct pios_exti_cfg pios_exti_mpu6000_cfg __exti_config = {
	.vector = PIOS_MPU6000_IRQHandler,
	.line = EXTI_Line8,
	.pin = {
		.gpio = GPIOD,
		.init = {
			.GPIO_Pin = GPIO_Pin_8,
			.GPIO_Speed = GPIO_Speed_100MHz,
			.GPIO_Mode = GPIO_Mode_IN,
			.GPIO_OType = GPIO_OType_OD,
			.GPIO_PuPd = GPIO_PuPd_NOPULL,
		},
	},
	.irq = {
		.init = {
			.NVIC_IRQChannel = EXTI9_5_IRQn,
			.NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_HIGH,
			.NVIC_IRQChannelSubPriority = 0,
			.NVIC_IRQChannelCmd = ENABLE,
		},
	},
	.exti = {
		.init = {
			.EXTI_Line = EXTI_Line8, // matches above GPIO pin
			.EXTI_Mode = EXTI_Mode_Interrupt,
			.EXTI_Trigger = EXTI_Trigger_Rising,
			.EXTI_LineCmd = ENABLE,
		},
	},
};

static const struct pios_mpu6000_cfg pios_mpu6000_cfg = {
	.exti_cfg = &pios_exti_mpu6000_cfg,
	.Fifo_store = PIOS_MPU6000_FIFO_TEMP_OUT | PIOS_MPU6000_FIFO_GYRO_X_OUT | PIOS_MPU6000_FIFO_GYRO_Y_OUT | PIOS_MPU6000_FIFO_GYRO_Z_OUT,
	// Clock at 8 khz, downsampled by 8 for 1khz
	.Smpl_rate_div = 7, 
	.interrupt_cfg = PIOS_MPU6000_INT_CLR_ANYRD,
	.interrupt_en = PIOS_MPU6000_INTEN_DATA_RDY,
	.User_ctl = PIOS_MPU6000_USERCTL_FIFO_EN,
	.Pwr_mgmt_clk = PIOS_MPU6000_PWRMGMT_PLL_X_CLK,
	.gyro_range = PIOS_MPU6000_SCALE_500_DEG,
	.filter = PIOS_MPU6000_LOWPASS_256_HZ
};
#endif /* PIOS_INCLUDE_MPU6000 */

/**
 * Configuration for L3GD20 chip
 */
#if defined(PIOS_INCLUDE_L3GD20)
#include "pios_l3gd20.h"
static const struct pios_exti_cfg pios_exti_l3gd20_cfg __exti_config = {
	.vector = PIOS_L3GD20_IRQHandler,
	.line = EXTI_Line8,
	.pin = {
		.gpio = GPIOD,
		.init = {
			.GPIO_Pin = GPIO_Pin_8,
			.GPIO_Speed = GPIO_Speed_100MHz,
			.GPIO_Mode = GPIO_Mode_IN,
			.GPIO_OType = GPIO_OType_OD,
			.GPIO_PuPd = GPIO_PuPd_NOPULL,
		},
	},
	.irq = {
		.init = {
			.NVIC_IRQChannel = EXTI9_5_IRQn,
			.NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_HIGH,
			.NVIC_IRQChannelSubPriority = 0,
			.NVIC_IRQChannelCmd = ENABLE,
		},
	},
	.exti = {
		.init = {
			.EXTI_Line = EXTI_Line8, // matches above GPIO pin
			.EXTI_Mode = EXTI_Mode_Interrupt,
			.EXTI_Trigger = EXTI_Trigger_Rising,
			.EXTI_LineCmd = ENABLE,
		},
	},
};

static const struct pios_l3gd20_cfg pios_l3gd20_cfg = {
	.exti_cfg = &pios_exti_l3gd20_cfg,
	.range = PIOS_L3GD20_SCALE_500_DEG,
};
#endif /* PIOS_INCLUDE_L3GD20 */


static const struct flashfs_cfg flashfs_m25p_cfg = {
	.table_magic = 0x85FB3D35,
	.obj_magic = 0x3015A371,
	.obj_table_start = 0x00000010,
	.obj_table_end = 0x00010000,
	.sector_size = 0x00010000,
};

static const struct pios_flash_jedec_cfg flash_m25p_cfg = {
	.sector_erase = 0xD8,
	.chip_erase = 0xC7
};


/**
 * PIOS_Board_Init()
 * initializes all the core subsystems on this specific hardware
 * called from System/openpilot.c
 */
void PIOS_Board_Init(void) {
	
	/* Delay system */
	PIOS_DELAY_Init();

	PIOS_LED_Init(&pios_led_cfg);

#ifdef PIOS_DEBUG_ENABLE_DEBUG_PINS
	PIOS_DEBUG_Init(&pios_tim_servo_all_channels, NELEMENTS(pios_tim_servo_all_channels));
#endif	/* PIOS_DEBUG_ENABLE_DEBUG_PINS */
	
	
	/* Set up the SPI interface to the accelerometer*/
	if (PIOS_SPI_Init(&pios_spi_accel_id, &pios_spi_accel_cfg)) {
		PIOS_DEBUG_Assert(0);
	}
	
	/* Set up the SPI interface to the gyro */
	if (PIOS_SPI_Init(&pios_spi_gyro_id, &pios_spi_gyro_cfg)) {
		PIOS_DEBUG_Assert(0);
	}
#if !defined(PIOS_FLASH_ON_ACCEL)
	/* Set up the SPI interface to the flash */
	if (PIOS_SPI_Init(&pios_spi_flash_id, &pios_spi_flash_cfg)) {
		PIOS_DEBUG_Assert(0);
	}
	PIOS_Flash_Jedec_Init(pios_spi_flash_id, 0, &flash_m25p_cfg);
#else
	PIOS_Flash_Jedec_Init(pios_spi_accel_id, 1, &flash_m25p_cfg);
#endif
	PIOS_FLASHFS_Init(&flashfs_m25p_cfg);
	
#if defined(PIOS_OVERO_SPI)
	/* Set up the SPI interface to the gyro */
	if (PIOS_SPI_Init(&pios_spi_overo_id, &pios_spi_overo_cfg)) {
		PIOS_DEBUG_Assert(0);
	}
#endif

	/* Initialize UAVObject libraries */
	EventDispatcherInitialize();
	UAVObjInitialize();
	
	HwSettingsInitialize();
	
#if defined(PIOS_INCLUDE_RTC)
	PIOS_RTC_Init(&pios_rtc_main_cfg);
#endif

	/* Initialize the alarms library */
	AlarmsInitialize();

	/* Initialize the task monitor library */
	TaskMonitorInitialize();

	/* Set up pulse timers */
	PIOS_TIM_InitClock(&tim_1_cfg);
	PIOS_TIM_InitClock(&tim_3_cfg);
	PIOS_TIM_InitClock(&tim_4_cfg);
	PIOS_TIM_InitClock(&tim_4_cfg);
	PIOS_TIM_InitClock(&tim_5_cfg);
	PIOS_TIM_InitClock(&tim_9_cfg);
	PIOS_TIM_InitClock(&tim_10_cfg);
	PIOS_TIM_InitClock(&tim_11_cfg);

	/* IAP System Setup */
	//PIOS_IAP_Init();
	
#if defined(PIOS_INCLUDE_COM)
#if defined(PIOS_INCLUDE_GPS)

	uint32_t pios_usart_gps_id;
	if (PIOS_USART_Init(&pios_usart_gps_id, &pios_usart_telem_main_cfg)) {
		PIOS_Assert(0);
	}
	
	uint8_t * rx_buffer = (uint8_t *) pvPortMalloc(PIOS_COM_GPS_RX_BUF_LEN);
	PIOS_Assert(rx_buffer);
	if (PIOS_COM_Init(&pios_com_gps_id, &pios_usart_com_driver, pios_usart_gps_id,
					  rx_buffer, PIOS_COM_GPS_RX_BUF_LEN,
					  NULL, 0)) {
		PIOS_Assert(0);
	}

#endif	/* PIOS_INCLUDE_GPS */
	
#if defined(PIOS_INCLUDE_COM_AUX)
	{
		uint32_t pios_usart_aux_id;
		
		if (PIOS_USART_Init(&pios_usart_aux_id, &pios_usart_aux_cfg)) {
			PIOS_DEBUG_Assert(0);
		}
		
		const uint32_t BUF_SIZE = 512;
		uint8_t * rx_buffer = (uint8_t *) pvPortMalloc(BUF_SIZE);
		uint8_t * tx_buffer = (uint8_t *) pvPortMalloc(BUF_SIZE);
		PIOS_Assert(rx_buffer);
		PIOS_Assert(tx_buffer);
		
		if (PIOS_COM_Init(&pios_com_aux_id, &pios_usart_com_driver, pios_usart_aux_id,
						  rx_buffer, BUF_SIZE,
						  tx_buffer, BUF_SIZE)) {
			PIOS_DEBUG_Assert(0);
		}
	}
#else
	pios_com_aux_id = 0;
#endif  /* PIOS_INCLUDE_COM_AUX */

#if defined(PIOS_INCLUDE_COM_TELEM)
	{ /* Eventually add switch for this port function */
		uint32_t pios_usart_telem_rf_id;
		if (PIOS_USART_Init(&pios_usart_telem_rf_id, &pios_usart_gps_cfg)) {
			PIOS_Assert(0);
		}
		
		uint8_t * rx_buffer = (uint8_t *) pvPortMalloc(PIOS_COM_TELEM_RF_RX_BUF_LEN);
		uint8_t * tx_buffer = (uint8_t *) pvPortMalloc(PIOS_COM_TELEM_RF_TX_BUF_LEN);
		PIOS_Assert(rx_buffer);
		PIOS_Assert(tx_buffer);
		if (PIOS_COM_Init(&pios_com_telem_rf_id, &pios_usart_com_driver, pios_usart_telem_rf_id,
						  rx_buffer, PIOS_COM_TELEM_RF_RX_BUF_LEN,
						  tx_buffer, PIOS_COM_TELEM_RF_TX_BUF_LEN)) {
			PIOS_Assert(0);
		}
	}
#else
	pios_com_telem_rf_id = 0;
#endif	/* PIOS_INCLUDE_COM_TELEM */

#endif	/* PIOS_INCLUDE_COM */
	
	// Set up spektrum receiver
	enum pios_dsm_proto proto;
	proto = PIOS_DSM_PROTO_DSM2;
	
	uint32_t pios_usart_dsm_id;
	if (PIOS_USART_Init(&pios_usart_dsm_id, &pios_usart_dsm_main_cfg)) {
		PIOS_Assert(0);
	}

	uint32_t pios_dsm_id;
	if (PIOS_DSM_Init(&pios_dsm_id,
					  &pios_dsm_main_cfg,
					  &pios_usart_com_driver,
					  pios_usart_dsm_id,
					  proto, 0)) {
		PIOS_Assert(0);
	}
	
	uint32_t pios_dsm_rcvr_id;
	if (PIOS_RCVR_Init(&pios_dsm_rcvr_id, &pios_dsm_rcvr_driver, pios_dsm_id)) {
		PIOS_Assert(0);
	}
	pios_rcvr_group_map[MANUALCONTROLSETTINGS_CHANNELGROUPS_DSMMAINPORT] = pios_dsm_rcvr_id;

#if defined(PIOS_INCLUDE_PWM) && defined(PIOS_INCLUDE_RCVR)
	/* Set up the receiver port.  Later this should be optional */
	uint32_t pios_pwm_id;
	PIOS_PWM_Init(&pios_pwm_id, &pios_pwm_cfg);
	
	uint32_t pios_pwm_rcvr_id;
	if (PIOS_RCVR_Init(&pios_pwm_rcvr_id, &pios_pwm_rcvr_driver, pios_pwm_id)) {
		PIOS_Assert(0);
	}
	pios_rcvr_group_map[MANUALCONTROLSETTINGS_CHANNELGROUPS_PWM] = pios_pwm_rcvr_id;
#endif

	/* Set up the servo outputs */
	PIOS_Servo_Init(&pios_servo_cfg);

	if (PIOS_I2C_Init(&pios_i2c_mag_adapter_id, &pios_i2c_mag_adapter_cfg)) {
		PIOS_DEBUG_Assert(0);
	}

	if (PIOS_I2C_Init(&pios_i2c_pressure_adapter_id, &pios_i2c_pressure_adapter_cfg)) {
		PIOS_DEBUG_Assert(0);
	}
	
	PIOS_DELAY_WaitmS(500);

#if defined(PIOS_INCLUDE_BMA180)
	PIOS_BMA180_Init(pios_spi_accel_id, 0, &pios_bma180_cfg);
	PIOS_Assert(PIOS_BMA180_Test() == 0);
#endif
#if defined(PIOS_INCLUDE_MPU6000)
	PIOS_MPU6000_Attach(pios_spi_gyro_id);
	PIOS_MPU6000_Init(&pios_mpu6000_cfg);
//	PIOS_Assert(PIOS_MPU6000_Test() == 0);
#elif defined(PIOS_INCLUDE_L3GD20)
	PIOS_L3GD20_Init(pios_spi_gyro_id, 0, &pios_l3gd20_cfg);
	PIOS_Assert(PIOS_L3GD20_Test() == 0);
#else
	PIOS_Assert(0);
#endif


	PIOS_HMC5883_Init(&pios_hmc5883_cfg);
	
	PIOS_MS5611_Init(&pios_ms5611_cfg, pios_i2c_pressure_adapter_id);
}

/**
 * @}
 * @}
 */

