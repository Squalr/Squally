#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class Troll : public PlatformerEnemy
{
public:
	static Troll* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Troll(cocos2d::ValueMap& properties);
	virtual ~Troll();

private:
	typedef PlatformerEnemy super;
};
