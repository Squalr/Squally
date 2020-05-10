#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class SkeletalWarrior : public PlatformerEnemy
{
public:
	static SkeletalWarrior* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	SkeletalWarrior(cocos2d::ValueMap& properties);
	virtual ~SkeletalWarrior();

private:
	typedef PlatformerEnemy super;
};
