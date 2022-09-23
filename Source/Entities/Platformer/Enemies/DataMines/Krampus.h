#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class Krampus : public PlatformerEnemy
{
public:
	static Krampus* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Krampus(cocos2d::ValueMap& properties);
	virtual ~Krampus();

private:
	typedef PlatformerEnemy super;
};
