/*
 * a header file for Scrabble.c
 */

 struct Player {
   int hand[7];
   int points;
   char *name;
 };

struct Pos {
  int x;
  int y;
};

struct Word {
  char* word;
  int* dir;
  struct Pos pos;
};

struct TrieNode {
  int is_end_of_word;
  struct TrieNode *children[26];
};

int board[15][15];
int HOR[2];
int VER[2];

struct TrieNode *dict;

int move_is_valid(struct TrieNode *dict, struct Player player, int board[15][15], struct Word word);
int player_can_play_word(struct Player player, int board[15][15], struct Word word);
int tile_in_hand(int tile, int hand[7]);
int word_is_in_dictionary(struct TrieNode *dict, char *word);
void list_to_dict(char *list[2]);
void add_dict_word(struct TrieNode *dict, char* word);
struct TrieNode *getNode(void);
int word_crosses_center_tile(struct Word word);
int word_connects_with_word_on_board(int board[15][15], struct Word word);
int word_covers_tile(int board[15][15], struct Word word);
int word_intersects_word_on_board(int board[15][15], struct Word word);
int word_already_on_board(int board[15][15], struct Word word);

struct Player player_moves(struct Player player, int board[15][15], struct Word word);
int update_points(int points, int board[15][15], struct Word word);
int points_for_word(int board[15][15], struct Word word);
void get_perpendicular_dir(int perp[2], int dir[2]);

void update_hand(int hand[], int board[15][15], struct Word word);
void remove_from_hand(int* hand, int letter);

struct Word get_word_from_board(int board[15][15], int x0, int y0, int dir[2]);

void insert_word(int board[15][15], struct Word word);
void insert_tile(int board[15][15], int x, int y, int val);
int char_to_tile(char c);

void copy_board(int cpy[15][15], int orig[15][15]);
int board_is_blank(int board[15][15]);

void draw(int board[15][15], struct Player current_player, struct Player other_player);
void draw_board(int board[15][15]);
void draw_hand(int hand[]);

struct Player init_player(struct Player player);
void shuffle(int *array, size_t n);
void init_hand(int *hand);
void fill_hand(int *hand);
void clean_pile(void);

void keep_game_fair(struct Player other_player);
struct Player player_turn(struct Player player, int board[15][15]);
int player_finished(int* hand);
struct Player player_plays_word(struct Player player, int board[15][15]);
int input_valid_format(char *input);
struct Word input_to_word(char *input);

void clear_screen(void);
char* input(void);
void remove_whitespace(char* word);
int word_is_alpha(char* word);
void free_dict(struct TrieNode *dict);
