#pragma once

#include <vector>
#include <utility>
#include <QString>

namespace map_data {

// First is data, second is image
static const std::vector<QString> borders_filepaths{
    {":resources/images/map_data/map_1.txt"},
    {":resources/images/map_data/map_2.txt"},
    {":resources/images/map_data/map_3.txt"},
    {":resources/images/map_data/map_4.txt"},
    {":resources/images/map_data/map_5.txt"},
    {":resources/images/map_data/map_6.txt"}
};

static const std::vector<QString> image_filepaths{
    {":resources/images/maps/map_1.jpg"},
    {":resources/images/maps/map_2.jpg"},
    {":resources/images/maps/map_3.jpg"},
    {":resources/images/maps/map_4.jpg"},
    {":resources/images/maps/map_5.jpg"},
    {":resources/images/maps/map_6.jpg"}
};

}  // namespace map_data
