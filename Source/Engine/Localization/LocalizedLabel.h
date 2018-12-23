#pragma once
#include <string>

#include "cocos/2d/CCLabel.h"

class LocalizedString;

class LocalizedLabel : public cocos2d::Label
{
public:
	enum class FontSize
	{
		H1,
		H2,
		H3,
		P,
		Small,
	};

	static LocalizedLabel* create();

private:
	LocalizedLabel();
	~LocalizedLabel();

	void onLocaleChange(std::string newString);

	LocalizedString* localizedString;
};
