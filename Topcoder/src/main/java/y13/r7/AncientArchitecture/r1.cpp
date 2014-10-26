#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

namespace {
	char buf[1005];
	// dy[i,j,W,H] = from W, to H
	int area;

	struct pnt{
		pnt() : x(0), y(0) {}
		pnt(int x,int y) : x(x), y(y) {}
		void transpose(){
			int temp = x;
			x = y;
			y = temp;
		}
		
		pnt operator +(const pnt& rhs) const{
			return pnt((int)(x+rhs.x), (int)(y+rhs.y));
		}
		pnt& operator=(const pnt& rhs) {
			this->x = (int)rhs.x;
			this->y = (int)rhs.y;
			return (*this);
		}
		bool operator==(const pnt& rhs) const{
			return x==rhs.x && y==rhs.y;
		}
		pnt operator/(int denom) const{
			return pnt(x/denom,y/denom);
		}
		pnt rot_r() const{
			pnt ret = pnt(this->y, -this->x);
			return ret;
		}
		bool operator<(const pnt& rhs) const{
			if (x<rhs.x)
				return true;
			else if (x==rhs.x)
				return y < rhs.y;
			else
				return false;
		}
		int x,y;
	};

	struct pntd{
		pntd() : x(0), y(0) {}
		pntd(double x,double y) : x(x), y(y) {}
		void transpose(){
			double temp = x;
			x = y;
			y = temp;
		}

		pntd operator +(const pntd& rhs) const{
			return pntd((double)(x+rhs.x), (double)(y+rhs.y));
		}
		pntd& operator=(const pntd& rhs) {
			this->x = (double)rhs.x;
			this->y = (double)rhs.y;
			return (*this);
		}
		bool operator==(const pntd& rhs) const{
			return x==rhs.x && y==rhs.y;
		}
		pntd operator/(double denom) const{
			return pntd(x/denom,y/denom);
		}
		pntd rot_r() const{
			pntd ret = pntd(this->y, -this->x);
			return ret;
		}
		bool operator<(const pntd& rhs) const{
			if (x<rhs.x)
				return true;
			else if (x==rhs.x)
				return y < rhs.y;
			else
				return false;
		}
		double x,y;
	};
	

	struct subpow{
		subpow add(char pmz/*-1,0,1*/,int pos) const{
			subpow ret = (*this);
			if ((int)ret.bits.size() < pos+1)
				ret.bits.resize(pos+1);
			ret.bits[pos] += pmz;
			return ret;
		}
		bool operator<(const subpow& rhs) const{
			int nmax = std::max(bits.size(),rhs.bits.size());
			for (int i=0;i<nmax;++i){
				int a = (i<(int)bits.size()) ? bits[i] : 0;
				int b = (i<(int)rhs.bits.size()) ? rhs.bits[i] : 0;
				if (a<b) return true;
				if (a>b) return false;
			}
			return false;
		}
		bool operator==(const subpow& rhs) const{
			int nmax = std::max(bits.size(),rhs.bits.size());
			for (int i=0;i<nmax;++i){
				int a = (i<(int)bits.size()) ? bits[i] : 0;
				int b = (i<(int)rhs.bits.size()) ? rhs.bits[i] : 0;
				if (a<b) return false;
				if (a>b) return false;
			}
			return true;
		}
		std::vector<char> bits;
	};

	struct bigdouble{
		double base;
		subpow sp;
		bigdouble (double x = 0) : base(x) {}
		bigdouble add(char pmz, int pos) const {
			bigdouble ret = (*this);
			ret.sp = ret.sp.add(pmz,pos);
			return ret;
		}
		bool operator<(const bigdouble& rhs) const{
			if (base<rhs.base)
				return true;
			else if (base>rhs.base)
				return false;
			else{
				return sp<rhs.sp;
			}
		}
		bool operator==(const bigdouble& rhs) const{
			return (base==rhs.base && sp==rhs.sp);
		}
	};

