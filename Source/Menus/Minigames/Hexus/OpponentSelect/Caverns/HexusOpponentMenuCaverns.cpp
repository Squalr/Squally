#include "HexusOpponentMenuCaverns.h"

HexusOpponentMenuCaverns* HexusOpponentMenuCaverns::instance = nullptr;

void HexusOpponentMenuCaverns::registerGlobalScene()
{
	if (HexusOpponentMenuCaverns::instance == nullptr)
	{
		HexusOpponentMenuCaverns::instance = new HexusOpponentMenuCaverns();

		HexusOpponentMenuCaverns::instance->autorelease();
		HexusOpponentMenuCaverns::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(HexusOpponentMenuCaverns::instance);
}

HexusOpponentMenuCaverns::HexusOpponentMenuCaverns() : HexusOpponentMenuBase(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter::Caverns, HexusChapterPreviewCaverns::stringKeyChapterName)
{
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentBrock::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentShaman::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCypress::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentForestGolem::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentFinch::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentEarthGolem::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentAlder::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentEarthElemental::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentFraya::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentSkeletalArcher::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentOlive::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentSkeletalWarrior::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentJasper::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentSkeletalNecromancer::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentMildred::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentGenie::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentPrincessDawn::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentShen::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentLightningGolem::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentSarude::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentKrampus::getInstance()));

	for (std::vector<HexusOpponentPreview*>::iterator it = this->opponents.begin(); it != this->opponents.end(); ++it)
	{
		this->scrollPane->addChild(*it);
	}
}

HexusOpponentMenuCaverns::~HexusOpponentMenuCaverns()
{
}
