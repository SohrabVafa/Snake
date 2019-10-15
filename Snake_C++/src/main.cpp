#include <cstdlib>
#include <ctime>
#include <string>
#include <stdlib.h>
#include <sstream>

#include "miniwin.h"
using namespace miniwin;
using namespace std;

struct Coordenada{
	int x;
	int y;
};

class Snape{
	private:
		Coordenada *serpiente;
		int tam;
 		Coordenada punto;
 		Coordenada anterior;
		static const int radio = 10; 
	public:
		Snape(){
			serpiente = new Coordenada[9];
			tam = 9;
			for(int i=0; i<tam; i++){
				serpiente[i].x = 350-i*20;
				serpiente[i].y = 290;
			}
			CrearPunto();
		}
		void Mostrar(){
			string score;
			stringstream ss;
			ss << tam-9;
			score = ss.str();
			texto(10,10,score);
			for(int i=0; i<tam; i++){
				circulo_lleno(serpiente[i].x, serpiente[i].y, radio);
			}
			color(VERDE);
			circulo_lleno(punto.x, punto.y, 9);
			color(BLANCO);
			refresca();
		}
		void Mover(int x, int y){
			anterior.x = serpiente[tam-1].x;
			anterior.y = serpiente[tam-1].y;
			for(int i=tam-1; i>0; i--){
				serpiente[i] = serpiente[i-1];
			}
			serpiente[0].x += x*20;
			serpiente[0].y += y*20;
		}
		void CrearPunto(){
			bool bueno = false;
			while(!bueno){
				bueno = true;
    			punto.x = (std::rand() %30)*20 + 10;
    			punto.y = (std::rand() %30)*20 + 10;
    			for(int i=0; i<tam && bueno; i++){
    				if(punto.x == serpiente[i].x && punto.y == serpiente[i].y){
    					bueno = false;
					}
				}
    		}
		}
		bool Comido(){
			return (serpiente[0].x == punto.x && serpiente[0].y == punto.y);
		}
		void Agregar(){
			Coordenada *aux = new Coordenada[tam+1];
			for(int i=0; i<tam; i++){
				aux[i] = serpiente[i];
			}
			aux[tam].x = anterior.x;
			aux[tam].y = anterior.y;
			tam++;
			delete[] serpiente;
			serpiente = aux;
		}
		bool Muerto(){
			bool muerto = false;
			if(serpiente[0].x<0 || serpiente[0].x>600 || serpiente[0].y<0 || serpiente[0].y>600)
				muerto = true;
			for(int i=2; i<tam && !muerto; i++){
				if(serpiente[0].x == serpiente[i].x && serpiente[0].y == serpiente[i].y){
					muerto = true;
				}
			}
			return muerto;
		}
		void GameOver(){
			color(ROJO);
			for(int i=0; i<tam; i++){
				circulo_lleno(serpiente[i].x, serpiente[i].y, radio);
				refresca();
				espera(80);
			}
			for(int i=0; i<3; i++){
				borra();
				refresca();
				espera(400);
				color(ROJO);
				Mostrar();
				refresca();
				espera(400);
			}
			borra();
			refresca();
			rectangulo(100,100,500,500);
			texto(270, 290, "GAME OVER!");	
			string score;
			stringstream ss;
			ss << tam-9;
			score = ss.str();
			texto(280,320,"Score:");	
			texto(330,320,score);
			refresca();
		}
};

int main(){
	vredimensiona(600, 600);
	std::srand(std::time(0));
	color(BLANCO);
	rectangulo(100,100,500,500);
	texto(285, 290, "START!");
	refresca();
	while(!raton_dentro() || !raton_boton_izq());
	borra();
	refresca();
	
	while(true){	
	bool game_over = false;
	Snape s;
	int t, estado = DERECHA, mov_x = 1, mov_y = 0;
	Coordenada punto;
	
	s.Mostrar();
	while(!game_over){
		t = tecla();
		switch (t){
			case ARRIBA:
				if(estado!=ABAJO){
					mov_x = 0;
					mov_y = -1;
					estado = ARRIBA;
				}
				break;
			case ABAJO:
				if(estado!=ARRIBA){
					mov_x = 0;
					mov_y = 1;
					estado = ABAJO;
				}
				break;
			case DERECHA:
				if(estado!=IZQUIERDA){
					mov_x = 1;
					mov_y = 0;
					estado = DERECHA;
				}
				break;
			case IZQUIERDA:
				if(estado!=DERECHA){
					mov_x = -1;
					mov_y = 0;
					estado = IZQUIERDA;
				}
				break;
		}
		s.Mover(mov_x, mov_y);
		if(s.Comido()){
			s.Agregar();
			s.CrearPunto();
		}else {
			game_over = s.Muerto();
		}
		borra();
		s.Mostrar();
		espera(100);
	}
	s.GameOver();
	while(!raton_dentro() || !raton_boton_izq());
	
	
	
	}
	
	
}
