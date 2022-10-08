#include<stdio.h> 
#include<string.h> 
#include<locale.h> //Tüm diller ve karakter setleri bu kütüphanededir biz burada Türkçe karakterler kullanabilmek için ekledik.
float similar_text(char a[], char b[])
	{
	int i;
	int esharf=0;
	
	for(i=0;i<strlen(b);i++)//döngü ana programda tanımlanan 'word' değişkenin uzunluğuna göre çalışacak.
	{
		if (a[i]==b[i])//Aynı harf var ise
		esharf++; //esharf adlı değişkeni bir arttır.
	}	
	return (float)esharf/strlen(b);//float bölmesi yapmamız gerektiği için (küsüratlı çıkması için 0.67 gibi) başına float ekleyerek bölme yaptık.
								  //esharfi b nin uzunluğuna yani doğru kelimeye bölerek oranımızı elde ettik.
}

int main() {

	setlocale(LC_ALL, "Turkish"); // Türkçe karakter kullanabilmek için bu kod satırını yazmamız gerekiyor.
	//int j;
	float islem, yuzde=0; //burada programda kullanacağımız tüm değişkenleri tanımladık.
	char ara[10], word[106], benzer[10]; //burada değişkenleri dizi tanımlamamızın sebebi dizinin temel mantığı birden çok değer ataması olacağından dolayıdır.
										//misal word[106] yazmasının sebebi metin belgesinin içerisinde tam 106 tane kelime olmasından dolayıdır.
	
	FILE *dosya; //ifadesi ile FILE tipinde adı dosya olan bir dosya göstericisi tanımlıyoruz ki bu gösterici, 
				//dosyalar üzerinde işlem yapabilmemiz için gereklidir.
		
	printf("Search: ");
	scanf("%s",&ara);
	strlwr(ara);//Büyük harfi küçük harfe dönüştürmek için kullanıldı.
	//2. küçük harfe dönüştürme methodu:
	
	/*while(ara[j]!='\0'){ //!='\0' null (boş) değere eşit değilse döngüyü çalıştır demek. 
        if(ara[j]>=65 && ara[j]<=90) //ASCII'deki 'a' ve A 'arasındaki fark ile türetilmiş kodlamalar arasındaki fark 32'dir bu yüzden 32 eklemek küçük harfe dönüştürür.
			ara[j] += 32;			   //İkili ASCII kod tablosu:
			j++;			          /*A 1000001    a 1100001
                                       B 1000010    b 1100010
                                       C 1000011    c 1100011
                                       ...
                                       Z 1011010    z 1111010
									   Ve 32, '0100000' küçük ve büyük harfler arasındaki tek farktır.
    }*/
	
	dosya=fopen("words.txt","r"); //komutu ile words.txt dosyasını okuma modunda ("r") açmış olduk.
								 //Sonrasında gelen if() yapısı dosyamızın okuma modunda başarılı bir şekilde açılıp açılmadığını sorgulamaktadır.
								 
	if(dosya == NULL)
	{
		printf("Dosya okuma modunda acilamadi, program kapatiliyor."); //1. Eğer fopen() fonksiyonu normal olarak çalışmazsa NULL bir işaretçi geri döndürür
		return 0;													  //o yüzden dosya NULL'a eşitse çalışmamıştır bu yüzden programı kapatmak gerekir.
																	 //2. Mevcut olmayan bir dosyayı sadece okuma (r) için açmak istediğimizde, 
																	//fopen() fonksiyonu hata verir.	
		
	}
	while(!feof(dosya))// dosya sonuna kadar okuma islemi gerceklestirir.
	{
		fscanf(dosya,"%s",word); //fscanf()  fonksiyonu, ilk parametre olarak hangi dosyadan okuma yapılacaksa o dosya ile ilişkilendirilmiş file pointerı alıyor.
								// Bizim uygulamamız için bu dosya.
							   //Sonrasında çift tırnak içerisindeki ifadeler ise okuma yapmak istediği değişken tipini veriyor. 
							  //üçüncü kısımsa hangi diziye aktarma yapılacaksa onun ismi yazılıyor. Yani, String ifade %s ile word dizisine aktarılacak
		islem=similar_text(ara,word);//üstte tanımlanan fonksiyona değer gönderimi yaptıktan sonra fonksiyon çalışacak hesaplanan değer daha sonra
									//islem adlı değişkene atanacak.
		
		if(yuzde<islem)//burada koşulu yazmazsak program yüzdeyi direkt 0 olarak alacak ve her seferinde "no matching" çıktısı verecek.
		{//islem yuzdeden (ilk değerini 0 vermiştik) büyükse yani fonksiyon bir değer döndürdüyse aşağıdaki atama işlemlerini yaptırmamız gerekiyor bunu 
		//sorgulamadan atama işlemi yaparsak üstte belirttiğim gibi no matching hatası verir. Eğer strcpy kısmını aynı şekilde bu koşulun içinde tanımlamazsak
	   //program yuzde kısmını doğru gösterir ama her seferinde did you mean? x (a.b) çıktısı verir (a.b)kısmı girilen kelimeye göre değişkenlik gösterir ama
	  //x kısmı her seferinde dosyanın en sonunda hangi değer varsa ki bu bizim programımız için 'zebra'dır zebra değerini döndürür çünkü üstte en son
	 //word değişkenine zebra değeri atanmıştır. Fonksiyon çalıştığında wordde olan kelimeyi benzere atadık ki bunu koşuldan çıktıktan sonra ekranda yazdırabilelim
			yuzde = islem;//fonksiyondaki dönen değeri isleme atamıştık burada ise yuzdeye atadık
			strcpy(benzer,word);//Bu fonksiyon word stringini benzer stringine kopya eder.
		}
	}
	
	fclose(dosya); //burada başka işlemimiz kalmadığı için dosyayı kapatıyoruz.
	
	if(yuzde == 0)//eğer çıkan değer yani yüzde değişkeni 0'a eşitse hiç eşleşme olmadığından ötürü ekrana "no matching" yazdırılacaktır.
		printf("No Matching.");
	else//eğer yüzde 0dan başka herhangi bi değerse bu programda bize eşleşen bazı harflerin olduğunu gösterir.
	   //Girilen kelimeye benzeyen kelime ve yüzde kaç benzediği ekrana yazılır.
		printf("Did You Mean? %s (%.2f)",benzer,yuzde);
	return 0;//programdan çıkış yapılır.
}
