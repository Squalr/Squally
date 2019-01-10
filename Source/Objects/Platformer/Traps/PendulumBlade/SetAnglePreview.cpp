#include "SetAnglePreview.h"

#include "cocos/2d/CCSprite.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

SetAnglePreview* SetAnglePreview::create()
{
	SetAnglePreview* instance = new SetAnglePreview();

	instance->autorelease();

	return instance;
}

SetAnglePreview::SetAnglePreview()
{
	this->previewBlade = Sprite::create(ObjectResources::Traps_PendulumBlade_PreviewBlade);

	this->previewNode->addChild(this->previewBlade);
}

HackablePreview* SetAnglePreview::clone()
{
	return SetAnglePreview::create();
}