#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class ZombieElric : public PlatformerEnemy
{
public:
	static ZombieElric* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	ZombieElric(cocos2d::ValueMap& properties);
	virtual ~ZombieElric();

private:
	typedef PlatformerEnemy super;
};
