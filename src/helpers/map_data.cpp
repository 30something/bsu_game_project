#include "src/helpers/map_data.h"

map_data::JsonFilePaths::JsonFilePaths() {
  QFileInfoList list = QDir(":resources/Jsons").entryInfoList();
  for (const auto& file : list) {
    file_paths.push_back(file.filePath());
  }
}

map_data::ImageFilePaths::ImageFilePaths() {
  QFileInfoList map_list = QDir(":resources/images/maps").entryInfoList();
  for (const auto& file : map_list) {
    maps_file_paths.push_back(file.filePath());
  }
  QFileInfoList minimap_list =
      QDir(":resources/images/maps/minimaps").entryInfoList();
  for (const auto& file : minimap_list) {
    minimaps_file_paths.push_back(file.filePath());
  }
}
