#include<iostream> // std::cout
#include<vector>   // std::vector
#include<string>   // std::string
#include<fstream>  // std::ifstream
#include<random>   // random things
#include<fstream>  // std::ofstream

int main()
{
    std::string line{};
    std::vector<std::string> vec{};
    std::ifstream myfile("words.txt");
    if (myfile.is_open())
    {
        while (std::getline(myfile, line))
        {
            vec.push_back(line);
        }
        myfile.close();
    }

    int longest_in_common = 0;
    std::string first_word{vec[0]};
    std::string second_word{vec[1]};

    for(int i = 0; i < vec.size(); i++)
    {
        for(int j = 0; j < vec.size(); j++)
        {
            if(i != j)
            {
                for(int x = 1; x < 5;x++)
                {
                    if((vec[i].substr(vec[i].size() - x, vec[i].size()) ==
                        vec[j].substr(0, x)) && (vec[j].substr(vec[j].size() - x, vec[j].size()) ==
                        vec[i].substr(0, x)) && x >= longest_in_common) 
                    {
                        longest_in_common = x;
                        first_word = vec[i];
                        second_word = vec[j];
                        std::cout << first_word << ", " << second_word << ", " << longest_in_common << '\n';
                    }
                }
            }
        }
    }

    std::cout << "\n------------------------------------------\n" << first_word << "\n" << second_word;
}
