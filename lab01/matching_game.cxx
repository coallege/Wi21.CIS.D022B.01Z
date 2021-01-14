#include <iostream>
#include <fstream>
#include <string>
using namespace std;

static const auto LENGTH = 3;
static const auto HEIGHT = 4;

void InitializeCards(int cards[][LENGTH]);
void ShowCards(int cards[][LENGTH], bool faceup[][LENGTH]);
bool GameIsWon(bool faceup[HEIGHT][LENGTH]);
int main();

int main() {
   // Step 1
   cout << "Welcome to my game!\n";
   cout << "Please enter your full name: ";

   string fullname;
   getline(cin, fullname);

   cout << "Find all matching pairs on the board!\n";

   // Step 2
   // remember, it's cards[y][x]
   // cards is an array that holds rows of numbers
   int cards[][LENGTH] = {
      {1, 1, 2},
      {2, 3, 3},
      {4, 4, 5},
      {5, 6, 6},
   };
   InitializeCards(cards);

   // Step 3
   // do this
   bool faceup[HEIGHT][LENGTH]{};

   // same as
   /*
   bool faceup[][LENGTH] = {
      {false, false, false},
      {false, false, false},
      {false, false, false},
      {false, false, false},
   };
   */

   // You don't want to do this because there's no guarantee
   // that this will all be zero or false
   /*
   bool faceup[HEIGHT][LENGTH];
   */

   int turns = 0;
   // Step 4
   // let's loop forever
   while (true) {
      // Step 4a
      ShowCards(cards, faceup);

      // Step 4b
      cout << "Please enter the coordinates for card A: ";
      int Ax;
      int Ay;
      cin >> Ax;
      cin >> Ay;

      cout << "Please enter the coordinates for card B: ";
      int Bx, By;
      cin >> Bx >> By;

      // what happens if the user enters a value that is
      // too large for the coordinates?
      // the program will break.
      // we have to check to make sure it's not
      if (
         // check lower bounds first
            Ax < 0
         || Ay < 0
         || Bx < 0
         || By < 0
         // check if x is too high
         || Ax >= LENGTH
         || Bx >= LENGTH
         // check if y is too high
         || Ay >= HEIGHT
         || By >= HEIGHT
      ) {
         cout << "Invalid coordinate pairs!\n";
         cout << "The lowest pair is (0, 0)\n";
         cout << "The highest pair is (" << LENGTH - 1 << ", " << HEIGHT - 1 << ")\n";
         cout << "Try again!\n";

         // ignore the error
         cin.clear();
         // ignore all input
         cin.ignore();

         // go back to the start of the loop
         continue;
      }

      // Step 4c
      int cardA = cards[Ay][Ax];
      int cardB = cards[By][Bx];
      // Flip the cards face up to show them
      faceup[Ay][Ax] = true;
      faceup[By][Bx] = true;
      if (cardA == cardB) {
         cout << "A match has been found!\n";
         // we don't need to flip them face down
         // since a match was found
      } else {
         // show the cards
         ShowCards(cards, faceup);
         // a match was not found,
         // flip them face down
         faceup[Ay][Ax] = false;
         faceup[By][Bx] = false;
      }

      // You want to keep track of the turns for what happens below
      turns++;

      // Step 4.5?
      if (GameIsWon(faceup)) {
         // write out to a file
         ofstream gamelog("gamelog.txt");
         gamelog << fullname << '\n';
         gamelog << "Status: Has won\n";
         gamelog << "Turns: " << turns << '\n';
         gamelog.close();

         // exit the program completely
         return 0;
      }

      // Step 5 or something
      cout << "Enter 'q' to quit or press any key to continue...\n";
      char quit_maybe;
      cin >> quit_maybe;
      if (quit_maybe == 'q') {
         ofstream gamelog("gamelog.txt");
         gamelog << fullname << '\n';
         gamelog << "Status: Hasn't won\n";
         gamelog << "Turns: " << turns << '\n';
         gamelog <<
            "Don't give up.\n"
            "If you give up, we'll send you back to gulag.\n";

         return 0;
      }
   }
}

void ShowCards(int cards[][LENGTH], bool faceup[][LENGTH]) {
   cout << ". 0 1 2\n";
   for (int y = 0; y < HEIGHT; y++) {
      cout << y << ' ';
      for (int x = 0; x < LENGTH; x++) {
         if (faceup[y][x]) {
            cout << cards[y][x] << ' ';
         } else {
            cout << "* ";
         }
      }
      // we are done printing the row, add a newline
      cout << '\n';
   }
}

/// So how do we know if the game is won?
/// It's if every card is turned face up
/// Aka if every value in faceup is true
bool GameIsWon(bool faceup[HEIGHT][LENGTH]) {
   for (int y = 0; y < HEIGHT; y++) {
      for (int x = 0; x < LENGTH; x++) {
         if (!faceup[y][x]) {
            return false;
         }
         // is the same as
         /*
         if (faceup[y][x] == false) {
           return false;
         }
         */
      }
   }

   // we did not exit the function in the loop.
   // therefore, every value was true.
   // we have won the game
   return true;
}

/// this was apparently already given but not to me
/// since I'm not actually in the class
/// you can ignore this function
void InitializeCards(int cards[][LENGTH]) {
   srand(time(nullptr));
   // we're going to swap stuff 10 times
   for (int i = 0; i < 10; i++) {
      int ax = rand() % LENGTH;
      int ay = rand() % HEIGHT;
      int bx = rand() % LENGTH;
      int by = rand() % HEIGHT;

      int a  = cards[ay][ax];
      int b  = cards[by][bx];

      // swap them
      cards[ay][ax] = b;
      cards[by][bx] = a;
   }
}
