#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;
class LocalizedString;

class Horse : public PlatformerFriendly
{
public:
	static Horse* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Horse(cocos2d::ValueMap& properties);
	virtual ~Horse();

private:
	typedef PlatformerFriendly super;
};
