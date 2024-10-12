#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>

int compar(const void *a,const void *b){
    return *(int*)b-*(int*)a;
}

int checkHorizontal(int turn,int TAy,int *xarr,int *yarr){
    int round=0;
    
    for(int i=0;i<turn;++i){
        if(yarr[i]==TAy) ++round;
    }
    if(round<5) return 0; 
    int *checkXArr=(int*)calloc(round,sizeof(int));
    int index=0;
    for(int i=0;i<turn;++i){
        if(yarr[i]==TAy) checkXArr[index++]=xarr[i];
    }
    qsort(checkXArr,round,sizeof(int), compar);
    int good=1;
    for(int i=0;i<round-1;++i){
        if(checkXArr[i]-checkXArr[i+1]==1){
            ++good;
            if(good>=5){
                free(checkXArr);
                return 1;
            }
        }else good=1;
    }
    free(checkXArr);
    return 0;
}

int checkDiagonalR(int turn,int TAx,int TAy,int *xarr,int *yarr,int direction){
    int pxarr[9];
    int pyarr[9];
    int round=0;
    
    for(int i=-4;i<5;++i){
        pxarr[i+4]=TAx+i;
        pyarr[i+4]=TAy+i*direction;
    }

    for(int i=0;i<turn;++i){
       for(int j=0;j<9;++j){
            if(xarr[i]==pxarr[j]&&yarr[i]==pyarr[j]){
                ++round;
            }
        } 
    }
    if(round<5) return 0;
    int *checkIndex=(int*)calloc(round,sizeof(int));
    int index=0;
    for(int i=0;i<turn;++i){
        for(int j=0;j<9;++j){
            if(xarr[i]==pxarr[j]&&yarr[i]==pyarr[j]){
                checkIndex[index++]=j;
            }
        }
    }
    qsort(checkIndex,round,sizeof(int),compar);
    int good=1;
    for(int i=0;i<round-1;++i){
        if (checkIndex[i]-checkIndex[i+1]==1){
            ++good;
            if(good>=5){
                free(checkIndex);
                return 1;
            }
        }
        else good=1;
    }
    free(checkIndex);
    return 0;
}

int enterInt(int enterInt){
    while(1){
        if(scanf("%d",&enterInt)){
            break;
        }else{
            printf("\nEnter a valid option: ");
            while(getchar()!='\n');
        }
    }
   return enterInt;
}

void kill(int turn,int*xarr,int*yarr,int killRate){ 
        int killNumber=turn*killRate*0.1;

        for (int i=0;i<killNumber; ++i) {
            int index=rand() % turn;
            xarr[index]=-1; 
            yarr[index]=-1; 
        }
    }

void cpuPlayer(int TAx,int TAy,int*xarr2,int*yarr2,int*turn2,int size,int*xarr1,int*yarr1){
        int direction;
        bool available=false;
        int failTime=0;
        int expand=1;

        while(!available){

            direction=rand()%8;

            switch(direction){

                case 0: 
                    if(TAx-expand>=0){
                        xarr2[*turn2]=TAx-expand;
                        yarr2[*turn2]=TAy;
                    }
                    break;
                case 1: 
                    if(TAx+expand<=size-1){
                        xarr2[*turn2]=TAx+expand;
                        yarr2[*turn2]=TAy;
                    }
                    break;
                case 2: 
                    if(TAy-expand>=0){
                        xarr2[*turn2]=TAx;
                        yarr2[*turn2]=TAy-expand;
                    }
                    break;
                case 3: 
                    if(TAy+expand<=size-1){
                        xarr2[*turn2]=TAx;
                        yarr2[*turn2]=TAy+expand;
                    }
                    break;
                case 4: 
                    if(TAx-expand>=0&&TAy-expand>=0){
                        xarr2[*turn2]=TAx-expand;
                        yarr2[*turn2]=TAy-expand;
                    }
                    break;
                case 5: 
                    if(TAx+expand<=size-1&&TAy-expand>=0){
                        xarr2[*turn2]=TAx+expand;
                        yarr2[*turn2]=TAy-expand;
                    }
                    break;
                case 6: 
                    if(TAx-expand>=0&&TAy+expand<=size-1){
                        xarr2[*turn2]=TAx-expand;
                        yarr2[*turn2]=TAy+expand;
                    }
                    break;
                case 7: 
                    if(TAx+expand<=size-1&&TAy+expand<=size-1){
                        xarr2[*turn2]=TAx+expand;
                        yarr2[*turn2]=TAy+expand;
                    }
                    break;
            }

            for(int i=0;i<*turn2+1;++i){
                if(xarr1[i]==xarr2[*turn2]&&yarr1[i]==yarr2[*turn2]){
                    available=false;
                    ++failTime;
                    break;
                }else available=true;
            }
            
            if(available){
                for(int i=0;i<*turn2;++i){
                    if(xarr2[i]==xarr2[*turn2]&&yarr2[i]==yarr2[*turn2]){
                        available=false;
                        ++failTime;
                        break;
                    }else available=true;
                }
            }

            
            expand=1+failTime/16;

        }

        ++*turn2;

}

