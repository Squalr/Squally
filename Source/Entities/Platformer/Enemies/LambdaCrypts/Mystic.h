#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class Mystic : public PlatformerEnemy
{
public:
	static Mystic* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Mystic(cocos2d::ValueMap& properties);
	virtual ~Mystic();

private:
	typedef PlatformerEnemy super;
};
