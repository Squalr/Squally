#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources.h"

using namespace cocos2d;

class CastleGuard : public NpcBase
{
public:
	static CastleGuard * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyCastleGuard;

private:
	CastleGuard(ValueMap* initProperties);
	~CastleGuard();
};
