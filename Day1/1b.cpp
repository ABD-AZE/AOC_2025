#include<iostream>
#include<string>
#include<fstream>

using namespace std;

int main(){
  int ans=0;
  int pos = 50;
  std::ifstream f("input.txt");
  while(true){
    string s;
    long int rot;
    f>>s;
    if(s.empty()){
      cout<<ans;
      break;
    }
    rot = stol(s.substr(1,s.size()-1));
    ans += rot/100;
    rot = rot%100;
    long f_pos;
    if(s[0] == 'R'){
      f_pos = (pos+rot)%100;
      if(f_pos<pos){
        ans++;
      }
    } else{
      long f_pos = ((pos -rot)%100 + 100)%100;
      if(!f_pos) ans++;
      else if(f_pos>pos&&pos!=0) ans++;
    }
    pos = f_pos;
  }
  return 0;
}
