#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <algorithm>

using namespace std;

class algorithm
{

public:
void solution(char *input, char *output);

/* You can add your own class functions, 
but main function call "solution" function only. */

};

#ifdef TESTING
#define ASSERT assert
#define PRINTF printf
#else
#define ASSERT
#define PRINTF
#endif

static int M, K;

enum {
	max_length = 200,
	max_iters = 2500000,
};

struct Node {
	Node() { }
	void clear() {
		for(int n = 0; n < 10; n++)
			children[n] = -1;
		count = 0;
	}
	bool is_end() const { return count > 0; }

	int children[10];
	int count, temp;
};

struct Tree {
	Node *nodes;
	int count, longest, iters;

	Tree(int size) {
		nodes = new Node[size];
		clear();
	}

	void clear() {
		nodes[0].clear();
		longest = 0;
		count = 1;
		iters = 0;
	}

	void insert(const char *string, int length) {
		int node_id = 0;

		for(int i = 0; i < length; i++) {
			int id = string[i] - '0';
			int next_id = nodes[node_id].children[id];
			if(next_id == -1) {
				next_id = count++;
				nodes[next_id].clear();
				nodes[node_id].children[id] = next_id;
			}
			node_id = next_id;
		}
		nodes[node_id].count++;
		longest = max(longest, length);
	}

	int find_longest(int *ptrs, int ptr_count, int length) {
		if(length == max_length)
			return max_length;
		if(iters++ > max_iters)
			return length;

		int longest = length > 0? length : -1;

		for(int s = 0; s < M; s++) {
			bool ok = true;
			int nptrs[22], nptr_count = 0;

			for(int p = 0; p < ptr_count; p++) {
				int next = nodes[ptrs[p]].children[s];
				if(next == -1)
					continue;

				if(nodes[next].is_end()) {
					ok = false;
					break;
				}

				nptrs[nptr_count++] = next;
				ASSERT(nptr_count < sizeof(nptrs)/sizeof(int));
			}

			if(ok) {
			//	PRINTF("[%d] Entering: %d\n", length, s);

				int next0 = nodes[0].children[s];
				if(next0 != -1)
					nptrs[nptr_count++] = next0;

				longest = max(longest, find_longest(nptrs, nptr_count, length + 1));
			}
		}

		return longest;
	}

};

void algorithm::solution(char *input, char *output){
	FILE *in = fopen(input, "rb");
	FILE *out = fopen(output, "wb");

	int cases;
	fscanf(in, "%d", &cases);
	Tree tree(100 * 1024 * 20);
	
	for(int c = 0; c < cases; c++) {
		fscanf(in, "%d %d", &M, &K);
		
		tree.clear();
		for(int k = 0; k < K; k++) {
			char block[32];
			fscanf(in, "%s", block);
			tree.insert(block, strlen(block));
		}

		int result = tree.find_longest(NULL, 0, 0);
		if(result == max_length)
			result = -1;

		fprintf(out, "Case# %d\n", c + 1);
		fprintf(out, result == -1? "No\n" : "%d\n", result);
	}

	fclose(in);
	fclose(out);
}


#ifdef TESTING

int main(int argc, char **argv) {
	assert(argc > 1);
	algorithm alg;
	char output[] = "output.txt";
	alg.solution(argv[1], output);
	return 0;
}

#endif