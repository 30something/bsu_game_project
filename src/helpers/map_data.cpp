#include "src/helpers/map_data.h"

map_data::JsonFilePaths::JsonFilePaths() {
  QFileInfoList list = QDir(":resources/Jsons").entryInfoList();
  for (const auto& file : list) {
    file_paths.push_back(file.filePath());
  }
}

map_data::ImageFilePaths::ImageFilePaths() {
  QFileInfoList list = QDir(":resources/images/maps").entryInfoList();
  for (const auto& file : list) {
    file_paths.push_back(file.filePath());
  }
}
