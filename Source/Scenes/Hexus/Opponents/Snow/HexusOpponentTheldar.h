#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentTheldar : public HexusOpponentData
{
public:
	static HexusOpponentTheldar* getInstance();

private:
	HexusOpponentTheldar();
	~HexusOpponentTheldar();

	static const std::string OpponentSaveKey;
	static HexusOpponentTheldar* instance;
};
