#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentTinsel : public HexusOpponentData
{
public:
	static HexusOpponentTinsel* getInstance();

private:
	HexusOpponentTinsel();
	~HexusOpponentTinsel();

	static const std::string OpponentSaveKey;
	static HexusOpponentTinsel* instance;
};
