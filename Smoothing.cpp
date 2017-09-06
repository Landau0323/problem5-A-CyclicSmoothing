//
// Created by 研究用 on 2017/08/29.
//

#include <string>
#include <limits>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "Smoothing.h"
#include "parameter.h"

using namespace std;

Smoothing::Smoothing() {
    //set up the original path
    XY original_path(0,0);
    path.push_back(original_path);
    original_path.set_XY(1,0);
    path.push_back(original_path);
    original_path.set_XY(2,0);
    path.push_back(original_path);
    original_path.set_XY(3,0);
    path.push_back(original_path);
    original_path.set_XY(4,0);
    path.push_back(original_path);
    original_path.set_XY(5,0);
    path.push_back(original_path);
    original_path.set_XY(6,0);
    path.push_back(original_path);
    original_path.set_XY(6,1);
    path.push_back(original_path);
    original_path.set_XY(6,2);
    path.push_back(original_path);
    original_path.set_XY(6,3);
    path.push_back(original_path);
    original_path.set_XY(5,3);
    path.push_back(original_path);
    original_path.set_XY(4,3);
    path.push_back(original_path);
    original_path.set_XY(3,3);
    path.push_back(original_path);
    original_path.set_XY(2,3);
    path.push_back(original_path);
    original_path.set_XY(1,3);
    path.push_back(original_path);
    original_path.set_XY(0,3);
    path.push_back(original_path);
    original_path.set_XY(0,2);
    path.push_back(original_path);
    original_path.set_XY(0,1);
    path.push_back(original_path);

    OriginalPath=PreviousPath=path;

    //install fix
    fix.push_back(1);
    fix.push_back(0);
    fix.push_back(0);
    fix.push_back(0);
    fix.push_back(0);
    fix.push_back(0);
    fix.push_back(1);
    fix.push_back(0);
    fix.push_back(0);
    fix.push_back(1);
    fix.push_back(0);
    fix.push_back(0);
    fix.push_back(0);
    fix.push_back(0);
    fix.push_back(0);
    fix.push_back(1);
    fix.push_back(0);
    fix.push_back(0);

}

void Smoothing::show_path() {
    cout<<"show path"<<endl;
    for(int i=0;i<path.size();i++) path[i].show();
}

void Smoothing::smooth_path() {
    cout<<"smoothen path"<<endl;
    while(1){
        for(int i=0;i<path.size();i++){   //exclude the initial and final points
            //minimizing (yi-xi)^2 (close to the original path), minimizing (yi+1+yi-1-2yi)^2 (smooth path)

            int i_next=i+1;
            int i_previous=i-1;
            //cyclic property
            if(i_next==path.size()) i_next=0;
            if(i_previous==-1) i_previous=path.size()-1;

            double path_i_x=PreviousPath[i].getX()+weight_data*(OriginalPath[i].getX()-PreviousPath[i].getX())
                                                   +weight_smooth*(PreviousPath[i_next].getX()+PreviousPath[i_previous].getX()-2*PreviousPath[i].getX());
            double path_i_y=PreviousPath[i].getY()+weight_data*(OriginalPath[i].getY()-PreviousPath[i].getY())
                                                   +weight_smooth*(PreviousPath[i_next].getY()+PreviousPath[i_previous].getY()-2*PreviousPath[i].getY());

            path[i].set_XY(path_i_x,path_i_y);

//path[i].show();
        }

        if(judge_smoothness()==true) break;
        PreviousPath=path;
    }
}

