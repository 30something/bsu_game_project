#include "src/helpers/map_data.h"

map_data::JsonFilePaths::JsonFilePaths() {
//<<<<<<< HEAD
//  QFileInfoList list = QDir(":resources/Jsons/").entryInfoList();
    QFileInfoList list = {QFileInfo(":resources/Jsons/map1_data.json"),
                          QFileInfo(":resources/Jsons/map2_data.json"),
                          QFileInfo(":resources/Jsons/map3_data.json"),
                          QFileInfo(":resources/Jsons/map4_data.json"),
                          QFileInfo(":resources/Jsons/map5_data.json"),
                          QFileInfo(":resources/Jsons/map6_data.json"),
                          QFileInfo(":resources/Jsons/map7_data.json")};
    for (const auto& file : list) {
        file_paths.push_back(file.filePath());
    }
}

map_data::ImageFilePaths::ImageFilePaths() {
//  QFileInfoList map_list = QDir(":resources/images/maps/").entryInfoList();
    QFileInfoList map_list = {QFileInfo(":resources/images/maps/map1.jpg"),
                              QFileInfo(":resources/images/maps/map2.jpg"),
                              QFileInfo(":resources/images/maps/map3.jpg"),
                              QFileInfo(":resources/images/maps/map4.jpg"),
                              QFileInfo(":resources/images/maps/map5.jpg"),
                              QFileInfo(":resources/images/maps/map6.jpg"),
                              QFileInfo(":resources/images/maps/map7.jpg")};

    for (const auto& file : map_list) {
        maps_file_paths.push_back(file.filePath());
    }
//  QFileInfoList minimap_list =
//      QDir(":resources/images/maps/minimaps/").entryInfoList();

    QFileInfoList minimap_list = {QFileInfo(":resources/images/maps/minimaps/minimap1.jpg"),
                                  QFileInfo(":resources/images/maps/minimaps/minimap2.jpg"),
                                  QFileInfo(":resources/images/maps/minimaps/minimap3.jpg"),
                                  QFileInfo(":resources/images/maps/minimaps/minimap4.jpg"),
                                  QFileInfo(":resources/images/maps/minimaps/minimap5.jpg"),
                                  QFileInfo(":resources/images/maps/minimaps/minimap6.jpg"),
                                  QFileInfo(":resources/images/maps/minimaps/minimap7.jpg")};
    for (const auto& file : minimap_list) {
        minimaps_file_paths.push_back(file.filePath());
    }
}
//
//=======
//  QFileInfoList list = QDir(":resources/Jsons").entryInfoList();
//  for (const auto& file : list) {
//    file_paths.push_back(file.filePath());
//  }
//}
//
//map_data::ImageFilePaths::ImageFilePaths() {
//  QFileInfoList map_list = QDir(":resources/images/maps").entryInfoList();
//  for (const auto& file : map_list) {
//    maps_file_paths.push_back(file.filePath());
//  }
//  QFileInfoList minimap_list =
//      QDir(":resources/images/maps/minimaps").entryInfoList();
//  for (const auto& file : minimap_list) {
//    minimaps_file_paths.push_back(file.filePath());
//  }
//}
//>>>>>>> dev
