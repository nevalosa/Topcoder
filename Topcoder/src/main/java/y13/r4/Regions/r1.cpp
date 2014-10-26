//You can include standard C++ language libraries that you want use.//
#include <stdio.h>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <memory.h>


class algorithm
{

public:
void solution(char *input, char *output);

/* You can add your own class functions,
but main function call "solution" function only. */

};

struct line{
	line() : d(0), u(0), x(0), v(0), acc(0) {}
	line(int __d,int __u,int __x,int __v, int __acc = 1) : d(__d), u(__u), x(__x), v(__v), acc(__acc) {}
	static bool sortcomp(const line& lhs, const line& rhs){
		return lhs.x < rhs.x;
	}
	bool operator<(const line& rhs) const { // sweep comparer
		return d < rhs.d;
	}
	int d,u,x;
	long long v;
	int acc;
};

std::vector<line> lines;

std::set<line> sweep;
typedef std::set<line>::iterator sweep_it;

sweep_it find(int y){ // intersect or apart.
	line finderline(y,y,0,0);
	return --sweep.upper_bound(finderline);
}


#include <map>


const int MAX_AREAMAP = 500000000;
const long long SPEED_CUT = 10000000000LL;

//std::map<int, int> countscount;
//std::map<int, int> areamap;
//hash_map<int> areamap;
unsigned int areamap[MAX_AREAMAP];
//std::map<int, int> areamap;
long long count, reduced;
unsigned int maxarea;
typedef std::map<unsigned int, unsigned int>::iterator map_it;

void add_area(long long c, int area){
	c = c % MAX_AREAMAP;
	unsigned int areaold = areamap[c];
	areamap[c] = area + areaold;
	if (c != 0){
		maxarea = std::max(maxarea, area+areaold);
	}
}

int get_area(long long c){
	return areamap[c % MAX_AREAMAP];
}

void reduce_city(long long c){
	//areamap.erase(c);
	++reduced;
}

void merge_it(sweep_it lwr, sweep_it upr){
	int minv, maxv, maxx;
	if (lwr->v != upr->v){
		minv = std::min(lwr->v, upr->v);
		maxv = std::max(lwr->v, upr->v);
		maxx = std::max(lwr->x, upr->x);
		add_area(lwr->v, (maxx - lwr->x) * (lwr->u - lwr->d));
		add_area(upr->v, (maxx - upr->x) * (upr->u - upr->d));
		const_cast<line&>(*lwr).x = maxx; const_cast<line&>(*upr).x = maxx;
		add_area(minv, get_area(maxv));
		reduce_city(maxv);
		const_cast<line&>(*lwr).v = minv;
		const_cast<line&>(*upr).v = minv;
		//--countscount[maxv];
	}
	const_cast<line&>(*lwr).u = upr->u; // remove upr;
	sweep.erase(upr);
}

