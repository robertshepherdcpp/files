#include<iostream>
#include<string>
#include<vector>
#include<random>
#include<utility>

auto input(std::string x)
{
    std::cout << x;
    std::string y{};
    std::cin >> y;
    return y;
}

auto random_direction() -> int
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 4);

    return dist6(rng);
}

auto random_character() -> char
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 25);

    return char(dist6(rng) + 97);
}

auto random_number(int n) -> int
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0, n);

    return dist6(rng);
}

auto find(std::vector<std::pair<int, int>> v, std::pair<int, int> p)
{
    for(const auto& i : v)
    {
        if(i == p)
        {
            return true;
        }
    }
    return false;
}

auto other_pos(std::pair<int, int> pos, std::string str, int direction)
{
    std::vector<std::pair<int, int>> positions{};
    if(direction == 1)
    {
        auto copy_pos = pos;
        for(int i = 0; i < str.size(); i++)
        {
            copy_pos.first -= 1;
            positions.push_back(copy_pos);
        }
        return positions;
    }
    if(direction == 2)
    {
        auto copy_pos = pos;
        for(int i = 0; i < str.size(); i++)
        {
            copy_pos.second += 1;
            positions.push_back(copy_pos);
        }
        return positions;
    }
    if(direction == 3)
    {
        auto copy_pos = pos;
        for(int i = 0; i < str.size(); i++)
        {
            copy_pos.first += 1;
            positions.push_back(copy_pos);
        }
        return positions;
    }
    if(direction == 4)
    {
        auto copy_pos = pos;
        for(int i = 0; i < str.size(); i++)
        {
            copy_pos.second -= 1;
            positions.push_back(copy_pos);
        }
        return positions;
    }
    return positions;
}

template<typename T>
auto has_shared(std::vector<T> v1, std::vector<T> v2)
{
    for(auto& x : v1)
    {
        for(auto& y : v2)
        {
            if(x == y)
            {
                return true;
            }
        }
    }
    return false;
}

auto crossword_board(std::vector<std::string> strs, int dimension)
{
    // first make the board
    std::vector<std::vector<char>> board{};
    std::vector<std::pair<int, int>> pos_taken{};
    for(int i = 0; i < dimension; i++)
    {
        std::vector<char> temp{};
        for(int j = 0; j < dimension; j++)
        {
            temp.push_back(random_character());
        }
        board.push_back(temp);
    }

    for(const auto& x : strs)
    {
        // first get random direction for the string to be in the crosswords
        int direction = random_direction();
        if(direction == 1)
        {
            // this means that it will be going up the board
            bool good_position = false;
            std::pair<int, int> random_pos{};
            while(!good_position)
            {
                random_pos = {random_number(board.size()), random_number(board.size())};
                if(((random_pos.first >= x.size() - 1) && find(pos_taken, random_pos) == false) and !(has_shared(pos_taken, other_pos(random_pos, x, 1))))
                {
                    good_position = true;
                }
            }
            for (char c : x)
            {
                board[random_pos.first][random_pos.second] = c;
                random_pos.first -= 1;
            }

            auto taken_pos = other_pos(random_pos, x, 1);
            for(auto& x : taken_pos)
            {
                pos_taken.push_back(x);
            }
        }
        if(direction == 2)
        {
            // this means that it will be going up the board
            bool good_position = false;
            std::pair<int, int> random_pos{};
            while(!good_position)
            {
                random_pos = {random_number(board.size()), random_number(board.size())};
                if(((random_pos.second < (dimension - x.size() - 1)) && find(pos_taken, random_pos) == false) and !(has_shared(pos_taken, other_pos(random_pos, x, 2))))
                {
                    good_position = true;
                }
            }
            for (char c : x)
            {
                board[random_pos.first][random_pos.second] = c;
                random_pos.second += 1;
            }

            auto taken_pos = other_pos(random_pos, x, 2);
            for(auto& x : taken_pos)
            {
                pos_taken.push_back(x);
            }
        }
        if(direction == 3)
        {
            // this means that it will be going up the board
            bool good_position = false;
            std::pair<int, int> random_pos{};
            while(!good_position)
            {
                random_pos = {random_number(board.size()), random_number(board.size())};
                if(((random_pos.first <= (dimension - x.size() - 1)) && find(pos_taken, random_pos) == false) and !(has_shared(pos_taken, other_pos(random_pos, x, 3))))
                {
                    good_position = true;
                }
            }
            for (char c : x)
            {
                board[random_pos.first][random_pos.second] = c;
                random_pos.first += 1;
            }

            auto taken_pos = other_pos(random_pos, x, 3);
            for(auto& x : taken_pos)
            {
                pos_taken.push_back(x);
            }
        }
        if(direction == 4)
        {
            // this means that it will be going up the board
            bool good_position = false;
            std::pair<int, int> random_pos{};
            while(!good_position)
            {
                random_pos = {random_number(board.size()), random_number(board.size())};
                if(((random_pos.second > x.size() - 1) && find(pos_taken, random_pos) == false) and !(has_shared(pos_taken, other_pos(random_pos, x, 4))))
                {
                    good_position = true;
                }
            }
            for (char c : x)
            {
                board[random_pos.first][random_pos.second] = c;
                random_pos.second -= 1;
            }

            auto taken_pos = other_pos(random_pos, x, 4);
            for(auto& x : taken_pos)
            {
                pos_taken.push_back(x);
            }
        }
    }

    return board;
}

int main()
{
    std::vector<std::string> strs{"hello", "there"};
    // int amount_of_moves = std::stoi(input("Please enter the amount of moves that you want to do: "));
    // int dimension = std::stoi(input("Please enter the dimensions of the grid: "));
    // for(int i = 0; i < amount_of_moves; i++)
    // {
    //     std::string word = input("Enter the word: ");
    //     strs.push_back(word);
    // }

    auto v = crossword_board(strs, 10);
    for(auto x : v)
    {
        for(auto z : x)
        {
            std::cout << z << " ";
        }
        std::cout << '\n';
    }
}

// to do: add stuff to the pos_taken vector to make sure that the words don't overlap
