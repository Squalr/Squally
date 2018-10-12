#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentDudly : public HexusOpponentData
{
public:
	static HexusOpponentDudly* getInstance();

private:
	HexusOpponentDudly();
	~HexusOpponentDudly();

	static const std::string StringKeyOpponentName;
	static HexusOpponentDudly* instance;
};
