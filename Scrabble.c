#include <stdio.h>
#include <string.h>
#include <stdlib.h>
size_t strlen(const char *s);
#include <time.h>
#include <unistd.h>
#include "Scrabble.h"

// Board is board[y][x]
int board[15][15] = { 0 };


// The point values for different tiles
// TILE_VALS[0] is an empty board square
// TILE_VALS[27] is a blank tile
// TILE_VALS[1] is 'A' tile value
// TILE_VALS[2] is 'B' tile value
// ...
int TILE_VALS[28] = {0, 1, 3,  3, 2,  1, 4,
                     2, 4, 1,  8, 5,  1, 3,
                     1, 1, 3, 10, 1,  1, 1,
                     1, 4, 4,  8, 4, 10, 0};

// DIRECTION is list {dy, dx}
//    where dx is change in x
//    and   dy is change in y
// HOR is horizontal direction
// VER is vertical direction
int HOR[2] = {0, 1};
int VER[2] = {1, 0};

// All the available tiles in the game.
// 1 is an 'A' tile
// 2 is a 'B' tile
// ...
int g_tiles[100] = { 1,  1,  1,  1,  1,  1,  1,  1,  1,  2,
                      2,  3,  3,  4,  4,  4,  4,  5,  5,  5,
                      5,  5,  5,  5,  5,  5,  5,  5,  5,  6,
                      6,  7,  7,  7,  8,  8,  9,  9,  9,  9,
                      9,  9,  9,  9,  9, 10, 11, 12, 12, 12,
                     12, 13, 13, 14, 14, 14, 14, 14, 14, 15,
                     15, 15, 15, 15, 15, 15, 15, 16, 16, 17,
                     18, 18, 18, 18, 18, 18, 19, 19, 19, 19,
                     20, 20, 20, 20, 20, 20, 21, 21, 21, 21,
                     22, 22, 23, 23, 24, 25, 25, 26, 10, 11 };

char SPECIAL_TILES[15][15] =
    // * is double word score
    // @ is tripple word score
    // + is double letter score
    // ~ is tripple letter score
    { { '@', '\0', '\0',  '+', '\0', '\0', '\0',  '@', '\0', '\0', '\0',  '+', '\0', '\0',  '@' }
    , {'\0',  '*', '\0', '\0', '\0',  '~', '\0', '\0', '\0',  '~', '\0', '\0', '\0',  '*', '\0' }
    , {'\0', '\0',  '*', '\0', '\0', '\0',  '+', '\0',  '+', '\0', '\0', '\0',  '*', '\0', '\0' }
    , { '+', '\0', '\0',  '*', '\0', '\0', '\0',  '+', '\0', '\0', '\0',  '*', '\0', '\0',  '+' }
    , {'\0', '\0', '\0', '\0',  '*', '\0', '\0', '\0', '\0', '\0',  '*', '\0', '\0', '\0', '\0' }
    , {'\0',  '~', '\0', '\0', '\0',  '~', '\0', '\0', '\0',  '~', '\0', '\0', '\0',  '~', '\0' }
    , {'\0', '\0',  '+', '\0', '\0', '\0',  '+', '\0',  '+', '\0', '\0', '\0',  '+', '\0', '\0' }
    , { '@', '\0', '\0',  '+', '\0', '\0', '\0',  '*', '\0', '\0', '\0',  '+', '\0', '\0',  '@' }
    , {'\0', '\0',  '+', '\0', '\0', '\0',  '+', '\0',  '+', '\0', '\0', '\0',  '+', '\0', '\0' }
    , {'\0',  '~', '\0', '\0', '\0',  '~', '\0', '\0', '\0',  '~', '\0', '\0', '\0',  '~', '\0' }
    , {'\0', '\0', '\0', '\0',  '*', '\0', '\0', '\0', '\0', '\0',  '*', '\0', '\0', '\0', '\0' }
    , { '+', '\0', '\0',  '*', '\0', '\0', '\0',  '+', '\0', '\0', '\0',  '*', '\0', '\0',  '+' }
    , {'\0', '\0',  '*', '\0', '\0', '\0',  '+', '\0',  '+', '\0', '\0', '\0',  '*', '\0', '\0' }
    , {'\0',  '*', '\0', '\0', '\0',  '~', '\0', '\0', '\0',  '~', '\0', '\0', '\0',  '*', '\0' }
    , { '@', '\0', '\0',  '+', '\0', '\0', '\0',  '@', '\0', '\0', '\0',  '+', '\0', '\0',  '@' }
  };

