#include "CipherPuzzleMenuUnderflowRuins.h"

#include "Engine/GlobalDirector.h"
#include "Events/NavigationEvents.h"
#include "Scenes/Cipher/CipherMenu/PuzzleSelect/CipherPuzzlePreview.h"
#include "Scenes/Cipher/CipherPuzzles/CipherPuzzleData.h"
#include "Scenes/Cipher/CipherPuzzles/CipherPuzzleDeserializer.h"

#include "Resources/CipherResources.h"

using namespace cocos2d;

CipherPuzzleMenuUnderflowRuins* CipherPuzzleMenuUnderflowRuins::instance = nullptr;
std::string CipherPuzzleMenuUnderflowRuins::ChapterSavekey = "CIPHER_CHAPTER_UNDERFLOW_RUINS";

void CipherPuzzleMenuUnderflowRuins::registerGlobalScene()
{
	if (CipherPuzzleMenuUnderflowRuins::instance == nullptr)
	{
		CipherPuzzleMenuUnderflowRuins::instance = new CipherPuzzleMenuUnderflowRuins();

		CipherPuzzleMenuUnderflowRuins::instance->autorelease();
		CipherPuzzleMenuUnderflowRuins::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(CipherPuzzleMenuUnderflowRuins::instance);
}

CipherPuzzleMenuUnderflowRuins::CipherPuzzleMenuUnderflowRuins() : super(NavigationEvents::NavigateCipherPuzzleSelectArgs::Chapter::UnderflowRuins, CipherPuzzleMenuUnderflowRuins::ChapterSavekey)
{
	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_UnderflowRuins_Chest0,
		CipherResources::Menus_UnderflowRuins_Chest0,
		CipherResources::Menus_UnderflowRuins_Chest0
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_UnderflowRuins_Chest1,
		CipherResources::Menus_UnderflowRuins_Chest1,
		CipherResources::Menus_UnderflowRuins_Chest1
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_UnderflowRuins_Chest2,
		CipherResources::Menus_UnderflowRuins_Chest2,
		CipherResources::Menus_UnderflowRuins_Chest2
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_UnderflowRuins_Chest3,
		CipherResources::Menus_UnderflowRuins_Chest3,
		CipherResources::Menus_UnderflowRuins_Chest3
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_UnderflowRuins_Chest4,
		CipherResources::Menus_UnderflowRuins_Chest4,
		CipherResources::Menus_UnderflowRuins_Chest4
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_UnderflowRuins_Chest5,
		CipherResources::Menus_UnderflowRuins_Chest5,
		CipherResources::Menus_UnderflowRuins_Chest5
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_UnderflowRuins_Chest6,
		CipherResources::Menus_UnderflowRuins_Chest6,
		CipherResources::Menus_UnderflowRuins_Chest6
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_UnderflowRuins_Chest7,
		CipherResources::Menus_UnderflowRuins_Chest7,
		CipherResources::Menus_UnderflowRuins_Chest7
	));
	
	this->buildCipherList();
}

CipherPuzzleMenuUnderflowRuins::~CipherPuzzleMenuUnderflowRuins()
{
}
