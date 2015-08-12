#Generated by VisualGDB (http://visualgdb.com)
#DO NOT EDIT THIS FILE MANUALLY UNLESS YOU ABSOLUTELY NEED TO
#USE VISUALGDB PROJECT PROPERTIES DIALOG INSTEAD

BINARYDIR := Release

#Toolchain
CC := C:/SysGCC/raspberry/bin/arm-linux-gnueabihf-gcc.exe
CXX := C:/SysGCC/raspberry/bin/arm-linux-gnueabihf-g++.exe
LD := $(CXX)
AR := C:/SysGCC/raspberry/bin/arm-linux-gnueabihf-ar.exe
OBJCOPY := C:/SysGCC/raspberry/bin/arm-linux-gnueabihf-objcopy.exe

#Additional flags
PREPROCESSOR_MACROS := NDEBUG RELEASE __GCC_HAVE_SYNC_COMPARE_AND_SWAP_1 __GCC_HAVE_SYNC_COMPARE_AND_SWAP_2 __GCC_HAVE_SYNC_COMPARE_AND_SWAP_4 __GCC_HAVE_SYNC_COMPARE_AND_SWAP_1 __GCC_HAVE_SYNC_COMPARE_AND_SWAP_8
INCLUDE_DIRS := include ../libraries/live555/live_media/liveMedia/include ../libraries/live555/live_media/groupsock/include ../libraries/live555/live_media/BasicUsageEnvironment/include ../libraries/live555/live_media/UsageEnvironment/include ../libuvxx/include
LIBRARY_DIRS := 
LIBRARY_NAMES := 
ADDITIONAL_LINKER_INPUTS := 
MACOS_FRAMEWORKS := 
LINUX_PACKAGES := 

CFLAGS := -s -ffunction-sections -O3 -Wall -Wno-unused-parameter -Wextra -fno-common -pthread -fexceptions -fnon-call-exceptions -D_NO_ASYNCRTIMP -Wno-unknown-pragmas  -fexceptions -fnon-call-exceptions -fno-common -march=armv7-a -mtune=cortex-a8 -mfpu=neon
CXXFLAGS := -s -ffunction-sections -O3 -std=c++1y -Wall -Wno-unused-parameter -Wextra -fno-common -pthread -fexceptions -fnon-call-exceptions -D_NO_ASYNCRTIMP -Wno-unknown-pragmas  -fexceptions -fnon-call-exceptions -fno-common -march=armv7-a -mtune=cortex-a8 -mfpu=neon
ASFLAGS := 
LDFLAGS := -Wl,-gc-sections -s
COMMONFLAGS := 
LINKER_SCRIPT := 

START_GROUP := -Wl,--start-group
END_GROUP := -Wl,--end-group

#Additional options detected from testing the toolchain
USE_DEL_TO_CLEAN := 1
CP_NOT_AVAILABLE := 1
IS_LINUX_PROJECT := 1
