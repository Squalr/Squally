#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class Scarecrow : public PlatformerEnemy
{
public:
	static Scarecrow* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Scarecrow(cocos2d::ValueMap& properties);
	virtual ~Scarecrow();

private:
	typedef PlatformerEnemy super;
};
