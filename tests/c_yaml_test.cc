#include <gtest/gtest.h>

#include "PDITools.hpp"

const std::string runToolOn(const std::string &filepath);
// Compare c files to expected yaml
TEST(TestLevel1, CFiles)
{
  auto cfile = runToolOn("../examples/level_1.c");
  auto yamlfile = get_file_contents("../examples/expected/level_1.yml");
  EXPECT_STREQ(cfile.c_str(), yamlfile.c_str());
}