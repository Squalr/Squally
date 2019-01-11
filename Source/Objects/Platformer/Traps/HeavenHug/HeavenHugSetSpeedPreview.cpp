#include "HeavenHugSetSpeedPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/ObjectResources.h"

#include "Strings/Hacking/Objects/Previews/RegisterEax.h"
#include "Strings/Hacking/Objects/Previews/RegisterRax.h"

using namespace cocos2d;

HeavenHugSetSpeedPreview* HeavenHugSetSpeedPreview::create()
{
	HeavenHugSetSpeedPreview* instance = new HeavenHugSetSpeedPreview();

	instance->autorelease();

	return instance;
}

HeavenHugSetSpeedPreview::HeavenHugSetSpeedPreview()
{
	this->previewHeavenHug = Sprite::create(ObjectResources::Traps_HeavenHug_PreviewHeavenHug);

	if (sizeof(void*) == 4)
	{
		this->eax0Degrees = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Hacking_Objects_Previews_RegisterEax::create());
		this->eax90Degrees = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Hacking_Objects_Previews_RegisterEax::create());
		this->eax180Degrees = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Hacking_Objects_Previews_RegisterEax::create());
		this->eax270Degrees = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Hacking_Objects_Previews_RegisterEax::create());
	}
	else
	{
		this->eax0Degrees = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Hacking_Objects_Previews_RegisterRax::create());
		this->eax90Degrees = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Hacking_Objects_Previews_RegisterRax::create());
		this->eax180Degrees = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Hacking_Objects_Previews_RegisterRax::create());
		this->eax270Degrees = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Hacking_Objects_Previews_RegisterRax::create());
	}

	this->eax0Degrees->setTextColor(HackablePreview::RegisterColor);
	this->eax90Degrees->setTextColor(HackablePreview::RegisterColor);
	this->eax180Degrees->setTextColor(HackablePreview::RegisterColor);
	this->eax270Degrees->setTextColor(HackablePreview::RegisterColor);

	this->eax0Degrees->enableOutline(Color4B::BLACK, 2);
	this->eax90Degrees->enableOutline(Color4B::BLACK, 2);
	this->eax180Degrees->enableOutline(Color4B::BLACK, 2);
	this->eax270Degrees->enableOutline(Color4B::BLACK, 2);

	this->eax0Degrees->setStringReplacementVariables(ConstantString::create("0"));
	this->eax90Degrees->setStringReplacementVariables(ConstantString::create("90"));
	this->eax180Degrees->setStringReplacementVariables(ConstantString::create("180"));
	this->eax270Degrees->setStringReplacementVariables(ConstantString::create("270"));

	this->previewHeavenHug->setAnchorPoint(Vec2(0.5f, 1.0f));

	this->previewNode->addChild(this->previewHeavenHug);
	this->assemblyTextNode->addChild(this->eax0Degrees);
	this->assemblyTextNode->addChild(this->eax90Degrees);
	this->assemblyTextNode->addChild(this->eax180Degrees);
	this->assemblyTextNode->addChild(this->eax270Degrees);
}

HackablePreview* HeavenHugSetSpeedPreview::clone()
{
	return HeavenHugSetSpeedPreview::create();
}

void HeavenHugSetSpeedPreview::onEnter()
{
	super::onEnter();

	const float offset = 48.0f;

	this->previewHeavenHug->setPosition(Vec2(0.0f, HackablePreview::PreviewRadius - offset));

	this->previewHeavenHug->runAction(
		RepeatForever::create(Sequence::create(
			EaseSineInOut::create(MoveTo::create(1.5f, Vec2(0.0f, -(HackablePreview::PreviewRadius - offset)))),
			EaseSineInOut::create(MoveTo::create(1.5f, Vec2(0.0f, HackablePreview::PreviewRadius - offset))),
			nullptr
		))
	);
}

void HeavenHugSetSpeedPreview::initializePositions()
{
	super::initializePositions();

	const float offset = 24.0f;

	this->eax0Degrees->setPosition(Vec2(HackablePreview::PreviewRadius - offset, 0.0f));
	this->eax90Degrees->setPosition(Vec2(0.0f, HackablePreview::PreviewRadius - offset));
	this->eax180Degrees->setPosition(Vec2(-(HackablePreview::PreviewRadius - offset), 0.0f));
	this->eax270Degrees->setPosition(Vec2(0.0f, -(HackablePreview::PreviewRadius - offset)));
}
