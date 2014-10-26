#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <string>
#include <map>
#include <iostream>
using namespace std;

#define sz(a) ((int)((a).size()))
#define pb push_back
#define mp make_pair

template<class T> T sqr(const T& a) { return a * a; }
template<class T> T abs(const T& a) { return a < 0 ? -a : a; }

class algorithm
{

  private:
  vector<int> b, x, need, cur;
  FILE* fin;
  FILE* fout;
  public:
  void solution(char *input, char *output);
  void solve(int test_num);

  /* You can add your own class functions, 
  but main function call "solution" function only. */

};

void algorithm::solve(int test_num) {
  int n, k;
  fscanf(fin, "%d%d", &n, &k);
  b.resize(n);
  x.resize(n);
  need.resize(k);
  cur.resize(k);
  for (int i = 0; i < k; ++i) fscanf(fin, "%d", &need[i]);
  for (int i = 0; i < k; ++i) cur[i] = 0;
  for (int i = 0; i < n; ++i) {
      fscanf(fin, "%d%d", &b[i], &x[i]);
      --b[i];
  }

  fprintf(fout, "Case# %d\n", test_num);
  int L = 0;
  int R = 0;
  //first stuff
  for (int i = 0; i < k; ++i) {
    while (R < n && cur[i] < need[i]) {
      int typ = b[R];
//      printf("typ = %d\n", typ);
      ++cur[typ];
      ++R;
    }
    if (cur[i] < need[i]) {
      fprintf(fout, "-1\n");
      return;
    }
  }
  if (R == 0) {
    //No restrictions
    fprintf(fout, "0\n");
    return;
  }
  int best_result = x[R - 1] - x[L] + 1;
  for (L = 1; L < n; ++L) {
    int typ = b[L - 1];
    --cur[typ];
    while (R < n && cur[typ] < need[typ]) {
      ++cur[b[R]];
      ++R;
    }
    if (cur[typ] < need[typ]) {
      break;
    }
    int cur_result = x[R - 1] - x[L] + 1;
    if (best_result > cur_result) best_result = cur_result;
  }
  fprintf(fout, "%d\n", best_result);
}

//You can include standard C++ language libraries that you want use.//

void algorithm::solution(char *input, char *output){
  fin = fopen(input, "r");
  fout = fopen(output, "w");

  int tests;
  fscanf(fin, "%d", &tests);
  for (int test_num = 1; test_num <= tests; ++test_num) {
    solve(test_num);
  }
  /* User Implementation
   1.     first argument is input path(include file name)
           second argument is output path(include file name).
            2.      you must parsing the input data form input file.
             3.     you must write the output data into text file.
              */
                  
  fclose(fin);
  fclose(fout);
}