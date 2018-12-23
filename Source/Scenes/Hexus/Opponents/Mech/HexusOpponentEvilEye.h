#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentEvilEye : public HexusOpponentData
{
public:
	static HexusOpponentEvilEye* getInstance();

private:
	HexusOpponentEvilEye();
	~HexusOpponentEvilEye();

	static const std::string OpponentSaveKey;
	static HexusOpponentEvilEye* instance;
};
