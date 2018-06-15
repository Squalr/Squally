#pragma once
#include "cocos2d.h"

#include "Engine/Maps/IDeserializer.h"
#include "Objects/Collision/CollisionObject.h"
#include "Resources.h"

using namespace cocos2d;

class CollisionDeserializer : public IDeserializer
{
public:
	CollisionDeserializer();
	~CollisionDeserializer();

	void onDeserializationRequest(DeserializationRequestArgs* args) override;

	static const std::string KeyCollisionTypeSolid;
	static const std::string KeyCollisionTypeWater;
	static const std::string KeyCollisionTypeSolidNpc;
	static const std::string KeyCollisionTypeSolidNpcFlying;

	static const std::string KeyCollisionPointsProperty;
};
