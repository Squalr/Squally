#include "CipherPuzzlePreview.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/NavigationEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Scenes/Cipher/CipherPuzzles/CipherPuzzleData.h"
#include "Scenes/Cipher/CipherScene.h"
#include "Scenes/Cipher/CipherState.h"

using namespace cocos2d;

CipherPuzzlePreview* CipherPuzzlePreview::create(CipherPuzzleData* cipherPuzzleData, std::string spriteResource, std::string spriteSelectedResource, std::string spriteDisabledResource)
{
	CipherPuzzlePreview* instance = new CipherPuzzlePreview(cipherPuzzleData, spriteResource, spriteSelectedResource, spriteDisabledResource);

	instance->autorelease();

	return instance;
}

CipherPuzzlePreview::CipherPuzzlePreview(CipherPuzzleData* cipherPuzzleData, std::string spriteResource, std::string spriteSelectedResource, std::string spriteDisabledResource)
{
	this->cipherPuzzleData = cipherPuzzleData;
	this->previewNode = ClickableNode::create(spriteResource, spriteSelectedResource);
	this->previewNodeDisabled = Sprite::create(spriteDisabledResource);

	this->addChild(this->cipherPuzzleData);
	this->addChild(this->previewNode);
	this->addChild(this->previewNodeDisabled);
}

CipherPuzzlePreview::~CipherPuzzlePreview()
{
}

void CipherPuzzlePreview::onEnter()
{
	super::onEnter();
}

void CipherPuzzlePreview::initializePositions()
{
	super::initializePositions();
}

void CipherPuzzlePreview::initializeListeners()
{
	super::initializeListeners();

	this->previewNode->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		CipherScene* cipherScene = CipherScene::create(this->cipherPuzzleData);

		NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs(cipherScene));
	});
}

void CipherPuzzlePreview::enableInteraction()
{
	this->previewNode->enableInteraction(255);
	this->previewNodeDisabled->setVisible(false);
}

void CipherPuzzlePreview::disableInteraction()
{
	this->previewNode->disableInteraction(0);
	this->previewNodeDisabled->setVisible(true);
}

CipherPuzzleData* CipherPuzzlePreview::getPuzzleData()
{
	return this->cipherPuzzleData;
}
