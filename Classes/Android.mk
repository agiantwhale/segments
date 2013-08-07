LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos_game_common

LOCAL_MODULE_FILENAME := libgamecommon

LOCAL_SRC_FILES := \
AppDelegate.cpp \
ArrowNode.cpp \
GameLayer.cpp \
GameScene.cpp \
Global.cpp \
HudLayer.cpp \
LoseMenuLayer.cpp \
LoseScene.cpp \
MainMenuLayer.cpp \
MenuScene.cpp \
PieceNode.cpp \
PolygonNode.cpp \
Rig.cpp \
RippleNode.cpp \
ScoreMenuLayer.cpp \
ScoreScene.cpp \
SettingsScene.cpp \
triangulate.cpp

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../libs/rapidjson/include/rapidjson

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)

include $(BUILD_STATIC_LIBRARY)

$(call import-module,CocosDenshion/android)
$(call import-module,cocos2dx)
$(call import-module,extensions)
