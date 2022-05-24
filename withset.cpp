#include <iostream>
#include <algorithm>
#include <fstream>
#include <set>
#include <vector>
#include <map>

using namespace std;
const int maxi=1000;
int tg[maxi];
int to[maxi];
int har[maxi];
int enj[maxi];
set<int> kopoli;
set<int> R1;
set<int> R2;
int qg[maxi];
int qo[maxi];
set<int> G1;
set<int> G2;
int which[maxi];
set<int> s[maxi];
vector<int> done;
int rto[maxi];
int greed,times;

set<int> g2(int l);
set<int> r2(int l);

map<int, set<int> >sg2;
map<int, set<int> >sr2;
map<pair<int,int>, set<int> >salt;
set<int> alt(int l,int t){
    cerr<<"alt "<<l<<' '<<t<<" started"<<endl;
    set<int> jav;
    jav.clear();
    if(t==0){
        cerr<<"alt "<<l<<' '<<t<<" ended"<<endl;
        return jav;
    }

    if(salt[make_pair(l,t)].size()){
        cerr<<"alt "<<l<<' '<<t<<" ended"<<endl;
        return salt[make_pair(l,t)];
    }
    set<int> y=g2(l-1);
  //  cerr<<"injam2"<<endl;
    jav.insert(y.begin(),y.end());
    jav.insert(s[l].begin(),s[l].end());
    set<int>::iterator it=jav.begin();
    vector <int> cp;
    cp.clear();
    while(it!=jav.end()){
        if(which[*it]<=t)
            cp.push_back(*it);
        it++;
    }
    jav.clear();
    for(int i=0;i<cp.size();i++)
        jav.insert(cp[i]);

    cerr<<"alt "<<l<<' '<<t<<" ended"<<endl;
    salt[make_pair(l,t)]=jav;
    return jav;
}
//I should assess the below function about what is t_o_i exactly;
set<int> blt(int l,int t){
    cerr<<"blt "<<l<<' '<<t<<" started"<<endl;
    set<int> jav;
    jav.clear();
    if(t==0){
        cerr<<"blt "<<l<<' '<<t<<" ended"<<endl;
        return jav;
    }
    set<int> y=r2(l-1);
    jav.insert(y.begin(),y.end());
    set<int>::iterator it=jav.begin();
    while(it!=jav.end()){
        if(rto[*it]>t){
            jav.erase(it);
            it=jav.begin();
        }
        else
            it++;

    }
    cerr<<"blt "<<l<<' '<<t<<" ended"<<endl;
    return jav;
}



int tl(int l){
    cerr<<"tl "<<l<<" started"<<endl;
    for(int i=times;i>=0;i--){
        set<int> y=alt(l,i);
        set<int> z=blt(l,i);
        if(y.size()>=z.size()){
            cerr<<"tl "<<l<<" ended"<<endl;
            return i;
        }
    }
}

set<int> g2(int l){
    cerr<<"g2 "<<l<<" started"<<' '<<endl;
    set<int> jav;
    jav.clear();

    if(l==greed){
        cerr<<"g2 "<<l<<" ended"<<endl;
        return jav;
    }
    if(l==0){
        cerr<<"g2 "<<l<<" ended"<<endl;
        return jav;
    }
     if(sg2[l].size()){
        cerr<<"g2 "<<l<<" ended"<<endl;
        return sg2[l];
    }
   // cerr<<"alan injam"<<endl;
    set<int> y=g2(l-1);
    cerr<<"injam"<<endl;
    jav.insert(y.begin(),y.end());
    jav.insert(s[l].begin(),s[l].end());
    int t_l=tl(l);
    set<int> rr;
    rr.clear();
    rr=alt(l,t_l);
    jav.erase(rr.begin(),rr.end());
    sg2[l]=jav;
    cerr<<"g2 "<<l<<" ended"<<endl;
  //  cerr<<jav.size()<<endl;
    return jav;
}

