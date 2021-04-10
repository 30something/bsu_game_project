#pragma once

#include <vector>
#include <utility>
#include <QString>

namespace map_data {

static const std::vector<QString> json_filepaths{
    {":resources/Jsons/map_1_data.json"},
    {":resources/Jsons/map_2_data.json"},
    {":resources/Jsons/map_3_data.json"}
};

static const std::vector<QString> finish_lines_filepaths{
    {":resources/images/map_data/finish_map_1.txt"},
    {":resources/images/map_data/finish_map_2.txt"},
    {":resources/images/map_data/finish_map_3.txt"}
};

static const std::vector<QString> image_filepaths{
    {":resources/images/maps/map_1.jpg"},
    {":resources/images/maps/map_2.jpg"},
    {":resources/images/maps/map_3.jpg"}
};

}  // namespace map_data
