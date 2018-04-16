#include "LifxMessageHandler.h"

void LifxMessageHandler::parseMessage(byte *packet, int packetSize, LifxMessage &message)
{
  message.size = packet[0] + (packet[1] << 8);

  message.protocol = (packet[2] + (packet[3] << 8)) & 0x7FF;
  message.addressable = ((packet[2] + (packet[3] << 8)) & 0x1000) >> 12;
  message.tagged = ((packet[2] + (packet[3] << 8)) & 0x2000) >> 13;
  message.origin = ((packet[2] + (packet[3] << 8)) & 0xC000) >> 14;

  memcpy(message.source, packet + 4, 4);
  memcpy(message.target, packet + 8, 8);
  memcpy(message.reserved, packet + 16, 6);

  message.ack_required = (packet[22] & 0x02) >> 0x01;
  message.res_required = (packet[22] & 0x01);

  message.sequence = packet[23];

  message.type = packet[32] + (packet[33] << 8);

  message.payload_size = packetSize - LIFX_PACKET_HEADER_LENGTH;
  memcpy(message.payload, packet + LIFX_PACKET_HEADER_LENGTH, message.payload_size);
}

void LifxMessageHandler::buildPacketBuffer(byte *packetBuffer, LifxMessage message)
{

}
