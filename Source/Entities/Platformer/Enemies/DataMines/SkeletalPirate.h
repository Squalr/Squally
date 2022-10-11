#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class SkeletalPirate : public PlatformerEnemy
{
public:
	static SkeletalPirate* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	SkeletalPirate(cocos2d::ValueMap& properties);
	virtual ~SkeletalPirate();

private:
	typedef PlatformerEnemy super;
};
