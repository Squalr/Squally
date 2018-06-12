#pragma once
#include "cocos2d.h"

#include "Engine/Maps/SerializableLayer.h"
#include "Objects/Objects.h"
#include "Resources.h"
#include "Utils/GameUtils.h"

using namespace cocos2d;

class CollisionDeserializer
{
public:
	static SerializableLayer* deserialize(TMXObjectGroup* objectGroup);

	static const std::string KeyCollisionTypeProperty;
	static const std::string KeyCollisionTypeSolid;
	static const std::string KeyCollisionTypeWater;
	static const std::string KeyCollisionTypeSolidNpc;
	static const std::string KeyCollisionTypeSolidNpcFlying;

	static const std::string KeyCollisionPointsProperty;
};
