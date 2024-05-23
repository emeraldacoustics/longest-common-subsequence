#include <algorithm>
#include <vector>

using namespace std;

vector<int> longest_common_subsequence(const vector<int> & P, const vector<int> & Q)
{
	vector<int> p(P.size()), q(Q.size());
	for (int i = 0; i < P.size(); i++)
		p[P[i]] = i;
	for (int i = 0; i < Q.size(); i++)
		q[Q[i]] = i;

	vector<int> lis;
	vector<vector<int> > lisv;
	for (const auto &x : Q)
	{
		int k = lower_bound(lis.begin(), lis.end(), p[x]) - lis.begin();
		if (k == lis.size())
		{
			lis.emplace_back();
			lisv.emplace_back();
		}
		lis[k] = p[x];
		lisv[k].push_back(x);
	}

	vector<vector<int> > vld(lis.size());
	for (int i = lis.size() - 1; i >= 0; i--)
	{
		if (i == lis.size() - 1)
			vld[i] = lisv[i];
		else
		{
			int k = 0;
			for (const auto &x : vld[i + 1])
			{
				for (; k < lisv[i].size() && p[lisv[i][k]] > p[x]; k++);
				for (; k < lisv[i].size() && q[lisv[i][k]] < q[x]; k++)
					vld[i].push_back(lisv[i][k]);
			}
		}
	}
	vector<int> ans;
	for (int i = 0, plmt = -1, qlmt = -1; i < lis.size(); i++)
	{
		int l = 0;
		for (; q[vld[i][l]] < qlmt; l++);
		int r = vld[i].size();
		for (; p[vld[i][r - 1]] < plmt; r--);
		int k = min_element(vld[i].begin() + l, vld[i].begin() + r) - vld[i].begin();
		ans.push_back(vld[i][k]);
		plmt = p[vld[i][k]];
		qlmt = q[vld[i][k]];
	}
	return ans;
}
