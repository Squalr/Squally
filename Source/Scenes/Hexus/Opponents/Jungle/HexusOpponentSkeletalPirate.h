#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentSkeletalPirate : public HexusOpponentData
{
public:
	static HexusOpponentSkeletalPirate* getInstance();

private:
	HexusOpponentSkeletalPirate();
	~HexusOpponentSkeletalPirate();

	static const std::string StringKeyOpponentName;
	static HexusOpponentSkeletalPirate* instance;
};
