// tests.cpp
#include "Lifx.h"
#include "LifxDevice.h"

#include <gtest/gtest.h>

class test : public LifxDevice {
    test() {}
};

TEST(Lifx, Costructor) { 
    test mockDevice();
    LifxDevice *device = new LifxDevice();
    Lifx *lifx = new Lifx(device);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}