#include "Lifx.h"

Lifx::Lifx(LifxDevice *device) {
    this->device = device;
}

void Lifx::begin() {
    // do listen stuff
}

void Lifx::handle() {
    // do other stuff
}

void Lifx::setColor() {
    // do network stuff
    this->device->setColor();
}