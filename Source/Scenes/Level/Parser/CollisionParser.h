#pragma once
#include "cocos2d.h"

#include "Objects/Objects.h"
#include "Resources.h"
#include "Utils/GameUtils.h"

using namespace cocos2d;

class CollisionParser
{
public:
static Layer* parse(TMXObjectGroup* objectGroup);

};
