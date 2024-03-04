#include <iostream> 
#include <vector> 
using namespace std; 
vector<string> split_string(string str, string range_str) { 
 // 1. Declare variables which will be used or returned. 
 vector<string> result; 
 // 2. Parse the range_str for the function 
int start_len = 0, end_len = 0;
size_t dashPos = range_str.find('-');

if (dashPos == string::npos) {
    // No dash found, fixed range input
    start_len = stoi(range_str);
    end_len = start_len;
} else {
    // Dash found, parse range
    start_len = stoi(range_str.substr(0, dashPos));
    end_len = stoi(range_str.substr(dashPos + 1));

    // Check for additional dashes or invalid positions
    if (dashPos == 0 || dashPos == range_str.length() - 1 || range_str.find('-', dashPos + 1) != string::npos) {
        cerr << "Invalid range input." << endl;
        return {}; // Return an empty vector or
    }
}

// Validate the range
if (start_len <= 0 || end_len < start_len) {
    cerr << "Invalid range input." << endl;
    return {}; // Return an empty vector
}
 // 3. Remove whitespaces from the string 
 str.erase(remove(str.begin(), str.end(), ' '), str.end()); 
 // 4. Loop through the string 
int pos = 0; 
bool useStartLen = true;  // Flag to alternate between start_len and end_len
while (pos < str.length()) { 
    // Determine the length of the next word
    int len = useStartLen ? start_len : end_len; 

    // Make sure we don't go past the end of the string
    if (pos + len > str.length()) { 
        len = str.length() - pos; 
    } 

    // Add the word to the result array
    string word = str.substr(pos, len); 
    result.push_back(word); 

    // Move to the next position
    pos += len; 

    // Toggle the flag to alternate word length
    useStartLen = !useStartLen;
}

 // 8. Sort the words using a custom comparison function  
sort(result.begin(), result.end(), [](const string& a, const string& b) {
    // First, sort segments with numbers before segments with letters
    bool isDigitA = isdigit(a[0]);
    bool isDigitB = isdigit(b[0]);
    if (isDigitA != isDigitB) {
        return isDigitA > isDigitB; // Numbers first
    }

    // Next, sort uppercase before lowercase
    bool isUpperA = isupper(a[0]);
    bool isUpperB = isupper(b[0]);
    if (isUpperA != isUpperB) {
        return isUpperA > isUpperB; // Uppercase first
    }

    // Then, if both are digits or both are letters, sort alphabetically
    // This also covers the case for both uppercase or both lowercase letters
    if (a != b) {
        return a < b; // Alphabetical order
    }

    // Finally, ensure the shortest word appears at the end
    // This is tricky because we typically sort shorter to longer, but here we want the opposite
    // So, we invert the typical comparison for length
    return a.length() > b.length(); // Shortest word at the end
});
 
    // Find the shortest word
    auto shortestIt = min_element(result.begin(), result.end(), [](const string& a, const string& b) {
        return a.length() < b.length();
    });

    // If the shortest word is not already at the end, move it there
    if (shortestIt != prev(result.end())) {
        string shortestWord = *shortestIt;
        result.erase(shortestIt); // Remove the shortest word from its current position
        result.push_back(shortestWord); // Add the shortest word at the end
    }


 // 9. Return the result computed 
 return result; 
} 

int main() { 
 string str = "abcdBabcdabc1AdabcdZaaaaa";  string range_str = "4-6"; 
 vector<string> result = split_string(str, range_str);  for (const auto& word : result) { 
 cout << word << " "; 
 } 
 cout << endl; 
 return 0; 
}
