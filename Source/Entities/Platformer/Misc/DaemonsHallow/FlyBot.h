////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEntity.h"

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////A////A////A////A////A////A////A////A////A////A/

class Sound;

////B////B////B////B////B////B////B////B////B////B/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

class HexusOpponentData;

class FlyBot : public PlatformerEntity
{
public:
	static FlyBot* deserialize(cocos2d::ValueMap& initProperties);
	
	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/
	
	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyFlyBot;

private:
	typedef PlatformerEntity super;
	FlyBot(cocos2d::ValueMap& initProperties);
	~FlyBot();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
	
	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////X////X////X////X////X////X////X////X////X////X/

	void initializeListeners() override;

	Sound* droidAlarmedSound;
	Sound* droidBrief1Sound;
	Sound* droidBrief2Sound;
	Sound* droidChatterSound;

	static const std::string EventGreetSqually;
	
	////O////O////O////O////O////O////O////O////O////O/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
};
