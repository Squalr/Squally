#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class Gorilla : public PlatformerEnemy
{
public:
	static Gorilla* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Gorilla(cocos2d::ValueMap& properties);
	virtual ~Gorilla();

private:
	typedef PlatformerEnemy super;
};
