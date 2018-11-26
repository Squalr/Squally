#pragma once
#include "cocos2d.h"

#include "Engine/Maps/IObjectDeserializer.h"
#include "Engine/Physics/CollisionObject.h"

using namespace cocos2d;

class CollisionDeserializer : public IObjectDeserializer
{
public:
	CollisionDeserializer();
	~CollisionDeserializer();

	void onDeserializationRequest(ObjectDeserializationRequestArgs* args) override;
};
