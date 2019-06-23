////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEntity.h"

class Sound;

class HexusOpponentData;

class FlyBot : public PlatformerEntity
{
public:
	static FlyBot* deserialize(cocos2d::ValueMap& initProperties);

	float getFloatHeight() override;

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyFlyBot;

private:
	typedef PlatformerEntity super;
	FlyBot(cocos2d::ValueMap& initProperties);
	~FlyBot();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;

	void onEnter() override;
	void initializeListeners() override;
	void runEndOfDemoEvent();
	void runGreetEvent();
	void runHelpHealEvent();
	void runTeachHackerModeEvent();
	void runSpotOgreEvent();
	void runRestorePotionTutorial();
	void runSquallyTrappedEvent();

	bool hasRunTutorialEvent;
	Sound* droidAlarmedSound;
	Sound* droidBrief1Sound;
	Sound* droidBrief2Sound;
	Sound* droidChatterSound;

	static const std::string EventEndOfDemo;
	static const std::string EventGreetSqually;
	static const std::string EventHelpSquallyHeal;
	static const std::string EventTeachHackerMode;
	static const std::string EventSpotOgre;
	static const std::string EventSquallyTrapped;
};
