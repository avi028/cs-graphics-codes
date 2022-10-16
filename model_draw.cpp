#include <iostream>
#include <fstream>
using namespace std;


void glacier(int gridSize ,int step){
    
    int ySt=(-1)*(gridSize/2)*step;
    int yEd=(gridSize/2)*step;

    int zSt =(-1)*(gridSize/2)*step;
    int zEd =(gridSize/2)*step;

    int xSt=(-1)*(gridSize/2)*step;
    int xEd=(gridSize/2)*step;


    ySt=0;
    yEd=yEd;

    string filename = "modelTest1.raw";
    ofstream fout(filename.c_str(),std::ios_base::out);
    float r,g,b;
    r=0.74902 , g=0.847059 , b=0.847059;

   /*water*/ 
   for(int y=ySt;y<yEd;y+=step){
        // zSt = (-1)*(gridSize/2)*step + y;
        // zEd = (gridSize/2)*step -y;
        for(int z=zSt;z<zEd;z+=step){
            // xSt = (-1)*(gridSize/2)*step + y;
            // xEd = (gridSize/2)*step -y;
            for(int x=xSt;x<xEd;x+=step){
                //    fout<<x<<"\t"<<y<<"\t"<<z<<"\t"<<r<<"\t"<<g<<"\t"<<b<<"\n";
                   fout<<x<<"\t"<<-1*y-step<<"\t"<<z<<"\t"<<r<<"\t"<<g<<"\t"<<b<<"\n";
            }
        }
    }
    
    float r1,g1,b1;
    r1=0.372549 , g1=0.623529 , b1=0.623529;
    /*Down*/ 
    for(int y=ySt;y<yEd;y+=step){
        zSt = (-1)*(gridSize/2)*step + y;
        zEd = (gridSize/2)*step -y;
        for(int z=zSt;z<zEd;z+=step){
            xSt = (-1)*(gridSize/2)*step + y;
            xEd = (gridSize/2)*step -y;
            for(int x=xSt;x<xEd;x+=step){
                   fout<<x<<"\t"<<-1*y-step<<"\t"<<z<<"\t"<<r1<<"\t"<<g1<<"\t"<<b1<<"\n";
                //    fout<<x<<"\t"<<y<<"\t"<<z<<"\t"<<r<<"\t"<<g<<"\t"<<b<<"\n";
            }
        }
    }

    /*Up*/ 
     r=g=b=0.8;
    for(int y=ySt;y<yEd;y+=step){
        zSt = (-1)*(gridSize/2)*step + y+step;
        zEd = (gridSize/2)*step -y-step;
        for(int z=zSt;z<zEd;z+=step){
            xSt = (-1)*(gridSize/2)*step + y+step;
            xEd = (gridSize/2)*step -y-step;
            for(int x=xSt;x<xEd;x+=step){
                   fout<<x<<"\t"<<y<<"\t"<<z<<"\t"<<r<<"\t"<<g<<"\t"<<b<<"\n";
            }
        }
    }
 
}

int main(){
    int gridSize =50;
    int step=5;
    /**
     * 
     * gridSize =6;
     * step=5;
     * -15,-10,-5,0,5,10,15
     * 
     * 
     * 
     * -50 -21  -20 -01  0 14  15  24 25  30    45
     * 
    */
    
    int ySt=(-1)*(gridSize/2)*step;
    int yEd=(gridSize/2)*step;

    int zSt =(-1)*(gridSize/2)*step;
    int zEd =(gridSize/2)*step;

    int xSt=(-1)*(gridSize/2)*step;
    int xEd=(gridSize/2)*step;



    string filename = "modelTest2.raw";
    ofstream fout(filename.c_str(),std::ios_base::out);
    float r,g,b;
    r=0.74902 , g=0.847059 , b=0.847059;

   /*water*/
   int hset[] = {2,14,14,10,10};
   int wset[] = {2,3,5,10,25};
   double colorSet[][3]={
    {0.647059 , 0.164706 , 0.164706},
    {0.0,1.0,0.0},
    {1.0,1.0,1.0},
    {1.0 , 0.5 , 0.0},
    {0.0,0.0,1.0}
   }; 
   int h_size = 5;

    for (int i=0;i<h_size;i++){
        int h = hset[i];
        int w = wset[4-i];

        int xs,xe,ys,ye,zs,ze;

        ys = ySt ;
        ye = ySt + h*step;
        ySt = ye;

        xs = -w*step;
        xe =  w*step; 

        zs = -w*step;
        ze =  w*step; 

        r=colorSet[i][0];
        g=colorSet[i][1];
        b=colorSet[i][2];

        for(int y=ys;y<ye;y+=step){
                cout<<y<<endl;
                for(int z=zs;z<ze;z+=step)
                    for(int x=xs;x<xe;x+=step)
                        fout<<x<<"\t"<<y<<"\t"<<z<<"\t"<<r<<"\t"<<g<<"\t"<<b<<"\n";

        }
        
    }
    fout.close();
   return 0;
}