/* 
 * File:   LightPoint.cpp
 * Author: Fran_2
 * 
 * Created on 11 de mayo de 2011, 18:25
 */

#include "LightPoint.h"
#include "WasabiEngine/Utils/Vectors.h"

using namespace WasabiEngine;

LightPoint::LightPoint(int index) : Light(index) {
}

LightPoint::LightPoint(const LightPoint& orig) : Light(0) {
}

LightPoint::~LightPoint() {
}

void LightPoint::renderObject() {
    glEnable(GL_COLOR_MATERIAL);
    if (getAmbient() != NULL) {
        glMaterialfv(GL_FRONT, GL_AMBIENT, getAmbient()->ptr());
        glLightfv(getIndex(), GL_AMBIENT, getAmbient()->ptr());
    }
    if (getDiffuse() != NULL) {
        glMaterialfv(GL_FRONT, GL_DIFFUSE, getDiffuse()->ptr());
        glLightfv(getIndex(), GL_AMBIENT, getDiffuse()->ptr());
    }
    if (getSpecular() != NULL) {
        glMaterialfv(GL_FRONT, GL_SPECULAR, getSpecular()->ptr());
        glLightfv(getIndex(), GL_SPECULAR, getSpecular()->ptr());
    }
    float p[4] = {getPosition().x, getPosition().y, getPosition().z, 1}; //w -> 0: Directional, 1: Positional
    glLightfv(getIndex(), GL_POSITION, p);
    glLightf(getIndex(), GL_LINEAR_ATTENUATION, getAttenuation());
    glEnable(getIndex());
}
