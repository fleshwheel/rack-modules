#pragma once
#include <rack.hpp>


using namespace rack;

// Declare the Plugin, defined in plugin.cpp
extern Plugin* pluginInstance;

// Declare each Model, defined in each module source file
extern Model* modelOscillator;
extern Model* modelIntegrator;
extern Model* modelMultiplier;
extern Model* modelDot;
extern Model* modelMagnitude;