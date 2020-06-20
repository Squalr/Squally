#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class Warlock : public PlatformerEnemy
{
public:
	static Warlock* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Warlock(cocos2d::ValueMap& properties);
	virtual ~Warlock();

private:
	typedef PlatformerEnemy super;
};
