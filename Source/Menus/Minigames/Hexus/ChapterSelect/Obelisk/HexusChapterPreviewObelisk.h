#pragma once
#include <string>

#include "Menus/Minigames/Hexus/ChapterSelect/HexusChapterPreview.h"

class HexusChapterPreviewObelisk : public HexusChapterPreview
{
public:
	static HexusChapterPreviewObelisk* create();

	static const std::string SaveKeyChapterName;

protected:
	HexusChapterPreviewObelisk();
	~HexusChapterPreviewObelisk();

private:
	void initializePositions() override;
};
