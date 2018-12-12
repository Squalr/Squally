#pragma once

#include "Engine/Events/CollisionMappingEvents.h"
#include "Engine/GlobalNode.h"
#include "Scenes/Maps/Platformer/Physics/PlatformerCollisionType.h"

namespace cocos2d
{
	class EventCustom;
}

class PlatformerCollisionMapping : public GlobalNode
{
public:
	static void registerGlobalNode();

	void onAllowedCollisionsMapRequest(cocos2d::EventCustom* eventCustom);
	void onMapKeyMappingRequest(cocos2d::EventCustom* eventCustom);

	static const std::string MapKeyCollisionTypeSolid;
	static const std::string MapKeyCollisionTypePassThrough;
	static const std::string MapKeyCollisionTypePlayer;
	static const std::string MapKeyCollisionTypeNpc;
	static const std::string MapKeyCollisionTypeEnemy;
	static const std::string MapKeyCollisionTypeEnemyFlying;
	static const std::string MapKeyCollisionTypeForce;
	static const std::string MapKeyCollisionTypeSolidNpc;
	static const std::string MapKeyCollisionTypeSolidNpcFlying;
	static const std::string MapKeyCollisionTypeWater;
	static const std::string MapKeyCollisionTypeLava;

private:
	PlatformerCollisionMapping();
	~PlatformerCollisionMapping();

	void initializeListeners() override;

	static PlatformerCollisionMapping* instance;
};