set<int> r2(int l){
    cerr<<"r2 "<<l<<" started"<<endl;
    if(sr2[l].size()){
        cerr<<"r2 "<<l<<" ended"<<endl;
        return sr2[l];
    }
    set<int> jav;
    jav.clear();
    if(l==greed){
        cerr<<"r2 "<<l<<" ended"<<endl;
        return jav;
    }
    if(l==0){
        cerr<<"r2 "<<l<<" ended"<<endl;
        return R2;
    }

    set<int> y=r2(l-1);
    jav.insert(y.begin(),y.end());
    int t_l=tl(l);
    y.clear();
    y=blt(l,t_l);
    jav.erase(y.begin(),y.end());
    sr2[l]=jav;
    cerr<<"r2 "<<l<<" ended"<<endl;
    return jav;
}

/*set<int>& set<int>::operator=(const set<int>& a){
        this->clear();
        this->insert(a.begin(),a.end());
        return *this;
}*/


int main(){
    int test=600;
    ifstream fin ("backtrack.txt");
    ifstream gin("greedy.txt");
    ofstream fout("implement.txt");
    for(int ll=1;ll<=1;ll++){
        int opt;
        fin>>opt;
        int jobs;
        fin>>jobs;

        fin>>times;
        sg2.clear();
        sr2.clear();
        salt.clear();
        fill(rto,rto+maxi,0);
        fill(to,to+maxi,0);
        fill(tg,tg+maxi,0);
        fill(qg,qg+maxi,0);
        fill(qo,qo+maxi,0);
        fill(har,har+maxi,0);
        fill(enj,enj+maxi,0);
        fill(which,which+maxi,0);
        for(int i=1;i<=times;i++){
            fin>>to[i];
            if(to[i])
                rto[to[i]]=i;
        }
        for(int i=1;i<=times;i++)
            fin>>har[i];
        for(int i=1;i<=jobs;i++)
            fin>>enj[i];

        gin>>greed;
        for(int i=1;i<=times;i++){
            gin>>tg[i];
            which[tg[i]]=i;
        }
        for(int i=1;i<=greed;i++)
            s[i].clear();
        done.clear();
        done.push_back(0);

        for(int i=1;i<=greed;i++){
            int u;
            gin>>u;
            done.push_back(u);
        }
        if(ll!=1)
            continue;
        R1.clear();
        R2.clear();
        for(int i=1;i<=times;i++){
            bool con=true;
            if(to[i]>0){
                for(int j=1;j<=times;j++)
                    if(tg[j]==to[i]){
                        con=false;
                        break;
                    }
            }
            if(con==false)
                continue;
            if((tg[i]>0)&&(to[i]>0))
               R1.insert(to[i]);
            else if(to[i]>0)
                R2.insert(to[i]);
        }
        fill(qg,qg+times+1,0);
        fill(qo,qo+times+1,0);
        for(int i=1;i<=times;i++){
            if(to[i]>0)
                qo[i]=har[i]+enj[to[i]];
            if(tg[i]>0)
                qg[i]=har[i]+enj[tg[i]];
        }
        G1.clear();
        G2.clear();
        for(int i=1;i<=times;i++)
            if(tg[i]){
                if(qg[i]<=qo[i])
                    G1.insert(tg[i]);
                else
                    G2.insert(tg[i]);
            }
        fout<<"test "<<ll<<":"<<endl;
        fout<<"R1 = ";
        set<int>::iterator it=R1.begin();
        while(it!=R1.end()){
            fout<<*it<<' ';
            it++;
        }
        fout<<endl;
        fout<<"G1 = ";
        it=G1.begin();
        while(it!=G1.end()){
            fout<<*it<<' ';
            it++;
        }
        fout<<endl;
        fout<<"R2 = ";
        it=R2.begin();
        while(it!=R2.end()){
            fout<<*it<<' ';
            it++;
        }
        fout<<endl;
        fout<<"G2 = ";
        it=G2.begin();
        while(it!=G2.end()){
            fout<<*it<<' ';
            it++;
        }
        for(int i=1;i<=greed;i++)
            if(G2.find(done[i])!=G2.end())
                s[i].insert(done[i]);
        fout<<endl<<endl;
        for(int i=1;i<=greed;i++){
            cerr<<"iteration "<<i<<":"<<endl;
            set<int> k=g2(i);
        //    cerr<<" residam "<<endl;
            cerr<<"for iteration "<<i<<' '<<"size g2 = "<<k.size()<<endl;
            cerr<<endl<<endl;
        }
    }


    return 0;
}
