#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class SkeletalBaron : public PlatformerEnemy
{
public:
	static SkeletalBaron* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	SkeletalBaron(cocos2d::ValueMap& properties);
	virtual ~SkeletalBaron();

private:
	typedef PlatformerEnemy super;
};
