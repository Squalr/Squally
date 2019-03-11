////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "HexusOpponentMenuEndianForest.h"

#include "Engine/GlobalDirector.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Scenes/Hexus/Menus/ChapterSelect/Castle/HexusChapterPreviewCastle.h"
#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentPreview.h"
#include "Scenes/Hexus/Opponents/Castle/CastleHexusOpponents.h"

////X////X////X////X////X////X////X////X////X////X/

#include "Entities/Platformer/Enemies/EndianForest/Centaur.h"
#include "Entities/Platformer/Enemies/EndianForest/Cyclops.h"
#include "Entities/Platformer/Enemies/EndianForest/Ent.h"
#include "Entities/Platformer/Enemies/EndianForest/GoblinGruntBoar.h"
#include "Entities/Platformer/Enemies/EndianForest/GoblinShaman.h"
#include "Entities/Platformer/Enemies/EndianForest/GoblinWarriorPig.h"
#include "Entities/Platformer/Enemies/EndianForest/KingGrogg.h"
#include "Entities/Platformer/Enemies/EndianForest/Ogre.h"
#include "Entities/Platformer/Enemies/EndianForest/OrcBomber.h"
#include "Entities/Platformer/Enemies/EndianForest/OrcGrunt.h"
#include "Entities/Platformer/Enemies/EndianForest/OrcSwordsman.h"
#include "Entities/Platformer/Enemies/EndianForest/OrcWarrior.h"
#include "Entities/Platformer/Enemies/EndianForest/Troll.h"
#include "Entities/Platformer/Helpers/EndianForest/Goblin.h"
#include "Entities/Platformer/Helpers/EndianForest/Turtle.h"
#include "Entities/Platformer/Npcs/EndianForest/Appolo.h"
#include "Entities/Platformer/Npcs/EndianForest/Chiron.h"
#include "Entities/Platformer/Npcs/EndianForest/Cooper.h"
#include "Entities/Platformer/Npcs/EndianForest/Dudly.h"
#include "Entities/Platformer/Npcs/EndianForest/Gramps.h"
#include "Entities/Platformer/Npcs/EndianForest/Lycan.h"
#include "Entities/Platformer/Npcs/EndianForest/Minos.h"
#include "Entities/Platformer/Npcs/EndianForest/Polyphemus.h"
#include "Entities/Platformer/Npcs/EndianForest/PrincessMatu.h"
#include "Entities/Platformer/Npcs/EndianForest/Robin.h"
#include "Entities/Platformer/Npcs/EndianForest/Rupert.h"
#include "Entities/Platformer/Npcs/EndianForest/Rusty.h"
#include "Entities/Platformer/Npcs/EndianForest/Toben.h"

////O////O////O////O////O////O////O////O////O////O/

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

HexusOpponentMenuEndianForest::HexusOpponentMenuEndianForest() : super(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter::Castle, HexusChapterPreviewCastle::SaveKeyChapterName)
{
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/

	this->opponents.push_back(HexusOpponentPreview::create(Centaur::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Cyclops::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Ent::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(GoblinGruntBoar::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(GoblinShaman::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(GoblinWarriorPig::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(KingGrogg::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Ogre::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(OrcBomber::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(OrcGrunt::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(OrcSwordsman::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(OrcWarrior::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Troll::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Goblin::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Turtle::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Appolo::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Chiron::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Cooper::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Dudly::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Gramps::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Lycan::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Minos::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Polyphemus::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(PrincessMatu::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Robin::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Rupert::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Rusty::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Toben::getHexusOpponentData()));

	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/

	for (std::vector<HexusOpponentPreview*>::iterator it = this->opponents.begin(); it != this->opponents.end(); ++it)
	{
		this->scrollPane->addChild(*it);
	}
}

HexusOpponentMenuEndianForest::~HexusOpponentMenuEndianForest()
{
}
