#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Chiron : public PlatformerFriendly
{
public:
	static Chiron* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Chiron(cocos2d::ValueMap& properties);
	virtual ~Chiron();

private:
	typedef PlatformerFriendly super;
};
