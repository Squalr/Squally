#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Zelina : public PlatformerFriendly
{
public:
	static Zelina* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Zelina(cocos2d::ValueMap& properties);
	virtual ~Zelina();

private:
	typedef PlatformerFriendly super;
};