char *filename = "words_alpha.txt";

int main(void) {
  clear_screen();

  printf("Welcome to ScrabbleC!\n");

  printf("Loading dictionary...\n");
  dict = getNode();
  FILE* fh;
  char buffer[255];
  fh = fopen(filename, "r");
  // check if file exists
  if (fh==NULL)
  {
    exit(EXIT_FAILURE);
  }
  while(fgets(buffer, 255, (FILE*) fh))
  {
    remove_whitespace(buffer);
    add_dict_word(dict, buffer);
  }
  fclose(fh);
  clear_screen();

  shuffle(g_tiles, 100);

  struct Player player1;
  struct Player player2;
  player1.points = 0;
  init_hand(player1.hand);
  fill_hand(player1.hand);
  printf("Enter name of player 1?: ");
  char *p1name = input();
  player1.name = p1name;

  player2.points = 0;
  init_hand(player2.hand);
  fill_hand(player2.hand);
  printf("Enter name of player 2?: ");
  char *p2name = input();
  player2.name = p2name;

  clear_screen();

  struct Player current_player;
  struct Player other_player;

  int coin_flip = rand() % 2;
  if (coin_flip == 1)
  {
    current_player = player1;
    other_player = player2;
    printf("%s begins!\n", player1.name);
  }
  else
  {
    current_player = player2;
    other_player = player1;
    printf("%s begins!\n", player2.name);
  }

  // while (!game_over(player1.hand, player2.hand, g_tiles))
  while(!(player_finished(current_player.hand) && player_finished(other_player.hand)))
  {
    keep_game_fair(other_player);
    draw(board, current_player, other_player);
    current_player = player_turn(current_player, board);
    clear_screen();
    struct Player temp = current_player;

    if (!player_finished(other_player.hand))
    {
      current_player = other_player;
      other_player = temp;
    }
  }

  if (current_player.points > other_player.points)
  {
    printf("%s wins with %i points!", current_player.name, current_player.points);
  }
  else if (other_player.points > current_player.points)
  {
    printf("%s wins with %i points!", other_player.name, other_player.points);
  }
  else if (other_player.points == current_player.points)
  {
    printf("The game ends with a tie! Both players have %i points!", current_player.points);
  }

  free_dict(dict);
}

int player_finished(int* hand)
{
  for (int i = 0; i < 7; i++)
  {
    if (hand[i] != 0)
    {
      return 0;
    }
  }
  return 1;
}

void remove_whitespace(char* word)
{
  for (int i = 0; i < strlen(word); i++)
  {
    if (word[i] < 'a' || word[i] > 'z')
    {
      word[i] = '\0';
    }
  }
}

char* input(void)
{
  char *input = malloc(100);
  fgets(input, 100, stdin);
  int n = strlen(input);
  if (n>0 && input[n-1]=='\n')
  {
    input[n-1] = 0;
  }
  return input;
}

void keep_game_fair(struct Player other_player)
{
  char *opt;
  do
  {
    printf("Is %s looking? <y or n>: ", other_player.name);
    opt = input();
  }
  while(strncmp(opt, "n",1)!=0);
  clear_screen();
}

struct Player player_turn(struct Player player, int board[15][15])
{
  printf("What would %s like to do? <p for play word, d for draw new hand, e for end game>: ", player.name);
  char* opt;
  opt = input();

