<?xml version="1.0" encoding="UTF-8"?>
<data version="1.0">
    <struct type="Settings">
        <key>fileFormatVersion</key>
        <int>1</int>
        <key>variation</key>
        <string>main</string>
        <key>verbose</key>
        <false/>
        <key>autoSDSettings</key>
        <array>
            <struct type="AutoSDSettings">
                <key>scale</key>
                <double>0.5</double>
                <key>extension</key>
                <string>/HD/</string>
                <key>acceptFractionalValues</key>
                <false/>
                <key>maxTextureSize</key>
                <QSize>
                    <key>width</key>
                    <int>2048</int>
                    <key>height</key>
                    <int>2048</int>
                </QSize>
            </struct>
            <struct type="AutoSDSettings">
                <key>scale</key>
                <double>0.25</double>
                <key>extension</key>
                <string>/SD/</string>
                <key>acceptFractionalValues</key>
                <false/>
                <key>maxTextureSize</key>
                <QSize>
                    <key>width</key>
                    <int>1024</int>
                    <key>height</key>
                    <int>1024</int>
                </QSize>
            </struct>
        </array>
        <key>allowRotation</key>
        <true/>
        <key>quiet</key>
        <false/>
        <key>premultiplyAlpha</key>
        <false/>
        <key>shapeDebug</key>
        <false/>
        <key>dpi</key>
        <uint>72</uint>
        <key>dataFormat</key>
        <string>cocos2d</string>
        <key>textureFileName</key>
        <filename>../segment/Resources/HDR/Graphics.pvr</filename>
        <key>flipPVR</key>
        <false/>
        <key>ditherType</key>
        <enum type="SettingsBase::DitherType">NearestNeighbour</enum>
        <key>backgroundColor</key>
        <uint>0</uint>
        <key>libGdx</key>
        <struct type="LibGDX">
            <key>filtering</key>
            <struct type="LibGDXFiltering">
                <key>x</key>
                <enum type="LibGDXFiltering::Filtering">Linear</enum>
                <key>y</key>
                <enum type="LibGDXFiltering::Filtering">Linear</enum>
            </struct>
        </struct>
        <key>shapePadding</key>
        <uint>8</uint>
        <key>jpgQuality</key>
        <uint>80</uint>
        <key>pngOptimizationLevel</key>
        <uint>0</uint>
        <key>textureSubPath</key>
        <string></string>
        <key>textureFormat</key>
        <enum type="SettingsBase::TextureFormat">pvr2</enum>
        <key>borderPadding</key>
        <uint>8</uint>
        <key>maxTextureSize</key>
        <QSize>
            <key>width</key>
            <int>2048</int>
            <key>height</key>
            <int>2048</int>
        </QSize>
        <key>fixedTextureSize</key>
        <QSize>
            <key>width</key>
            <int>-1</int>
            <key>height</key>
            <int>-1</int>
        </QSize>
        <key>reduceBorderArtifacts</key>
        <true/>
        <key>algorithmSettings</key>
        <struct type="AlgorithmSettings">
            <key>algorithm</key>
            <enum type="AlgorithmSettings::AlgorithmId">MaxRects</enum>
            <key>freeSizeMode</key>
            <enum type="AlgorithmSettings::AlgorithmFreeSizeMode">Best</enum>
            <key>sizeConstraints</key>
            <enum type="AlgorithmSettings::SizeConstraints">POT</enum>
            <key>forceSquared</key>
            <false/>
            <key>forceWordAligned</key>
            <false/>
            <key>maxRects</key>
            <struct type="AlgorithmMaxRectsSettings">
                <key>heuristic</key>
                <enum type="AlgorithmMaxRectsSettings::Heuristic">Best</enum>
            </struct>
            <key>basic</key>
            <struct type="AlgorithmBasicSettings">
                <key>sortBy</key>
                <enum type="AlgorithmBasicSettings::SortBy">Best</enum>
                <key>order</key>
                <enum type="AlgorithmBasicSettings::Order">Ascending</enum>
            </struct>
        </struct>
        <key>andEngine</key>
        <struct type="AndEngine">
            <key>minFilter</key>
            <enum type="AndEngine::MinFilter">Linear</enum>
            <key>packageName</key>
            <string>Texture</string>
            <key>javaFileName</key>
            <filename>../segment/Resources/HDR/Graphics.java</filename>
            <key>wrap</key>
            <struct type="AndEngineWrap">
                <key>s</key>
                <enum type="AndEngineWrap::Wrap">Clamp</enum>
                <key>t</key>
                <enum type="AndEngineWrap::Wrap">Clamp</enum>
            </struct>
            <key>magFilter</key>
            <enum type="AndEngine::MagFilter">MagLinear</enum>
        </struct>
        <key>dataFileName</key>
        <filename>../segment/Resources/HDR/Graphics.plist</filename>
        <key>multiPack</key>
        <false/>
        <key>mainExtension</key>
        <string>/HDR/</string>
        <key>forceIdenticalLayout</key>
        <false/>
        <key>outputFormat</key>
        <enum type="SettingsBase::OutputFormat">RGBA8888</enum>
        <key>contentProtection</key>
        <struct type="ContentProtection">
            <key>key</key>
            <string></string>
        </struct>
        <key>autoAliasEnabled</key>
        <true/>
        <key>trimSpriteNames</key>
        <false/>
        <key>globalSpriteSettings</key>
        <struct type="SpriteSettings">
            <key>scale</key>
            <double>1</double>
            <key>scaleMode</key>
            <enum type="ScaleMode">Smooth</enum>
            <key>innerPadding</key>
            <uint>0</uint>
            <key>extrude</key>
            <uint>0</uint>
            <key>trimThreshold</key>
            <uint>1</uint>
            <key>trimMode</key>
            <enum type="SpriteSettings::TrimMode">Trim</enum>
            <key>heuristicMask</key>
            <false/>
        </struct>
        <key>fileList</key>
        <array>
            <filename>Export/button_pressed.png</filename>
            <filename>Export/button.png</filename>
            <filename>Export/logo.png</filename>
            <filename>Export/window_button.png</filename>
            <filename>Export/pause.png</filename>
            <filename>Export/timer.png</filename>
            <filename>Export/exit.png</filename>
            <filename>Export/next.png</filename>
            <filename>Export/reload.png</filename>
            <filename>Export/cut.png</filename>
            <filename>Export/board.png</filename>
        </array>
        <key>ignoreFileList</key>
        <array/>
        <key>replaceList</key>
        <array/>
        <key>ignoredWarnings</key>
        <array/>
        <key>commonDivisorX</key>
        <uint>1</uint>
        <key>commonDivisorY</key>
        <uint>1</uint>
    </struct>
</data>
