#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;
typedef struct nomPereDist
{string nom,pere;
   int d;
}nomPereDist;
int existe(nomPereDist t[],string s,int n)
{for(int k=0;k<=n;k++)
    if (t[k].nom == s)
        return k;
return -1;
}
bool trouve(pair <string,string>m[30][320],string ch,string s)
{int i(0),j(0);
  while(m[i][j].first != "nil")
  {while(m[i][j].first != "nil")
       {if(m[i][j].first==ch && m[i][j].second==s)
          return true;
        j++;
       }
i++;j=0;}
return false;
}

int main()
{ifstream metro("metro_paris.txt",ios_base::in);
     string x,ch,sArrivee,sDepart;
     int i(0),j(0);
     pair<string,string> m[30][320];///mat de (nomLigne,nomStation)
    for(int i=0;i<20;i++)
      for(int j=0;j<320;j++)
        m[i][j].first="nil";
    nomPereDist t[320];
    if (metro)
        cout<<"OK"<<endl;
    else cout<<"Erreur"<<endl;
    int taille=0;
    /*** Remplissage de la mat ***/
    int v(0),p;
    j=-1;
    string x1;
while( metro)
{if(v==0) getline(metro,x);
       if(x != "")
       {if(x.substr(0,5)=="Ligne"){ch=x;getline(metro,x);}//cout<<"ch= "<<ch<<"x= "<<x<<endl;
        p=existe(t,x,j);//cout<<p<<endl;
    if(p == -1 && x!="")
         {j++;
             m[0][j].first=ch; m[0][j].second=x;
         t[j].nom=x;t[j].pere="nil";t[j].d=99999;taille++;
          i=1;
         }
    else if (p!=-1  )  ///x existe dans le tableau.
         {i=1;x1=x;getline(metro,x);bool tr=false;//cout<<x<<endl;
         while(m[i][p].first != "nil")
               {if(m[i][p].second == x) { tr=true;break;}
               else i++;
               }
           if(tr==false && x1 != x && x!= ""){m[i][p].first=ch; m[i][p].second=x;}
       v=1;   continue;
         }
    if(i == 1 )
        {getline(metro,x);//cout<<x<<endl;
        if(x != "") {m[i][j].first=ch; m[i][j].second=x;v=1;}
        else v=0;
       }
       }
    else v=0;
}
/*cout<<"j= "<<j<<endl;
       for(int k=0;k<taille;k++)
       {cout<<t[k].pere<<"-->"<<t[k].nom<<"\t"<<t[k].d<<endl;}*/
       do
       {cout <<"Donner la station de depart: ";getline(cin,x);
       p=existe(t,x,taille);
      }while(p==-1);
      t[p].d=0;
    ///*** Le parcour ***/
    int w=0,n=2,r=2;
    string ch1,ch2;
for (int cpt=0;cpt<taille-1;cpt++)
 {for(int k=0;k<taille;k++)
    {int i=1,p=existe(t,m[0][k].second,taille);
     while(m[i][k].first != "nil")
      {int p2=existe(t,m[i][k].second,taille);
      ch1=m[0][k].first;ch2=m[i][k].first;///cout<<"ch1= "<<ch1<<" et ch2= "<<ch2<<endl;
     if(atoi(ch1.substr(6,2).c_str())>9)n=3;
     if(atoi(ch2.substr(6,2).c_str())>9)r=3;
      if(ch1.substr(6,n)==ch2.substr(6,r)||trouve(m,ch1,m[i][k].second) ) w=2;
      else w=6;
      if(t[p2].d > t[p].d+w)
        {t[p2].d= t[p].d+w;
         t[p2].pere=m[0][k].second;}
  i++; }
      }
}
 do
   {cout <<"Donner la distination : ";getline(cin,sArrivee);
       p=existe(t,sArrivee,taille);
   }while(p == -1);
      /*** Affichage ***/
      puts("°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°") ;
puts( "°°°°°°°°°°°                  RESULT                    °°°°°°°°°°°°°°°°°°°°°°") ;
 int s(0),cpt(0);cout<<"\n"<<'\n';
 x1=sArrivee;
  s=t[p].d;
 nomPereDist  tab[taille];
while(x1 != "nil")
{tab[cpt].nom=x1;
   cpt++;
   x1=t[p].pere;
    p=existe(t,x1,taille);
}

cpt--;
cout<<" La plus cours chemin est:"<<endl;
while(cpt != 0)
{cout<<tab[cpt].nom<<"-->";
cpt--;}
cout<<tab[0].nom<<endl;
cout<<"le temps necessaire est "<<s<<" min."<<endl;

char c=1;cout<<endl;
cout<<"°°°°°°°°°°°°°°°°°°°°°"<<c<<c<<c<<c<<c<<c<<c<<c<<"  FIN  "<<c<<c<<c<<c<<c<<c<<c<<c<<"°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°" ;
    return 0;
}
