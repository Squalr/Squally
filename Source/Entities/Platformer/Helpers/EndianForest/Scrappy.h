#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;
class LocalizedString;
class SmartAnimationSequenceNode;
class Sound;

class Scrappy : public PlatformerFriendly
{
public:
	static Scrappy* deserialize(cocos2d::ValueMap& properties);

	float getFloatHeight() override;

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;
	static HexusOpponentData* getHexusOpponentData();

	Sound* droidAlarmedSound;
	Sound* droidBrief1Sound;
	Sound* droidBrief2Sound;
	Sound* droidChatterSound;

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
	void runEndOfDemoEvent();

	SmartAnimationSequenceNode* fireAnimation;

	static const std::string EventEndOfDemo;
};
