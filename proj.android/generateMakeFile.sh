#!/bin/bash
echo "Genrating MakeFile in Classes Folder...."
echo ""
echo ""

cd ..
cd Classes
for f in `ls *.cpp`
do
names=("${names[@])}" "$f")
done
echo "LOCAL_PATH := \$(call my-dir)">Android.mk
echo "">>Android.mk
echo "include \$(CLEAR_VARS)">>Android.mk
echo "">>Android.mk
echo "LOCAL_MODULE := cocos_game_common" >> Android.mk
echo "">>Android.mk
echo "LOCAL_MODULE_FILENAME := libgamecommon" >> Android.mk
echo "">>Android.mk
echo "LOCAL_SRC_FILES := \\" >> Android.mk
i=1
length=${#names[@]}
for name in "${names[@])}"
do
if [ "$i" -ne "$length" ];then
echo "$name \\" >> Android.mk
else
echo "$name" >> Android.mk
fi
i=$(($i+1))
done
echo "">>Android.mk
echo "LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static">> Android.mk
echo "LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static">> Android.mk
echo "LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static">> Android.mk
echo "">>Android.mk
echo "LOCAL_EXPORT_C_INCLUDES := \$(LOCAL_PATH)">> Android.mk
echo "">>Android.mk
echo "include \$(BUILD_STATIC_LIBRARY)">> Android.mk
echo "">>Android.mk
echo "\$(call import-module,CocosDenshion/android)">> Android.mk
echo "\$(call import-module,cocos2dx)">> Android.mk
echo "\$(call import-module,extensions)">> Android.mk

echo "Genrating MakeFile in Classes Folder Completed!"
echo ""
echo ""