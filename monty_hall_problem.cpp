// monty-hall problem
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>

auto get_random_number_1_to_(int x) -> int {
    typedef std::mt19937 rng_type;
std::uniform_int_distribution<rng_type::result_type> udist(0, 7);

rng_type rng;
  // seed rng first:
  //rng_type::result_type const seedval = get_seed(); // get this from somewhere
  //rng.seed(seedval);

  rng_type::result_type random_number = udist(rng);

  return random_number;
}

auto monty_hall_problem(auto guess)
{
    std::cout << "You guess was: " << guess << "\n";
    auto where_goat_is = [](auto guess_) {
        auto value = get_random_number_1_to_(3);
        if (value == guess_) {
            if ((value + 1) < 4) {
                return value + 1;
            } else {
                // value + 1 == 4
                return 1;
            }
        } else {
            return value;
        }
    }(guess);
    std::cout << "The goat is in position: " << where_goat_is << "\n";
    auto where_car_is = [](auto where_goat_is_)
    {
        auto first_thought = get_random_number_1_to_(2);
        if((where_goat_is_) == 1)
        {
            if(first_thought == 1)
            {
                return 2;
            }
            else
            {
                return 3;
            }
        }
        else if((where_goat_is_) == 2)
        {
            if(first_thought == 1)
            {
                return 1;
            }
            else
            {
                return 3;
            }
        }
        else if((where_goat_is_) == 3)
        {
            if(first_thought == 1)
            {
                return 1;
            }
            else{
                return 2;
            }
        }
        return 1;
    }(where_goat_is);
    std::cout << "Would you like to change your position: ";
    bool would_change_position = []()
    {
        auto value = get_random_number_1_to_(2);
        if(value == 1)
        {
            return false;
        }
        else
        {
            return true;
        }
    }();
    std::cout << std::boolalpha << would_change_position;
    if(would_change_position)
    {
        auto curr_position = 0;
        if((guess == 1) && (where_goat_is == 2))
        {
            curr_position = 3;
        }
        else if((guess == 1) && (where_goat_is == 3))
        {
            curr_position = 2;
        }
        else if((guess == 2) && (where_goat_is == 1))
        {
            curr_position = 3;
        }
        else if((guess == 2) && (where_goat_is == 3))
        {
            curr_position = 1;
        }
        else if((guess == 3) && (where_goat_is == 1))
        {
            curr_position = 2;
        }
        else if((guess == 3) && (where_goat_is == 2))
        {
            curr_position = 1;
        }
        if(curr_position == where_car_is)
        {
            //std::cout << "It was better_to_change!\n";
            return 1;
        }
        else
        {
            //std::cout << "In this case it was not better_to_change!\n";
            return 0;
        }
    }
    else
    {
        if(guess == where_car_is)
        {
            //std::cout << "In this case it was not better_to_change!\n";
            return 0;
        }
        else
        {
            //std::cout << "It was better_to_change!\n";
            return 1;
        }
    }
}

int main() {
    int better_to_change = 0;
    int better_to_stay = 0;
    for(int i = 0; i < 10; i++)
    {
        auto random_num = get_random_number_1_to_(3);
        auto x = monty_hall_problem(random_num);
        if(x == 0)
        {
            better_to_stay += 1;
            std::cout << "\t better to stay\n";
        }
        else if(x == 1)
        {
            better_to_change += 1;
            std::cout << "\t better to change\n";
        }
    }

    std::cout << "better_to_stay:   " << better_to_stay << "\n";
    std::cout << "better_to_change: " << better_to_change << "\n";

    if(better_to_change > better_to_stay)
    {
        return better_to_change;
    }
    else
    {
        return better_to_stay;
    }
}
