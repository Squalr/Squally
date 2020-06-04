#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class Rhinoman : public PlatformerEnemy
{
public:
	static Rhinoman* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Rhinoman(cocos2d::ValueMap& properties);
	virtual ~Rhinoman();

private:
	typedef PlatformerEnemy super;
};
