/*
* File:   can_bit_parser.h
* Author: VBKesha
*
*/


#ifndef CAN_BIT_PARSER_H
#define	CAN_BIT_PARSER_H

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

    uint8_t can_read_uint8(uint8_t * arr, uint16_t offset_bit, uint8_t length);
    uint16_t can_read_uint16(uint8_t * arr, uint16_t offset_bit, uint8_t length);
    uint32_t can_read_uint32(uint8_t * arr, uint16_t offset_bit, uint8_t length);
    uint32_t can_read_float(uint8_t * arr, uint16_t offset_bit, uint8_t length);

#ifdef	__cplusplus
}
#endif

#endif	/* CAN_BIT_PARSER_H */

#pragma once
