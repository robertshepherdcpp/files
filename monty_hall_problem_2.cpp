#include <iostream>
#include <random>
#include <vector>

auto random_3() -> int {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 3);
    return dist6(rng);
}

auto true_or_false() -> bool {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 2);
    if (dist6(rng) == 1) {
        return false;
    } else {
        return true;
    }
}

auto getIndexShow(int x, std::vector<int>& doors) -> int {
    for (int i = 0; i < doors.size(); i++) {
        if (doors[i] == 0 && i != x) {
            return i;
        }
    }

    return {};
}

int main() {
    int switchWins = 0;
    int switchNonWins = 0;
    int nonSwitchWins = 0;
    int nonSwitchNonWins = 0;
    int totalRounds = 0;

    for (int i = 0; i < 10'000; i++) {
        // first make the three doors, initialize them all to goats at first but
        // then get a random pos of goat.
        std::vector<int> doors{0, 0, 0};
        doors[random_3() - 1] = 1;

        // now we want to choose a random door
        int door_selected = random_3();

        // now the game show host shows one of the doors that is not the
        // selected door or is not a prize
        int show_door = getIndexShow(door_selected - 1, doors);

        // decide whether you should switch or not
        bool should_switch = true_or_false();

        // now get whether it was a win or a loss
        bool win = false;
        if (doors[door_selected - 1] == 1 && should_switch) {
            win = false;
        } else if (doors[door_selected - 1] == 1 && !should_switch) {
            win = true;
        } else if (doors[door_selected - 1] == 0 && should_switch) {
            win = true;
        } else {
            win = false;
        }

        if (should_switch && win) {
            switchWins++;
        } else if (!should_switch && win) {
            nonSwitchWins++;
        }
        else if(!should_switch && !win) {
            nonSwitchNonWins++;
        }
        else if(should_switch && !win) {
            switchNonWins++;
        }
        totalRounds++;
    }

    
    std::cout << "Switch Wins:         " << double(switchWins) / totalRounds * 100 << "%" << '\n';
    std::cout << "Non Switch Wins:     " << double(nonSwitchWins) / totalRounds * 100 << "%" << "\n\n";
    std::cout << "Switch Non Wins:     " << double(switchNonWins) / totalRounds * 100 << "%" << '\n';
    std::cout << "Non Switch Non Wins: " << double(nonSwitchNonWins) / totalRounds * 100 << "%" << '\n';

    std::cout << '\n' << (double(switchWins) / totalRounds * 100) + (double(nonSwitchWins) / totalRounds * 100) + (double(switchNonWins) / totalRounds * 100) + (double(nonSwitchNonWins) / totalRounds * 100) << "%" ;
}
