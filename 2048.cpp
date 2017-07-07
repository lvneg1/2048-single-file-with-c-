#include<cstdio>
#include<conio.h>
#include<windows.h>
#include<algorithm>
#include<string>
#define UP_KEY 72
#define DOWN_KEY 80
#define LEFT_KEY 75
#define RIGHT_KEY 77
#define VER "V:1.11 With Colors" 
using namespace std;
const char message[6][31]={
" ----------------------------\n",
"|     The  2048  Game      |\n",
"|   Difficultly:Easy/Hard  |\n",
"----------------------------\n",
"Loading.....................\n",
"Ticks:"
};
void GameStart();
void ClearLine();
void ClearLine(){
	for(int i=1;i<=100;i++) putchar('\b');
}
int main(){
	system("mode con lines=8 cols=34");
	system("title The 2048 Game by:Chenye Jin!");
	printf("This ver is %s!!!\n",VER);
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
int easylevel;
void init(){
	memset(mp,0,sizeof mp);
	score=0;
	printf("Press e to Easy,h to Hard.\n");
	char ch=getch();
	while(ch!='e'&&ch!='E'&&ch!='h'&&ch!='H') ch=getch();
	if(ch=='e'||ch=='E') easylevel=2;
	else easylevel=1;
	printf("Generating maps...\nPlease wait\n");printf("°´¡ü¡ý¡û¡ú·½Ïò¼üÀ´²Ù¿Ø!\n");Sleep(500);
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
	if(cnt) cnt-=(rand())%cnt;
	while(cnt>0){
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
int filescore=0;
bool breit=0;
void showEnd(int score){
		printf("Your score:%d\nMax:%d\n",score,maxnum());
		FILE*fp=fopen("score.dat","rb");char bnam[20005];
		if(fp==NULL) filescore=-1;
		else fscanf(fp,"%s%d",bnam,&filescore);fclose(fp);
		if(filescore==-1) printf("!!!There's not any history of score!\n");
		else printf("The best score is %d by %s\n",filescore,bnam);
		if(filescore<score){
			printf("Great!Your are best now!\nYour name:");char s[20005];int tmp=0;
			{
				char ch=getchar();
				while(ch!='\n') s[++tmp]=ch,ch=getchar();
			}
			fp=fopen("score.dat","wb");fprintf(fp,"%s\n%d\n",s+1,score);fclose(fp);
		}
		printf("Y to continue and N to exit:");
		char ch=getchar();while(ch!='Y'&&ch!='y'&&ch!='N'&&ch!='n') ch=getchar();
		if(ch=='\n') ch=getchar();
		if(ch=='Y'||ch=='y') breit=1;
		else if(ch=='N'||ch=='n') exit(0);
		else system("pause"),exit(0);
		system("cls");
}
void rndcolor(){
//	const char colors[]={'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
	const char colors[]="0123456789abcdef";
	string command="color ";int t=rand()%16;
	command=command+colors[t]+colors[(t+7)%16];
	system(command.c_str());
}
void GameStart(){
	init();bool nogen=0;
	while(1){
		rndcolor();
		display();
		switch(getch()){
			case UP_KEY:{
				for(int i=1;i<=2;i++) works(1);
				break;
			}
			case DOWN_KEY:{
				for(int i=1;i<=2;i++) works(2);
				break;
			}
			case LEFT_KEY:{
				for(int i=1;i<=2;i++) works(3);
				break;
			}
			case RIGHT_KEY:{
				for(int i=1;i<=2;i++) works(4);
				break;
			}
			default:{
				//printf("°´¡ü¡ý¡û¡ú·½Ïò¼üÀ´²Ù¿Ø!\n");
				nogen=1;
				break;
			} 
		}
		if(checkWin()){
			system("cls");
			for(int i=1;i<=rand()%4;i++) printf("You win!\n");
			showEnd(score);
		}
		if(checkFail()){
			system("cls");
			for(int i=1;i<=rand()%4;i++) printf("You failed!\n");
			showEnd(score);
		}
		if(breit){
			breit=0;
			break;
		}
		if(!nogen&&rand()%easylevel==0) newNum();nogen=0;
		display();
	}
}
