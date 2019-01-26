#include <stdio.h>
#include <stdlib.h>

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
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define WHT "\x1B[37m"
#define RESET "\x1B[0m"

#define SIZE 8

int min(int[]);
void displayAccessibility(const int[SIZE][SIZE]);
void decreaseAccessibility(int[SIZE][SIZE], const int[SIZE][SIZE],
                           const int[SIZE], const int[SIZE], int, int);
void displayChessBoard(const int[SIZE][SIZE]);
void sayWhereIsKnight(int, int);
void displayMovement(void);

int main() {
  int x_coordinate_knight, y_coordinate_knight;
  int chessBoard[SIZE][SIZE] = {0};
  int vertical_move[SIZE] = {2, 1, -1, -2, -2, -1, 1, 2};
  int horizontal_move[SIZE] = {-1, -2, -2, -1, 1, 2, 2, 1};
  int accessibilityRate[SIZE] = {0};
  int accessibility[SIZE][SIZE] = {
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
  printf("Right Now, Where are your horse?In order of x and y: ");
  scanf("%d%d", &x_coordinate_knight, &y_coordinate_knight);
  chessBoard[x_coordinate_knight][y_coordinate_knight]++;
  decreaseAccessibility(accessibility, chessBoard, horizontal_move,
                        vertical_move, x_coordinate_knight,
                        y_coordinate_knight);
  int movement, step = 0, tempValue;
  while (step < 64) {
    clear();
    displayChessBoard(chessBoard);
    sayWhereIsKnight(x_coordinate_knight, y_coordinate_knight);
    displayAccessibility(accessibility);
    displayMovement();
    // Select suitable movement(least accessibility and knight is not never
    // exist to there )
    for (int i = 0; i < 8; i++) {
      movement = i;
      int y = y_coordinate_knight + vertical_move[movement];
      int x = x_coordinate_knight + horizontal_move[movement];
      if (x < 8 && x >= 0 && y < 8 && y >= 0 && (chessBoard[x][y] != 1)) {
        accessibilityRate[i] = accessibility[x][y];
      } else {
        accessibilityRate[i] = 10;
      }
    }
    movement = min(accessibilityRate);
    y_coordinate_knight += vertical_move[movement];
    x_coordinate_knight += horizontal_move[movement];
    tempValue = chessBoard[x_coordinate_knight][y_coordinate_knight];
    if ((tempValue == 1) && (step != 63)) {
      printf(RED "Game over!!!\n" RESET);
      break;
    }
    decreaseAccessibility(accessibility, chessBoard, horizontal_move,
                          vertical_move, x_coordinate_knight,
                          y_coordinate_knight);
    chessBoard[x_coordinate_knight][y_coordinate_knight]++;
    step++;
    printf(YEL "\t\t\tNext Movement: %d\n" RESET, movement);
    printf(MAG "\t\t\tStep: %d\n" RESET, step);
    sleep(1);
  }
  if (step == 64) {
    printf(CYN "Well done...\n" RESET);
  } else {
    printf("Game End...\n");
  }
}

void displayAccessibility(const int accessibility[SIZE][SIZE]) {
  printf(GRN "\n******Accessibility******\n\n" RESET);
  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j < SIZE; j++)
      printf("%3d%s", accessibility[i][j], (j == SIZE - 1) ? "\n" : "");
}

void decreaseAccessibility(int accessibility[SIZE][SIZE],
                           const int chessBoard[SIZE][SIZE],
                           const int horizontal_move[SIZE],
                           const int vertical_move[SIZE], int x, int y) {
  int movement;
  accessibility[x][y] = 0;
  for (int i = 0; i < 8; i++) {
    movement = i;
    x += horizontal_move[movement];
    y += vertical_move[movement];
    if (x < 8 && x >= 0 && y < 8 && y >= 0) {
      accessibility[x][y]--;
      if (chessBoard[x][y] == 1)
        accessibility[x][y] = 0;
    }
    x -= horizontal_move[movement];
    y -= vertical_move[movement];
  }
}

// find Minimum! // array is Accessibility Rate
int min(int array[]) {
  int index = 0;
  for (int i = 1; i < SIZE; i++) {
    if (array[index] > array[i]) {
      array[index] = array[i];
      index = i;
    }
  }
  return index;
}

void sayWhereIsKnight(int x, int y) {
  printf("\n Knight's  X: %d - Y: %d\n", x, y);
}

void displayChessBoard(const int chessBoard[SIZE][SIZE]) {
  printf(RED "\n********Chess Board********\n\n" RESET);
  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j < SIZE; j++)
      printf("%3d%s", chessBoard[i][j], (j == SIZE - 1) ? "\n" : "");
}

void displayMovement(void) {
  printf(BLU "\n******Display Movement********\n" RESET);
  printf("0. Movement: 2 East + 1 North\n");
  printf("1. Movement: 1 East + 2 North\n");
  printf("2. Movement: 1 West + 2 North\n");
  printf("3. Movement: 2 West + 1 North\n");
  printf("4. Movement: 2 West + 1 South\n");
  printf("5. Movement: 1 West + 2 South\n");
  printf("6. Movement: 1 East + 2 South\n");
  printf("7. Movement: 2 East + 1 South\n");
}
