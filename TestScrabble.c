#include <string.h>
#include "Unity/src/unity.h"
#include "Scrabble.h"


void test_input_valid_format(void)
{
  TEST_ASSERT_EQUAL_INT(1, input_valid_format("7 7 h of"));
  TEST_ASSERT_EQUAL_INT(1, input_valid_format("11 1 v blue"));
  TEST_ASSERT_EQUAL_INT(1, input_valid_format("1 11 h blue"));

  TEST_ASSERT_EQUAL_INT(0, input_valid_format("77hof"));
  TEST_ASSERT_EQUAL_INT(0, input_valid_format("ab 7 h of"));
  TEST_ASSERT_EQUAL_INT(0, input_valid_format("a 7 h blue"));
  TEST_ASSERT_EQUAL_INT(0, input_valid_format("7 ab h blue"));
  TEST_ASSERT_EQUAL_INT(0, input_valid_format("a7 7 h blue"));
  TEST_ASSERT_EQUAL_INT(0, input_valid_format("7 a7 h blue"));
  TEST_ASSERT_EQUAL_INT(0, input_valid_format("15 7 h blue"));
  TEST_ASSERT_EQUAL_INT(0, input_valid_format("7 15 h blue"));
  TEST_ASSERT_EQUAL_INT(0, input_valid_format("7 7 i blue"));
  TEST_ASSERT_EQUAL_INT(0, input_valid_format("7  7 h blue"));
  TEST_ASSERT_EQUAL_INT(0, input_valid_format("7 7  h blue"));
  TEST_ASSERT_EQUAL_INT(0, input_valid_format("7 7 h  blue"));
  TEST_ASSERT_EQUAL_INT(0, input_valid_format(" 7 7 h blue"));
  TEST_ASSERT_EQUAL_INT(0, input_valid_format("7 7 h blue "));
}

void test_input_to_word(void)
{
  struct Pos pos1 = { 7, 7 };
  struct Word word1 = { "of", HOR, pos1};
  struct Word word2 = input_to_word("7 7 h of");

  TEST_ASSERT_EQUAL_INT(word1.pos.x, word2.pos.x);
  TEST_ASSERT_EQUAL_INT(word1.pos.y, word2.pos.y);
  TEST_ASSERT_EQUAL_INT(word1.dir[0], word2.dir[0]);
  TEST_ASSERT_EQUAL_INT(word1.dir[1], word2.dir[1]);
  TEST_ASSERT_EQUAL_STRING(word1.word, word2.word);

  struct Pos pos3 = { 11, 1 };
  struct Word word3 = { "blue", VER, pos3};
  struct Word word4 = input_to_word("11 1 v blue");

  TEST_ASSERT_EQUAL_INT(word3.pos.x, word4.pos.x);
  TEST_ASSERT_EQUAL_INT(word3.pos.y, word4.pos.y);
  TEST_ASSERT_EQUAL_INT(word3.dir[0], word4.dir[0]);
  TEST_ASSERT_EQUAL_INT(word3.dir[1], word4.dir[1]);
  TEST_ASSERT_EQUAL_STRING(word3.word, word4.word);

  struct Pos pos5 = { 1, 11 };
  struct Word word5 = { "blue", HOR, pos5};
  struct Word word6 = input_to_word("1 11 h blue");

  TEST_ASSERT_EQUAL_INT(word5.pos.x, word6.pos.x);
  TEST_ASSERT_EQUAL_INT(word5.pos.y, word6.pos.y);
  TEST_ASSERT_EQUAL_INT(word5.dir[0], word6.dir[0]);
  TEST_ASSERT_EQUAL_INT(word5.dir[1], word6.dir[1]);
  TEST_ASSERT_EQUAL_STRING(word5.word, word6.word);
}

void test_move_is_valid_returns_true_only_if_move_is_valid(void)
{
  char *list[] = { "a", "hello", "bob", "organic", "anteater", "tomato", "mob" };
  dict = getNode();
  for (int i = 0; i < 7; i++)
  {
    add_dict_word(dict, list[i]);
  }


  int B1[15][15] = { 0 };
  struct Player Player1;
  int temp1[] = { 1, 2, 3, 4, 5, 6, 7 };
  memcpy(Player1.hand, temp1, 7);
  Player1.points = 0;
  struct Pos pos1 = { 7, 7 };
  struct Word word1 = { "A", HOR, pos1 };

  TEST_ASSERT_EQUAL_INT(1, move_is_valid(dict, Player1, B1, word1));

  // // -------------------------------------------------------

  int B9[15][15] = { 0 };
  struct Player Player9;
  int temp9[] = {8, 5, 12, 12, 15, 1, 2};
  memcpy(Player9.hand, temp9, sizeof temp9);
  Player9.points = 0;
  struct Pos pos2 = { 3, 7 };
  struct Word word2 = { "hello", HOR, pos2 };

  TEST_ASSERT_EQUAL_INT(1, move_is_valid(dict, Player9, B9, word2));

  // // -------------------------------------------------------

  int B11[15][15] = { 0 };
  struct Player Player11;
  memcpy(Player11.hand, temp9, sizeof temp9);
  Player11.points = 0;
  struct Pos pos3 = { 7, 4 };
  struct Word word3 = { "HELLO", VER, pos3 };

  TEST_ASSERT_EQUAL_INT(1, move_is_valid(dict, Player11, B11, word3));

  // // ---------------------------------------------------------

  int B13[15][15] = { 0 };
  struct Pos pos4 = { 3, 7 };
  struct Word word4 = { "hello", HOR, pos4 };
  insert_word(B13, word4);
  struct Player Player13;
  int temp13[] = { 3, 1, 18, 7, 9, 14, 15};
  memcpy(Player13.hand, temp13, sizeof temp13);
  Player13.points = 0;
  struct Pos pos5 = { 7, 7 };
  struct Word word5 = { "organic", VER, pos5 };

  TEST_ASSERT_EQUAL_INT(1, move_is_valid(dict, Player13, B13, word5));

  // // --------------------------------------------------------

  int B15[15][15] = { 0 };
  struct Pos pos6 = { 7, 7 };
  struct Word word6 = { "hello", VER, pos6 };
  insert_word(B15, word6);
  struct Player Player15;
  memcpy(Player15.hand, temp13, sizeof temp13);
  Player15.points = 0;
  struct Pos pos7 = { 7, 11 };
  struct Word word7 = { "organic", HOR, pos7 };

  TEST_ASSERT_EQUAL_INT(1, move_is_valid(dict, Player15, B15, word7));

  // // -----------------------------------------------------------

  int B17[15][15] = { 0 };
  struct Pos pos8 = { 6, 7 };
  struct Word word8 = { "ant", HOR, pos8 };
  insert_word(B17, word8);
  struct Player Player17;
  int temp17[] = { 18, 5, 1, 5, 20, 2, 20 };
  memcpy(Player17.hand, temp17, sizeof temp17);
  Player17.points = 0;
  struct Pos pos9 = { 6, 7 };
  struct Word word9 = { "anteater", HOR, pos9 };

  TEST_ASSERT_EQUAL_INT(1, move_is_valid(dict, Player17, B17, word9));

  // // -------------------------------------------------------------

  int B19[15][15] = { 0 };
  struct Pos pos10 = { 7, 7 };
  struct Word word10 = { "ant", VER, pos10 };
  insert_word(B19, word10);
  struct Player Player19;
  memcpy(Player19.hand, temp17, sizeof temp17);
  Player19.points = 0;
  struct Pos pos11 = { 7, 7 };
  struct Word word11 = { "anteater", VER, pos11 };

  TEST_ASSERT_EQUAL_INT(1, move_is_valid(dict, Player19, B19, word11));

  // // -----------------------------------------------------------------

  int B21[15][15] = { 0 };
  struct Pos pos12 = { 7, 7 };
  struct Word word12 = { "no", HOR, pos12 };
  insert_word(B21, word12);
  struct Player Player21;
  int temp21[] = { 20, 15, 13, 1, 20, 15, 18 };
  memcpy(Player21.hand, temp21, sizeof temp21);
  Player21.points = 0;
  struct Pos pos13 = { 8, 6 };
  struct Word word13 = { "tomato", VER, pos13 };

  TEST_ASSERT_EQUAL_INT(1, move_is_valid(dict, Player21, B21, word13));

  // // ------------------------------------------------------------------

  int B23[15][15] = { 0 };
  struct Pos pos14 = { 7, 5 };
  struct Word word14 = { "farms", VER, pos14 };
  insert_word(B23, word14);
  struct Pos pos15 = { 5, 7 };
  struct Word word15 = { "horn", HOR, pos15 };
  insert_word(B23, word15);
  struct Pos pos16 = { 5, 9 };
  struct Word word16 = { "paste", HOR, pos16 };
  insert_word(B23, word16);
  struct Player Player23;
  int temp23[] = { 13, 15, 2, 3, 5, 1, 16 };
  memcpy(Player23.hand, temp23, sizeof temp23);
  Player23.points = 30;
  struct Pos pos17 = { 7, 8 };
  struct Word word17 = { "mob", HOR, pos17 };

  TEST_ASSERT_EQUAL_INT(1, move_is_valid(dict, Player23, B23, word17));

  // --------------------------------------------------------------

  int B24[15][15] = { 0 };
  struct Player Player24;
  int temp24[] = { 1, 2, 3, 4, 5, 6, 7 };
  memcpy(Player24.hand, temp24, sizeof temp24);
  Player24.points = 0;
  struct Pos pos24 = { 7, 6 };
  struct Word word24 = { "A", HOR, pos24 };

  TEST_ASSERT_EQUAL_INT(0, move_is_valid(dict, Player24, B24, word24));
    // first move must pass center tile

  // -------------------------------------------------------------

  int B25[15][15] = { 0 };
  struct Player Player25;
  int temp25[] = {8, 5, 12, 12, 15, 1, 2};
  memcpy(Player25.hand, temp25, sizeof temp25);
  Player25.points = 0;
  struct Pos pos25 = { 2, 7 };
  struct Word word25 = { "hello", HOR, pos25 };

  TEST_ASSERT_EQUAL_INT(0, move_is_valid(dict, Player25, B25, word25));
    // first move must pass center tile

  // --------------------------------------------------------------

  int B26[15][15] = { 0 };
  struct Player Player26;
  int temp26[] = {8, 5, 12, 12, 15, 1, 2};
  memcpy(Player26.hand, temp26, sizeof temp26);
  Player26.points = 0;
  struct Pos pos26 = { 7, 2 };
  struct Word word26 = { "hello", VER, pos25 };

  TEST_ASSERT_EQUAL_INT(0, move_is_valid(dict, Player26, B26, word26));
    // first move must pass center tile

  // -------------------------------------------------------

  int B27[15][15] = { 0 };
  struct Player Player27;
  int temp27[] = {8, 9, 12, 12, 15, 1, 2};
  memcpy(Player27.hand, temp27, sizeof temp27);
  Player27.points = 0;
  struct Pos pos27 = { 3, 7 };
  struct Word word27 = { "hillo", HOR, pos27 };

  TEST_ASSERT_EQUAL_INT(0, move_is_valid(dict, Player27, B27, word27));
    // must be a word in dictionary

  // -------------------------------------------------------

  int B28[15][15] = { 0 };
  struct Player Player28;
  int temp28[] = {8, 9, 12, 12, 15, 1, 2};
  memcpy(Player28.hand, temp28, sizeof temp28);
  Player28.points = 0;
  struct Pos pos28 = { 3, 7 };
  struct Word word28 = { "hello", HOR, pos28 };

  TEST_ASSERT_EQUAL_INT(0, move_is_valid(dict, Player28, B28, word28));
    // all characters must be from hand or board

  // --------------------------------------------------------

  int B29[15][15] = { 0 };
  insert_word(B29, word28);
  struct Player Player29;
  int temp29[] = { 3, 1, 18, 7, 9, 14, 15};
  memcpy(Player29.hand, temp29, sizeof temp29);
  Player29.points = 0;
  struct Pos pos29 = { 7, 8 };
  struct Word word29 = { "organic", VER, pos29 };

  TEST_ASSERT_EQUAL_INT(0, move_is_valid(dict, Player29, B29, word29));
    // new word must intersect with word on board

  // ---------------------------------------------------------

  int B30[15][15] = { 0 };
  insert_word(B30, word28);
  struct Player Player30;
  int temp30[] = {8, 5, 12, 12, 15, 1, 2};
  memcpy(Player30.hand, temp30, sizeof temp30);
  Player30.points = 0;

  TEST_ASSERT_EQUAL_INT(0, move_is_valid(dict, Player30, B30, word28));
    // new word must add a tile to board

  // -----------------------------------------------------------

  int B31[15][15] = { 0 };
  struct Pos pos31 = { 7, 7 };
  struct Word word31 = { "Always", HOR, pos31};
  insert_word(B31, word31);
  struct Player Player31;
  int temp31[] = { 3, 1, 18, 7, 9, 14, 15};
  memcpy(Player31.hand, temp31, sizeof temp31);
  Player31.points = 0;
  struct Pos pos32 = { 8, 7 };
  struct Word word32 = { "organic", VER, pos32 };

  TEST_ASSERT_EQUAL_INT(0, move_is_valid(dict, Player31, B31, word32));
    // new word word cannot place new tile on filled spot

  // ---------------------------------------------------------
}

