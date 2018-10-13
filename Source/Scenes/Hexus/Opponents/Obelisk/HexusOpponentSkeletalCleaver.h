#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentSkeletalCleaver : public HexusOpponentData
{
public:
	static HexusOpponentSkeletalCleaver* getInstance();

private:
	HexusOpponentSkeletalCleaver();
	~HexusOpponentSkeletalCleaver();

	static const std::string StringKeyOpponentName;
	static HexusOpponentSkeletalCleaver* instance;
};
