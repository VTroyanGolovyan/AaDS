#include <iostream>
#include <vector>
#include <cassert>

std::vector<size_t> CalculatePreffixFunction(const std::string& text) {
    size_t n = text.length(); // 7
    // text = abacaba
    std::vector<size_t> preffix_function(n, 0); // 0, 0, 1, 0, 1, 2, 3

    size_t len = 0;
    size_t i = 1;

    while (i < n) {
        if (text[i] == text[len]) {
            len++;
            preffix_function[i] = len;
            i++;
        } else if (len != 0) {
            len = preffix_function[len - 1];
        } else {
            preffix_function[i] = 0;
            i++;
        }
    }

    return preffix_function;
}

std::vector<size_t> FindAllOccurences(const std::string& pattern, const std::string& text) {
    std::string combined = pattern + "#" + text;
    std::vector<size_t> pi = CalculatePreffixFunction(combined);
    std::vector<size_t> result;
    
    size_t m = pattern.size();
    for (size_t i = m + 1; i < combined.size(); ++i) {
        if (pi[i] == m) {
            result.push_back(i - 2 * m);
        }
    }
    return result;
}


// aba   "mama papa aba ababa"
// 10, 14, 16

int main()
{
    {
        std::vector<size_t> expected = {0, 0, 1, 0, 1, 2, 3};
        assert(CalculatePreffixFunction("abacaba") == expected);
    }

    {
        std::vector<size_t> expected = {};
        assert(CalculatePreffixFunction("") == expected);
    }

    {
        std::vector<size_t> expected = {0,1,2,3,4};
        assert(CalculatePreffixFunction("aaaaa") == expected);
    }
    return 0;
}
