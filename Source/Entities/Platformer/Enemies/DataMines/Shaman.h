#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class Shaman : public PlatformerEnemy
{
public:
	static Shaman* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Shaman(cocos2d::ValueMap& properties);
	virtual ~Shaman();

private:
	typedef PlatformerEnemy super;
};
