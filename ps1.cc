#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "ps1_lib.h"

ABSL_FLAG(std::vector<std::string>, workspace_path, {},
          "Paths to known/special directories.\n"
          "The last directory name in this path will always be displayed and "
          "will be shown in the title bar.");
ABSL_FLAG(std::string, prefix, "[",
          "Fixed path of the prompt that appears before the path.");
ABSL_FLAG(std::string, suffix, "]$ ",
          "Fixed path of the prompt that appears after the path.");
ABSL_FLAG(std::string, pwd, "",
          "Manual override for the path for testing purposes.");
ABSL_FLAG(int, max_length, 40,
          "How many characters wide the prompt should be at a maximum.");

int main(int argc, char *argv[]) {
  absl::ParseCommandLine(argc, argv);
  std::string pwd = absl::GetFlag(FLAGS_pwd);
  if (pwd.empty()) {
    pwd = std::getenv("PWD");
  }

  std::cout << GetPs1(pwd, std::getenv("HOME"), absl::GetFlag(FLAGS_prefix),
                      absl::GetFlag(FLAGS_suffix),
                      absl::GetFlag(FLAGS_max_length),
                      absl::GetFlag(FLAGS_workspace_path));
  return 0;
}
