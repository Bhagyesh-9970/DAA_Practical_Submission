#include <bits/stdc++.h>
using namespace std;
using namespace chrono;
struct Order {
string id;
system_clock::time_point ts;
};
void gen(vector<Order>& o) {
auto base = system_clock::from_time_t(timegm(new tm{0,0,12,24,5,125}));
mt19937 g(random_device{}());
uniform_int_distribution<> d(0,100000);
for(int i=0;i<o.size();i++)
o[i] = {"ORD"+to_string(i+1), base + minutes(d(g))};
}
void mergeVec(vector<Order>& o,int l,int m,int r){
int n1=m-l+1,n2=r-m;vector<Order>L(n1),R(n2);
for(int i=0;i<n1;i++)L[i]=o[l+i];
for(int j=0;j<n2;j++)R[j]=o[m+1+j];
int i=0,j=0,k=l;
while(i<n1&&j<n2) o[k++]=(L[i].ts<=R[j].ts)?L[i++]:R[j++];
while(i<n1)o[k++]=L[i++];
while(j<n2)o[k++]=R[j++];
}
void mergeSort(vector<Order>& o,int l,int r){
if(l>=r)return;
int m=l+(r-l)/2;
mergeSort(o,l,m);
mergeSort(o,m+1,r);
mergeVec(o,l,m,r);
}
void printN(vector<Order>& o,int n){
for(int i=0;i<min(n,(int)o.size());i++){
time_t t=system_clock::to_time_t(o[i].ts);
char b[30];
strftime(b,sizeof(b),"%Y-%m-%dT%H:%M:%SZ",gmtime(&t));

cout<<"OrderId : "<<o[i].id<<", Timestamp : "<<b<<endl;
}
}
int main(){
const int N=1'000'000;
vector<Order> o(N);
cout<<"Generating orders...\n";
gen(o);
cout<<"Sorting orders by timestamp...\n";
auto s=high_resolution_clock::now();
mergeSort(o,0,o.size()-1);
auto e=high_resolution_clock::now();
double t=duration<double>(e-s).count();
cout<<"Done! sorted "<<N<<" orders in "<<fixed<<setprecision(2)<<t<<" seconds.\n\n";
cout<<"first 10 sorted orders\n";
printN(o,10);
}
