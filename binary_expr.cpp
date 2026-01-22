// a program to generate a random sequence of arithmetic operations
#include<iostream>
#include<vector>
#include<string>
#include<cstdlib>

auto random(int range) {
    return rand() % range;
}

const std::vector<std::string> v {
    " + ", " - ", " / ", " * "
};

int main() {
    std::string res;
    int paren_count = 0;
    while(res.size() < 100) {
        if(random(5) == 1) {
            // then we use a paren
            res += "(";
            paren_count += 1;
        }
        int a = random(10);
        res += std::to_string(a);
        int idx = random(v.size());
        res += v[idx];
        int b = random(10);
        if(random(5) == 1) {
            // then we use a paren
            res += "(";
            paren_count += 1;
            res += std::to_string(b);
        }
        else {
            res += std::to_string(b);
            if(paren_count > 0) {
                if(random(5) == 1) {
            // then we use a paren
            res += ") ";
            paren_count -= 1;
        }
            }
        }


    }
    char c = res[res.size()-2];
    bool seen = false;
    for(int i = 0; i < v.size(); i++) {
        if(v[i][1] == c) {
            res += std::to_string(random(10));
        }
    }
    for(int i = 0; i < paren_count; i++) {
        res += ")";
    }
    std::cout << res << "\n";
}
