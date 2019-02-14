#pragma once

#include "Scenes/Hexus/Menus/ChapterSelect/HexusChapterPreview.h"

class HexusChapterPreviewObelisk : public HexusChapterPreview
{
public:
	static HexusChapterPreviewObelisk* create();

	static const std::string SaveKeyChapterName;

protected:
	HexusChapterPreviewObelisk();
	~HexusChapterPreviewObelisk();

private:
	typedef HexusChapterPreview super;
	void initializePositions() override;
};
