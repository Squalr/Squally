#pragma once
#include <string>

#include "Menus/Minigames/Hexus/ChapterSelect/HexusChapterPreview.h"

class HexusChapterPreviewJungle : public HexusChapterPreview
{
public:
	static HexusChapterPreviewJungle* create();

	static const std::string SaveKeyChapterName;

protected:
	HexusChapterPreviewJungle();
	~HexusChapterPreviewJungle();

private:
	void initializePositions() override;
};
