#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class Shade : public PlatformerEnemy
{
public:
	static Shade* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Shade(cocos2d::ValueMap& properties);
	virtual ~Shade();

private:
	typedef PlatformerEnemy super;
};
