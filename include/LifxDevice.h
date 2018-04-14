#ifndef LIFX_DEVICE_HEADER
#define LIFX_DEVICE_HEADER

class LifxDevice {
    public:
        LifxDevice();

        void addCapability();
        void getCapabilities();

        virtual void getState() = 0;

        virtual void setColor() = 0;
        virtual void setPower() = 0;
        virtual void setWaveform() = 0;
        virtual void setWaveformOptional() = 0;
        virtual void setInfrared() = 0;
};

#endif