    data save

xarr 
yarr
same index
p0turn
p1turn

    
    
    check horizontal  (int TAy) 
//check how many index y=TAy
for{
    if (yarr[i])==TAy{
        ++round;
    }
}
if round<5 return 0;

//create arr contain same y as TAy
int checkXArr=calloc(round,sizeof(int));
for{
    if (yarr[i])==TAy{
        checkXArr[i]=xarr[i];
    }
}

qsort decending checkXArr
for checkXArr{
    if checkXArr[i]-checkXArr[i+1]==1{
        ++good;
        if good>=5 return 1;
    }
    else good=1;
}
return 0;




    check slide(right bottom to left top) (int TAx,int TAy)
px=TAx-1;
py=TAy-1;
nx=TAx+1;
ny=TAy+1;
//check if any point match previous point
for{
    if(xarr[i]!=px||yarr[i]!=py){
        if(xarr[i]!=nx||yarr[i]!=ny){
            return 0;
        }
    } 

}


way2 list every possible point and see if any of them matches xarr yarr
int pxarr[9];
int pyarr[9];
for(int i=-4;i<5;++i){
    pxarr[i+4]=TAx-i;
    pyarr[i+4]=TAy-i;
}
//2345 6 78910



    for(int i=0;i<elementOfXarr;++i){
        for(int j=0;j<9;++j){
            if(xarr[i]==pxarr[j]&&yarr[i]==pyarr[j]){
                ++round;
            }
        }
    }
    round=0;
    int checkIndex=calloc(round,sizeof(int));
    for(int i=0;i<elementOfXarr;++i){
        for(int j=0;j<9;++j){
            if(xarr[i]==pxarr[j]&&yarr[i]==pyarr[j]){
                checkIndex[round]=j;
                ++round;
            }
        }
    }
    qsort checkIndex decending;
    for(int i=0;i<round;++i){
        if checkIndex[i]-checkIndex[i+1]==1{
            ++good;
            if good>=5 return 1;
        }
        else good=1;
    }
    return 0;
  



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


int checkDiagonalR(int turn,int TAx,int TAy,int *xarr,int *yarr){
    int pxarr[9];
    int pyarr[9];
    int round=0;
    
    for(int i=-4;i<5;++i){
        pxarr[i+4]=TAx-i;
        pyarr[i+4]=TAy-i;
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


    kill