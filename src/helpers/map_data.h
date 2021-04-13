#pragma once

#include <vector>
#include <utility>
#include <QString>

namespace map_data {

static const std::vector<QString> json_filepaths{
    {":resources/Jsons/map_1_data.json"},
    {":resources/Jsons/map_2_data.json"},
    {":resources/Jsons/map_3_data.json"},
    {":resources/Jsons/map_4_data.json"},
    {":resources/Jsons/map_5_data.json"},
    {":resources/Jsons/map_6_data.json"},
    {":resources/Jsons/map_7_data.json"},

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
