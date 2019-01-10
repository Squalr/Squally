#include "GenericPreview.h"

#include "cocos/2d/CCSprite.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

GenericPreview* GenericPreview::create()
{
	GenericPreview* instance = new GenericPreview();

	instance->autorelease();

	return instance;
}

GenericPreview::GenericPreview()
{
	this->previewBlade = Sprite::create(ObjectResources::Traps_PendulumBlade_PreviewBlade);

	this->previewNode->addChild(this->previewBlade);
}

HackablePreview* GenericPreview::clone()
{
	return GenericPreview::create();
}
