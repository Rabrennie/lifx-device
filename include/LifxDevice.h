#ifndef LIFX_DEVICE_HEADER
#define LIFX_DEVICE_HEADER
#include <stdint.h>
typedef uint8_t byte;

class LifxDevice {
    public:
        LifxDevice();
        byte mac[8] = {
            0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x7
        };

        void addCapability();
        void getCapabilities();
        byte * getMacAddress();

        virtual void getState() = 0;

        virtual void setColor() = 0;
        virtual void setPower() = 0;
        virtual void setWaveform() = 0;
        virtual void setWaveformOptional() = 0;
        virtual void setInfrared() = 0;
};

#endif
