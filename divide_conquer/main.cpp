#include <iostream>
#include <bits/stdc++.h>
using namespace std;
class Chip{
private:
    bool good;
    int id;
public:
    Chip(int init_id,int init){
        id=init_id;
        if(init){
            good=true;
        }
        else{
            good=false;
        }
    }
    Chip(){

    }
    bool run(Chip b){
        if(good){
            return b.good;//此处的good不是private属性吗？？？？？？？？？？？
        }
        else{
            return rand()%2;
        }
    }
    int get_id(){
        return id;
    }
};
int chip_test(vector<Chip>& all_chip){
    int k=all_chip.size();
    if(k<3) cout<<"i can not judge which chip is good.Please increase at least one chip"<<endl;
    while(k>3){
        int middle=k/2;
        if(k%2==1){//k为奇数
            int sum_good=0;
            for(auto it=all_chip.begin();it!=all_chip.end()-1;){
                if(it->run(*(all_chip.end()-1))) ++sum_good;
                if((all_chip.begin()-it)%2==0){
                    if(it->run(*(it+1))&&(it+1)->run(*it)){
                        int random=rand()%2;
                        if(random==1)
                            if((it+1)->run(*(all_chip.end()-1)))
                                ++sum_good;
                        it=all_chip.erase(it+random);
                    }
                    else{
                        it=all_chip.erase(it);
                        if(it->run(*(all_chip.end()-1))) ++sum_good;
                        it=all_chip.erase(it);
                    }
                }
            }
            if(sum_good>=(k-1)/2)
                    return (all_chip.end()-1)->get_id();
        }
        else{//k为偶数
            for(auto it=all_chip.begin();it!=all_chip.end();){
                if((all_chip.begin()-it)%2==0){
                    if(it->run(*(it+1))&&(it+1)->run(*it)){
                        int random=rand()%2;
                        it=all_chip.erase(it+random);
                    }
                    else{
                        it=all_chip.erase(it);
                        it=all_chip.erase(it);
                    }
                }
            }
        }
        k=all_chip.size();
    }
    if(k==1||k==2)
        return all_chip[0].get_id();
    else{
        if(all_chip[0].run(all_chip[1])&&all_chip[1].run(all_chip[0]))
            return all_chip[0].get_id();
        else
            return all_chip[2].get_id();
    }
}
int main()
{
    int num_chip;
    cin>>num_chip;
    vector<Chip> all_chips(num_chip);
    int good;
    for(int i=0;i<num_chip;++i){
        cin>>good;
        all_chips[i]=Chip(i,good);
    }

    int result=chip_test(all_chips);
    cout<<result;
    return 0;
}
