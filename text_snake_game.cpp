#include<iostream>
#include<vector>
#include<string>
#include<random>
#include<utility>
#include<cstddef>

auto get_random_position() -> std::pair<int, int>
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0,2);

    return std::pair{dist6(rng), dist6(rng)};
}

auto plant_random_four_in_grid(std::vector<std::vector<char>>& grid) -> void {
    bool finished = false;
    while (!finished) {
        auto random_coord = get_random_position();
        if (random_coord.first < grid.size() && random_coord.second < grid[0].size() && // Check bounds
            grid[random_coord.first][random_coord.second] != 'X' && grid[random_coord.first][random_coord.second] != '4') {
            grid[random_coord.first][random_coord.second] = '4';
            finished = true;
        }
    }
}

auto print_vector(std::vector<std::vector<char>>& vec)
{
    for(auto& i : vec)
    {
        std::cout << "{";
        for(auto x : i)
        {
            std::cout << " " << x;
        }
        std::cout << " }\n";
    }
}

auto move_left_in_grid(std::vector<std::vector<char>>& grid) {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == 'X' && j >= 1) {
                grid[i][j - 1] = 'X';
                grid[i][j] = '0';
            }
        }
    }
}

auto move_down_in_grid(std::vector<std::vector<char>>& grid) {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == 'X' && i < grid.size() - 1) {
                grid[i + 1][j] = 'X';
                grid[i][j] = '0';
            }
        }
    }
}

auto move_right_in_grid(std::vector<std::vector<char>>& grid) {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == 'X' && j < grid[0].size() - 1) {
                grid[i][j + 1] = 'X';
                grid[i][j] = '0';
            }
        }
    }
}

auto move_up_in_grid(std::vector<std::vector<char>>& grid) {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == 'X' && i > 0) {
                grid[i - 1][j] = 'X';
                grid[i][j] = '0';
            }
        }
    }
}

auto four(const std::vector<std::vector<char>>& grid) -> bool {
    for (const auto& row : grid) {
        for (char cell : row) {
            if (cell == '4') {
                return true;
            }
        }
    }
    return false;
}

int main()
{
    char input{};
    int score{};
   
    std::vector<std::vector<char>> arr{
        {'0', '0', '0'},
        {'0', 'X', '0'},
        {'0', '0', '0'}
    };
   
    plant_random_four_in_grid(arr);
   
    while(true)
    {
        print_vector(arr);
       
        std::cout << "Enter your move: ";
        std::cin >> input;
        std::cout << '\n';
        if(input == 'a')
        {
            move_left_in_grid(arr);
        }
        else if(input == 's')
        {
            move_down_in_grid(arr);
        }
        else if(input == 'd')
        {
            move_right_in_grid(arr);
        }
        else if(input == 'w')
        {
            move_up_in_grid(arr);
        }
       
        if(!four(arr))
        {
            score += 1;
            plant_random_four_in_grid(arr);
        }
    }
}
