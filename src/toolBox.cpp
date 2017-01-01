#include "../include/toolBox.h"

float toolBox::convertDegToRad(float deg) {
    return (deg*M_PI)/180;
}

float toolBox::convertRadToDeg(float rad) {
    return (rad/M_PI)*180;
}

