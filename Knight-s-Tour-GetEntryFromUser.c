#include <stdio.h>

#define clear() printf("\033[H\033[J")

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

int vertical_move[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int horizontal_move[8] = {-1, -2, -2, -1, 1, 2, 2, 1};

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

struct Knight get_knight_info() {
  struct Knight knight;
  println("Which coordinate do you want to put the knight in?", "white",
          NEW_LINE);
  knight.x = input_as_int("X: ");
  knight.y = input_as_int("Y: ");
  return knight;
}

void move_knight(struct Knight *k, int movement) {
  k->y += vertical_move[movement];
  k->x += horizontal_move[movement];
}

void display_chess_board(const int chess_board[BOARD_SIZE][BOARD_SIZE]) {
  println("\n********Chess Board********\n\n", RED, NEW_LINE);
  for (int i = 0; i < BOARD_SIZE; i++)
    for (int j = 0; j < BOARD_SIZE; j++)
      printf("%3d%s", chess_board[i][j], (j == BOARD_SIZE - 1) ? "\n" : "");
}

void display_movement(void) {
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

int main() {
  int chess_board[BOARD_SIZE][BOARD_SIZE] = {0};
  struct Knight knight = get_knight_info();
  chess_board[knight.x][knight.y]++;

  int movement, y, x;
  for (int i = 1; i < (BOARD_SIZE * BOARD_SIZE); i++) {
    while (1) {
      movement =
          input_as_int("Which movement will you choose? And if you want to see "
                       "all the movements, you should type 99 : ");
      if (movement == 99) {
        display_chess_board(chess_board);
        print_knight_position(knight);
        display_movement();
        continue;
      } else if (movement >= 0 && movement < BOARD_SIZE) {
        y = knight.y + vertical_move[movement];
        x = knight.x + horizontal_move[movement];
        if (is_valid_coordinate(x, y)) {
          printf("Okey...\n");
          if (chess_board[x][y] == 1) {
            printf("The knight got there a while ago.\n");
            continue;
          }
          chess_board[x][y]++;
          knight.x = x;
          knight.y = y;
          break;
        } else {
          printf("Board 8-8 !\n");
        }
      } else {
        printf("Please enter a number between 0-7.\n");
      }
    }
  }
  printf("Well done, Game End!!!");
}
