/*
 *  MATH.h
 *  Date   : JULY 29, 2020
 *  Author : Ahmed ElKhouly
 *  Version: V01
 */

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(VAR,BIT) (VAR) |=  (1 << (BIT))
#define CLR_BIT(VAR,BIT) (VAR) &= ~(1 << (BIT))
#define TOG_BIT(VAR,BIT) (VAR) ^=  (1 << (BIT))
#define GET_BIT(VAR,BIT) (((VAR) >> (BIT)) & 0x01)

#endif /* BIT_MATH_H_ */
