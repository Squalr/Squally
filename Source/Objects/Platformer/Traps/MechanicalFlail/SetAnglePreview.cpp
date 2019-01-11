#include "SetAnglePreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/ObjectResources.h"

#include "Strings/Hacking/Objects/Previews/RegisterEax.h"
#include "Strings/Hacking/Objects/Previews/RegisterRax.h"
#include "Engine/Hackables/HackableCode.h"

using namespace cocos2d;

SetAnglePreview* SetAnglePreview::create()
{
	SetAnglePreview* instance = new SetAnglePreview();

	instance->autorelease();

	return instance;
}

SetAnglePreview::SetAnglePreview()
{
	this->previewBlade = Sprite::create(ObjectResources::Traps_MechanicalFlail_PreviewFlail);

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

	this->previewBlade->setAnchorPoint(Vec2(0.5f, 1.0f));

	this->previewNode->addChild(this->previewBlade);
	this->assemblyTextNode->addChild(this->eax0Degrees);
	this->assemblyTextNode->addChild(this->eax90Degrees);
	this->assemblyTextNode->addChild(this->eax180Degrees);
	this->assemblyTextNode->addChild(this->eax270Degrees);
}

HackablePreview* SetAnglePreview::clone()
{
	return SetAnglePreview::create();
}

void SetAnglePreview::onEnter()
{
	super::onEnter();

	this->previewBlade->setRotation(0.0f);

	this->previewBlade->runAction(
		RepeatForever::create(Sequence::create(
			EaseSineInOut::create(RotateTo::create(1.5f, 270.0f)),
			EaseSineInOut::create(RotateTo::create(1.5f, 180.0f)),
			EaseSineInOut::create(RotateTo::create(1.5f, 90.0f)),
			EaseSineInOut::create(RotateTo::create(1.5f, 0.0f)),
			nullptr
		))
	);
}

void SetAnglePreview::initializePositions()
{
	super::initializePositions();

	const float offset = 24.0f;

	this->eax0Degrees->setPosition(Vec2(HackablePreview::PreviewRadius - offset, 0.0f));
	this->eax90Degrees->setPosition(Vec2(0.0f, HackablePreview::PreviewRadius - offset));
	this->eax180Degrees->setPosition(Vec2(-(HackablePreview::PreviewRadius - offset), 0.0f));
	this->eax270Degrees->setPosition(Vec2(0.0f, -(HackablePreview::PreviewRadius - offset)));
}
