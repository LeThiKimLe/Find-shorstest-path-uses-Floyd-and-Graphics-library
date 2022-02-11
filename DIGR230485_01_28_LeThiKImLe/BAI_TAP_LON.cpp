#include<stdio.h>
#include<graphics.h>
#include<windows.h>
#define MAX 99999
typedef struct tagDiem{
	int i;
	int x,y;
	char name[50];
}Diem;
typedef struct tagCriteria{
	float Init[100][100];
	float S[100][100];
	int P[100][100];
}CTR;
Diem D[50];
CTR N[5];
char kc[10],tg[10],z1[20],z2[20],z3[20];
int I;
int c[100],TF[25][25],CV[25][25];
int dem=0,dem1=0,A,B,d=0,giatri;
int u,v,bb,x,y;
void thuchien();
void Docfile();
void Vebando();
void Floyd(int n);
void Truyvet(int i);
void Xuatkq();
void xoa();
void mouseMoveHandler(int x,int y);
void mouseMoveHandler1(int x,int y);
void mouseMoveHandler2(int x,int y);
void detailwindow();
int main()
{
	Docfile();
	Floyd(1);
	Floyd(2);
	thuchien();
}
void thuchien()
{
	initwindow(1200,720);
    HWND hWnd, hWndChild;
    hWnd = FindWindow(NULL, "Windows BGI");
    hWndChild = GetWindow(hWnd, GW_CHILD);
    SendMessage((HWND) hWnd, WM_SETTEXT,0, (LPARAM)"Shortest and quickest path");
	setactivepage(0);
	setbkcolor(0);		
   	setcolor(15);
	setlinestyle(1,0,1); 
	setwritemode(COPY_PUT);
	Vebando();
	registermousehandler(WM_LBUTTONDOWN, mouseMoveHandler);
	getch();
}
void Docfile()
{
	FILE *ptr=fopen("Map.txt","rt");
	if(ptr==NULL)
		return;
	for(int i=1;i<=24;i++)
		fscanf(ptr,"%d%d%d%s",&D[i].i,&D[i].x,&D[i].y,&D[i].name);
	fclose(ptr);
	FILE *fp=fopen("Distance.txt","rt");
	if(fp==NULL)
		return;
	for(int i=1;i<=24;i++)
		for(int j=1;j<=24;j++)
			fscanf(fp,"%f",&N[1].Init[i][j]);
	fclose(fp);	
	FILE *tm=fopen("Time.txt","rt");
	if(tm==NULL)
		return;
	for(int i=1;i<=24;i++)
		for(int j=1;j<=24;j++)
			fscanf(fp,"%f",&N[2].Init[i][j]);
	fclose(tm);	
	FILE *tr=fopen("Trafficvol.txt","rt");
	if(tr==NULL)
		return;
	for(int i=1;i<=24;i++)
		for(int j=1;j<=24;j++)
			fscanf(fp,"%d",&TF[i][j]);
	fclose(tr);	
	FILE *cv=fopen("COVID.txt","rt");
	if(cv==NULL)
		return;
	for(int i=1;i<=24;i++)
		for(int j=1;j<=24;j++)
			fscanf(fp,"%d",&CV[i][j]);
	fclose(cv);	
}
void Vebando()
{
	settextstyle(3,0,2);
	char s[10];
	A=781,B=1000;
	line(A,0,A,B);
	for(int i=1;i<=24;i++)
		for(int j=1;j<=24;j++)
			if(N[1].Init[i][j]>0){
				line(D[i].x,D[i].y,D[j].x,D[j].y);
				d=d+1;
		}
	setlinestyle(0,0,1);		
	for(int i=1;i<=24;i++)
	{
		rectangle(D[i].x-50,D[i].y-15,D[i].x+50,D[i].y+15);
		outtextxy(D[i].x-35,D[i].y-12,D[i].name);
	}
	settextstyle(3,0,1);
	setcolor(11);
	outtextxy(A+5,0," *Click to select Departure anh Destination*");
}
void mouseMoveHandler(int x,int y)
{
	
	for(int i=1;i<=24;i++)
	{
		if((x>=D[i].x-50)&& (x<=D[i].x+50) && (y>=D[i].y-15) && (y<=D[i].y+15))
			{
				setlinestyle(0,0,3);
				setcolor(12);
				rectangle(D[i].x-50,D[i].y-15,D[i].x+50,D[i].y+15);
				dem=dem+1;
				if (dem==2)
				{
					v=i;
					break;
				}
				u=i;
				break;
			}
		if(dem==2)
			break;
	}
	setcolor(15);
	setlinestyle(1,0,1); 
	if(dem==2)
	{
		outtextxy(A+5,40,"     *Click to select criteria for your path*");
		rectangle(A+5,97,A+150,127);
		outtextxy(A+10,100,"  Shortest Path");
		rectangle(A+5,127,A+300,350);
		rectangle(A+5,367,A+150,397);
		outtextxy(A+10,370," Quickest Path");
		rectangle(A+5,397,A+300,620);
		registermousehandler(WM_LBUTTONDOWN, mouseMoveHandler1);
	}
}
void mouseMoveHandler1(int x,int y)
{
	setactivepage(0);
	if(x>=A+5 && x<=A+150 && y>=97 && y<=127)
	{
		setcolor(0);
	    setlinestyle(0,0,3);
	    rectangle(A+5,367,A+150,397);
		setcolor(15);
	    setlinestyle(1,0,1);
	    rectangle(A+5,367,A+150,397);
	    setlinestyle(0,0,3);
	    setcolor(12);
		rectangle(A+5,97,A+150,127);
		dem1=dem1+1;
		if (dem1>=2)
		xoa();
		giatri=1;
		Xuatkq();
	}
	if(x>=A+5 && x<=A+150 && y>=367 && y<=397)
	{
		setcolor(0);
	    setlinestyle(0,0,3);
	    rectangle(A+5,97,A+150,127);
		setcolor(15);
	    setlinestyle(1,0,1);
		rectangle(A+5,97,A+150,127);
		setlinestyle(0,0,3);
     	setcolor(12);
		rectangle(A+5,367,A+150,397);
		dem1=dem1+1;
		if (dem1>=2)
		xoa();
		giatri=2;
		Xuatkq();
	}
	if((((x-A-125)*(x-A-125)+(y-293)*(y-293))<=25*25 && giatri==1) || (((x-A-125)*(x-A-125)+(y-563)*(y-563))<=25*25 && giatri==2))
		detailwindow();	
	setactivepage(0);
	{
		setlinestyle(3,3,3);
		setcolor(12);
		outtextxy(A+58,653,"Exit");
		outtextxy(A+109,653,"X");
		rectangle(A+100,650,A+130,680);
		setcolor(10);
		outtextxy(A+180,653,"Restart");
		outtextxy(A+257,653,"O");
		rectangle(A+250,650,A+280,680);
    	if(x>=A+100 && x <=A+130 && y>=650 && y<=680)
		exit(0);
		if(x>=A+250 && x<=A+280 && y>=650 && y<=680)
    	{		
		closegraph();
		dem=0;
		dem1=0;
		thuchien();
    	}			
	}	
}
void Floyd(int n)
{
	int j,i;
	float t;
	for(i=1;i<=24;i++)
		for(j=1;j<=24;j++)
		{
			if(N[n].Init[i][j]==0)
				N[n].S[i][j]=MAX;
			else
				N[n].S[i][j]=N[n].Init[i][j];
			N[n].P[i][j]=i;
		}
	for(int k=1;k<=24;k++)
		for(int i=1;i<=24;i++)
			for(int j=1;j<=24;j++)
			{
				t=N[n].S[i][k]+N[n].S[k][j];
				if(t>MAX)
					t=MAX;
				if(N[n].S[i][j]>t)
				{
					N[n].S[i][j]=t;
					N[n].P[i][j]=N[n].P[k][j];
				}
			}
}