  if (strncmp(opt, "p", 1) == 0)
  {
    player = player_plays_word(player, board);
    fill_hand(player.hand);
  }
  if (strncmp(opt, "d", 1) == 0)
  {
    init_hand(player.hand);
    fill_hand(player.hand);
  }
  if (strncmp(opt, "e", 1) == 0)
  {
    init_hand(player.hand);
  }
  return player;
}

struct Player player_plays_word(struct Player player, int board[15][15])
{
  char *player_input;
  int cont = 0;
  struct Word word;
  while (cont == 0)
  {
    printf("Enter a word as 'X Y d word': ");
    player_input = input();
    if (input_valid_format(player_input))
    {
      word = input_to_word(player_input);
      if (move_is_valid(dict, player, board, word))
      {
        cont = 1;
      }
    }
  }

  player = player_moves(player, board, word);
  return player;
}

struct Player init_player(struct Player player)
{
  player.points = 0;
  init_hand(player.hand);
  fill_hand(player.hand);
  printf("Enter name of player?: ");
  char pname[100];
  scanf( "%s", pname );
  player.name = pname;
  return player;
}

void draw(int board[15][15], struct Player current_player, struct Player other_player)
{
  draw_board(board);
  printf("%s: %i", current_player.name, current_player.points);
  printf("     ");
  draw_hand(current_player.hand);
  printf("     ");
  printf("%s: %i", other_player.name, other_player.points);
  printf("\n");
}

void draw_hand(int hand[])
{
  for (int i = 0; i < 7; i++)
  {
    char c = hand[i] - 1 + 'A';
    printf("%c ", c);
  }
}

void draw_board(int board[15][15])
{
  printf("   ");
  for (int i = 0; i < 15; i++)
  {
    printf("%2i ", i);
  }
  printf("\n");

  for (int i = 0; i < 15; i++)
  {
    printf("%2i ", i);
    for (int j = 0; j < 15; j++)
    {
      if (board[i][j] == 0)
      {
        if (SPECIAL_TILES[i][j] == '\0')
        {
          printf(" - ");
        }
        else
        {
          printf("%2c ", SPECIAL_TILES[i][j]);
        }
      }
      else
      {
        printf(" %c ", board[i][j] - 1 + 'A');
      }
    }
    printf("%2i ", i);
    printf("\n");
  }
  printf("   ");
  for (int i = 0; i < 15; i++)
  {
    printf("%2i ", i);
  }
  printf("\n");
}

void init_hand(int *hand)
{
  for (int i = 0; i < 7; i++)
  {
    hand[i] = 0;
  }
}

void fill_hand(int *hand)
{
  int pile_i = 0;
  for (int i = 0; i < 7; i++)
  {
    if (hand[i] == 0)
    {
      hand[i] = g_tiles[pile_i];
      g_tiles[pile_i] = 0;
      pile_i++;
    }
  }
  clean_pile();
}

void clean_pile(void)
{
  int new_pile[100] = { 0 };
  int new_pile_i = 0;
  for (int i = 0; i < 100; i++)
  {
    if (g_tiles[i] != 0)
    {
      new_pile[new_pile_i] = g_tiles[i];
      new_pile_i++;
    }
  }
  for (int i = 0; i < 100; i++)
  {
    g_tiles[i] = new_pile[i];
  }
}

void shuffle(int *array, size_t n)
{
  srand((unsigned)time(NULL));
  if (n > 1)
  {
    for (int i = 0; i < n - 1; i++) {
        size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
        int t = array[j];
        array[j] = array[i];
        array[i] = t;
    }
  }
}

int move_is_valid (struct TrieNode *dict, struct Player player, int board[15][15], struct Word word)
{
  // returns 1 only if move is valid, else returns 0
  if ((board_is_blank(board) == 1
        && word_crosses_center_tile(word) == 0)
      || (board_is_blank(board) == 0
        &&word_connects_with_word_on_board(board, word) == 0)
      || word_is_in_dictionary(dict, word.word) == 0
      || player_can_play_word(player, board, word) == 0)
  {
    return 0;
  }
  return 1;
}

