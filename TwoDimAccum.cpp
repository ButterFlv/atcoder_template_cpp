template <typename num1>
struct TwoDimAccum{
public:
  int H,W;
  vector<vector<num1>> acc;

  // コンストラクタ
  TwoDimAccum(const vector<vector<num1>>&);

  // H1<=h<H2, W1<=w<W2 を満たす A[h][w] の総和
  template <typename num2>
  num1 sum(num2,num2,num2,num2);

  // 0<=h<H1, 0<=w<W1 を満たす A[h][w] の総和
  template <typename num2>
  num1 sum0(num2,num2);
};

template <typename num1>
TwoDimAccum<num1>::TwoDimAccum(const vector<vector<num1>>& arg){
  H=arg.size(); W=arg.front().size(); acc.resize(H+1, vector<num1>(W+1));
  for(int i=0;i<H;i++)for(int j=0;j<W;j++)acc[i+1][j+1]+=acc[i+1][j]+arg[i][j];
  for(int j=0;j<W;j++)for(int i=0;i<H;i++)acc[i+1][j+1]+=acc[i][j+1];
}

template <typename num1>
template <typename num2>
num1 TwoDimAccum<num1>::sum(num2 H1,num2 W1,num2 H2,num2 W2){return sum0(H2,W2)-sum0(H2,W1)-sum0(H1,W2)+sum0(H1,W1);}

template <typename num1>
template <typename num2>
num1 TwoDimAccum<num1>::sum0(num2 H1,num2 W1){return acc[H][W]*(H1/H)*(W1/W)+acc[H1%H][W]*(W1/W)+acc[H][W1%W]*(H1/H)+acc[H1%H][W1%W];}
