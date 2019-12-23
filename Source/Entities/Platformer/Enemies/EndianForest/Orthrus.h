#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class Orthrus : public PlatformerEnemy
{
public:
	static Orthrus* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKeyOrthrus;

private:
	typedef PlatformerEnemy super;
	Orthrus(cocos2d::ValueMap& properties);
	~Orthrus();
};
