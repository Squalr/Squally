#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class Wraith : public PlatformerEnemy
{
public:
	static Wraith* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Wraith(cocos2d::ValueMap& properties);
	virtual ~Wraith();

private:
	typedef PlatformerEnemy super;
};
