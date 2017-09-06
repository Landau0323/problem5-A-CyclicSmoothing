#include <iostream>
#include "Smoothing.h"

using namespace std;

int main() {
/*    Smoothing path;
    path.smooth_path();
    path.show_change_path();
    path.write_change_path();

    Smoothing path_fixed_naive;
    path_fixed_naive.smooth_path_fixed_naive();
    path_fixed_naive.show_change_path();
    path_fixed_naive.write_change_path();
    */

    Smoothing path_fixed;
    path_fixed.smooth_path_fixed();
    path_fixed.show_change_path();
    path_fixed.write_change_path();

    return 0;
}