void test_word_is_in_dictionary(void)
{
  char *list[] = { "a", "hello", "bob", "organic", "anteater", "tomato", "mob" };
  dict = getNode();
  for (int i = 0; i < 7; i++)
  {
    add_dict_word(dict, list[i]);
  }



  char *word27 = "hillo";

  TEST_ASSERT_EQUAL_INT(0, word_is_in_dictionary(dict, word27));
    // must be a word in dictionary

  // -------------------------------------------------------

  char *word1 = "a";

  TEST_ASSERT_EQUAL_INT(1, word_is_in_dictionary(dict, word1));

  // // -------------------------------------------------------

  char *word2 = "hello";

  TEST_ASSERT_EQUAL_INT(1, word_is_in_dictionary(dict, word2));

  // // -------------------------------------------------------

  char *word3 = "HELLO";

  TEST_ASSERT_EQUAL_INT(1, word_is_in_dictionary(dict, word3));

  // // ---------------------------------------------------------

  char *word5 = "organic";

  TEST_ASSERT_EQUAL_INT(1, word_is_in_dictionary(dict, word5));

  // // --------------------------------------------------------

  char *word7 = "organic";

  TEST_ASSERT_EQUAL_INT(1, word_is_in_dictionary(dict, word7));

  // // -----------------------------------------------------------

  char *word9 = "anteater";

  TEST_ASSERT_EQUAL_INT(1, word_is_in_dictionary(dict, word9));

  // // -------------------------------------------------------------

  char *word11 = "anteater";

  TEST_ASSERT_EQUAL_INT(1, word_is_in_dictionary(dict, word11));

  // // -----------------------------------------------------------------

  char *word13 = "tomato";

  TEST_ASSERT_EQUAL_INT(1, word_is_in_dictionary(dict, word13));

  // // ------------------------------------------------------------------

  char *word17 = "mob";

  TEST_ASSERT_EQUAL_INT(1, word_is_in_dictionary(dict, word17));
}

