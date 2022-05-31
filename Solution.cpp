
#include <array>
#include <queue>
#include <vector>
using namespace std;

struct Point {
    
    int row{};
    int column{};
    int removedObstacles{};
    
    Point(int row, int column, int removedObstacles) : row {row}, column {column}, removedObstacles {removedObstacles}{}

    Point() = default;
    virtual ~Point() = default; //virtual: no derived structs but for the sake of good practice.

    Point(const Point& point) = default;
    Point& operator=(const Point& point) = default;

    Point(Point&& point) noexcept = default;
    Point& operator=(Point&& point) noexcept = default;
};

class Solution {
    
    size_t rows;
    size_t columns;
    inline static const array<array<int, 2>, 4> moves{ {{-1, 0}, {1, 0}, {0, -1}, {0, 1}} };

public:
    int minimumObstacles(vector<vector<int>>& matrix) {
        rows = matrix.size();
        columns = matrix[0].size();
        return findPathWithMinObstaclesBy01BreadthFirstSearch(matrix);
    }

private:
    int findPathWithMinObstaclesBy01BreadthFirstSearch(const vector<vector<int>>& matrix) {
        deque<Point> queue;
        queue.push_back(Point(0, 0, matrix[0][0]));

        vector<vector<int>> minRemovedObstacles(rows, vector<int>(columns, INT_MAX));
        minRemovedObstacles[0][0] = 0;

        while (!queue.empty()) {

            Point current = queue.front();
            queue.pop_front();

            if (current.row == rows - 1 && current.column == columns - 1) {
                break;
            }

            for (const auto& move : moves) {
                int nextRow = current.row + move[0];
                int nextColumn = current.column + move[1];

                if (isInMatrix(nextRow, nextColumn) && minRemovedObstacles[nextRow][nextColumn] > current.removedObstacles + matrix[nextRow][nextColumn]) {
                    Point next(nextRow, nextColumn, current.removedObstacles + matrix[nextRow][nextColumn]);
                    minRemovedObstacles[nextRow][nextColumn] = next.removedObstacles;

                    if (matrix[nextRow][nextColumn] == 0) {
                        queue.push_front(next);
                    } else {
                        queue.push_back(next);
                    }
                }
            }
        }
        return minRemovedObstacles[rows - 1][columns - 1];
    }

    bool isInMatrix(int row, int column) {
        return row >= 0 && row < rows && column >= 0 && column < columns;
    }
};
