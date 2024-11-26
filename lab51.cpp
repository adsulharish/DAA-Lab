#include <iostream>
#include <vector>
#include <algorithm>
 
using namespace std;

// Class to represent each item
class Item {
public:
    double value;
    double weight;
    double ratio; // value/weight ratio

    Item(double v, double w) {
        value = v;
        weight = w;
        ratio = (weight != 0) ? value / weight : 0; // Handle zero-weight case
    }

    // Comparator to sort items by value-to-weight ratio in descending order
    static bool compare(Item& a, Item& b) {
        return a.ratio > b.ratio; // Sort in descending order of ratio
    }
};

// Function to solve the fractional knapsack problem
double fractionalKnapsack(double capacity, vector<Item>& items) {
    if (capacity <= 0 || items.empty()) return 0.0; // Handle invalid cases

    // Filter out items with negative weights
    vector<Item> validItems;
    for (const auto& item : items) {
        if (item.weight > 0) validItems.push_back(item);
    }

    // Sort items by value-to-weight ratio
    sort(validItems.begin(), validItems.end(), Item::compare);

    double totalValue = 0.0; // Total value in the knapsack
    double remainingCapacity = capacity; // Remaining capacity of the knapsack

    for (const auto& item : validItems) {
        if (remainingCapacity == 0) break;

        if (item.weight <= remainingCapacity) {
            totalValue += item.value;
            remainingCapacity -= item.weight;
        } else {
            totalValue += item.value * (remainingCapacity / item.weight);
            remainingCapacity = 0;
        }
    }

    return totalValue;
}


// Brute-force knapsack recursive function
double bruteForceKnapsackRecursion(const vector<Item>& items, int index, double W) {
    if (index == items.size() || W <= 0) {
        return 0.0; // Base case
    }

    if (items[index].weight <= 0) {
        return bruteForceKnapsackRecursion(items, index + 1, W); // Skip invalid items
    }

    double exclude = bruteForceKnapsackRecursion(items, index + 1, W);
    double include = 0;
    if (items[index].weight <= W) {
        include = items[index].value + bruteForceKnapsackRecursion(items, index + 1, W - items[index].weight);
    }

    return max(include, exclude);
}


// Function to run a test case
void runTestCase(vector<Item>& items, double capacity, int testCaseNumber) {
    cout << "\nTest Case " << testCaseNumber << ":\n";
    cout << "Items (Value, Weight, Value/Weight Ratio):" << endl;
    for (size_t i = 0; i < items.size(); i++) {
        cout << "Item " << i + 1 << ": " 
             << "Value = " << items[i].value << ", "
             << "Weight = " << items[i].weight << ", "
             << "Ratio = " << items[i].ratio << endl;
    }

    double maxValueFractional = fractionalKnapsack(capacity, items);
    cout << "\nMaximum value the vehicle can carry using Fractional Knapsack: " << maxValueFractional;

    double maxValueBruteForce = bruteForceKnapsackRecursion(items, 0, capacity);
    cout << "\nMaximum value the vehicle can carry using Brute Force method: " << maxValueBruteForce << endl;
}

int main() {
    // Define normal test cases
    vector<vector<Item>> testCases = {
        { {60, 10}, {100, 20}, {120, 30} },               // Test Case 1
        { {500, 50}, {400, 40}, {300, 30}, {200, 20} },   // Test Case 2
        { {90, 10}, {80, 10}, {70, 10}, {60, 10} },       // Test Case 3
        { {5, 5}, {10, 10}, {15, 15}, {20, 20} },         // Test Case 4
        { {100, 1}, {90, 1}, {80, 1}, {70, 1}, {60, 1} }  // Test Case 5
    };
    
    // Define knapsack capacities for each test case
    vector<double> capacities = {50.0, 100.0, 30.0, 40.0, 3.0};

    // Run normal test cases
    for (size_t i = 0; i < testCases.size(); i++) {
        runTestCase(testCases[i], capacities[i], i + 1);
    }

    // Define additional edge test cases
    vector<vector<Item>> edgeCases = {
        { {60, 10}, {100, 20}, {120, 30} },                // Edge Case 1: Capacity is zero
        {},                                                // Edge Case 2: No items
        { {0, 10}, {0, 20}, {0, 30} },                     // Edge Case 3: All items have zero value
        { {100, -10}, {200, 20}, {300, 30} },              // Edge Case 4: Only consider items with positive weights
        { {60, 10}, {100, 20}, {120, 30} }                 // Edge Case 5: Capacity is negative
    };
    
    // Define capacities for each edge test case
    vector<double> edgeCapacities = {0.0, 50.0, 50.0, 50.0, -10.0};

    // Run edge test cases
    for (size_t i = 0; i < edgeCases.size(); i++) {
        runTestCase(edgeCases[i], edgeCapacities[i], i + 6); // Edge cases start from Test Case 6
    }

    return 0;
}
