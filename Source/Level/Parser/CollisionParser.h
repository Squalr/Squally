#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Utils/GameUtils.h"
#include "Objects/Objects.h"

using namespace cocos2d;

class CollisionParser
{
public:
static Layer* parse(TMXObjectGroup* objectGroup);

};
