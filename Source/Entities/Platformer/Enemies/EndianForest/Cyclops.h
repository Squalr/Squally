#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class Cyclops : public PlatformerEnemy
{
public:
	static Cyclops* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKeyCyclops;

private:
	typedef PlatformerEnemy super;
	Cyclops(cocos2d::ValueMap& properties);
	~Cyclops();
};
