#ifndef LIFX_MESSAGE_HEADER
#define LIFX_MESSAGE_HEADER

#include <stdint.h>
typedef uint8_t byte;

struct LifxMessage {
    /* frame */
  uint16_t size;
  uint16_t protocol:12;
  uint8_t  addressable:1;
  uint8_t  tagged:1;
  uint8_t  origin:2;
  byte source[4];
  /* frame address */
  byte  target[8];
  byte  reserved[6];
  uint8_t  res_required:1;
  uint8_t  ack_required:1;
  uint8_t  :6;
  uint8_t  sequence;
  /* protocol header */
  uint64_t :64;
  uint16_t type;
  uint16_t :16;
  /* variable length payload follows */
  byte payload[128];
  int payload_size;
};

#endif
