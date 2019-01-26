#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Sleep() function cross platform
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

// https://stackoverflow.com/questions/17271576/clear-screen-in-c-and-c-on-unix-based-system
// Keep in mind that this method not compatible with all
// terminals
#define clear() printf("\033[H\033[J")

// https://stackoverflow.com/questions/3585846/color-text-in-terminal-applications-in-unix
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN "\x1B[36m"
#define WHITE "\x1B[37m"
#define RESET "\x1B[0m"

#define NEW_LINE 1
#define NOT_NEW_LINE 0

#define BOARD_SIZE 8

void println(char message[], char color[], int with_new_line) {
  printf("%s%s%s", color, message, RESET);
  if (with_new_line == NEW_LINE) {
    printf("\n");
  }
}

int input_as_int(char message[]) {
  int temp_input;
  println(message, WHITE, NOT_NEW_LINE);
  scanf("%d", &temp_input);
  return temp_input;
}

struct Knight {
  int x;
  int y;
};

void print_knight_position(struct Knight k) {
  printf("\n Knight's  X: %d - Y: %d\n", k.x, k.y);
}

int is_valid_coordinate(int x, int y) {
  return x < BOARD_SIZE && x >= 0 && y < BOARD_SIZE && y >= 0;
}

int min(int[]);
void display_accessibility(const int[BOARD_SIZE][BOARD_SIZE]);
void display_chess_board(const int[BOARD_SIZE][BOARD_SIZE]);
void decrease_accessibility(const int[BOARD_SIZE][BOARD_SIZE],
                            const int[BOARD_SIZE], const int[BOARD_SIZE],
                            int[BOARD_SIZE][BOARD_SIZE], int, int);

int main() {
  int chess_board[BOARD_SIZE][BOARD_SIZE] = {0};
  int vertical_move[BOARD_SIZE] = {2, 1, -1, -2, -2, -1, 1, 2};
  int horizontal_move[BOARD_SIZE] = {-1, -2, -2, -1, 1, 2, 2, 1};
  int accessibility_rate[BOARD_SIZE] = {0};
  int accessibility[BOARD_SIZE][BOARD_SIZE] = {
      {2, 3, 4, 4, 4, 4, 3, 2}, {3, 4, 6, 6, 6, 6, 4, 3},
      {4, 6, 8, 8, 8, 8, 6, 4}, {4, 6, 8, 8, 8, 8, 6, 4},
      {4, 6, 8, 8, 8, 8, 6, 4}, {4, 6, 8, 8, 8, 8, 6, 4},
      {3, 4, 6, 6, 6, 6, 4, 3}, {2, 3, 4, 4, 4, 4, 3, 2}};
  /*
              North
              (-y)
                |
                |
  West (-x)|----------|(+x)  East
                |
                |
              (+y)
              South
  */
  struct Knight knight;
  println("Right Now, Where are your horse?", "white", NEW_LINE);
  knight.x = input_as_int("X: ");
  knight.y = input_as_int("Y: ");
  chess_board[knight.x][knight.y]++;
  decrease_accessibility(accessibility, chess_board, horizontal_move,
                         vertical_move, knight.x, knight.y);
  int movement, step = 0, temp_cordinate_value;
  while (step < 64) {
    clear();
    display_chess_board(chess_board);
    print_knight_position(knight);
    display_accessibility(accessibility);
    // Select suitable movement(least accessibility and knight is not never
    // exist to there )
    for (int i = 0; i < BOARD_SIZE; i++) {
      movement = i;
      int y = knight.y + vertical_move[movement];
      int x = knight.x + horizontal_move[movement];
      if (is_valid_coordinate(x, y) && (chess_board[x][y] != 1)) {
        accessibility_rate[i] = accessibility[x][y];
      } else {
        accessibility_rate[i] = 10;
      }
    }
    movement = min(accessibility_rate);
    knight.y += vertical_move[movement];
    knight.x += horizontal_move[movement];
    temp_cordinate_value = chess_board[knight.x][knight.y];
    if ((temp_cordinate_value == 1) &&
        (step != (BOARD_SIZE * BOARD_SIZE - 1))) {
      println("Game over!!!", RED, NEW_LINE);
      break;
    }
    decrease_accessibility(chess_board, horizontal_move, vertical_move,
                           accessibility, knight.x, knight.y);
    chess_board[knight.x][knight.y]++;
    step++;
    println("Next Movement: ", YELLOW, NEW_LINE);
    printf("%d\n", movement);
    println("Step: ", MAGENTA, NEW_LINE);
    printf("%d\n", step);
    sleep(1);
  }
  if (step == BOARD_SIZE * BOARD_SIZE) {
    printf("Well done...", CYAN, NEW_LINE);
  } else {
    println("Game End...", BLUE, NEW_LINE);
  }
}

void display_accessibility(const int accessibility[BOARD_SIZE][BOARD_SIZE]) {
  println("\n******Accessibility******\n\n", GREEN, NEW_LINE);
  for (int i = 0; i < BOARD_SIZE; i++)
    for (int j = 0; j < BOARD_SIZE; j++)
      printf("%3d%s", accessibility[i][j], (j == BOARD_SIZE - 1) ? "\n" : "");

  printf("\n");
}

void decrease_accessibility(const int chess_board[BOARD_SIZE][BOARD_SIZE],
                            const int horizontal_move[BOARD_SIZE],
                            const int vertical_move[BOARD_SIZE],
                            int accessibility[BOARD_SIZE][BOARD_SIZE], int x,
                            int y) {
  int movement;
  accessibility[x][y] = 0;
  for (int i = 0; i < BOARD_SIZE; i++) {
    movement = i;
    x += horizontal_move[movement];
    y += vertical_move[movement];
    if (is_valid_coordinate(x, y)) {
      accessibility[x][y]--;
      if (chess_board[x][y] == 1)
        accessibility[x][y] = 0;
    }
    x -= horizontal_move[movement];
    y -= vertical_move[movement];
  }
}

// find Minimum! // array is Accessibility Rate
int min(int array[]) {
  int index = 0;
  for (int i = 1; i < BOARD_SIZE; i++) {
    if (array[index] > array[i]) {
      array[index] = array[i];
      index = i;
    }
  }
  return index;
}

void display_chess_board(const int chess_board[BOARD_SIZE][BOARD_SIZE]) {
  println("\n********Chess Board********\n\n", RED, NEW_LINE);
  for (int i = 0; i < BOARD_SIZE; i++)
    for (int j = 0; j < BOARD_SIZE; j++)
      printf("%3d%s", chess_board[i][j], (j == BOARD_SIZE - 1) ? "\n" : "");
}
