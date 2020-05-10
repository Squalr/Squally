#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class AnubisPup : public PlatformerEnemy
{
public:
	static AnubisPup* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	AnubisPup(cocos2d::ValueMap& properties);
	virtual ~AnubisPup();

private:
	typedef PlatformerEnemy super;
};
