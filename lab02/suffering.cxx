#include <cstdint>
#include <iostream>
#include <limits>
#include <stdint.h>
#include <string>
using namespace std;

void enter_students  (uint32_t student_count, string* names, unsigned **test_scores);
void display_students(uint32_t student_count, string* names, unsigned **test_scores);

int main() {
   cout << "How many students are there?\n> ";
   uint32_t student_count;
   cin >> student_count;
   cin.clear();
   cin.ignore(numeric_limits<streamsize>::max(), '\n');

   string *names = new string[student_count];
   uint32_t **test_scores = new uint32_t*[student_count];

   enter_students  (student_count, names, test_scores);
   display_students(student_count, names, test_scores);

   delete[] names;
   for (uint32_t student_idx = 0; student_idx < student_count; ++student_idx) {
      delete[] test_scores[student_idx];
   }
   delete[] test_scores;

   names = nullptr;
   test_scores = nullptr;
}

void enter_students(uint32_t student_count, string* names, unsigned **test_scores) {
   for (uint32_t student_idx = 0; student_idx < student_count; ++student_idx) {
      cout << "Enter a name for student " << student_idx + 1 << "\n> ";
      getline(cin, names[student_idx]);

      cout << "How many tests does " << names[student_idx] << " have?\n> ";
      uint32_t test_count;
      cin >> test_count;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      // + 1 for the length at the beginning
      test_scores[student_idx] = new uint32_t[test_count + 1];
      test_scores[student_idx][0] = test_count;

      for (uint32_t test_idx = 1; test_idx <= test_count; ++test_idx) {
         cout << names[student_idx] << "'s test #" << test_idx << " score:\n> ";
         cin >> test_scores[student_idx][test_idx];
         cin.clear();
         cin.ignore(numeric_limits<streamsize>::max(), '\n');
      }
   }
}

void display_students(uint32_t student_count, string* names, unsigned **test_scores) {
   for (uint32_t student_idx = 0; student_idx < student_count; ++student_idx) {
      uint32_t test_count = test_scores[student_idx][0];
      cout << names[student_idx] << " had " << test_count << " tests:\n";
      for (uint32_t test_idx = 1; test_idx <= test_count; ++test_idx) {
         cout << test_scores[student_idx][test_idx] << ", ";
      }
      cout << '\n';
   }
}
