//
// Created by xac1k on 6/6/26.
//

#ifndef YEAR_STUDY_WORK_TASK_H
#define YEAR_STUDY_WORK_TASK_H
#include <vector>
#include <crow/json.h>

#include "../../GJO/New/Point.h"

using Task = std::pair<Point3d, Point3d>;
using Tasks = std::vector<Task>;

class TaskParser {
public:
    Tasks Parse(const crow::json::rvalue& source);
};

#endif //YEAR_STUDY_WORK_TASK_H