#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <vector>

using namespace std;

class algorithm
{

public:
void solution(char *input, char *output);

/* You can add your own class functions, 
but main function call "solution" function only. */

};

#ifdef TESTING
#define PRINTF printf
#define ASSERT assert
#else
#define PRINTF
#define ASSERT
#endif

static int N;
static int lengths[1024];
static char strings[1024][128];


struct Node {
	Node() { }
	void clear() {
		for(int n = 0; n < 26; n++)
			children[n] = -1;
		count = 0;
	}

	int children[26];
	int count, temp[5];
};

struct Tree {
	Node *nodes;
	int count;

	Tree(int size) {
		nodes = new Node[size];
		count = 1;
		clear();
	}

	void clear() {
		nodes[0].clear();
		count = 1;
	}

	void insert(const char *string, int length) {
		int node_id = 0;

		for(int i = 0; i < length; i++) {
			int id = string[i] - 'a';
			int next_id = nodes[node_id].children[id];
			if(next_id == -1) {
				next_id = count++;
				nodes[next_id].clear();
				nodes[node_id].children[id] = next_id;
			}
			node_id = next_id;
			nodes[node_id].count++;
		}
	}

	int find(const char *string, int length) {
		int node_id = 0;

		for(int i = 0; i < length; i++) {
			node_id = nodes[node_id].children[string[i] - 'a'];
			if(node_id == -1)
				return 0;
		}
		return nodes[node_id].count;
	}
};

void algorithm::solution(char *input, char *output){
	FILE *in = fopen(input, "rb");
	FILE *out = fopen(output, "wb");

	int cases;
	fscanf(in, "%d", &cases);

	Tree main_tree(4 * 1024 * 1024);
	Tree local_tree(128 * 128);

	for(int c = 0; c < cases; c++) {
		fscanf(in, "%d", &N);
		for(int n = 0; n < N; n++) {
			fscanf(in, "%s", strings[n]);
			lengths[n] = strlen(strings[n]);
		}

		int min[1024], max_len = 0;
		for(int n = 0; n < N; n++) {
			min[n] = lengths[n];
			max_len = max(max_len, min[n]);
		}

		main_tree.clear();
		for(int n = 0; n < N; n++) {
			int length = lengths[n];
			for(int i = 0; i < length; i++)
				main_tree.insert(strings[n] + i, length - i);
		}

		for(int n = 0; n < N; n++) {
			local_tree.clear();
			int length = lengths[n];
			for(int i = 0; i < length; i++)
				local_tree.insert(strings[n] + i, length - i);

			for(int w = 1; w < min[n]; w++) {
				for(int i = 0; i < length - w + 1; i++) {
					int mc = main_tree.find(strings[n] + i, w);
					int lc = local_tree.find(strings[n] + i, w);
					ASSERT(mc >= lc && mc > 0);

					if(mc == lc) {
						PRINTF("min %d: %s[%d]\n", n, strings[n] + i, w);
						min[n] = w;
						break;
					}
				}
			
			}
		}

		fprintf(out, "Case# %d\n", c + 1);
		for(int n = 0; n < N; n++)
			fprintf(out, "%d\n", min[n]);
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