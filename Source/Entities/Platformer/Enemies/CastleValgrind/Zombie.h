#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class Zombie : public PlatformerEnemy
{
public:
	static Zombie* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Zombie(cocos2d::ValueMap& properties);
	virtual ~Zombie();

private:
	typedef PlatformerEnemy super;
};
