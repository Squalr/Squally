#pragma once
#include "cocos2d.h"

#include "Engine/GlobalDirector.h"
#include "Engine/GlobalNode.h"
#include "Events/DeserializationEvents.h"
#include "Objects/Collision/CollisionObject.h"
#include "Resources.h"

using namespace cocos2d;

class CollisionDeserializer : public GlobalNode
{
public:
	static void registerGlobalNode();

	void onDeserializationRequest(EventCustom* eventCustom);

private:
	CollisionDeserializer();
	~CollisionDeserializer();

	void initializeEventListeners() override;

	static CollisionDeserializer* instance;
};
