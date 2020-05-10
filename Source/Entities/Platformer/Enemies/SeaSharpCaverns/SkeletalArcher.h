#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class SkeletalArcher : public PlatformerEnemy
{
public:
	static SkeletalArcher* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	SkeletalArcher(cocos2d::ValueMap& properties);
	virtual ~SkeletalArcher();

private:
	typedef PlatformerEnemy super;
};
