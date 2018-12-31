#include "HexusOpponentMenuJungle.h"

#include "Engine/GlobalDirector.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Menus/Hexus/ChapterSelect/Jungle/HexusChapterPreviewJungle.h"
#include "Menus/Hexus/OpponentSelect/HexusOpponentPreview.h"
#include "Scenes/Hexus/Opponents/Jungle/JungleHexusOpponents.h"

using namespace cocos2d;

HexusOpponentMenuJungle* HexusOpponentMenuJungle::instance = nullptr;

void HexusOpponentMenuJungle::registerGlobalScene()
{
	if (HexusOpponentMenuJungle::instance == nullptr)
	{
		HexusOpponentMenuJungle::instance = new HexusOpponentMenuJungle();

		HexusOpponentMenuJungle::instance->autorelease();
		HexusOpponentMenuJungle::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(HexusOpponentMenuJungle::instance);
}

HexusOpponentMenuJungle::HexusOpponentMenuJungle() : super(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter::Jungle, HexusChapterPreviewJungle::SaveKeyChapterName)
{
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentBlackbeard::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentGoblinWarriorPig::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentBodom::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentGoblinShaman::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentElriel::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentGoblinGruntBoar::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentDrak::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentGorilla::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentGramps::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentReanimatedPig::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentPrincessMatu::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentRaka::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentMinotaur::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentMinos::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentSkeletalPirate::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentHades::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentBarbarian::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentThor::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentViking::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentTikiGolem::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentRhinoman::getInstance()));

	for (std::vector<HexusOpponentPreview*>::iterator it = this->opponents.begin(); it != this->opponents.end(); ++it)
	{
		this->scrollPane->addChild(*it);
	}
}

HexusOpponentMenuJungle::~HexusOpponentMenuJungle()
{
}
