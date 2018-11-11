#include "HexusOpponentMenuTraining.h"

HexusOpponentMenuTraining * HexusOpponentMenuTraining::create()
{
	HexusOpponentMenuTraining* instance = new HexusOpponentMenuTraining();

	instance->autorelease();

	return instance;
}

HexusOpponentMenuTraining::HexusOpponentMenuTraining() : HexusOpponentMenuBase(HexusChapterPreviewTraining::stringKeyChapterName)
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
