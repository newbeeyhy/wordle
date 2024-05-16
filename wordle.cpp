#include<bits/stdc++.h>

#define ll long long
#define il inline 

using namespace std;

int read(){
    int x=0,f=1; char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {x=(x<<1)+(x<<3)+(ch^48); ch=getchar();}
    return x*f;
}

struct mystr{
    char s[6];
    void r() {scanf("%s",s);}
    void w() {printf("%s\n",s);}
    friend bool operator == (mystr a,mystr b){
        for(int i=0;i<5;i++){
            if(a.s[i]!=b.s[i]) return false;
        }
        return true;
    }
};

int n,lst;
mystr word[2400];
mystr match[2400][2400];
mystr ret[250],I;
int dic[27];
int now[2400];
double Q[2400];
int tot;

void judge(int x,int y){
    mystr a=word[x],b=word[y],c;
    memset(dic,0,sizeof(dic));
    for(int i=0;i<5;i++){
        if(a.s[i]==b.s[i]){
            c.s[i]='G';
            a.s[i]=b.s[i]='X';
        }
    }
    for(int i=0;i<5;i++){
        if(a.s[i]!='X') dic[a.s[i]-'a']++;
    }
    for(int i=0;i<5;i++){
        if(b.s[i]!='X'&&dic[b.s[i]-'a']) c.s[i]='Y',dic[b.s[i]-'a']--;
        else if(b.s[i]!='X') c.s[i]='B';
    }
    match[x][y]=c;
}

int calc(){
    for(int i=1;i<=n;i++){
        if(!now[i]) continue;
        Q[i]=0;
        double cnt;
        for(int k=1;k<=tot;k++){
            cnt=0;
            for(int j=1;j<=n;j++){
                if(!now[j]) continue;
                if(match[j][i]==ret[k]) cnt+=1;
            }
            if(cnt==0) continue;
            Q[i]+=cnt/(double)lst*(double)(-log2(cnt/(double)lst));
        }
    }
    int guess=0;
    for(int i=1;i<=n;i++){
        if(!now[i]) continue;
        if(Q[i]>Q[guess]) guess=i;
    }
    printf("Guess: ");word[guess].w();
    return guess;
}

int init(){
    ifstream infile1("wordle.txt");
    while(infile1.getline(word[++n].s,6));
    lst=n;
    for(int i=1;i<=n;i++) now[i]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            judge(i,j);
        }
    }
    ifstream infile2("ret.txt");
    while(infile2.getline(ret[++tot].s,6));
    printf("There are %d words in total.\n",n);
    printf("Loading...\n");
    return calc();
}

int main(){
    int guess=init();
    mystr s;
    while(1){
        s.r();
        for(int i=1;i<=n;i++){
            if(now[i]&&!(match[i][guess]==s)) now[i]=0,lst--;
        }
        if(lst==1){
            for(int i=1;i<=n;i++){
                if(now[i]){
                    word[i].w();
                    break;
                }
            }
            printf("Finish!!!\n");
            break;
        }
        guess=calc();
        printf("Last %d words.\n",lst);
    }
    getchar();getchar();
    return 0;
}