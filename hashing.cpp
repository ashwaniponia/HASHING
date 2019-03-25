#include<bits/stdc++.h>
using namespace std;

int prime(int n){
    int ans;
    for(int i=n;i<=100000;i++){
        bool flag=true;
        for(int j=2;j<=sqrt(i);j++){
            if(i%j==0){
                flag=false;
                break;
            }
        }
        if(flag){
          ans=i;
          break;
        }
    }

return ans;
}


struct node{
  string key;
  string phone;
  int chain;
};

class hashing{
int pri;
int choice;
node *p;
int records;
float alpha;
int n;
public:
 hashing(int pr){
     records=0;
     alpha=0;
     pri=pr;
     n=pr;
     p=new node[n]; 
     for(int i=0;i<n;i++){
         p[i].chain=-1;
         p[i].key="";
         p[i].phone="";
     }
 }
 int h(string s);
 ~hashing(){
     delete []p;
 }

void choice_menu();
bool without_replacement(node *p,string s,string ph,int n);
bool search(string s);
bool with_replacement(node *p,string s,string ph,int n);
void helper(string s,string ph);
void display();
};

void hashing::choice_menu(){
   cout<<"\nWITHOUT REPLACEMENT OR WITH REPLACEMENT ";
   cin>>choice;
}

int hashing::h(string s){
    int hash=0;
    for(int i=0;i<s.size();i++){
        hash+=(s[i]-'A')*(i+1);
    }
    return hash;
}

void hashing::helper(string s,string ph){

  bool  ans= (choice==1)?without_replacement(p,s,ph,n):with_replacement(p,s,ph,n);
   if(ans){
       records++;
   }else{
       int m=prime(2*n);
       node *temp=new node[m];
       for(int i=0;i<m;i++){
           temp[i].key="";
           temp[i].phone="";
           temp[i].chain=-1;
       }     
       for(int i=0;i<n;i++){
           (choice==1)?without_replacement(temp,p[i].key,p[i].phone,m):with_replacement(temp,p[i].key,p[i].phone,m);
       }
       (choice==1)? without_replacement(temp,s,ph,m):with_replacement(temp,s,ph,m);
       delete []p;
       p=temp;
       n=m;
       records++;
   }

}

bool hashing::search(string s){
    
    bool found=false;
    
    int hash=h(s);
    hash=hash%n;
    while(p[hash].chain!=-1 && p[hash].key!=s){
        hash=(hash+31)%n;
    }
    
    if(p[hash].key==s)
     {  
         cout<<p[hash].phone<<endl;
         return true;  
     }

    int temp=p[hash].chain;
    while(temp!=-1){
        if(p[hash].key==s){
            cout<<p[hash].phone<<endl;
            return true;
        }
        temp=p[temp].chain;
    }

    return false; 
}

void hashing::display(){

    cout<<"\n-------------DISPLAYING HASH TABLE------------\n";
    cout<<"\t\tRECORD\t\t PHONE \t\t\tCHAIN\n";
    for(int i=0;i<n;i++){
      cout<<i<<"\t\t"<<p[i].key<<"\t\t"<<p[i].phone<<"\t\t\t"<<p[i].chain<<endl;
    }
}

bool hashing::without_replacement(node *p,string s,string ph,int n){
  
  int prime_no=31;
  alpha=(float)records/n;
  int hash;
  if(alpha < 0.5){
  hash=h(s);
  hash=hash%n;
  while(p[hash].key!=""){
      int temp=hash;
      hash=(hash+prime_no)%n;
      p[temp].chain=hash;
  }
  p[hash].key=s;
  p[hash].phone=ph;
  return true;
  }
  return false;
}

bool hashing::with_replacement(node *p,string s,string ph,int n){

int prime_no=31;
  alpha=(float)records/n;
  int hash=0;
  if(alpha < 0.5){
   hash=h(s);
   hash=hash%n;
  
  if(p[hash].key==""){
      p[hash].key=s;
      p[hash].phone=ph;
  }

 else if(p[hash].key!=""){
      if(h(p[hash].key)==hash){
          int t;
          while(p[hash].key!=""){
           t=hash;
           hash=(hash+prime_no)%n;
           p[t].chain=hash;
          }
       p[t].chain=hash;
       p[hash].key=s;
       p[hash].phone=ph;
      }else{
          int temp=hash,t;
         while(p[hash].key!=""){
          t=hash;
          hash=(hash+prime_no)%n;
          p[t].chain=hash;
         }
       p[t].chain=hash;
       p[hash].key=p[temp].key;
       p[hash].phone=p[temp].phone;
       
       p[temp].key=s;
       p[temp].phone=ph;

      }  
   }
   return true;
  }

  return false;
}



int main(){
    
    int n;
    int ch;
    cout<<"\nEnter the number of records to be inserted:";
    cin>>n;
    
    int m=prime(n);
  
    hashing obj(m);
    obj.choice_menu();
    for(int i=0;i<n;i++)
     {string s1,s2;
         cout<<"\nEnter the string to be inserted into the table:";
         cin>>s1;
         cout<<"\nEnter the phone number to be inserted:";
         cin>>s2;
         obj.helper(s1,s2);
         obj.display();
     }
     
     do{
     string s;
     cout<<"\nEnter a  string to be searched in the table:";
     cin>>s;
     bool ans=obj.search(s);
     if(ans){
         cout<<"\nRECORD FOUND SUCCESSFULLY!";
     }else{
         cout<<"\nNO RECORD FOUND!";
     }
      cout<<"\n0.EXIT 1.CONTINUE:";
      cin>>ch;

     }while(ch!=0);
    
    return 0;
}