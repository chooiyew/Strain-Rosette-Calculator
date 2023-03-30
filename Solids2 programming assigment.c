#include<stdio.h>
#include<string.h>
#include<math.h>

void main()
{
	printf("This program aims to solve any type of STRAIN ROSETTES problems.\n");
	printf("This program will provide all the essential information like PRINCIPAL STRAINS, PRINCIPAL STRESS, MAX IN-PLANE SHEAR STRESS and ABSOLUTE MAX SHEAR STRESS.\n\n");
	//define parameters
	int n=3;
	int i,j,k;
	float strain[10][10];
	float angle[3];
	float strain_x,strain_y,strain_shear;
	float a,b;
	
	//get input from the user
	for(i=1;i<=n;i++) //creates 3 by 4 matrix
	{
		printf("Strain Gauge %c : \n",(char)i+64);
		printf("Strain(x10^-6)= ");
		scanf("%f",&strain[i][4]);
		printf("Theta(degree)= ");
		scanf("%f",&angle[i]);
		angle[i]=angle[i]*3.14159/180;
		strain[i][1]=pow(cos(angle[i]),2);	
		strain[i][2]=pow(sin(angle[i]),2);
		a=sin(angle[i]),b=cos(angle[i]);
		strain[i][3]=a*b;
		printf("\n");
	}
	
	//determine the determinant of the 3by3 matrix, solve the problem using Cramer's Rule 
	float Det,Dx,Dy,Dz;
	float r1,r2,r3;
	r1 = strain[1][1]*(strain[2][2]*strain[3][3]-strain[3][2]*strain[2][3]);
	r2 = strain[1][2]*(strain[2][1]*strain[3][3]-strain[3][1]*strain[2][3]);
	r3 = strain[1][3]*(strain[2][1]*strain[3][2]-strain[3][1]*strain[2][2]);
	Det = r1-r2+r3;
	
	r1 = strain[1][4]*(strain[2][2]*strain[3][3]-strain[3][2]*strain[2][3]);
	r2 = strain[1][2]*(strain[2][4]*strain[3][3]-strain[3][4]*strain[2][3]);
	r3 = strain[1][3]*(strain[2][4]*strain[3][2]-strain[3][4]*strain[2][2]);
	Dx = r1-r2+r3;
	
	r1 = strain[1][1]*(strain[2][4]*strain[3][3]-strain[3][4]*strain[2][3]);
	r2 = strain[1][4]*(strain[2][1]*strain[3][3]-strain[3][1]*strain[2][3]);
	r3 = strain[1][3]*(strain[2][1]*strain[3][4]-strain[3][1]*strain[2][4]);
	Dy = r1-r2+r3;
	
	r1 = strain[1][1]*(strain[2][2]*strain[3][4]-strain[3][2]*strain[2][4]);
	r2 = strain[1][2]*(strain[2][1]*strain[3][4]-strain[3][1]*strain[2][4]);
	r3 = strain[1][4]*(strain[2][1]*strain[3][2]-strain[3][1]*strain[2][2]);
	Dz = r1-r2+r3;
	
	strain_x = Dx/Det;
	strain_y = Dy/Det;
	strain_shear = Dz/Det;
	
	if(strain_x>1e6||strain_y>1e6)
	{
		printf("The are errors occur in the Strain Gauge ! Unable to calculate result !\n\n");
	}else
	{
		//print the results(strain in x and y direction, shear strain)
		printf("\nStrain in x direction= %.2fx10^-6\n",strain_x);
		printf("Strain in y direction= %.2fx10^-6\n",strain_y);
		printf("Shear Strain = %.2fx10^-6\n",strain_shear);
	
		//calculate the principal strains and max in plane shear strain
		float p_strain1,p_strain2,p_strain_angle,max_strain;
		p_strain2 = 0.5*(strain_x+strain_y) - sqrt(pow((0.5*(strain_x-strain_y)),2) + pow((0.5*strain_shear),2));
		p_strain1 = 0.5*(strain_x+strain_y) + sqrt(pow((0.5*(strain_x-strain_y)),2) + pow((0.5*strain_shear),2));
		p_strain_angle = 0.5*(atan(strain_shear/(strain_x-strain_y)));
		max_strain = 2*sqrt(pow((0.5*(strain_x-strain_y)),2) + pow((0.5*strain_shear),2));
		printf("\n\n");
		printf("The principal strains are %.2fx10^-6 and %.2fx10^-6 respectively with an angle of orientation of %.2f degree\n",p_strain2,p_strain1,p_strain_angle*180/3.14159);
		printf("The max in plane shear strain is %.2fx10^-6 \n\n",max_strain);
		
		//option to calculate principal stresses and absolute max shear stresss
		int ans;
		float E,v,p_stress1,p_stress2,absmax_stress,A;
		
		printf("\nDO YOU WANT TO CONTINUE CALCULATE THE PRINCIPAL STRESSES AND ABSOLUTE MAX SHEAR STRESS ?\n");
		printf("If yes type 1, If no ignore\n");
		scanf("%d",&ans);
		if (ans==1)
		{
			printf("\nFOR A TYPICAL STEEL PLATE WITH MODULUS OF ELASTICITY, E= 210 GPa, and POISSON'S RATIO, v=0.3\n");
			printf("Enter Modulus of Elasticity of Material, E(GPa) : \n");
			scanf("%f",&E);
			printf("Enter Poisson's Ratio, v : \n");
			scanf("%f",&v);
			
			A = E/(float)(1 - pow(v,2));
			p_stress1 = A*(p_strain1 + v*p_strain2)/1000;
			p_stress2 = (E/(1 - pow(v,2)))*(p_strain2 + v*p_strain1)/1000;
			
			if(p_stress1>0&&p_stress2>0)
			{
				absmax_stress = p_stress1/2;
			}else if(p_stress1<0||p_stress2<0)
			{
				absmax_stress = (p_stress1 - p_stress2) /2;
			}
			
			printf("The principal stresses are %.2fMPa and %.2fMPa respectively\n",p_stress2,p_stress1);
			printf("The absolute max shear stress is %.2fMPa\n",absmax_stress);
		}		
	}
		
	system("PAUSE");
}
