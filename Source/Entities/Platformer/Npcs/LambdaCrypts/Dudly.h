#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Dudly : public PlatformerFriendly
{
public:
	static Dudly* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Dudly(cocos2d::ValueMap& properties);
	virtual ~Dudly();

private:
	typedef PlatformerFriendly super;
};
