namespace formt { // to format output

    auto find_braces(std::string s_p) 
    {for(int i = 0; i < s_p.size(); i++) 
        {
            if(s_p[i] == '{' and s_p[i + 1] == '}') {
                return i;
            }
        }
        return -1; }
struct format {
    explicit format(std::string);
    template<typename T>
    explicit format(std::string, T t);
    template<typename T, typename... Ts>
    explicit format(std::string, T t, Ts... ts);
};
format::format(std::string s) {
    std::cout << s << "\n";
}
template<typename T>
void func(std::string s, T t) {
    int i = find_braces(s);
    if(i == -1) {
        throw std::runtime_error("Entered variables but no /'{}/'."); }
    auto substr_v = s.substr(0, i);
    std::cout << substr_v << t;
    auto substr_v2 = s.substr(i + 2, (s.size() - i));
    std::cout << substr_v2;
}
int j = 0;
int c = 0;
template<typename T, typename... Ts>
void func(std::string s, T t, Ts... ts) {
    auto x = find_braces(s);
    j = x;
    if(j != -1) {
    auto sub_str_v = s.substr(0, j);
    std::cout << sub_str_v;
    std::cout << t;
    } else {
        throw std::runtime_error("Entered variables but no /'{}/'.");
    }
    auto w = s.substr(x + 2, s.size());
    func(w, ts...);
}
template<typename T>
format::format(std::string s, T t) {
    func(s, t);
}
template<typename T, typename... Ts>
format::format(std::string s, T t, Ts... ts) {
    func(s, t, ts...);
}
} // formt
