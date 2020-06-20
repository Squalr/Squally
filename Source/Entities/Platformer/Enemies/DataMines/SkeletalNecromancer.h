#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class SkeletalNecromancer : public PlatformerEnemy
{
public:
	static SkeletalNecromancer* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	SkeletalNecromancer(cocos2d::ValueMap& properties);
	virtual ~SkeletalNecromancer();

private:
	typedef PlatformerEnemy super;
};
