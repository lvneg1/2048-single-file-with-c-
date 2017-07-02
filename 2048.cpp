#include<cstdio>
#include<conio.h>
#include<windows.h>
#include<algorithm>
#define UP_KEY 72
#define DOWN_KEY 80
#define LEFT_KEY 75
#define RIGHT_KEY 77
using namespace std;
const char message[6][31]={
" ----------------------------\n",
"|     The  2048  Game      |\n",
"|         发行版 1         |\n",
"----------------------------\n",
"Loading.....................\n",
"Ticks:"
};
void GameStart();
int main(){
	system("mode con lines=10 cols=40");
	system("title The 2048 Game by:Chenye Jin!");
	for(int i=0;i<6;i++){
		for(int j=0;j<=strlen(message[i]);j++){
			putchar(message[i][j]);
			Sleep(40);
		}
	}
	for(int i=3;i>=0;i--) Sleep(1000),printf("\b%d",i);
	system("cls");
	while(1){
		GameStart();
	}
	return 0;
}
int mp[4][4],score=0;
int getval(){
//	switch(rand()%3){
//		case 0:return 2;
//		case 1:return 4;
//		case 2:return 8;
//	}
	return (1<<(rand()%3)+1);
}
void init(){
	memset(mp,0,sizeof mp);
	score=0;
	printf("\tGenerating maps... Please wait\t\n");printf("按↑↓←→方向键来操控!\n");Sleep(500);
	srand(GetTickCount());
	int cnt=rand()%(7-4+1)+4;
	while(cnt){
		int x=rand()%4,y=rand()%4;
		while(mp[x][y]) x=rand()%4,y=rand()%4;
		mp[x][y]=getval();
		cnt--;
	}
	system("cls");
}
void display(){
	system("cls");
	printf("\nYour score:%d\n",score);
	printf("----------------------------\n");
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(j==0) putchar('|');
			printf(" %4d ",mp[i][j]);
			if(j==3) putchar('|');
		}putchar('\n');
	}
	printf("----------------------------\n");
}
void newNum(){
	int tot=0;
	for(int i=0;i<4;i++)
	  for(int j=0;j<4;j++)
		if(!mp[i][j]) tot++;
	if(tot==0) return;
	int cnt=rand()%tot+1;
	if(tot>4) cnt/=2;
	while(cnt){
		int x=rand()%4,y=rand()%4;
		while(mp[x][y]) x=rand()%4,y=rand()%4;
		mp[x][y]=getval();
		cnt--;
	}
}
bool checkWin(){
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(mp[i][j]>=2048) return 1;
		}
	}
	return 0;
}
bool checkFail(){
	int tot=0;
	for(int i=0;i<4;i++)
	  for(int j=0;j<4;j++)
		if(mp[i][j]) tot++;
	if(tot!=16) return 0;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(j!=3&&mp[i][j]==mp[i][j+1]) return 0;
			if(j!=0&&mp[i][j]==mp[i][j-1]) return 0;
			if(i!=3&&mp[i][j]==mp[i+1][j]) return 0;
			if(i!=0&&mp[i][j]==mp[i-1][j]) return 0;
		}
	}
	return 1;
}
int cmp(int a[4][4],int b[4][4]){
	for(int i=0;i<4;i++)
	  for(int j=0;j<4;j++)
	  	if(a[i][j]>b[i][j]) return -1;
	  	else if(a[i][j]<b[i][j]) return 1;
	return 0;
}
const int f[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
bool yes(int x,int y){
	if(x<0||y<0||x>3||y>3) return 0;
	return 1;
}
void works(int cur){cur-=1; 
//	for(int k=1;k<=16;k++){
	for(int i=0;i<4;i++){
	  for(int j=0;j<4;j++){
	  	if(yes(i+f[cur][0],j+f[cur][1])&&mp[i+f[cur][0]][j+f[cur][1]]==mp[i][j]) mp[i+f[cur][0]][j+f[cur][1]]+=mp[i][j],score+=mp[i+f[cur][0]][j+f[cur][1]],mp[i][j]=0;
	  }
	}
	for(int k=1;k<=4;k++)
	  for(int i=0;i<4;i++){
	    for(int j=0;j<4;j++){
	    	if(yes(i+f[cur][0],j+f[cur][1])&&!mp[i+f[cur][0]][j+f[cur][1]]) swap(mp[i+f[cur][0]][j+f[cur][1]],mp[i][j]);
	    }
	  }

//	}
}
int maxnum(){
	int mx=0;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			mx=max(mx,mp[i][j]);
		}
	}
}
void GameStart(){
	init();bool nogen=0;
	while(1){
		display();
		if(!nogen) newNum();nogen=0;
		switch(getch()){
			case UP_KEY:{
				works(1);
				break;
			}
			case DOWN_KEY:{
				works(2);
				break;
			}
			case LEFT_KEY:{
				works(3);
				break;
			}
			case RIGHT_KEY:{
				works(4);
				break;
			}
			default:{
				printf("按↑↓←→方向键来操控!\n");
				nogen=1;
				break;
			} 
		}
		if(checkWin()){
			system("cls");
			for(int i=1;i<=rand()%4;i++) printf("You win!\n");
			printf("Score:%d\nMax:%d\n",score,maxnum());
			printf("Y to continue and N to exit:");
			char ch=getchar();while(ch!='Y'&&ch!='y'&&ch!='N'&&ch!='n') ch=getchar();
			if(ch=='Y'||ch=='y') break;
			else if(ch=='N'||ch=='n') exit(0);
			else system("pause"),exit(0);
		}
		if(checkFail()){
			system("cls");
			for(int i=1;i<=rand()%4;i++) printf("You failed!\n");
			printf("Score:%d\nMax:%d\n",score,maxnum());
			printf("Y to continue and N to exit:");
			char ch=getchar();while(ch!='Y'&&ch!='y'&&ch!='N'&&ch!='n') ch=getchar();
			if(ch=='Y'||ch=='y') break;
			else if(ch=='N'||ch=='n') exit(0);
			else system("pause"),exit(0);
		}
		display();
	}
}
