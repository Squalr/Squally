#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Viper : public PlatformerFriendly
{
public:
	static Viper* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Viper(cocos2d::ValueMap& properties);
	virtual ~Viper();

private:
	typedef PlatformerFriendly super;
};
