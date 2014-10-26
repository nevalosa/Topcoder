#include <fstream>
#include <cstring>

class algorithm {
public:
    void solution(char *input, char *output);

private:
    void fill(unsigned short n);

private:
    static const unsigned short kMaxN = 10000;
    unsigned short mOutPut[kMaxN];
};

void algorithm::solution(char *input, char *output) {
    std::ifstream in(input);
    std::ofstream out(output);

    unsigned int T = 0;
    in >> T;

    for (unsigned int testCase = 0; testCase < T; ++testCase) {
        unsigned short n = 0;
        in >> n;
        fill(n);
        for (unsigned short *i = mOutPut, *end = mOutPut + n; i != end; ++i)
            out << *i << " ";
        out << std::endl;
    }

    in.close();
    out.close();
}

void algorithm::fill(unsigned short n) {
    memset(mOutPut, 0, n * sizeof (unsigned short));
    unsigned short step = 2;
    for (unsigned short i = 1, pos = 1; i <= n; ++i) {
        mOutPut[pos] = i;
        unsigned short curPath = step;
        pos += step;
        while (pos >= n) {
            pos %= n;
            step <<= 1;
            pos <<= 1;
        }
    }
}
