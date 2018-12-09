#pragma once

#include "Engine/GlobalNode.h"

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

	enum CategoryGroupType
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

private:
	PlatformerCollisionMapping();
	~PlatformerCollisionMapping();

	void initializeListeners() override;

	static PlatformerCollisionMapping* instance;
};