void add(line nl){
	sweep_it lwr = find(nl.d);
	sweep_it upr = find(nl.u);
	line ul = nl;
	if (lwr->d <= nl.d && nl.u <= lwr->u){ // included
		nl.v = ++count;
		areamap[count%MAX_AREAMAP] = 0;
		ul.u = lwr->u;
		ul.d = nl.u;
		ul.acc = lwr->acc;
		ul.v = lwr->v;
		nl.acc = lwr->acc+1;
		add_area(lwr->v, (lwr->u-nl.d)*(nl.x-lwr->x));
		sweep.insert(ul);
		sweep.insert(nl);
		const_cast<line&>(*lwr).x = nl.x;
		const_cast<line&>(*lwr).u = nl.d;
		return;
	}
	if (lwr->u > nl.d){ // intersect lower!
		ul.d = lwr->u;
		// d u left count
		line dl(nl.d, lwr->u, nl.x, ++count);
		areamap[count%MAX_AREAMAP] = 0;
		add_area(lwr->v, (nl.x-lwr->x)*(lwr->u-lwr->d) );
		const_cast<line&>(*lwr).x = nl.x;
		const_cast<line&>(*lwr).u = nl.d;
		dl.acc = lwr->acc + 1;
		sweep.insert(dl);
	}

	line udl = ul;
	if (upr->d < ul.u){ // intersect upper!
		udl.u = upr->d;
		line uul(upr->d, ul.u, nl.x, ++count);
		areamap[count%MAX_AREAMAP] = 0;
		add_area(upr->v, (nl.x-upr->x)*(upr->u-upr->d) );
		const_cast<line&>(*upr).x = nl.x;
		const_cast<line&>(*upr).d = ul.u;
		uul.acc = upr->acc + 1;
		sweep.insert(uul);
	}

	// now insert udl ---> increasing all intervals within.. by iteration.
	sweep_it from = find(udl.d);
	sweep_it end = find(udl.u);
	int downline = udl.d, upline = udl.u;
	for (sweep_it itline = from; itline != end; ++itline){
		if (upline < itline->d){
			line nmid(downline, itline->d, nl.x, ++count);
			areamap[count%MAX_AREAMAP] = 0;
			sweep.insert(nmid);
		}
		add_area(itline->v, (itline->u - itline->d) * (nl.x-itline->x));
		++const_cast<line&>(*itline).acc;
		const_cast<line&>(*itline).x = nl.x;
		const_cast<line&>(*itline).v = ++count;
		areamap[count%MAX_AREAMAP] = 0;
		downline = itline->u;
	}
}

// |----|--|-----|---|-------|
//-     |------------|
//               upr(|-------|)
//  lwr(|--|)
//=|-------|-----|-----------|

void remove(const line& nl){
	sweep_it lwr = find(nl.d);
	sweep_it upr = find(nl.u);
	for (sweep_it itline = lwr; itline != upr; ++itline){
		add_area(itline->v, (itline->u - itline->d) * (nl.x-itline->x));
		--const_cast<line&>(*itline).acc;
		const_cast<line&>(*itline).x = nl.x;
		const_cast<line&>(*itline).v = ++count;
		areamap[count%MAX_AREAMAP] = 0;
	}
	sweep_it lwrm1 = lwr;
	--lwrm1;
	merge_it(lwrm1, lwr);
	sweep_it uprm1 = upr;
	--uprm1;
	merge_it(uprm1, upr);
}

void solve(){
	int i,n;

	scanf("%d",&n);
	lines.clear();
	lines.reserve(n*2);
	for (i=0;i<n;++i){
		int l,d,r,u;
		scanf("%d %d %d %d",&l,&d,&r,&u);
		lines.push_back(line(2147483647 - u,2147483647 - d,2147483647 - r,1));
		lines.push_back(line(2147483647 - u,2147483647 - d,2147483647 - l,-1));
	}
	count = 0, reduced = 0, maxarea = 0;
	sweep.clear();
	//areamap.clear();
	memset(areamap,0,sizeof(areamap));
	sweep.insert(line(-1,2147483647,0,0,0));
	std::sort(lines.begin(),lines.end(),line::sortcomp);
	for(i=0;i<(int)lines.size();++i){
		if (count > SPEED_CUT)
			break;
		if (lines[i].v == 1) add(lines[i]);
		else remove(lines[i]);
		/*
		printf("[%d:%d] ",i,lines[i].x);
		for (sweep_it sit=sweep.begin();sit!=sweep.end();++sit){
			printf("%2d %2d %2d : %2d %2d|", sit->d, sit->u, sit->x, sit->v, sit->acc);
		}
		printf("\n");
		printf("[%d:%d] ",i,lines[i].x);
		for (map_it mit=areamap.begin();mit!=areamap.end();++mit){
			printf("%2d %2d|",mit->first,mit->second);
		}
		printf("\n");*/
	}
	printf("%d %d\n",count-reduced, maxarea);
}

void algorithm::solution(char *input, char *output){
	freopen(input,"rt",stdin);
	freopen(output,"wt",stdout);
	int t,T;
	scanf("%d",&T);
	for (t = 0; t < T; ++t){
		solve();
	}
}