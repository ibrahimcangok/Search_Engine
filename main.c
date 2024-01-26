#include<stdio.h> 
#include<string.h> 
#include<locale.h>
float similar_text(char a[], char b[])
	{
	int i;
	int esharf=0;
	
	for(i=0;i<strlen(b);i++)
	{
		if (a[i]==b[i])
		esharf++; 
	}	
	return (float)esharf/strlen(b);
}

int main() {

	setlocale(LC_ALL, "Turkish");
	float islem, yuzde=0; 
	char ara[10], word[106], benzer[10]; 
	
	FILE *dosya;
		
	printf("Search: ");
	scanf("%s",&ara);
	strlwr(ara);

	
	dosya=fopen("words.txt","r");
								 
	if(dosya == NULL)
	{
		printf("Dosya okuma modunda acilamadi, program kapatiliyor.");
		return 0;													  	
		
	}
	while(!feof(dosya))
	{
		fscanf(dosya,"%s",word); 
		islem=similar_text(ara,word);
		
		if(yuzde<islem)
		{
			yuzde = islem;
			strcpy(benzer,word);
		}
	}
	
	fclose(dosya);
	
	if(yuzde == 0)
		printf("No Matching.");
	else
		printf("Did You Mean? %s (%.2f)",benzer,yuzde);
	return 0;
}
