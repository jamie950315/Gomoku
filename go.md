    data save

xarr 
yarr
same index
    
    
    check horizontal  (int TAy) (code already generated)
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
    if checkXArr[i]-checkXArr[i+1]!=1 return 0 
    else ++good;
}
if good>=5 return 1;



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
int pxarr[9]

for(int i=-4;i<5;++i){
    pxarr[i+4]=TAx-i;

}
2345 6 78910