void draw(int TAx,int TAy,int player,int size, int *xarr1, int *yarr1, int turn1, int *xarr2, int *yarr2, int turn2){
    system("cls");
    for(int i=0;i<size;++i){
        for(int j=0;j<size;++j){
            bool printed = false;
            for(int k=0; k<turn1; ++k){
                if(xarr1[k] == j && yarr1[k] == i){
                    if(j == TAx && i == TAy){
                        printf("∞ ");
                    } else {
                        printf("○ ");
                    }
                    printed = true;
                    break;
                }
            }
            for(int k=0; k<turn2; ++k){
                if(xarr2[k] == j && yarr2[k] == i){
                    if(j == TAx && i == TAy){
                        printf("∞ ");
                    } else {
                        printf("● ");
                    }
                    printed = true;
                    break;
                }
            }
            if(!printed){
                if(j==TAx && i==TAy){
                    if(player==1) printf("○ ");
                    else if(player==2) printf("● ");
                }else{

                    if(j==0){
                        if(i==0) printf("┌ ");
                        else if(i==size-1) printf("└ ");
                        else printf("├ ");
                    }else if(j==size-1){
                        if(i==0) printf("┐ ");
                        else if(i==size-1) printf("┘ ");
                        else printf("┤ ");
                    }else if(i==0) printf("┬ ");
                    else if(i==size-1) printf("┴ ");
                    else printf("┼ ");
                    
                }
            }
        }
        printf("\n");
    }
}

void end(int*win,char*move,int*leave,int*mode,int*size,int*turn1,int*turn2,int*player,int*TAx,int*TAy,int*xarr1,int*yarr1,int*xarr2,int*yarr2,int p1score,int p2score,int*regretTime1,int*regretTime2,int*passedTime,time_t*t,int regretTime,bool*justRegret){
    system("cls");
    draw(*TAx,*TAy,*player,*size, xarr1, yarr1, *turn1, xarr2, yarr2, *turn2);
    printf("\n");
    printf("## Game Over! ##\n");
    if(*win!=0)printf("Player %d Wins!\n",*win);
    printf("Score  P1:%d   P2:%d\n",p1score,p2score);
    printf("Continue? (y/n/m): ");
    scanf(" %c", &*move);
    while(*move != 'y' && *move != 'n'&& *move != 'm') {
        printf("\nEnter a valid option: ");
        scanf(" %c", &*move);
    }
    if(*move=='n'){
        free(xarr1);
        free(yarr1);
        free(xarr2);
        free(yarr2);
        *leave=1;
    }else if(*move=='m'){
        free(xarr1);
        free(yarr1);
        free(xarr2);
        free(yarr2);
        *mode=0;
    }else if(*move=='y'){
        free(xarr1);
        free(yarr1);
        free(xarr2);
        free(yarr2);
        
        *win=0;
        *turn1=0;
        *turn2=0;
        *player=1;
        *TAx=0;
        *TAy=0;
        *passedTime=0;
        *t=time(NULL);

        xarr1=(int*)calloc(*size**size,sizeof(int));
        yarr1=(int*)calloc(*size**size,sizeof(int));
        xarr2=(int*)calloc(*size**size,sizeof(int));
        yarr2=(int*)calloc(*size**size,sizeof(int));

        *regretTime1=regretTime;
        *regretTime2=regretTime;
        *justRegret=false;
        

    }

}

