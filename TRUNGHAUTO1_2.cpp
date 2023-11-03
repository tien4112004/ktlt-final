/**
 * @author phanttien
 * @email phanttien@outlook.com
 * @create date 2023-06-03 12:18:25
 * @modify date 2023-06-03 12:18:48
 * @desc TRUNGHAUTO1_2
 */
#include <bits/stdc++.h>
using namespace std;

struct Stack {
};

void init(Stack s) {
    return;
}

bool full(Stack s) {
    return false;
}
// Function to return precedence of operators
int prec(char c)
{
	if (c == '^')
		return 3;
	else if (c == '/' || c == '*')
		return 2;
	else if (c == '+' || c == '-')
		return 1;
	else
		return -1;
}

// The main function to convert infix expression
// to postfix expression
void infixToPostfix(string s)
{

	stack<char> st;
	string result;

	for (int i = 0; i < s.length(); i++) {
	    char c = s[i];
        if (c == ' ') continue; 
		// If the scanned character is
		// an operand, add it to output string.
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
			|| (c >= '0' && c <= '9'))
			result += c;

		// If the scanned character is an
		// ‘(‘, push it to the stack.
		else if (c == '(')
			st.push('(');

		// If the scanned character is an ‘)’,
		// pop and add to output string from the stack
		// until an ‘(‘ is encountered.
		else if (c == ')') {
			while (st.top() != '(') {
				result += st.top();
				st.pop();
			}
			st.pop();
		}

		// If an operator is scanned
		else {
			while (!st.empty()
				&& prec(s[i]) <= prec(st.top())) {
				result += st.top();
				st.pop();
			}
			st.push(c);
		}
	}

	// Pop all the remaining elements from the stack
	while (!st.empty()) {
		result += st.top();
		st.pop();
	}

    for (int i = 0; i < result.size(); i++)
	    cout << result[i] << ' ';
}

// Driver code
int main()
{
	string exp = "";
	getline(cin, exp);

	// Function call
	infixToPostfix(exp);
	
	return 0;
}