void test_player_can_play_word(void)
{
  int B28[15][15] = { 0 };
  struct Player Player28;
  int temp28[] = {8, 9, 12, 12, 15, 1, 2};
  memcpy(Player28.hand, temp28, sizeof temp28);
  Player28.points = 0;
  struct Pos pos28 = { 3, 7 };
  struct Word word28 = { "hello", HOR, pos28 };

  TEST_ASSERT_EQUAL_INT(0, player_can_play_word(Player28, B28, word28));
    // all characters must be from hand or board

  // --------------------------------------------------------

  int B1[15][15] = { 0 };
  struct Player Player1;
  int temp1[] = { 1, 2, 3, 4, 5, 6, 7 };
  memcpy(Player1.hand, temp1, sizeof temp1);
  Player1.points = 0;
  struct Pos pos1 = { 7, 7 };
  struct Word word1 = { "A", HOR, pos1 };

  TEST_ASSERT_EQUAL_INT(1, player_can_play_word(Player1, B1, word1));

  // -------------------------------------------------------

  int B9[15][15] = { 0 };
  struct Player Player9;
  int temp9[] = {8, 5, 12, 12, 15, 1, 2};
  memcpy(Player9.hand, temp9, sizeof temp9);
  Player9.points = 0;
  struct Pos pos2 = { 3, 7 };
  struct Word word2 = { "hello", HOR, pos2 };

  TEST_ASSERT_EQUAL_INT(1, player_can_play_word(Player9, B9, word2));

  // -------------------------------------------------------

  int B11[15][15] = { 0 };
  struct Player Player11;
  memcpy(Player11.hand, temp9, sizeof temp9);
  Player11.points = 0;
  struct Pos pos3 = { 7, 4 };
  struct Word word3 = { "HELLO", VER, pos3 };

  TEST_ASSERT_EQUAL_INT(1, player_can_play_word(Player11, B11, word3));

  // ---------------------------------------------------------

  int B13[15][15] = { 0 };
  struct Pos pos4 = { 3, 7 };
  struct Word word4 = { "hello", HOR, pos4 };
  insert_word(B13, word4);
  struct Player Player13;
  int temp13[] = { 3, 1, 18, 7, 9, 14, 15};
  memcpy(Player13.hand, temp13, sizeof temp13);
  Player13.points = 0;
  struct Pos pos5 = { 7, 7 };
  struct Word word5 = { "organic", VER, pos5 };

  TEST_ASSERT_EQUAL_INT(1, player_can_play_word(Player13, B13, word5));

  // --------------------------------------------------------

  int B15[15][15] = { 0 };
  struct Pos pos6 = { 7, 7 };
  struct Word word6 = { "hello", VER, pos6 };
  insert_word(B15, word6);
  struct Player Player15;
  memcpy(Player15.hand, temp13, sizeof temp13);
  Player15.points = 0;
  struct Pos pos7 = { 7, 11 };
  struct Word word7 = { "organic", HOR, pos7 };

  TEST_ASSERT_EQUAL_INT(1, player_can_play_word(Player15, B15, word7));

  // -----------------------------------------------------------

  int B17[15][15] = { 0 };
  struct Pos pos8 = { 6, 7 };
  struct Word word8 = { "ant", HOR, pos8 };
  insert_word(B17, word8);
  struct Player Player17;
  int temp17[] = { 18, 5, 1, 5, 20, 2, 20 };
  memcpy(Player17.hand, temp17, sizeof temp17);
  Player17.points = 0;
  struct Pos pos9 = { 6, 7 };
  struct Word word9 = { "anteater", HOR, pos9 };

  TEST_ASSERT_EQUAL_INT(1, player_can_play_word(Player17, B17, word9));

  // -------------------------------------------------------------

  int B19[15][15] = { 0 };
  struct Pos pos10 = { 7, 7 };
  struct Word word10 = { "ant", VER, pos10 };
  insert_word(B19, word10);
  struct Player Player19;
  memcpy(Player19.hand, temp17, sizeof temp17);
  Player19.points = 0;
  struct Pos pos11 = { 7, 7 };
  struct Word word11 = { "anteater", VER, pos11 };

  TEST_ASSERT_EQUAL_INT(1, player_can_play_word(Player19, B19, word11));

  // ---------------------------------------------------------------

  int B21[15][15] = { 0 };
  struct Pos pos12 = { 7, 7 };
  struct Word word12 = { "no", HOR, pos12 };
  insert_word(B21, word12);
  struct Player Player21;
  int temp21[] = { 20, 15, 13, 1, 20, 15, 18 };
  memcpy(Player21.hand, temp21, sizeof temp21);
  Player21.points = 0;
  struct Pos pos13 = { 9, 7 };
  struct Word word13 = { "tomato", VER, pos13 };

  TEST_ASSERT_EQUAL_INT(1, player_can_play_word(Player21, B21, word13));

  // ------------------------------------------------------------

  int B23[15][15] = { 0 };
  struct Pos pos14 = { 7, 5 };
  struct Word word14 = { "farms", VER, pos14 };
  insert_word(B23, word14);
  struct Pos pos15 = { 5, 7 };
  struct Word word15 = { "horn", HOR, pos15 };
  insert_word(B23, word15);
  struct Pos pos16 = { 5, 9 };
  struct Word word16 = { "paste", HOR, pos16 };
  insert_word(B23, word16);
  struct Player Player23;
  int temp23[] = { 13, 15, 2, 3, 5, 1, 16 };
  memcpy(Player23.hand, temp23, sizeof temp23);
  Player23.points = 30;
  struct Pos pos17 = { 7, 8 };
  struct Word word17 = { "mob", HOR, pos17 };

  TEST_ASSERT_EQUAL_INT(1, player_can_play_word(Player23, B23, word17));
}

void test_tile_in_hand(void)
{
  int tile = 8;
  int hand[7] = { 1, 4, 6, 4, 8, 6, 7 };
  TEST_ASSERT_EQUAL_INT(1, tile_in_hand(tile, hand));

  int tile1 = 1;
  int hand1[7] = { 3, 4, 5, 6, 7, 8, 9 };
  TEST_ASSERT_EQUAL_INT(0, tile_in_hand(tile1, hand1));
}

void test_word_connects_with_word_on_board(void)
{
  int B31[15][15] = { 0 };
  struct Pos pos31 = { 7, 7 };
  struct Word word31 = { "Always", HOR, pos31};
  insert_word(B31, word31);
  struct Pos pos32 = { 8, 7 };
  struct Word word32 = { "organic", VER, pos32 };

  TEST_ASSERT_EQUAL_INT(0, word_connects_with_word_on_board(B31, word32));
    // new word word cannot place new tile on filled spot

  // ------------------------------------------------------------

  int B29[15][15] = { 0 };
  struct Pos pos28 = { 3, 7 };
  struct Word word28 = { "hello", HOR, pos28 };
  insert_word(B29, word28);
  struct Pos pos29 = { 7, 8 };
  struct Word word29 = { "organic", VER, pos29 };

  TEST_ASSERT_EQUAL_INT(0, word_connects_with_word_on_board(B29, word29));
    // new word must intersect with word on board

  // ---------------------------------------------------------

  int B30[15][15] = { 0 };
  insert_word(B30, word28);

  TEST_ASSERT_EQUAL_INT(0, word_connects_with_word_on_board(B30, word28));
    // new word must add a tile to board

  // ---------------------------------------------------------


  int B13[15][15] = { 0 };
  struct Pos pos4 = { 3, 7 };
  struct Word word4 = { "hello", HOR, pos4 };
  insert_word(B13, word4);
  struct Pos pos5 = { 7, 7 };
  struct Word word5 = { "organic", VER, pos5 };

  TEST_ASSERT_EQUAL_INT(1, word_connects_with_word_on_board(B13, word5));

  // // --------------------------------------------------------

  int B15[15][15] = { 0 };
  struct Pos pos6 = { 7, 7 };
  struct Word word6 = { "hello", VER, pos6 };
  insert_word(B15, word6);
  struct Pos pos7 = { 7, 11 };
  struct Word word7 = { "organic", HOR, pos7 };

  TEST_ASSERT_EQUAL_INT(1, word_connects_with_word_on_board(B15, word7));

  // // -----------------------------------------------------------

  int B17[15][15] = { 0 };
  struct Pos pos8 = { 6, 7 };
  struct Word word8 = { "ant", HOR, pos8 };
  insert_word(B17, word8);
  struct Pos pos9 = { 6, 7 };
  struct Word word9 = { "anteater", HOR, pos9 };

  TEST_ASSERT_EQUAL_INT(1, word_connects_with_word_on_board(B17, word9));

  // // -------------------------------------------------------------

  int B19[15][15] = { 0 };
  struct Pos pos10 = { 7, 7 };
  struct Word word10 = { "ant", VER, pos10 };
  insert_word(B19, word10);
  struct Pos pos11 = { 7, 7 };
  struct Word word11 = { "anteater", VER, pos11 };

  TEST_ASSERT_EQUAL_INT(1, word_connects_with_word_on_board(B19, word11));

  // // -----------------------------------------------------------------

  int B21[15][15] = { 0 };
  struct Pos pos12 = { 7, 7 };
  struct Word word12 = { "no", HOR, pos12 };
  insert_word(B21, word12);
  struct Pos pos13 = { 8, 6 };
  struct Word word13 = { "tomato", VER, pos13 };

  TEST_ASSERT_EQUAL_INT(1, word_connects_with_word_on_board(B21, word13));

  // // ------------------------------------------------------------------

  int B23[15][15] = { 0 };
  struct Pos pos14 = { 7, 5 };
  struct Word word14 = { "farms", VER, pos14 };
  insert_word(B23, word14);
  struct Pos pos15 = { 5, 7 };
  struct Word word15 = { "horn", HOR, pos15 };
  insert_word(B23, word15);
  struct Pos pos16 = { 5, 9 };
  struct Word word16 = { "paste", HOR, pos16 };
  insert_word(B23, word16);
  struct Pos pos17 = { 7, 8 };
  struct Word word17 = { "mob", HOR, pos17 };

  TEST_ASSERT_EQUAL_INT(1, word_connects_with_word_on_board(B23, word17));

}

