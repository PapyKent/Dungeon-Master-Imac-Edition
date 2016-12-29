//
// Created by Quentin on 28/12/2016.
//

#include "../include/toolBox.h"

float toolBox::convertDegToRad(float deg) {
    return (deg*M_PI)/180;
}

float toolBox::convertRadToDeg(float rad) {
    return (rad/M_PI)*180;
}
