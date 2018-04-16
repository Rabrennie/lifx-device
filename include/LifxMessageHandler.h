#ifndef LIFX_MESSAGE_HANDLER_HEADER
#define LIFX_MESSAGE_HANDLER_HEADER
#include "LifxMessage.h"
#include "LifxConstants.h"
#include <cstring>
#include <stdint.h>
typedef uint8_t byte;

class LifxMessageHandler {
    public:
        LifxMessageHandler();
        static void parseMessage(byte *packet, int packetSize, LifxMessage &message);
        static void buildPacketBuffer(byte *packetBuffer, LifxMessage message);
};

#endif
