#pragma once
#include "cocos2d.h"

#include "Engine/Events/DeserializationEvents.h"
#include "Engine/GlobalDirector.h"
#include "Engine/GlobalNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Resources.h"

using namespace cocos2d;

class CollisionMapper : public GlobalNode
{
public:
	static void registerGlobalNode();

	void onMapRequest(EventCustom* eventCustom);

private:
	CollisionMapper();
	~CollisionMapper();

	void initializeEventListeners() override;

	static const std::string KeyCollisionTypeSolid;
	static const std::string KeyCollisionTypeWater;
	static const std::string KeyCollisionTypeSolidNpc;
	static const std::string KeyCollisionTypeSolidNpcFlying;

	static CollisionMapper* instance;
};
