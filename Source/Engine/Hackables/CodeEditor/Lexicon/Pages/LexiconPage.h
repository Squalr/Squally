#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class DrawNode;
}

class LexiconPage : public SmartNode
{
public:
	static const cocos2d::Size TotalPageSize;
	static const cocos2d::Size PageMargin;
	static const cocos2d::Size PageSize;

protected:
	LexiconPage(std::string pageIdentifier);
	~LexiconPage();
	
	void onEnter() override;
	void initializeListeners() override;
	void onDeveloperModeEnable() override;
	void onDeveloperModeDisable() override;

private:
	typedef SmartNode super;

	cocos2d::DrawNode* debugDrawNode;
	std::string pageIdentifier;
};
