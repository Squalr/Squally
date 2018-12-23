#include "LocalizedLabel.h"

#include "Engine/Localization/LocalizedString.h"
#include "Engine/Localization/Localization.h"

LocalizedLabel* LocalizedLabel::create(FontStyle fontStyle, FontSize fontSize, LocalizedString* localizedString)
{
	LocalizedLabel* label = new LocalizedLabel(fontStyle, fontSize, localizedString);

	label->autorelease();

	return label;
}

LocalizedLabel* LocalizedLabel::create(FontStyle fontStyle, FontSize fontSize)
{
	LocalizedLabel* label = new LocalizedLabel(fontStyle, fontSize);

	label->autorelease();

	return label;
}

LocalizedLabel::LocalizedLabel(FontStyle fontStyle, FontSize fontSize, LocalizedString* localizedString)
{
	this->fontStyle = fontStyle;
	this->fontSize = fontSize;
	this->localizedString = localizedString;

	this->initializeStringToLocale(localizedString->getString());

	localizedString->setOnLocaleChangeCallback(CC_CALLBACK_1(LocalizedLabel::initializeStringToLocale, this));

	this->addChild(this->localizedString); // Just adding this to retain it -- this has no visuals
}

LocalizedLabel::LocalizedLabel(FontStyle fontStyle, FontSize fontSize)
{
	this->fontStyle = fontStyle;
	this->fontSize = fontSize;
	this->localizedString = nullptr;
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
	std::string fontPath;

	switch (this->fontStyle)
	{
		default:
		case FontStyle::Main:
			fontPath = Localization::getMainFont();
			break;
		case FontStyle::Coding:
			fontPath = Localization::getCodingFont();
			break;
		case FontStyle::Pixel:
			fontPath = Localization::getPixelFont();
			break;
	}

	float fontSize;

	switch (this->fontSize)
	{
		default:
		case FontSize::P:
			fontSize = Localization::getFontSizeP(fontPath);
			break;
		case FontSize::H1:
			fontSize = Localization::getFontSizeH1(fontPath);
			break;
		case FontSize::H2:
			fontSize = Localization::getFontSizeH2(fontPath);
			break;
		case FontSize::H3:
			fontSize = Localization::getFontSizeH3(fontPath);
			break;
	}

	this->initWithTTF(newString, fontPath, fontSize/*, dimensions, hAlignment, vAlignment*/);
}
