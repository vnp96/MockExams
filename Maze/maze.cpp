#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* helper function which allocates a dynamic 2D array */
char **allocate_2D_array(int rows, int columns) {
  char **m = new char *[rows];
  assert(m);
  for (int r=0; r<rows; r++) {
    m[r] = new char[columns];
    assert(m[r]);
  }
  return m;
}

/* helper function which deallocates a dynamic 2D array */
void deallocate_2D_array(char **m, int rows) {
  for (int r=0; r<rows; r++)
    delete [] m[r];
  delete [] m;
}

/* helper function for internal use only which gets the dimensions of a maze */
bool get_maze_dimensions(const char *filename, int &height, int &width) {
  char line[512];
  
  ifstream input(filename);

  height = width = 0;

  input.getline(line,512);  
  while (input) {
    if ( (int) strlen(line) > width)
      width = strlen(line);
    height++;
    input.getline(line,512);  
  }

  if (height > 0)
    return true;
  return false;
}

/* pre-supplied function to load a maze from a file*/
char **load_maze(const char *filename, int &height, int &width) {

  bool success = get_maze_dimensions(filename, height, width);
  
  if (!success)
    return NULL;

  char **m = allocate_2D_array(height, width);
  
  ifstream input(filename);

  char line[512];

  for (int r = 0; r<height; r++) {
    input.getline(line, 512);
    strcpy(m[r], line);
  }
  
  return m;
}

/* pre-supplied function to print a maze */
void print_maze(char **m, int height, int width) {
  cout << setw(4) << " " << " ";
  for (int c=0; c<width; c++)
    if (c && (c % 10) == 0) 
      cout << c/10;
    else
      cout << " ";
  cout << endl;

  cout << setw(4) << " " << " ";
  for (int c=0; c<width; c++)
    cout << (c % 10);
  cout << endl;

  for (int r=0; r<height; r++) {
    cout << setw(4) << r << " "; 
    for (int c=0; c<width; c++)
      cout << m[r][c];
    cout << endl;
  }
}

bool find_marker(char ch, char **maze, int height, int width,
					int& row, int& column){
	for(int r = 0 ; r < height; r++){
		for(int c = 0; c < width; c++){
			if(maze[r][c] == ch){
				row = r;
				column = c;
				return true;
			}
		}

	}

	row = -1;
	column = -1;
	return false;
}

bool valid_path(const char* path){
	const char* valid_char = "NEWS";
	for(const char* ch = path; *ch != '\0'; ch++){
		bool cur_valid = false;
		for(const char* v = valid_char; *v != '\0'; v++)
			if(*v == *ch)
				cur_valid = true;
		if(!cur_valid)
			return false;
	}
	return true;
}

bool move(char ch, int height, int width, int& row, int& column){
	if(ch == 'N'){
		if(row-1 < 0)
			return false;
		row -= 1;
		return true;
	}
	if(ch == 'E'){
		if(column+1 >= width)
			return false;
		column += 1;
		return true;
	}
	if(ch == 'W'){
		if(column-1 < 0)
			return false;
		column -= 1;
		return true;
	}
	if(ch == 'S'){
		if(row+1 >= height)
			return false;
		row += 1;
		return true;
	}

	return false;
}

bool valid_solution(const char* path, char **maze, int height, int width){
	if(!valid_path(path))
		return false;

	int start_row, start_column;
	if(!find_marker('>', maze, height, width, start_row, start_column) )
		return false;

	int exit_row, exit_column;
	if(!find_marker('X', maze, height, width, exit_row, exit_column) )
		return false;

	int row = start_row, column = start_column;
	for(const char* ch = path; *ch != '\0'; ch++){
		if( !move(*ch, height, width, row, column) )
			return false;
		if( !( maze[row][column] == ' ' || maze[row][column] == 'X' || maze[row][column] == '>') )
			return false;
	}

	if( row != exit_row || column != exit_column)
		return false;

	return true;
}

bool get_path(char** maze, int height, int width, int row, int col, 
        int exit_row, int exit_col, char* path, int path_ind){
    if(row == exit_row && col == exit_col){
        maze[row][col] = '#';
        return true;
    }

    if((maze[row][col] == '|' || maze[row][col] == '+' || 
            maze[row][col] == '-' || maze[row][col] == '#') )
        return false;

    char actual_maze_value = maze[row][col];
    maze[row][col] = '#';

    const char* dirs = "NEWS";
    for(const char* ch = dirs; *ch != '\0'; ch++){
        int new_row = row;
        int new_col = col;
        path[path_ind] = *ch;
        if( move(*ch, height, width, new_row, new_col) )
            if( get_path(maze, height, width, new_row, new_col, 
                        exit_row, exit_col, path, path_ind+1) )
                return true;
        path[path_ind] = '\0';
    }

    maze[row][col] = actual_maze_value;
    return false;
}


char* find_path(char** maze, int height, int width, char start, char end){
	char* path = new char[512];

	int start_row, start_column;
	int exit_row, exit_column;
	if( !find_marker(start, maze, height, width, start_row, start_column) ||
            !find_marker(end, maze, height, width, exit_row, exit_column) ||
            !get_path(maze, height, width, start_row, start_column, 
                exit_row, exit_column, path, 0) )
		strcpy(path, "no solution");
	return path;
}



