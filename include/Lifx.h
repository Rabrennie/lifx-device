#include "LifxDevice.h"

class Lifx {
    public:
        Lifx(LifxDevice *device);

        void begin();
        void handle();
    private:
        LifxDevice *device;

        void setColor();
};