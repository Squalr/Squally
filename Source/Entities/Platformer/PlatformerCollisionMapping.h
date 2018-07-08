#pragma once
#include "cocos2d.h"

#include "Engine/Events/DeserializationEvents.h"
#include "Engine/GlobalDirector.h"
#include "Engine/GlobalNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Resources.h"

using namespace cocos2d;

class PlatformerCollisionMapping : public GlobalNode
{
public:
	static void registerGlobalNode();

	void onMapRequest(EventCustom* eventCustom);

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

	const enum CategoryGroupType
	{
		G_None = 0,
		G_Solid = 1 << 1,
		G_PassThrough = 1 << 2,
		G_Player = 1 << 3,
		G_Npc = 1 << 4,
		G_Enemy = 1 << 5,
		G_EnemyFlying = 1 << 6,
		G_Force = 1 << 7,
		G_SolidNpc = 1 << 8,
		G_SolidFlyingNpc = 1 << 9,
		G_Water = 1 << 10,
		G_Lava = 1 << 11,
	};

	void initializeEventListeners() override;

	static PlatformerCollisionMapping* instance;
};
