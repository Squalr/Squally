#pragma once

#include "Scenes/Hexus/Menus/ChapterSelect/HexusChapterPreview.h"

class HexusChapterPreviewRuins : public HexusChapterPreview
{
public:
	static HexusChapterPreviewRuins* create();

	static const std::string SaveKeyChapterName;

protected:
	HexusChapterPreviewRuins();
	~HexusChapterPreviewRuins();

private:
	typedef HexusChapterPreview super;
	void initializePositions() override;
};
