#include <iostream>
#include <random>
#include <string>

auto random_number(int start, int end)
{
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist6(start, end);
  return dist6(rng);
}

int main() {
  bool finished = false;
  int player_go = 1;
  int num_matches = 27;

  std::string player1;
  std::cout << "Player 1's name: ";
  std::cin >> player1;

  std::string player2{"Computer"};

  player_go = random_number(1, 2);
  int choice = -1;
  bool has_passed = false;
  bool computer_passed = false;

  while(!finished)
  {
    std::cout << "\n There are " << num_matches << " matches remaining.\n";
    if(player_go == 1)
    {
      while(!has_passed)
        {
      std::cout << player1 << "'s turn (pick a number between 1 and 3): ";
      std::cin >> choice;
          if(choice <= 3 && choice >= 0)
          {
            has_passed = true;
          }
        }
      has_passed = false;
      if((num_matches - choice) <= 0)
      {
        std::cout << player2 << " wins!\n";
        finished = true;
      }
      else
      {
        num_matches -= choice;
      }
      player_go = 2;
      choice = -1;
    }
    else if(player_go == 2)
    {
      while(!computer_passed)
      {
      choice = random_number(1, 3);
      std::cout << "Computer's turn: " << choice << "\n";
        if(((num_matches - choice) >= 1) || num_matches == 1)
        {
          computer_passed = true;
        }
      }
      computer_passed = false;
      if((num_matches - choice) <= 0)
      {
        std::cout << player1 << " wins!\n";
        finished = true;
      }
      else
      {
        num_matches -= choice;
      }
      player_go = 1;
    }
  }
}
