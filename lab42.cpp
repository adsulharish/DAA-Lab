#include <iostream>
#include <vector>

using namespace std;

// Function to count inversions using brute force method
int count_inversions_brute_force(const vector<int>& course_choices)
{
    int count = 0;
    int n = course_choices.size();

    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            if (course_choices[i] > course_choices[j])
            {
                ++count;
            }
        }
    }

    return count;
}

// Function to merge and count inversions
int merge_and_count(vector<int>& arr, int left, int mid, int right)
{
    int i = left;
    int j = mid;
    int k = 0;
    int inv_count = 0;
    
    vector<int> temp(right - left + 1);

    while (i < mid && j <= right)
    {
        if (arr[i] <= arr[j])
        {
            temp[k++] = arr[i++];
        }
        else
        {
            temp[k++] = arr[j++];
            inv_count += (mid - i);
        }
    }

    while (i < mid)
    {
        temp[k++] = arr[i++];
    }

    while (j <= right)
    {
        temp[k++] = arr[j++];
    }

    for (i = left, k = 0; i <= right; ++i, ++k)
    {
        arr[i] = temp[k];
    }

    return inv_count;
}

// Recursive function to count inversions using divide and conquer
int count_inversions_dnc(vector<int>& arr, int left, int right)
{
    int inv_count = 0;

    if (left < right)
    {
        int mid = left + (right - left) / 2;
        
        inv_count += count_inversions_dnc(arr, left, mid);
        inv_count += count_inversions_dnc(arr, mid + 1, right);
        inv_count += merge_and_count(arr, left, mid + 1, right);
    }

    return inv_count;
}

// Function to test inversion count for a given set of course choices
void test_inversion_count(const vector<int>& course_choices)
{
    int brute_force_count = count_inversions_brute_force(course_choices);
    vector<int> course_choices_copy = course_choices;
    int dnc_count = count_inversions_dnc(course_choices_copy, 0, course_choices_copy.size() - 1);

    cout << "Brute Force Inversion Count: " << brute_force_count << endl;
    cout << "Divide and Conquer Inversion Count: " << dnc_count << endl;
    cout << "----------------------------" << endl;
}

// Main function with 3 different cases
int main()
{
    // Case 1: Course code choices in ascending order (no inversions)
    vector<int> case1 = {
        101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 
        111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 
        121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 
        131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 
        141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 
        151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 
        161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 
        171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 
        181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 
        191, 192, 193, 194, 195, 196, 197, 198, 199, 200
    };

    // Case 2: Course code choices in descending order (maximum inversions)
    vector<int> case2 = {
        200, 199, 198, 197, 196, 195, 194, 193, 192, 191, 
        190, 189, 188, 187, 186, 185, 184, 183, 182, 181, 
        180, 179, 178, 177, 176, 175, 174, 173, 172, 171, 
        170, 169, 168, 167, 166, 165, 164, 163, 162, 161, 
        160, 159, 158, 157, 156, 155, 154, 153, 152, 151, 
        150, 149, 148, 147, 146, 145, 144, 143, 142, 141, 
        140, 139, 138, 137, 136, 135, 134, 133, 132, 131, 
        130, 129, 128, 127, 126, 125, 124, 123, 122, 121, 
        120, 119, 118, 117, 116, 115, 114, 113, 112, 111, 
        110, 109, 108, 107, 106, 105, 104, 103, 102, 101
    };

    // Case 3: Course code choices randomly shuffled
    vector<int> case3 = {
        150, 112, 130, 178, 105, 190, 115, 145, 169, 120, 
        101, 140, 180, 162, 111, 172, 160, 125, 117, 195, 
        102, 108, 157, 192, 122, 109, 170, 161, 198, 103, 
        123, 141, 174, 184, 134, 116, 177, 119, 133, 165, 
        147, 139, 155, 149, 110, 128, 182, 106, 118, 136, 
        137, 167, 191, 121, 146, 126, 189, 156, 132, 164, 
        166, 114, 151, 124, 152, 193, 153, 179, 181, 104, 
        154, 107, 142, 138, 131, 185, 173, 129, 183, 194, 
        171, 199, 135, 176, 158, 188, 143, 127, 144, 148, 
        159, 163, 187, 186, 100, 175, 168, 186, 200, 113
    };

    cout << "Test Case 1 (Ascending Order):" << endl;
    test_inversion_count(case1);

    cout << "Test Case 2 (Descending Order):" << endl;
    test_inversion_count(case2);

    cout << "Test Case 3 (Random Shuffled):" << endl;
    test_inversion_count(case3);

    return 0;
}
