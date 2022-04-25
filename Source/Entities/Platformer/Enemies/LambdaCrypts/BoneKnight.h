#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class BoneKnight : public PlatformerEnemy
{
public:
	static BoneKnight* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	BoneKnight(cocos2d::ValueMap& properties);
	virtual ~BoneKnight();

private:
	typedef PlatformerEnemy super;
};
