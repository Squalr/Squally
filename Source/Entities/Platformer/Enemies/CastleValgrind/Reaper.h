#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class Reaper : public PlatformerEnemy
{
public:
	static Reaper* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Reaper(cocos2d::ValueMap& properties);
	virtual ~Reaper();

private:
	typedef PlatformerEnemy super;
};
