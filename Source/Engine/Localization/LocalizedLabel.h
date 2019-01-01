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
		// Listed in decreasing size
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
	static LocalizedLabel* create(
		FontStyle fontStyle,
		FontSize fontSize,
		const cocos2d::Size& dimensions = cocos2d::Size::ZERO,
		cocos2d::TextHAlignment hAlignment = cocos2d::TextHAlignment::LEFT,
		cocos2d::TextVAlignment vAlignment = cocos2d::TextVAlignment::TOP
	);

	LocalizedLabel* clone();
	void setLocalizedString(
		LocalizedString* localizedString,
		const cocos2d::Size& dimensions = cocos2d::Size::ZERO,
		cocos2d::TextHAlignment hAlignment = cocos2d::TextHAlignment::LEFT,
		cocos2d::TextVAlignment vAlignment = cocos2d::TextVAlignment::TOP);
	void setStringReplacementVariables(std::vector<std::string> stringReplacementVariables);
	float getFontSize();
	std::string getFont();
	void runTypeWriterEffect(float speed = LocalizedLabel::DefaultTypeSpeed);
	void setTypeWriterFinishedCallback(std::function<void()> callback);

private:
	typedef cocos2d::Label super;
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
	static float getFontSizeM1(std::string fontResource);
	static float getFontSizeM2(std::string fontResource);
	static float getFontSizeM3(std::string fontResource);
	static float getFontSizeH1(std::string fontResource);
	static float getFontSizeH2(std::string fontResource);
	static float getFontSizeH3(std::string fontResource);
	static float getFontSizeP(std::string fontResource);
	static float getFontSizeSmall(std::string fontResource);

	static std::string getPixelFont();
	static std::string getMainFont();
	static std::string getCodingFont();

	LocalizedString* localizedString;
	FontStyle fontStyle;
	FontSize fontSize;
	std::function<void()> typeWriterFinishedCallback;

	static const std::string ScheduleKeyTypeWriterEffect;
	static const float DefaultTypeSpeed;
};
