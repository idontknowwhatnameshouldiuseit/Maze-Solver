#include <iostream>
#include <string>
#include "MazeSolver.h"

using namespace std;

// test
void runCase(const string& title, int rows, int cols, const string mazeData[]) {
    cout << title << endl;
    MazeSolver solver(rows, cols, mazeData);
    solver.printMaze();
    //can't find send this 
    if (!solver.findStartAndTarget()) {
        cout << "Start or target not found!" << endl;
        return;
    }

    solver.solve();
    solver.printMaze();
    cout << endl;
}

int main() {
    // assignment maze
    const string demo[8] = {
        "s#     ",
        " ## ## ",
        " ## ###",
        "       ",
        "### ###",
        "  #   #",
        "#   #  ",
        "t # ## "
    };

    const string sample1[4] = {
        "#s##",
        "# ##",
        "# ##",
        "#t##"
    };

    const string sample2[4] = {
        "#s##",
        "#   ",
        "# ##",
        "#t##"
    };

    const string sample3[4] = {
        "#s##",
        "# ##",
        "# ##",
        "###t"
    };

    const string sample4[4] = {
        "#s##",
        "# # ",
        "t   ",
        "# # "
    };

    // Execute all test
    runCase("Question Page 1 Demo", 8, 7, demo);
    runCase("Sample 1: Simple (success)", 4, 4, sample1);
    runCase("Sample 2: Simple (backtrack)", 4, 4, sample2);
    runCase("Sample 3: Simple (failed)", 4, 4, sample3);
    runCase("Sample 4: Another example", 4, 4, sample4);

    return 0;
}