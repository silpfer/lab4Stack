#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <cctype>
#include <unordered_map>
using namespace std;

class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

//Завдання 1
bool task1(string s) {
    stack<char> brackets;
    unordered_map<char, char> mapping = {
        {')', '('},
        {']', '['},
        {'}', '{'}
    };

    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') {
            brackets.push(c);
        }
        else {
            if (brackets.empty() || brackets.top() != mapping[c]) {
                return false;
            }
            brackets.pop();
        }
    }

    return brackets.empty();
}

//Завдання 2
vector<int> task2(TreeNode* root) {
    vector<int> result;
    stack<TreeNode*> nodes;

    while (root != nullptr || !nodes.empty()) {
        while (root != nullptr) {
            nodes.push(root);
            root = root->left;
        }

        root = nodes.top();
        nodes.pop();
        result.push_back(root->val);
        root = root->right;
    }

    return result;
}

//Завдання 3
class MinStack {
    int topIndex = 0, size = 1, newSize = 1;
    int* arr = new int[size];

public:

    void push(int val) {
        if (topIndex >= size)
        {
            newSize++;
            arr = resizeArray(arr, size, newSize);
            size = newSize;
        }
        
        arr[topIndex] = val;
        topIndex++;
    }

    void pop()
    {
        newSize--;
        arr = resizeArray(arr, size, newSize);
        size = newSize; 
        topIndex--;
    }

    int top()
    {
        return arr[topIndex-1];
    }

    int getMin() {
        int min = arr[0];
        for (int i=0; i<size; i++)
        {
            min = (min > arr[i]) ? arr[i] : min;
        }
        return min;
    }

    void printStack()
    {
        for (int i = 0; i < size; i++)
        {
            cout << arr[i] << " ";
        }
    }

    int* resizeArray(int* array1d, int currentSize, int newSize) {
        int* newArray = new int[newSize];

        int elementsToCopy = (currentSize < newSize) ? currentSize : newSize;
        for (int i = 0; i < elementsToCopy; i++) {
            newArray[i] = array1d[i];
        }
        delete[] array1d;
        return newArray;
    }

};

//Завдання 4
class MyQueue {

    stack<int> input, output;

public:
    void push(int val)
    {
        input.push(val);
    }

    int pop()
    {
        while (!input.empty())
        {
            output.push(input.top());
            input.pop();
        }

        int res = output.top();
        output.pop();

        while (!output.empty())
        {
            input.push(output.top());
            output.pop();
        }

        return res;
    }

    int peek()
    {
        while (!input.empty())
        {
            output.push(input.top());
            input.pop();
        }

        int res = output.top();

        while (!output.empty())
        {
            input.push(output.top());
            output.pop();
        }

        return res;
    }

    bool empty() {
        return input.empty() && output.empty();
    }

    void printQueue() {
        while (!input.empty())
        {
            output.push(input.top());
            input.pop();
        }
        
        while (!output.empty())
        {
            cout << output.top() << " ";
            input.push(output.top());
            output.pop();
        }
    }
};

//Завдання 5
string task5(string s)
{
    stack<int> nums;
    stack<string> strs;
    string result = "";
    int num = 0;

    for (char c : s) {
        if (isdigit(c)) {
            num = (int)(c - '0');
        }
        else if (c == '[') {
            nums.push(num);
            strs.push(result);
            num = 0;
            result = "";
        }
        else if (c == ']') {
            int times = nums.top();
            nums.pop();
            string temp = strs.top();
            strs.pop();
            for (int i = 0; i < times; i++) {
                temp += result;
            }
            result = temp;
        }
        else {
            result += c;
        }
    }

    return result;
}

//Завдання 6
int task6(string s[], int size)
{
    stack<int> nums;
    int result=0;
    int a, b;

    for (int i = 0; i < size; ++i) {
        const std::string& str = s[i];

        if ((isdigit(str[0])) || (str[0] == '-' && isdigit(str[1]))) {
            nums.push(std::stoi(str));
        }
        else if (s[i] == "/")
        {
            a = nums.top();
            nums.pop();
            b = nums.top();
            nums.pop();

            result = b / a;
            nums.push(result);
        }
        else if (s[i] == "*")
        {
            a = nums.top();
            nums.pop();
            b = nums.top();
            nums.pop();

            result = b * a;
            nums.push(result);
        }
        else if (s[i] == "+")
        {
            a = nums.top();
            nums.pop();
            b = nums.top();
            nums.pop();

            result = b + a;
            nums.push(result);
        }
        else if (s[i] == "-")
        {
            a = nums.top();
            nums.pop();
            b = nums.top();
            nums.pop();

            result = b - a;
            nums.push(result);
        }
    }
            

    return result;
}

//Завдання 7
int task7(string s) {
    stack<int> st;
    int maxLen = 0;
    st.push(-1);

    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == '(') {
            st.push(i);
        }
        else {
            st.pop();
            if (st.empty()) {
                st.push(i);
            }
            else {
                maxLen = std::max(maxLen, i - st.top());
            }
        }
    }

    return maxLen;
}

int main()
{
    string s = "()", s2 = "()[]{}", s3 = "(]";

    if (task1(s))
        cout << s << " - true\n";
    else
        cout << s << " - false\n";

    if (task1(s2))
        cout << s2 << " - true\n";
    else
        cout << s2 << " - false\n";

    if (task1(s3))
        cout << s3 << " - true\n";
    else
        cout << s3 << " - false\n";

    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(NULL);
    root->right = new TreeNode(2);
    root->left->left = new TreeNode(3);

    vector<int> res = task2(root);

    for (int val : res) {
        cout << val << " ";
    }

    cout << "\n";

    MinStack st;
    st.push(-2);
    st.push(-4);
    st.push(3);
    st.pop();
    st.printStack();
    cout << "\nMinimum " << st.getMin() << "\nTop " << st.top() << "\n";

    MyQueue qu;
    qu.push(5);
    qu.push(7);
    qu.push(3);
    qu.printQueue();
    cout << "\nPop " << qu.pop() << "\n";
    qu.printQueue();
    cout << "\nPeek " << qu.peek() << "\n";
    if (qu.empty())
        cout << "Empty";
    else
        cout << "Not empty";

    string s1 = "3[a2[ac]]";
    cout << "\n" << task5(s1);

    string s4[] = { "10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+" };
    cout << "\nResult: " << task6(s4, 13);

    string s5 = ")()())";
    cout << "\nResult: " << task7(s5);
}
