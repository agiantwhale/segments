all:
	./build_native.sh
	ant -Dsdk.dir=/Users/iljaelee/Android/android-sdk-macosx debug
run:
	/Users/iljaelee/Android/android-sdk-macosx/platform-tools/adb -d uninstall com.freesoda99.segment
	/Users/iljaelee/Android/android-sdk-macosx/platform-tools/adb -d install bin/segment-debug.apk
	/Users/iljaelee/Android/android-sdk-macosx/platform-tools/adb shell am start -n com.freesoda99.segment/com.freesoda99.segment.segment
	/Users/iljaelee/Android/android-sdk-macosx/platform-tools/adb -d logcat | grep cocos2d
clean:
	rm -rf libs/
	rm -rf obj/
	rm -rf bin/*
	rm -rf gen/
	rm -rf assets/*