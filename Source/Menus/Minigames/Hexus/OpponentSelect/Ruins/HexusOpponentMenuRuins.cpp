#include "HexusOpponentMenuRuins.h"

HexusOpponentMenuRuins* HexusOpponentMenuRuins::instance = nullptr;

void HexusOpponentMenuRuins::registerGlobalScene()
{
	if (HexusOpponentMenuRuins::instance == nullptr)
	{
		HexusOpponentMenuRuins::instance = new HexusOpponentMenuRuins();

		HexusOpponentMenuRuins::instance->autorelease();
		HexusOpponentMenuRuins::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(HexusOpponentMenuRuins::instance);
}

HexusOpponentMenuRuins::HexusOpponentMenuRuins() : HexusOpponentMenuBase(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter::Ruins, HexusChapterPreviewRuins::stringKeyChapterName)
{
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentHorus::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentAnubisPup::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentAphrodite::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentLioness::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentAres::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentLionMan::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentAthena::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentTigress::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentHera::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentTigerMan::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentGeryon::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentMummyPriest::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentAjax::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentMummyWarrior::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentGriffin::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentMermaid::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentZeus::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentMedusa::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentPoseidon::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentAnubisWarrior::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCleopatra::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentOsiris::getInstance()));

	for (std::vector<HexusOpponentPreview*>::iterator it = this->opponents.begin(); it != this->opponents.end(); ++it)
	{
		this->scrollPane->addChild(*it);
	}
}

HexusOpponentMenuRuins::~HexusOpponentMenuRuins()
{
}
