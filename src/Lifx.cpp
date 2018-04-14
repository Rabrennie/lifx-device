#include "Lifx.h"

Lifx::Lifx(LifxDevice *device) {
    this->device = device;
}
// TODO: add debug serial prints
void Lifx::begin() {
    this->Udp.begin(LIFX_PORT);
}

void Lifx::handle() {
    // do other stuff
    byte packet[LIFX_PACKET_LENGTH];

    int packetSize = this->Udp.parsePacket();
    if(packetSize) {
        this->Udp.read(packet, LIFX_PACKET_LENGTH);

        LifxMessage message;
        this->processPacket(packet, packetSize, message);

        this->handleMessage(message);
    }   
}