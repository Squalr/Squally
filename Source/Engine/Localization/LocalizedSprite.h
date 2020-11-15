#pragma once
#include <string>
#include <functional>

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedSprite : public SmartNode
{
public:
	static LocalizedSprite* create(std::string resourceEn);

	cocos2d::LanguageType getOverrideLanguage();
	void setOverrideLanguage(cocos2d::LanguageType overrideLanguage);

protected:
	LocalizedSprite(std::string resourceEn);
	virtual ~LocalizedSprite();

	void onEnter() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;

	void updateSprite();

	cocos2d::Sprite* localizedSprite;
	std::string resourceBase;
};
