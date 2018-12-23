#include "LocalizedLabel.h"

#include "Engine/Localization/LocalizedString.h"
#include "Engine/Localization/Localization.h"

using namespace cocos2d;

LocalizedLabel* LocalizedLabel::create(
	FontStyle fontStyle,
	FontSize fontSize,
	LocalizedString* localizedString,
	const Size& dimensions,
	TextHAlignment hAlignment,
	TextVAlignment vAlignment)
{
	LocalizedLabel* label = new LocalizedLabel(fontStyle, fontSize, localizedString, dimensions, hAlignment, vAlignment);

	label->autorelease();

	return label;
}

LocalizedLabel* LocalizedLabel::create(
	FontStyle fontStyle, 
	FontSize fontSize,
	const Size& dimensions,
	TextHAlignment hAlignment,
	TextVAlignment vAlignment)
{
	LocalizedLabel* label = new LocalizedLabel(fontStyle, fontSize, dimensions, hAlignment, vAlignment);

	label->autorelease();

	return label;
}

LocalizedLabel::LocalizedLabel(
	FontStyle fontStyle,
	FontSize fontSize,
	LocalizedString* localizedString,
	const Size& dimensions,
	TextHAlignment hAlignment,
	TextVAlignment vAlignment)
{
	this->fontStyle = fontStyle;
	this->fontSize = fontSize;
	this->localizedString = localizedString;

	this->initializeStringToLocale(localizedString->getString());

	localizedString->setOnLocaleChangeCallback(CC_CALLBACK_1(LocalizedLabel::initializeStringToLocale, this));

	this->addChild(this->localizedString); // Just adding this to retain it -- this has no visuals

	this->initWithTTF(localizedString->getString(), this->resolvedFontPath, this->resolvedFontSize, dimensions, hAlignment, vAlignment);
}

LocalizedLabel::LocalizedLabel(
	FontStyle fontStyle,
	FontSize fontSize,
	const Size& dimensions,
	TextHAlignment hAlignment,
	TextVAlignment vAlignment)
{
	this->fontStyle = fontStyle;
	this->fontSize = fontSize;
	this->localizedString = nullptr;

	this->initializeStringToLocale("");

	this->initWithTTF("", this->resolvedFontPath, this->resolvedFontSize, dimensions, hAlignment, vAlignment);
}

LocalizedLabel::~LocalizedLabel()
{
}

void LocalizedLabel::onEnter()
{
	Label::onEnter();

	// If this label is not bound to a localized string, we'll just listen for events to set the font style and size. Normally the string callback would handle thing.
	// This is generally used if this label is numeric, and thus has no localized string. We'd still want to update the font accordingly.
	if (this->localizedString == nullptr)
	{
		// TODO: Add event that refreshes the current fontstyle and font size 
		/*
		this->addGlobalEventListener(EventListenerCustom::create(LocalizationEvents::LocaleChangeEvent, [=](EventCustom* args)
		{
			if (this->onLocaleChange != nullptr)
			{
				this->onLocaleChange(this->getString());
			}
		}));*/
	}
}

LocalizedLabel* LocalizedLabel::clone()
{
	if (this->localizedString == nullptr)
	{
		return LocalizedLabel::create(this->fontStyle, this->fontSize);
	}

	return LocalizedLabel::create(this->fontStyle, this->fontSize, this->localizedString->clone());
}

void LocalizedLabel::initializeStringToLocale(std::string newString)
{
	this->resolvedString = newString;

	switch (this->fontStyle)
	{
		default:
		case FontStyle::Main:
			this->resolvedFontPath = Localization::getMainFont();
			break;
		case FontStyle::Coding:
			this->resolvedFontPath = Localization::getCodingFont();
			break;
		case FontStyle::Pixel:
			this->resolvedFontPath = Localization::getPixelFont();
			break;
	}

	switch (this->fontSize)
	{
		default:
		case FontSize::P:
			this->resolvedFontSize = Localization::getFontSizeP(this->resolvedFontPath);
			break;
		case FontSize::H1:
			this->resolvedFontSize = Localization::getFontSizeH1(this->resolvedFontPath);
			break;
		case FontSize::H2:
			this->resolvedFontSize = Localization::getFontSizeH2(this->resolvedFontPath);
			break;
		case FontSize::H3:
			this->resolvedFontSize = Localization::getFontSizeH3(this->resolvedFontPath);
			break;
	}

	// TODO: update font/font size

	this->setString(newString);
}
