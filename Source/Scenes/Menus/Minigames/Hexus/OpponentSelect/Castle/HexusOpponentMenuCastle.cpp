#include "HexusOpponentMenuCastle.h"

HexusOpponentMenuCastle * HexusOpponentMenuCastle::create()
{
	HexusOpponentMenuCastle* instance = new HexusOpponentMenuCastle();

	instance->autorelease();

	return instance;
}

HexusOpponentMenuCastle::HexusOpponentMenuCastle() : HexusOpponentMenuBase(HexusChapterPreviewCastle::stringKeyChapterName)
{
	auto callback = CC_CALLBACK_1(HexusOpponentMenuCastle::onGameEndCallback, this);

	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentAgnes::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentErlic::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentExecutioner::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentGarin::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentJack::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentKingRedsong::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentKingRedsongSlime::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentLeroy::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentMabel::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentMerlin::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentPrincessOpal::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentRaven::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentReaper::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentRogas::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentScarecrow::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentShade::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentThurstan::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentTyracius::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentVampireLord::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentVampiress::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentWraith::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentZombie::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentZombieErlic::getInstance(), callback));

	for (std::vector<HexusOpponentPreview*>::iterator it = this->opponents.begin(); it != this->opponents.end(); ++it)
	{
		this->scrollPane->addChild(*it);
	}
}

HexusOpponentMenuCastle::~HexusOpponentMenuCastle()
{
}
