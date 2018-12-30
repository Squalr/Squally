#include "LocalizedLabel.h"

#include "cocos/2d/CCSprite.h"

#include "2d/CCActionInterval.h"

#include "Engine/Localization/LocalizedString.h"
#include "Engine/Localization/Localization.h"

#include "Resources/FontResources.h"

#include "Strings/Empty.h"

const std::string LocalizedLabel::ScheduleKeyTypeWriterEffect = "SCHEDULE_TYPE_WRITER_EFFECT";
const float LocalizedLabel::DefaultTypeSpeed = 0.025f;

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
	LocalizedLabel* label = new LocalizedLabel(fontStyle, fontSize, LocaleStrings::Empty::create(), dimensions, hAlignment, vAlignment);

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
	this->typeWriterFinishedCallback = nullptr;
	this->typeWriterSpeed = LocalizedLabel::DefaultTypeSpeed;

	this->setOverflow(Label::Overflow::RESIZE_HEIGHT);

	this->setLocalizedString(localizedString);
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

void LocalizedLabel::setLocalizedString(LocalizedString* localizedString, const Size& dimensions, TextHAlignment hAlignment, TextVAlignment vAlignment)
{
	if (this->localizedString != nullptr)
	{
		this->removeChild(this->localizedString);
	}

	this->localizedString = localizedString;

	if (this->localizedString == nullptr)
	{
		this->initializeStringToLocale("");
		return;
	}

	this->initializeStringToLocale(this->localizedString->getString());
	this->localizedString->setOnLocaleChangeCallback(CC_CALLBACK_1(LocalizedLabel::initializeStringToLocale, this));

	this->addChild(this->localizedString); // Just adding this to retain it -- this has no visuals

	this->initWithTTF(this->localizedString->getString(), this->resolvedFontPath, this->resolvedFontSize, dimensions, hAlignment, vAlignment);
}

float LocalizedLabel::getFontSize()
{
	return this->resolvedFontSize;
}

std::string LocalizedLabel::getFont()
{
	return this->resolvedFontPath;
}

void LocalizedLabel::initializeStringToLocale(std::string newString)
{
	this->resolvedString = newString;

	switch (this->fontStyle)
	{
		default:
		case FontStyle::Main:
		{
			this->resolvedFontPath = LocalizedLabel::getMainFont();
			break;
		}
		case FontStyle::Coding:
		{
			this->resolvedFontPath = LocalizedLabel::getCodingFont();
			break;
		}
		case FontStyle::Pixel:
		{
			this->resolvedFontPath = LocalizedLabel::getPixelFont();
			break;
		}
	}

	switch (this->fontSize)
	{
		case FontSize::M1:
		{
			this->resolvedFontSize = LocalizedLabel::getFontSizeM1(this->resolvedFontPath);
			break;
		}
		case FontSize::M2:
		{
			this->resolvedFontSize = LocalizedLabel::getFontSizeM2(this->resolvedFontPath);
			break;
		}
		case FontSize::M3:
		{
			this->resolvedFontSize = LocalizedLabel::getFontSizeM3(this->resolvedFontPath);
			break;
		}
		case FontSize::H1:
		{
			this->resolvedFontSize = LocalizedLabel::getFontSizeH1(this->resolvedFontPath);
			break;
		}
		case FontSize::H2:
		{
			this->resolvedFontSize = LocalizedLabel::getFontSizeH2(this->resolvedFontPath);
			break;
		}
		case FontSize::H3:
		{
			this->resolvedFontSize = LocalizedLabel::getFontSizeH3(this->resolvedFontPath);
			break;
		}
		default:
		case FontSize::P:
		{
			this->resolvedFontSize = LocalizedLabel::getFontSizeP(this->resolvedFontPath);
			break;
		}
		case FontSize::Small:
		{
			this->resolvedFontSize = LocalizedLabel::getFontSizeSmall(this->resolvedFontPath);
			break;
		}
	}

	// TODO: update font/font size

	this->setString(newString);
}

void LocalizedLabel::setTypeWriterSpeed(float speed)
{
	this->typeWriterSpeed = speed;
}

void LocalizedLabel::runTypeWriterEffect()
{
	this->unschedule(LocalizedLabel::ScheduleKeyTypeWriterEffect);

	static std::map<LocalizedLabel*, int> mapTypeIdx;
	std::map<LocalizedLabel*, int>::iterator it;
	it = mapTypeIdx.find(this);

	if (it == mapTypeIdx.end())
	{
		mapTypeIdx.insert(std::pair<LocalizedLabel*, int>(this, 0));
		it = mapTypeIdx.find(this);
	}
	else
	{
		it->second = 0;
	}

	int max = this->getStringLength();

	for (int i = 0; i < max; i++)
	{
		if (this->getLetter(i) != nullptr)
		{
			this->getLetter(i)->setOpacity(0);
		}
	}

	// TODO: It would be cool to introduce some delay upon encountering a period. Of course w/ localization, this may be a unicode period (ie japanese)
	this->schedule([=](float dt)
	{
		if (this->getLetter(it->second) != nullptr)
		{
			this->getLetter(it->second)->runAction(FadeTo::create(0.25f, 255));
		}

		it->second++;

		if (it->second == max)
		{
			this->unschedule(LocalizedLabel::ScheduleKeyTypeWriterEffect);
			mapTypeIdx.erase(it);

			if (this->typeWriterFinishedCallback != nullptr)
			{
				this->typeWriterFinishedCallback();
			}
		}

	}, this->typeWriterSpeed, max - 1, 0, LocalizedLabel::ScheduleKeyTypeWriterEffect);
}

