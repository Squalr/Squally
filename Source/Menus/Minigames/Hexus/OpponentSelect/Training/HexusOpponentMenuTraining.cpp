#include "HexusOpponentMenuTraining.h"

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

HexusOpponentMenuTraining::HexusOpponentMenuTraining() : HexusOpponentMenuBase(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter::Training, HexusChapterPreviewTraining::stringKeyChapterName)
{
	auto callback = CC_CALLBACK_1(HexusOpponentMenuTraining::onGameEndCallback, this);

	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentTutorialA::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentTutorialB::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentTutorialC::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentTutorialD::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentTutorialE::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentTutorialF::getInstance(), callback));

	for (std::vector<HexusOpponentPreview*>::iterator it = this->opponents.begin(); it != this->opponents.end(); ++it)
	{
		this->scrollPane->addChild(*it);
	}
}

HexusOpponentMenuTraining::~HexusOpponentMenuTraining()
{
}
