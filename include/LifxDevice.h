#ifndef LIFX_DEVICE_HEADER
#define LIFX_DEVICE_HEADER

class LifxDevice {
    public:
        LifxDevice();

        void addCapability();
        void getCapabilities();

        void getState();

        void setColor();
        void setPower();
        void setWaveform();
        void setWaveformOptional();
        void setInfrared();
};

#endif