	struct pntbd{
		pntbd() : x(0), y(0) {}
		pntbd(bigdouble x,bigdouble y) : x(x), y(y) {}
		void transpose(){
			bigdouble temp = x;
			x = y;
			y = temp;
		}

		/*
		pntbd operator +(const pntd& rhs) const{
			return pntbd(x+rhs.x, y+rhs.y);
		}*/

		pntbd& operator=(const pntbd& rhs) {
			this->x = rhs.x;
			this->y = rhs.y;
			return (*this);
		}
		bool operator==(const pntbd& rhs) const{
			return x==rhs.x && y==rhs.y;
		}
		/*
		pntbd operator/(double denom) const{
			return pntbd(x/denom,y/denom);
		}*/
		/*
		pntbd rot_r() const{
			pnt ret = pntbd(this->y, -this->x);
			return ret;
		}*/
		bool operator<(const pntbd& rhs) const{
			if (x<rhs.x)
				return true;
			else if (x==rhs.x)
				return y < rhs.y;
			else
				return false;
		}
		bigdouble x,y;
	};

	typedef std::vector<bigdouble> svbd;

	std::vector<pnt> calcpnt(int w, int h, int r){
		std::vector<pnt> ret;
		if (r==0){
			ret.push_back(pnt(w,0));
		}
		else{
			ret.push_back(pnt(1,0));
			for (int i=0;i<r;++i){
				if (i>0){
					ret.push_back(pnt(1+i,h-(r-1)+i-1));
				}
				ret.push_back(pnt(1+i,h-(r-1)+i));
			}
			ret.push_back(pnt(w,h));
		}
		return ret;
	}
	std::vector<pnt> calcpnt_trans(pnt p0, int rot, int w, int h, int r){
		std::vector<pnt> ret = calcpnt(w,h,r);
		for (int i=0;i<(int)ret.size();++i){
			if (rot==1 || rot==3)
				ret[i].transpose();
			if (rot==1 || rot==2)
				ret[i].x = -ret[i].x;
			if (rot==2 || rot==3)
				ret[i].y = -ret[i].y;
		}
		for (int i=0;i<(int)ret.size();++i)
			ret[i] = ret[i] + p0;
		return ret;
	}
	int calcarea(int w, int h, int r){
		int ret = 0;
		if (r==0)
			return w*h;
		ret += h;
		//ret += w-r-1;
		ret += (r * (r-1))/2;
		return ret;
	}
	struct pstate{
		int w0, h0, w1, h1, w2, h2, w3, h3;
		pstate() : w0(0),h0(0),w1(0),h1(0),w2(0),h2(0),w3(0),h3(0){}
		pstate(int w0, int w1, int w2, int w3, int h0, int h1, int h2, int h3)
			: w0(w0), w1(w1), w2(w2), w3(w3), h0(h0), h1(h1), h2(h2), h3(h3) {}
	};
	pstate ans_st;
	std::vector<pnt> prt;
	std::vector<pnt> pstate_to_prt(pstate pst, int rs[4]){
		pnt base_pnt;
		std::vector<pnt> ps0 = calcpnt_trans(base_pnt, 0,pst.w0, pst.h0, rs[0]);
		base_pnt = base_pnt + pnt(pst.w0, pst.h0);
		std::vector<pnt> ps1 = calcpnt_trans(base_pnt, 1,pst.h1, pst.w1, rs[1]);
		base_pnt = base_pnt + pnt(-pst.w1, pst.h1);
		std::vector<pnt> ps2 = calcpnt_trans(base_pnt, 2,pst.w2, pst.h2, rs[2]);
		base_pnt = base_pnt + pnt(-pst.w2, -pst.h2);
		std::vector<pnt> ps3 = calcpnt_trans(base_pnt, 3,pst.h3, pst.w3, rs[3]);
		std::vector<pnt> prt2;
		prt2.insert(prt2.end(),ps0.begin(),ps0.end());
		prt2.insert(prt2.end(),ps1.begin(),ps1.end());
		prt2.insert(prt2.end(),ps2.begin(),ps2.end());
		prt2.insert(prt2.end(),ps3.begin(),ps3.end());
		return prt2;
	}
	void solve1(){
		int n = strlen(buf);
		int i = 0, m = -1, sti = 0;
		int rs[4] = {0,};
		int atleastone=0;
		int w0,h0,w1,h1,w2,h2,w3,h3;
		while(1){
			if (buf[i%n] == 'L' && buf[(i+1)%n] == 'L'){
				++m;
				if (m==0) sti = i;
				if (m==4) break;
			}
			if (buf[i%n] == 'R' && m >= 0){
				++rs[m];
			}
			++i;
		}
		int minh = std::max(1+rs[0]+rs[1],1+rs[2]+rs[3]);
		int minw = std::max(1+rs[1]+rs[2],1+rs[3]+rs[0]);
		while(1){
			// w0 >= 1+rs[0], h1 >= 1+rs[1], w2 >= 1+rs[2], h3 >= 1+rs[3]
			for (w0=1+rs[0];w0<=minw;++w0){
				w3 = minw - w0;
				if (w3 >= rs[3]){
					for (h0=rs[0];h0<=minh;++h0){
						h1 = minh - h0;
						if (h1 >= 1+rs[1]){
							for (w1=rs[1];w1<=minw;++w1){
								w2 = minw - w1;
								if (w2 >= 1+rs[2]){
									for (h2=rs[2];h2<=minh;++h2){
										h3 = minh - h2;
										if (h3 >= 1+rs[3]){
											int adjustment = 0;
											int originalarea = minh * minw;
											int newarea = w0*h0 + w1*h1 + w2*h2 + w3*h3;
											adjustment = originalarea - newarea;
											int a0 = calcarea(w0,h0,rs[0]);
											int a1 = calcarea(h1,w1,rs[1]);
											int a2 = calcarea(w2,h2,rs[2]);
											int a3 = calcarea(h3,w3,rs[3]);
											int tot = a0 + a1 + a2 + a3;
											int currentarea = tot + adjustment;
											std::vector<pnt> pt = pstate_to_prt(pstate(w0,w1,w2,w3,h0,h1,h2,h3), rs);
											std::set<pnt> pset;
											int xi = 0;
											bool strange = false;
											for (xi=0;xi<(int)pt.size();++xi){
												pnt bef = pt[xi==0 ? (pt.size()-1) : (xi-1)];
												pnt cur = pt[xi];
												pnt curval = cur;
												if (bef.x != cur.x){
													for (int o = std::min(bef.x,cur.x)+1; o < std::max(bef.x,cur.x);++o){
														curval = pnt(o,bef.y);
														if (pset.find(curval)==pset.end())
															pset.insert(curval);
														else{
															strange = true;
															break;
														}
													}
												}
												else{
													for (int o = std::min(bef.y,cur.y)+1; o < std::max(bef.y,cur.y);++o){
														curval = pnt(bef.x,o);
														if (pset.find(curval)==pset.end())
															pset.insert(curval);
														else{
															strange = true;
															break;
														}
													}
												}
												if (pset.find(cur)==pset.end())
													pset.insert(cur);
												else{
													strange = true;
													break;
												}
												if (strange)
													break;
											}
											if (!strange && area > currentarea){
												atleastone = 1;
												pt = pstate_to_prt(pstate(w0,w1,w2,w3,h0,h1,h2,h3), rs);
												area = currentarea;
												ans_st = pstate(w0,w1,w2,w3,h0,h1,h2,h3);
											}
										}
									}
								}
							}
						}
					}
				}
			}
			if (!atleastone){
				if (rand()%2){
					++minh;
				}
				else{
					++minw;
				}
			}
			else
				break;
		}
		std::vector<pnt> prt2 = pstate_to_prt(ans_st, rs);
		for (i=(n-sti); i<(n-sti)+n; ++i){
			prt.push_back(prt2[(i+n-1)%n]);
		}
	}
	struct ang{
		ang() : i(-1), lr(0), l(-1), m(-1), r(-1) {}
		ang(int i, char lr, int l = -1, int m = -1, int r = -1)
			: i(i), lr(lr), l(l), m(m), r(r) {}
		bool isnull() const{ return i==-1; }
		bool iscomplex() const{ return l!=-1; }
		int i;
		char lr; // represents l or r
		int l, m, r;
		pntd p;
		pntbd pb;
	};
	ang angarr[2005], angsink[1005];

