#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void greedy_activity_selector(const vector<int> &s, const vector<int> &f, int n)
{
  vector<pair<int, int>> activity;
  for (int i = 0; i < n; i++)
  {
    activity.push_back({f[i], s[i]});
  }
  sort(activity.begin(), activity.end());

  vector<pair<int, int>> A = {activity[0]};
  int j = 0;
  for (int i = 1; i < n; i++)
  {
    if (activity[i].second >= activity[j].first)
    {
      A.push_back(activity[i]);
      j = i;
    }
  }

  cout << "The maximum-size subset of compatible activities is: ";
  for (auto it : A)
  {
    cout << "[" << it.second << ", " << it.first << ") ";
  }
  cout << endl;
}

int main()
{
  vector<int> s = {7, 9, 8, 4, 1, 3};
  vector<int> f = {10, 12, 9, 7, 4, 5};
  int n = s.size();
  greedy_activity_selector(s, f, n);
  return 0;
}
