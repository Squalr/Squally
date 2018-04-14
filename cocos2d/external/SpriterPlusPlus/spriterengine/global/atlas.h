#ifndef ATLAS_H
#define ATLAS_H

#include <vector>
#include <string>

#include "../global/global.h"

namespace SpriterEngine
{
	struct atlasframedata {
                atlasframedata(point initialFrameSize = point(), point initialFramePosition = point(), point initialSourceSize = point(),
                               point initialSpriteSourceSize = point(), point initialSpriteSourcePosition = point(),bool initialRotated = false, bool initialTrimmed = false) :
                        frameSize(initialFrameSize), framePosition(initialFramePosition), sourceSize(initialSourceSize),
                        spriteSourceSize(initialSpriteSourceSize), spriteSourcePosition(initialSpriteSourcePosition), rotated(initialRotated), trimmed(initialTrimmed)
		{
                }
		point frameSize;
		point framePosition;
		point sourceSize;
                point spriteSourceSize;
                point spriteSourcePosition;
		bool rotated;
                bool trimmed;
	};

        struct atlasdata
        {
                atlasdata(real initialX = 0, real initialY = 0, real initialW = 0, real initialH = 0, real initialOW = 0, real initialOH = 0, real initialXoff = 0, real initialYoff = 0, bool initialRotated = false, bool initialActive = false) :
                        x(initialX),
                        y(initialY),
                        w(initialW),
                        h(initialH),
                        ow(initialOW),
                        oh(initialOH),
                        xoff(initialXoff),
                        yoff(initialYoff),
                        rotated(initialRotated),
                        active(initialActive)
                {
                }

                real x;
                real y;
                real w;
                real h;
                real ow;
                real oh;
                real xoff;
                real yoff;
                bool rotated;
                bool active;
        };
}

#endif // ATLAS_H
