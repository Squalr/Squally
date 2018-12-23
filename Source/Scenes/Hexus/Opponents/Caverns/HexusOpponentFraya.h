#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentFraya : public HexusOpponentData
{
public:
	static HexusOpponentFraya* getInstance();

private:
	HexusOpponentFraya();
	~HexusOpponentFraya();

	static const std::string OpponentSaveKey;
	static HexusOpponentFraya* instance;
};