void LocalizedLabel::setTypeWriterFinishedCallback(std::function<void()> callback)
{
	this->typeWriterFinishedCallback = callback;
}

std::string LocalizedLabel::getPixelFont()
{
	switch (Localization::getLanguage())
	{
		default:
		case LanguageType::ENGLISH:
		case LanguageType::CHINESE_SIMPLIFIED:
		case LanguageType::CHINESE_TRADITIONAL:
		case LanguageType::JAPANESE:
		case LanguageType::KOREAN:
		{
			return FontResources::Pixel_Zpix;
		}
		case LanguageType::ARABIC:
		case LanguageType::BULGARIAN:
		case LanguageType::CZECH:
		case LanguageType::DANISH:
		case LanguageType::DUTCH:
		case LanguageType::FINNISH:
		case LanguageType::FRENCH:
		case LanguageType::GERMAN:
		case LanguageType::GREEK:
		case LanguageType::HUNGARIAN:
		case LanguageType::ITALIAN:
		case LanguageType::NORWEGIAN:
		case LanguageType::POLISH:
		case LanguageType::PORTUGUESE:
		case LanguageType::PORTUGUESE_BRAZIL:
		case LanguageType::ROMANIAN:
		case LanguageType::RUSSIAN:
		case LanguageType::SPANISH:
		case LanguageType::SPANISH_LATIN_AMERICAN:
		case LanguageType::SWEDISH:
		case LanguageType::THAI:
		case LanguageType::TURKISH:
		case LanguageType::UKRAINIAN:
		case LanguageType::VIETNAMESE:
		{
			// TODO
			return FontResources::Pixel_Zpix;
		}
	}
}

std::string LocalizedLabel::getMainFont()
{
	switch (Localization::getLanguage())
	{
		default:
		case LanguageType::ENGLISH:
		{
			return FontResources::Montserrat_Medium;
		}
		case LanguageType::CHINESE_SIMPLIFIED:
		case LanguageType::CHINESE_TRADITIONAL:
		case LanguageType::JAPANESE:
		case LanguageType::KOREAN:
		case LanguageType::ARABIC:
		case LanguageType::BULGARIAN:
		case LanguageType::CZECH:
		case LanguageType::DANISH:
		case LanguageType::DUTCH:
		case LanguageType::FINNISH:
		case LanguageType::FRENCH:
		case LanguageType::GERMAN:
		case LanguageType::GREEK:
		case LanguageType::HUNGARIAN:
		case LanguageType::ITALIAN:
		case LanguageType::NORWEGIAN:
		case LanguageType::POLISH:
		case LanguageType::PORTUGUESE:
		case LanguageType::PORTUGUESE_BRAZIL:
		case LanguageType::ROMANIAN:
		case LanguageType::RUSSIAN:
		case LanguageType::SPANISH:
		case LanguageType::SPANISH_LATIN_AMERICAN:
		case LanguageType::SWEDISH:
		case LanguageType::THAI:
		case LanguageType::TURKISH:
		case LanguageType::UKRAINIAN:
		case LanguageType::VIETNAMESE:
		{
			// TODO
			return FontResources::Montserrat_Medium;
		}
	}
}

std::string LocalizedLabel::getCodingFont()
{
	switch (Localization::getLanguage())
	{
		default:
		case LanguageType::ENGLISH:
		{
			return FontResources::UbuntuMono_Bold;
		}
		case LanguageType::CHINESE_SIMPLIFIED:
		case LanguageType::CHINESE_TRADITIONAL:
		case LanguageType::JAPANESE:
		case LanguageType::KOREAN:
		{
			return FontResources::Ubuntu_WenQuanYiMicroHeiMono_02;
		}
		case LanguageType::ARABIC:
		case LanguageType::BULGARIAN:
		case LanguageType::CZECH:
		case LanguageType::DANISH:
		case LanguageType::DUTCH:
		case LanguageType::FINNISH:
		case LanguageType::FRENCH:
		case LanguageType::GERMAN:
		case LanguageType::GREEK:
		case LanguageType::HUNGARIAN:
		case LanguageType::ITALIAN:
		case LanguageType::NORWEGIAN:
		case LanguageType::POLISH:
		case LanguageType::PORTUGUESE:
		case LanguageType::PORTUGUESE_BRAZIL:
		case LanguageType::ROMANIAN:
		case LanguageType::RUSSIAN:
		case LanguageType::SPANISH:
		case LanguageType::SPANISH_LATIN_AMERICAN:
		case LanguageType::SWEDISH:
		case LanguageType::THAI:
		case LanguageType::TURKISH:
		case LanguageType::UKRAINIAN:
		case LanguageType::VIETNAMESE:
		{
			// TODO
			return FontResources::UbuntuMono_Bold;
		}
	}
}

float LocalizedLabel::getFontSizeM1(std::string fontResource)
{
	return 80.0f;
}

float LocalizedLabel::getFontSizeM2(std::string fontResource)
{
	return 64.0f;
}

float LocalizedLabel::getFontSizeM3(std::string fontResource)
{
	return 48.0f;
}

float LocalizedLabel::getFontSizeH1(std::string fontResource)
{
	return 32.0f;
}

float LocalizedLabel::getFontSizeH2(std::string fontResource)
{
	return 28.0f;
}

float LocalizedLabel::getFontSizeH3(std::string fontResource)
{
	return 24.0f;
}

float LocalizedLabel::getFontSizeP(std::string fontResource)
{
	return 20.0f;
}

float LocalizedLabel::getFontSizeSmall(std::string fontResource)
{
	return 16.0f;
}
