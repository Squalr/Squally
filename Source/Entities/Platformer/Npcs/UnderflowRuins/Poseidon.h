#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Poseidon : public PlatformerFriendly
{
public:
	static Poseidon* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Poseidon(cocos2d::ValueMap& properties);
	virtual ~Poseidon();

private:
	typedef PlatformerFriendly super;
};
