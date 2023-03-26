#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<math.h>

float x,y,ax,ay,bx,by; //correspondra aux coordonnées en x et en y respectivement du points dont on veut savoir si on l'utilise, du point de départ et du point d'arrivée

float marge;

bool excl_carre(x,y,ax,ay,bx,by,marge)
{
    bool res=true;
    int c1,c2,c3,c4;
    //[1**2]
    //[****] comment j'ai décidé de numéroter les 4 coins du carré (c1,c2,c3,c4)
    //[****]
    //[3**4]

    if(ax>bx)
    {
        if(x>(ax+marge)||x<(bx-marge))
        {
            res=false;
        }
    }
    else if(x>(bx+marge)||x<(ax-marge))
    {
        res=false;
    }

    if(ay>by)
    {
        if(y>(ay+marge)||y<(by-marge))
        {
            res=false;
        }
    }
    else if(y>(by+marge)||y<(ay-marge))
    {
        res=false;
    }
    return(res);
}