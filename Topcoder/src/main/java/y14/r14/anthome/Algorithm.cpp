#include <stdio.h>
#include <vector>

int n, m;

struct Node
{
         std::vector<int> adj_node;
         int parent;
         int pre, post;
};

Node tree[200010];
int counter;

void traverse_tree(int cur)
{
         int adj;
         tree[cur].pre = counter++;
         std::vector<int>& adj_node_vec = tree[cur].adj_node;
         
         for(int i = 0; i < adj_node_vec.size(); i++)
         {
                   adj = adj_node_vec[i];
                   
                   if(adj != tree[cur].parent)
                   {
                            tree[adj].parent = cur;
                            traverse_tree(adj);
                   }
         }
         tree[cur].post = counter++;
}

int check_path(int node1, int node2)
{
         if(node1 == 1 || node2 == 1 || node1 == node2)
                   return 1;
         return tree[node1].pre < tree[node2].pre && tree[node1].post > tree[node2].post || tree[node1].pre > tree[node2].pre && tree[node1].post < tree[node2].post ? 1 : 0;
}

int main()
{
         int tc, i, t1, t2;
         scanf("%d", &tc);
         for(int c = 1; c <= tc; c++)
         {
                   scanf("%d%d", &n, &m);
                   if(c > 1)
                            for(i = 1; i <= n; i++)
                                     tree[i].adj_node.clear();
                   for(i = 1; i < n; i++)
                   {
                            scanf("%d%d", &t1, &t2);
                            tree[t1].adj_node.push_back(t2);
                            tree[t2].adj_node.push_back(t1);
                   }
                   
                   printf("Case #%d\n", c);
                   
                   counter = 1;
                   tree[1].parent = 0;
                   traverse_tree(1);
                   
                   for(i = 0; i < m; i++)
                   {
                            scanf("%d%d", &t1, &t2);
                            printf("%d\n", check_path(t1, t2));
                   }
         }
         return 0;
}
