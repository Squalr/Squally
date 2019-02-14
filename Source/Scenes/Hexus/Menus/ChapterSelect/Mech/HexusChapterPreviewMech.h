#pragma once

#include "Scenes/Hexus/Menus/ChapterSelect/HexusChapterPreview.h"

class HexusChapterPreviewMech : public HexusChapterPreview
{
public:
	static HexusChapterPreviewMech* create();

	static const std::string SaveKeyChapterName;

protected:
	HexusChapterPreviewMech();
	~HexusChapterPreviewMech();

private:
	typedef HexusChapterPreview super;
	void initializePositions() override;
};
