#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class Undead : public PlatformerEnemy
{
public:
	static Undead* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Undead(cocos2d::ValueMap& properties);
	virtual ~Undead();

private:
	typedef PlatformerEnemy super;
};
