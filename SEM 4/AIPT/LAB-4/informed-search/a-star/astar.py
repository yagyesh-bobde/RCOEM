import heapq

def astar(start_state, goal_state):
    open_list = []
    closed_set = set()

    start_node = (start_state, None, 0, manhattan_distance(start_state, goal_state))
    heapq.heappush(open_list, (start_node[2] + start_node[3], id(start_node), start_node))

    while open_list:
        _, _, current_node = heapq.heappop(open_list)

        if current_node[0] == goal_state:
            path = []
            while current_node:
                path.append(current_node[0])
                current_node = current_node[1]
            return path[::-1]

        closed_set.add(current_node[0])

        for successor_state, step_cost in successors(current_node[0]):
            if successor_state in closed_set:
                continue

            g = current_node[2] + step_cost
            h = manhattan_distance(successor_state, goal_state)
            new_node = (successor_state, current_node, g, h)
            heapq.heappush(open_list, (g + h, id(new_node), new_node))

    return None  # No path found

def manhattan_distance(state, goal_state):
    distance = 0
    for i in range(3):
        for j in range(3):
            if state[i][j] != goal_state[i][j]:
                x, y = divmod(state[i][j] - 1, 3)
                distance += abs(x - i) + abs(y - j)
    return distance

def successors(state):
    successors = []
    x, y = find_blank(state)
    for dx, dy in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
        new_x, new_y = x + dx, y + dy
        if 0 <= new_x < 3 and 0 <= new_y < 3:
            new_state = [list(row) for row in state]
            new_state[x][y], new_state[new_x][new_y] = new_state[new_x][new_y], new_state[x][y]
            successors.append((tuple(map(tuple, new_state)), 1))  # Assuming cost for each step is 1
    return successors

def find_blank(state):
    for i in range(3):
        for j in range(3):
            if state[i][j] == 0:
                return i, j

def print_solution(path):
    if path:
        print("Steps to reach the goal:")
        for i, state in enumerate(path):
            print(f"Step {i}:")
            for row in state:
                print(" ".join(map(str, row)))
            print()
    else:
        print("No solution found.")

# Example puzzle
start_state = (
    (1, 2, 3),
    (4, 5, 6),
    (0, 7, 8)
)
goal_state = (
    (1, 2, 3),
    (4, 5, 6),
    (7, 8, 0)
)

path = astar(start_state, goal_state)
print_solution(path)
