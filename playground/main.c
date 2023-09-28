#include <stdio.h>

#define ROWS 13
#define COLS 28

// Define directions for neighboring cells
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int is_valid(int x, int y) {
    // Check if the coordinates (x, y) are within the map boundaries
    return x >= 0 && x < ROWS && y >= 0 && y < COLS;
}

int flood_fill(int x, int y, int map[ROWS][COLS]) {
    if (!is_valid(x, y)) {
        return 0;
    }

    if (map[x][y] == 1) {
        return 1;  // We've reached a wall, so it's surrounded
    }

    if (map[x][y] == 2) {
        return 0;  // We've already visited this cell
    }

    // Mark the current cell as visited
    map[x][y] = 2;

    // Check the neighboring cells in all four directions
    int surrounded = 1;

    for (int i = 0; i < 4; i++) {
        surrounded = surrounded && flood_fill(x + dx[i], y + dy[i], map);
    }

    return surrounded;
}

int is_surrounded_by_walls(int map[ROWS][COLS]) {
    int start_x = 0, start_y = 0;  // You can change these coordinates to your desired starting point

    return flood_fill(start_x, start_y, map);
}

int main() {
    int map[ROWS][COLS] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        // Add more rows of your map here
    };

    int surrounded = is_surrounded_by_walls(map);

    if (surrounded) {
        printf("The map and empty spaces are surrounded by walls.\n");
    } else {
        printf("The map and empty spaces are not surrounded by walls.\n");
    }

    return 0;
}