void test_word_already_on_board(void)
{
  struct Pos pos4 = { 3, 7 };
  struct Word word4 = { "hello", HOR, pos4 };
  int B30[15][15] = { 0 };
  insert_word(B30, word4);

  TEST_ASSERT_EQUAL_INT(1, word_already_on_board(B30, word4));
    // new word must add a tile to board

  // ---------------------------------------------------------


  int B13[15][15] = { 0 };
  insert_word(B13, word4);
  struct Pos pos5 = { 7, 7 };
  struct Word word5 = { "organic", VER, pos5 };

  TEST_ASSERT_EQUAL_INT(0, word_already_on_board(B13, word5));

  // // --------------------------------------------------------

  int B15[15][15] = { 0 };
  struct Pos pos6 = { 7, 7 };
  struct Word word6 = { "hello", VER, pos6 };
  insert_word(B15, word6);
  struct Pos pos7 = { 7, 11 };
  struct Word word7 = { "organic", HOR, pos7 };

  TEST_ASSERT_EQUAL_INT(0, word_already_on_board(B15, word7));

  // // -----------------------------------------------------------

  int B17[15][15] = { 0 };
  struct Pos pos8 = { 6, 7 };
  struct Word word8 = { "ant", HOR, pos8 };
  insert_word(B17, word8);
  struct Pos pos9 = { 6, 7 };
  struct Word word9 = { "anteater", HOR, pos9 };

  TEST_ASSERT_EQUAL_INT(0, word_already_on_board(B17, word9));

  // // -------------------------------------------------------------

  int B19[15][15] = { 0 };
  struct Pos pos10 = { 7, 7 };
  struct Word word10 = { "ant", VER, pos10 };
  insert_word(B19, word10);
  struct Pos pos11 = { 7, 7 };
  struct Word word11 = { "anteater", VER, pos11 };

  TEST_ASSERT_EQUAL_INT(0, word_already_on_board(B19, word11));

  // // -----------------------------------------------------------------

  int B23[15][15] = { 0 };
  struct Pos pos14 = { 7, 5 };
  struct Word word14 = { "farms", VER, pos14 };
  insert_word(B23, word14);
  struct Pos pos15 = { 5, 7 };
  struct Word word15 = { "horn", HOR, pos15 };
  insert_word(B23, word15);
  struct Pos pos16 = { 5, 9 };
  struct Word word16 = { "paste", HOR, pos16 };
  insert_word(B23, word16);
  struct Pos pos17 = { 7, 8 };
  struct Word word17 = { "mob", HOR, pos17 };

  TEST_ASSERT_EQUAL_INT(0, word_already_on_board(B23, word17));

}

void test_word_intersects_word_on_board(void)
{
  int B29[15][15] = { 0 };
  struct Pos pos28 = { 3, 7 };
  struct Word word28 = { "hello", HOR, pos28 };
  insert_word(B29, word28);
  struct Pos pos29 = { 7, 8 };
  struct Word word29 = { "organic", VER, pos29 };

  TEST_ASSERT_EQUAL_INT(0, word_intersects_word_on_board(B29, word29));
    // new word must intersect with word on board

  // ---------------------------------------------------------

  int B13[15][15] = { 0 };
  struct Pos pos4 = { 3, 7 };
  struct Word word4 = { "hello", HOR, pos4 };
  insert_word(B13, word4);
  struct Pos pos5 = { 7, 7 };
  struct Word word5 = { "organic", VER, pos5 };

  TEST_ASSERT_EQUAL_INT(1, word_intersects_word_on_board(B13, word5));

  // // --------------------------------------------------------

  int B15[15][15] = { 0 };
  struct Pos pos6 = { 7, 7 };
  struct Word word6 = { "hello", VER, pos6 };
  insert_word(B15, word6);
  struct Pos pos7 = { 7, 11 };
  struct Word word7 = { "organic", HOR, pos7 };

  TEST_ASSERT_EQUAL_INT(1, word_intersects_word_on_board(B15, word7));

  // // -----------------------------------------------------------

  int B17[15][15] = { 0 };
  struct Pos pos8 = { 6, 7 };
  struct Word word8 = { "ant", HOR, pos8 };
  insert_word(B17, word8);
  struct Pos pos9 = { 6, 7 };
  struct Word word9 = { "anteater", HOR, pos9 };

  TEST_ASSERT_EQUAL_INT(1, word_intersects_word_on_board(B17, word9));

  // // -------------------------------------------------------------

  int B19[15][15] = { 0 };
  struct Pos pos10 = { 7, 7 };
  struct Word word10 = { "ant", VER, pos10 };
  insert_word(B19, word10);
  struct Pos pos11 = { 7, 7 };
  struct Word word11 = { "anteater", VER, pos11 };

  TEST_ASSERT_EQUAL_INT(1, word_intersects_word_on_board(B19, word11));

  // // -----------------------------------------------------------------

  int B21[15][15] = { 0 };
  struct Pos pos12 = { 7, 7 };
  struct Word word12 = { "no", HOR, pos12 };
  insert_word(B21, word12);
  struct Pos pos13 = { 8, 6 };
  struct Word word13 = { "tomato", VER, pos13 };

  TEST_ASSERT_EQUAL_INT(1, word_intersects_word_on_board(B21, word13));

  // // ------------------------------------------------------------------

  int B23[15][15] = { 0 };
  struct Pos pos14 = { 7, 5 };
  struct Word word14 = { "farms", VER, pos14 };
  insert_word(B23, word14);
  struct Pos pos15 = { 5, 7 };
  struct Word word15 = { "horn", HOR, pos15 };
  insert_word(B23, word15);
  struct Pos pos16 = { 5, 9 };
  struct Word word16 = { "paste", HOR, pos16 };
  insert_word(B23, word16);
  struct Pos pos17 = { 7, 8 };
  struct Word word17 = { "mob", HOR, pos17 };

  TEST_ASSERT_EQUAL_INT(1, word_intersects_word_on_board(B23, word17));
}

void test_word_covers_tile(void)
{
  int B1[15][15] = { 0 };
  struct Pos pos1 = { 7, 7 };
  struct Word word1 = { "Always", HOR, pos1};
  insert_word(B1, word1);
  struct Pos pos2 = { 8, 7 };
  struct Word word2 = { "organic", VER, pos2 };

  TEST_ASSERT_EQUAL_INT(1, word_covers_tile(B1, word2));

  int B3[15][15] = { 0 };
  struct Pos pos3 = { 7, 7 };
  struct Word word3 = { "Bottom", HOR, pos3 };
  insert_word(B3, word3);
  struct Pos pos4 = { 8, 7 };
  struct Word word4 = { "organic", VER, pos4 };

  TEST_ASSERT_EQUAL_INT(0, word_covers_tile(B3, word4));
}

void test_word_crosses_center_tile(void)
{
  struct Pos pos1 = { 7, 7 };
  struct Word word1 = { "A", HOR, pos1 };
  TEST_ASSERT_EQUAL_INT(1, word_crosses_center_tile(word1));

  struct Pos pos2 = { 7, 7 };
  struct Word word2 = { "HELLO", HOR, pos2};
  TEST_ASSERT_EQUAL_INT(1, word_crosses_center_tile(word2));

  struct Pos pos3 = { 3, 7 };
  struct Word word3 = { "HELLO", HOR, pos3};
  TEST_ASSERT_EQUAL_INT(1, word_crosses_center_tile(word3));

  struct Pos pos4 = { 7, 3 };
  struct Word word4 = { "HELLO", VER, pos4};
  TEST_ASSERT_EQUAL_INT(1, word_crosses_center_tile(word4));

  struct Pos pos5 = { 2, 7 };
  struct Word word5 = { "HELLO", HOR, pos5};
  TEST_ASSERT_EQUAL_INT(0, word_crosses_center_tile(word5));

  struct Pos pos6 = { 7, 2 };
  struct Word word6 = { "HELLO", VER, pos6};
  TEST_ASSERT_EQUAL_INT(0, word_crosses_center_tile(word6));
}

