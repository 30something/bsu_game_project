#pragma once

#include <vector>
#include <utility>
#include <QString>

namespace map_data {

// First is data, second is image
static const std::vector<std::pair<QString, QString>> map_filepaths{
    {":resources/images/map_data/map_1.txt",
     ":resources/images/maps/map_1.jpg"},
    {":resources/images/map_data/map_2.txt",
     ":resources/images/maps/map_2.jpg"},
    {":resources/images/map_data/map_3.txt",
     ":resources/images/maps/map_3.jpg"}
};

}  // namespace map_data
