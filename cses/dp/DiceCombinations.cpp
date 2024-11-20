#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1000000007;

// Problem Approach:
// Given a target sum `t`, calculate the number of ways to reach it using dice rolls (1 to 6).
// This is a classic Dynamic Programming (DP) problem.
// Two approaches: Memoized (top-down recursion with cache) and Tabulated (bottom-up iterative).

/* 
Memoized Approach (Commented Out):
1. Use recursion to calculate the number of ways to reach `t` from `curr`.
2. Use a `dp` array to store already computed results to avoid redundant calculations.
3. Recursively compute ways for all valid dice rolls (1 to 6).
*/

int helper (int curr, int target, vector<int> &dp) {
    // Base case: if current position equals target, one valid way is found
    if(curr == target) return 1;
    
    // Return cached result if already computed
    if(dp[curr] != -1) return dp[curr];
    
    int ways = 0;
    for(int i = 6; i > 0; i--) { // Iterate over dice rolls (1 to 6)
        if(curr + i <= target) { // Check if dice roll doesn't exceed target
            ways = ((ways % mod) + helper(curr + i, target, dp) % mod) % mod;
        }
    }
    
    // Store the result in dp array
    return dp[curr] = ways % mod;
}

void solve(int t) {
    int curr = 0;
    vector<int> dp(t + 1, -1); // Initialize dp array with -1 (uncomputed state)
    int ans = helper(curr, t, dp); // Compute result using helper function
    cout << ans % mod << "\n";
    return;
}

/*
Tabulated Approach (Current Implementation):
1. Use a `dp` array where `dp[i]` represents the number of ways to reach sum `i`.
2. Initialize `dp[0] = 1` (1 way to get sum 0: no dice rolls).
3. For every possible sum from 1 to `t`, compute it iteratively using dice rolls (1 to 6).
dp[i] = dp[i-1] + dp[i-2] .... dp[i-6] . note that reaching the target sums adds 1 to number of ways and not 1 roll of dice.
4. Use modulo arithmetic to avoid overflow and handle large values.
*/

void solve(int t) {
    vector<int> dp(t + 1, 0); // Create DP array initialized to 0
    dp[0] = 1; // Base case: 1 way to achieve sum 0

    // Fill the DP array iteratively
    for (int i = 1; i <= t; i++) { // For every sum from 1 to t
        for (int j = 1; j <= 6; j++) { // Iterate over dice rolls (1 to 6)
            if (j <= i) { // Check if dice roll does not exceed current sum
                dp[i] = (dp[i] % mod + dp[i - j] % mod) % mod;
            }
        }
    }

    cout << dp[t] % mod; // Output the result stored in dp[t]
}

int main() {
    ios::sync_with_stdio(false); // Optimize input/output
    cin.tie(nullptr); // Disable synchronization with C-style I/O

    int t; // Target sum
    cin >> t;
    solve(t); // Call the solve function
    return 0;
}
