//
//  TGTools.h
//  yajnavalkya
//
//  Created by cipher on 08.09.2023.
//

#ifndef TGTools_h
#define TGTools_h

#include <stdio.h>
#include <time.h>
#include <stdarg.h>
#include <string>

namespace spcTelega {

enum TGToolsVidyaType {
    TGTOOLS_VIDYA_INFO,
    TGTOOLS_VIDYA_WARNING,
    TGTOOLS_VIDYA_ERROR
};

class TGTools {
public:
    static std::string parse(const std::string& startMark, const std::string& endMark, const std::string& textToParse);
    static void waitFor(const time_t seconds);
    static void vidyaInfo(const char* format, ...);
    static void vidyaError(const char* format, ...);
    static void vidyaWarning(const char* format, ...);
    static void save(const std::string& filename, const char *data, const size_t dataSize);

private:
    static void vidya(const TGToolsVidyaType type, const char* format, va_list args);
};

};

#endif /* TGTools_h */
