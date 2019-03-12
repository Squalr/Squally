#pragma once

#include "Scenes/Hexus/Menus/ChapterSelect/HexusChapterPreview.h"

class HexusChapterPreviewUnderflowRuins : public HexusChapterPreview
{
public:
	static HexusChapterPreviewUnderflowRuins* create();

	static const std::string SaveKeyChapterName;

protected:
	HexusChapterPreviewUnderflowRuins();
	~HexusChapterPreviewUnderflowRuins();

private:
	typedef HexusChapterPreview super;
	void initializePositions() override;
};
