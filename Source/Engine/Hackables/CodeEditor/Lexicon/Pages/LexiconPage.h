#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class DrawNode;
}

class LexiconPage : public SmartNode
{
public:
	enum class PageType
	{
		Left,
		Right,
		Full
	};

	static const cocos2d::Size TotalPageSize;
	static const cocos2d::Size PageMargin;
	static const cocos2d::Size PageSize;
	static const cocos2d::Vec2 ChapterMarkerLocation;
	static const cocos2d::Vec2 ChapterLocation;

protected:
	LexiconPage(std::string pageIdentifier, PageType pageType);
	~LexiconPage();
	
	void onEnter() override;
	void initializeListeners() override;
	void onDeveloperModeEnable() override;
	void onDeveloperModeDisable() override;
	
	static const cocos2d::Color4B TextColor;

private:
	typedef SmartNode super;

	cocos2d::DrawNode* debugDrawNode;
	std::string pageIdentifier;
	PageType pageType;
};
