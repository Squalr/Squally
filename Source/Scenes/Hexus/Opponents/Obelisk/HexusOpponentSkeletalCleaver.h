#pragma once
#include "cocos2d.h"

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentSkeletalCleaver : public HexusOpponentData
{
public:
	static HexusOpponentSkeletalCleaver* getInstance();

private:
	HexusOpponentSkeletalCleaver();
	~HexusOpponentSkeletalCleaver();

	static const std::string OpponentSaveKey;
	static HexusOpponentSkeletalCleaver* instance;
};
