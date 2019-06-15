#include "CipherChapterPreview.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Save/SaveManager.h"
#include "Scenes/Cipher/CipherState.h"

using namespace cocos2d;

CipherChapterPreview* CipherChapterPreview::create(std::string saveKey, std::string spriteResource, std::string spriteSelectedResource, std::string spriteDisabledResource)
{
	CipherChapterPreview* instance = new CipherChapterPreview(saveKey, spriteResource, spriteSelectedResource, spriteDisabledResource);

	instance->autorelease();

	return instance;
}

CipherChapterPreview::CipherChapterPreview(std::string saveKey, std::string spriteResource, std::string spriteSelectedResource, std::string spriteDisabledResource)
{
	this->saveKey = saveKey;
	this->previewNode = ClickableNode::create(spriteResource, spriteSelectedResource);
	this->previewNodeDisabled = Sprite::create(spriteDisabledResource);

	this->disableInteraction();

	this->addChild(this->previewNode);
	this->addChild(this->previewNodeDisabled);
}

CipherChapterPreview::~CipherChapterPreview()
{
}

void CipherChapterPreview::onEnter()
{
	super::onEnter();
}

void CipherChapterPreview::initializePositions()
{
	super::initializePositions();
}

void CipherChapterPreview::initializeListeners()
{
	super::initializeListeners();
}

void CipherChapterPreview::setClickCallback(std::function<void()> callback)
{
	this->previewNode->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		if (callback != nullptr)
		{
			callback();
		}
	});
}

std::string CipherChapterPreview::getSaveKey()
{
	return this->saveKey;
}

bool CipherChapterPreview::isChapterCleared()
{
	return SaveManager::getGlobalDataOrDefault(this->saveKey, Value(false)).asBool();
}
	void setClickCallback(std::function<void()> callback);

void CipherChapterPreview::enableInteraction()
{
	this->previewNode->enableInteraction(255);
	this->previewNodeDisabled->setVisible(false);
}

void CipherChapterPreview::disableInteraction()
{
	this->previewNode->disableInteraction(0);
	this->previewNodeDisabled->setVisible(true);
}
