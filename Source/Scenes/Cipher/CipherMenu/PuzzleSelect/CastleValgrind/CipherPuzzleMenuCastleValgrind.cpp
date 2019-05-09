#include "CipherPuzzleMenuCastleValgrind.h"

#include "Engine/GlobalDirector.h"
#include "Events/NavigationEvents.h"
#include "Scenes/Cipher/CipherMenu/PuzzleSelect/CipherPuzzlePreview.h"
#include "Scenes/Cipher/CipherPuzzles/CipherPuzzleData.h"
#include "Scenes/Cipher/CipherPuzzles/CipherPuzzleDeserializer.h"

#include "Resources/CipherResources.h"

using namespace cocos2d;

CipherPuzzleMenuCastleValgrind* CipherPuzzleMenuCastleValgrind::instance = nullptr;
std::string CipherPuzzleMenuCastleValgrind::ChapterSavekey = "CIPHER_CHAPTER_CASTLE_VALGRIND";

void CipherPuzzleMenuCastleValgrind::registerGlobalScene()
{
	if (CipherPuzzleMenuCastleValgrind::instance == nullptr)
	{
		CipherPuzzleMenuCastleValgrind::instance = new CipherPuzzleMenuCastleValgrind();

		CipherPuzzleMenuCastleValgrind::instance->autorelease();
		CipherPuzzleMenuCastleValgrind::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(CipherPuzzleMenuCastleValgrind::instance);
}

CipherPuzzleMenuCastleValgrind::CipherPuzzleMenuCastleValgrind() : super(NavigationEvents::NavigateCipherPuzzleSelectArgs::Chapter::CastleValgrind, CipherPuzzleMenuCastleValgrind::ChapterSavekey)
{
	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_CastleValgrind_Chest0,
		CipherResources::Menus_CastleValgrind_Chest0,
		CipherResources::Menus_CastleValgrind_Chest0
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_CastleValgrind_Chest1,
		CipherResources::Menus_CastleValgrind_Chest1,
		CipherResources::Menus_CastleValgrind_Chest1
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_CastleValgrind_Chest2,
		CipherResources::Menus_CastleValgrind_Chest2,
		CipherResources::Menus_CastleValgrind_Chest2
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_CastleValgrind_Chest3,
		CipherResources::Menus_CastleValgrind_Chest3,
		CipherResources::Menus_CastleValgrind_Chest3
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_CastleValgrind_Chest4,
		CipherResources::Menus_CastleValgrind_Chest4,
		CipherResources::Menus_CastleValgrind_Chest4
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_CastleValgrind_Chest5,
		CipherResources::Menus_CastleValgrind_Chest5,
		CipherResources::Menus_CastleValgrind_Chest5
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_CastleValgrind_Chest6,
		CipherResources::Menus_CastleValgrind_Chest6,
		CipherResources::Menus_CastleValgrind_Chest6
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_CastleValgrind_Chest7,
		CipherResources::Menus_CastleValgrind_Chest7,
		CipherResources::Menus_CastleValgrind_Chest7
	));

	this->buildCipherList();
}

CipherPuzzleMenuCastleValgrind::~CipherPuzzleMenuCastleValgrind()
{
}
