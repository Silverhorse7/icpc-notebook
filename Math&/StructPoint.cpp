#include<bits/stdc++.h>
 
using namespace std;
 
typedef long double ld;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<ld,int> pld;
 
const ld EPS = 1e-10;
const ld INF = 1e20;
 
struct Pt {
	ld x,y;
	int ind;
	Pt(ld a, ld b) : x(a),y(b) {}
	Pt() {}
};
 
inline bool EQ(ld a, ld b) {
	return abs(a-b) < EPS;
}
inline ld sq(ld n) {
	return n*n;
}
inline Pt operator-(Pt a,Pt b) {
	return Pt(a.x-b.x,a.y-b.y);
}
inline Pt operator+(Pt a,Pt b) {
	return Pt(a.x+b.x,a.y+b.y);
}
inline Pt operator*(ld k,Pt a) {
	return Pt(k*a.x,k*a.y);
}
inline Pt operator/(Pt a,ld k) {
	return Pt(a.x/k,a.y/k);
}
inline ld operator*(Pt a, Pt b) {
	return a.x*b.x + a.y*b.y;
}
inline ld operator^(Pt a, Pt b) {
	return a.x*b.y-a.y*b.x;
}
inline bool operator<(Pt a, Pt b) {
	if (!EQ(a.x,b.x)) return a.x < b.x;
	if (!EQ(a.y,b.y)) return a.y < b.y;
	return a.ind > b.ind;
}
inline bool operator==(Pt a,Pt b) {
	return EQ(a.x,b.x) and EQ(a.y,b.y);
}
 
inline ld norm(Pt a) {
	return sqrt(sq(a.x) + sq(a.y));
}
inline ld norm2(Pt a) {
	return (sq(a.x) + sq(a.y));
}
inline ld dist(Pt a, Pt b) {
	return norm(a-b);
}
inline Pt unit(Pt a) {
	return a/norm(a);
}
inline ld area2(Pt a, Pt b, Pt c) {
	return (a-c)^(b-c);
}
inline Pt rot(Pt a) {
	return Pt(-a.y,a.x);
}
