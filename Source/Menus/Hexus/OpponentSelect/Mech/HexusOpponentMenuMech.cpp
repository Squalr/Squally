#include "HexusOpponentMenuMech.h"

#include "Engine/GlobalDirector.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Menus/Hexus/ChapterSelect/Mech/HexusChapterPreviewMech.h"
#include "Menus/Hexus/OpponentSelect/HexusOpponentPreview.h"
#include "Scenes/Hexus/Opponents/Mech/MechHexusOpponents.h"

using namespace cocos2d;

HexusOpponentMenuMech* HexusOpponentMenuMech::instance = nullptr;

void HexusOpponentMenuMech::registerGlobalScene()
{
	if (HexusOpponentMenuMech::instance == nullptr)
	{
		HexusOpponentMenuMech::instance = new HexusOpponentMenuMech();

		HexusOpponentMenuMech::instance->autorelease();
		HexusOpponentMenuMech::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(HexusOpponentMenuMech::instance);
}

HexusOpponentMenuMech::HexusOpponentMenuMech() : HexusOpponentMenuBase(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter::Mech, HexusChapterPreviewMech::SaveKeyChapterName)
{
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentMara::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentPiper::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentMarcel::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentIllia::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentLeon::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentYsara::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentAtreus::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentExterminator::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentRadon::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentRoboGolem::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentXenon::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentQueenElise::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentEvilEye::getInstance()));

	for (std::vector<HexusOpponentPreview*>::iterator it = this->opponents.begin(); it != this->opponents.end(); ++it)
	{
		this->scrollPane->addChild(*it);
	}
}

HexusOpponentMenuMech::~HexusOpponentMenuMech()
{
}
