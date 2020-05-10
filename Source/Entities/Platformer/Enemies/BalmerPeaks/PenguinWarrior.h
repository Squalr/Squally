#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class PenguinWarrior : public PlatformerEnemy
{
public:
	static PenguinWarrior* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	PenguinWarrior(cocos2d::ValueMap& properties);
	virtual ~PenguinWarrior();

private:
	typedef PlatformerEnemy super;
};
