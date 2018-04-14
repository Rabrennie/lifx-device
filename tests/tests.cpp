// tests.cpp
#include "Lifx.h"
#include "LifxDevice.h"

#include <gtest/gtest.h>

class test : public LifxDevice {
    public:
        test() {}
        ~test() {}

        void getState(){}

        void setColor(){}
        void setPower(){}
        void setWaveform(){}
        void setWaveformOptional(){}
        void setInfrared(){}
};

TEST(Lifx, Costructor) { 
    test mockDevice();
    LifxDevice *device = new test();
    Lifx *lifx = new Lifx(device);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}