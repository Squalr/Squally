#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class Barbarian : public PlatformerEnemy
{
public:
	static Barbarian* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Barbarian(cocos2d::ValueMap& properties);
	virtual ~Barbarian();

private:
	typedef PlatformerEnemy super;
};