int player_can_play_word(struct Player player, int board[15][15], struct Word word)
{
  for (int i = 0; i < strlen(word.word); i++)
  {
    int x = word.pos.x + (word.dir[1] * i);
    int y = word.pos.y + (word.dir[0] * i);

    if (board[y][x] != char_to_tile(word.word[i])
        && !tile_in_hand(char_to_tile(word.word[i]), player.hand))
    {
      return 0;
    }
  }
  return 1;
}

int tile_in_hand(int tile, int hand[7])
{
  for (int i = 0; i < 7; i++)
  {
    if (hand[i] == tile)
    {
      return 1;
    }
  }
  return 0;
}

int word_is_in_dictionary(struct TrieNode *dict, char *word)
{
  struct TrieNode *crawl = dict;
  for (int i = 0; i < strlen(word); i++)
  {
    int index = char_to_tile(word[i])-1;
    if (!crawl->children[index])
    {
      return 0;
    }
    crawl = crawl->children[index];
  }
  if (crawl->is_end_of_word == 1)
  {
    return 1;
  }
  return 0;
}

void add_dict_word(struct TrieNode *dict, char* word)
{
  struct TrieNode *crawl = dict;
  for (int i = 0; i < strlen(word); i++)
  {
    if ((word[i] >= 'A' && word[i] <= 'Z') || (word[i] >= 'a' || word[i] <= 'z'))
    {
      int index = char_to_tile(word[i])-1;
      if (!crawl->children[index])
      {
        crawl->children[index] = getNode();
      }
      crawl = crawl->children[index];
    }
  }
  crawl->is_end_of_word = 1;
}

struct TrieNode *getNode(void)
{
  struct TrieNode *node = (struct TrieNode*) malloc(sizeof (struct TrieNode));
  node->is_end_of_word = 0;
  for (int i = 0; i < 26; i++)
  {
    node->children[i] = NULL;
  }
  return node;
}

int word_crosses_center_tile(struct Word word)
{
  // returns 1 only if one char in word has pos [7, 7], else returns 0
  for (int i = 0; i < strlen(word.word); i++)
  {
    int x = word.pos.x + (word.dir[1] * i);
    int y = word.pos.y + (word.dir[0] * i);

    if (x == 7 && y == 7)
    {
      return 1;
    }
  }
  return 0;
}

int word_connects_with_word_on_board(int board[15][15], struct Word word)
{
  if (word_covers_tile(board, word) == 1
      || word_intersects_word_on_board(board, word) == 0
      || word_already_on_board(board, word) == 1)
  {
    return 0;
  }
  return 1;
}

int word_covers_tile(int board[15][15], struct Word word)
{
  // returns 1 if the word places a tile on a spot tht is already
  // filled with a differemt tile. Else, returns 0
  for (int i = 0; i < strlen(word.word); i++)
  {
    int x = word.pos.x + (word.dir[1] * i);
    int y = word.pos.y + (word.dir[0] * i);

    if (board[y][x] != 0 && board[y][x] != char_to_tile(word.word[i]))
    {
      return 1;
    }
  }
  return 0;
}

int word_intersects_word_on_board(int board[15][15], struct Word word)
{
  for (int i = 0; i < strlen(word.word); i++)
  {
    int x = word.pos.x + (word.dir[1] * i);
    int y = word.pos.y + (word.dir[0] * i);

    if (board[y][x] == char_to_tile(word.word[i]))
    {
      return 1;
    }
  }
  return 0;
}

int word_already_on_board(int board[15][15], struct Word word)
{
  for (int i = 0; i < strlen(word.word); i++)
  {
    int x = word.pos.x + (word.dir[1] * i);
    int y = word.pos.y + (word.dir[0] * i);

    if (board[y][x] == 0)
    {
      return 0;
    }
  }
  return 1;
}

