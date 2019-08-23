#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;
class LocalizedString;

class QueenLiana : public PlatformerFriendly
{
public:
	static QueenLiana* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyQueenLiana;

private:
	typedef PlatformerFriendly super;
	QueenLiana(cocos2d::ValueMap& properties);
	~QueenLiana();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
