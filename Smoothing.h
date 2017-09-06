//
// Created by 研究用 on 2017/08/29.
//

#ifndef PROBLEM5_A_CYCLICSMOOTHING_SMOOTHING_H
#define PROBLEM5_A_CYCLICSMOOTHING_SMOOTHING_H

#include <string>
#include <limits>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "XY.h"

using namespace std;


class Smoothing {
private:
    vector<XY> path, OriginalPath,PreviousPath;
    vector<int> fix;

public:
    Smoothing();
    void show_path();
    void show_change_path();
    void write_change_path();
    void smooth_path();
    void smooth_path_fixed_naive();
    void smooth_path_fixed();
    bool judge_smoothness();

};


#endif //PROBLEM5_A_CYCLICSMOOTHING_SMOOTHING_H
