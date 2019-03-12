////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "HexusOpponentMenuUnderflowRuins.h"

#include "Engine/GlobalDirector.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Scenes/Hexus/Menus/ChapterSelect/Castle/HexusChapterPreviewCastle.h"
#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentPreview.h"
#include "Scenes/Hexus/Opponents/Castle/CastleHexusOpponents.h"

#include "Entities/Platformer/Enemies/UnderflowRuins/AnubisPup.h"
#include "Entities/Platformer/Enemies/UnderflowRuins/AnubisWarrior.h"
#include "Entities/Platformer/Enemies/UnderflowRuins/LionMan.h"
#include "Entities/Platformer/Enemies/UnderflowRuins/Lioness.h"
#include "Entities/Platformer/Enemies/UnderflowRuins/Medusa.h"
#include "Entities/Platformer/Enemies/UnderflowRuins/Mermaid.h"
#include "Entities/Platformer/Enemies/UnderflowRuins/Minotaur.h"
#include "Entities/Platformer/Enemies/UnderflowRuins/MummyPriest.h"
#include "Entities/Platformer/Enemies/UnderflowRuins/MummyWarrior.h"
#include "Entities/Platformer/Enemies/UnderflowRuins/Osiris.h"
#include "Entities/Platformer/Enemies/UnderflowRuins/TigerMan.h"
#include "Entities/Platformer/Enemies/UnderflowRuins/Tigress.h"
#include "Entities/Platformer/Helpers/UnderflowRuins/Mummy.h"
#include "Entities/Platformer/Npcs/UnderflowRuins/Ajax.h"
#include "Entities/Platformer/Npcs/UnderflowRuins/Aphrodite.h"
#include "Entities/Platformer/Npcs/UnderflowRuins/Ares.h"
#include "Entities/Platformer/Npcs/UnderflowRuins/Athena.h"
#include "Entities/Platformer/Npcs/UnderflowRuins/Cleopatra.h"
#include "Entities/Platformer/Npcs/UnderflowRuins/Geryon.h"
#include "Entities/Platformer/Npcs/UnderflowRuins/Griffin.h"
#include "Entities/Platformer/Npcs/UnderflowRuins/Hades.h"
#include "Entities/Platformer/Npcs/UnderflowRuins/Hera.h"
#include "Entities/Platformer/Npcs/UnderflowRuins/Horus.h"
#include "Entities/Platformer/Npcs/UnderflowRuins/Poseidon.h"
#include "Entities/Platformer/Npcs/UnderflowRuins/Zeus.h"


using namespace cocos2d;

HexusOpponentMenuUnderflowRuins* HexusOpponentMenuUnderflowRuins::instance = nullptr;

void HexusOpponentMenuUnderflowRuins::registerGlobalScene()
{
	if (HexusOpponentMenuUnderflowRuins::instance == nullptr)
	{
		HexusOpponentMenuUnderflowRuins::instance = new HexusOpponentMenuUnderflowRuins();

		HexusOpponentMenuUnderflowRuins::instance->autorelease();
		HexusOpponentMenuUnderflowRuins::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(HexusOpponentMenuUnderflowRuins::instance);
}

HexusOpponentMenuUnderflowRuins::HexusOpponentMenuUnderflowRuins() : super(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter::Castle, HexusChapterPreviewCastle::SaveKeyChapterName)
{
	this->opponents.push_back(HexusOpponentPreview::create(AnubisPup::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(AnubisWarrior::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(LionMan::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Lioness::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Medusa::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Mermaid::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Minotaur::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(MummyPriest::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(MummyWarrior::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Osiris::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(TigerMan::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Tigress::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Mummy::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Ajax::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Aphrodite::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Ares::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Athena::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Cleopatra::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Geryon::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Griffin::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Hades::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Hera::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Horus::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Poseidon::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Zeus::getHexusOpponentData()));


	for (std::vector<HexusOpponentPreview*>::iterator it = this->opponents.begin(); it != this->opponents.end(); ++it)
	{
		this->scrollPane->addChild(*it);
	}
}

HexusOpponentMenuUnderflowRuins::~HexusOpponentMenuUnderflowRuins()
{
}