	long long floodfill(){
		long long ret = 0;
		std::vector<int> xs,ys;
		for (int i=0;i<(int)prt.size();++i){
			xs.push_back(prt[i].x);
			ys.push_back(prt[i].y);
		}
		for (int i=0;i<(int)xs.size();++i){
			ret += xs[i] * ys[(i+1)%xs.size()];
			ret -= xs[(i+1)%xs.size()] * ys[i];
		}
		return ret;
	}
	pntbd padd(const pntbd& lhs, const pnt& delta, int depth)
	{
		pntbd ret = lhs;
		ret.x = ret.x.add(delta.x, depth);
		ret.y = ret.y.add(delta.y, depth);
		return ret;
	}
	void flatten(int city, pnt delta, int depth){
		int lcity = angarr[city].l;
		int mcity = angarr[city].m;
		int rcity = angarr[city].r;
		pntbd pos;
		pos = angarr[city].pb;
		pnt deltar1 = delta.rot_r();
		pnt deltar2 = deltar1.rot_r();
		pntbd p1 = padd(pos, delta, depth);
		pntbd p2 = padd(p1, deltar1, depth);
		pntbd p3 = padd(p2, deltar2, depth);
		angarr[lcity].pb = p1;
		angarr[mcity].pb = p2;
		angarr[rcity].pb = p3;
		if (angarr[lcity].iscomplex()){
			flatten(lcity,delta,depth+1);
		}
		if (angarr[mcity].iscomplex()){
			flatten(mcity,deltar1,depth+1);
		}
		if (angarr[rcity].iscomplex()){
			flatten(rcity,deltar2,depth+1);
		}
	}
	void solve2(){
		int n = strlen(buf);
		int i = 0, m = -1, sti = 0;
		int rs[4] = {0,};
		for (int i=0;i<n;++i){
			angarr[i] = ang(i,buf[i]);
			angsink[i] = angarr[i];
		}
		angarr[n] = ang();
		angsink[n] = ang();
		int cc = n, nn = n;
		bool changed;
		while(1){
			changed = false;
			for (int i=0;i<nn;++i){
				if (angsink[i%nn].lr=='R' && angsink[(i+1)%nn].lr=='R' && angsink[(i+2)%nn].lr=='L'){
					angarr[cc] = ang(cc,'R',angsink[i%nn].i, angsink[(i+1)%nn].i, angsink[(i+2)%nn].i);
					angsink[i%nn] = angarr[cc]; angsink[(i+1)%nn] = ang(); angsink[(i+2)%nn] = ang();
					++cc;
					for (int j=0;j<nn;++j){
						if (angsink[j].isnull()){
							for (int k=j;k<nn;++k)
								angsink[k] = angsink[k+1];
							--j;
							--nn;
						}
					}
					changed = true;
				}
			}
			if (!changed)
				break;
		}
		int oldn = n;
		memset(buf,0,sizeof(buf));
		int countls = 0, countrs = 0;
		for (int i=0;i<nn;++i){
			buf[i] = angsink[i].lr;
			if (buf[i]=='L') ++countls;
			else ++countrs;
		}
		solve1();
		n = oldn;
		for (int i=0;i<nn;++i){
			angsink[i].p.x = prt[i].x;
			angsink[i].p.y = prt[i].y;
			if (n > 500){
				angsink[i].p.x *= 1000000;
				angsink[i].p.y *= 1000000;
			}
			angarr[angsink[i].i].p = angsink[i].p;
			angarr[angsink[i].i].pb.x = angsink[i].p.x;
			angarr[angsink[i].i].pb.y = angsink[i].p.y;
		}
		for (int i=0;i<nn;++i){
			if (angsink[i].iscomplex()){
				double dx, dy;
				dx = angsink[i].p.x - angsink[(i+(nn-1))%nn].p.x;
				dy = angsink[i].p.y - angsink[(i+(nn-1))%nn].p.y;
				int idx = 0, idy = 0;
				if (dx > 0) idx = 1;
				else if (dx < 0) idx = -1;
				else idx = 0;
				if (dy > 0) idy = 1;
				else if (dy < 0) idy = -1;
				else idy = 0;
				flatten(angsink[i].i, pnt(idx, idy), 0);
			}
		}
		prt.clear();
		prt.resize(n);
		std::vector<pntbd> prtd(n);
		svbd xs, ys;
		std::map<bigdouble, int> xd2i, yd2i;
		for (int i=0;i<cc;++i){
			if (angarr[i].i < n){
				prtd[angarr[i].i] = angarr[i].pb;
			}
		}
		for (int i=0;i<(int)prtd.size();++i){
			xs.push_back(prtd[i].x);
			ys.push_back(prtd[i].y);
		}
		std::sort(xs.begin(),xs.end());
		std::sort(ys.begin(),ys.end());
		xs.resize(std::unique(xs.begin(),xs.end())-xs.begin());
		ys.resize(std::unique(ys.begin(),ys.end())-ys.begin());
		for (int i=0;i<(int)xs.size();++i){
			xd2i[xs[i]] = i+1;
		}
		for (int i=0;i<(int)ys.size();++i){
			yd2i[ys[i]] = i+1;
		}
		for (int i=0;i<(int)prtd.size();++i){
			prt[i] = pnt(xd2i[prtd[i].x],yd2i[prtd[i].y]);
			//prt[i] = pnt(prtd[i].x*(1<<10),prtd[i].y*(1<<10));
		}
		// prt[i] = pnt(prtd[i].x*(1<<10),prtd[i].y*(1<<10));
		//}
	}
	//#define MATLAB_DEBUG_MODE
#ifdef MATLAB_DEBUG_MODE
	FILE *fmatlab = fopen("output1.out","wt");
#endif
#define FREOPEN_MODE
	void print(){
		int minx = 1, miny = 1;
		for (int i=0;i<(int)prt.size();++i){
			if (prt[i].x < minx) minx = prt[i].x;
			if (prt[i].y < miny) miny = prt[i].y;
		}
		for (int i=0;i<(int)prt.size();++i){
			prt[i].x = prt[i].x + (1 - minx);
			prt[i].y = prt[i].y + (1 - miny);
		}
		//printf("%d\n",area);
#ifdef MATLAB_DEBUG_MODE
		fprintf(fmatlab,"%d\n",prt.size());
		for (int i=0;i<(int)prt.size();++i){
			fprintf(fmatlab,"%d %d\n",prt[i].x,prt[i].y);
		}
#endif

		int arr = floodfill()/2;
		//printf("%d %d\n",arr, area);
		printf("%d\n",arr);
		for (int i=0;i<(int)prt.size();++i){
			printf("%d %d ",prt[i].x,prt[i].y);
		}
		printf("\n");
	}
}
class algorithm
{
public:
	void solution(char *input, char *output);
	/* You can add your own class functions,
	but main function call "solution" function only. */
};

void algorithm::solution(char *input, char *output)
{
	freopen(input, "rt", stdin);
	freopen(output, "wt", stdout);
	for (int T=1;T<=50;++T){
		memset(buf,0,sizeof(buf));
		scanf("%s",buf);
		if (buf[0]==0)
			break;
		area = 2147483640; 
		prt.clear();
		if (T <= 10){
			solve1();
		}
		else{
			solve2();
		}
		printf("Case# %d\n",T);
		print();
	}
}


