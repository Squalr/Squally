#include "HexusOpponentMenuTraining.h"

#include "Engine/GlobalDirector.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Scenes/Hexus/Menus/ChapterSelect/Training/HexusChapterPreviewTraining.h"
#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentPreview.h"
#include "Scenes/Hexus/Opponents/Tutorials/TutorialHexusOpponents.h"

using namespace cocos2d;

HexusOpponentMenuTraining* HexusOpponentMenuTraining::instance = nullptr;

HexusOpponentMenuTraining* HexusOpponentMenuTraining::getInstance()
{
	if (HexusOpponentMenuTraining::instance == nullptr)
	{
		HexusOpponentMenuTraining::instance = new HexusOpponentMenuTraining();

		HexusOpponentMenuTraining::instance->autorelease();
		GlobalDirector::registerGlobalScene(HexusOpponentMenuTraining::instance);
	}

	return HexusOpponentMenuTraining::instance;
}

HexusOpponentMenuTraining::HexusOpponentMenuTraining() : super(HexusChapterPreviewTraining::SaveKeyChapterName)
{
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentTutorialA::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentTutorialB::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentTutorialC::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentTutorialD::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentTutorialE::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentTutorialF::getInstance()));

	this->buildOpponentList();
}

HexusOpponentMenuTraining::~HexusOpponentMenuTraining()
{
}
