#pragma once

#include <vector>
#include <utility>
#include <QString>

namespace map_data {

static const std::vector<QString> borders_filepaths{
    {":resources/images/map_data/map_1.txt"},
    {":resources/images/map_data/map_2.txt"},
    {":resources/images/map_data/map_3.txt"}
};

static const std::vector<QString> image_filepaths{
    {":resources/images/maps/map_1.jpg"},
    {":resources/images/maps/map_2.jpg"},
    {":resources/images/maps/map_3.jpg"}
};

}  // namespace map_data
