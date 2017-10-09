#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;

struct Nodo{
	int dato;
	Nodo *izq;
	Nodo *der;
};

class ArbolBinario{
	Nodo *raiz;
	
	int profundidad(Nodo *);
	//Metodos
	public:
		ArbolBinario();
		Nodo *agregar(Nodo *,int);
		int eliminar();
		void mostrarPreorden(Nodo *);
		void mostrarInorden(Nodo *);
		void mostrarPostorden(Nodo *);
		void mostrarNiveles();
		int profundidad();
		Nodo *buscar(Nodo *,int);
		Nodo *getRaiz();
		void setRaiz(Nodo *);
	
};

ArbolBinario::ArbolBinario(){
	raiz=NULL;
}

Nodo * ArbolBinario::getRaiz(){
	return raiz;
}

void ArbolBinario::setRaiz(Nodo *raiz){
	this->raiz=raiz;
}


Nodo * ArbolBinario::agregar(Nodo *raiz,int dato){
	if(raiz!=NULL){
       int profIzq = 0;
	   int profDer = 0;
	   profIzq = profundidad(raiz->izq);
	   profDer = profundidad(raiz->der);
	   if(raiz->der!=NULL){
          profDer++;
       }
       if(raiz->izq!=NULL){
          profIzq++;
       }
	   if(profDer!=0 || profIzq!= 0){
		  if(profIzq <= profDer){
			 raiz->izq=agregar(raiz->izq,dato);
		  }else{
			 raiz->der=agregar(raiz->der,dato);
		  }
	   }else{
		  raiz->izq=new Nodo;
		  raiz->izq->dato=dato;
		  raiz->izq->izq=raiz->izq->der=NULL;
	   }
    }else{    
		raiz=new Nodo;
		raiz->dato=dato;
		raiz->izq=raiz->der=NULL;
    }
	return raiz;
}

int ArbolBinario::eliminar(){
	int nodo, prof=0, elm=rand()%2;
	bool izq;
	Nodo *aux, *hoja=raiz;
	if(raiz){
		if(elm==0){
            while(hoja->izq!=NULL){
               aux = hoja;
               hoja = hoja->izq;
            }
            do{
               if(profundidad(hoja->izq)<=profundidad(hoja->der)){
                  aux = hoja;
                  hoja = hoja->izq;
                  izq=true;
               }else{
                  aux = hoja;
                  hoja = hoja->der;
                  izq =false;
               }
               prof = profundidad(hoja);
            }while(prof>0);
            nodo = hoja->dato;
            delete hoja;
            if(izq)
               aux->izq = NULL;
            else
               aux->der = NULL;
            return nodo;
        }else{
            while(hoja->der!=NULL)
               hoja = hoja->der;
            do{
               if(profundidad(hoja->izq)>=profundidad(hoja->der))
                  hoja = hoja->izq;
               else
                  hoja = hoja->der;
               prof = profundidad(hoja);
            }while(prof>0);
            nodo = hoja->dato;
            delete hoja;
            return nodo;
        }
	}
}

void ArbolBinario::mostrarPreorden(Nodo *raiz){
	if(raiz){
		cout<<raiz->dato<<" ";
		mostrarPreorden(raiz->izq);
		mostrarPreorden(raiz->der);
	}
}

void ArbolBinario::mostrarInorden(Nodo *raiz){
	if(raiz){
		mostrarInorden(raiz->izq);
		cout<<raiz->dato<<" ";
		mostrarInorden(raiz->der);
	}
}

void ArbolBinario::mostrarPostorden(Nodo *raiz){
	if(raiz){
		mostrarPostorden(raiz->izq);
		mostrarPostorden(raiz->der);
		cout<<raiz->dato<<" ";
	}
}

Nodo * ArbolBinario::buscar(Nodo *raiz, int dato){
	if(raiz){
		if(raiz->dato==dato)
			return raiz;
		else{
			buscar(raiz->izq,dato);
			buscar(raiz->der,dato);
		}
	}
	else
		return NULL;
}

int ArbolBinario::profundidad(){
	int prof = 0;
	prof = profundidad(raiz);
	return prof;
}

int ArbolBinario::profundidad(Nodo *raiz){
	if(raiz!=NULL){
        int proDer=0, proIzq=0;
	    Nodo *raizDer=raiz->der, *raizIzq=raiz->izq;
	    if(raizDer!=NULL){
	        proDer = 1;
	        proDer += profundidad(raizDer);
        }
    
        if(raizIzq!=NULL){
            proIzq = 1;
            proIzq += profundidad(raizIzq);
        }
    
        if(proDer>=proIzq)
            return proDer;
        else
            return proIzq;
    }else{
        return 0;
    }
}

char menu(){
	char opcion;
	cout<<"\n MENU\n";
	cout<<"(A)gregar\n";
	cout<<"(E)liminar\n";
	cout<<"(B)uscar\n";
	cout<<"(P)rofundidad\n";
	cout<<"(M)ostrar\n";
	cout<<"(T)erminar\n";
	cout<<"Eliga una opcion: ";
	cin>>opcion;
	return opcion;
}

int main(){
	srand(time(NULL));
	Nodo *raiz, *b;
	ArbolBinario arbol;
	char opcion;
	int dato, pro, elm;
	do{
		opcion=menu();
		switch(opcion){
			case 'a':
			case 'A':
				cout<<"Digite un elemento a agregar: ";
				cin>>dato;
				raiz=arbol.getRaiz();
				arbol.setRaiz(arbol.agregar(raiz,dato));
				break;
			case 'e':
			case 'E':
				elm=arbol.eliminar();
				cout<<"Elemento eliminado: "<<elm<<endl;
				break;
			case 'b':
			case 'B':
				cout<<"Digite un elemento a buscar: ";
				cin>>dato;
				raiz=arbol.getRaiz();
				b=arbol.buscar(raiz,dato);
				if(b)
					cout<<"El elemento "<<dato<<" se encuentra en el arbol\n";
				else
					cout<<"El elemento "<<dato<<" no se encuentra en el arbol\n";
				break;
			case 'p':
			case 'P':
				raiz=arbol.getRaiz();
				pro=arbol.profundidad();
				cout<<"Profundidad del arbol: "<<pro<<endl;
				break;
			case 'm':
			case 'M':
				raiz=arbol.getRaiz();
				cout<<"El arbol en PreOrden:\n";
				arbol.mostrarPreorden(raiz);
				cout<<"\nEl arbol en InOrden:\n";
				arbol.mostrarInorden(raiz);
				cout<<"\nEl arbol en PostOrden:\n";
				arbol.mostrarPostorden(raiz);
				break;			
		}
	}while(opcion!='T' && opcion!='t');
	return 0;
}
