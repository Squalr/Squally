#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class DemonGhost : public PlatformerEnemy
{
public:
	static DemonGhost* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	DemonGhost(cocos2d::ValueMap& properties);
	virtual ~DemonGhost();

private:
	typedef PlatformerEnemy super;
};