void test_player_moves_updates_board_and_player(void)
{
  int B1[15][15] = { 0 };      // checked Board and Played
  struct Player Player1;
  int temp1[] = { 1, 2, 3, 4, 5, 6, 7 };
  memcpy(Player1.hand, temp1, sizeof temp1);
  Player1.points = 0;

  int B2[15][15] = { 0 };     // expected Board and Player
  struct Pos pos1 = { 7, 7 };
  struct Word word1 = { "A", HOR, pos1 };
  insert_word(B2, word1);
  struct Player Player2;
  int temp2[] = { 0, 2, 3, 4, 5, 6, 7 };
  memcpy(Player2.hand, temp2, sizeof temp2);
  Player2.points = 2;

  Player1 = player_moves(Player1, B1, word1); // Player1 plays first move; valid word in valid pos
                                                  //    Must cross the center tile.
                                                  //    Receives double points
  TEST_ASSERT_EQUAL_INT(Player1.points, Player2.points);
  TEST_ASSERT_EQUAL_INT_ARRAY(Player1.hand, Player2.hand, 7);
  TEST_ASSERT_EQUAL_INT_ARRAY(B1, B2, 15*15);

  // -------------------------------------------------------

  int B9[15][15] = { 0 };
  struct Player Player9;
  int temp9[] = {8, 5, 12, 12, 15, 1, 2};
  memcpy(Player9.hand, temp9, sizeof temp9);
  Player9.points = 0;

  int B10[15][15] = { 0 };
  struct Pos pos2 = { 3, 7 };
  struct Word word2 = { "hello", HOR, pos2 };
  insert_word(B10, word2);
  struct Player Player10;
  int temp10[] = {0, 0, 0, 0, 0, 1, 2};
  memcpy(Player10.hand, temp10, sizeof temp10);
  Player10.points = 24; // H = 4 (* 2 [x = 3, y = 7]), E = 1, L = 1, L = 1,
                        // 0 = 1; [x = 7, y = 7]: word double score

  Player9 = player_moves(Player9, B9, word2); // Player 9 moves first
                                                           // Places valid multi letter word
                                                           // Horizontally, crossing center
  TEST_ASSERT_EQUAL_INT(Player9.points, Player10.points);
  TEST_ASSERT_EQUAL_INT_ARRAY(Player9.hand, Player10.hand, 7);
  TEST_ASSERT_EQUAL_INT_ARRAY(B9, B10, 15*15);

  // -------------------------------------------------------

  int B11[15][15] = { 0 };
  struct Player Player11;
  memcpy(Player11.hand, temp9, sizeof temp9);
  Player11.points = 0;

  int B12[15][15] = { 0 };
  struct Pos pos3 = { 7, 4 };
  struct Word word3 = { "HELLO", VER, pos3 };
  insert_word(B12, word3);
  struct Player Player12;
  memcpy(Player12.hand, temp10, sizeof temp10);
  Player12.points = 16; // H = 4, E = 1, L = 1, L = 1, O = 1; word double score (center tile)

  Player11 = player_moves(Player11, B11, word3);  // Player 11 moves first
                                                               // Places valid multi letter word
                                                               // Vertically crossing center tile
  TEST_ASSERT_EQUAL_INT(Player11.points, Player12.points);
  TEST_ASSERT_EQUAL_INT_ARRAY(Player11.hand, Player12.hand, 7);
  TEST_ASSERT_EQUAL_INT_ARRAY(B11, B12, 15*15);

  // ---------------------------------------------------------

  int B13[15][15] = { 0 };
  struct Pos pos4 = { 3, 7 };
  struct Word word4 = { "hello", HOR, pos4 };
  insert_word(B13, word4);
  struct Player Player13;
  int temp13[] = { 3, 1, 18, 7, 9, 14, 15};
  memcpy(Player13.hand, temp13, sizeof temp13);
  Player13.points = 0;

  int B14[15][15] = { 0 };
  insert_word(B14, word4);
  struct Pos pos5 = { 7, 7 };
  struct Word word5 = { "organic", VER, pos5 };
  insert_word(B14, word5);
  struct Player Player14;
  int temp14[] = { 0, 0, 0, 0, 0, 0, 15 };
  memcpy(Player14.hand, temp14, sizeof temp14);
  Player14.points = 11; // O = 1, R = 1, G = 2, A = 1, N = 1 * 2, I = 1, C = 3

  Player13 = player_moves(Player13, B13, word5); // Player 13 moves second
                                                                // places a valid word
                                                                // perpandicular to a horizontal
                                                                // word on board
  TEST_ASSERT_EQUAL_INT(Player13.points, Player14.points);
  TEST_ASSERT_EQUAL_INT_ARRAY(Player13.hand, Player14.hand, 7);
  TEST_ASSERT_EQUAL_INT_ARRAY(B13, B14, 15*15);

  // --------------------------------------------------------

  int B15[15][15] = { 0 };
  struct Pos pos6 = { 7, 7 };
  struct Word word6 = { "hello", VER, pos6 };
  insert_word(B15, word6);
  struct Player Player15;
  memcpy(Player15.hand, temp13, sizeof temp13);
  Player15.points = 0;

  int B16[15][15] = { 0 };
  insert_word(B16, word6);
  struct Pos pos7 = { 7, 11 };
  struct Word word7 = { "organic", HOR, pos7 };
  insert_word(B16, word7);
  struct Player Player16;
  memcpy(Player16.hand, temp14, sizeof temp14);
  Player16.points = 20;// O = 1, R = 1, G = 2, A = 1, N = 1, I = 1, C = 3; WS * 2

  Player15 = player_moves(Player15, B15, word7);  // Player 15 moves second
                                                                  // places a valid word
                                                                  // perpandicular to a vertical
                                                                  // word on board
  TEST_ASSERT_EQUAL_INT(Player15.points, Player16.points);
  TEST_ASSERT_EQUAL_INT_ARRAY(Player15.hand, Player16.hand, 7);
  TEST_ASSERT_EQUAL_INT_ARRAY(B15, B16, 15*15);

  // -----------------------------------------------------------

  int B17[15][15] = { 0 };
  struct Pos pos8 = { 6, 7 };
  struct Word word8 = { "ant", HOR, pos8 };
  insert_word(B17, word8);
  struct Player Player17;
  int temp17[] = { 18, 5, 1, 5, 20, 2, 20 };
  memcpy(Player17.hand, temp17, sizeof temp17);
  Player17.points = 0;

  int B18[15][15] = { 0 };
  struct Pos pos9 = { 6, 7 };
  struct Word word9 = { "anteater", HOR, pos9 };
  insert_word(B18, word9);
  struct Player Player18;
  int temp18[] = { 0, 0, 0, 0, 0, 2, 20 };
  memcpy(Player18.hand, temp18, sizeof temp18);
  Player18.points = 9; // A = 1, N = 1, T = 1, E = 1, A = 1, T = 1 * 2, E = 1, R = 1

  Player17 = player_moves(Player17, B17, word9); // Player17 moves second
                                                                 // forms a valid word by
                                                                 // extending a horizontal
                                                                 // word on board
  TEST_ASSERT_EQUAL_INT(Player17.points, Player18.points);
  TEST_ASSERT_EQUAL_INT_ARRAY(Player17.hand, Player18.hand, 7);
  TEST_ASSERT_EQUAL_INT_ARRAY(B17, B18, 15*15);

  // -------------------------------------------------------------

  int B19[15][15] = { 0 };
  struct Pos pos10 = { 7, 7 };
  struct Word word10 = { "ant", VER, pos10 };
  insert_word(B19, word10);
  struct Player Player19;
  memcpy(Player19.hand, temp17, sizeof temp17);
  Player19.points = 0;

  int B20[15][15] = { 0 };
  struct Pos pos11 = { 7, 7 };
  struct Word word11 = { "anteater", VER, pos11 };
  insert_word(B20, word11);
  struct Player Player20;
  memcpy(Player20.hand, temp18, sizeof temp18);
  Player20.points = 27; // A = 1, N = 1, T = 1, E = 1, A = 1 * 2, T = 1, E = 1, R = 1; WS * 3

  Player19 = player_moves(Player19, B19, word11); // Player19 moves second
                                                                 // forms a valid word by
                                                                 // extending a vertical
                                                                 // word on board
  TEST_ASSERT_EQUAL_INT(Player19.points, Player20.points);
  TEST_ASSERT_EQUAL_INT_ARRAY(Player19.hand, Player20.hand, 7);
  TEST_ASSERT_EQUAL_INT_ARRAY(B19, B20, 15*15);

  // -----------------------------------------------------------------

  int B21[15][15] = { 0 };
  struct Pos pos12 = { 7, 7 };
  struct Word word12 = { "no", HOR, pos12 };
  insert_word(B21, word12);
  struct Player Player21;
  int temp21[] = { 20, 15, 13, 1, 20, 15, 18 };
  memcpy(Player21.hand, temp21, sizeof temp21);
  Player21.points = 0;

  int B22[15][15] = { 0 };
  insert_word(B22, word12);
  struct Pos pos13 = { 9, 7 };
  struct Word word13 = { "tomato", VER, pos13 };
  insert_word(B22, word13);
  struct Player Player22;
  int temp22[] = { 0, 0, 0, 0, 0, 0, 18 };
  memcpy(Player22.hand, temp22, sizeof temp22);
  Player22.points = 17; // N = 1; O = 1; T = 1
                      // T = 1; O = 1; M = 3 * 3; A = 1; T = 1; O = 1

  Player21 = player_moves(Player21, B21, word13); // Player 21 moves second
                                                               // places a valid move and
                                                               // extends a word already on
                                                               // the board
  TEST_ASSERT_EQUAL_INT(Player21.points, Player22.points);
  TEST_ASSERT_EQUAL_INT_ARRAY(Player21.hand, Player22.hand, 7);
  TEST_ASSERT_EQUAL_INT_ARRAY(B21, B22, 15*15);

  // ------------------------------------------------------------------

  int B23[15][15] = { 0 };
  struct Pos pos14 = { 7, 5 };
  struct Word word14 = { "farms", VER, pos14 };
  insert_word(B23, word14);
  struct Pos pos15 = { 5, 7 };
  struct Word word15 = { "horn", HOR, pos15 };
  insert_word(B23, word15);
  struct Pos pos16 = { 5, 9 };
  struct Word word16 = { "paste", HOR, pos16 };
  insert_word(B23, word16);
  struct Player Player23;
  int temp23[] = { 13, 15, 2, 3, 5, 1, 16 };
  memcpy(Player23.hand, temp23, sizeof temp23);
  Player23.points = 30;

  int B24[15][15] = { 0 };
  insert_word(B24, word14);
  insert_word(B24, word15);
  insert_word(B24, word16);
  struct Pos pos17 = { 7, 8 };
  struct Word word17 = { "mob", HOR, pos17 };
  insert_word(B24, word17);
  struct Player Player24;
  int temp24[] = { 13, 0, 0, 3, 5, 1, 16};
  memcpy(Player24.hand, temp24, sizeof temp24);
  Player24.points = 30 + 16; // M = 3; O = 1 * 2; B = 3;
                             // N = 1; O = 1; T = 1 * 2;
                             // B = 3; E = 1;

  Player23 = player_moves(Player23, B23, word17);

  TEST_ASSERT_EQUAL_INT(Player23.points, Player24.points);
  TEST_ASSERT_EQUAL_INT_ARRAY(Player23.hand, Player24.hand, 7);
  TEST_ASSERT_EQUAL_INT_ARRAY(B23, B24, 15*15);

}

