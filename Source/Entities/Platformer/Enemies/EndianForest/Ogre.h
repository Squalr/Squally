#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class Ogre : public PlatformerEnemy
{
public:
	static Ogre* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKeyOgre;

private:
	typedef PlatformerEnemy super;
	Ogre(cocos2d::ValueMap& properties);
	~Ogre();
};
