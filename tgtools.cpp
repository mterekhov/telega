//
//  TGTools.cpp
//  yajnavalkya
//
//  Created by cipher on 08.09.2023.
//

#include <stdio.h>
#include "TGTools.h"

namespace spcTelega {

void TGTools::save(const std::string& filename, const char *data, const size_t dataSize) {
    std::string finalFileName = "/Users/cipher/backup/" + filename;
    FILE *fileHandler = fopen(finalFileName.c_str(), "wb");
    fwrite(data, dataSize, 1, fileHandler);
    fclose(fileHandler);
}

void TGTools::waitFor(const time_t seconds) {
    time_t mark = time(NULL);
    while((time(NULL) - mark) < seconds) {
    }
}

std::string TGTools::parse(const std::string& startMark, const std::string& endMark, const std::string& textToParse) {
    auto markStartPosition = textToParse.find(startMark);
    auto markEndPosition = textToParse.find(endMark, markStartPosition);
    if ((markStartPosition == std::string::npos) || (markEndPosition == std::string::npos)) {
        return "";
    }
    return textToParse.substr(markStartPosition + startMark.length(),
                              markEndPosition - markStartPosition - startMark.length());
}

void TGTools::vidyaInfo(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vidya(TGTOOLS_VIDYA_INFO, format, args);
    va_end(args);
}

void TGTools::vidyaError(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vidya(TGTOOLS_VIDYA_ERROR, format, args);
    va_end(args);
}

void TGTools::vidyaWarning(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vidya(TGTOOLS_VIDYA_WARNING, format, args);
    va_end(args);
}

void TGTools::vidya(const TGToolsVidyaType type, const char* format, va_list args) {
#ifdef NDEBUG
    return;
#endif
    time_t rawtime;
    time(&rawtime);
    char timeBuffer[BUFSIZ] = {0};
    char *timeFormat = "%d-%m-%Y %H:%M:%S";
    strftime(timeBuffer, BUFSIZ, timeFormat, localtime(&rawtime));

    std::string newFormat = timeBuffer;
    switch (type) {
        case TGTOOLS_VIDYA_INFO:
            newFormat += " YajnaValkya: ";
            break;
        case TGTOOLS_VIDYA_WARNING:
            newFormat += " YajnaValkya-WARNING: ";
            break;
        case TGTOOLS_VIDYA_ERROR:
            newFormat += " YajnaValkya-ERROR: ";
            break;

        default:
            break;
    }
    newFormat += format;

    vprintf(newFormat.c_str(), args);
}

}

