#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentSkeletalPriestess : public HexusOpponentData
{
public:
	static HexusOpponentSkeletalPriestess* getInstance();

private:
	HexusOpponentSkeletalPriestess();
	~HexusOpponentSkeletalPriestess();

	static const std::string OpponentSaveKey;
	static HexusOpponentSkeletalPriestess* instance;
};
