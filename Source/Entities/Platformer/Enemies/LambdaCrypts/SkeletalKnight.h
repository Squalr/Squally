#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class SkeletalKnight : public PlatformerEnemy
{
public:
	static SkeletalKnight* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	SkeletalKnight(cocos2d::ValueMap& properties);
	virtual ~SkeletalKnight();

private:
	typedef PlatformerEnemy super;
};
