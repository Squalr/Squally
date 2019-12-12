#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class KingGrogg : public PlatformerEnemy
{
public:
	static KingGrogg* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKeyKingGrogg;

private:
	typedef PlatformerEnemy super;
	KingGrogg(cocos2d::ValueMap& properties);
	~KingGrogg();
};
