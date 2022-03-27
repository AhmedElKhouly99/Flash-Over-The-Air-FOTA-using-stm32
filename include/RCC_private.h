/*
 *  MATH.h
 *  Date   : 8 August , 2020
 *  Author : Ahmed ElKhouly
 *  Version: V01
 */
 
#ifndef RRC_PRIVATE_H
#define RRC_PRIVATE_H
/* Register Definitions */
#define RCC_CR         *((u32*)0x40021000)
#define RCC_CFGR       *((u32*)0x40021004)
#define RCC_CIR        *((u32*)0x40021008)
#define RCC_APB2RSTR   *((u32*)0x4002100c)
#define RCC_APB1RSTS   *((u32*)0x40021010)
#define RCC_AHBENR     *((u32*)0x40021014)
#define RCC_APB2ENR    *((u32*)0x40021018)
#define RCC_APB1ENR    *((u32*)0x4002101c)
#define RCC_BDCR       *((u32*)0x40021020)
#define RCC_CSR        *((u32*)0x40021024)

/* Clock Type */
#define RCC_HSE_CRYSTAL 0
#define RCC_HSE_RC		1
#define RCC_HSI			2
#define RCC_PLL			3

/* PLL Options */
#define RCC_PLL_INPUT_HSI_DIV_2	0
#define RCC_PLL_INPUT_HSE_DIV_2	1
#define RCC_PLL_INPUT_HSE		2

#endif /* RRC_PRIVATE_H */
