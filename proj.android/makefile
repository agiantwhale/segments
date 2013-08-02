all:
     ./build_native.sh
     ant -Dsdk.dir=/Users/iljae/AndroidSDK debug
run:
     adb -d uninstall com.freesoda99.segment
     adb -d install bin/segment-debug.apk
     adb -d logcat | grep cocos2d
clean:
     rm -rf libs/
     rm -rf obj/
     rm -rf bin/*
     rm -rf gen/
     rm -rf assets/*