#pragma once
#include "cocos2d.h"

#include "Engine/Maps/SerializableLayer.h"
#include "Objects/Objects.h"
#include "Resources.h"
#include "Utils/GameUtils.h"

using namespace cocos2d;

class ObjectDeserializer
{
public:
	static SerializableLayer* deserialize(TMXObjectGroup* objectGroup);
	static Sprite* loadObject(ValueMap object);
};