void render(int TAx,int TAy,int player,int size, int *xarr1, int *yarr1, int turn1, int *xarr2, int *yarr2, int turn2, int p1score, int p2score, int regret, int regretTime1, int regretTime2, bool justRegret, int timer, int countdown, int passedTime){
    draw(TAx,TAy,player,size, xarr1, yarr1, turn1, xarr2, yarr2, turn2);
    printf("Score  P1:%d   P2:%d\n",p1score,p2score);
    if(regret) printf("Regret P1:%d   P2:%d\n",regretTime1,regretTime2);
    printf("Player %d's turn\n",player);
    if(timer) printf("Time left: %d\n",countdown-passedTime);
    printf("Enter your move: ");
}

int main(void){
    int mode=0;

    while(mode==0){
        int size=15;
        int turn1=0;
        int turn2=0;
        int player=1;
        int TAx=0;
        int TAy=0;
        int winScore=5;
        char move;
        bool available=true;
        int p1score=0;
        int p2score=0;
        
        bool regret=true;
        int regretTime=5;
        int regretTime1=5;
        int regretTime2=5;
        bool justRegret=false;

        bool timer=false;
        time_t t=time(NULL);
        int countdown=5;
        int passedTime=0;
        
        int killRate=3;

        srand(time(NULL));
        
        int *xarr1=(int*)calloc(size*size,sizeof(int));
        int *yarr1=(int*)calloc(size*size,sizeof(int));
        int *xarr2=(int*)calloc(size*size,sizeof(int));
        int *yarr2=(int*)calloc(size*size,sizeof(int));

        int win=0;
        int leave=0;
        
        system("cls");
        printf("########################\n");
        printf("#######  Gomoku  #######\n");
        printf("####### 1  Play  #######\n");
        printf("####### 2 Scores #######\n");
        printf("####### 3  CPU   #######\n");
        printf("####### 4 Option #######\n");
        printf("####### 5  Exit  #######\n");
        printf("########################\n");
        
        mode=enterInt(mode);
        while(mode!=1&&mode!=2&&mode!=3&&mode!=4&&mode!=5&&mode!=6){
            printf("\nEnter a valid option: ");
            mode=enterInt(mode);
        }

        if(mode==4){
            system("cls");
            printf("Enter the size of the board: ");
            size=enterInt(size);
            printf("Enable regret? (y/n):");
            scanf(" %c",&move);
            while(move!='y'&&move!='n'){
                printf("\nEnter a valid option: ");
                scanf(" %c",&move);
            }
            if(move=='y') regret=true;
            else if(move=='n') regret=false;
            if(regret){
                printf("Enter times can regret: ");
                regretTime=enterInt(regretTime);
                regretTime1=regretTime;
                regretTime2=regretTime;
            }
            printf("Enable timer? (y/n):");
            scanf(" %c",&move);
            while(move!='y'&&move!='n'){
                printf("\nEnter a valid option: ");
                scanf(" %c",&move);
            }
            if(move=='y') timer=true;
            else if(move=='n') timer=false;
            if(timer){
                printf("Enter countdown time: ");
                countdown=enterInt(countdown);
            }
            
            printf("Apply to which mode? (1/2/3):");
            mode=enterInt(mode);
            while(mode!=1&&mode!=2&&mode!=3){
                printf("\nEnter a valid option: ");
                mode=enterInt(mode);
            }

        }else if(mode==5){
            free(xarr1);
            free(yarr1);
            free(xarr2);
            free(yarr2);
            return 0;
        }else if(mode==6){
        system("cls");
        printf("########################\n");
        printf("#######  Gomoku  #######\n");
        printf("####  NTUST PROJECT ####\n");
        printf("########################\n");
        printf("######   CREDIT	  ######\n");
        printf("###### Jamie Chen ######\n");
        printf("######  OCT.2024  ######\n");
        printf("########################\n");
        printf("\n");
        printf("Press any key to menu:\n");
        scanf(" %c",&move);
        mode=0;
        }    
        if(mode==2){
            printf("\n");
            printf("Enter win score: ");
            winScore=enterInt(winScore);
            printf("Enter kill rate: (0~10)");
            killRate=enterInt(killRate);

            render(TAx,TAy,player,size, xarr1, yarr1, turn1, xarr2, yarr2, turn2, p1score, p2score, regret, regretTime1, regretTime2, justRegret, timer, countdown, passedTime);
            
            t=time(NULL);
        }

        if(mode==1){
            render(TAx,TAy,player,size, xarr1, yarr1, turn1, xarr2, yarr2, turn2, p1score, p2score, regret, regretTime1, regretTime2, justRegret, timer, countdown, passedTime);
            
            t=time(NULL);
        }

    while(mode==1){
       
        if(kbhit()){
            move=getch();
            if(move=='w'&&TAy>0) --TAy;
            else if(move=='s'&&TAy<size-1) ++TAy;
            else if(move=='a'&&TAx>0) --TAx;
            else if(move=='d'&&TAx<size-1) ++TAx;
            else if(move=='f'){

                for(int i=0;i<turn1;++i){
                    if(xarr1[i]==TAx&&yarr1[i]==TAy){
                        printf("\nInvalid move");
                        available=false;
                        break;
                    }
                }

                for(int i=0;i<turn2;++i){
                    if(xarr2[i]==TAx&&yarr2[i]==TAy){
                        printf("\nInvalid move");
                        available=false;
                        break;
                    }
                }

                if(!available){
                    available=true;
                    continue;
                }

                if(player==1){
                    xarr1[turn1]=TAx;
                    yarr1[turn1]=TAy;
                    ++turn1;
                    if(checkHorizontal(turn1,TAy,xarr1,yarr1)||checkHorizontal(turn1,TAx,yarr1,xarr1)||checkDiagonalR(turn1,TAx,TAy,xarr1,yarr1,1)||checkDiagonalR(turn1,TAx,TAy,xarr1,yarr1,-1)){
                        win=1;
                        ++p1score;
                        end(&win, &move, &leave, &mode, &size, &turn1, &turn2, &player, &TAx, &TAy, xarr1, yarr1, xarr2, yarr2, p1score, p2score, &regretTime1, &regretTime2, &passedTime, &t, regretTime, &justRegret);
                        if(leave==1)return 0;
                        
                    }
                    else player=2;
                    t=time(NULL);
                    passedTime=0;
                    justRegret=false;
                }else if(player==2){
                    xarr2[turn2]=TAx;
                    yarr2[turn2]=TAy;
                    ++turn2;
                    if(checkHorizontal(turn2,TAy,xarr2,yarr2)||checkHorizontal(turn2,TAx,yarr2,xarr2)||checkDiagonalR(turn2,TAx,TAy,xarr2,yarr2,1)||checkDiagonalR(turn2,TAx,TAy,xarr2,yarr2,-1)){
                        win=2;
                        ++p2score;
                        end(&win, &move, &leave, &mode, &size, &turn1, &turn2, &player, &TAx, &TAy, xarr1, yarr1, xarr2, yarr2, p1score, p2score, &regretTime1, &regretTime2, &passedTime, &t, regretTime, &justRegret);
                        if(leave==1)return 0;
                        
                    }
                    else player=1;
                    t=time(NULL);
                    passedTime=0;
                    justRegret=false;
                }
            }else if(move=='q'){
                end(&win, &move, &leave, &mode, &size, &turn1, &turn2, &player, &TAx, &TAy, xarr1, yarr1, xarr2, yarr2, p1score, p2score, &regretTime1, &regretTime2, &passedTime, &t, regretTime, &justRegret);
                if(leave==1)return 0;
            }else if(move=='r'&&regret&&!justRegret){
                    if(player==2&&turn2>0&&regretTime1>0){
                        player=1;
                        --turn1;
                        --regretTime1;
                        TAx = xarr1[turn1];
                        TAy = yarr1[turn1];
                        justRegret=true;
                    }else if(player==1&&turn1>0&&regretTime2>0){
                        player=2;
                        --turn2;
                        --regretTime2;
                        TAx = xarr2[turn2];
                        TAy = yarr2[turn2];
                        justRegret=true;
                    }
            }
            render(TAx,TAy,player,size, xarr1, yarr1, turn1, xarr2, yarr2, turn2, p1score, p2score, regret, regretTime1, regretTime2, justRegret, timer, countdown, passedTime);
            
        }

        if(difftime(time(NULL),t)>=1&&timer&&!justRegret){
            ++passedTime;
            if(passedTime>=countdown){
                passedTime=0;
                if(player==1){
                    player=2;
                }else if(player==2){
                    player=1;
                }
            }

            render(TAx,TAy,player,size, xarr1, yarr1, turn1, xarr2, yarr2, turn2, p1score, p2score, regret, regretTime1, regretTime2, justRegret, timer, countdown, passedTime);
            
            t=time(NULL);
        }

    }

    while(mode==2){
        
        if(kbhit()){
            move=getch();
            if(move=='w'&&TAy>0) --TAy;
            else if(move=='s'&&TAy<size-1) ++TAy;
            else if(move=='a'&&TAx>0) --TAx;
            else if(move=='d'&&TAx<size-1) ++TAx;
            else if(move=='f'){

                for(int i=0;i<turn1;++i){
                    if(xarr1[i]==TAx&&yarr1[i]==TAy){
                        printf("\nInvalid move");
                        available=false;
                        break;
                    }
                }

                for(int i=0;i<turn2;++i){
                    if(xarr2[i]==TAx&&yarr2[i]==TAy){
                        printf("\nInvalid move");
                        available=false;
                        break;
                    }
                }

                
                if(!available){
                    available=true;
                    continue;
                }

                if(player==1){
                    xarr1[turn1]=TAx;
                    yarr1[turn1]=TAy;
                    ++turn1;
                    if(checkHorizontal(turn1,TAy,xarr1,yarr1)||checkHorizontal(turn1,TAx,yarr1,xarr1)||checkDiagonalR(turn1,TAx,TAy,xarr1,yarr1,1)||checkDiagonalR(turn1,TAx,TAy,xarr1,yarr1,-1)){
                    
                        ++p1score;
                        kill(turn1, xarr1, yarr1, killRate);
                        if(p1score>=winScore){
                            win=1;
                            end(&win, &move, &leave, &mode, &size, &turn1, &turn2, &player, &TAx, &TAy, xarr1, yarr1, xarr2, yarr2, p1score, p2score, &regretTime1, &regretTime2, &passedTime, &t, regretTime, &justRegret);
                            p1score=0;
                            p2score=0;
                            player=1;
                            if(leave==1)return 0;
                        }else player=2;
                    }
                    else player=2;
                    t=time(NULL);
                    passedTime=0;
                    justRegret=false;
                }else if(player==2){
                    xarr2[turn2]=TAx;
                    yarr2[turn2]=TAy;
                    ++turn2;
                    if(checkHorizontal(turn2,TAy,xarr2,yarr2)||checkHorizontal(turn2,TAx,yarr2,xarr2)||checkDiagonalR(turn2,TAx,TAy,xarr2,yarr2,1)||checkDiagonalR(turn2,TAx,TAy,xarr2,yarr2,-1)){
                        
                        ++p2score;
                        kill(turn2, xarr2, yarr2, killRate);
                        if(p2score>=winScore){
                            win=2;
                            end(&win, &move, &leave, &mode, &size, &turn1, &turn2, &player, &TAx, &TAy, xarr1, yarr1, xarr2, yarr2, p1score, p2score, &regretTime1, &regretTime2, &passedTime, &t, regretTime, &justRegret);
                            p1score=0;
                            p2score=0;
                            player=1;
                            if(leave==1)return 0;
                        }else player=1;
                    }
                    else player=1;
                    t=time(NULL);
                    passedTime=0;
                    justRegret=false;
                }
                
            }else if(move=='q'){
                if(p1score>p2score)win=1;
                else if(p1score<p2score)win=2;
                else win=0;
                end(&win, &move, &leave, &mode, &size, &turn1, &turn2, &player, &TAx, &TAy, xarr1, yarr1, xarr2, yarr2, p1score, p2score, &regretTime1, &regretTime2, &passedTime, &t, regretTime, &justRegret);
                if(leave==1)return 0;
            }else if(move=='r'&&regret&&!justRegret){
                    if(player==2&&turn2>0&&regretTime1>0){
                        player=1;
                        --turn1;
                        --regretTime1;
                        TAx = xarr1[turn1];
                        TAy = yarr1[turn1];
                        justRegret=true;
                    }else if(player==1&&turn1>0&&regretTime2>0){
                        player=2;
                        --turn2;
                        --regretTime2;
                        TAx = xarr2[turn2];
                        TAy = yarr2[turn2];
                        justRegret=true;
                    }
            }
            render(TAx,TAy,player,size, xarr1, yarr1, turn1, xarr2, yarr2, turn2, p1score, p2score, regret, regretTime1, regretTime2, justRegret, timer, countdown, passedTime);
            
        }

        if(difftime(time(NULL),t)>=1&&timer&&!justRegret){
            ++passedTime;
            if(passedTime>=countdown){
                passedTime=0;
                if(player==1){
                    player=2;
                }else if(player==2){
                    player=1;
                }
                
            }
            render(TAx,TAy,player,size, xarr1, yarr1, turn1, xarr2, yarr2, turn2, p1score, p2score, regret, regretTime1, regretTime2, justRegret, timer, countdown, passedTime);

            t=time(NULL);
        }
        
        
    }
    
    if(mode==3){
        render(TAx,TAy,player,size, xarr1, yarr1, turn1, xarr2, yarr2, turn2, p1score, p2score, regret, regretTime1, regretTime2, justRegret, timer, countdown, passedTime);
        t=time(NULL);
    }

    while(mode==3){
        if(kbhit()){
            move=getch();
            if(move=='w'&&TAy>0) --TAy;
            else if(move=='s'&&TAy<size-1) ++TAy;
            else if(move=='a'&&TAx>0) --TAx;
            else if(move=='d'&&TAx<size-1) ++TAx;
            else if(move=='f'){

                for(int i=0;i<turn1;++i){
                    if(xarr1[i]==TAx&&yarr1[i]==TAy){
                        printf("\nInvalid move");
                        available=false;
                        break;
                    }
                }

                for(int i=0;i<turn2;++i){
                    if(xarr2[i]==TAx&&yarr2[i]==TAy){
                        printf("\nInvalid move");
                        available=false;
                        break;
                    }
                }

                if(!available){
                    available=true;
                    continue;
                }

                
                    xarr1[turn1]=TAx;
                    yarr1[turn1]=TAy;
                    ++turn1;
                    if(checkHorizontal(turn1,TAy,xarr1,yarr1)||checkHorizontal(turn1,TAx,yarr1,xarr1)||checkDiagonalR(turn1,TAx,TAy,xarr1,yarr1,1)||checkDiagonalR(turn1,TAx,TAy,xarr1,yarr1,-1)){
                        win=1;
                        ++p1score;
                        end(&win, &move, &leave, &mode, &size, &turn1, &turn2, &player, &TAx, &TAy, xarr1, yarr1, xarr2, yarr2, p1score, p2score, &regretTime1, &regretTime2, &passedTime, &t, regretTime, &justRegret);
                        if(leave==1)return 0;
                        
                    }
                    else player=2;
                    cpuPlayer(TAx,TAy,xarr2,yarr2,&turn2,size,xarr1,yarr1);
                    if(checkHorizontal(turn2,TAy,xarr2,yarr2)||checkHorizontal(turn2,TAx,yarr2,xarr2)||checkDiagonalR(turn2,TAx,TAy,xarr2,yarr2,1)||checkDiagonalR(turn2,TAx,TAy,xarr2,yarr2,-1)){
                        win=2;
                        ++p2score;
                        end(&win, &move, &leave, &mode, &size, &turn1, &turn2, &player, &TAx, &TAy, xarr1, yarr1, xarr2, yarr2, p1score, p2score, &regretTime1, &regretTime2, &passedTime, &t, regretTime, &justRegret);
                        if(leave==1)return 0;
                        
                    }
                    else player=1;
                    t=time(NULL);
                    passedTime=0;
                    justRegret=false;
                
            }else if(move=='q'){
                end(&win, &move, &leave, &mode, &size, &turn1, &turn2, &player, &TAx, &TAy, xarr1, yarr1, xarr2, yarr2, p1score, p2score, &regretTime1, &regretTime2, &passedTime, &t, regretTime, &justRegret);
                if(leave==1)return 0;
            }else if(move=='r'&&regret&&!justRegret){
                    if(player==1&&turn1>0&&regretTime1>0){
                        player=1;
                        --turn1;
                        --regretTime1;
                        TAx = xarr1[turn1];
                        TAy = yarr1[turn1];
                        --turn2;
                        xarr2[turn2]=-1;
                        yarr2[turn2]=-1;
                        justRegret=true;
                    }
            }
            render(TAx,TAy,player,size, xarr1, yarr1, turn1, xarr2, yarr2, turn2, p1score, p2score, regret, regretTime1, regretTime2, justRegret, timer, countdown, passedTime);
            
        }

        if(difftime(time(NULL),t)>=1&&timer&&!justRegret){
            ++passedTime;
            if(passedTime>=countdown){
                passedTime=0;
                if(player==1){
                    cpuPlayer(TAx,TAy,xarr2,yarr2,&turn2,size,xarr1,yarr1);
                    if(checkHorizontal(turn2,TAy,xarr2,yarr2)||checkHorizontal(turn2,TAx,yarr2,xarr2)||checkDiagonalR(turn2,TAx,TAy,xarr2,yarr2,1)||checkDiagonalR(turn2,TAx,TAy,xarr2,yarr2,-1)){
                        win=2;
                        ++p2score;
                        end(&win, &move, &leave, &mode, &size, &turn1, &turn2, &player, &TAx, &TAy, xarr1, yarr1, xarr2, yarr2, p1score, p2score, &regretTime1, &regretTime2, &passedTime, &t, regretTime, &justRegret);
                        if(leave==1)return 0;
                        
                    }
                    else player=1;
                }else if(player==2){
                    player=1;
                }
            }

            render(TAx,TAy,player,size, xarr1, yarr1, turn1, xarr2, yarr2, turn2, p1score, p2score, regret, regretTime1, regretTime2, justRegret, timer, countdown, passedTime);
            
            t=time(NULL);
        }
    }

    }
    
    return 0;
}
