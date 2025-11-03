#include <bits/stdc++.h>
using namespace std;
using namespace chrono;
struct Movie {
string title;
float rating;
int year, popularity;
void show() const {
printf("%s | Rating: %.1f | Year: %d | Popularity: %d\n", title.c_str(), rating, year, popularity);
}
};
using Comp = function<bool(const Movie&, const Movie&)>;
int partition(vector<Movie>& v, int l, int h, Comp cmp) {
Movie pivot = v[h];
int i = l;
for (int j = l; j < h; j++) if (cmp(v[j], pivot)) swap(v[i++], v[j]);
swap(v[i], v[h]);
return i;
}
void quickSort(vector<Movie>& v, int l, int h, Comp cmp) {
if (l < h) {
int p = partition(v, l, h, cmp);
quickSort(v, l, p - 1, cmp);
quickSort(v, p + 1, h, cmp);
}
}
vector<Movie> genMovies(int n) {
vector<Movie> v(n);
mt19937 g(random_device{}());
uniform_int_distribution<> rd(10,99), yd(1980,2024), pd(1000,1'000'000);
for (int i = 0; i < n; i++)
v[i] = {"Movie " + to_string(i+1), rd(g)/10.0f, yd(g), pd(g)};
return v;
}
int main() {
int n = 100'000;
auto movies = genMovies(n);
cout << "Sort movies by (rating/year/popularity): ";
string s; cin >> s;
Comp cmp;
if (s=="rating") cmp=[](auto&a,auto&b){return a.rating<b.rating;};
else if (s=="year") cmp=[](auto&a,auto&b){return a.year<b.year;};

else if (s=="popularity") cmp=[](auto&a,auto&b){return a.popularity<b.popularity;};
else {cout<<"Invalid choice. Defaulting to rating.\n"; cmp=[](auto&a,auto&b){return a.rating<b.rating;};}
auto st=high_resolution_clock::now();
quickSort(movies,0,n-1,cmp);
auto en=high_resolution_clock::now();
cout<<"\nTop 10 movies by "<<s<<" (highest first):\n";
for(int i=n-1;i>=n-10;i--) movies[i].show();
cout<<"\nSorted "<<n<<" movies in "<<duration<double>(en-st).count()<<" seconds.\n";
}
