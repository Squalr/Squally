#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class Werewolf : public PlatformerEnemy
{
public:
	static Werewolf* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Werewolf(cocos2d::ValueMap& properties);
	virtual ~Werewolf();

private:
	typedef PlatformerEnemy super;
};
