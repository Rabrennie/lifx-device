#ifndef LIFX_HEADER
#define LIFX_HEADER

#include "LifxDevice.h"
#include "LifxMessage.h"
#include "LifxConstants.h"

#include <WiFiUDP.h>

class Lifx {
    public:
        Lifx(LifxDevice *device);

        void begin();
        void handle();
    private:
        LifxDevice *device;
        WiFiUDP Udp;

        void sendMessage(LifxMessage message, bool broadcast);
        void processPacket(byte *packet, int packetSize, LifxMessage &lifxMessage);
        void handleMessage(LifxMessage lifxMessage);
};

#endif