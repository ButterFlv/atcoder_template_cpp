template <typename int_like_1>
struct TwoDimAccum
{
  int H,W;
  vector<vector<int_like_1>> acc;
  TwoDimAccum(const vector<vector<int_like_1>>& arg)
  {
    H=arg.size(); W=arg.front().size();
    acc.resize(H+1, vector<int_like_1>(W+1));
    for(int i=0;i<H;i++)for(int j=0;j<W;j++)acc[i+1][j+1]+=acc[i+1][j]+arg[i][j];
    for(int j=0;j<W;j++)for(int i=0;i<H;i++)acc[i+1][j+1]+=acc[i][j+1];
  }
  template <typename il2> /* il2 : int_like_2 */
  int_like_1 sum(const il2&H1,const il2&W1,const il2&H2,const il2&W2)
  {
    return sum0(H2,W2)-sum0(H2,W1)-sum0(H1,W2)+sum0(H1,W1);
  }
  private:
  template <typename il2> /* il2 : int_like_2 */
  int_like_1 sum0(const il2&H1,const il2&W1)
  {
    return (
      acc[H][W] * (H1/H) * (W1/W)
      +acc[H1%H][W] * (W1/W)
      +acc[H][W1%W] * (H1/H)
      +acc[H1%H][W1%W]
    );
  }
};
