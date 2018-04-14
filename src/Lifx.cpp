#include "Lifx.h"
#include <Arduino.h>

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
    byte packet[LIFX_PACKET_MAX_LENGTH];
    this->Udp.read(packet, LIFX_PACKET_MAX_LENGTH);

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

  message.payload_size = packetSize - LIFX_PACKET_HEADER_LENGTH;
  memcpy(message.payload, packet + LIFX_PACKET_HEADER_LENGTH, message.payload_size);
}

void Lifx::handleMessage(LifxMessage message)
{
  if (message.tagged == 0 && memcmp(message.target, this->device->getMacAddress(), 8) == 0)
  {
    return;
  }

  Serial.println(message.type, HEX);

  if (message.type == GET_SERVICE)
  {
    LifxMessage response;
    response.type = STATE_SERVICE;
    response.protocol = LIFX_PROTOCOL;
    byte stateServiceData[] = {
        0x01, //UDP
        lowByte(LIFX_PORT),
        highByte(LIFX_PORT),
        0x00,
        0x00};

    memcpy(response.payload, stateServiceData, sizeof(stateServiceData));
    response.payload_size = sizeof(stateServiceData);
    this->sendMessage(response, true);
  }

  if (message.type == GET_WIFI_FIRMWARE)
  {
    LifxMessage response;
    response.type = STATE_WIFI_FIRMWARE;
    response.protocol = LIFX_PROTOCOL;

    byte WifiVersionData[] = {
        0x00, 0x70, 0xA6, 0xC7, 0x74, 0xF0, 0xDA, 0x13, //build timestamp
        0xc0, 0x0c, 0x07, 0x00, 0x48, 0x46, 0xd9, 0x43, //install timestamp
        lowByte(1),
        highByte(1),
        lowByte(2),
        highByte(2)};

    memcpy(response.payload, WifiVersionData, sizeof(WifiVersionData));
    response.payload_size = sizeof(WifiVersionData);
    this->sendMessage(response, true);
  }
}

// TODO: refactor
void Lifx::sendMessage(LifxMessage &message, bool broadcast)
{
  IPAddress remote_addr(Udp.remoteIP());

  if (broadcast)
  {
    remote_addr[3] = 255;
  }

  Udp.beginPacket(remote_addr, Udp.remotePort());

  // size
  Udp.write(lowByte(LIFX_PACKET_HEADER_LENGTH + message.payload_size));
  Udp.write(highByte(LIFX_PACKET_HEADER_LENGTH + message.payload_size));

  // protocol, addressable, tagged, origin
  uint16_t test = (message.protocol + (message.addressable << 12) + (message.tagged << 13) + (message.origin << 14)) >> 8;
  Udp.write(lowByte(test));
  Udp.write(highByte(test));

  // source
  unsigned char *source = (unsigned char *)&message.source;
  Udp.write(source[0]);
  Udp.write(source[1]);
  Udp.write(source[2]);
  Udp.write(source[3]);

  // target
  Udp.write(this->device->getMacAddress(), 8);

  Udp.write(lowByte(0x00));
  Udp.write(lowByte(0x00));
  Udp.write(lowByte(0x00));
  Udp.write(lowByte(0x00));
  Udp.write(lowByte(0x00));
  Udp.write(lowByte(0x00));

  // ack and res
  Udp.write(message.ack_required + message.res_required);

  Udp.write(message.sequence);

  Udp.write(lowByte(0x00));
  Udp.write(lowByte(0x00));
  Udp.write(lowByte(0x00));
  Udp.write(lowByte(0x00));
  Udp.write(lowByte(0x00));
  Udp.write(lowByte(0x00));
  Udp.write(lowByte(0x00));
  Udp.write(lowByte(0x00));

  Udp.write(lowByte(message.type));
  Udp.write(highByte(message.type));

  for (int i = 0; i < message.payload_size; i++)
  {
    Udp.write(lowByte(message.payload[i]));
  }

  Udp.endPacket();
}
