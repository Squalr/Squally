#pragma once
#include "cocos2d.h"

#include "Engine/Maps/SerializableLayer.h"
#include "Objects/Objects.h"
#include "Resources.h"
#include "Utils/GameUtils.h"

#include "ObjectDeserializer.h"

using namespace cocos2d;

class ParallaxDeserializer
{
public:
	static SerializableLayer* deserialize(TMXObjectGroup* objectGroup);
};