void Smoothing::smooth_path_fixed_naive() {
    cout<<"smoothen path with fixed points (naively)"<<endl;
    while(1){
        for(int i=0;i<path.size();i++){   //exclude the initial and final points
            //minimizing (yi-xi)^2 (close to the original path), minimizing (yi+1+yi-1-2yi)^2 (smooth path)
            if(fix[i]==0) {
                int i_next = i + 1;
                int i_previous = i - 1;
                //cyclic property
                if (i_next == path.size()) i_next = 0;
                if (i_previous == -1) i_previous = path.size() - 1;

                double path_i_x =
                        PreviousPath[i].getX() + weight_data * (OriginalPath[i].getX() - PreviousPath[i].getX())
                        + weight_smooth *
                          (PreviousPath[i_next].getX() + PreviousPath[i_previous].getX() - 2 * PreviousPath[i].getX());
                double path_i_y =
                        PreviousPath[i].getY() + weight_data * (OriginalPath[i].getY() - PreviousPath[i].getY())
                        + weight_smooth *
                          (PreviousPath[i_next].getY() + PreviousPath[i_previous].getY() - 2 * PreviousPath[i].getY());

                path[i].set_XY(path_i_x, path_i_y);
            }
//path[i].show();
        }
        if(judge_smoothness()==true) break;
        PreviousPath=path;
    }
}

void Smoothing::smooth_path_fixed() {
    cout<<"smoothen path with fixed points"<<endl;
    double gamma=weight_smooth*0.5;
    while(1){
        for(int i=0;i<path.size();i++){   //exclude the initial and final points
            //minimizing (yi-xi)^2 (close to the original path), minimizing (yi+1+yi-1-2yi)^2 (smooth path)
            if(fix[i]==0) {
                int i_next = i + 1;
                int i_previous = i - 1;
                //cyclic property
                if (i_next == path.size()) i_next = 0;
                if (i_previous == -1) i_previous = path.size() - 1;
                int i_next2=i+2;
                int i_previous2=i-2;
                //cyclic property
                if(i_next2==path.size()) i_next2 = 0;
                else if(i_next2==path.size()+1) i_next2 = 1;
                if(i_previous2 == -1) i_previous2 = path.size() - 1;
                else if(i_previous2 == -2) i_previous2 = path.size() - 2;

                double path_i_x =
                        PreviousPath[i].getX()
                        + weight_smooth *
                          (PreviousPath[i_next].getX() + PreviousPath[i_previous].getX() - 2 * PreviousPath[i].getX())
                        + gamma * (2*PreviousPath[i_next].getX() + 2*PreviousPath[i_previous].getX()
                           -PreviousPath[i_next2].getX() -PreviousPath[i_previous2].getX()
                           - 2 * PreviousPath[i].getX());
                double path_i_y =
                        PreviousPath[i].getY()
                        + weight_smooth *
                          (PreviousPath[i_next].getY() + PreviousPath[i_previous].getY() - 2 * PreviousPath[i].getY())
                        + gamma * (2*PreviousPath[i_next].getY() + 2*PreviousPath[i_previous].getY()
                                   -PreviousPath[i_next2].getY() -PreviousPath[i_previous2].getY()
                                   - 2 * PreviousPath[i].getY());

                path[i].set_XY(path_i_x, path_i_y);
            }
        }
        if(judge_smoothness()==true) break;
        PreviousPath=path;
    }
}

bool Smoothing::judge_smoothness() {
    double change=0;
    for(int i=0;i<path.size();i++) change+=path[i].distance(PreviousPath[i]);

//cout<<"change:"<<change<<endl;
    if(change<=tolerance) return true;
    else return false;
}

void Smoothing::show_change_path() {
    cout<<"show change of path"<<endl;
    for(int i=0;i<path.size();i++){
        OriginalPath[i].show_nonewline();
        cout<<"->";
        path[i].show_nonewline();
        cout<<endl;
    }
}

void Smoothing::write_change_path() {
    string filename="change_path.dat";
    ofstream fout;  //書き込み用のofstreamを宣言
    fout.open(filename,ios::app);

    cout<<"write results"<<endl;
    for(int i=0;i<path.size();i++) fout<< OriginalPath[i].getX()<<" "<<OriginalPath[i].getY()<<endl;
    fout<<endl<<endl;
    for(int i=0;i<path.size();i++) fout<< path[i].getX()<<" "<<path[i].getY()<<endl;

    fout.close();
}




