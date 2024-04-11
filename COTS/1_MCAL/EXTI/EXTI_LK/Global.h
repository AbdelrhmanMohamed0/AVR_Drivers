
/*
 * Global.h
 *
 * Created: 10/04/2024 05:12:32 م
 *  Author: Abdelrhman
 */ 
#ifndef GLOBAL_H_
#define GLOBAL_H_

#define ACTIVE 1
#define DEACTIVE 0

 typedef enum
 {
	 LOW_LEVEL = 0,
	 ANY_LOGIC_CHANGE,
	 FALLING_EDGE,
	 RISING_EDGE,
 } TriggerEdge_type;

 typedef enum
 {
	 EX_INT0 = 0,
	 EX_INT1,
	 EX_INT2
 } ExInterruptSource_type;
 
#endif
