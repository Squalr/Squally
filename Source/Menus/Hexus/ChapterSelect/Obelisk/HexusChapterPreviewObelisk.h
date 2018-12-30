#pragma once
#include <string>

#include "Menus/Hexus/ChapterSelect/HexusChapterPreview.h"

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
