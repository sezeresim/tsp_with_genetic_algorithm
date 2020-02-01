#include<math.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>

//
int citiesSize=8;
int populationSize=20;
int mutationProbability=1;

int randomGens(int gen,int populationGens[]){
    int randG=rand()%citiesSize;
    int genDetected=0;
    for(int k=gen-1;k>=0;k--){
        if(randG==populationGens[k]){
            genDetected=1;
        }
    }
    if(genDetected==1){
        randomGens(gen,populationGens);
    }else{
        return randG;
    }
}
int crossoverCheck(int index,int offSpring[],int gen2[],int startPoint,int endPoint){
    int checked=0;
    int checked2=0;
    for(int i=startPoint;i<endPoint;i++){
        if(gen2[index]==offSpring[i]){
            checked=1;
        }
    }
    for(int i=0;i<citiesSize;i++){
        if(gen2[index]==offSpring[i]){
            checked2=1;
        }
    }
    if(checked==0 && checked2==0){
        return gen2[index];
    }else{
        if(index<citiesSize-1){
                crossoverCheck(index+1,offSpring,gen2,startPoint,endPoint);
        }
    }
}

int main(){

    srand(time(NULL));
    int populationMap[citiesSize][2];
    int populationGens[populationSize][citiesSize];
    //Population Map Randomly

    for(int i=0;i<citiesSize;i++){
        populationMap[i][0]=rand()%100;
        populationMap[i][1]=rand()%100;
        printf("%d City Coardinats = [ %d , %d ] \n",i,populationMap[i][0],populationMap[i][1]);
    }

    //Generating Different Paths

    for(int i=0;i<populationSize;i++){
        for(int j=0;j<citiesSize;j++){
            int randomGen=rand()%citiesSize;
            int genDetect=0;
            //control before
            for(int k=j;k>=0;k--){
                if(randomGen==populationGens[i][k]){
                    genDetect=1;
                }
            }
            if(genDetect==1){
                int arr[citiesSize];
                for(int p=0;p<citiesSize;p++){
                    arr[p]=populationGens[i][p];
                }
                int index=j;
                populationGens[i][j]=randomGens(index,arr);
            }else{
                populationGens[i][j]=randomGen;
            }
        }
    }
    printf("\nCities Paths\n");
    for(int i=0;i<populationSize;i++){
        printf("%d. Individual = ",i);
        for(int j=0;j<citiesSize;j++){
            printf("%d ",populationGens[i][j]);
        }
        printf("\n");
    }
    //Loop
    int t=0;
    int secondGen=2;
    int tempX=0;
    int tempY=0;
    int tempX2=0;
    int tempY2=0;
    float fitness[populationSize];
    for(int i=0;i<populationSize;i++){
        fitness[i]=0;
    }
    float fitnessDistance[populationSize];
    for(int i=0;i<populationSize;i++){
        fitnessDistance[i]=0;
    }
    int fitnessprint=1;
    for(int loop=0;loop<1000;loop++){
    //Fitness

   // printf("\nFITNESS FOR INDIVIDUALS\n\n");

    for(int i=0;i<populationSize;i++){
        for(int j=0;j<citiesSize;j++){
            tempX=populationMap[populationGens[i][j]][0];
            tempY=populationMap[populationGens[i][j]][1];
            if(j+1==citiesSize){
                tempX2=populationMap[populationGens[i][0]][0];
                tempY2=populationMap[populationGens[i][0]][1];
            }else{
                tempX2=populationMap[populationGens[i][j+1]][0];
                tempY2=populationMap[populationGens[i][j+1]][1];
            }
            fitness[i]=fitness[i]+sqrt((tempX-tempX2)*(tempX-tempX2)+(tempY-tempY2)*(tempY-tempY2));
            fitnessDistance[i]=fitnessDistance[i]+sqrt((tempX-tempX2)*(tempX-tempX2)+(tempY-tempY2)*(tempY-tempY2));
        }
        fitness[i]=citiesSize/fitness[i]*10000;


    }
        if(fitnessprint==1){
                for(int kl=0;kl<populationSize;kl++){

                    printf("%d. Individual Fitness %f\n",kl,fitness[kl]);
                    printf("%d. Individual Distance %f\n",kl,fitnessDistance[kl]);

                }
            fitnessprint=0;

        }



            //Roulette Wheel Selection
    float rouletteTotal=0;
    for(int i=0;i<populationSize;i++){
        rouletteTotal=rouletteTotal+fitness[i];
    }
    //printf("\nRoulette Total = %f ",rouletteTotal);

    int selectedRandomGen1=rand()%(int)rouletteTotal;
    int selectedRandomGen2=rand()%(int)rouletteTotal;

    int gen1;
    int gen2;
    int selectedGen1=0;
    int selectedGen2=0;
    int countPopulation=0;
    for(int i=0;i<populationSize;i++){
        countPopulation=fitness[i]+countPopulation;
        if(selectedRandomGen1<=countPopulation && selectedGen1==0){
            gen1=i;
            selectedGen1=1;
        }
        if(selectedRandomGen2<=countPopulation && selectedGen2==0){
            gen2=i;
            selectedGen2=1;
        }
    }
    //printf("\n\nSelected %d.Individual\n",gen1);

    int newGens[2][citiesSize];
    for(int k=0;k<citiesSize;k++){
        newGens[0][k]=populationGens[gen1][k];
        //printf("%d ",populationGens[gen1][k]);
    }
   // printf("\n\nSelected %d.Individual\n",gen2);
    for(int k=0;k<citiesSize;k++){
        newGens[0][k]=populationGens[gen2][k];
        //printf("%d ",populationGens[gen2][k]);
    }

    //CrossOVER
    int genA=rand()%citiesSize;
    int genB=rand()%citiesSize;
    int endGen=0;
    int startGen=0;
    if(genA>genB){
        endGen=genA;
        startGen=genB;
    }else{
        endGen=genB;
        startGen=genA;
    }
    int offSpring[citiesSize];
    for(int i=0;i<citiesSize;i++){
        offSpring[i]=citiesSize+1;
    }
    //printf("\n%d %d\n",startGen,endGen);
    for(int i=startGen;i<endGen;i++){
        offSpring[i]=populationGens[gen1][i];
        //printf("%d",offSpring[i]);
    }
    int genFun2[citiesSize];
    for(int i=0;i<citiesSize;i++){
        genFun2[i]=populationGens[gen2][i];
    }
    for(int i=0;i<citiesSize;i++){
        if(offSpring[i]==citiesSize+1){
            offSpring[i]=crossoverCheck(i,offSpring,genFun2,startGen,endGen);
        }
    }
    //Mutation
    int randomMutation=rand()%100;
    if(randomMutation<=mutationProbability){
        int mutationGen1=rand()%citiesSize;
        int mutationGen2=rand()%citiesSize;
        int tempMutation1=offSpring[mutationGen1];
        int tempMutation2=offSpring[mutationGen2];
        offSpring[mutationGen1]=tempMutation2;
        offSpring[mutationGen2]=tempMutation1;
    }
    //printf("\n\nAfter CrossOver and Mutation\n");
    for(int i=0;i<citiesSize;i++){
        //printf("%d ",offSpring[i]);
    }
    //Adding Child to Population
    int worstIndex=0;
    for(int i=1;i<populationSize;i++){
        if(fitness[i]>fitness[i-1]){
            worstIndex=i;
        }
    }
    for(int i=0;i<citiesSize;i++){
        populationGens[worstIndex][i]=offSpring[i];
    }
}

    printf("\nLAST PATHS\n");
    for(int i=0;i<populationSize;i++){
        printf("%d. Individual = ",i);
        for(int j=0;j<citiesSize;j++){
            printf("%d ",populationGens[i][j]);
        }
        printf("\n");
    }
    for(int i=0;i<populationSize;i++){
        printf("\n%f ",fitness[i]);
        printf("Distance\n%f ",fitnessDistance[i]);
    }
	return 0;
}
