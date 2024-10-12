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