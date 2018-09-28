#pragma once
#include "cocos2d.h"
#include "Resources.h"

#include "Engine/UI/Controls/MenuSprite.h"
#include "Scenes/Menus/Minigames/Hexus/ChapterSelect/HexusChapterPreview.h"

using namespace cocos2d;

class HexusChapterPreviewJungle : public HexusChapterPreview
{
public:
	static HexusChapterPreviewJungle * create();

	static const std::string stringKeyChapterName;

protected:
	HexusChapterPreviewJungle();
	~HexusChapterPreviewJungle();

private:
	void initializePositions() override;
};
