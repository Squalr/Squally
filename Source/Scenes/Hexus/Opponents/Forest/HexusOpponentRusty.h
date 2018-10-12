#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentForestHighwayman : public HexusOpponentData
{
public:
	static HexusOpponentForestHighwayman* getInstance();

private:
	HexusOpponentForestHighwayman();
	~HexusOpponentForestHighwayman();

	static const std::string StringKeyOpponentName;
	static HexusOpponentForestHighwayman* instance;
};
