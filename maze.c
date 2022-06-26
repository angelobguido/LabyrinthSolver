#include <stdlib.h>
#include <stdio.h>
#include "maze.h"

void solve_maze(int**matrix, int rows, int columns){
    POSITION initial_position;
    POSITION final_position;
    find_position(matrix, rows, columns, -1, &initial_position);
    find_position(matrix, rows, columns, -2, &final_position);

    int flag = find_path(matrix, rows, columns, initial_position, final_position);

    if(flag){
        //printf("ACHEI\n");
        trace_back(matrix, rows, columns, initial_position, final_position);
    }else{
        //printf("NUM ACHEI NAUM\n");
    }

    clean_map(matrix, rows, columns);
}

int find_path(int**matrix, int rows, int columns, POSITION initial_position, POSITION final_position){
    int flag = 0;
    _find_path(matrix, rows, columns, initial_position.x, initial_position.y,final_position, 1, &flag);
    return flag;
}

void _find_path(int**matrix, int rows, int columns, int initial_position_x, int initial_position_y, POSITION final_position, int value, int*flag){
    
    if(*flag){
        return;
    }
    if(initial_position_x<0||initial_position_x>=columns||initial_position_y<0||initial_position_y>=rows){
        return;
    }
    if(matrix[initial_position_y][initial_position_x]==-2){
        matrix[initial_position_y][initial_position_x]=value; // Important to trace back.
        *flag=1;
        return;
    }
    if(matrix[initial_position_y][initial_position_x]!=0&&matrix[initial_position_y][initial_position_x]!=-1){
        return;
    }

    matrix[initial_position_y][initial_position_x]=value;
    
    POSITION down = {initial_position_x, initial_position_y+1};
    POSITION up = {initial_position_x, initial_position_y-1};
    POSITION left = {initial_position_x+1, initial_position_y};
    POSITION right = {initial_position_x-1, initial_position_y};
    POSITION positions[4] = {right, left, down, up};
    int i;
    
    order_positions(final_position, positions);
    
    for(i = 0; i < 4; i++){
        _find_path(matrix, rows, columns, positions[i].x, positions[i].y, final_position, value+1, flag);    
    }
}

void order_positions(POSITION reference_position, POSITION*positions){
    POSITION temp;
    int distance, compare_distance, index;
    int i, j;
    for(i = 0; i < 4; i++){
        distance = ABS(reference_position.x-positions[i].x) + ABS(reference_position.y-positions[i].y);
        index = i;
        for(j = i+1; j< 4; j++){
            compare_distance = ABS(reference_position.x-positions[j].x) + ABS(reference_position.y-positions[j].y);
            if(distance>compare_distance){
                index = j;
                distance = compare_distance; 
            }
        }
        temp = positions[index];
        positions[index] = positions[i];
        positions[i] = temp;
    }
}

void find_position(int**matrix, int rows, int columns, int value, POSITION*position){
    int i,j;
    for(i=0; i<rows; i++){
        for(j=0; j<columns; j++){
            if(matrix[i][j]==value){
                position->x = j;
                position->y = i;
                return;
            }
        }
    }
}

void trace_back(int**matrix, int rows, int columns, POSITION initial_position, POSITION final_position){
    int value = matrix[final_position.y][final_position.x];
    int flag = 0;
    matrix[final_position.y][final_position.x] = -2;
    _trace_back(matrix, rows, columns, final_position.x+1, final_position.y, value-1, &flag);
    _trace_back(matrix, rows, columns, final_position.x-1, final_position.y, value-1, &flag);
    _trace_back(matrix, rows, columns, final_position.x, final_position.y+1, value-1, &flag);
    _trace_back(matrix, rows, columns, final_position.x, final_position.y-1, value-1, &flag);
}

void _trace_back(int**matrix, int rows, int columns, int position_x, int position_y, int value, int*flag){
    if(position_x<0||position_x>=columns||position_y<0||position_y>=rows){
        return;
    }
    if(matrix[position_y][position_x]!=value){
        return;
    }
    if(matrix[position_y][position_x]==1&&(*flag)!=1){
        (*flag) = 1;
        matrix[position_y][position_x]=-1;
        return;
    }

    matrix[position_y][position_x] = 2;

    _trace_back(matrix, rows, columns, position_x+1, position_y, value-1, flag);
    _trace_back(matrix, rows, columns, position_x-1, position_y, value-1, flag);
    _trace_back(matrix, rows, columns, position_x, position_y+1, value-1, flag);
    _trace_back(matrix, rows, columns, position_x, position_y-1, value-1, flag);
}

