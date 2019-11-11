#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;
class LocalizedString;
class SmartAnimationSequenceNode;
class WorldSound;

class Scrappy : public PlatformerFriendly
{
public:
	static Scrappy* deserialize(cocos2d::ValueMap& properties);

	float getFloatHeight() override;

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;
	static HexusOpponentData* getHexusOpponentData();

	WorldSound* droidAlarmedSound;
	WorldSound* droidBrief1Sound;
	WorldSound* droidBrief2Sound;
	WorldSound* droidChatterSound;

	static const std::string MapKeyScrappy;

private:
	typedef PlatformerFriendly super;
	Scrappy(cocos2d::ValueMap& properties);
	~Scrappy();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	SmartAnimationSequenceNode* fireAnimation;
};