void test_update_points_awards_returns_correct_no_points(void)
{
  int B1[15][15] = { 0 };
  int points1 = 0;

  int B2[15][15] = { 0 };
  int points2 = 2;

  struct Pos pos1 = { 7, 7 };
  struct Word word1 = { "A", HOR, pos1 };
  points1 = update_points(points1, B1, word1);

  TEST_ASSERT_EQUAL_INT(points1, points2);
  TEST_ASSERT_EQUAL_INT_ARRAY(B1, B2, 15*15);

  // -------------------------------------------------------------------

  int B3[15][15] = { 0 };
  int points3 = 0;

  int B4[15][15] = { 0 };
  int points4 = 24; // H = 4 (* 2 [x = 3, y = 7]), E = 1, L = 1, L = 1,
                //         0 = 1; [x = 7, y = 7]: word double score

  struct Pos pos2 = { 3, 7 };
  struct Word word2 = { "HELLO", HOR, pos2 };
  points3 = update_points(points3, B3, word2);

  TEST_ASSERT_EQUAL_INT(points3, points4);
  TEST_ASSERT_EQUAL_INT_ARRAY(B3, B4, 15*15);

  // --------------------------------------------------------------------

  int B5[15][15] = { 0 };
  int points5 = 0;

  int B6[15][15] = { 0 };
  int points6 = 16; // H = 4, E = 1, L = 1, L = 1, O = 1; word double score (center tile)

  struct Pos pos3 = { 7, 4 };
  struct Word word3 = { "hello", VER, pos3 };
  points5 = update_points(points5, B5, word3);

  TEST_ASSERT_EQUAL_INT(points5, points6);
  TEST_ASSERT_EQUAL_INT_ARRAY(B5, B6, 15*15);

  // --------------------------------------------------------------------

  int B7[15][15] = { 0 };
  struct Pos pos4 = { 3, 7 };
  struct Word word4 = { "hello", HOR, pos4 };
  insert_word(B7, word4);
  int points7 = 0;

  int B8[15][15] = { 0 };
  insert_word(B8, word4);
  int points8 = 11; // O = 1, R = 1, G = 2, A = 1, N = 1 * 2, I = 1, C = 3

  struct Pos pos5 = { 7, 7 };
  struct Word word5 = { "organic", VER, pos5 };
  points7 = update_points(points7, B7, word5);

  TEST_ASSERT_EQUAL_INT(points7, points8);
  TEST_ASSERT_EQUAL_INT_ARRAY(B7, B8, 15*15);

  // ----------------------------------------------------------------------

  int B9[15][15] = { 0 };
  struct Pos pos6 = { 7, 7 };
  struct Word word6 = { "ant", VER, pos6 };
  insert_word(B9, word6);
  int points9 = 0;

  int B10[15][15] = { 0 };
  insert_word(B10, word6);
  int points10 = 27; // A = 1, N = 1, T = 1, E = 1, A = 1 * 2, T = 1, E = 1, R = 1; WS * 3

  struct Pos pos7 = { 7, 7 };
  struct Word word7 = { "anteater", VER, pos7 };
  points9 = update_points(points9, B9, word7);

  TEST_ASSERT_EQUAL_INT(points9, points10);
  TEST_ASSERT_EQUAL_INT_ARRAY(B9, B10, 15*15);

  // ------------------------------------------------------------------------

  int B11[15][15] = { 0 };
  struct Pos pos8 = { 7, 7 };
  struct Word word8 = { "no", HOR, pos8 };
  insert_word(B11, word8);
  int points11 = 0;

  int B12[15][15] = { 0 };
  insert_word(B12, word8);
  int points12 = 17; // N = 1; O = 1; T = 1
                      // T = 1; O = 1; M = 3 * 3; A = 1; T = 1; O = 1

  struct Pos pos9 = { 9, 7 };
  struct Word word9 = { "tomato", VER, pos9 };
  points11 = update_points(points11, B11, word9);

  TEST_ASSERT_EQUAL_INT(points11, points12);
  TEST_ASSERT_EQUAL_INT_ARRAY(B11, B12, 15*15);

  // ------------------------------------------------------------------------

  int B13[15][15] = { 0 };
  struct Pos pos10 = { 7, 5 };
  struct Word word10 = { "farms", VER, pos10 };
  insert_word(B13, word10);
  struct Pos pos11 = { 5, 7 };
  struct Word word11 = { "horn", HOR, pos11 };
  insert_word(B13, word11);
  struct Pos pos12 = { 5, 9 };
  struct Word word12 = { "paste", HOR, pos12 };
  insert_word(B13, word12);
  int points13 = 30;

  int B14[15][15] = { 0 };
  insert_word(B14, word10);
  insert_word(B14, word11);
  insert_word(B14, word12);
  int points14 = 30 + 16; // M = 3; O = 1 * 2; B = 3;
                             // N = 1; O = 1; T = 1;
                             // B = 3; E = 1;

  struct Pos pos13 = { 7, 8 };
  struct Word word13 = { "mob", HOR, pos13 };
  points13 = update_points(points13, B13, word13);

  TEST_ASSERT_EQUAL_INT(points13, points14);
  TEST_ASSERT_EQUAL_INT_ARRAY(B13, B14, 15*15);

}

void test_points_for_word_returns_appropriate_points_for_word(void)
{
  int B1[15][15] = { 0 };
  int B2[15][15] = { 0 };

  struct Pos pos1 = { 7, 7 };
  struct Word word1 = { "A", HOR, pos1 };
  int points1 = points_for_word(B1, word1);

  TEST_ASSERT_EQUAL_INT(points1, 2);
  TEST_ASSERT_EQUAL_INT_ARRAY(B1, B2, 15*15);

  // -------------------------------------------------------------------

  int B3[15][15] = { 0 };
  int B4[15][15] = { 0 };

  struct Pos pos2 = { 3, 7 };
  struct Word word2 = { "HELLO", HOR, pos2 };
  int points2 = points_for_word(B3, word2);
                                            // H = 4 (* 2 [x = 3, y = 7]), E = 1, L = 1,
                                            //   L = 1, 0 = 1; [x = 7, y = 7]: word
                                            //   double score

  TEST_ASSERT_EQUAL_INT(points2, 24);
  TEST_ASSERT_EQUAL_INT_ARRAY(B3, B4, 15*15);

  // // --------------------------------------------------------------------

  int B5[15][15] = { 0 };
  int B6[15][15] = { 0 };

  struct Pos pos3 = { 7, 4 };
  struct Word word3 = { "hello", VER, pos3 };
  int points3 = points_for_word(B5, word3);
                      // H = 4, E = 1, L = 1, L = 1, O = 1; word double score (center tile)
  TEST_ASSERT_EQUAL_INT(points3, 16);
  TEST_ASSERT_EQUAL_INT_ARRAY(B5, B6, 15*15);

  // // --------------------------------------------------------------------

  int B7[15][15] = { 0 };
  struct Pos pos4 = { 3, 7 };
  struct Word word4 = { "hello", HOR, pos4 };
  insert_word(B7, word4);
  int B8[15][15] = { 0 };
  insert_word(B8, word4);

  struct Pos pos5 = { 7, 7 };
  struct Word word5 = { "organic", VER, pos5 };
  int points4 = points_for_word(B7, word5);
                    // O = 1, R = 1, G = 2, A = 1, N = 1 * 2, I = 1, C = 3
  TEST_ASSERT_EQUAL_INT(points4, 11);
  TEST_ASSERT_EQUAL_INT_ARRAY(B7, B8, 15*15);

  // // ----------------------------------------------------------------------

  int B9[15][15] = { 0 };
  struct Pos pos6 = { 7, 7 };
  struct Word word6 = { "ant", VER, pos6 };
  insert_word(B9, word6);
  int B10[15][15] = { 0 };
  insert_word(B10, word6);

  struct Pos pos7 = { 7, 7 };
  struct Word word7 = { "anteater", VER, pos7 };
  int points5 = points_for_word(B9, word7);
                // A = 1, N = 1, T = 1, E = 1, A = 1 * 2, T = 1, E = 1, R = 1; WS * 3
  TEST_ASSERT_EQUAL_INT(points5, 27);
  TEST_ASSERT_EQUAL_INT_ARRAY(B9, B10, 15*15);

  // // ------------------------------------------------------------------------

  int B11[15][15] = { 0 };
  struct Pos pos8 = { 7, 7 };
  struct Word word8 = { "no", HOR, pos8 };
  insert_word(B11, word8);
  int B12[15][15] = { 0 };
  insert_word(B12, word8);

  struct Pos pos9 = { 9, 7 };
  struct Word word9 = { "tomato", VER, pos9 };
  int points6 = points_for_word(B11, word9);
                // T = 1; O = 1; M = 3 * 3; A = 1; T = 1; O = 1
  TEST_ASSERT_EQUAL_INT(points6, 14);
  TEST_ASSERT_EQUAL_INT_ARRAY(B11, B12, 15*15);

  // // ------------------------------------------------------------------------

  int B13[15][15] = { 0 };
  struct Pos pos10 = { 7, 5 };
  struct Word word10 = { "farms", VER, pos10 };
  insert_word(B13, word10);
  struct Pos pos11 = { 5, 7 };
  struct Word word11 = { "horn", HOR, pos11 };
  insert_word(B13, word11);
  struct Pos pos12 = { 5, 9 };
  struct Word word12 = { "paste", HOR, pos12 };
  insert_word(B13, word12);
  int B14[15][15] = { 0 };
  insert_word(B14, word10);
  insert_word(B14, word11);
  insert_word(B14, word12);

  struct Pos pos13 = { 7, 8 };
  struct Word word13 = { "mob", HOR, pos13 };
  int points7 = points_for_word(B13, word13);

  TEST_ASSERT_EQUAL_INT(points7, 8);
  TEST_ASSERT_EQUAL_INT_ARRAY(B13, B14, 15*15);

}

