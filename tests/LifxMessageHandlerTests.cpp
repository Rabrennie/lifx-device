#include "LifxMessageHandler.h"
#include "LifxMessage.h"

#include <gtest/gtest.h>

byte packet[49]{
      //size
      0x31, 0x00,
      //protocol, origin, tagged, addressable
      0x00, 0x34,
      //source
      0x01, 0x02, 0x03, 0x04,
      // target
      0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00, 0x00,
      //reserved
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      //ack_requied, res_required
      0x03,
      //sequence
      0x55,
      //reserved
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      // type
      0x66, 0x00,
      //reserved
      0x00, 0x00,
      //payload
      0x00, 0x55, 0x55, 0xFF, 0xFF, 0xFF, 0xFF, 0xAC, 0x0D, 0x00, 0x04, 0x00, 0x00};

TEST(LifxMessageHandler, parseMessage_size)
{
  LifxMessage message;

  LifxMessageHandler::parseMessage(packet, 49, message);
  ASSERT_EQ(message.size, 49);
}

TEST(LifxMessageHandler, parseMessage_protocol)
{
  LifxMessage message;

  LifxMessageHandler::parseMessage(packet, 49, message);
  ASSERT_EQ(message.protocol, 1024);
}

TEST(LifxMessageHandler, parseMessage_origin)
{
  LifxMessage message;

  LifxMessageHandler::parseMessage(packet, 49, message);
  ASSERT_EQ(message.origin, 0);
}

TEST(LifxMessageHandler, parseMessage_tagged)
{
  LifxMessage message;

  LifxMessageHandler::parseMessage(packet, 49, message);
  ASSERT_EQ(message.tagged, 1);
}

TEST(LifxMessageHandler, parseMessage_addressable)
{
  LifxMessage message;

  LifxMessageHandler::parseMessage(packet, 49, message);
  ASSERT_EQ(message.addressable, 1);
}

TEST(LifxMessageHandler, parseMessage_source)
{
  LifxMessage message;

  LifxMessageHandler::parseMessage(packet, 49, message);
  ASSERT_EQ(message.source[0], 0x01);
  ASSERT_EQ(message.source[1], 0x02);
  ASSERT_EQ(message.source[2], 0x03);
  ASSERT_EQ(message.source[3], 0x04);
}

TEST(LifxMessageHandler, parseMessage_target)
{
  LifxMessage message;

  LifxMessageHandler::parseMessage(packet, 49, message);
  ASSERT_EQ(message.target[0], 0x06);
  ASSERT_EQ(message.target[1], 0x05);
  ASSERT_EQ(message.target[2], 0x04);
  ASSERT_EQ(message.target[3], 0x03);
  ASSERT_EQ(message.target[4], 0x02);
  ASSERT_EQ(message.target[5], 0x01);
  ASSERT_EQ(message.target[6], 0x00);
  ASSERT_EQ(message.target[7], 0x00);
}

TEST(LifxMessageHandler, parseMessage_res_required)
{
  LifxMessage message;

  LifxMessageHandler::parseMessage(packet, 49, message);
  ASSERT_EQ(message.res_required, 1);
}

TEST(LifxMessageHandler, parseMessage_ack_required)
{
  LifxMessage message;

  LifxMessageHandler::parseMessage(packet, 49, message);
  ASSERT_EQ(message.ack_required, 1);
}

TEST(LifxMessageHandler, parseMessage_sequence)
{
  LifxMessage message;

  LifxMessageHandler::parseMessage(packet, 49, message);
  ASSERT_EQ(message.sequence, 0x55);
}

TEST(LifxMessageHandler, parseMessage_type)
{
  LifxMessage message;

  LifxMessageHandler::parseMessage(packet, 49, message);
  ASSERT_EQ(message.type, 0x66);
}

TEST(LifxMessageHandler, parseMessage_payload)
{
  LifxMessage message;

  LifxMessageHandler::parseMessage(packet, 49, message);
  ASSERT_EQ(message.payload_size, 13);
  ASSERT_EQ(message.payload[0], 0x00);
  ASSERT_EQ(message.payload[1], 0x55);
  ASSERT_EQ(message.payload[2], 0x55);
  ASSERT_EQ(message.payload[3], 0xFF);
  ASSERT_EQ(message.payload[4], 0xFF);
  ASSERT_EQ(message.payload[5], 0xFF);
  ASSERT_EQ(message.payload[6], 0xFF);
  ASSERT_EQ(message.payload[7], 0xAC);
  ASSERT_EQ(message.payload[8], 0x0D);
  ASSERT_EQ(message.payload[9], 0x00);
  ASSERT_EQ(message.payload[10], 0x04);
  ASSERT_EQ(message.payload[11], 0x00);
  ASSERT_EQ(message.payload[12], 0x00);
}

TEST(LifxMessageHandler, buildPacketBuffer)
{
  LifxMessage * message;
  message->protocol = 1234;

  LifxMessageHandler::buildPacketBuffer(message);
}
