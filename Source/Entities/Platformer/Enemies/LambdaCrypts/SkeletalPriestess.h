#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class SkeletalPriestess : public PlatformerEnemy
{
public:
	static SkeletalPriestess* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	SkeletalPriestess(cocos2d::ValueMap& properties);
	virtual ~SkeletalPriestess();

private:
	typedef PlatformerEnemy super;
};
