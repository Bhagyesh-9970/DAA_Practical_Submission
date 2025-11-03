#include <bits/stdc++.h>
using namespace std;
struct Item {
string name;
double weight, value;
bool divisible;
int priority;
double valuePerWeight() const { return value / weight; }
};

bool compareItems(const Item &a, const Item &b) {
if (a.priority == b.priority)
return a.valuePerWeight() > b.valuePerWeight();
return a.priority < b.priority;
}
double fractionalKnapsack(vector<Item> &items, double capacity, double &totalWeightCarried) {
sort(items.begin(), items.end(), compareItems);
cout << "\nSorted Items (by Priority, then Value/Weight):\n";
printf("%-20s%-10s%-10s%-12s%-15s%-15s\n", "Item", "Weight", "Value", "Priority",
"Value/Weight", "Type");
for (auto &i : items)
printf("%-20s%-10.2f%-10.2f%-12d%-15.2f%-15s\n",
i.name.c_str(), i.weight, i.value, i.priority, i.valuePerWeight(),
(i.divisible ? "Divisible" : "Indivisible"));
double totalValue = 0.0;
totalWeightCarried = 0.0;
cout << "\nItems selected for transport:\n";
for (auto &i : items) {
if (capacity <= 0) break;
if (i.divisible) {
double takenWeight = min(i.weight, capacity);
double takenValue = i.valuePerWeight() * takenWeight;
totalValue += takenValue;
capacity -= takenWeight;
totalWeightCarried += takenWeight;
printf(" - %s: %.2f kg, Utility = %.2f, Priority = %d, Type = Divisible\n",
i.name.c_str(), takenWeight, takenValue, i.priority);
} else if (i.weight <= capacity) {
totalValue += i.value;
capacity -= i.weight;
totalWeightCarried += i.weight;
printf(" - %s: %.2f kg, Utility = %.2f, Priority = %d, Type = Indivisible\n",
i.name.c_str(), i.weight, i.value, i.priority);
}
}
return totalValue;
}
int main() {

int n;
cout << "Enter number of relief items: ";
cin >> n;
vector<Item> items(n);
for (int i = 0; i < n; i++) {
cout << "\nItem #" << i + 1 << ":\n";
cout << "Name: ";
cin.ignore(numeric_limits<streamsize>::max(), '\n');
getline(cin, items[i].name);
cout << "Weight (kg): ";
cin >> items[i].weight;
cout << "Utility Value: ";
cin >> items[i].value;
cout << "Is it divisible? (1 = Yes, 0 = No): ";
int d; cin >> d; items[i].divisible = d == 1;
cout << "Priority (1 = High, 2 = Medium, 3 = Low): ";
cin >> items[i].priority;
}
double capacity;
cout << "\nEnter maximum weight capacity of the boat (in kg): ";
cin >> capacity;
double totalWeightCarried = 0.0;
double maxValue = fractionalKnapsack(items, capacity, totalWeightCarried);
cout << "\n===== Final Report =====\n";
printf("Total weight carried: %.2f kg\n", totalWeightCarried);
printf("Total utility value carried: %.2f units\n", maxValue);
}
