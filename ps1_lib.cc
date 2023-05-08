#include "ps1_lib.h"

#include <iostream>
#include <sstream>

#include "absl/strings/match.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_split.h"

namespace {

struct WorkspaceResult {
  std::string basename;
  std::string remaining_path;
};

WorkspaceResult ExtractWorkspace(
    std::string_view pwd, std::string_view home,
    const std::vector<std::string>& workspace_paths) {
  WorkspaceResult result;
  result.remaining_path = pwd;

  for (std::string_view workspace : workspace_paths) {
    workspace = absl::StripSuffix(workspace, "/");
    if (absl::StartsWith(pwd, workspace)) {
      const auto path_parts =
          std::vector<std::string>(absl::StrSplit(workspace, "/"));
      if (path_parts.empty()) {
        continue;
      }
      result.basename = path_parts.back();
      result.remaining_path = pwd.substr(workspace.size());
      break;
    }
  }

  if (result.basename.empty() && absl::StartsWith(pwd, home)) {
    result.basename = "~";
    result.remaining_path = absl::StripPrefix(pwd.substr(home.size()), "/");
  }

  return result;
}

std::string TruncatePath(std::string_view path, int target_length) {
  if (path.size() <= target_length) {
    return std::string(path);
  }

  // last last target-3 characters then add the ... prefix.
  return absl::StrCat("...", path.substr((int)path.size() - target_length + 3));
}

std::string Color(std::string_view code) {
  return absl::StrCat("\033[", code, "m");
}
std::string Color(int code) { return Color(absl::StrCat(code)); }

}  // namespace

std::string GetPs1(std::string_view pwd, std::string_view home,
                   std::string_view prefix, std::string_view suffix,
                   int max_length,
                   const std::vector<std::string>& workspace_paths) {
  std::stringstream out;
  WorkspaceResult workspace = ExtractWorkspace(pwd, home, workspace_paths);

  std::string path_color = "97;1";
  std::string workspace_color = "92;1";
  std::string surround_color = "97;22";
  std::string separator_color = "97;1";

  if (workspace.basename.empty()) {
    out                                     //
        << Color(surround_color) << prefix  //
        << Color(path_color)
        << TruncatePath(workspace.remaining_path,
                        max_length - prefix.size() - suffix.size())  //
        << Color(surround_color) << suffix                           //
        << Color(0);
  } else {
    out                                                  //
        << Color(surround_color) << prefix               //
        << Color(workspace_color) << workspace.basename  //
        << Color(separator_color) << "/"                 //
        << Color(path_color)
        << TruncatePath(workspace.remaining_path,
                        max_length - 1 - workspace.basename.size() -
                            prefix.size() - suffix.size())  //
        << Color(surround_color) << suffix                  //
        << Color(0);
  }

  // TODO: remove
  out << "\n\n";

  return out.str();
}
