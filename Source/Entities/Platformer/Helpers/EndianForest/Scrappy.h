#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEntity.h"

class Sound;

class HexusOpponentData;

class Scrappy : public PlatformerEntity
{
public:
	static Scrappy* deserialize(cocos2d::ValueMap& properties);

	float getFloatHeight() override;

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	Sound* droidAlarmedSound;
	Sound* droidBrief1Sound;
	Sound* droidBrief2Sound;
	Sound* droidChatterSound;

	static const std::string MapKeyScrappy;

private:
	typedef PlatformerEntity super;
	Scrappy(cocos2d::ValueMap& properties);
	~Scrappy();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;

	void onEnter() override;
	void initializeListeners() override;
	void runEndOfDemoEvent();
	void runSquallyTrappedEvent();

	static const std::string EventEndOfDemo;
	static const std::string EventSquallyTrapped;
};
