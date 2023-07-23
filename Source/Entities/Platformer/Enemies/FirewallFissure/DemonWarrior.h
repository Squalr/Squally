#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class DemonWarrior : public PlatformerEnemy
{
public:
	static DemonWarrior* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	DemonWarrior(cocos2d::ValueMap& properties);
	virtual ~DemonWarrior();

private:
	typedef PlatformerEnemy super;
};
