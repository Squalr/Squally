#pragma once

#include "Engine/SmartNode.h"

/*
 *  This class is basically a container that holds the information about the height the target height and the speed of a single vertical slice of the water surface
 *  This Node won't be added to any Scene, and might actually be worth to convert this into a struct instead of a class
 *  Many LiquidColumns together compose a water surface (WaterNode)
 */
class LiquidColumn : public SmartNode
{
public:
    // creation
    static LiquidColumn *create()
    {
        // we call our custom creation method inline, BEWARE THAT WE DO NOT CALL THE AUTORELEASE since we want this node to stay alive even if not added to any parent
        auto ret = new LiquidColumn();
        ret->init();
        return ret;
    }
    
    // variables
    float targetHeight;   // the height we want to reach, based on the splash effect we are applying
    float height;         // the real height we reached so far
    float speed;          // the speed at which we try to reach the targetHeight
    
    // functions
    bool init();
    void initWithTargetHeight(float targetHeight, float height, float speed);
    void update(float dampening, float tension);
};
