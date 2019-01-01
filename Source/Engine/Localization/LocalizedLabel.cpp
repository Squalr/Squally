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

	this->setOverflow(Label::Overflow::RESIZE_HEIGHT);

	this->setLocalizedString(localizedString);
}

LocalizedLabel::~LocalizedLabel()
{
}

void LocalizedLabel::onEnter()
{
	super::onEnter();
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
		return;
	}

	this->setDimensions(dimensions.width, dimensions.height);
	this->setHorizontalAlignment(hAlignment);
	this->setVerticalAlignment(vAlignment);

	this->onLocaleChange(this->localizedString);

	this->localizedString->setOnLocaleChangeCallback(CC_CALLBACK_1(LocalizedLabel::onLocaleChange, this));

	this->addChild(this->localizedString); // Just adding this to retain it -- this has no visuals
}

float LocalizedLabel::getFontSize()
{
	switch (this->fontSize)
	{
		case FontSize::M1:
		{
			return LocalizedLabel::getFontSizeM1(this->getFont());
			break;
		}
		case FontSize::M2:
		{
			return LocalizedLabel::getFontSizeM2(this->getFont());
			break;
		}
		case FontSize::M3:
		{
			return LocalizedLabel::getFontSizeM3(this->getFont());
			break;
		}
		case FontSize::H1:
		{
			return LocalizedLabel::getFontSizeH1(this->getFont());
			break;
		}
		case FontSize::H2:
		{
			return LocalizedLabel::getFontSizeH2(this->getFont());
			break;
		}
		case FontSize::H3:
		{
			return LocalizedLabel::getFontSizeH3(this->getFont());
			break;
		}
		default:
		case FontSize::P:
		{
			return LocalizedLabel::getFontSizeP(this->getFont());
			break;
		}
		case FontSize::Small:
		{
			return LocalizedLabel::getFontSizeSmall(this->getFont());
			break;
		}
	}
}

std::string LocalizedLabel::getFont()
{
	switch (this->fontStyle)
	{
		default:
		case FontStyle::Main:
		{
			return LocalizedLabel::getMainFont();
			break;
		}
		case FontStyle::Coding:
		{
			return LocalizedLabel::getCodingFont();
			break;
		}
		case FontStyle::Pixel:
		{
			return LocalizedLabel::getPixelFont();
			break;
		}
	}
}

void LocalizedLabel::onLocaleChange(LocalizedString* localizedString)
{
	this->initWithTTF(
		localizedString->getString(),
		this->getFont(),
		this->getFontSize(),
		this->getDimensions(), 
		this->getHorizontalAlignment(),
		this->getVerticalAlignment()
	);
}

void LocalizedLabel::runTypeWriterEffect(float speed)
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
			this->getLetter(it->second)->runAction(FadeTo::create(0.1f, 255));
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

	}, speed, max - 1, 0, LocalizedLabel::ScheduleKeyTypeWriterEffect);
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
			return FontResources::Pixel_Standard_Pixel_Zpix;
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
			return FontResources::Pixel_Standard_Pixel_Zpix;
		}
	}
}

std::string LocalizedLabel::getMainFont()
{
	switch (Localization::getLanguage())
	{
		case LanguageType::CHINESE_SIMPLIFIED:
		{
			return FontResources::Main_ChineseSimplified_NotoSansCJKsc_Medium;
		}
		case LanguageType::CHINESE_TRADITIONAL:
		{
			return FontResources::Main_ChineseTraditional_NotoSansCJKtc_Medium;
		}
		case LanguageType::JAPANESE:
		{
			return FontResources::Main_Japanese_NotoSansCJKjp_Medium;
		}
		case LanguageType::KOREAN:
		{
			return FontResources::Main_Korean_NotoSansCJKkr_Medium;
		}
		case LanguageType::ARABIC:
		{
			return FontResources::Main_Arabic_NotoSansArabic_Medium;
		}
		case LanguageType::THAI:
		{
			return FontResources::Main_Thai_NotoSansThai_Medium;
		}
		default:
		{
			// This covers almost all languages with a standard alphabet (cyrillic, greek, latin based)
			return FontResources::Main_Standard_NotoSans_Medium;
		}
	}
}

std::string LocalizedLabel::getCodingFont()
{
	switch (Localization::getLanguage())
	{
		case LanguageType::CHINESE_SIMPLIFIED:
		{
			return FontResources::Coding_ChineseSimplified_NotoSansMonoCJKsc_Bold;
		}
		case LanguageType::CHINESE_TRADITIONAL:
		{
			return FontResources::Coding_ChineseTraditional_NotoSansMonoCJKtc_Bold;
		}
		case LanguageType::JAPANESE:
		{
			return FontResources::Coding_Japanese_NotoSansMonoCJKjp_Bold;
		}
		case LanguageType::KOREAN:
		{
			return FontResources::Coding_Korean_NotoSansMonoCJKkr_Bold;
		}
		case LanguageType::ARABIC:
		{
			return FontResources::Main_Arabic_NotoSansArabic_Bold;
		}
		case LanguageType::THAI:
		{
			return FontResources::Main_Thai_NotoSansThai_Bold;
		}
		default:
		{
			// This covers almost all languages with a standard alphabet (cyrillic, greek, latin based)
			return FontResources::Coding_Standard_NotoMono_Regular;
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
