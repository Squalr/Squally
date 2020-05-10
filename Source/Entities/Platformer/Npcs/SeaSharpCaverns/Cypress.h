#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Cypress : public PlatformerFriendly
{
public:
	static Cypress* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Cypress(cocos2d::ValueMap& properties);
	virtual ~Cypress();

private:
	typedef PlatformerFriendly super;
};
