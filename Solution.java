
import java.util.Arrays;
import java.util.LinkedList;

public class Solution {

    private static final record Point(int row, int column, int removedObstacles){}
    int rows;
    int columns;
    private static final int[][] moves = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    public int minimumObstacles(int[][] matrix) {
        rows = matrix.length;
        columns = matrix[0].length;
        return findPathWithMinObstaclesBy01BreadthFirstSearch(matrix);
    }

    private int findPathWithMinObstaclesBy01BreadthFirstSearch(int[][] matrix) {
        LinkedList<Point> queue = new LinkedList<>();
        queue.add(new Point(0, 0, matrix[0][0]));

        int[][] minRemovedObstacles = new int[rows][columns];
        for (int r = 0; r < rows; ++r) {
            Arrays.fill(minRemovedObstacles[r], Integer.MAX_VALUE);
        }
        minRemovedObstacles[0][0] = 0;

        while (!queue.isEmpty()) {

            Point current = queue.poll();
            if (current.row == rows - 1 && current.column == columns - 1) {
                break;
            }

            for (int[] move : moves) {
                int nextRow = current.row + move[0];
                int nextColumn = current.column + move[1];

                if (isInMatrix(nextRow, nextColumn) && minRemovedObstacles[nextRow][nextColumn] > current.removedObstacles + matrix[nextRow][nextColumn]) {
                    Point next = new Point(nextRow, nextColumn, current.removedObstacles + matrix[nextRow][nextColumn]);
                    minRemovedObstacles[nextRow][nextColumn] = next.removedObstacles;

                    if (matrix[nextRow][nextColumn] == 0) {
                        queue.addFirst(next);
                    } else {
                        queue.addLast(next);
                    }
                }
            }
        }
        return minRemovedObstacles[rows - 1][columns - 1];
    }

    private boolean isInMatrix(int row, int column) {
        return row >= 0 && row < rows && column >= 0 && column < columns;
    }
}
