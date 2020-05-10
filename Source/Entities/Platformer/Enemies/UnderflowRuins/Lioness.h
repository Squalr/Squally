#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class Lioness : public PlatformerEnemy
{
public:
	static Lioness* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Lioness(cocos2d::ValueMap& properties);
	virtual ~Lioness();

private:
	typedef PlatformerEnemy super;
};
