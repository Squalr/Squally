#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class Gargoyle : public PlatformerEnemy
{
public:
	static Gargoyle* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Gargoyle(cocos2d::ValueMap& properties);
	virtual ~Gargoyle();

private:
	typedef PlatformerEnemy super;
};
