#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentSkeletalNecromancer : public HexusOpponentData
{
public:
	static HexusOpponentSkeletalNecromancer* getInstance();

private:
	HexusOpponentSkeletalNecromancer();
	~HexusOpponentSkeletalNecromancer();

	static const std::string StringKeyOpponentName;
	static HexusOpponentSkeletalNecromancer* instance;
};
