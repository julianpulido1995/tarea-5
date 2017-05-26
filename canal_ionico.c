#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float radio(float can[42][2], float x,float y);

int main(){

int i;
int j;
float can[42][2];
float can1[42][2];
//para can
float xw[200000];
float yw[200000];
float r[200000];
//para can1
float xw1[200000];
float yw1[200000];
float r1[200000];


FILE *canal;
FILE *canal1;
canal = fopen("Canal_ionico.txt","r");
canal1 = fopen("Canal_ionico1.txt","r");
for(i=0;i<42;i++){
	for(j=0;j<2;j++){
		fscanf(canal,"%f	", &can[i][j]);
	}
}

fclose(canal);

for(i=0;i<42;i++){
	for(j=0;j<2;j++){
		fscanf(canal1,"%f	", &can1[i][j]);
	}
}

fclose(canal1);

//para canal_ionico.txt


float xo;
float yo;
float xo1;
float yo1;
float ro;
float ro1;

//canalionico
xo = (drand48()*20.0) - 5.0;
yo = (drand48()*25.03) - 7.07;
//canalionico1
xo1 = (drand48()*20.0) - 5.0;
yo1 = (drand48()*23.94) - 7.75;


for(i=0;i<200000;i++){
	if(i==0){
		
		xw[i] = xo;
		yw[i] = yo;
		xw1[i] = xo1;
		yw1[i] = yo1;
	}
	else{
		xw[i] = 0.0;
		yw[i] = 0.0;
		xw1[i] = 0.0;
		yw1[i] = 0.0;
		
	}
}

for(i=0;i<200000;i++){
	if(i==0){
		ro = radio(can,xw[i],yw[i]);
		r[i] = ro;
		ro1= radio(can1,xw1[i],yw1[i]);
		r1[i] = ro1;
	}
	else{		
		r[i] = 0.0;
		r1[i] = 0.0;
	}
}

float xnew;
float ynew;
float alpha;
float rnew;

//canalionico.txt
for(i = 0;i<200000-1;i++){
	float R1;
	float R2;
	
       	R1 = (float)rand()/(float)(RAND_MAX);
	R2 = (float)rand()/(float)(RAND_MAX);
       	
	xnew = xw[i] + 1.0*cos(2.0*M_PI*R2)*sqrt(-2.0*log(R1));
	ynew = yw[i] + 1.0*sin(2.0*M_PI*R2)*sqrt(-2.0*log(R1));
	
	if(15.0> xnew && xnew> -5.0 && ynew< 17.96 && ynew> -7.07){
		rnew = radio(can,xnew,ynew);
		alpha = rnew/r[i];
	
		if(alpha>= 1.0){
			xw[i+1] = xnew;
			yw[i+1] = ynew;
			r[i+1] = rnew;
		}
		else{
			float beta = drand48(); 
		 	if(beta<=alpha){
				xw[i+1] = xnew;
				yw[i+1] = ynew;
				r[i+1] = rnew;
			}
			else{
				xw[i+1] = xw[i];
				yw[i+1] = yw[i];
				r[i+1] = r[i];
			}
		}
	}		
}


 // canal ionico 1.txt

for(i = 0;i<200000-1;i++){
	float a1;
	float a2;
	
       	a1 = (float)rand()/(float)(RAND_MAX);
      
       	a2 = (float)rand()/(float)(RAND_MAX);

	xnew = xw1[i] + 0.1*cos(2.0*M_PI*a2)*sqrt(-2.0*log(a1));//distribucion normal numeros
	ynew = yw1[i] + 0.1*sin(2.0*M_PI*a2)*sqrt(-2.0*log(a1));

	if(15.0> xnew && xnew> -5.0 && ynew< 16.19 && ynew> -7.75){
		rnew = radio(can1,xnew,ynew);
		alpha = rnew/r1[i];
	
		if(alpha>= 1.0){
			xw1[i+1] = xnew;
			yw1[i+1] = ynew;
			r1[i+1] = rnew;
		}
		else{
			float beta = drand48(); 
		 	if(beta<=alpha){
				xw1[i+1] = xnew;
				yw1[i+1] = ynew;
				r1[i+1] = rnew;
			}
			else{
				xw1[i+1] = xw1[i];
				yw1[i+1] = yw1[i];
				r1[i+1] = r1[i];
			}
		}
	}
			
}
//generacion de archivos que python va a leer, los centros+el radio
FILE *xcanal;
	xcanal = fopen("xcanal.txt","w");
	for(i=0;i<200000;i++) {		
    		fprintf(xcanal,"%f\n",xw[i]);				
	}
	fclose(xcanal);
FILE *ycanal;
	ycanal = fopen("ycanal.txt","w");
	for(i=0;i<200000;i++) {		
    		fprintf(ycanal,"%f\n",yw[i]);				
	}
	fclose(ycanal);
FILE *xcanal1;
	xcanal1 = fopen("xcanal1.txt","w");
	for(i=0;i<200000;i++) {		
    		fprintf(xcanal1,"%f\n",xw1[i]);				
	}
	fclose(xcanal1);
FILE *ycanal1;
	ycanal1 = fopen("ycanal1.txt","w");
	for(i=0;i<200000;i++) {		
    		fprintf(ycanal1,"%f\n",yw1[i]);				
	}
	fclose(ycanal1);
FILE *radius;
	radius = fopen("radius.txt","w");
	for(i=0;i<200000;i++) {		
    		fprintf(radius,"%f\n",r[i]);				
	}
	fclose(radius);
FILE *radius1;
	radius1 = fopen("radius1.txt","w");
	for(i=0;i<200000;i++) {		
    		fprintf(radius,"%f\n",r1[i]);				
	}
	fclose(radius1);

}

float radio(float can[42][2], float x,float y){
	float vector[42];
	int i,j;
	float aux;
	for(i = 0;i<42;i++){
		vector[i] = sqrt(pow(can[i][0]-x,2.0)+pow(can[i][1]-y,2.0))-1.0;
	}
//ordeno el vector	
	float minimo = vector[0];
	for(i=1;i<42;i++){
		if(minimo>vector[i]){
			minimo = vector[i];
		}
	}

return minimo;//minimo del arreglo

}











