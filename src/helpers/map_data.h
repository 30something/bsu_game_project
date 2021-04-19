#pragma once

#include <vector>
#include <utility>

#include <QDirIterator>
#include <QFileInfoList>
#include <QString>

namespace map_data {

class JsonFilePaths {
 public:
  std::vector<QString> file_paths;
  JsonFilePaths();
};

static const JsonFilePaths json_file_paths;

class ImageFilePaths {
 public:
  std::vector<QString> file_paths;
  ImageFilePaths();
};

static const ImageFilePaths image_file_paths;

}  // namespace map_data
