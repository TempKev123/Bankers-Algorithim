#include <vector>
#include <string>
using namespace std;

// Function to convert a space-separated string to an integer array
vector<int> convertStrtoArr(const string& str) {
    vector<int> result;
    int num = 0;
    bool hasNum = false;

    for (char ch : str) {
        if (isdigit(ch)) {
            num = num * 10 + (ch - '0'); // Convert character to integer
            hasNum = true;
        } else if (ch == ' ' || ch == ',') {
            if (hasNum) {
                result.push_back(num);
                num = 0;
                hasNum = false;
            }
        }
    }

    // Push last number if any
    if (hasNum) {
        result.push_back(num);
    }

    return result;
}
