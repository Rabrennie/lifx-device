// tests.cpp
#include "LifxMessageHandler.h"
#include "LifxMessage.h"

#include <gtest/gtest.h>

TEST(LifxMessageHandler, parseMessage)
{
  LifxMessage message;

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

  LifxMessageHandler::parseMessage(packet, 49, message);
  EXPECT_EQ(message.size, 49);

  EXPECT_EQ(message.protocol, 1024);
  EXPECT_EQ(message.origin, 0);
  EXPECT_EQ(message.tagged, 1);
  EXPECT_EQ(message.addressable, 1);

  EXPECT_EQ(message.source[0], 0x01);
  EXPECT_EQ(message.source[1], 0x02);
  EXPECT_EQ(message.source[2], 0x03);
  EXPECT_EQ(message.source[3], 0x04);

  EXPECT_EQ(message.target[0], 0x06);
  EXPECT_EQ(message.target[1], 0x05);
  EXPECT_EQ(message.target[2], 0x04);
  EXPECT_EQ(message.target[3], 0x03);
  EXPECT_EQ(message.target[4], 0x02);
  EXPECT_EQ(message.target[5], 0x01);
  EXPECT_EQ(message.target[6], 0x00);
  EXPECT_EQ(message.target[7], 0x00);

  EXPECT_EQ(message.res_required, 1);
  EXPECT_EQ(message.ack_required, 1);

  EXPECT_EQ(message.sequence, 0x55);

  EXPECT_EQ(message.type, 0x66);

  EXPECT_EQ(message.payload_size, 13);
  EXPECT_EQ(message.payload[0], 0x00);
  EXPECT_EQ(message.payload[1], 0x55);
  EXPECT_EQ(message.payload[2], 0x55);
  EXPECT_EQ(message.payload[3], 0xFF);
  EXPECT_EQ(message.payload[4], 0xFF);
  EXPECT_EQ(message.payload[5], 0xFF);
  EXPECT_EQ(message.payload[6], 0xFF);
  EXPECT_EQ(message.payload[7], 0xAC);
  EXPECT_EQ(message.payload[8], 0x0D);
  EXPECT_EQ(message.payload[9], 0x00);
  EXPECT_EQ(message.payload[10], 0x04);
  EXPECT_EQ(message.payload[11], 0x00);
  EXPECT_EQ(message.payload[12], 0x00);
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
