#pragma once
#include <string>

#include "cocos/2d/CCLabel.h"
#include "cocos/platform/CCCommon.h"

class LocalizedString;
class ClickableNode;

class LocalizedLabel : public cocos2d::Label
{
public:
	enum class FontStyle
	{
		Main,
		Coding,
		Monospaced,
	};

	enum class FontSize
	{
		// Listed in decreasing size
		S1,
		S2,
		S3,
		M1,
		M2,
		M3,
		H1,
		H2,
		H3,
		P,
		Small,
	};

	static LocalizedLabel* create(
		FontStyle fontStyle, 
		FontSize fontSize,
		LocalizedString* localizedString,
		const cocos2d::Size& dimensions = cocos2d::Size::ZERO,
		cocos2d::TextHAlignment hAlignment = cocos2d::TextHAlignment::LEFT,
		cocos2d::TextVAlignment vAlignment = cocos2d::TextVAlignment::TOP
	);

	LocalizedLabel* clone();
	void setLocalizedString(LocalizedString* localizedString);
	void setStringReplacementVariables(LocalizedString* stringReplacementVariable);
	void setStringReplacementVariables(std::vector<LocalizedString*> stringReplacementVariables);
	void setFontSize(FontSize fontSize);
	float getFontSize();
	std::string getFont();

private:
	typedef cocos2d::Label super;
	friend class TypeWriterEffect; // I dont care if this is bad practice

	LocalizedLabel(
		FontStyle fontStyle,
		FontSize fontSize,
		LocalizedString* localizedString,
		const cocos2d::Size& dimensions = cocos2d::Size::ZERO,
		cocos2d::TextHAlignment hAlignment = cocos2d::TextHAlignment::LEFT,
		cocos2d::TextVAlignment vAlignment = cocos2d::TextVAlignment::TOP);
	~LocalizedLabel();

	// Hide methods that we do not want available
	using super::setString;

	void onEnter() override;
	void onStringUpdate(LocalizedString* localizedString);
	cocos2d::LanguageType getCurrentLanguage();
	float getFontSizeS1();
	float getFontSizeS2();
	float getFontSizeS3();
	float getFontSizeM1();
	float getFontSizeM2();
	float getFontSizeM3();
	float getFontSizeH1();
	float getFontSizeH2();
	float getFontSizeH3();
	float getFontSizeP();
	float getFontSizeSmall();

	std::string getPixelFont();
	std::string getMainFont();
	std::string getMonospacedFont();
	std::string getCodingFont();

	LocalizedString* localizedString;
	FontStyle fontStyle;
	FontSize fontSize;
};