void clean_map(int**matrix, int rows, int columns){
    int i, j, value;
    for(i=0;i<rows;i++){
        for(j=0;j<columns;j++){
            value = matrix[i][j];
            switch(value){
                case -1: break;
                case -2: break;
                case -3: break;
                case 0: break;
                case 1: break;
                case 2: matrix[i][j] = 1; break;
                default: matrix[i][j] = 0; break;
            }
        }
    }
}

//RANDOM MAZE GENERATOR:

int**create_random_maze(int rows, int columns){
    srand(time(NULL));
    int**maze = initialize_maze(rows, columns);
    int visited_cells, max_number_of_cells;
    POSITION graph_position = {0,0};
    CELL root = {graph_position, NULL};

    max_number_of_cells = (rows+1)/2 * (columns+1)/2;
    visited_cells = 0;

    _create_random_maze(maze, rows, columns, &root, &visited_cells, max_number_of_cells);

    clean_map(maze, rows, columns);
    maze[0][0] = -1;
    maze[(rows%2==0)?(rows-2):(rows-1)][(columns%2==0)?(columns-2):(columns-1)] = -2;
    
    return maze;
}

void _create_random_maze(int**maze, int rows, int columns, CELL*actual_graph, int*visited_cells, int max_number_of_cells){
    
    if((*visited_cells)==max_number_of_cells){
        return;
    }
    if(actual_graph==NULL){
        return;
    }

    int position_x = actual_graph->graph_position.x;
    int position_y = actual_graph->graph_position.y;

    if(maze[position_y][position_x]==0){
        maze[position_y][position_x] = -4;
        (*visited_cells)++;
    }

    int length;
    POSITION*next_positions = find_positions(maze, rows, columns, actual_graph->graph_position, &length);
    if(length==0){
        CELL*previous_graph = actual_graph->previous_graph;
        //free(actual_graph); --> This is an issue (There is memory leak)
        _create_random_maze(maze, rows, columns, previous_graph, visited_cells, max_number_of_cells);
        return;
    }
    POSITION new_position = next_positions[rand()%length];
    free(next_positions);
    CELL new_graph = {new_position, actual_graph};
    CELL*new_graph_pointer = (CELL*)malloc(sizeof(CELL));
    destroyWall(maze, rows, columns, actual_graph->graph_position, new_position);
    (*new_graph_pointer) = new_graph;
    _create_random_maze(maze, rows, columns, new_graph_pointer, visited_cells, max_number_of_cells);
    return;

}

void destroyWall(int**maze, int rows, int columns, POSITION initial_position, POSITION final_position){
    int delta_x = (final_position.x - initial_position.x)/2;
    int delta_y = (final_position.y - initial_position.y)/2;

    maze[initial_position.y+delta_y][initial_position.x+delta_x] = -4;
}

int**initialize_maze(int rows, int columns){
    int**maze = (int**)malloc(sizeof(int*)*rows);
    int i, j;
    for(i=0;i<rows;i++){
        maze[i] = (int*)malloc(sizeof(int)*columns);
    }

    for(i=0;i<rows;i++){
        for(j=0;j<columns;j++){
            if((i+1)%2&&(j+1)%2){
                maze[i][j] = 0;
            }else{
                maze[i][j] = -3;
            }
        }
    }

    return maze;

}

POSITION*find_positions(int**matrix, int rows, int columns, POSITION actual_position, int*vector_length){
    POSITION top={actual_position.x, actual_position.y-2}, down={actual_position.x, actual_position.y+2}
    , right={actual_position.x+2, actual_position.y}, left={actual_position.x-2, actual_position.y};
    POSITION all_positions_vector[] = {top, down, right, left};
    
    int i;
    *vector_length = 0;
    POSITION*positions_vector = NULL;

    for(i=0; i<4; i++){
        if(is_valid_position(matrix, rows, columns, all_positions_vector[i])){
            (*vector_length)++;
            positions_vector = (POSITION*)realloc(positions_vector, sizeof(POSITION)*(*vector_length));
            positions_vector[(*vector_length)-1] = all_positions_vector[i];
        }
    }

    return positions_vector;
        
}

int is_valid_position(int**matrix, int rows, int columns, POSITION reference_position){
    int position_x = reference_position.x;
    int position_y = reference_position.y;

    if(position_x>=columns||position_y>=rows||position_x<0||position_y<0){
        return 0;
    }
    if(matrix[position_y][position_x]!=0){
        return 0;
    }
    return 1;
}