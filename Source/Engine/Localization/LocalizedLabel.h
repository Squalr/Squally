#pragma once
#include <string>

#include "cocos/2d/CCLabel.h"
#include "cocos/platform/CCCommon.h"

class LocalizedString;

class LocalizedLabel : public cocos2d::Label
{
public:
	enum class FontStyle
	{
		Main,
		Monospaced,
		Coding,
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
		H4,
		P,
		Small,
		Tiny,
		Micro,
		
		MAX = S1,
		MIN = Micro,
	};

	static LocalizedLabel* create(
		FontStyle fontStyle, 
		FontSize fontSize,
		LocalizedString* localizedString,
		const cocos2d::CSize& dimensions = cocos2d::CSize::ZERO,
		cocos2d::TextHAlignment hAlignment = cocos2d::TextHAlignment::LEFT,
		cocos2d::TextVAlignment vAlignment = cocos2d::TextVAlignment::TOP
	);

	LocalizedLabel* clone();
	void setLocalizedString(LocalizedString* localizedString);
	void setStringReplacementVariables(LocalizedString* stringReplacementVariable);
	void setStringReplacementVariables(std::vector<LocalizedString*> stringReplacementVariables);
	void setFontSize(FontSize fontSize);
	bool increaseFontSize();
	bool decreaseFontSize();
	float getFontSize();
	std::string getFont();
	
    void enableShadow(const cocos2d::Color4B& shadowColor = cocos2d::Color4B::BLACK, const cocos2d::CSize& offset = cocos2d::CSize(2,-2), int blurRadius = 0) override;
    void enableOutline(const cocos2d::Color4B& outlineColor, int outlineSize = -1) override;
    void enableGlow(const cocos2d::Color4B& glowColor) override;

protected:
	LocalizedLabel(
		FontStyle fontStyle,
		FontSize fontSize,
		LocalizedString* localizedString,
		const cocos2d::CSize& dimensions = cocos2d::CSize::ZERO,
		cocos2d::TextHAlignment hAlignment = cocos2d::TextHAlignment::LEFT,
		cocos2d::TextVAlignment vAlignment = cocos2d::TextVAlignment::TOP);
	virtual ~LocalizedLabel();

private:
	typedef cocos2d::Label super;
	friend class TypeWriterEffect; // I dont care if this is bad practice

	// Hide methods that we do not want available
	using super::setString;

	void onEnter() override;
	void onStringUpdate();
	void cleanupState();
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
	float getFontSizeH4();
	float getFontSizeP();
	float getFontSizeSmall();
	float getFontSizeTiny();
	float getFontSizeMicro();

	std::string getMainFont();
	std::string getMonospacedFont();
	std::string getCodingFont();

	LocalizedString* localizedString = nullptr;
	FontStyle fontStyle = FontStyle::Main;
	FontSize fontSize = FontSize::P;
};
