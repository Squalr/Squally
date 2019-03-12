////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "HexusOpponentMenuSeaSharpCaverns.h"

#include "Engine/GlobalDirector.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Entities/Platformer/Npcs/SeaSharpCaverns/Alder.h"
#include "Entities/Platformer/Npcs/SeaSharpCaverns/Brock.h"
#include "Entities/Platformer/Npcs/SeaSharpCaverns/Cypress.h"
#include "Entities/Platformer/Npcs/SeaSharpCaverns/Finch.h"
#include "Entities/Platformer/Npcs/SeaSharpCaverns/Fraya.h"
#include "Entities/Platformer/Npcs/SeaSharpCaverns/Jasper.h"
#include "Entities/Platformer/Npcs/SeaSharpCaverns/Mildred.h"
#include "Entities/Platformer/Npcs/SeaSharpCaverns/Olive.h"
#include "Entities/Platformer/Npcs/SeaSharpCaverns/PrincessDawn.h"
#include "Entities/Platformer/Npcs/SeaSharpCaverns/Raka.h"
#include "Entities/Platformer/Npcs/SeaSharpCaverns/Sarude.h"
#include "Entities/Platformer/Npcs/SeaSharpCaverns/Shen.h"
#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentPreview.h"
#include "Entities/Platformer/Npcs/SeaSharpCaverns/Alder.h"
#include "Entities/Platformer/Npcs/SeaSharpCaverns/Brock.h"
#include "Entities/Platformer/Npcs/SeaSharpCaverns/Cypress.h"
#include "Entities/Platformer/Npcs/SeaSharpCaverns/Finch.h"
#include "Entities/Platformer/Npcs/SeaSharpCaverns/Fraya.h"
#include "Entities/Platformer/Npcs/SeaSharpCaverns/Jasper.h"
#include "Entities/Platformer/Npcs/SeaSharpCaverns/Mildred.h"
#include "Entities/Platformer/Npcs/SeaSharpCaverns/Olive.h"
#include "Entities/Platformer/Npcs/SeaSharpCaverns/PrincessDawn.h"
#include "Entities/Platformer/Npcs/SeaSharpCaverns/Raka.h"
#include "Entities/Platformer/Npcs/SeaSharpCaverns/Sarude.h"
#include "Entities/Platformer/Npcs/SeaSharpCaverns/Shen.h"
#include "Scenes/Hexus/Menus/ChapterSelect/SeaSharpCaverns/HexusChapterPreviewSeaSharpCaverns.h"

using namespace cocos2d;

HexusOpponentMenuSeaSharpCaverns* HexusOpponentMenuSeaSharpCaverns::instance = nullptr;

void HexusOpponentMenuSeaSharpCaverns::registerGlobalScene()
{
	if (HexusOpponentMenuSeaSharpCaverns::instance == nullptr)
	{
		HexusOpponentMenuSeaSharpCaverns::instance = new HexusOpponentMenuSeaSharpCaverns();

		HexusOpponentMenuSeaSharpCaverns::instance->autorelease();
		HexusOpponentMenuSeaSharpCaverns::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(HexusOpponentMenuSeaSharpCaverns::instance);
}

HexusOpponentMenuSeaSharpCaverns::HexusOpponentMenuSeaSharpCaverns() : super(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter::SeaSharpCaverns, HexusChapterPreviewSeaSharpCaverns::SaveKeyChapterName)
{
	this->opponents.push_back(HexusOpponentPreview::create(Alder::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Brock::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Cypress::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Finch::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Fraya::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Jasper::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Mildred::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Olive::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(PrincessDawn::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Raka::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Sarude::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Shen::getHexusOpponentData()));

	for (std::vector<HexusOpponentPreview*>::iterator it = this->opponents.begin(); it != this->opponents.end(); ++it)
	{
		this->scrollPane->addChild(*it);
	}
}

HexusOpponentMenuSeaSharpCaverns::~HexusOpponentMenuSeaSharpCaverns()
{
}
