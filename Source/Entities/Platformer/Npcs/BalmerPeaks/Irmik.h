#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Irmik : public PlatformerFriendly
{
public:
	static Irmik* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Irmik(cocos2d::ValueMap& properties);
	virtual ~Irmik();

private:
	typedef PlatformerFriendly super;
};
