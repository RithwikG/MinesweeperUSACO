#include <iostream>
#include <vector>

using namespace std;

int n, m, k;

int bomb = 0;

bool exitall = false;

vector<pair<int, int> > changes = {{0, 0}, {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};



// int valid(int i, int j, int val, vector<vector<int> > &bombs) {
// 	int total = 0;
// 	for (auto vals : changes) {
// 		if (i + vals.first >= 0 && i + vals.first < n && j + vals.second >= 0 && j + vals.second < m && bombs[i + vals.first][j + vals.second] == 1) total++;
// 	}

// 	if (total == val) return 0;
// 	if (total > val) return -1;
// 	if (total < val) return 1;
// }

void recurse(vector<vector<int> > &grid, vector<vector<int> > &bombs, int i, int j, vector<pair<int, int> > subset) {
	// cout << i << j << endl;
	if (exitall) return;
	if (subset.size() == k) {
		// for (auto val : subset) cout << val.first + 1 << val.second + 1 << ' ';
			// cout << endl;
		if (bombs == grid) {
			exitall = true;
			for (auto val : subset) cout << val.first + 1 << ' ' << val.second + 1 << endl;
		}
		return;
	}

	if (i > n) return;
	bool good = true;
	for (auto val : changes) {
		if (i + val.first >= 0 && i + val.first < n && j + val.second >= 0 && j + val.second < m) {
			bombs[i + val.first][j + val.second]++;
			if (bombs[i + val.first][j + val.second] > grid[i + val.first][j + val.second]) good = false;	
		}
	}

	if (i > 0 && j > 0) {
		if (bombs[i - 1][j - 1] != grid[i - 1][j - 1]) good = false;
	}

	if (j == m && i > 0) {
		if (bombs[i - 1][j] != grid[i - 1][j]) good = false;
	}

	if (good) {
		subset.push_back({i, j});
		recurse(grid, bombs, (j + 1 == m) ? i + 1 : i, (j + 1) % m, subset);
		subset.pop_back();
	}

	for (auto val : changes) {
		if (i + val.first >= 0 && i + val.first < n && j + val.second >= 0 && j + val.second < m) {
			bombs[i + val.first][j + val.second]--;	
		}
	}
	good = true;
	if (i > 0 && j > 0) {
		if (bombs[i - 1][j - 1] != grid[i - 1][j - 1]) good = false;
	}

	if (j == m && i > 0) {
		if (bombs[i - 1][j] != grid[i - 1][j]) good = false;
	}
	if (good) recurse(grid, bombs, (j + 1 == m) ? i + 1 : i, (j + 1) % m, subset);


	// if (exitall) return;
	// bool good = true;

	// vector<vector<bool> > visited(n, vector<bool>(m, false));
	// // for (auto val : bombs) {for (auto v : val) cout << v << ' ';
	// // 	cout << endl;}
	// for (int i = 0; i < n; i++) {
	// 	for (int j = 0; j < m; j++) {
	// 		if (valid(i, j, grid[i][j], bombs) != 0) {
	// 			good = false;
	// 			if (bomb == k) return;
	// 			if (valid(i, j, grid[i][j], bombs) == 1) {
	// 				for (auto val : changes) {
	// 					if (i + val.first >= 0 && i + val.first < n && j + val.second >= 0 && j + val.second < m && bombs[i + val.first][j + val.second] == -1 && !visited[i + val.first][j + val.second]) {
	// 						// cout << string(" ", bomb) << i + val.first << j + val.second << endl;
	// 						visited[i+val.first][j + val.second] = true;
	// 						bomb++;
	// 						bombs[i + val.first][j + val.second] = 1;
	// 						recurse(grid, bombs);
	// 						bombs[i + val.first][j + val.second] = -1;
	// 						bomb--;
	// 					}	

	// 				}
	// 			} else return;
	// 		}
	// 	}
	// }
	// if (bomb == k && good) {
	// 	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) if (bombs[i][j] == 1) cout << i + 1 << ' ' << j + 1 << endl;
	// 	exitall = true;
	// }
}

int main() {
	cin >> n >> m >> k;

	vector<pair<int, int> > subset;

	vector<vector<int> > grid(n, vector<int>(m));
	vector<vector<int> > bombs(n, vector<int>(m, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) cin >> grid[i][j];
	}

	// bombs[0][2] = 1;
	// bombs[1][1] = 1;
	// for (int i = 0; i < n; i++) {
	// 	for (int j = 0; j < m; j++) cout << valid(i, j, grid[i][j], bombs) << ' ';
	// 	cout << endl;

	// }
	recurse(grid, bombs, 0, 0, subset);	

	if (!exitall) cout << "NO SOLUTION" << endl;
}