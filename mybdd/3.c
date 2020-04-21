#include <bdd.h>
#include <time.h>
#define varnum 14

 main(void )
{
time_t tval;
struct tm *now;
	//显示当前时间
    tval = time(NULL);
    now = localtime(&tval);
    printf("现在时间: %4d年 %d月 %02d日 %d:%02d:%02d\n",  now->tm_year+1900,now->tm_mon+1, now->tm_mday, now->tm_hour, now->tm_min,now->tm_sec);

int i,j,k,bddnodenum;
double f;
 bdd pn,pninit,pnfrom,pnnew,to,pnbad,pngood;
 bdd p[14],et[10],cet[10];
 bdd_init(100000,10000);
bdd_setvarnum(14);

et[0]=bdd_ithvar(0);
et[1]=bdd_apply(bdd_ithvar(1),bdd_ithvar(12),bddop_and);
et[2]=bdd_apply(bdd_ithvar(2),bdd_ithvar(13),bddop_and);
et[3]=bdd_apply(bdd_ithvar(3),bdd_ithvar(4),bddop_and);
et[4]=bdd_ithvar(5);
et[5]=bdd_ithvar(6);
et[6]=bdd_apply(bdd_ithvar(7),bdd_ithvar(13),bddop_and);
et[7]=bdd_apply(bdd_ithvar(8),bdd_ithvar(12),bddop_and);
et[8]=bdd_apply(bdd_ithvar(9),bdd_ithvar(10),bddop_and);
et[9]=bdd_ithvar(11);

int dat[10][14]={{0,1,1,2,2,2,2,2,2,2,2,2,2,2},
                      {2,0,2,1,2,2,2,2,2,2,2,2,0,2},
		      {2,2,0,2,1,2,2,2,2,2,2,2,2,0},
		      {2,2,2,0,0,1,2,2,2,2,2,2,2,2},
		      {1,2,2,2,2,0,2,2,2,2,2,2,1,1},
		      {2,2,2,2,2,2,0,1,1,2,2,2,2,2},
		      {2,2,2,2,2,2,2,0,2,1,2,2,2,0},
		      {2,2,2,2,2,2,2,2,0,2,1,2,0,2},
		      {2,2,2,2,2,2,2,2,2,0,0,1,2,2},
		      {2,2,2,2,2,2,1,2,2,2,2,0,1,1}};

for(i=0;i<14;i++)
{
p[i]=bdd_ithvar(i); 
}
pn=bdd_apply(p[0],p[6],bddop_and);
pn=bdd_apply(pn,p[12],bddop_and);
pn=bdd_apply(pn,p[13],bddop_and);
for(i=1;i<6;i++)
{
pn=bdd_apply(pn,p[i],bddop_diff);
}
for(i=7;i<12;i++)
{
pn=bdd_apply(pn,p[i],bddop_diff);
}
pninit=pn;
to=pninit;
pnfrom=pninit;
k=0;
while(pnfrom!=bddfalse)
{
printf("\n\nThe %dth pnfrom is :\n\n",k);
bdd_printset(pnfrom);
for(i=0;i<10;i++)
{
pnnew=bdd_apply(pnfrom,et[i],bddop_and);
if (pnnew==bddfalse)
 {printf("\nt%d  unenable",i);
continue;}
printf("\nt%d  enable pnnew is:\n",i);
bdd_printset(pnnew);
for(j=0;j<varnum;j++)
{if (dat[i][j]==0)
 {pnnew=bdd_exist(pnnew,bdd_ithvar(j));
  pnnew=bdd_apply(pnnew,bdd_nithvar(j),bddop_and);
  }
  else if (dat[i][j]==1)
  {pnnew=bdd_exist(pnnew,bdd_ithvar(j));
  pnnew=bdd_apply(pnnew,bdd_ithvar(j),bddop_and);
  }
  }
  printf("\nfire t%d,pnnew is:\n",i);
  bdd_printset(pnnew);
  to=bdd_apply(to,pnnew,bddop_or);

  }
  pnfrom=bdd_apply(to,bdd_not(pn),bddop_and);
  pn=to;
    f=bdd_satcount(to);
  printf("\nto  is :%f\n",f);
  k++;
}
printf("\nComplete successfully!\n\nk is%d\npn is:\n",k);
bdd_printset(pn);
f=bdd_satcount(pn);
printf("\nstats number: %f\n",f);
bddnodenum=bdd_nodecount(pn);
printf("The node number of pn is: %d\n",bddnodenum);

bdd pndead=pn;
bdd pnenable;
for(i=0;i<10;i++)
{
pnenable=bdd_apply(pndead,et[i],bddop_and);
pndead=bdd_apply(pndead,bdd_not(pnenable),bddop_and);
}

if(pndead==bddfalse)
printf("This pn is not dead.\n");
else 
{f=bdd_satcount(pndead);
printf("This pn is dead.The number of dead states is %f:\ndead states:\n",f);
bdd_printset(pndead);
}

cet[0]=bdd_apply(bdd_ithvar(1),bdd_ithvar(2),bddop_and);
cet[1]=bdd_ithvar(3);
cet[2]=bdd_ithvar(4);
cet[3]=bdd_ithvar(5);
cet[4]=bdd_apply(bdd_ithvar(0),bdd_ithvar(12),bddop_and);
cet[4]=bdd_apply(cet[4],bdd_ithvar(13),bddop_and);
cet[5]=bdd_apply(bdd_ithvar(7),bdd_ithvar(8),bddop_and);
cet[6]=bdd_ithvar(9);
cet[7]=bdd_ithvar(10);
cet[8]=bdd_ithvar(11);
cet[9]=bdd_apply(bdd_ithvar(6),bdd_ithvar(12),bddop_and);
cet[9]=bdd_apply(cet[9],bdd_ithvar(13),bddop_and);
to=pninit;
pnfrom=pninit;
pngood=pninit;
k=0;
while(pnfrom!=bddfalse)
{
printf("\n\nThe %dth pnfrom is :\n\n",k);
bdd_printset(pnfrom);
for(i=0;i<10;i++)
{
pnnew=bdd_apply(pnfrom,cet[i],bddop_and);
if (pnnew==bddfalse)
 {printf("\nconvert t%d  unenable",i);
continue;}
printf("\n conver t%d  enable pnnew is:\n",i);
bdd_printset(pnnew);
for(j=0;j<varnum;j++)
{if (dat[i][j]==1)
 {pnnew=bdd_exist(pnnew,bdd_ithvar(j));
  pnnew=bdd_apply(pnnew,bdd_nithvar(j),bddop_and);
  }
  else if (dat[i][j]==0)
  {pnnew=bdd_exist(pnnew,bdd_ithvar(j));
  pnnew=bdd_apply(pnnew,bdd_ithvar(j),bddop_and);
  }
  }
  printf("\nfire conver  t%d,pnnew is:\n",i);
  bdd_printset(pnnew);
  to=bdd_apply(to,pnnew,bddop_or);

  }
  pnfrom=bdd_apply(to,bdd_not(pngood),bddop_and);
  pngood=to;
    f=bdd_satcount(to);
  printf("\nto  is :%f\n",f);
  k++;
}
pngood=bdd_apply(pn,pngood,bddop_and);
printf("\nComplete successfully!\n\nk is%d\npngood is:\n",k);
bdd_printset(pngood);
f=bdd_satcount(pngood);
printf("\npngood states number is :%f\n",f);

pnbad=bdd_apply(pn,bdd_not(pngood),bddop_and);
printf("\npn bad states is:\n");
bdd_printset(pnbad);
f=bdd_satcount(pnbad);
printf("\npnbad states number is :%f\n",f);


// *finf event dis*//
for(i=0;i<10;i++)
{
pnnew=bdd_apply(pnbad,cet[i],bddop_and);
if (pnnew==bddfalse)
continue;
for(j=0;j<varnum;j++)
{if (dat[i][j]==1)
 {pnnew=bdd_exist(pnnew,bdd_ithvar(j));
  pnnew=bdd_apply(pnnew,bdd_nithvar(j),bddop_and);
  }
  else if (dat[i][j]==0)
  {pnnew=bdd_exist(pnnew,bdd_ithvar(j));
  pnnew=bdd_apply(pnnew,bdd_ithvar(j),bddop_and);
  }
  }
  pnnew=bdd_apply(pnnew,pn,bddop_and);

  if (pnnew!=bddfalse)
 { printf("\ndis states   is:  t%d\n",i);
  bdd_printset(pnnew);
  }
}
printf("\nAll missions done!!\n");

	//显示当前时间
    tval = time(NULL);
    now = localtime(&tval);
    printf("现在时间: %4d年 %d月 %02d日 %d:%02d:%02d\n",  now->tm_year+1900,now->tm_mon+1, now->tm_mday, now->tm_hour, now->tm_min,now->tm_sec);

bdd_done();
}
