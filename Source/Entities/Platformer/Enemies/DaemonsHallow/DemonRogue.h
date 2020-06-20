#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class DemonRogue : public PlatformerEnemy
{
public:
	static DemonRogue* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	DemonRogue(cocos2d::ValueMap& properties);
	virtual ~DemonRogue();

private:
	typedef PlatformerEnemy super;
};