void test_get_perpendicular_dir_returns_opposite_dir(void)
{
  int perp1[2];
  get_perpendicular_dir(perp1, HOR);
  TEST_ASSERT_EQUAL_INT_ARRAY(perp1, VER, 2);

  int perp2[2];
  get_perpendicular_dir(perp2, VER);
  TEST_ASSERT_EQUAL_INT_ARRAY(perp2, HOR, 2);
}

void test_update_hand_removes_used_tiles_from_hand(void)
{
  int B1[15][15] = { 0 };      // checked Board and Played
  int hand1[] = {1, 2, 3, 4, 5, 6, 7};

  int B2[15][15] = { 0 };     // expected Board and Player
  int hand2[] = {0, 2, 3, 4, 5, 6, 7};

  struct Pos pos1 = { 7, 7 };
  struct Word word1 = { "A", HOR, pos1 };
  update_hand(hand1, B1, word1); // place a single letter on an empty board

  TEST_ASSERT_EQUAL_INT_ARRAY(hand1, hand2, 7);
  TEST_ASSERT_EQUAL_INT_ARRAY(B1, B2, 15*15);

  // -------------------------------------------------------------------

  int B3[15][15] = { 0 };
  int hand3[] = { 8, 5, 12, 12, 15, 1, 2 };

  int B4[15][15] = { 0 };
  int hand4[] = { 0, 0, 0, 0, 0, 1, 2 };

  struct Pos pos2 = { 3, 7 };
  struct Word word2 = { "HELLO", HOR, pos2 };
  update_hand(hand3, B3, word2); // place a 5 letter word horizontally
                                              // on empty board
  TEST_ASSERT_EQUAL_INT_ARRAY(hand3, hand4, 7);
  TEST_ASSERT_EQUAL_INT_ARRAY(B3, B4, 15*15);

  // --------------------------------------------------------------------

  int B5[15][15] = { 0 };
  int hand5[] = { 8, 5, 12, 12, 15, 1, 2 };

  int B6[15][15] = { 0 };
  int hand6[] = { 0, 0, 0, 0, 0, 1, 2 };

  struct Pos pos3 = { 7, 4 };
  struct Word word3 = { "HELLO", VER, pos3 };
  update_hand(hand5, B5, word3); // place a 5 letter word vertically
                                              // on empty board

  TEST_ASSERT_EQUAL_INT_ARRAY(hand5, hand6, 7);
  TEST_ASSERT_EQUAL_INT_ARRAY(B5, B6, 15*15);

  // ---------------------------------------------------------------------

  int B7[15][15] = { 0 };
  struct Pos pos4 = { 6, 7 };
  struct Word word4 = { "ant", HOR, pos4 };
  insert_word(B7, word4);
  int hand7[] = { 18, 2, 5, 20, 1, 5, 20 };

  int B8[15][15] = { 0 };
  insert_word(B8, word4);;
  int hand8[] = { 0, 2, 0, 0, 0, 0, 20 };

  struct Pos pos5 = { 6, 7 };
  struct Word word5 = { "anteater", HOR, pos5 };
  update_hand(hand7, B7, word5);

  TEST_ASSERT_EQUAL_INT_ARRAY(hand7, hand8, 7);
  TEST_ASSERT_EQUAL_INT_ARRAY(B7, B8, 15*15);

  // ----------------------------------------------------------------------

  int B9[15][15] = { 0 };
  struct Pos pos6 = { 7, 7 };
  struct Word word6 = { "ant", VER, pos6 };
  insert_word(B9, word6);
  int hand9[] = { 18, 5, 1, 5, 20, 2, 20 };

  int B10[15][15] = { 0 };
  insert_word(B10, word6);
  int hand10[] = { 0, 0, 0, 0, 0, 2, 20 };

  struct Pos pos7 = { 7, 7 };
  struct Word word7 = { "anteater", VER, pos7 };
  update_hand(hand9, B9, word7);

  TEST_ASSERT_EQUAL_INT_ARRAY(hand9, hand10, 7);
  TEST_ASSERT_EQUAL_INT_ARRAY(B9, B10, 15*15);

  // ---------------------------------------------------------------

  int B11[15][15] = { 0 };
  struct Pos pos8 = { 7, 7 };
  struct Word word8 = { "no", HOR, pos8 };
  insert_word(B11, word8);
  int hand11[] = { 20, 15, 18, 13, 1, 20, 15 };

  int B12[15][15] = { 0 };
  insert_word(B12, word8);
  int hand12[] = { 0, 0, 18, 0, 0, 0, 0 };

  struct Pos pos9 = { 9, 7 };
  struct Word word9 = { "tomato", VER, pos9 };
  update_hand(hand11, B11, word9);

  TEST_ASSERT_EQUAL_INT_ARRAY(hand11, hand12, 7);
  TEST_ASSERT_EQUAL_INT_ARRAY(B11, B12, 15*15);
}

void test_remove_from_hand_removes_tile_from_hand(void)
{
  int hand1[] = { 1, 2, 3, 4, 5, 6, 7 };
  remove_from_hand(hand1, 1);
  int hand2[] = { 0, 2, 3, 4, 5, 6, 7 };
  TEST_ASSERT_EQUAL_INT_ARRAY(hand1, hand2, 7);

  int hand3[] = { 1, 2, 3, 4, 5, 6, 7 };
  remove_from_hand(hand3, 4);
  int hand4[] = { 1, 2, 3, 0, 5, 6, 7 };
  TEST_ASSERT_EQUAL_INT_ARRAY(hand3, hand4, 7);
}

void test_insert_tile_should_insert_tile_into_board_at_pos_x_y_if_pos_blank(void)
{
  int B1[15][15] = { 0 };
  int board[15][15] = { 0 };
  TEST_ASSERT_EQUAL_INT_ARRAY(board, B1, 15*15);

  B1[0][0] = 4;
  insert_tile(board, 0, 0, 4);  // insert a tile into a blank board
  TEST_ASSERT_EQUAL_INT_ARRAY(board, B1, 15*15);

  B1[10][5] = 3;
  insert_tile(board, 5, 10, 3);  // insert a tile in a pos with different x and y vals
  TEST_ASSERT_EQUAL_INT_ARRAY(board, B1, 15*15);

  insert_tile(board, 5, 10, 3); // insert a tile in a non-blank spot
  TEST_ASSERT_EQUAL_INT_ARRAY(board, B1, 15*15);
}

void text_char_to_tile_produces_the_correct_tile(void)
{
  TEST_ASSERT_EQUAL_INT(1, char_to_tile('A'));
  TEST_ASSERT_EQUAL_INT(20, char_to_tile('T'));
  TEST_ASSERT_EQUAL_INT(5, char_to_tile('e'));
  TEST_ASSERT_EQUAL_INT(27, char_to_tile(' '));
  TEST_ASSERT_EQUAL_INT(0, char_to_tile('@'));
}

