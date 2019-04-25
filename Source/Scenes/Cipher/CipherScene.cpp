#include "CipherScene.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/GlobalDirector.h"
#include "Events/NavigationEvents.h"
#include "Scenes/Cipher/Cipher.h"

#include "Resources/CipherResources.h"

using namespace cocos2d;

CipherScene* CipherScene::instance = nullptr;

void CipherScene::registerGlobalScene()
{
	if (CipherScene::instance == nullptr)
	{
		CipherScene::instance = new CipherScene();

		CipherScene::instance->autorelease();
		CipherScene::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(CipherScene::instance);
}

CipherScene::CipherScene()
{
	this->cipher = Cipher::create();

	this->addChild(this->cipher);
}

CipherScene::~CipherScene()
{
}

void CipherScene::onEnter()
{
	super::onEnter();
	
	this->cipher->setVisible(true);
}

void CipherScene::initializePositions()
{
	super::initializePositions();
}

void CipherScene::initializeListeners()
{
	super::initializeListeners();

	CipherScene::instance->addGlobalEventListener(EventListenerCustom::create(NavigationEvents::EventNavigateCipher, [](EventCustom* eventCustom)
	{
		NavigationEvents::NavigateCipherArgs* args = static_cast<NavigationEvents::NavigateCipherArgs*>(eventCustom->getUserData());
		
		if (args != nullptr)
		{
			GlobalDirector::loadScene(CipherScene::instance);

			CipherScene::instance->cipher->openCipher(args->cipherPuzzleData);
		}
	}));
}

