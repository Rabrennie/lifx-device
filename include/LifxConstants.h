#ifndef LIFX_CONSTANTS_HEADER
#define LIFX_CONSTANTS_HEADER

#include <stdint.h>
typedef uint8_t byte;

// settings
static int const LIFX_PORT = 56700;
static int const LIFX_PROTOCOL = 0x400;
static int const LIFX_PACKET_HEADER_LENGTH = 36;
static int const LIFX_PACKET_MAX_LENGTH = 128;

// Device Message Types - https://lan.developer.lifx.com/docs/device-messages
static byte const GET_SERVICE = 0x02;
static byte const STATE_SERVICE = 0x03;

static byte const GET_HOST_INFO = 0x0C;
static byte const STATE_HOST_INFO = 0x0D;

static byte const GET_HOST_FIRMWARE = 0x0E;
static byte const STATE_HOST_FIRMWARE = 0x0F;

static byte const GET_WIFI_INFO = 0x10;
static byte const STATE_WIFI_INFO = 0x11;

static byte const GET_WIFI_FIRMWARE = 0x12;
static byte const STATE_WIFI_FIRMWARE = 0x13;

static byte const GET_POWER = 0x14;
static byte const SET_POWER = 0x15;
static byte const STATE_POWER = 0x16;

static byte const GET_LABEL = 0x17;
static byte const SET_LABEL = 0x18;
static byte const STATE_LABEL = 0x19;

static byte const GET_VERSION = 0x20;
static byte const STATE_VERSION = 0x21;

static byte const GET_INFO = 0x22;
static byte const STATE_INFO = 0x23;

static byte const ACKNOWLEDGEMENT = 0x2D;

static byte const GET_LOCATION = 0x30;
static byte const SET_LOCATION = 0x31;
static byte const STATE_LOCATION = 0x32;

static byte const GET_GROUP = 0x33;
static byte const SET_GROUP = 0x34;
static byte const STATE_GROUP = 0x35;

static byte const ECHO_REQUEST = 0x3A;
static byte const ECHO_RESPONSE = 0x3B;

// light messages

static byte const GET = 0x65;
static byte const STATE = 0x6B;

#endif
