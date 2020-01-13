/*
* File:   can_bit_parser.h
* Author: VBKesha
*
*/

#include <stdint.h>
#include "can_bit_parser.h"

#define MAX_CAN_MSG_LEN 64

static uint8_t bitarr_read_bit(uint8_t * arr, uint16_t offset_bit) {
    uint8_t byte_offset;
    uint8_t bit_offset;
    uint8_t mask;

    byte_offset = offset_bit / 8;
    bit_offset = offset_bit - (byte_offset * 8);
    mask = (1 << (7 - bit_offset));
    return ((arr[byte_offset] & mask) != 0) ? 1 : 0;
}

uint8_t can_read_uint8(uint8_t * arr, uint16_t offset_bit, uint8_t length) {
    uint8_t result;
    uint8_t i;

    result = 0;

    if (length > 8) {
        length = 8;
    }

    if ((offset_bit + length) > MAX_CAN_MSG_LEN * 8) {
        return 0;
    }

    for (i = 0; i<length; i++) {
        result = result << 1;
        result |= bitarr_read_bit(arr, offset_bit + i);
    }

    return result;
}

uint16_t can_read_uint16(uint8_t * arr, uint16_t offset_bit, uint8_t length) {
    uint16_t result;
    uint8_t i;

    result = 0;

    if (length > 16) {
        length = 16;
    }

    if ((offset_bit + length) > MAX_CAN_MSG_LEN * 8) {
        return 0;
    }

    for (i = 0; i<length; i++) {
        result = result << 1;
        result |= bitarr_read_bit(arr, offset_bit + i);
    }

    return result;
}
uint32_t can_read_uint32(uint8_t * arr, uint16_t offset_bit, uint8_t length) {
    uint32_t result;
    uint8_t i;

    result = 0;

    if (length > 32) {
        length = 32;
    }

    if ((offset_bit + length) > MAX_CAN_MSG_LEN * 8) {
        return 0;
    }

    for (i = 0; i<length; i++) {
        result = result << 1;
        result |= bitarr_read_bit(arr, offset_bit + i);
    }

    return result;
}

uint32_t can_read_float(uint8_t * arr, uint16_t offset_bit, uint8_t length) {
    uint32_t result;
    uint8_t i;

    result = 0;

    if (length > 32) {
        length = 32;
    }

    if ((offset_bit + length) > MAX_CAN_MSG_LEN * 8) {
        return 0;
    }

    for (i = 0; i<length; i++) {
        result = result << 1;
        result |= bitarr_read_bit(arr, offset_bit + i);
    }

    return result;
}
