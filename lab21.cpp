 #include <iostream>
  #include <vector>

  // Linear Search (Iterative)
  int linearSearch(const std::vector<int>& arr, int target) {
      for (size_t i = 0; i < arr.size(); ++i) {
          if (arr[i] == target) {
              return i;  // Return the index where the target is found
          }
      }
      return -1;  // Return -1 if the target is not found
  }

  // Binary Search (Recursive)
  int binarySearch(const std::vector<int>& arr, int start, int end, int target) {
      if (start <= end) {
          int mid = start + (end - start) / 2;

          // Check if target is present at mid
          if (arr[mid] == target) {
              return mid;
          }

          // If target is smaller, it must be in the left subarray
          if (arr[mid] > target) {
              return binarySearch(arr, start, mid - 1, target);
          }

          // Otherwise, the target must be in the right subarray
          return binarySearch(arr, mid + 1, end, target);
      }

      return -1;  // Return -1 if the target is not found
  }

  // Test Cases for Linear Search
  void testLinearSearch() {
      std::vector<std::vector<int>> testCases = {
          {},                       // Case 1: Empty array
          {1, 2, 3, 4, 5, 6},       // Case 2: Target is 5
          {6, 6, 6},                // Case 3: All elements are 6
          {10, 90, 40, 160, 70},    // Case 4: Target is not present
          {-2, 3, 0, -8, 14}        // Case 5: Negative and positive numbers
      };
      std::vector<int> targets = {0, 5, 6, 65, 3};
      std::vector<int> expected = {-1, 4, 0, -1, 1};

      for (size_t i = 0; i < testCases.size(); ++i) {
          int result = linearSearch(testCases[i], targets[i]);
          std::cout << "Linear Search Test Case " << i + 1 << ":" << std::endl;
          std::cout << "Array: ";
          for (int num : testCases[i]) std::cout << num << " ";
          std::cout << std::endl;
          std::cout << "Target: " << targets[i] << std::endl;
          std::cout << "Expected Output: " << expected[i] << std::endl;
          std::cout << "Actual Output: " << result << std::endl;
          std::cout << (result == expected[i] ? "Test Passed" : "Test Failed") << std::endl;
          std::cout << std::endl;
      }
  }

  // Test Cases for Binary Search
  void testBinarySearch() {
      std::vector<std::vector<int>> testCases = {
          {8, 11, 13, 18, 21, 30},   // Case 1: Target is 21
          {-84, 84, 813},            // Case 2: Target is not present
          {},                        // Case 3: Empty array
          {3, 9, 27, 51, 81},        // Case 4: Target is not present
          {0, 0, 9, 18}              // Case 5: Target is 0
      };
      std::vector<int> targets = {21, 831, 51, 82, 0};
      std::vector<int> expected = {4, -1, -1, -1, 0};

      for (size_t i = 0; i < testCases.size(); ++i) {
          int result = binarySearch(testCases[i], 0, testCases[i].size() - 1, targets[i]);
          std::cout << "Binary Search Test Case " << i + 1 << ":" << std::endl;
          std::cout << "Array: ";
          for (int num : testCases[i]) std::cout << num << " ";
          std::cout << std::endl;
          std::cout << "Target: " << targets[i] << std::endl;
          std::cout << "Expected Output: " << expected[i] << std::endl;
          std::cout << "Actual Output: " << result << std::endl;
          std::cout << (result == expected[i] ? "Test Passed" : "Test Failed") << std::endl;
          std::cout << std::endl;
      }
  }

  int main() {
      std::cout << "Testing Linear Search:" << std::endl;
      testLinearSearch();
      std::cout << std::endl;

      std::cout << "Testing Binary Search:" << std::endl;
      testBinarySearch();

      return 0;
  }
