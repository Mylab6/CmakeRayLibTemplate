#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

# Define Android SDK and NDK paths
ANDROID_SDK_ROOT="$HOME/Android/Sdk"
ANDROID_NDK_HOME="$ANDROID_SDK_ROOT/ndk-bundle"

# Android Build Settings
ANDROID_ABI="armeabi-v7a"
ANDROID_PLATFORM="android-21"

# Define project directories
PROJECT_DIR=$(pwd)
BUILD_DIR="$PROJECT_DIR/build"

# Step 1: Install Android SDK and NDK
install_android_sdk_ndk() {
    echo "Installing Android SDK and NDK..."

    # Create necessary directories for Android SDK
    mkdir -p $ANDROID_SDK_ROOT/cmdline-tools

    # Download Android SDK command-line tools
    echo "Downloading Android SDK command-line tools..."
    wget https://dl.google.com/android/repository/commandlinetools-linux-7583922_latest.zip -O cmdline-tools.zip

    # Unzip the command-line tools into the cmdline-tools/latest directory
    unzip cmdline-tools.zip -d $ANDROID_SDK_ROOT/cmdline-tools
    mkdir -p $ANDROID_SDK_ROOT/cmdline-tools/latest
    mv $ANDROID_SDK_ROOT/cmdline-tools/cmdline-tools/* $ANDROID_SDK_ROOT/cmdline-tools/latest/
    
    # Set Android SDK environment variables
    export PATH=$ANDROID_SDK_ROOT/cmdline-tools/latest/bin:$ANDROID_SDK_ROOT/platform-tools:$PATH
    
    # Install required components (NDK, platforms, build-tools)
    yes | $ANDROID_SDK_ROOT/cmdline-tools/latest/bin/sdkmanager --sdk_root=$ANDROID_SDK_ROOT --install "platform-tools" "platforms;android-29" "ndk-bundle" "build-tools;29.0.3"
}

# Step 2: Set up environment variables for Android SDK and NDK
setup_android_env() {
    echo "Setting up Android environment variables..."
    export ANDROID_SDK_ROOT=$ANDROID_SDK_ROOT
    export ANDROID_NDK_HOME=$ANDROID_NDK_HOME
    export PATH=$ANDROID_SDK_ROOT/cmdline-tools/latest/bin:$ANDROID_SDK_ROOT/platform-tools:$PATH
}

# Step 3: Configure CMake for Android
configure_cmake_for_android() {
    echo "Configuring CMake for Android..."
    # Ensure the build directory is clean
    rm -rf $BUILD_DIR
    mkdir -p $BUILD_DIR
    cd $BUILD_DIR

    # Run the CMake configuration for Android
    cmake -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK_HOME/build/cmake/android.toolchain.cmake \
          -DANDROID_ABI=$ANDROID_ABI \
          -DANDROID_PLATFORM=$ANDROID_PLATFORM \
          -DCMAKE_BUILD_TYPE=Release \
          $PROJECT_DIR
}

# Step 4: Build APK using Gradle
build_apk() {
    echo "Building APK using Gradle..."
    cd $BUILD_DIR
    ./gradlew assembleDebug
}

# Step 5: Display APK path
display_apk_path() {
    APK_PATH=$(find $BUILD_DIR -name "*-debug.apk")

    if [ -f "$APK_PATH" ]; then
        echo "APK built successfully: $APK_PATH"
    else
        echo "APK build failed."
        exit 1
    fi
}

# Main script execution
install_android_sdk_ndk
setup_android_env
configure_cmake_for_android
build_apk
display_apk_path

echo "Android APK build complete."
