#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class Centaur : public PlatformerEnemy
{
public:
	static Centaur* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Centaur(cocos2d::ValueMap& properties);
	virtual ~Centaur();

private:
	typedef PlatformerEnemy super;
};
