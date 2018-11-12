#pragma once
#include "cocos2d.h"

#include "Engine/UI/Controls/MenuSprite.h"
#include "Menus/Minigames/Hexus/ChapterSelect/HexusChapterPreview.h"
#include "Resources.h"

using namespace cocos2d;

class HexusChapterPreviewMech : public HexusChapterPreview
{
public:
	static HexusChapterPreviewMech * create();

	static const std::string stringKeyChapterName;

protected:
	HexusChapterPreviewMech();
	~HexusChapterPreviewMech();

private:
	void initializePositions() override;
};