void Xuatkq()
{
	setactivepage(0);
	int dau,cuoi;
	float z;
	char zc[10]; 
	if (giatri==1)
	{
		Truyvet(1);
		for(int i=bb;i>0;i--)
			z=z+N[2].Init[c[i]][c[i-1]];
		setcolor(15);
		snprintf(kc,10,"%.1f",N[1].S[u][v]);
		outtextxy(A+10,157,"Total distance   :");
		outtextxy(A+175,157,kc);outtextxy(A+230,157,"km");
		outtextxy(A+10,187,"Total travel time: ");
		snprintf(zc,10,"%.0f",z);
		outtextxy(A+177,187,zc);outtextxy(A+230,187,"minutes");
		outtextxy(A+10,230,"Click here for detail:");
		outtextxy(A+10,280,"======>");
		setcolor(13);
		setlinestyle(0,0,3);
		circle(A+125,293,25);
		setcolor(15);
		settextstyle(3,0,3);
		outtextxy(A+107,281,"^_^");
		settextstyle(3,0,1);
    } 
	else if(giatri==2)
	{
		Truyvet(2);
		for(int i=bb;i>0;i--)
			z=z+N[1].Init[c[i]][c[i-1]];
		setcolor(15);	
		snprintf(tg,10,"%.0f",N[2].S[u][v]);
		snprintf(zc,10,"%.1f",z);
		outtextxy(A+10,427,"Total distance   :");
		outtextxy(A+175,427,zc);outtextxy(A+230,427,"km");
		outtextxy(A+10,457,"Total travel time: ");
		outtextxy(A+177,457,tg);
		outtextxy(A+230,457,"minutes");
		outtextxy(A+10,500,"Click here for detail:");
		outtextxy(A+10,550,"======>");
		setcolor(11);
		setlinestyle(0,0,3);
		circle(A+125,563,25);
		setcolor(15);
		settextstyle(3,0,3);
		outtextxy(A+107,551,"^_^");
		settextstyle(3,0,1);
	}
	for(int i=bb;i>0;i--)
	{
	    dau=c[i];
		cuoi=c[i-1];
		setcolor(9);
		setlinestyle(0,0,3);
		line(D[dau].x,D[dau].y,D[cuoi].x,D[cuoi].y);
		setcolor(2);
		if(i!=bb)
			rectangle(D[dau].x-50,D[dau].y-15,D[dau].x+50,D[dau].y+15);
	    if(i-1!=0)
			rectangle(D[cuoi].x-50,D[cuoi].y-15,D[cuoi].x+50,D[cuoi].y+15);
	    setcolor(15);
		outtextxy(D[dau].x-35,D[dau].y-12,D[dau].name);
		outtextxy(D[cuoi].x-35,D[cuoi].y-12,D[cuoi].name);
	}
}
void Truyvet(int i)
{
	int nb=0;
	int t=v;
	while(t!=u)
	{
		c[nb++]=t;
		t=N[i].P[u][t];
	}
	c[nb]=u;
	bb=nb;
}		
void xoa()
{
	int dau,cuoi;
	for(int i=bb;i>0;i--)
	{
	dau=c[i];
	cuoi=c[i-1];
	setcolor(0);
	setlinestyle(0,0,3);
	line(D[dau].x,D[dau].y,D[cuoi].x,D[cuoi].y);
	if(i!=bb)
		rectangle(D[dau].x-50,D[dau].y-15,D[dau].x+50,D[dau].y+15);
	if(i-1!=0)
		rectangle(D[cuoi].x-50,D[cuoi].y-15,D[cuoi].x+50,D[cuoi].y+15);
	setcolor(15);
	setlinestyle(1,0,1);
	line(D[dau].x,D[dau].y,D[cuoi].x,D[cuoi].y);
	setlinestyle(0,0,1);
	if(i!=bb)
		rectangle(D[dau].x-50,D[dau].y-15,D[dau].x+50,D[dau].y+15);
	if(i-1!=0)
		rectangle(D[cuoi].x-50,D[cuoi].y-15,D[cuoi].x+50,D[cuoi].y+15);
	outtextxy(D[dau].x-35,D[dau].y-12,D[dau].name);
	outtextxy(D[cuoi].x-35,D[cuoi].y-12,D[cuoi].name);
    }
}
void detailwindow()
{
	setactivepage(1);
	setfillstyle(1,0);
	bar(0,0,1200,720);
	setcolor(8);
	settextstyle(3,0,2);
	char s[10];
	A=781,B=1000;
	line(A,0,A,B);
	setlinestyle(1,0,1);
	for(int i=1;i<=24;i++)
		for(int j=1;j<=24;j++)
			if(N[1].Init[i][j]>0){
				line(D[i].x,D[i].y,D[j].x,D[j].y);
				}
	for(int i=1;i<=24;i++)
	{
		rectangle(D[i].x-50,D[i].y-15,D[i].x+50,D[i].y+15);
		outtextxy(D[i].x-35,D[i].y-12,D[i].name);
	}
	setlinestyle(0,0,1);
	setcolor(10);
	rectangle(A+130,60,A+240,170);
	setlinestyle(0,0,3);
	line(A+185,60,A+145,30);
	line(A+185,60,A+225,10);
	int a1[]={A+140,110,A+155,75,A+170,110};
	int a2[]={A+200,110,A+215,75,A+230,110};
	int a3[]={A+173,130,A+183,150,A+193,130,A+173,130};
	drawpoly(3,a1);
	drawpoly(4,a3);
	drawpoly(3,a2);
	setlinestyle(1,0,1);
	setcolor(15);
	outtextxy(A+10,190," *Click next to see the detail of each path*");
	rectangle(A+15,250,A+400,550);
	setlinestyle(0,0,1);
	setcolor(14);
	rectangle(A+165,580,A+225,610);
	outtextxy(A+175,585,"Next");
	rectangle(A+125,630,A+275,660);
	setcolor(2);
	outtextxy(A+172,632,"BACK");
	setlinestyle(0,0,3);
	setcolor(12);
	rectangle(D[u].x-50,D[u].y-15,D[u].x+50,D[u].y+15);
	rectangle(D[v].x-50,D[v].y-15,D[v].x+50,D[v].y+15);
	outtextxy(D[u].x-35,D[u].y-12,D[u].name);
	outtextxy(D[v].x-35,D[v].y-12,D[v].name);
	I=bb;					
	setvisualpage(1);
	registermousehandler(WM_LBUTTONDOWN,mouseMoveHandler2);
}
void mouseMoveHandler2(int x,int y)
{
	int dau,cuoi;
	if(x>=A+150 && x<=A+300 && y>=630 && y<=660)
	{
	setvisualpage(0);
	I=bb;
	registermousehandler(WM_LBUTTONDOWN,mouseMoveHandler1);	
	}
	if(x>=A+190 && x<=A+250 && y>=580 && y<=610)
	{
		
		setactivepage(1);
		if(I>0){
		dau=c[I];
		cuoi=c[I-1];
		setcolor(0);
		outtextxy(A+20,280,"                                                                     ");
		outtextxy(A+20,320,"                                                                     ");
		outtextxy(A+20,360,"                                                                     ");
		outtextxy(A+20,440,"                                                                     ");
		if(I<bb)
		{
			setcolor(0);
			line(D[c[I+1]].x,D[c[I+1]].y,D[dau].x,D[dau].y);
			setcolor(8);
			setlinestyle(1,0,1);
			line(D[c[I+1]].x,D[c[I+1]].y,D[dau].x,D[dau].y);
			setcolor(2);
			setlinestyle(0,0,3);
			rectangle(D[c[I+1]].x-50,D[c[I+1]].y-15,D[c[I+1]].x+50,D[c[I+1]].y+15);
			setcolor(15);
			outtextxy(D[c[I+1]].x-35,D[c[I+1]].y-12,D[c[I+1]].name);
		}
		setcolor(9);
		setlinestyle(0,0,3);
		line(D[dau].x,D[dau].y,D[cuoi].x,D[cuoi].y);
		setcolor(2);
		if(I-1!=0){
			rectangle(D[cuoi].x-50,D[cuoi].y-15,D[cuoi].x+50,D[cuoi].y+15);
			setcolor(15);
			outtextxy(D[cuoi].x-35,D[cuoi].y-12,D[cuoi].name);
			if(I!=bb){
			outtextxy(D[dau].x-35,D[dau].y-12,D[dau].name);setcolor(2);
			rectangle(D[dau].x-50,D[dau].y-15,D[dau].x+50,D[dau].y+15);
			}
		}
		setlinestyle(0,0,3);
		setcolor(12);
		rectangle(D[u].x-50,D[u].y-15,D[u].x+50,D[u].y+15);
		rectangle(D[v].x-50,D[v].y-15,D[v].x+50,D[v].y+15);
		outtextxy(D[u].x-35,D[u].y-12,D[u].name);
		outtextxy(D[v].x-35,D[v].y-12,D[v].name);
		outtextxy(A+20,280,"Distance");
		outtextxy(A+210,280,":");
		snprintf(z1,10,"%.1f",N[1].Init[dau][cuoi]);
		outtextxy(A+250,280,z1);
		outtextxy(A+300,280,"km");
		outtextxy(A+20,320,"Travel time");
		outtextxy(A+210,320,":");
		snprintf(z2,10,"%.0f",N[2].Init[dau][cuoi]);
		outtextxy(A+250,320,z2);
		outtextxy(A+300,320,"mins");
		outtextxy(A+20,360,"Traffic volume");
		outtextxy(A+210,360,":");
		itoa(TF[dau][cuoi],z3,10); 
		outtextxy(A+250,360,z3);
		outtextxy(A+300,360,"%");
		outtextxy(A+20,440,"Danger of COVID_19");
		outtextxy(A+210,440,":");
		if(CV[dau][cuoi]==3)
			outtextxy(A+250,440,"High");
		else
			outtextxy(A+250,440,"Medium");
		I--;
		registermousehandler(WM_LBUTTONDOWN,mouseMoveHandler2);
		}
		settextstyle(3,0,1);
	}
}


