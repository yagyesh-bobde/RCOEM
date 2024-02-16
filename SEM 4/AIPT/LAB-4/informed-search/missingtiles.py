
SIZE = 3

heuristic_values = []

def count_missing_tiles(source, target):
    """
    Count the number of missing tiles between the source and target grids.
    """
    count = 0
    for i in range(SIZE):
        for j in range(SIZE):
            if source[i][j] != target[i][j]:
                count += 1
    return count


def go_up(grid):
    """
    Move the empty tile up in the grid.
    """
    for i in range(SIZE):
        for j in range(SIZE):
            if grid[i][j] == 0 and i > 0:
                grid[i][j], grid[i-1][j] = grid[i-1][j], grid[i][j]
                return grid
    return None

def go_down(grid):
    """
    Move the empty tile down in the grid.
    """
    for i in range(SIZE):
        for j in range(SIZE):
            if grid[i][j] == 0 and i < SIZE-1:
                grid[i][j], grid[i+1][j] = grid[i+1][j], grid[i][j]
                return grid
    return None

def go_left(grid):
    """
    Move the empty tile left in the grid.
    """
    for i in range(SIZE):
        for j in range(SIZE):
            if grid[i][j] == 0 and j > 0:
                grid[i][j], grid[i][j-1] = grid[i][j-1], grid[i][j]
                return grid
    return None

def go_right(grid):
    """
    Move the empty tile right in the grid.
    """
    for i in range(SIZE):
        for j in range(SIZE):
            if grid[i][j] == 0 and j < SIZE-1:
                grid[i][j], grid[i][j+1] = grid[i][j+1], grid[i][j]
                return grid
    return None

source = [[1, 2, 3], [4, 5, 6], [7, 8, 0]]
random_grid = [[1, 2, 3], [7, 8, 0], [4, 5, 6]]

print("Source Array:")
for i in range(SIZE):
    for j in range(SIZE):
        print(source[i][j], end=" ")
    print()

print("\nTarget Array:")
for i in range(SIZE):
    for j in range(SIZE):
        print(random_grid[i][j], end=" ")
    print()

missing_tiles = count_missing_tiles(source, random_grid)
print("\nNumber of missing tiles:", missing_tiles)

while random_grid != source:
    print("\nRandom Grid:")
    for i in range(SIZE):
        for j in range(SIZE):
            print(random_grid[i][j], end=" ")
        print()

    heuristic_values = []
    directions = [go_up, go_down, go_left, go_right]
    for direction in directions:
        new_grid = direction(random_grid)
        if new_grid is not None:
            heuristic = count_missing_tiles(new_grid, source)
            heuristic_values.append((heuristic, new_grid))

    heuristic_values.sort()
    random_grid = heuristic_values[0][1]

print("\nRandom Grid:")
for i in range(SIZE):
    for j in range(SIZE):
        print(random_grid[i][j], end=" ")
    print()
