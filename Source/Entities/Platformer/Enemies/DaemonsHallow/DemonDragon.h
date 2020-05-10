#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class DemonDragon : public PlatformerEnemy
{
public:
	static DemonDragon* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	DemonDragon(cocos2d::ValueMap& properties);
	virtual ~DemonDragon();

private:
	typedef PlatformerEnemy super;
};
