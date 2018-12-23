#pragma once
#include <string>

#include "cocos/2d/CCLabel.h"

class LocalizedString;

class LocalizedLabel : public cocos2d::Label
{
public:
	enum class FontStyle
	{
		Main,
		Coding,
		Pixel,
	};

	enum class FontSize
	{
		H1,
		H2,
		H3,
		P,
		Small,
	};

	// const Size& dimensions = Size::ZERO, TextHAlignment hAlignment = TextHAlignment::LEFT, TextVAlignment vAlignment = TextVAlignment::TOP
	static LocalizedLabel* create(FontStyle fontStyle, FontSize fontSize, LocalizedString* localizedString);
	static LocalizedLabel* create(FontStyle fontStyle, FontSize fontSize);

	LocalizedLabel* clone();

private:
	LocalizedLabel(FontStyle fontStyle, FontSize fontSize, LocalizedString* localizedString);
	LocalizedLabel(FontStyle fontStyle, FontSize fontSize);
	~LocalizedLabel();

	void initializeStringToLocale(std::string newString);
	void onEnter() override;

	LocalizedString* localizedString;
	FontStyle fontStyle;
	FontSize fontSize;
};
