#include "HexusOpponentMenuObelisk.h"

#include "Engine/GlobalDirector.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Menus/Hexus/ChapterSelect/Obelisk/HexusChapterPreviewObelisk.h"
#include "Menus/Hexus/OpponentSelect/HexusOpponentPreview.h"
#include "Scenes/Hexus/Opponents/Obelisk/ObeliskHexusOpponents.h"

using namespace cocos2d;

HexusOpponentMenuObelisk* HexusOpponentMenuObelisk::instance = nullptr;

void HexusOpponentMenuObelisk::registerGlobalScene()
{
	if (HexusOpponentMenuObelisk::instance == nullptr)
	{
		HexusOpponentMenuObelisk::instance = new HexusOpponentMenuObelisk();

		HexusOpponentMenuObelisk::instance->autorelease();
		HexusOpponentMenuObelisk::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(HexusOpponentMenuObelisk::instance);
}

HexusOpponentMenuObelisk::HexusOpponentMenuObelisk() : HexusOpponentMenuBase(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter::Void, HexusChapterPreviewObelisk::SaveKeyChapterName)
{
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentAmelia::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentVoidDemon::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentGarrick::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentAbomination::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentRoger::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentSkeletalBaron::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentAzmus::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentUndead::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentNecron::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentReanimatedFighter::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentJohann::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentVoidArcher::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentThion::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentSkeletalCleaver::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentUrsula::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentSkeletalKnight::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentViper::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentSkeletalPriestess::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentPrincessNebea::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentGargoyle::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentZana::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentKingZul::getInstance()));

	for (std::vector<HexusOpponentPreview*>::iterator it = this->opponents.begin(); it != this->opponents.end(); ++it)
	{
		this->scrollPane->addChild(*it);
	}
}

HexusOpponentMenuObelisk::~HexusOpponentMenuObelisk()
{
}
