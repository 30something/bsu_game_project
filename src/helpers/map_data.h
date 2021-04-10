#pragma once

#include <vector>
#include <utility>
#include <QString>

namespace map_data {

// First is data, second is image
static const std::vector<QString> borders_filepaths{
    {":resources/images/map_data/map1.txt"},
    {":resources/images/map_data/map2.txt"},
    {":resources/images/map_data/map3.txt"},
    {":resources/images/map_data/map4.txt"},
    {":resources/images/map_data/map5.txt"},
    {":resources/images/map_data/map6.txt"},
    {":resources/images/map_data/map7.txt"}
};

static const std::vector<QString> image_filepaths{
    {":resources/images/maps/map1.jpg"},
    {":resources/images/maps/map2.jpg"},
    {":resources/images/maps/map3.jpg"},
    {":resources/images/maps/map4.jpg"},
    {":resources/images/maps/map5.jpg"},
    {":resources/images/maps/map6.jpg"},
    {":resources/images/maps/map7.jpg"}
};

}  // namespace map_data
