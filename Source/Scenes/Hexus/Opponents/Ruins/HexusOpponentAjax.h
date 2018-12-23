#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentAjax : public HexusOpponentData
{
public:
	static HexusOpponentAjax* getInstance();

private:
	HexusOpponentAjax();
	~HexusOpponentAjax();

	static const std::string OpponentSaveKey;
	static HexusOpponentAjax* instance;
};
