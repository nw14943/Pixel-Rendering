/***********************************************
* Renderer
* --------------------------------------
* Author : Nathan Wood
* --------------------------------------
* Purpose:
* This file holds the Main function and the
* callback. There is also some other functions
* for setup purposes.
***********************************************/

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
void callback(void* p)
{
    std::vector<std::tuple<Position, int>>* pts = (std::vector<std::tuple<Position, int>>*) p;
    double dtime = GUI::getdTime();

    // If the up key is pressed.
    if (GUI::isUp())
    {
        rotate(1.0 * dtime, true, false, false);
        std::cout << "Up" << std::endl;
    }
    // If the down key is pressed.
    if (GUI::isDown())
    {
        rotate(-1.0 * dtime, true, false, false);
        std::cout << "Down" << std::endl;
    }
    // If the right key is pressed.
    if (GUI::isRight())
    {
        rotate(-1.0 * dtime, false, true, false);
        std::cout << "Right" << std::endl;
    }
    // If the left key is pressed.
    if (GUI::isLeft())
    {
        rotate(1.0 * dtime, false, true, false);
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
}


/***********************************************
* Parse Clusters
* This function parses the clusters.csv file.
* It expects the csv to follow the format of
* X, Y, Z, score, radius
* (X, Y, Z can be replaced with R, G, B)
* and returns a vector of tuples of position, size
***********************************************/
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


/***********************************************
* Parse Pixels
* This function parses the pixels.csv file.
* It expects the csv to follow the format of
* X, Y, Z
* (X, Y, Z can be replaced with R, G, B)
* and returns a vector of tuples of position, 5
***********************************************/
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

    // Parse the csv files
    std::vector<std::tuple<Position, int>> pixels = parsePixels("pixels.csv");
    std::vector<std::tuple<Position, int>> clusters = parseClusters("clusters.csv");
    
    // Combine into a single object
    pixels.insert(pixels.end(), clusters.begin(), clusters.end());

    // Start the program loop
    gui.run(callback, &pixels);
}