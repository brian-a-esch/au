#include "au/AuDecoder.h"

#include "AuRecordHandler.h"
#include "JsonOutputHandler.h"

#include "gtest/gtest.h"

#include <filesystem>

namespace fs = std::filesystem;

namespace au {

TEST(AuDecoderTestCases, doesntCrashOnCases) {
  for (auto &p: fs::directory_iterator("cases")) {
    SCOPED_TRACE(std::string("Processing ") + p.path().c_str());
    try {
      AuDecoder auDecoder(p.path());
      Dictionary dictionary;
      JsonOutputHandler valueHandler;
      AuRecordHandler<JsonOutputHandler> recordHandler(dictionary,
                                                       valueHandler);
      auDecoder.decode(recordHandler, false);
    } catch (const std::exception &) {}
  }
}

}
