#include <Windows.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>

struct timestamp {
    int x;
    int y;
    float time;
};


int main (void){
    HWND clientCheck = FindWindow(0, (LPCSTR)("League of Legends"));
    if (clientCheck == NULL) {
        std::cout <<"Client not Running\n";
        system("pause");
        return 0;
    }
    std::cout << "Waiting for Game start\n";



    HWND leaguecheck;
    bool waiting = true;
    while (waiting == true){
        leaguecheck = FindWindow(0, (LPCSTR)("League of Legends (TM) Client"));
        if (leaguecheck != NULL){
            waiting = false;
            std::cout << "Collecting Data\n";
        }
    }



    bool collectingData = true;
    clock_t timer;
    timer = clock();
    clock_t start_time = timer;
    POINT mousePoint;
    GetCursorPos(&mousePoint);
    timestamp tmp;
    tmp.x = mousePoint.x;
    tmp.y = mousePoint.y;
    tmp.time = (timer - start_time)/CLOCKS_PER_SEC;
    std::vector<timestamp> mousePositionData;
    mousePositionData.push_back(tmp);
    while (collectingData == true){
        if (((clock() - timer)/CLOCKS_PER_SEC)>0.25){
            GetCursorPos(&mousePoint);
            tmp.x = mousePoint.x;
            tmp.y = mousePoint.y;
            tmp.time = (clock() - start_time) / CLOCKS_PER_SEC;
            mousePositionData.push_back(tmp);

            leaguecheck = FindWindow(0, (LPCSTR)("League of Legends (TM) Client"));
            if (leaguecheck == NULL){
                collectingData = false;
            }
            timer = clock();
        }
    }
    std::ofstream file("data.csv");
    file <<"x,y,time\n";
    for (const timestamp &position: mousePositionData){
        file << position.x << "," << position.y << "," << position.time << "\n";
    }
    file.close();
    return 0;
}