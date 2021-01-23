#include <iostream>
#include <cstdint>
#include <limits>
#include <string>

using namespace std;
using u32 = uint32_t;

void enter_students  (u32 student_count, string* names, unsigned **test_scores);
void display_students(u32 student_count, string* names, unsigned **test_scores);

int main() {
   cout << "How many students are there?\n> ";
   u32 student_count;
   cin >> student_count;
   if (!cin.good()) {
      // there was an error and I don't care
      // just quit the program
      return 0;
   }
   cin.ignore(numeric_limits<streamsize>::max(), '\n');

   string *names     = new string[student_count];
   u32 **test_scores = new u32*[student_count];

   enter_students  (student_count, names, test_scores);
   display_students(student_count, names, test_scores);

   // this is where we free all the memory
   delete[] names;
   for (u32 student_idx = 0; student_idx < student_count; ++student_idx) {
      // have to free every single allocation that was done inside
      // this array in enter_students as well
      delete[] test_scores[student_idx];
   }
   delete[] test_scores;

   names = nullptr;
   test_scores = nullptr;
}

void enter_students(u32 student_count, string* names, unsigned **test_scores) {
   // count up to student_count and ask for a name
   // ask for how many tests
   // ask for each test score
   for (u32 student_idx = 0; student_idx < student_count; ++student_idx) {
      cout << "Enter a name for student " << student_idx + 1 << "\n> ";
      getline(cin, names[student_idx]);

      cout << "How many tests does " << names[student_idx] << " have?\n> ";
      u32 test_count = 0;
      cin >> test_count;
      cin.clear(); // ignore the error if it happens, who cares
      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      // allocate memory; add 1 for the length at the beginning
      test_scores[student_idx] = new u32[test_count + 1];
      // add the length at the beginning
      test_scores[student_idx][0] = test_count;

      // start at index 1 since index 0 is used for the length
      // it's okay to go one more on the test count so we use <=
      for (u32 test_idx = 1; test_idx <= test_count; ++test_idx) {
         cout << names[student_idx] << "'s test #" << test_idx << " score:\n> ";
         cin >> test_scores[student_idx][test_idx];
         cin.clear();
         cin.ignore(numeric_limits<streamsize>::max(), '\n');
      }
   }
}

void display_students(u32 student_count, string* names, u32 **test_scores) {
   // count up to student_count
   for (u32 student_idx = 0; student_idx < student_count; ++student_idx) {
      string &student_name = names[student_idx];
      u32* student_test_scores = test_scores[student_idx];

      // this is the number of tests this student has
      u32 test_count = student_test_scores[0];
      cout << student_name << " had " << test_count << " tests:\n";

      // print every test score
      for (u32 test_idx = 1; test_idx <= test_count; ++test_idx) {
         cout << student_test_scores[test_idx] << ", ";
      }
      cout << '\n';
   }
}
