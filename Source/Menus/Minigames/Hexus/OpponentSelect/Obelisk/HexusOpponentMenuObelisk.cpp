#include "HexusOpponentMenuObelisk.h"

HexusOpponentMenuObelisk * HexusOpponentMenuObelisk::create()
{
	HexusOpponentMenuObelisk* instance = new HexusOpponentMenuObelisk();

	instance->autorelease();

	return instance;
}

HexusOpponentMenuObelisk::HexusOpponentMenuObelisk() : HexusOpponentMenuBase(HexusChapterPreviewObelisk::stringKeyChapterName)
{
	auto callback = CC_CALLBACK_1(HexusOpponentMenuObelisk::onGameEndCallback, this);

	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentAmelia::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentVoidDemon::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentGarrick::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentAbomination::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentRoger::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentSkeletalBaron::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentAzmus::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentUndead::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentNecron::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentReanimatedFighter::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentJohann::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentVoidArcher::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentThion::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentSkeletalCleaver::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentUrsula::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentSkeletalKnight::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentViper::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentSkeletalPriestess::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentPrincessNebea::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentGargoyle::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentZana::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentKingZul::getInstance(), callback));

	for (std::vector<HexusOpponentPreview*>::iterator it = this->opponents.begin(); it != this->opponents.end(); ++it)
	{
		this->scrollPane->addChild(*it);
	}
}

HexusOpponentMenuObelisk::~HexusOpponentMenuObelisk()
{
}
