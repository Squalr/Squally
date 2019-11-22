#include "CipherConnectTutorial.h"

#include <vector>

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/HelpArrow.h"
#include "Engine/UI/HUD/FocusTakeOver.h"
#include "Scenes/Cipher/CipherState.h"

#include "Resources/UIResources.h"

#include "Strings/Menus/GotIt.h"
#include "Strings/Menus/Next.h"

using namespace cocos2d;

const std::string CipherConnectTutorial::MapKeyTutorial = "connect";

CipherConnectTutorial* CipherConnectTutorial::create()
{
	CipherConnectTutorial* instance = new CipherConnectTutorial();

	instance->autorelease();

	return instance;
}

CipherConnectTutorial::CipherConnectTutorial() : super(CipherState::StateType::Neutral)
{
	this->focusTakeOver = FocusTakeOver::create();

	this->addChild(this->focusTakeOver);
}

CipherConnectTutorial::~CipherConnectTutorial()
{
}

void CipherConnectTutorial::onEnter()
{
	super::onEnter();
}

void CipherConnectTutorial::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}

void CipherConnectTutorial::initializeListeners()
{
	super::initializeListeners();
}

bool CipherConnectTutorial::tryHijackState(CipherState* gameState)
{
	this->initializeCallbacks(gameState);

	this->focusTakeOver->focus({});

	return true;
}

void CipherConnectTutorial::onBeforeStateChange(CipherState* gameState)
{
	super::onBeforeStateChange(gameState);
}

void CipherConnectTutorial::onAnyStateChange(CipherState* gameState)
{
	super::onAnyStateChange(gameState);
}

void CipherConnectTutorial::initializeCallbacks(CipherState* gameState)
{
}

void CipherConnectTutorial::unHijackState(CipherState* gameState)
{
	this->focusTakeOver->unfocus();
}
