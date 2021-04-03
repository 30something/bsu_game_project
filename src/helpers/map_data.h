#pragma once

#include <vector>
#include <utility>
#include <QString>

namespace map_data {

// First is data, second is image
static const std::vector<std::pair<QString, QString>> map_filepaths{
    {":resources/images/map_data/Map_1.txt",
     ":resources/images/maps/Map_1.jpg"},
    {":resources/images/map_data/Map_2.txt",
     ":resources/images/maps/Map_2.jpg"},
    {":resources/images/map_data/Map_3.txt",
     ":resources/images/maps/Map_3.jpg"},
    {":resources/images/map_data/Map_4.txt",
     ":resources/images/maps/Map_4.jpg"}
};

}  // namespace map_data
