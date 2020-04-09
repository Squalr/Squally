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

	static const std::string MapKey;
	
protected:
	Orthrus(cocos2d::ValueMap& properties);
	virtual ~Orthrus();

private:
	typedef PlatformerEnemy super;
};
