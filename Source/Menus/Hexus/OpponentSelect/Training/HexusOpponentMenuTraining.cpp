#include "HexusOpponentMenuTraining.h"

#include "Engine/GlobalDirector.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Menus/Hexus/ChapterSelect/Training/HexusChapterPreviewTraining.h"
#include "Menus/Hexus/OpponentSelect/HexusOpponentPreview.h"
#include "Scenes/Hexus/Opponents/Tutorials/TutorialHexusOpponents.h"

using namespace cocos2d;

HexusOpponentMenuTraining* HexusOpponentMenuTraining::instance = nullptr;

void HexusOpponentMenuTraining::registerGlobalScene()
{
	if (HexusOpponentMenuTraining::instance == nullptr)
	{
		HexusOpponentMenuTraining::instance = new HexusOpponentMenuTraining();

		HexusOpponentMenuTraining::instance->autorelease();
		HexusOpponentMenuTraining::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(HexusOpponentMenuTraining::instance);
}

HexusOpponentMenuTraining::HexusOpponentMenuTraining() : HexusOpponentMenuBase(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter::Training, HexusChapterPreviewTraining::SaveKeyChapterName)
{
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentTutorialA::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentTutorialB::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentTutorialC::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentTutorialD::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentTutorialE::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentTutorialF::getInstance()));

	for (std::vector<HexusOpponentPreview*>::iterator it = this->opponents.begin(); it != this->opponents.end(); ++it)
	{
		this->scrollPane->addChild(*it);
	}
}

HexusOpponentMenuTraining::~HexusOpponentMenuTraining()
{
}
