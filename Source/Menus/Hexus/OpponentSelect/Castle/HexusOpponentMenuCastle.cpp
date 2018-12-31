#include "HexusOpponentMenuCastle.h"

#include "Engine/GlobalDirector.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Menus/Hexus/ChapterSelect/Castle/HexusChapterPreviewCastle.h"
#include "Menus/Hexus/OpponentSelect/HexusOpponentPreview.h"
#include "Scenes/Hexus/Opponents/Castle/CastleHexusOpponents.h"

using namespace cocos2d;

HexusOpponentMenuCastle* HexusOpponentMenuCastle::instance = nullptr;

void HexusOpponentMenuCastle::registerGlobalScene()
{
	if (HexusOpponentMenuCastle::instance == nullptr)
	{
		HexusOpponentMenuCastle::instance = new HexusOpponentMenuCastle();

		HexusOpponentMenuCastle::instance->autorelease();
		HexusOpponentMenuCastle::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(HexusOpponentMenuCastle::instance);
}

HexusOpponentMenuCastle::HexusOpponentMenuCastle() : super(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter::Castle, HexusChapterPreviewCastle::SaveKeyChapterName)
{
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentGarin::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentWraith::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentLeroy::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentZombie::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentThurstan::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentExecutioner::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentRogas::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentKingRedsongSlime::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentJack::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentTyracius::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentReaper::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentErlic::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentVampireLord::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentMabel::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentVampiress::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentMerlin::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentZombieErlic::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentPrincessOpal::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentScarecrow::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentRaven::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentShade::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentKingRedsong::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentAgnes::getInstance()));

	for (std::vector<HexusOpponentPreview*>::iterator it = this->opponents.begin(); it != this->opponents.end(); ++it)
	{
		this->scrollPane->addChild(*it);
	}
}

HexusOpponentMenuCastle::~HexusOpponentMenuCastle()
{
}
