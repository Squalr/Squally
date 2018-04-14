LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := SpriterPlusPlus

LOCAL_MODULE_FILENAME := libspriterplusplus

LOCAL_SRC_FILES := \
spriterengine/timeline/tagtimelineinstance.cpp \
spriterengine/timeline/variabletimelineinstance.cpp \
spriterengine/timeline/timelineinstance.cpp \
spriterengine/timeline/timelinekey.cpp \
spriterengine/timeline/triggertimelineinstance.cpp \
spriterengine/timeline/soundtimelineinstance.cpp \
spriterengine/timeline/proxytimelinekey.cpp \
spriterengine/timeline/timeline.cpp \
spriterengine/global/settings.cpp \
spriterengine/override/imagefile.cpp \
spriterengine/override/soundfile.cpp \
spriterengine/override/spriterfiledocumentwrapper.cpp \
spriterengine/override/objectfactory.cpp \
spriterengine/override/spriterfileattributewrapper.cpp \
spriterengine/override/filefactory.cpp \
spriterengine/override/soundobjectinforeference.cpp \
spriterengine/override/spriterfileelementwrapper.cpp \
spriterengine/override/atlasfile.cpp \
spriterengine/objectref/spriteref.cpp \
spriterengine/objectref/boneref.cpp \
spriterengine/objectref/transformprocessor.cpp \
spriterengine/objectref/entityref.cpp \
spriterengine/objectref/spriterefinstance.cpp \
spriterengine/objectref/entityrefinstance.cpp \
spriterengine/objectref/objectrefinstance.cpp \
spriterengine/objectref/objectref.cpp \
spriterengine/objectref/bonerefinstance.cpp \
spriterengine/variable/variable.cpp \
spriterengine/variable/variablecontainer.cpp \
spriterengine/variable/variableinstancenameandidmap.cpp \
spriterengine/loading/loader.cpp \
spriterengine/loading/loadinghelpers.cpp \
spriterengine/loading/spriterdocumentloader.cpp \
spriterengine/objectinfo/tagobjectinfo.cpp \
spriterengine/objectinfo/soundobjectinfo.cpp \
spriterengine/objectinfo/spriteobjectinfo.cpp \
spriterengine/objectinfo/intvariableinfo.cpp \
spriterengine/objectinfo/taglist.cpp \
spriterengine/objectinfo/stringvariableinforeference.cpp \
spriterengine/objectinfo/entityobjectinfo.cpp \
spriterengine/objectinfo/eventobjectinfo.cpp \
spriterengine/objectinfo/angleinfo.cpp \
spriterengine/objectinfo/pointinstanceinfo.cpp \
spriterengine/objectinfo/boxinstanceinfo.cpp \
spriterengine/objectinfo/boneinstanceinfo.cpp \
spriterengine/objectinfo/universalobjectinterface.cpp \
spriterengine/objectinfo/realvariableinfo.cpp \
spriterengine/objectinfo/triggerobjectinfo.cpp \
spriterengine/objectinfo/pointobjectinfo.cpp \
spriterengine/objectinfo/boneobjectinfo.cpp \
spriterengine/objectinfo/tagobjectinforeference.cpp \
spriterengine/objectinfo/stringvariableinfo.cpp \
spriterengine/objectinfo/boxobjectinfo.cpp \
spriterengine/charactermap/charactermap.cpp \
spriterengine/charactermap/charactermapinstruction.cpp \
spriterengine/model/spritermodel.cpp \
spriterengine/file/file.cpp \
spriterengine/file/filereference.cpp \
spriterengine/entity/object.cpp \
spriterengine/entity/entity.cpp \
spriterengine/entity/entityinstance.cpp \
spriterengine/entity/entityinstancedata.cpp \
spriterengine/animation/mainlinekey.cpp \
spriterengine/animation/animationinstance.cpp \
spriterengine/animation/mainlinekeyinstance.cpp \
spriterengine/animation/animation.cpp \
spriterengine/timeinfo/cubiceasingcurve.cpp \
spriterengine/timeinfo/easingcurveinterface.cpp \
spriterengine/timeinfo/timeinfo.cpp \
spriterengine/timeinfo/instanteasingcurve.cpp \
spriterengine/timeinfo/quarticeasingcurve.cpp \
spriterengine/timeinfo/quadraticeasingcurve.cpp \
spriterengine/timeinfo/beziereasingcurve.cpp \
spriterengine/timeinfo/lineareasingcurve.cpp \
spriterengine/timeinfo/quinticeasingcurve.cpp \

include $(BUILD_STATIC_LIBRARY)
