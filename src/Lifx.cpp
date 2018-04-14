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

void processPacket(byte *packet, int packetSize, LifxMessage &message) {
    message.size = packet[0] + (packet[1] << 8);
    
    // TODO: could be wrong
    message.protocol = (packet[2] + (packet[3] << 8)) & 0x400;
    message.addressable = (packet[2] + (packet[3] << 8)) & 0x03;
    message.tagged = (packet[2] + (packet[3] << 8)) & 0x04;
    message.origin = (packet[2] + (packet[3] << 8)) & 0x08;

    byte source[] = {
        packet[4],
        packet[5],
        packet[6],
        packet[7]
    };
    memcpy(message.source, source, 4);

    byte target[] = {
        packet[8],
        packet[9],
        packet[10],
        packet[11],
        packet[12],
        packet[13],
        packet[14],
        packet[15] 
    };
    memcpy(message.target, target, 8);

    byte reserved[] = {
        packet[16],
        packet[17],
        packet[18],
        packet[19],
        packet[20],
        packet[21],
    };
    memcpy(message.reserved, reserved, 6);

    message.ack_required = (packet[22] & 0x02);
    message.res_required = (packet[22] & 0x01);

    message.sequence = packet[23];

    message.type = packet[32] + (packet[33] << 8);

    int i;
    for (i = 36; i < packetSize; i++) {
        message.payload[i - 36] = packet[i];
    }

    message.payload_size = i;
}