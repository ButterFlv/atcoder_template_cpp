#include<bits/stdc++.h>
int main(){
  std::random_device seed_gen;
  std::mt19937_64 engine(seed_gen());
  std::cout<<engine()<<std::endl;
}
