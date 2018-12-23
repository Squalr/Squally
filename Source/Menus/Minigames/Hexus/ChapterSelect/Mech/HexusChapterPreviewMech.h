#pragma once
#include <string>

#include "Menus/Minigames/Hexus/ChapterSelect/HexusChapterPreview.h"

class HexusChapterPreviewMech : public HexusChapterPreview
{
public:
	static HexusChapterPreviewMech* create();

	static const std::string SaveKeyChapterName;

protected:
	HexusChapterPreviewMech();
	~HexusChapterPreviewMech();

private:
	void initializePositions() override;
};
