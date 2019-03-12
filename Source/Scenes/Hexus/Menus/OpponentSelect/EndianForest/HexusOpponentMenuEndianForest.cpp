////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "HexusOpponentMenuEndianForest.h"

#include "Engine/GlobalDirector.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Entities/Platformer/Npcs/EndianForest/Toben.h"
#include "Entities/Platformer/Npcs/EndianForest/Rusty.h"
#include "Entities/Platformer/Npcs/EndianForest/Robin.h"
#include "Entities/Platformer/Npcs/EndianForest/PrincessMatu.h"
#include "Entities/Platformer/Npcs/EndianForest/Polyphemus.h"
#include "Entities/Platformer/Npcs/EndianForest/Minos.h"
#include "Entities/Platformer/Npcs/EndianForest/Lycan.h"
#include "Entities/Platformer/Npcs/EndianForest/Gramps.h"
#include "Entities/Platformer/Npcs/EndianForest/Dudly.h"
#include "Entities/Platformer/Npcs/EndianForest/Cooper.h"
#include "Entities/Platformer/Npcs/EndianForest/Appolo.h"
#include "Entities/Platformer/Npcs/EndianForest/Rupert.h"
#include "Entities/Platformer/Npcs/EndianForest/Chiron.h"
#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentPreview.h"
#include "Entities/Platformer/Npcs/EndianForest/Toben.h"
#include "Entities/Platformer/Npcs/EndianForest/Rusty.h"
#include "Entities/Platformer/Npcs/EndianForest/Robin.h"
#include "Entities/Platformer/Npcs/EndianForest/PrincessMatu.h"
#include "Entities/Platformer/Npcs/EndianForest/Polyphemus.h"
#include "Entities/Platformer/Npcs/EndianForest/Minos.h"
#include "Entities/Platformer/Npcs/EndianForest/Lycan.h"
#include "Entities/Platformer/Npcs/EndianForest/Gramps.h"
#include "Entities/Platformer/Npcs/EndianForest/Dudly.h"
#include "Entities/Platformer/Npcs/EndianForest/Cooper.h"
#include "Entities/Platformer/Npcs/EndianForest/Appolo.h"
#include "Entities/Platformer/Npcs/EndianForest/Rupert.h"
#include "Entities/Platformer/Npcs/EndianForest/Chiron.h"
#include "Scenes/Hexus/Menus/ChapterSelect/EndianForest/HexusChapterPreviewEndianForest.h"

using namespace cocos2d;

HexusOpponentMenuEndianForest* HexusOpponentMenuEndianForest::instance = nullptr;

void HexusOpponentMenuEndianForest::registerGlobalScene()
{
	if (HexusOpponentMenuEndianForest::instance == nullptr)
	{
		HexusOpponentMenuEndianForest::instance = new HexusOpponentMenuEndianForest();

		HexusOpponentMenuEndianForest::instance->autorelease();
		HexusOpponentMenuEndianForest::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(HexusOpponentMenuEndianForest::instance);
}

HexusOpponentMenuEndianForest::HexusOpponentMenuEndianForest() : super(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter::EndianForest, HexusChapterPreviewEndianForest::SaveKeyChapterName)
{
	this->opponents.push_back(HexusOpponentPreview::create(Toben::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Rusty::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Robin::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(PrincessMatu::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Polyphemus::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Minos::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Lycan::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Gramps::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Dudly::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Cooper::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Appolo::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Rupert::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Chiron::getHexusOpponentData()));

	for (std::vector<HexusOpponentPreview*>::iterator it = this->opponents.begin(); it != this->opponents.end(); ++it)
	{
		this->scrollPane->addChild(*it);
	}
}

HexusOpponentMenuEndianForest::~HexusOpponentMenuEndianForest()
{
}
