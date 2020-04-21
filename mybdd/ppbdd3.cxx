#include <bdd.h>
#include<stdio.h>
#include <time.h>
#include <stdlib.h>
#include<fstream>
#include<ctype.h>
#define varnum 49
#define tnum 35
 main(void )
{
 using namespace std ;

int i,j,k,bddnodenum;
double f;
 bdd pn,pninit,pnfrom,pnnew,to,pnbad,pngood;
 bdd p[varnum][4],q[varnum][4],et[tnum],cet[tnum];
 bdd_init(100000,10000);
bdd_setvarnum(8*varnum);
for(i=0;i<varnum;i++)
for(j=0;j<4;j++)
{p[i][j]=bdd_ithvar(i*4+j);
q[i][j]=bdd_ithvar((i+varnum)*4+j);
}
//define M0 ,  transion mix //////////
char  ch[4],chline[80];
int pt,m,tp;
int m0[varnum];
int tpre[tnum][varnum]={0};
int tpos[tnum][varnum]={0};

ifstream input;
input.open("1.pnt");
if(!input.is_open()) printf("File open failed! Please check  your file naame\n");
else  {input.getline(chline,sizeof(chline));
for(i=0;i<varnum;i++)
{
input.getline(chline,sizeof(chline));
j=0;
while(chline[j]==' ') j++;
k=0;
while(chline[j]!=' ')
{ch[k]=chline[j];
k++;
j++;
}
m=atoi(ch);
while(chline[j]==' ') j++;
k=0;
while(chline[j]!=' ')
{ch[k]=chline[j];
k++;
j++;
}
ch[k]='\0';
m0[m-1]=atoi(ch);
while(chline[j]!=',')
{if (chline[j]==' ') j++;
else 
{k=0;
while((chline[j]!=' ')&&(chline[j]!=','))
{ch[k]=chline[j];
k++;
j++;
}
ch[k]='\0';
tp=0;
while(tpos[atoi(ch)-1][tp]!=0) tp++;
tpos[atoi(ch)-1][tp]=m;
}
}
j++;
while(chline[j]!='\0')
{if (chline[j]==' ') j++;
else 
{k=0;
while((chline[j]!=' ')&&(chline[j]!='\0'))
{ch[k]=chline[j];
k++;
j++;
}
ch[k]='\0';
tp=0;
while(tpre[atoi(ch)-1][tp]!=0) tp++;
tpre[atoi(ch)-1][tp]=m;
tp++;
}
}
}
for(i=0;i<varnum;i++)
printf("%4d",m0[i]);
printf("\n");
for(i=0;i<tnum;i++)
   { 
   for(j=0;j<varnum;j++)
     printf("%4d",tpos[i][j]);
     printf("\n");
    }

 
//get infint bdd
pninit=bddtrue;
for(i=0;i<varnum;i++)
   {
    m=m0[i];
    for(j=0;j<4;j++)
        {
	 if(m%2==0) pninit=bdd_apply(pninit,bdd_not(p[i][j]),bddop_and);
	 else pninit=bdd_apply(pninit,p[i][j],bddop_and);
	 m=m/2;
	}
   }
  printf("The infinit pn is:\n");
  bdd_printset(pninit);
  printf("\n");
  //set pairs
  bddPair *pair=bdd_newpair();
 int oldvar[varnum][4];
int newvar[varnum][4];
for(i=0;i<varnum;i++)
for(j=0;j<4;j++)
{oldvar[i][j]=i*4+j+4*varnum;
newvar[i][j]=i*4+j;
}

  //computer et[i]
  bdd det;
  for(i=0;i<tnum;i++)
      {
      et[i]=bddtrue;
      for(j=0;j<varnum;j++)
      {
       det=bddtrue;
       if(tpre[i][j]==0) break;
       for(k=0;k<4;k++)
              {
	       det=bdd_apply(det,bdd_not(p[tpre[i][j]-1][k]),bddop_and);
	      }      
     //bdd_printset(det);
     //printf(" above:\n");
     et[i]=bdd_apply(et[i],bdd_not(det),bddop_and);
     }
     }
     bdd_printset(et[1]);
     //
     bdd add[varnum],reduce[varnum],a[4];
     for(i=0;i<varnum;i++)
         {
	 reduce[i]=bddtrue;
	 a[0]=bdd_apply(q[i][0],p[i][0],bddop_xor);
	 a[1]=bdd_apply(p[i][1],p[i][0],bddop_biimp);
	 a[1]=bdd_apply(a[1],q[i][1],bddop_biimp);
	 a[2]=bdd_apply(bdd_not(p[i][0]),bdd_not(p[i][1]),bddop_and);
	 a[2]=bdd_apply(a[2],p[i][2],bddop_xor);
	 a[2]=bdd_apply(a[2],q[i][2],bddop_biimp);
	 a[3]=bdd_apply(bdd_not(p[i][2]),bdd_apply(bdd_not(p[i][1]),bdd_not(p[i][0]),bddop_and),bddop_and);
	 a[3]=bdd_apply(a[3],p[i][3],bddop_xor);
	 a[3]=bdd_apply(a[3],q[i][3],bddop_biimp);
	 for(j=0;j<4;j++)
	     {
	     reduce[i]=bdd_apply(reduce[i],a[j],bddop_and);
	     }
	 add[i]=bddtrue;
	 a[0]=bdd_apply(q[i][0],p[i][0],bddop_xor);
	 a[1]=bdd_apply(p[i][1],p[i][0],bddop_xor);
	 a[1]=bdd_apply(a[1],q[i][1],bddop_biimp);
	 a[2]=bdd_apply(p[i][0],p[i][1],bddop_and);
	 a[2]=bdd_apply(a[2],p[i][2],bddop_xor);
	 a[2]=bdd_apply(a[2],q[i][2],bddop_biimp);
	 a[3]=bdd_apply(p[i][2],bdd_apply(p[i][1],p[i][0],bddop_and),bddop_and);
	 a[3]=bdd_apply(a[3],p[i][3],bddop_xor);
	 a[3]=bdd_apply(a[3],q[i][3],bddop_biimp);
	 for(j=0;j<4;j++)
	     {
	     add[i]=bdd_apply(add[i],a[j],bddop_and);
	     }
	 }
  //computer pn
 pn=pnfrom=to=pninit;
 while(1)
 {
  for(i=0;i<tnum;i++)
      {
       pnnew=bdd_apply(pnfrom,et[i],bddop_and);
       if(pnnew==bddfalse) continue;
       printf("\n pnfrom is:\n");
       bdd_printset(pnnew);
       for(j=0;j<varnum;j++)
           {
	   if(tpre[i][j]==0) break;   
	   pnnew=bdd_apply(pnnew,reduce[tpre[i][j]-1],bddop_and);
	   bdd_setpairs(pair,oldvar[tpre[i][j]-1],newvar[tpre[i][j]-1],4);
	   for(k=0;k<4;k++)
	        pnnew=bdd_exist(pnnew,p[tpre[i][j]-1][k]);
	   pnnew=bdd_replace(pnnew,pair);
	   }
       for(j=0;j<varnum;j++)
          {
	   if(tpos[i][j]==0) break;   
	  pnnew=bdd_apply(pnnew,add[tpos[i][j]-1],bddop_and);
	   bdd_setpairs(pair,oldvar[tpos[i][j]-1],newvar[tpos[i][j]-1],4);
	   for(k=0;k<4;k++)
	        pnnew=bdd_exist(pnnew,p[tpos[i][j]-1][k]);
	   pnnew=bdd_replace(pnnew,pair);
	   for(k=0;k<4;k++)
	        pnnew=bdd_exist(pnnew,q[tpos[i][j]-1][k]);
	  }
	  to=bdd_apply(to,pnnew,bddop_or);
//for(i=0;i<varnum;i++)
//pnnew=bdd_exist(pnnew,bdd_ithvar(i));
//pnnew=bdd_replace(pnnew,pair);
//pnto=bdd_apply(pn,pnnew,bddop_or);
printf("\n pnnew is:\n");
bdd_printset(pnnew);
//pnfrom=bdd_apply(pnto,bdd_not(pn),bddop_and);
//pn=pnto;
      }
pnfrom=bdd_apply(to,bdd_not(pn),bddop_and);
if(pnfrom==bddfalse) break;
pn=to=bdd_apply(pn,pnfrom,bddop_or);
}
for(k=0;k<4*varnum;k++)
    pn=bdd_apply(pn,bdd_ithvar(k+4*varnum),bddop_and);
f=bdd_satcount(pn);
for(k=0;k<4*varnum;k++)
     pn=bdd_exist(pn,bdd_ithvar(k+4*varnum));
printf("\n pn is   %f states:\n",f);
bdd_printset(pn);
}
bdd_done();
}
