/*
 *  MATH.h
 *  Date   : 8 August , 2020
 *  Author : Ahmed ElKhouly
 *  Version: V01
 */
 
#ifndef RRC_CONFIG_H
#define RRC_CONFIG_H

/* Options : RCC_HSE_CRYSTAL
		   : RCC_HSE_RC
		   : RCC_HSI
		   : RCC_PLL
		   */
#define RCC_CLOCK_TYPE RCC_HSI

/* Options	:RCC_PLL_INPUT_HSI_DIV_2
			:RCC_PLL_INPUT_HSE_DIV_2
			:RCC_PLL_INPUT_HSE
			*/
/* Note : Select value only if you have PLL as input source */
#if RCC_CLOCK_TYPE	== RCC_PLL
#define RCC_PLL_INPUT	RCC_PLL_INPUT_HSE_DIV_2
#endif

/* Options : from 2 to 16 */
/* Note : Select value only if you have PLL as input source */
#if RCC_CLOCK_TYPE	== RCC_PLL
#define RCC_PLL_MUL_VAL	4
#endif

#endif /* RRC_CONFIG_H */
