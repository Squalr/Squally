#include "HexusOpponentMenuForest.h"

#include "Engine/GlobalDirector.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Menus/Hexus/ChapterSelect/Forest/HexusChapterPreviewForest.h"
#include "Menus/Hexus/OpponentSelect/HexusOpponentPreview.h"
#include "Scenes/Hexus/Opponents/Forest/ForestHexusOpponents.h"

using namespace cocos2d;

HexusOpponentMenuForest* HexusOpponentMenuForest::instance = nullptr;

void HexusOpponentMenuForest::registerGlobalScene()
{
	if (HexusOpponentMenuForest::instance == nullptr)
	{
		HexusOpponentMenuForest::instance = new HexusOpponentMenuForest();

		HexusOpponentMenuForest::instance->autorelease();
		HexusOpponentMenuForest::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(HexusOpponentMenuForest::instance);
}

HexusOpponentMenuForest::HexusOpponentMenuForest() : super(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter::Forest, HexusChapterPreviewForest::SaveKeyChapterName)
{
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentLycan::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentThug::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentToben::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentOrcGrunt::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentDudly::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentOrcSwordsman::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCooper::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentOrcWarrior::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentAppolo::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentOrcBomber::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentChiron::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentRobin::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentOgre::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentRupert::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentEnt::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentRusty::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentTroll::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentPrincessMittens::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCyclops::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentPolyphemus::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentKingGrogg::getInstance()));

	for (std::vector<HexusOpponentPreview*>::iterator it = this->opponents.begin(); it != this->opponents.end(); ++it)
	{
		this->scrollPane->addChild(*it);
	}
}

HexusOpponentMenuForest::~HexusOpponentMenuForest()
{
}
