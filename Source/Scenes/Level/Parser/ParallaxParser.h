#pragma once
#include "cocos2d.h"

#include "Objects/Objects.h"
#include "Resources.h"
#include "Utils/GameUtils.h"

#include "ObjectParser.h"

using namespace cocos2d;

class ParallaxParser
{
public:
	static Layer* parse(TMXObjectGroup* objectGroup);
};
