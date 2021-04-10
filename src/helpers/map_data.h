#pragma once

#include <vector>
#include <utility>
#include <QString>

namespace map_data {

// First is data, second is image
static const std::vector<QString> borders_filepaths{
    {":resources/images/map_data/Map_1.txt"},
    {":resources/images/map_data/Map_2.txt"},
    {":resources/images/map_data/Map_3.txt"},
    {":resources/images/map_data/Map_4.txt"},
    {":resources/images/map_data/Map_5.txt"},
    {":resources/images/map_data/Map_6.txt"},
    {":resources/images/map_data/Map_7.txt"},
};

static const std::vector<QString> image_filepaths{
    {":resources/images/maps/Map_1.jpg"},
    {":resources/images/maps/Map_2.jpg"},
    {":resources/images/maps/Map_3.jpg"},
    {":resources/images/maps/Map_4.jpg"},
    {":resources/images/maps/Map_5.jpg"},
    {":resources/images/maps/Map_6.jpg"},
    {":resources/images/maps/Map_7.jpg"}
};

}  // namespace map_data
