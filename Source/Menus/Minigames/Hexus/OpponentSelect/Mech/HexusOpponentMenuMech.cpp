#include "HexusOpponentMenuMech.h"

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

HexusOpponentMenuMech::HexusOpponentMenuMech() : HexusOpponentMenuBase(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter::Mech, HexusChapterPreviewMech::stringKeyChapterName)
{
	auto callback = CC_CALLBACK_1(HexusOpponentMenuMech::onGameEndCallback, this);

	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentMara::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentPiper::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentMarcel::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentIllia::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentLeon::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentYsara::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentAtreus::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentExterminator::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentRadon::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentRoboGolem::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentXenon::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentQueenElise::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentEvilEye::getInstance(), callback));

	for (std::vector<HexusOpponentPreview*>::iterator it = this->opponents.begin(); it != this->opponents.end(); ++it)
	{
		this->scrollPane->addChild(*it);
	}
}

HexusOpponentMenuMech::~HexusOpponentMenuMech()
{
}
