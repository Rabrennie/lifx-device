#include "Lifx.h"

Lifx::Lifx(LifxDevice *device)
{
  this->device = device;
}
// TODO: add debug serial prints
void Lifx::begin()
{
  this->Udp.begin(LIFX_PORT);
}

void Lifx::handle()
{
  int packetSize = this->Udp.parsePacket();
  if (packetSize)
  {
    byte packet[LIFX_PACKET_LENGTH];
    this->Udp.read(packet, LIFX_PACKET_LENGTH);

    LifxMessage message;
    this->processPacket(packet, packetSize, message);

    this->handleMessage(message);
  }
}

void Lifx::processPacket(byte *packet, int packetSize, LifxMessage &message)
{
  message.size = packet[0] + (packet[1] << 8);

  message.protocol = (packet[2] + (packet[3] << 8)) & 0x7FF;
  message.addressable = ((packet[2] + (packet[3] << 8)) & 0x1000) >> 12;
  message.tagged = ((packet[2] + (packet[3] << 8)) & 0x2000) >> 13;
  message.origin = ((packet[2] + (packet[3] << 8)) & 0xC000) >> 14;

  memcpy(message.source, packet + 4, 4);
  memcpy(message.target, packet + 8, 8);
  memcpy(message.reserved, packet + 16, 6);

  message.ack_required = (packet[22] & 0x02);
  message.res_required = (packet[22] & 0x01);

  message.sequence = packet[23];

  message.type = packet[32] + (packet[33] << 8);

  message.payload_size = packetSize - 36;
  memcpy(message.payload, packet + 36, message.payload_size);
}

void Lifx::handleMessage(LifxMessage message)
{

  if (message.tagged != 1 && message.target != device->getMacAddress())
  {
    return;
  }

}

void Lifx::sendMessage(LifxMessage &message, bool broadcast)
{
  // broadcast packet on local subnet
  IPAddress remote_addr(Udp.remoteIP());

  if (broadcast)
  {
    remote_addr[3] = 255;
  }

  Udp.beginPacket(remote_addr, Udp.remotePort());
  // do packet stuff

  Udp.endPacket();
}
