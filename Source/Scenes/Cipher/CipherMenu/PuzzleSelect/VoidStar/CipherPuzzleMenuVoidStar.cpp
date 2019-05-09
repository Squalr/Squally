#include "CipherPuzzleMenuVoidStar.h"

#include "Engine/GlobalDirector.h"
#include "Events/NavigationEvents.h"
#include "Scenes/Cipher/CipherMenu/PuzzleSelect/CipherPuzzlePreview.h"
#include "Scenes/Cipher/CipherPuzzles/CipherPuzzleData.h"
#include "Scenes/Cipher/CipherPuzzles/CipherPuzzleDeserializer.h"

#include "Resources/CipherResources.h"

using namespace cocos2d;

CipherPuzzleMenuVoidStar* CipherPuzzleMenuVoidStar::instance = nullptr;
std::string CipherPuzzleMenuVoidStar::ChapterSavekey = "CIPHER_CHAPTER_VOID_STAR";

void CipherPuzzleMenuVoidStar::registerGlobalScene()
{
	if (CipherPuzzleMenuVoidStar::instance == nullptr)
	{
		CipherPuzzleMenuVoidStar::instance = new CipherPuzzleMenuVoidStar();

		CipherPuzzleMenuVoidStar::instance->autorelease();
		CipherPuzzleMenuVoidStar::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(CipherPuzzleMenuVoidStar::instance);
}

CipherPuzzleMenuVoidStar::CipherPuzzleMenuVoidStar() : super(NavigationEvents::NavigateCipherPuzzleSelectArgs::Chapter::VoidStar, CipherPuzzleMenuVoidStar::ChapterSavekey)
{
	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_VoidStar_Chest0,
		CipherResources::Menus_VoidStar_Chest0,
		CipherResources::Menus_VoidStar_Chest0
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_VoidStar_Chest1,
		CipherResources::Menus_VoidStar_Chest1,
		CipherResources::Menus_VoidStar_Chest1
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_VoidStar_Chest2,
		CipherResources::Menus_VoidStar_Chest2,
		CipherResources::Menus_VoidStar_Chest2
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_VoidStar_Chest3,
		CipherResources::Menus_VoidStar_Chest3,
		CipherResources::Menus_VoidStar_Chest3
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_VoidStar_Chest4,
		CipherResources::Menus_VoidStar_Chest4,
		CipherResources::Menus_VoidStar_Chest4
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_VoidStar_Chest5,
		CipherResources::Menus_VoidStar_Chest5,
		CipherResources::Menus_VoidStar_Chest5
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_VoidStar_Chest6,
		CipherResources::Menus_VoidStar_Chest6,
		CipherResources::Menus_VoidStar_Chest6
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_VoidStar_Chest7,
		CipherResources::Menus_VoidStar_Chest7,
		CipherResources::Menus_VoidStar_Chest7
	));

	this->buildCipherList();
}

CipherPuzzleMenuVoidStar::~CipherPuzzleMenuVoidStar()
{
}