struct Player player_moves(struct Player player, int board[15][15], struct Word word)
{
  // updates a player's hand and points, and the board
  // ASSUME: the move is valid
  player.points = update_points(player.points, board, word);
  update_hand(player.hand, board, word);
  insert_word(board, word);
  return player;
}


int update_points(int points, int board[15][15], struct Word word)
{
  int new_points = points_for_word(board, word);

  int perp[2];
  get_perpendicular_dir(perp, word.dir);

  int board_cpy[15][15];
  copy_board(board_cpy, board);
  for (int i = 0; i < strlen(word.word); i++)
  {
    int x = word.pos.x + (word.dir[1] * i);
    int y = word.pos.y + (word.dir[0] * i);

    if (board[y][x] == 0)
    {
      board_cpy[y][x] = char_to_tile(word.word[i]);
      struct Word perp_word = get_word_from_board(board_cpy, x, y, perp);

      if (strlen(perp_word.word) > 1)
      {
        new_points = new_points + points_for_word(board, perp_word);
      }
    }
  }

  return points + new_points;
}

int points_for_word(int board[15][15], struct Word word)
{
  int points = 0;
  int double_word = 0;
  int tripple_word = 0;

  for (int i = 0; i < strlen(word.word); i++)
  {
    int x = word.pos.x + (word.dir[1] * i);
    int y = word.pos.y + (word.dir[0] * i);

    if (board[y][x] == 0)
    {
      int tile_val = TILE_VALS[char_to_tile(word.word[i])];

      if (SPECIAL_TILES[y][x] == '+')
      {
        tile_val = tile_val * 2;
      }
      else if (SPECIAL_TILES[y][x] == '~')
      {
        tile_val = tile_val * 3;
      }
      points = points + tile_val;

      if (SPECIAL_TILES[y][x] == '*')
      {
        double_word = 1;
      }
      else if (SPECIAL_TILES[y][x] == '@')
      {
        tripple_word = 1;
      }
    }
    else
    {
      points = points + TILE_VALS[char_to_tile(word.word[i])];
    }
  }

  if (double_word == 1)
  {
    points = points * 2;
  }
  else if (tripple_word == 1)
  {
    points = points * 3;
  }

  return points;
}

void get_perpendicular_dir(int perp[2], int dir[2])
{
  if (dir[0] == HOR[0] && dir[1] == HOR[1])
  {
    perp[0] = VER[0];
    perp[1] = VER[1];
  }
  else
  {
    perp[0] = HOR[0];
    perp[1] = HOR[1];
  }
}

void update_hand(int hand[], int board[15][15], struct Word word)
{
  // removes letters from word not already on board from hand
  // ASSUME: word is valid (word is in dictionary and letters are either in hand or on board)
  for (int i = 0; i < strlen(word.word); i++)
  {
    int x = word.pos.x + (word.dir[1] * i);
    int y = word.pos.y + (word.dir[0] * i);

    if (board[y][x] == 0)
    {
      remove_from_hand(hand, char_to_tile(word.word[i]));
    }
  }
}

void remove_from_hand(int* hand, int letter)
{
  // replaces one instance of letter in hand with empty slot (0)
  // ASSUME: letter is in hand
  for (int i = 0; i < 7; i++)
  {
    if (hand[i] == letter)
    {
      hand[i] = 0;
      return;
    }
  }
}

void insert_word(int board[15][15], struct Word word)
{
  for (int i = 0; i < strlen(word.word); i++)
  {
    int x = word.pos.x + (word.dir[1] * i);
    int y = word.pos.y + (word.dir[0] * i);
    int tile = char_to_tile(word.word[i]);
    insert_tile(board, x, y, tile);
  }
}

struct Word get_word_from_board(int board[15][15], int x0, int y0, int dir[2])
{
  int x = x0;
  int y = y0;
  while (board[y - dir[0]][x - dir[1]] != 0 && (x - dir[1]) >= 0 && (y - dir[0]) >= 0)
  {
    x = x - dir[1];
    y = y - dir[0];
  }
  int start_x = x;
  int start_y = y;

