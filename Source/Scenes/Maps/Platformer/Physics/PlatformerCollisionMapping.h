#pragma once

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

	void onMapRequest(cocos2d::EventCustom* eventCustom);

	static const std::string KeyCollisionTypeSolid;
	static const std::string KeyCollisionTypePassThrough;
	static const std::string KeyCollisionTypePlayer;
	static const std::string KeyCollisionTypeNpc;
	static const std::string KeyCollisionTypeEnemy;
	static const std::string KeyCollisionTypeEnemyFlying;
	static const std::string KeyCollisionTypeForce;
	static const std::string KeyCollisionTypeSolidNpc;
	static const std::string KeyCollisionTypeSolidNpcFlying;
	static const std::string KeyCollisionTypeWater;
	static const std::string KeyCollisionTypeLava;

private:
	PlatformerCollisionMapping();
	~PlatformerCollisionMapping();

	void initializeListeners() override;

	static PlatformerCollisionMapping* instance;
};
