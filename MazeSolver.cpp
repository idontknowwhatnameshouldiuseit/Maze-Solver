#include "MazeSolver.h"
#include <fstream>
#include <stdexcept>

//constructor: hard-coded maze from an array of strings and i copy each row into the dynamically allocated 2D array
//padding with spaces if the string is shorter than cols
MazeSolver::MazeSolver(int r, int c, const std::string mazeData[])
    : rows(r), cols(c) {
    maze = new char* [rows];
    for (int i = 0; i < rows; ++i) {
        maze[i] = new char[cols + 1];
        std::string line = mazeData[i];
        while (line.length() < static_cast<std::string::size_type>(cols))
            line += ' ';
        if (line.length() > static_cast<std::string::size_type>(cols))
            line.resize(cols);
        for (int j = 0; j < cols; ++j)
            maze[i][j] = line[j];
        maze[i][cols] = '\0';
    }
}

//destructor
MazeSolver::~MazeSolver() {
    for (int i = 0; i < rows; ++i)
        delete[] maze[i];
    delete[] maze;
}

//find the start adn target
bool MazeSolver::findStartAndTarget() {
    bool foundStart = false, foundTarget = false;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (maze[r][c] == 's') {
                start = { r, c };
                foundStart = true;
            }
            else if (maze[r][c] == 't') {
                target = { r, c };
                foundTarget = true;
            }
        }
    }
    return foundStart && foundTarget;
}

//I use this function to check all four directions around the current position 
//the order is strictly up right down left a cell is considered "walkable" only if it is not a wall '#' not visited '.' not a dead-end 'x' and not the start 's' 
//all valid moves are stored in the passed LinkedList reference
void MazeSolver::getPossibleMoves(const Position& pos, LinkedList<Position>& moves) {
    moves.clear();
    int dr[] = { -1, 0, 1, 0 };
    int dc[] = { 0, 1, 0, -1 };

    for (int i = 0; i < 4; ++i) {
        int nr = pos.row + dr[i];
        int nc = pos.col + dc[i];
        if (nr < 0 || nr >= rows || nc < 0 || nc >= cols)
            continue;
        char cell = maze[nr][nc];
        if (cell != '#' && cell != '.' && cell != 'x' && cell != 's') {
            moves.push_back({ nr, nc });
        }
    }
}

//print list
void MazeSolver::printMoves(const LinkedList<Position>& moves, std::ostream& os) {
    os << "{ ";
    bool first = true;
    moves.forEach([&](const Position& p) {
        if (!first) os << ", ";
        os << "(" << p.row << "," << p.col << ")";
        first = false;
        });
    os << " }";
}
//take out
void MazeSolver::printVisit(const Position& pos, const LinkedList<Position>& moves) {
    std::cout << "Visit (" << pos.row << "," << pos.col << ") => ";
    printMoves(moves);
    std::cout << std::endl;
}
//deposit
void MazeSolver::printNextMove(const Position& pos, const LinkedList<Position>& moves) {
    std::cout << "Next move (" << pos.row << "," << pos.col << "), updated list: ";
    printMoves(moves);
    std::cout << std::endl;
}
//skip
void MazeSolver::printRevisit(const Position& pos, const LinkedList<Position>& moves) {
    std::cout << "Re-visit (" << pos.row << "," << pos.col << ") => ";
    printMoves(moves);
    std::cout << std::endl;
}

//print maze
void MazeSolver::printMaze() const {
    for (int c = 0; c < cols; ++c)
        std::cout << c;
    std::cout << std::endl;

    for (int r = 0; r < rows; ++r) {
        std::cout << r;
        for (int c = 0; c < cols; ++c)
            std::cout << maze[r][c];
        std::cout << std::endl;
    }
}

//initialization of the starting node
bool MazeSolver::solve() {
    VisitedNode startNode;
    startNode.pos = start;
    getPossibleMoves(start, startNode.moves);
    stack.push(startNode);
    printVisit(start, startNode.moves);

    while (!stack.isEmpty()) {
        VisitedNode& current = stack.top();//If the stack is not empty, continue the search.

        if (current.pos == target) {//examine
            std::cout << "Visit (" << current.pos.row << "," << current.pos.col << ") => Goal!" << std::endl;
            return true;
        }

        if (!current.moves.isEmpty()) {
            //find
            Position next = current.moves.pop_front();
            printNextMove(next, current.moves);

            //mark the current node as a path (excluding the starting point).
            if (!(current.pos == start)) {
                maze[current.pos.row][current.pos.col] = '.';
            }

            //create newnode
            VisitedNode newNode;
            newNode.pos = next;
            getPossibleMoves(next, newNode.moves);
            stack.push(newNode);
            printVisit(newNode.pos, newNode.moves);
        }
        else {
            //dead end
            if (!(current.pos == start)) {
                maze[current.pos.row][current.pos.col] = 'x';
            }

            //Pop up the current dead-end
            stack.pop();

            if (!stack.isEmpty()) {
                VisitedNode& previous = stack.top();
                std::cout << "No possible move, backtrack to ("
                    << previous.pos.row << "," << previous.pos.col << ")" << std::endl;
                printRevisit(previous.pos, previous.moves);
            }
            else {
                std::cout << "No possible move, cannot backtrack anymore" << std::endl;
                std::cout << "No solution" << std::endl;
                return false;
            }
        }
    }
    return false;
}