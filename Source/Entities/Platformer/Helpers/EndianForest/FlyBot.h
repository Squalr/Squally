#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEntity.h"

class Sound;

class HexusOpponentData;

class FlyBot : public PlatformerEntity
{
public:
	static FlyBot* deserialize(cocos2d::ValueMap& properties);

	float getFloatHeight() override;

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	Sound* droidAlarmedSound;
	Sound* droidBrief1Sound;
	Sound* droidBrief2Sound;
	Sound* droidChatterSound;

	static const std::string MapKeyFlyBot;

private:
	typedef PlatformerEntity super;
	FlyBot(cocos2d::ValueMap& properties);
	~FlyBot();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;

	void onEnter() override;
	void initializeListeners() override;
	void runEndOfDemoEvent();
	void runSquallyTrappedEvent();

	static const std::string EventEndOfDemo;
	static const std::string EventSquallyTrapped;
};
