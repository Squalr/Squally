#pragma once
#include "cocos2d.h"

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentSkeletalBaron : public HexusOpponentData
{
public:
	static HexusOpponentSkeletalBaron* getInstance();

private:
	HexusOpponentSkeletalBaron();
	~HexusOpponentSkeletalBaron();

	static const std::string OpponentSaveKey;
	static HexusOpponentSkeletalBaron* instance;
};