void test_insert_word_should_insert_word_into_board(void)
{
  int B1[15][15] = { 0 };
  int board[15][15] = { 0 };
  TEST_ASSERT_EQUAL_INT_ARRAY(board, B1, 15*15);

  B1[7][7] = 1;
  struct Pos pos1 = { 7, 7 };
  struct Word word1 = { "A", VER, pos1 };
  insert_word(board, word1);  // one letter at the center of board
  TEST_ASSERT_EQUAL_INT_ARRAY(board, B1, 15*15);

  B1[3][4] = 1;
  struct Pos pos2 = { 4, 3 };
  struct Word word2 = { "a", VER, pos2 };
  insert_word(board, word2); // one letter, lowercase (check case insensitive)
  TEST_ASSERT_EQUAL_INT_ARRAY(board, B1, 15*15);

  B1[0][0] = 8;
  B1[0][1] = 5;
  B1[0][2] = 18;
  B1[0][3] = 18;
  B1[0][4] = 9;
  B1[0][5] = 14;
  B1[0][6] = 7;
  struct Pos pos3 = { 0, 0 };
  struct Word word3 = { "HERRING", HOR, pos3 };
  insert_word(board, word3); // word with many letters, horizontal
  TEST_ASSERT_EQUAL_INT_ARRAY(board, B1, 15*15);

  B1[0][0] = 8;
  B1[1][0] = 1;
  B1[2][0] = 20;
  struct Pos pos4 = { 0, 0 };
  struct Word word4 = { "HAT", VER, pos4 };
  insert_word(board, word4); // vertical word, first letter already on board
  TEST_ASSERT_EQUAL_INT_ARRAY(board, B1, 15*15);
}

void test_get_word_from_board_should_return_a_word_on_the_board(void)
{
  struct Pos pos1 = { 4, 5 };
  struct Word word1 = { "a", VER, pos1 };
  insert_word(board, word1);
  struct Word word2 = get_word_from_board(board, 4, 5, VER);
  TEST_ASSERT_EQUAL_STRING("A", word2.word);
  TEST_ASSERT_EQUAL_INT(4, word2.pos.x);
  TEST_ASSERT_EQUAL_INT(5, word2.pos.y);

  struct Pos pos3 = { 0, 14 };
  struct Word word3 = { "carpet", HOR, pos3 };
  insert_word(board, word3);
  struct Word word4 = get_word_from_board(board, 0, 14, HOR);
  TEST_ASSERT_EQUAL_STRING("CARPET", word4.word);
  TEST_ASSERT_EQUAL_INT(0, word4.pos.x);
  TEST_ASSERT_EQUAL_INT(14, word4.pos.y);

  struct Word word5 = get_word_from_board(board, 0, 14, VER);
  TEST_ASSERT_EQUAL_STRING("C", word5.word);
  TEST_ASSERT_EQUAL_INT(0, word5.pos.x);
  TEST_ASSERT_EQUAL_INT(14, word5.pos.y);

  struct Word word6 = get_word_from_board(board, 2, 14, HOR);
  TEST_ASSERT_EQUAL_STRING("CARPET", word6.word);
  TEST_ASSERT_EQUAL_INT(0, word6.pos.x);
  TEST_ASSERT_EQUAL_INT(14, word6.pos.y);

  struct Word word7 = get_word_from_board(board, 2, 14, VER);
  TEST_ASSERT_EQUAL_STRING("R", word7.word);
  TEST_ASSERT_EQUAL_INT(2, word7.pos.x);
  TEST_ASSERT_EQUAL_INT(14, word7.pos.y);

  struct Pos pos8 = { 9, 2 };
  struct Word word8 = { "zipper", VER, pos8 };
  insert_word(board, word8);
  struct Word word9 = get_word_from_board(board, 9, 2, VER);
  TEST_ASSERT_EQUAL_STRING("ZIPPER", word9.word);
  TEST_ASSERT_EQUAL_INT(9, word9.pos.x);
  TEST_ASSERT_EQUAL_INT(2, word9.pos.y);

  struct Word word10 = get_word_from_board(board, 9, 2, HOR);
  TEST_ASSERT_EQUAL_STRING("Z", word10.word);
  TEST_ASSERT_EQUAL_INT(9, word10.pos.x);
  TEST_ASSERT_EQUAL_INT(2, word10.pos.y);

  struct Word word11 = get_word_from_board(board, 9, 6, VER);
  TEST_ASSERT_EQUAL_STRING("ZIPPER", word11.word);
  TEST_ASSERT_EQUAL_INT(9, word11.pos.x);
  TEST_ASSERT_EQUAL_INT(2, word11.pos.y);

  struct Word word12 = get_word_from_board(board, 9, 6, HOR);
  TEST_ASSERT_EQUAL_STRING("E", word12.word);
  TEST_ASSERT_EQUAL_INT(9, word12.pos.x);
  TEST_ASSERT_EQUAL_INT(6, word12.pos.y);

  // insert_word(board, 0, 0, VER, "tree");
  // TEST_ASSERT_EQUAL_STRING("TREE", get_word_from_board(board, 0, 0, VER));
  // TEST_ASSERT_EQUAL_STRING("T", get_word_from_board(board, 0, 0, HOR));
  // TEST_ASSERT_EQUAL_STRING("TREE", get_word_from_board(board, 0, 3, VER));
  // TEST_ASSERT_EQUAL_STRING("E", get_word_from_board(board, 0, 3, HOR));
  //
  // insert_word(board, 0, 0, HOR, "tree");
  // TEST_ASSERT_EQUAL_STRING("TREE", get_word_from_board(board, 0, 0, HOR));
  // TEST_ASSERT_EQUAL_STRING("TREE", get_word_from_board(board, 3, 0, HOR));
  // TEST_ASSERT_EQUAL_STRING("E", get_word_from_board(board, 3, 0, VER));
  //
  // insert_word(board, 14, 11, VER, "RAIN");
  // TEST_ASSERT_EQUAL_STRING("RAIN", get_word_from_board(board, 14, 14, VER));
  // TEST_ASSERT_EQUAL_STRING("N", get_word_from_board(board, 14, 14, HOR));
  //
  // insert_word(board, 11, 14, HOR, "RAIN");
  // TEST_ASSERT_EQUAL_STRING("RAIN", get_word_from_board(board, 14, 14, HOR));
}

void test_board_is_blank_returns_1_only_if_board_is_blank(void)
{
  int B1[15][15] = { 0 };
  TEST_ASSERT_EQUAL_INT(1, board_is_blank(B1));

  int B2[15][15] = { 0 };
  struct Pos pos1 = { 7, 7 };
  struct Word word1 = { "A", VER, pos1 };
  insert_word(B2, word1);
  TEST_ASSERT_EQUAL_INT(0, board_is_blank(B2));

  int B3[15][15] = { 0 };
  struct Pos pos2 = { 7, 7 };
  struct Word word2 = { "A", VER, pos2 };
  insert_word(B3, word2);
  struct Pos pos3 = { 3, 3 };
  struct Word word3 = { "Hello", HOR, pos3};
  insert_word(B3, word3);
  TEST_ASSERT_EQUAL_INT(0, board_is_blank(B3));
}


int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(test_input_valid_format);
  RUN_TEST(test_input_to_word);
  RUN_TEST(test_move_is_valid_returns_true_only_if_move_is_valid);
  RUN_TEST(test_word_is_in_dictionary);
  RUN_TEST(test_player_can_play_word);
  RUN_TEST(test_tile_in_hand);
  RUN_TEST(test_word_connects_with_word_on_board);
  RUN_TEST(test_word_already_on_board);
  RUN_TEST(test_word_intersects_word_on_board);
  RUN_TEST(test_word_covers_tile);
  RUN_TEST(test_word_crosses_center_tile);
  RUN_TEST(test_remove_from_hand_removes_tile_from_hand);
  RUN_TEST(test_points_for_word_returns_appropriate_points_for_word);
  RUN_TEST(test_get_perpendicular_dir_returns_opposite_dir);
  RUN_TEST(test_player_moves_updates_board_and_player);
  RUN_TEST(test_update_hand_removes_used_tiles_from_hand);
  RUN_TEST(test_insert_tile_should_insert_tile_into_board_at_pos_x_y_if_pos_blank);
  RUN_TEST(test_insert_word_should_insert_word_into_board);
  RUN_TEST(text_char_to_tile_produces_the_correct_tile);
  RUN_TEST(test_get_word_from_board_should_return_a_word_on_the_board);
  RUN_TEST(test_update_points_awards_returns_correct_no_points);
  RUN_TEST(test_board_is_blank_returns_1_only_if_board_is_blank);

  return UNITY_END();
}
