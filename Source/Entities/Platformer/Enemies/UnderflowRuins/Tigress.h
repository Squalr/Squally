#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class Tigress : public PlatformerEnemy
{
public:
	static Tigress* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Tigress(cocos2d::ValueMap& properties);
	virtual ~Tigress();

private:
	typedef PlatformerEnemy super;
};
