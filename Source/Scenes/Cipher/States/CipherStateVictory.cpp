#include "CipherStateVictory.h"

#include "2d/CCActionInstant.h"
#include "2d/CCActionInterval.h"
#include "2d/CCLayer.h"
#include "2d/CCSprite.h"
#include "base/CCDirector.h"
#include "base/CCEventCustom.h"
#include "base/CCEventListenerCustom.h"

#include "Engine/Events/InventoryEvents.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Events/CipherEvents.h"
#include "Events/NotificationEvents.h"
#include "Scenes/Cipher/CipherPuzzleData.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CipherStateVictory* CipherStateVictory::create()
{
	CipherStateVictory* instance = new CipherStateVictory();

	instance->autorelease();

	return instance;
}

CipherStateVictory::CipherStateVictory() : super(CipherState::StateType::Victory)
{
}

CipherStateVictory::~CipherStateVictory()
{
}

void CipherStateVictory::onBeforeStateEnter(CipherState* cipherState)
{
	super::onBeforeStateEnter(cipherState);
}

void CipherStateVictory::onStateEnter(CipherState* cipherState)
{
	super::onStateEnter(cipherState);
	
	if (cipherState->puzzleData->onUnlock != nullptr)
	{
		cipherState->puzzleData->onUnlock(cipherState->puzzleData);
	}

	CipherState::updateState(cipherState, CipherState::StateType::GameEnd);
}

void CipherStateVictory::onStateReload(CipherState* cipherState)
{
	super::onStateReload(cipherState);
}

void CipherStateVictory::onStateExit(CipherState* cipherState)
{
	super::onStateExit(cipherState);
}
