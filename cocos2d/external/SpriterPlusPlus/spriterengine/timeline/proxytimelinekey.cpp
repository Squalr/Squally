#include "proxytimelinekey.h"

namespace SpriterEngine
{
	ProxyTimelineKey::ProxyTimelineKey(TimeInfo * initialTimeInfo, UniversalObjectInterface * initialObjectInfo, UniversalObjectInterface * initialNextObjectInfo) :
		TimelineKey(initialTimeInfo, initialObjectInfo)
	{
		setNextObjectInfo(initialNextObjectInfo);
	}

	ProxyTimelineKey::~ProxyTimelineKey()
	{
		objectInfo = 0;
	}

}
