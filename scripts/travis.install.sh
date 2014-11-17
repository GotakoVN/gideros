brew update
brew install jpeg
brew install libpng
brew install freetype
brew install glew
brew install wget
brew install qt5
brew install wine
brew install ant

export QT=/usr/local/Cellar/qt5/5.3.2
export IOS_SDK=8.0
export ANDROID_NDK=~/android-ndk-r10c
export ANDROID_HOME=~/android-sdk-macosx

cd scripts

bash installqscintilla.sh
bash qt5/buildqtlibs.sh
bash qt5/buildplugins.sh
bash qt5/cleanqt.sh
bash qt5/buildqt.sh

bash cleanioslibs.sh
bash buildioslibs.sh

bash makejar.sh
bash buildandroidlibs.sh
bash buildandroidso.sh
bash buildandroidplugins.sh

wine cmd /c qt5\\buildqtlibs.bat
wine cmd /c qt5\\buildplugins.bat
wine cmd /c qt5\\cleanqt.bat
wine cmd /c qt5\\buildqt.bat

travis setup releases
