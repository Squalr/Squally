#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


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