  static char tiles[15];
  int i = 0;
  while (board[y][x] != 0 && x >= 0 && y >= 0 && x <= 14 && y <= 14) {
    tiles[i] = board[y][x] + 64;
    x = x + dir[1];
    y = y + dir[0];
    i++;
  }
  tiles[i] = '\0';

  struct Word word;
  word.word = tiles;
  word.pos.x = start_x;
  word.pos.y = start_y;
  word.dir = dir;
  return word;
}


void insert_tile(int board[15][15], int x, int y, int val)
{
  if (board[y][x] == 0)
  {
    board[y][x] = val;
  }
}

int input_valid_format(char *input)
{
  int crawl = 0;
  char temp[100];
  while (input[crawl] != ' ' && input[crawl] != '\0')
  {
    if (input[crawl] > '9' || input[crawl] < '0')
    {
      return 0;
    }
    temp[crawl] = input[crawl];
    crawl++;
  }
  temp[crawl] = '\0';
  if (atoi(temp) > 14)
  {
    return 0;
  }
  crawl++;
  int i = 0;
  while (input[crawl] != ' ' && input[crawl] != '\0')
  {
    if (input[crawl] > '9' || input[crawl] < '0')
    {
      return 0;
    }
    temp[i] = input[crawl];
    crawl++;
    i++;
  }
  temp[i] = '\0';
  if (atoi(temp) > 14)
  {
    return 0;
  }
  crawl++;
  if (input[crawl] != 'h' && input[crawl] != 'v')
  {
    return 0;
  }
  crawl++;
  crawl++;
  while(input[crawl] != '\0')
  {
    if (input[crawl] < 'A' || (input[crawl] > 'Z' && input[crawl] < 'a') || input[crawl] > 'z')
    {
      return 0;
    }
    crawl++;
  }

  return 1;
}

struct Word input_to_word(char *input)
{
  struct Pos pos;
  int i = 0;
  char temp[100];
  while (input[i] != ' ')
  {
    temp[i] = input[i];
    i++;
  }
  temp[i] = '\0';
  pos.x = atoi(temp);

  int crawl = i+1;
  i = 0;
  temp[0] = '\0';
  while (input[i+crawl] != ' ')
  {
    temp[i] = input[i+crawl];
    i++;
  }
  temp[i] = '\0';
  pos.y = atoi(temp);

  struct Word word;
  word.pos = pos;


  crawl = crawl + i + 1;
  if(input[crawl] == 'h')
  {
    word.dir = HOR;
  }
  else if (input[crawl] == 'v')
  {
    word.dir = VER;
  }

  crawl = crawl + 2;
  temp[0] = '\0';
  for (int i = 0; crawl < strlen(input); i++)
  {
    temp[i] = input[crawl];
    crawl++;
  }
  temp[strlen(input)] = '\0';
  word.word = malloc(strlen(temp));
  strcpy(word.word, temp);

  return word;
}

void copy_board(int cpy[15][15], int orig[15][15])
{
  for (int i = 0; i < 15; i++)
  {
    memcpy(&cpy[i], &orig[i], sizeof(orig[0]));
  }
}

int board_is_blank(int board[15][15])
{
  // returns 1 only if board is blank, else returns 0
  for (int i = 0; i < 15; i++)
  {
    for (int j = 0; j < 15; j++)
    {
      if (board[i][j] != 0)
      {
        return 0;
      }
    }
  }
  return 1;
}

int char_to_tile(char c)
{
  if (c >= 'A' && c <= 'Z')
  {
    return c - 64;
  }
  else if (c >= 'a' && c <= 'z')
  {
    return c - 96;
  }
  else if (c == ' ')
  {
    return 27;
  }
  else
  {
    return 0;
  }
}

void free_dict(struct TrieNode *node)
{
  for (int i = 0; i < 26; i++)
  {
    if (node->children[i] != NULL)
    {
      free_dict(node->children[i]);
    }
  }
  free(node);
  node = NULL;
}

void clear_screen(void)
{
  const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}
