#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentSkeletalNecromancer : public HexusOpponentData
{
public:
	static HexusOpponentSkeletalNecromancer* getInstance();

private:
	HexusOpponentSkeletalNecromancer();
	~HexusOpponentSkeletalNecromancer();

	static const std::string OpponentSaveKey;
	static HexusOpponentSkeletalNecromancer* instance;
};
