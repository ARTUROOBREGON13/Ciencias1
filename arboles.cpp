//CARLOS ARTURO OBREGON RAVELO 20141020009

#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;

struct Nodo{
	int dato;
	Nodo *izq;
	Nodo *der;
};

struct NodoPila{
	int dato;
	Nodo *sig;
};

class Pila(){
	public:
		Nodo *cabeza;
		Pila();
		int sacar();
		void insertar(int n);
		bool vacio();
};

Pila::Pila(){
	cabeza =NULL;
}

void Pila::insertar(int n){
    NodoPila* np, *aux;
    np->dato = n;
    np->sig=NULL;
	if(cabeza==NULL)
	   	cabeza = np;
	else{
		aux = cabeza;
		while(aux->sig != NULL){
			aux=aux->sig;
		}
		aux->sig=np;
	}
}

int Pila::sacar(){
	NodoPila *aux, *np;
	int n;
	np = cabeza;
	while(np->sig!=NULL){
		aux = np;
		np = np->sig;
	}
	aux->sig=NULL;
	n= np->dato;
	delete np;
	return n;
}

bool Pila::vacio(){
	if(cabeza!=NULL)
	   return false;
	return true;
}

class ArbolBinario{	
	protected:
	int profundidad(Nodo *);
	//Metodos
	public:
		Nodo *raiz;
		ArbolBinario();
		Nodo *agregar(Nodo *,int);
		int eliminar();
		void mostrarPreorden(Nodo *);
		void mostrarInorden(Nodo *);
		void mostrarPostorden(Nodo *);
		void mostrarNiveles();
		int profundidad();
		int contarNodos();
		int contarHojas();
		Nodo *buscar(Nodo *,int);
		Nodo *getRaiz();
		void setRaiz(Nodo *);
		bool esCompleto(Nodo *);
	
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
			cout<<"Entra al elemento a eliminar"<<endl;
            while(hoja->izq!=NULL){
               aux = hoja;
               hoja = hoja->izq;
            }      
            do{
               if(profundidad(hoja->izq)<=profundidad(hoja->der)){
                  aux = hoja;
                  hoja = hoja->izq;
                  izq=true;
                  cout<<"Escoje eliminar del lado izquierdo-izq"<<endl;
               }else{
                  aux = hoja;
                  hoja = hoja->der;
                  izq =false;
                  cout<<"Escoje eliminar del lado izquierdo-izq"<<endl;
               }
               prof = profundidad(hoja);
            }while(prof>0);
            nodo = hoja->dato;
            if(izq)
               aux->izq = NULL;
            else
               aux->der = NULL;
            delete hoja;
			return nodo;
        }else{
            while(hoja->der!=NULL){
               aux=hoja;
			   hoja = hoja->der;
			}
            do{
               if(profundidad(hoja->izq)>=profundidad(hoja->der)){
				  izq = true;
				  aux = hoja;
				  hoja = hoja->izq;
               }else{
               	  izq = false;
               	  aux = hoja;
                  hoja = hoja->der;
               }prof = profundidad(hoja);
            }while(prof>0);
            nodo = hoja->dato;
            if(izq)
			   aux->izq = NULL;
			else
			   aux->der = NULL;   
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

void ArbolBinario::mostrarNiveles(){
	Pila p;
	Nodo *n = raiz, *izq, *der;
	int nodo = n->dato;
	p.insertar(nodo);
	izq = n;
	der = n;
	while(!p.vacio()){
		cout<<p.sacar()<<" ";
		izq = izq->izq;
		der = der->der;
		if(izq->izq!=NULL){
			nodo = izq->dato;
			p.insertar(nodo);
		}
		if(der->der!=NULL){
			nodo = der->dato;
			p.insertar(nodo);
		}
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

bool ArbolBinario::esCompleto(Nodo *raiz){
	if(raiz!=NULL){
		if(raiz->der!=NULL && raiz->izq!=NULL){
			return esCompleto(raiz->der) && esCompleto(raiz->izq);
		}else if(raiz->der==NULL && raiz->izq==NULL){
			return true;
		}
		return false;
	}
	return true;
}

class ArbolBinarioOrd::ArbolBinario{
	public:
		ArbolBinarioOrd();
		Nodo *agregar(Nodo *,int);
};

ArbolBinarioOrd::ArbolBinarioOrd(){
	raiz= NULL;
}

ArbolBinarioOrd::Agregar(Nodo *r, int dato){
	if(r!=NULL){
		if(r->dato<dato){
			if(r->der!=NULL)
				Agregar(r->der,dato);
			else{
				Nodo aux;
				aux->dato=dato;
				aux->izq=NULL;
				aux->der=NULL;
				r->der = aux;
			}
		}else{
			if(r->dato=dato){
				return raiz;
			}
			if(r->izq!=NULL)
				Agregar(r->izq,dato);
			else{
				Nodo aux;
				aux->dato=dato;
				aux->izq=NULL;
				aux->der=NULL;
				r->izq = aux;
			}
		}
	}
	else{
		Nodo aux;
		aux->dato=dato;
		aux->izq=NULL;
		aux->der=NULL;
		r = aux;
	}
	return raiz;
}

char menu(){
	char opcion;
	cout<<"\n MENU\n";
	cout<<"(A)gregar\n";
	cout<<"(E)liminar\n";
	cout<<"(B)uscar\n";
	cout<<"(P)rofundidad\n";
	cout<<"(M)ostrar\n";
	cout<<"(C)ontar\n";
	cout<<"Comp(L)eto\n";
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
				cout<<"\nEl arbol por Niveles:\n";
				arbol.mostrarNiveles();
				break;
				
			case 'c':
			case 'C':
				int nodos, hojas;
				nodos = arbol.contarNodos();
				hojas = arbol.contarHojas();
			    cout<<"Cantidad Nodos ="<<nodos;
			    cout<<"Cantidad Hojas ="<<hojas;	
				break;		
				
			case 'L':
			case 'l':
				raiz = arbol.getRaiz();
				if(arbol.esCompleto(raiz))
				   cout<<"\nEl arbol es completo\n";
				else
				   cout<<"\nEl arbol no es completo\n";
				break;
		}
	}while(opcion!='T' && opcion!='t');
	return 0;
}
