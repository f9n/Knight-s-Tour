#include <stdio.h>

// Keep in mind that this method not compatible with all terminals
#define clear() printf("\033[H\033[J")

#define SIZE 8

void displayChessBoard(const int[][SIZE]);
void sayWhereIsKnight(int, int);
void displayMovement(void);

int main() {
  int matrix[SIZE][SIZE] = {0};
  int x_coordinate_knight, y_coordinate_knight;
  int vertical_move[8] = {2, 1, -1, -2, -2, -1, 1, 2};
  int horizantal_move[8] = {-1, -2, -2, -1, 1, 2, 2, 1};

  printf("Right Now, Where are your horse?In order of x and y: ");
  scanf("%d%d", &x_coordinate_knight, &y_coordinate_knight);
  matrix[x_coordinate_knight][y_coordinate_knight]++;
  int movement;

  for (int i = 1; i < 64; i++) {
    while (1) {
      printf("\nWhich move will you select, And if you see all move, you write "
             "99 :");
      scanf("%d", &movement);
      if (movement == 99) {
        displayChessBoard(matrix);
        sayWhereIsKnight(x_coordinate_knight, y_coordinate_knight);
        displayMovement();
        continue;
      } else if (movement >= 0 && movement < 8) {
        int y = y_coordinate_knight + vertical_move[movement];
        int x = x_coordinate_knight + horizantal_move[movement];
        if (x < 8 && x >= 0 && y < 8 && y >= 0) {
          printf("Okey...");
          if (matrix[x][y] == 1) {
            printf("But Horse has been exist beforetime");
            continue;
          }
          matrix[x][y]++;
          x_coordinate_knight = x;
          y_coordinate_knight = y;
          ;
          break;
        } else {
          printf("Board 8-8 !");
        }
      } else {
        printf("Please Entry number between 0-7");
      }
    }
  }
  printf("Well done, Game End!!!");
}

void sayWhereIsKnight(int x, int y) {
  printf("\nKnight's  X: %d - Y: %d\n", x, y);
}

void displayChessBoard(const int board[SIZE][SIZE]) {
  clear();
  printf("\n********Chess Board********\n\n");
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      printf("%3d%s", board[i][j], (j == SIZE - 1) ? "\n" : "");
    }
  }
}

void displayMovement(void) {
  printf("\n******Display Movement********\n");
  printf("0. Movement: 2 East + 1 North\n");
  printf("1. Movement: 1 East + 2 North\n");
  printf("2. Movement: 1 West + 2 North\n");
  printf("3. Movement: 2 West + 1 North\n");
  printf("4. Movement: 2 West + 1 South\n");
  printf("5. Movement: 1 West + 2 South\n");
  printf("6. Movement: 1 East + 2 South\n");
  printf("7. Movement: 2 East + 1 South\n");
}
