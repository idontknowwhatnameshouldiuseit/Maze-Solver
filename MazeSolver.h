#ifndef MAZESOLVER_H
#define MAZESOLVER_H

#include <string>
#include <iostream>
#include "LinkedList.h"
#include "Stack.h"

struct Position {
    int row, col;
    bool operator==(const Position& other) const {
        return row == other.row && col == other.col;
    }
};

struct VisitedNode {
    Position pos;
    LinkedList<Position> moves;
};

class MazeSolver {
private:
    char** maze;
    int rows, cols;
    Position start, target;
    Stack<VisitedNode> stack;

    void getPossibleMoves(const Position& pos, LinkedList<Position>& moves);

    //print
    void printMoves(const LinkedList<Position>& moves, std::ostream& os = std::cout);
    void printVisit(const Position& pos, const LinkedList<Position>& moves);
    void printNextMove(const Position& pos, const LinkedList<Position>& moves);
    void printRevisit(const Position& pos, const LinkedList<Position>& moves);

public:
    //hard-coded
    MazeSolver(int r, int c, const std::string mazeData[]);
    ~MazeSolver();

    bool findStartAndTarget();
    bool solve();
    void printMaze() const;
};

#endif