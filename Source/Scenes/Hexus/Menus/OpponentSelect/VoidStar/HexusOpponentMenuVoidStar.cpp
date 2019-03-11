////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "HexusOpponentMenuVoidStar.h"

#include "Engine/GlobalDirector.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Scenes/Hexus/Menus/ChapterSelect/Castle/HexusChapterPreviewCastle.h"
#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentPreview.h"
#include "Scenes/Hexus/Opponents/Castle/CastleHexusOpponents.h"

////X////X////X////X////X////X////X////X////X////X/

#include "Entities/Platformer/Enemies/VoidStar/Barbarian.h"
#include "Entities/Platformer/Enemies/VoidStar/EvilEye.h"
#include "Entities/Platformer/Enemies/VoidStar/Exterminator.h"
#include "Entities/Platformer/Enemies/VoidStar/Gorilla.h"
#include "Entities/Platformer/Enemies/VoidStar/MechBoxDrone.h"
#include "Entities/Platformer/Enemies/VoidStar/MechDog.h"
#include "Entities/Platformer/Enemies/VoidStar/MechGolem.h"
#include "Entities/Platformer/Enemies/VoidStar/MechGuard.h"
#include "Entities/Platformer/Enemies/VoidStar/MiteBot.h"
#include "Entities/Platformer/Enemies/VoidStar/SkeletalPirate.h"
#include "Entities/Platformer/Enemies/VoidStar/Thug.h"
#include "Entities/Platformer/Enemies/VoidStar/Viking.h"
#include "Entities/Platformer/Enemies/VoidStar/VikingBot.h"
#include "Entities/Platformer/Enemies/VoidStar/VikingBotSmall.h"
#include "Entities/Platformer/Helpers/VoidStar/Professor.h"
#include "Entities/Platformer/Helpers/VoidStar/Robot.h"
#include "Entities/Platformer/Npcs/VoidStar/Atreus.h"
#include "Entities/Platformer/Npcs/VoidStar/Elriel.h"
#include "Entities/Platformer/Npcs/VoidStar/Illia.h"
#include "Entities/Platformer/Npcs/VoidStar/Leon.h"
#include "Entities/Platformer/Npcs/VoidStar/Mara.h"
#include "Entities/Platformer/Npcs/VoidStar/Marcel.h"
#include "Entities/Platformer/Npcs/VoidStar/Piper.h"
#include "Entities/Platformer/Npcs/VoidStar/QueenElise.h"
#include "Entities/Platformer/Npcs/VoidStar/Radon.h"
#include "Entities/Platformer/Npcs/VoidStar/Thor.h"
#include "Entities/Platformer/Npcs/VoidStar/Xenon.h"
#include "Entities/Platformer/Npcs/VoidStar/Ysara.h"

////O////O////O////O////O////O////O////O////O////O/

using namespace cocos2d;

HexusOpponentMenuVoidStar* HexusOpponentMenuVoidStar::instance = nullptr;

void HexusOpponentMenuVoidStar::registerGlobalScene()
{
	if (HexusOpponentMenuVoidStar::instance == nullptr)
	{
		HexusOpponentMenuVoidStar::instance = new HexusOpponentMenuVoidStar();

		HexusOpponentMenuVoidStar::instance->autorelease();
		HexusOpponentMenuVoidStar::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(HexusOpponentMenuVoidStar::instance);
}

HexusOpponentMenuVoidStar::HexusOpponentMenuVoidStar() : super(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter::Castle, HexusChapterPreviewCastle::SaveKeyChapterName)
{
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/

	this->opponents.push_back(HexusOpponentPreview::create(Barbarian::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(EvilEye::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Exterminator::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Gorilla::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(MechBoxDrone::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(MechDog::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(MechGolem::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(MechGuard::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(MiteBot::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(SkeletalPirate::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Thug::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Viking::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(VikingBot::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(VikingBotSmall::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Professor::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Robot::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Atreus::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Elriel::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Illia::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Leon::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Mara::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Marcel::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Piper::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(QueenElise::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Radon::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Thor::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Xenon::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Ysara::getHexusOpponentData()));

	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/

	for (std::vector<HexusOpponentPreview*>::iterator it = this->opponents.begin(); it != this->opponents.end(); ++it)
	{
		this->scrollPane->addChild(*it);
	}
}

HexusOpponentMenuVoidStar::~HexusOpponentMenuVoidStar()
{
}
