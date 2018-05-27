LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := box2d_static
LOCAL_MODULE_FILENAME := box2d_static
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libbox2d.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/../../include
include $(PREBUILT_STATIC_LIBRARY)
