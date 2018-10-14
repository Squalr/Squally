#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentSkeletalKnight : public HexusOpponentData
{
public:
	static HexusOpponentSkeletalKnight* getInstance();

private:
	HexusOpponentSkeletalKnight();
	~HexusOpponentSkeletalKnight();

	static const std::string OpponentSaveKey;
	static HexusOpponentSkeletalKnight* instance;
};
