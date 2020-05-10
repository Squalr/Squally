#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class Abomination : public PlatformerEnemy
{
public:
	static Abomination* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Abomination(cocos2d::ValueMap& properties);
	virtual ~Abomination();

private:
	typedef PlatformerEnemy super;
};
