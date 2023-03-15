

#define _USE_MATH_DEFINES
#include <cmath>

#include "GUI.h"
#include "position.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <tuple>

/***********************************************
* Callback
* This function runs every frame after all of
* the other OpenGL callback functions defined
* elsewhere.
***********************************************/
void callback4(void* p)
{
    std::vector<std::tuple<Position, int>>* pts = (std::vector<std::tuple<Position, int>>*) p;
    double dtime = GUI::camera.getdTime();

    // If the up key is pressed.
    if (GUI::isUp())
    {
        rotate(0.000000001 * dtime, true, false, false);
        //GUI::camera.ProcessKeyboard(FORWARD, dtime);
        std::cout << "Up" << std::endl;
    }
    // If the down key is pressed.
    if (GUI::isDown())
    {
        rotate(-0.000000001 * dtime, true, false, false);
        //GUI::camera.ProcessKeyboard(BACKWARD, dtime);
        std::cout << "Down" << std::endl;
    }
    // If the right key is pressed.
    if (GUI::isRight())
    {
        rotate(0.000000001 * dtime, false, true, false);
        //GUI::camera.ProcessKeyboard(RIGHT, dtime);
        std::cout << "Right" << std::endl;
    }
    // If the left key is pressed.
    if (GUI::isLeft())
    {
        rotate(-0.000000001 * dtime, false, true, false);
        //GUI::camera.ProcessKeyboard(LEFT, dtime);
        std::cout << "Left" << std::endl;
    }
    // If the space key is pressed.
    if (GUI::isSpace())
    {
        //rotate(1.0, false, false, true);
        std::cout << "Space " << std::endl;
    }
    drawAxis(-128, -128, -128);
    drawPoints(*pts, -128, -128, -128);
    //drawSphere(Position(0, 0, 0), 128);
}


std::vector<std::tuple<Position, int>> parseClusters(const char* filename)
{
    std::ifstream file(filename);
    std::vector<std::tuple<Position, int>> result;
    std::string line;
    int x, y, z, radius;
    double score;

    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            std::stringstream lineStream(line);
            std::string cell;

            std::getline(lineStream, cell, ',');
            x = stoi(cell);
            std::getline(lineStream, cell, ',');
            y = stoi(cell);
            std::getline(lineStream, cell, ',');
            z = stoi(cell);
            std::getline(lineStream, cell, ',');
            score = stod(cell);
            std::getline(lineStream, cell, ',');
            radius = stoi(cell);

            Position pos(x, y, z);
            result.push_back(std::tuple<Position, int>(pos, radius));
        }
    }
    else
    {
        std::cout << "file not open" << std::endl;
    }
    return result;
}


std::vector<std::tuple<Position, int>> parsePixels(const char* filename)
{
    std::ifstream file(filename);
    std::vector<std::tuple<Position, int>> result;
    std::vector<int> pxls;
    std::string line;
    int x, y, z;

    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            std::stringstream lineStream(line);
            std::string cell;

            while (std::getline(lineStream, cell, ','))
                pxls.push_back(stoi(cell));

            Position pos(pxls[0], pxls[1], pxls[2]);
            result.push_back(std::tuple<Position, int>(pos, 5));
            pxls = std::vector<int>();
        }
    }
    return result;
}


/***********************************************
* Main
* This is the main function. It the first code
* executed in the program.
***********************************************/
#ifdef _win32
#include <windows.h>
int winapi winmain(
    _in_ hinstance hinstance,
    _in_opt_ hinstance hprevinstance,
    _in_ pstr pcmdline,
    _in_ int ncmdshow)
#else // !_win32
int main(int argc, char** argv)
#endif // !_WIN32
{
    // Define the scaling of the game.
    Position extent(512.0, 512.0, 512.0);
    //Position extent(1024.0, 1024.0, 1024.0);

    // Initialize the GUI
    GUI gui(argc, argv, "game", extent);

    std::vector<std::tuple<Position, int>> pixels = parsePixels("pixels.csv");
    std::vector<std::tuple<Position, int>> clusters = parseClusters("clusters.csv");
    
    pixels.insert(pixels.end(), clusters.begin(), clusters.end());

    gui.run(callback4, &pixels);
}