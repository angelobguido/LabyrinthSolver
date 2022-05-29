#ifndef MAZE_H
#define MAZE_H

#define ABS(x) (((x)>=0)?(x):(-(x)))

typedef struct{
    int x;
    int y;
}POSITION;
typedef struct cell{
    POSITION graph_position;
    struct cell* previous_graph;
}CELL;

void solve_maze(int**matrix, int rows, int columns);

void find_position(int**matrix, int rows, int columns, int value, POSITION*position);

void _find_path(int**matrix, int rows, int columns, int initial_position_x, int initial_position_y, POSITION final_position, int value, int*flag);

int find_path(int**matrix, int rows, int columns, POSITION initial_position, POSITION final_position);

void order_positions(POSITION reference_position, POSITION*positions);

void trace_back(int**matrix, int rows, int columns, POSITION initial_position, POSITION final_position);

void _trace_back(int**matrix, int rows, int columns, int position_x, int position_y, int value);

void clean_map(int**matrix, int rows, int columns);

int**create_random_maze(int rows, int columns);

void _create_random_maze(int**maze, int rows, int columns, CELL*actual_graph, int*visited_cells, int max_number_of_cells);

int**initialize_maze(int rows, int columns);

POSITION*find_positions(int**maze, int rows, int columns, POSITION actual_position, int*vector_length);

int is_valid_position(int**maze, int rows, int columns, POSITION reference_position);

void destroyWall(int**maze, int rows, int columns, POSITION initial_position, POSITION final_position);

#endif