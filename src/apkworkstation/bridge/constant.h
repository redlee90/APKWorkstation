#ifndef APKSTUDIO_BRIDGE_CONSTANT_H
#define APKSTUDIO_BRIDGE_CONSTANT_H

#define APPLICATION_NAME "APKWorkstation"
#define EDITOR_BACKGROUND "#FFFFFF"
#define EDITOR_FOREGROUND "#333333"
#define EDITOR_HIGHLIGHT "#DCF5FF"
#define EDITOR_LINE "#999999"
#define EDITOR_SELECTION "#666666"
#define EDITOR_SIDEBAR "#DEDEDE"
#define EDITOR_TRIGGER 2

#define FORMAT_TIMESTAMP "MM-dd-yyyy hh:mm:ss"

#define PATH_COMPLETION ":/res/completion/"
#define PATH_FONT ":/res/font/"
#define PATH_HIGHLIGHT ":/res/highlight/"
#define PATH_ICON ":/res/icon/"
#define PATH_IMAGE ":/res/image/"
#define PATH_LANGUAGE ":/res/language/"

#define PREFERENCE_BINARIES "binaries"
#define PREFERENCE_HEAP "heap"
#define PREFERENCE_HEAP_DEFAULT 128
#define PREFERENCE_ROOT "root"
#define PREFERENCE_TEXT "text"
#define PREFERENCE_VERBOSE "verbose"
#define REGEX_ACCESS "(?<path>.*)\\.(accdb|accde|accdr|accdt)"
#define REGEX_APK "(?<path>.*)\\.apk"
#define REGEX_GETPROP "^\\[(?<key>[^]]+)\\]\\:\\s*\\[(?<value>.*)\\]$"
#define REGEX_FILENAME "^[A-Za-z0-9\\-\\._\\s]+$"
#define REGEX_IMAGE "(?<path>.*)\\.(?<extension>jpg|jpeg|png|tiff)"
#define REGEX_PROJECT "^[A-Za-z0-9.\\s\\-]+$"
#define REGEX_TAG "^[A-Za-z0-9_]+$"
#define ROLE_PATH 997
#define ROLE_STRUCT 998
#define ROLE_TYPE 999

#endif // APKSTUDIO_BRIDGE_CONSTANT_H
