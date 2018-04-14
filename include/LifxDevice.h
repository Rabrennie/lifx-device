#ifndef LifxDevice_H
#define LifxDevice_H

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