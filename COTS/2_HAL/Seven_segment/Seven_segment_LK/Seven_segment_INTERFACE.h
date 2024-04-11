#ifndef  SEVEN_SEGMENT_INTERFACE_H_
#define  SEVEN_SEGMENT_INTERFACE_H_

ES_t Seven_Segment_enuInit(SEG_t * Copy_pstrSegConfig);

ES_t Seven_Segment_enuDisplayNum(u8 Copy_u8SegID,u8 Copy_u8Num);

ES_t Seven_Segment_enuEnableCommon(u8 Copy_u8SegID);

ES_t Seven_Segment_enuDisableCommon(u8 Copy_u8SegID);

ES_t Seven_Segment_enuEnableDot(u8 Copy_u8SegID);

ES_t Seven_Segment_enuDisableDot(u8 Copy_u8SegID);

ES_t Seven_Segment_enuClearDisplay(u8 Copy_u8SegID);

#endif