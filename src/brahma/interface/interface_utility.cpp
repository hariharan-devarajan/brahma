//
// Created by haridev on 8/28/22.
//

#include <brahma/interface/interface_utility.h>

namespace brahma {
void InterfaceUtility::exclude_file(const char *filename,
                                    brahma::InterfaceType interface) {
  auto interface_iter = excluded_filenames.find(interface);
  std::unordered_set<std::string> excludes_files;
  if (interface_iter == excluded_filenames.end()) {
    excludes_files = std::unordered_set<std::string>();
  } else {
    excludes_files = interface_iter->second;
  }
  excludes_files.emplace(filename);
  excluded_filenames.insert_or_assign(interface, excludes_files);
}
void InterfaceUtility::include_file(const char *filename,
                                    brahma::InterfaceType interface) {
  auto interface_iter = excluded_filenames.find(interface);
  if (interface_iter != excluded_filenames.end()) {
    interface_iter->second.erase(filename);
    excluded_filenames.insert_or_assign(interface, interface_iter->second);
  }
}
bool InterfaceUtility::is_traced(const char *filename,
                                 brahma::InterfaceType interface) {
  auto interface_iter = excluded_filenames.find(interface);
  if (interface_iter != excluded_filenames.end()) {
    auto iter = interface_iter->second.find(filename);
    if (iter != interface_iter->second.end()) return false;
  }
  interface_iter = filenames.find(interface);
  if (interface_iter != filenames.end()) {
    auto iter = interface_iter->second.find(filename);
    if (iter != interface_iter->second.end()) return true;
  }
  return false;
}
void InterfaceUtility::track_file(const char *filename,
                                  brahma::InterfaceType interface) {
  auto interface_iter = filenames.find(interface);
  std::unordered_set<std::string> track_files;
  if (interface_iter == filenames.end()) {
    track_files = std::unordered_set<std::string>();
  } else {
    track_files = interface_iter->second;
    filenames.erase(interface_iter);
  }
  track_files.emplace(filename);
  filenames.emplace(interface, track_files);
}
void InterfaceUtility::untrack_file(const char *filename,
                                    brahma::InterfaceType interface) {
  auto interface_iter = filenames.find(interface);
  if (interface_iter != filenames.end()) {
    interface_iter->second.erase(filename);
    filenames.insert_or_assign(interface, interface_iter->second);
  }
}
}  // namespace brahma
