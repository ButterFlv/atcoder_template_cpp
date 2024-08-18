vector<vector<int>> doubling(
    int size, unsigned long long times, function<int(int)> f){
  int log2_times=0;
  while((1ULL<<(log2_times+1))<=times)log2_times++;
  vector<vector<int>> dp(log2_times+1, vector<int>(size));
  for(int i=0;i<size;i++)dp[0][i]=f(i);
  for(int i=1;i<=log2_times;i++)
    for(int j=0;j<size;j++)
      dp[i][j]=dp[i-1][dp[i-1][j]];
  return dp;
}
