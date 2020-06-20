#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class WaterElemental : public PlatformerEnemy
{
public:
	static WaterElemental* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	WaterElemental(cocos2d::ValueMap& properties);
	virtual ~WaterElemental();

private:
	typedef PlatformerEnemy super;
};
