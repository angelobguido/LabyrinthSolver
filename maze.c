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
        printf("ACHEI\n");
        trace_back(matrix, rows, columns, initial_position, final_position);
    }else{
        printf("NUM ACHEI NAUM\n");
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
    matrix[final_position.y][final_position.x] = 1;
    _trace_back(matrix, rows, columns, final_position.x+1, final_position.y, value-1);
    _trace_back(matrix, rows, columns, final_position.x-1, final_position.y, value-1);
    _trace_back(matrix, rows, columns, final_position.x, final_position.y+1, value-1);
    _trace_back(matrix, rows, columns, final_position.x, final_position.y-1, value-1);
}

void _trace_back(int**matrix, int rows, int columns, int position_x, int position_y, int value){
    if(position_x<0||position_x>=columns||position_y<0||position_y>=rows){
        return;
    }
    if(matrix[position_y][position_x]!=value){
        return;
    }
    if(matrix[position_y][position_x]==1){
        return;
    }

    matrix[position_y][position_x] = 1;

    _trace_back(matrix, rows, columns, position_x+1, position_y, value-1);
    _trace_back(matrix, rows, columns, position_x-1, position_y, value-1);
    _trace_back(matrix, rows, columns, position_x, position_y+1, value-1);
    _trace_back(matrix, rows, columns, position_x, position_y-1, value-1);
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
                default: matrix[i][j] = 0; break;
            }
        }
    }
}