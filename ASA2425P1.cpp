#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

// Define the DP_OPTION structure
struct DP_OPTION
{
    int result;       // The result of the sequence
    int k;            // The split point (index of the split)
    int left_result;  // Result of the left subsequence
    int right_result; // Result of the right subsequence
};

// Define the DP_CELL structure
struct DP_CELL
{
    vector<DP_OPTION> options;           // Stores the possible DP_OPTIONs for this subsequence
    unordered_set<int> possible_results; // Stores all possible results for this subsequence
};

vector<vector<DP_CELL>> dp_cells; // DP_CELL for each subsequence

void read_input(int &n, int &m, int &expected_result, int *&sequence, int **&op_table)
{
    cin >> n >> m;

    // Allocate memory for the operation table (2D matrix of size n x n)
    op_table = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        op_table[i] = (int *)malloc(n * sizeof(int));

    // Read the operation table
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> op_table[i][j];

    // Allocate memory for the sequence (array of size m)
    sequence = (int *)malloc(m * sizeof(int));

    // Read the sequence
    for (int i = 0; i < m; i++)
        cin >> sequence[i];

    // Read the expected result
    cin >> expected_result;
}

// Checks if a value is within the valid range
inline bool valid_value(int x, int n)
{
    return x >= 1 && x <= n;
}

// Recursive function to generate the expression
string generate_expression(int i, int j, int result, int n)
{
    if (i == j) // Base case: single number
        return to_string(result);

    // Find the corresponding DP_OPTION
    DP_OPTION *option = nullptr;
    for (auto &o : dp_cells[i][j].options)
    {
        if (o.result == result)
        {
            option = &o;
            break;
        }
    }

    if (option == nullptr)
    {
        // This should not happen if the result exists
        return "";
    }

    // Recursively build the expression
    string left_expr = generate_expression(i, option->k - 1, option->left_result, n);
    string right_expr = generate_expression(option->k, j, option->right_result, n);

    string exprStr = "(" + left_expr + " " + right_expr + ")";
    return exprStr;
}

// Solves the problem
void solve(int n, int m, int expected_result, int *sequence, int **op_table)
{
    // Initialize the DP table
    dp_cells.assign(m, vector<DP_CELL>(m));

    // Initialize the base case: subsequences of size 1
    for (int i = 0; i < m; i++)
    {
        if (valid_value(sequence[i], n))
        {
            DP_OPTION base_option = {sequence[i], -1, sequence[i], sequence[i]}; // Base case: no split, only sequence[i]
            dp_cells[i][i].options.push_back(base_option);
            dp_cells[i][i].possible_results.insert(sequence[i]);
        }
    }

    // Process subsequences of size >= 2
    for (int len = 2; len <= m; len++)
    {
        for (int i = 0; i <= m - len; i++)
        {
            int j = i + len - 1;

            // Try all possible splits of the subsequence [i, j]
            for (int k = j; k > i; k--)
            {
                for (auto Xoption : dp_cells[i][k - 1].options)
                {
                    int x = Xoption.result;
                    if (!valid_value(x, n))
                        continue;

                    for (auto Yoption : dp_cells[k][j].options)
                    {
                        int y = Yoption.result;
                        if (!valid_value(y, n))
                            continue;

                        int result = op_table[x - 1][y - 1];
                        if (!valid_value(result, n))
                            continue;

                        // Insert result into dp_cells[i][j] if not already present
                        if (dp_cells[i][j].possible_results.insert(result).second)
                        {
                            DP_OPTION new_option = {result, k, x, y};
                            dp_cells[i][j].options.push_back(new_option);
                        }
                        else
                        {
                            // If the result is already present, check for better split
                            for (auto &option : dp_cells[i][j].options)
                            {
                                if (option.result == result && option.k < k)
                                {
                                    option.k = k;
                                    option.left_result = x;
                                    option.right_result = y;
                                }
                            }
                        }
                    }
                }
            }

            // Stop if all possible results (1 to n) are found
            if ((int)dp_cells[i][j].possible_results.size() == n)
                break;
        }
    }

    // Check if the expected result is possible and print the solution
    if (dp_cells[0][m - 1].possible_results.count(expected_result))
    {
        string expr = generate_expression(0, m - 1, expected_result, n);
        cout << "1\n"
             << expr << endl;
    }
    else
    {
        cout << "0" << endl;
    }
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int n, m, expected_result;

    int *sequence = nullptr;  // Dynamically allocated sequence array
    int **op_table = nullptr; // Dynamically allocated operation table

    read_input(n, m, expected_result, sequence, op_table); // Read inputs
    solve(n, m, expected_result, sequence, op_table);      // Solve the problem

    // Free allocated memory
    free(sequence);
    for (int i = 0; i < n; i++)
        free(op_table[i]);
    free(op_table);

    return 0;
}