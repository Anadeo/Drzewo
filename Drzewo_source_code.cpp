#include<iostream>
#include<SFML/Graphics.hpp>
#include<cmath>
#include<windows.h>
#include<winbase.h>
using namespace std;
using namespace sf;
short skok_koloru;
long double skala;
RenderWindow window(VideoMode(1920, 1080), "Drzewo", Style::Fullscreen);
void drzewo(short x, short y, long double dlugosc, long double radiany1, long double radiany2, long double kat_wczesniejszy, short iteracja, short czerwony, short zielony, short niebieski){
	short czerwony_wczesniejszy=czerwony, zielony_wczesniejszy=zielony, niebieski_wczesniejszy=niebieski;
	long double odcinek1x, odcinek1y, odcinek2x, odcinek2y;
	Event event;
	if(window.pollEvent(event)){
		if(event.type==Event::Closed||(event.type==Event::KeyPressed&&event.key.code==Keyboard::Escape)){
			window.close();
		}
	}
	//obliczenie wspó³¿êdnych kolejnych punktów
	odcinek1x=x+cos(kat_wczesniejszy+radiany1)*dlugosc;
	odcinek1y=y+sin(kat_wczesniejszy+radiany1)*dlugosc;
	odcinek2x=x+cos(kat_wczesniejszy+radiany2)*dlugosc;
	odcinek2y=y+sin(kat_wczesniejszy+radiany2)*dlugosc;
	//update koloru
	if(niebieski==0&&zielony!=255){
		czerwony-=skok_koloru;
		zielony+=skok_koloru;
		if(czerwony<0){
			czerwony=0;
		}
		if(zielony>255){
			zielony=255;
		}
	}
	else if(czerwony==0&&niebieski!=255){
		zielony-=skok_koloru;
		niebieski+=skok_koloru;
		if(zielony<0){
			zielony=0;
		}
		if(niebieski>255){
			niebieski=255;
		}
	}
	else if(zielony==0&&czerwony!=255){
		niebieski-=skok_koloru;
		czerwony+=skok_koloru;
		if(niebieski<0){
			niebieski=0;
		}
		if(czerwony>255){
			czerwony=255;
		}
	}
	//rysowanie linji
	Vertex linia1[]={
		Vertex(Vector2f(x, y), Color(czerwony_wczesniejszy, zielony_wczesniejszy, niebieski_wczesniejszy)), Vertex(Vector2f(odcinek1x, odcinek1y), Color(czerwony, zielony, niebieski))
	}
	;
	Vertex linia2[]={
		Vertex(Vector2f(x, y), Color(czerwony_wczesniejszy, zielony_wczesniejszy, niebieski_wczesniejszy)), Vertex(Vector2f(odcinek2x, odcinek2y), Color(czerwony, zielony, niebieski))
	}
	;
	//update koloru
	if(niebieski==0&&zielony!=255){
		czerwony-=skok_koloru;
		zielony+=skok_koloru;
		if(czerwony<0){
			czerwony=0;
		}
		if(zielony>255){
			zielony=255;
		}
	}
	else if(czerwony==0&&niebieski!=255){
		zielony-=skok_koloru;
		niebieski+=skok_koloru;
		if(zielony<0){
			zielony=0;
		}
		if(niebieski>255){
			niebieski=255;
		}
	}
	else if(zielony==0&&czerwony!=255){
		niebieski-=skok_koloru;
		czerwony+=skok_koloru;
		if(niebieski<0){
			niebieski=0;
		}
		if(czerwony>255){
			czerwony=255;
		}
	}
	window.draw(linia1, 2, Lines);
	window.draw(linia2, 2, Lines);
	//iteracja
	if(iteracja!=0){
		drzewo(odcinek1x, odcinek1y, dlugosc*skala, radiany1, radiany2, M_PI+kat_wczesniejszy+radiany1, iteracja-1, czerwony, zielony, niebieski);
		drzewo(odcinek2x, odcinek2y, dlugosc*skala, radiany1, radiany2, M_PI+kat_wczesniejszy+radiany2, iteracja-1, czerwony, zielony, niebieski);
	}
}
int main(){
	window.setFramerateLimit(60);
	SYSTEMTIME czas;
	short x, y, dlugosc, iteracje, czerwony=255, zielony=0, niebieski=0;
	long double radiany1, radiany2=M_PI*0.5;
	cout<<"Podaj nastepujace parametry do wygenerowania animacji:"<<endl;
	cout<<"liczbe 1, 3, 5, 15, 17, 51, 85, 255 generujaca kolory: ";
	cin>>skok_koloru;
	cout<<"proporcje kolejnych odcinkow(0-1): ";
	cin>>skala;
	cout<<"poczatkowa dlugosc odcinka w pixelach: ";
	cin>>dlugosc;
	cout<<"ilosc iteracji podczas generowania: ";
	cin>>iteracje;
	while(window.isOpen()){
		Event event;
		if(window.pollEvent(event)){
			if(event.type==Event::Closed||(event.type==Event::KeyPressed&&event.key.code==Keyboard::Escape)){
				window.close();
			}
		}
		GetSystemTime(&czas);
		radiany1=M_PI*2*(czas.wMinute/(long double)60+czas.wSecond/(long double)3600)+M_PI;
		radiany2=M_PI*2*(czas.wSecond/(long double)60+czas.wMilliseconds/(long double)60000)+M_PI;
		if(niebieski==0&&zielony!=255){
			czerwony-=1;
			zielony+=1;
		}
		else if(czerwony==0&&niebieski!=255){
			zielony-=1;
			niebieski+=1;
		}
		else if(zielony==0&&czerwony!=255){
			niebieski-=1;
			czerwony+=1;
		}
		drzewo(960, 540, dlugosc, radiany1, radiany2, 0, iteracje, czerwony, zielony, niebieski);
		window.display();
		window.clear();
	}
}
