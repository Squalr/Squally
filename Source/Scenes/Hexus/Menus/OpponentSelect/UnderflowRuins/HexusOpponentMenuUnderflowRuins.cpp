////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "HexusOpponentMenuUnderflowRuins.h"

#include "Engine/GlobalDirector.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Entities/Platformer/Npcs/UnderflowRuins/Ajax.h"
#include "Entities/Platformer/Npcs/UnderflowRuins/Angel.h"
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
#include "Entities/Platformer/Npcs/UnderflowRuins/Thor.h"
#include "Entities/Platformer/Npcs/UnderflowRuins/Zeus.h"
#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentPreview.h"
#include "Scenes/Hexus/Menus/ChapterSelect/UnderflowRuins/HexusChapterPreviewUnderflowRuins.h"

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

HexusOpponentMenuUnderflowRuins::HexusOpponentMenuUnderflowRuins() : super(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter::UnderflowRuins, HexusChapterPreviewUnderflowRuins::SaveKeyChapterName)
{
	this->opponents.push_back(HexusOpponentPreview::create(Ajax::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Angel::getHexusOpponentData()));
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
	this->opponents.push_back(HexusOpponentPreview::create(Thor::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Zeus::getHexusOpponentData()));

	this->buildOpponentList();
}

HexusOpponentMenuUnderflowRuins::~HexusOpponentMenuUnderflowRuins()
{
}
