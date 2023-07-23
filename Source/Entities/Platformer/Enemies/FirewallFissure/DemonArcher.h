#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class DemonArcher : public PlatformerEnemy
{
public:
	static DemonArcher* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	DemonArcher(cocos2d::ValueMap& properties);
	virtual ~DemonArcher();

private:
	typedef PlatformerEnemy super;
};
