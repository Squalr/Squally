#include "HackablePreview.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const float HackablePreview::PreviewRadius = 156.0f;
const Color4B HackablePreview::RegisterColor = Color4B(86, 156, 214, 255);

HackablePreview::HackablePreview()
{
	this->assemblyTextNode = Node::create();
	this->previewNode = Node::create();

	this->assemblyTextNode->setVisible(false);

	this->addChild(this->previewNode);
	this->addChild(this->assemblyTextNode);
}

HackablePreview::~HackablePreview()
{
}

void HackablePreview::setAssemblyTextVisible(bool isVisible)
{
	this->assemblyTextNode->setVisible(isVisible);
}

LocalizedLabel* HackablePreview::createRegisterEqualsValueLabel(HackableCode::Register reg, bool isPointer, LocalizedString* value)
{
	LocalizedLabel* label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Common_XEqualsYBiDi::create());

	if (isPointer)
	{
		LocalizedString* pointerString = Strings::Common_Brackets::create();

		pointerString->setStringReplacementVariables(HackableCode::registerToLocalizedString(reg));

		label->setStringReplacementVariables({ pointerString, value });
	}
	else
	{
		label->setStringReplacementVariables({ HackableCode::registerToLocalizedString(reg), value });
	}

	label->setTextColor(HackablePreview::RegisterColor);
	label->enableOutline(Color4B::BLACK, 2);

	return label;
}
