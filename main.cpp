/* Introduccion a la programación COD: 00831

Proyecto Final en lenguaje C++

Alumna: Floricela Arguedas Zúñiga

Descripción: Programa que incluye 2 juegos y utiliza el manejo de archivos para su funcionamiento.
*/
//Prototipo
#include <iostream>
#include <iomanip> //Para poder tabular las salidas a pantalla con setw
#include <stdlib.h>
#include <fstream> //Libreria para el uso de archivos
#include <cstdlib> //Libreria para usar función rand
#include <ctime> //Librería para usar la función srand
#include<locale.h>//Librearía para el idioma español

using namespace std;
// Declaracion de variables globales y funciones.
int opcion_menu=0;
int azar;
char continuar ='s';
int turnosj1=0;
int turnosj2=0;
int ptsj1=0;
int ptsj2=0;
string puntaje_nuevo;
void menu();
void guardar_registro();
void reporte_jugadores();
void imprimir_top10();
void abrir_dip_hiato();
void abrir_sin_ant();
void agregar_puntaje (string cedula,int);
void finaliza_ganador();
bool turno_activo=true;
bool string_numerico(string);
void ordenar_top10();
string jugador1;
string jugador2;

//Funcion principal MAIN
int main()
{
    setlocale (LC_ALL,"Spanish");//Utilizado para que se lean las tíldes.
    cout<< "|| BIENVENIDO A JUGANDO Y APRENDIENDO CON LAS PALABRAS ||\n" <<endl;
    srand(time(0));//Semilla para generar números aleatorios cambiantes en cada ejecución.
    //Llamada a la función menú.
    menu();

    return 0;
}

//Funcion del menú
void menu(){
     //Switch que permitira el desarrollo del programa de acuerdo con las opciones del menú.
    do {
        //Presentación del menú del programa.
        cout<<"\n";
        cout<< "-        MENÚ PRINCIPAL      -\n"<<endl;
        cout<< "1. Ingresar jugadores "<<endl;
        cout<< "2. Jugar Hiatos y Diptongos "<<endl;
        cout<< "3. Jugar Sinónimos y Antónimos "<<endl;
        cout<< "4. Mostrar reporte de jugadores "<<endl;
        cout<< "5. Visualizar tabla del TOP 10 "<<endl;
        cout<< "6. Salir del programa\n "<<endl;
        cin >>opcion_menu;

        switch (opcion_menu){

        case 1:
            guardar_registro();
        break;

        case 2:
            abrir_dip_hiato();
            if ( ptsj1 !=0 && ptsj2 !=0){
                agregar_puntaje(jugador1,ptsj1);
                agregar_puntaje(jugador2,ptsj2);
            }
        break;

        case 3:
            abrir_sin_ant();
            if ( ptsj1 !=0 && ptsj2 !=0){
                agregar_puntaje(jugador1,ptsj1);
                agregar_puntaje(jugador2,ptsj2);
            }
        break;

        case 4:
            reporte_jugadores ();
        break;

        case 5:
            ordenar_top10 ();
        break;
        }
    }while (opcion_menu!=6);
}
// Reviso con esta funcion si la cedula ya esta en el archivo y creo una bandera para guardar datos en caso de no estar.
bool existe_jugador (string cedula){
    ifstream existe("Registro.txt", ios::in); //Abro el archivo
    if (!existe){
        cout<< "ERROR °° No se pudo abrir el archivo °°\n";
        exit(1);
     }
    string num_iden;
    while (existe>>num_iden){ //Recorro el archivo por líneas y voy guardando la cedula para poder compararla con la que recibo del usuario.
        if(num_iden == cedula){
          existe.close();
          return true;
        }
    }
   existe.close();
   return false;
 }
//Funcion para guardar los registros de los jugadores en el archivo correspondiente.
void guardar_registro(){
    ofstream Registro;
    string num_iden,nombre;
    Registro.open("Registro.txt",ios::app); //Abro el archivo y utilizo app para que me ingrese los datos al final y no me sobreescriba.
    if (!Registro){
        cout<< "ERROR °° No se pudo abrir el archivo °°\n";
        exit(1);
     }

    char registrar='s';
    while (registrar=='s'){
        cin.ignore();//Limpio el bufer para que no guarde lo capturado en el cin del menú, porque uso getline adelante.
        cout <<"\nNúmero de cédula: ";
        getline(cin,num_iden);
        while (!string_numerico(num_iden)){
            cout <<"\nNúmero de cédula: ";
            getline(cin,num_iden);//Utilizo getline, porque la variable es string y no char.
        }
        cout <<"\nNombre: ";
        getline(cin,nombre);
        if (existe_jugador (num_iden) == false){ //Llamo a la funcion que revisa si ya la cédula existe
            Registro<<num_iden<<" "<<nombre<<" 0"<<endl;//Ingreso un cero para que todos los puntajes inicien en cero.
        }
        else {
            cout<< "\n °°Este jugador ya se encuentra registrado°° "<<endl;
        }
        cout<< "\n Desea ingresar otro registro ? Digite S o N ";
        cin>>registrar;
        while (registrar !='s' && registrar !='n'){
            cout<< "\n Desea ingresar otro registro ? Digite S o N ";
            cin>>registrar;
        }
    }
   Registro.close();
}
//Funcion para mostrar reporte de los jugadores
void reporte_jugadores (){
     string num_iden,nombre,puntaje;
     ifstream registro( "Registro.txt",ios::in); //Abro el archivo en modo lectura

     if (!registro){
        cout<< "ERROR °° No se pudo abrir el archivo °°\n";
        exit(1);
     }
     cout<< " || REPORTE DE JUGADORES || \n"<<endl;
     cout<< "Número de Cédula"<<setw(11)<<" Nombre \n"<<endl;//Imprimo encabezado
     while (registro>>num_iden>>nombre>>puntaje){//Apunto a los datos del archivo y los imprimo en pantalla.
        cout<<left<<setw(3)<<" "<<num_iden<<" "<<right<<setw(12)<<nombre<<endl;
     }
}

//Funcion para validar que los jugadores ya estén registrados o de lo contrario salir al menu principal.
bool registro_valido(){

    char decision='c';
    while(decision=='c'){
        do{
            cout << "Indique la cedula del jugador 1: ";
            cin>>jugador1;
        } while(!string_numerico(jugador1));//Llamo a la función para validar que haya escrito números en la cédula.

        if ( existe_jugador (jugador1) == false){//Llamo a función para revisar que se encuentre registrado el jugador.
            do {
                cout << "\n Para poder jugar debe estar registrado \n" <<endl;
                cout << "\n Si desea regresar al menu digite 'm', si desea ingresar de nuevo la cédula digite 'c' \n"<<endl;
                cin >>decision;
                decision = tolower(decision);
            }while(decision != 'c' && decision != 'm');

            if (decision == 'm'){
                return false; //retorno falso para devolverme a la función y posterior al menú.
            }
        } else {
            break;// Hago break para que no se encicle con el valor de decisión.
        }
    }

    while(decision=='c'){
        do{
            cout << "Indique la cedula del jugador 2: ";
            cin>>jugador2;
        } while(!string_numerico(jugador2));

        if ( existe_jugador (jugador2) == false){
            do {
                cout << "\n Para poder jugar debe estar registrado \n" <<endl;
                cout << "\n Si desea regresar al menu digite 'm', si desea ingresar de nuevo la cédula digite 'c' \n"<<endl;
                cin >>decision;
                decision = tolower(decision);
            } while(decision != 'c' && decision != 'm');

            if (decision == 'm'){
                return false;
            }
        } else {
            break;
        }
    }

    return true;
}
//Funcion para abrir el documento de hiatos y diptongos y jugarlo.
void abrir_dip_hiato(){
    cout<< " || BIENVENIDOS AL JUEGO DE HIATO Y DIPTONGO ||\n"<<endl;
    if (!registro_valido()) return; //Si la función viene en false, retorno para salir al menú.

    continuar='s'; //Reestablezco continuar a positivo, para poder entrar al juego.
    turnosj1=0;//Reestablezco los turnos a cero.
    turnosj2=0;
    ptsj1=0;//Reestablezco los puntos a cero
    ptsj2=0;
    while ((turnosj1<=15 || turnosj2<=15) && continuar== 's'){

    //Abro el archivo para comenzar el juego.
    ifstream archivodh ("diptongos_hiatos.txt",ios::in);
     if (!archivodh){
        cout<< "ERROR °° No se pudo abrir el archivo °°\n";
        exit(1);
     }
    string dip_hiato;//Creo string para extraer del archivo la palabra y guardarla.
    char palabra; // Variable para calificar si la palabra es hiato o diptongo.
    int compara=0;//Contador de las filas del archivo
    char respuesta; //Guardo la respuesta del jugador para compararla con la palabra.

//INICIA EL TURNO DEL JUGADOR 1
    if (turno_activo ==true) { //Utilizo un booleano para alternar los turnos de los jugadores.
        //Limpio los char y contador para poder ingresar al turno con las validaciones limpias.
        palabra=' ';
        respuesta=' ';
        compara=0;
        azar = rand()%50;//Genero numero al azar que utilizo para sacar una palabra aleatoria del archivo.

        //Creo un ciclo para ir leyendo las lineas del archivo y aumentar un contador para poder comparar.
        while (!archivodh.eof()){
            getline(archivodh,dip_hiato);
            if (compara==azar){ //Si el numero de fila del archivo es igual al numero al azar, imprimo en pantalla la palabra.
                archivodh>>dip_hiato;
                cout<<"\n |||| Es el turno del jugador 1 |||| "<<endl;
                cout<< "\n La siguiente palabra: "<<dip_hiato<< " Es hiato (h) o diptongo (d)? ";
                cin>>respuesta;
                respuesta= tolower(respuesta);
                while (respuesta != 'h' && respuesta != 'd'){
                    cout<<"\nDebe digitar una (h) o una (d) para clasificar la palabra ";
                    cin>>respuesta;
                }
                turnosj1+=1;
                break; //Hago el break para que no siga recorriendo con el while el archivo.
            }
            compara++;
    }
    //Con los siguientes if, valido que la respuesta sea correcta o incorrecta.
            if (azar>=0 && azar <=24){
                    palabra= 'd';
            }
            if (azar>=25 && azar<=49){
                palabra='h';
            }
            if (palabra == respuesta){
                cout<<"\n Correcto ganaste un punto\n"<<endl;
                ptsj1+=1;
                cout<<"\n Los puntos que lleva son: "<<ptsj1<<endl;//Le muestro al jugador los puntos que lleva.
            }
            else cout<< "\n°° Incorrecto, perdiste el turno °°\n"<<endl;
            turno_activo=false; //Cambio el booleano para darle el turno al siguiente jugador.
        }
    archivodh.close();//Cierro el archivo, para que comience de nuevo en el siguiente turno.

// INICIA EL TURNO DEL SEGUNDO JUGADOR

    if (turno_activo==false) {
        ifstream archivodh ("diptongos_hiatos.txt",ios::in); //Abro el archivo en lectura.
        if (!archivodh){
        cout<< "ERROR °° No se pudo abrir el archivo °°\n";
        exit(1);
        }
        //Limpio los char y contador para poder ingresar al turno con las validaciones limpias.
        palabra=' ';
        respuesta= ' ';
        compara=0;
        azar = rand()%50;//Genero de nuevo numero al azar, para este turno.
        while (!archivodh.eof()){
            getline(archivodh,dip_hiato);
            if (compara==azar){ //Si el numero de fila del archivo es igual al numero al azar, imprimo en pantalla la palabra.
                archivodh>>dip_hiato;
                cout<<"\n|||| Es el turno del jugador 2 |||| "<<endl;
                cout<< "\n La siguiente palabra: "<<dip_hiato<< " Es hiato (h) o diptongo (d)? ";
                cin>>respuesta;
                respuesta= tolower(respuesta);
                while (respuesta != 'h' && respuesta != 'd'){
                    cout<<"\nDebe digitar una (h) o una (d) para clasificar la palabra ";
                    cin>>respuesta;
                }
                turnosj2+=1;
                break; //Hago el break para que no siga recorriendo con el while el archivo.
            }
            compara++;
        }

        if (azar>=0 && azar <=24){
                palabra= 'd';
        }
        if (azar>=25 && azar<=49){
            palabra='h';
        }
        if (palabra == respuesta){
            cout<<"\n Correcto ganaste un punto\n"<<endl;
            ptsj2+=1;
            cout<<"\n Los puntos que lleva son: "<<ptsj2;
        }
        else cout<< "\n°° Incorrecto, perdiste el turno °°\n"<<endl;
        turno_activo=true; //Cambio el booleano para darle el turno al siguiente jugador.

    }
        finaliza_ganador(); //Llamo a la funcion para ver si desean seguir jugando o dar ganador del juego.

    archivodh.close();
    }
}
//Función para abrir el documento de sinónimos y antónimos y jugar.
void abrir_sin_ant(){
    cout<< " || BIENVENIDOS AL JUEGO DE SINÓNIMOS Y ANTÓNIMOS ||\n"<<endl;
    if (!registro_valido()) return;

    continuar='s'; //Reestablezco continuar a positivo, para poder entrar al juego.
    turnosj1=0;//Reestablezco los turnos a cero.
    turnosj2=0;
    ptsj1=0;//Reestablezco los puntos a cero
    ptsj2=0;
    while ((turnosj1<=15 || turnosj2<=15) && continuar== 's'){

    //Abro el archivo para comenzar el juego.
    ifstream archivosa ("sinonimos_antonimos.txt",ios::in); //Abro el archivo en lectura.
    if (!archivosa){
        cout<< "ERROR °° No se pudo abrir el archivo °°\n";
        exit(1);
     }

    string sin_ant;//Creo string para extraer del archivo la palabra y guardarla.
    char palabra; // Variable para calificar si la palabra es sinonimo o antonimo.
    int compara=0;//Contador de las filas del archivo
    char respuesta; //Guardo la respuesta del jugador para compararla con la palabra.

//INICIA EL TURNO DEL JUGADOR 1
    if (turno_activo ==true) { //Utilizo un booleano para alternar los turnos de los jugadores.
        //Limpio los char y contador para poder ingresar al turno con las validaciones limpias.
        palabra=' ';
        respuesta=' ';
        compara=0;
        azar = rand()%40;//Genero numero al azar que utilizo para sacar una palabra aleatoria del archivo.

        //Creo un ciclo para ir leyendo las lineas del archivo y aumentar un contador para poder comparar.
        while (!archivosa.eof()){
            getline(archivosa,sin_ant);
            if (compara==azar){ //Si el numero de fila del archivo es igual al numero al azar, imprimo en pantalla la palabra.
                archivosa>>sin_ant;
                cout<<"\n |||| Es el turno del jugador 1 |||| "<<endl;
                cout<< "\n Las siguientes palabras: "<<sin_ant<< " Son sinónimo (s) o antónimo (a)? ";
                cin>>respuesta;
                respuesta= tolower(respuesta);
                while (respuesta != 'a' && respuesta != 's'){
                    cout<<"\nDebe digitar una (a) o una (s) para clasificar la palabra ";
                    cin>>respuesta;
                }
                turnosj1+=1;
                break; //Hago el break para que no siga recorriendo con el while el archivo.
            }
            compara++;
    }
    //Valido la respuesta del jugador.
            if (azar>=0 && azar <=19){
                    palabra= 's';
            }
            if (azar>=20 && azar<=39){
                palabra='a';
            }
            if (palabra == respuesta){
                cout<<"\n Correcto ganaste un punto\n"<<endl;
                ptsj1+=1;
                cout<<"\n Los puntos que lleva son: "<<ptsj1<<endl;
            }
            else cout<< "\n°° Incorrecto, perdiste el turno °°\n"<<endl;
            turno_activo=false; //Cambio el booleano para darle el turno al siguiente jugador.
        }
    archivosa.close();//Cierro el archivo, para que comience de nuevo en el siguiente turno.

// INICIA EL TURNO DEL SEGUNDO JUGADOR

    if (turno_activo==false) {
        ifstream archivosa ("sinonimos_antonimos.txt",ios::in); //Abro el archivo en lectura.
        if (!archivosa){
        cout<< "ERROR °° No se pudo abrir el archivo °°\n";
        exit(1);
        }
        //Limpio los char y contador para poder ingresar al turno con las validaciones limpias.
        palabra=' ';
        respuesta= ' ';
        compara=0;
        azar = rand()%40;//Genero de nuevo numero al azar, para este turno.

        while (!archivosa.eof()){
            getline(archivosa,sin_ant);
            if (compara==azar){ //Si el numero de fila del archivo es igual al numero al azar, imprimo en pantalla la palabra.
                archivosa>>sin_ant;
                cout<<"\n|||| Es el turno del jugador 2 |||| "<<endl;
                cout<< "\n Las siguientes palabras: "<<sin_ant<< " Son sinónimo (s) o antónimo (a)? ";
                cin>>respuesta;
                respuesta= tolower(respuesta);
                while (respuesta != 'a' && respuesta != 's'){
                    cout<<"\nDebe digitar una (a) o una (s) para clasificar la palabra ";
                    cin>>respuesta;
                }
                turnosj2+=1;

                break; //Hago el break para que no siga recorriendo con el while el archivo.
            }
            compara++;
        }

        if (azar>=0 && azar <=19){
                palabra= 's';
        }
        if (azar>=20 && azar<=39){
            palabra='a';
        }
        if (palabra == respuesta){
            cout<<"\n Correcto ganaste un punto\n"<<endl;
            ptsj2+=1;
            cout<<"\n Los puntos que lleva son: "<<ptsj2; //Muestro puntaje
        }
        else cout<< "\n°° Incorrecto, perdiste el turno °°\n"<<endl;
        turno_activo=true; //Cambio el booleano para darle el turno al siguiente jugador.

    }
        finaliza_ganador(); //Llamo a la funcion para ver si desean seguir jugando o dar ganador del juego.

    archivosa.close();
    }
}

//Funcion para verificar si desean continuar jugando y dar ganador.
void finaliza_ganador(){

        cout<< "\n Desean continuar jugando S/N ? ";
        cin>>continuar;
        while (continuar != 's' && continuar!= 'n'){
        cout<< "\n Desean continuar jugando S/N ? Digíte S o N ";
        cin>>continuar;
        continuar = tolower(continuar);
        }

        if (continuar== 'n' || (turnosj1==15 && turnosj2==15)){

            if (ptsj1>ptsj2){

                cout<<"\n El ganador del juego es el Jugador 1, con la cedula: "<<jugador1<< " || FELICIDADES || \n"<<endl;
                cout << " || Has recibido un bono de +5 puntos por ganar || "<<endl;
                ptsj1+=5;
            }
            if (ptsj1<ptsj2){

                cout<<"\n El ganador del juego es el Jugador 2, con la cedula: "<<jugador2<< " || FELICIDADES || "<<endl;
                cout << "\n Has recibido un bono de +5 puntos por ganar "<<endl;
                ptsj2+=5;

            }
            if (ptsj1 == ptsj2){

                cout<<"\n Hubo un empate, ambos son ganadores" <<" || FELICIDADES || "<<endl;
            }
        }

}

//Funcion para guardar modificar y guardar puntajes.
void agregar_puntaje (string cedula,int puntaje){

    ifstream top("Registro.txt",ios::in);
     if (!top){
        cout<< "ERROR °° No se pudo abrir el archivo °°\n";
        exit(1);
     }
    ofstream aux("Puntaje.txt",ios::app);
     if (!aux){
        cout<< "ERROR °° No se pudo abrir el archivo °°\n";
        exit(1);
     }

    string num_iden,nombre,puntos,line;
//Extraigo del archivo de registro los datos para hacer el top, los guardo en un archivo auxiliar.
    while (getline(top, line)){
        num_iden = line.substr(0, line.find(" "));
        line.erase(0, line.find(" ")+1);

        nombre = line.substr(0, line.find(" "));
        line.erase(0, line.find(" ")+1);

        puntos = line.substr(0, line.find(" "));
        line.erase(0, line.find(" ")+1);

        if (num_iden==cedula){
            int ptos =stoi(puntos);//convierto el string del archivo a int para poder sumarlo.
            puntaje = ptos+puntaje;//El puntaje que gano el jugador se lo sumo al que ya tenia guardado.
            puntaje_nuevo=(to_string(puntaje));//Ahora convierto el entero a string para ingresarlo al archivo.
            aux<<num_iden<<" "<<nombre<<" "<<puntaje<<endl; //Finalmente guardo el registro nuevo en el archivo aux.
        }
        else aux<<num_iden<<" "<<nombre<<" "<<puntos<<endl;//Si la cédula no coincide guardo los datos de jugador iguales al otro archivo.
    }
    top.close();
    aux.close();
    //Borro el archivo original y al auxiliar lo renombro igual al borrado.
    remove("Registro.txt");
    rename("Puntaje.txt","Registro.txt");
}

//Funcion para ordenar el top 10 y mostrarlo en pantalla.
void ordenar_top10 (){
    string ced,nom,puntos;
    int puntaje;
    int num_jug=0;
    ifstream registro ("Registro.txt", ios::in);
     if (!registro){
        cout<< "ERROR °° No se pudo abrir el archivo °°\n";
        exit(1);
     }
    //Recorro el archivo con este while, para saber cuantos jugadores hay y usar esa variable como condicion.
    while (registro>>ced>>nom>>puntos){
        num_jug++;
    }
    registro.close();// Cierro el archivo para arrancar de nuevo en la fila 0
    int puntajes[num_jug]; //Defino arreglo para ingresar los puntos de los jugadores y poder usar burbuja.
    string nombres[num_jug]; //Defino arreglo para meter lo nombres y ordenarlos en burbuja.
    registro.open("Registro.txt", ios::in); //Abro de nuevo el archivo para recorrerlo y extraerle datos para los arreglos.
    if (!registro){
        cout<< "ERROR °° No se pudo abrir el archivo °°\n";
        exit(1);
     }
    for (int i=0;i<num_jug;i++){ //Recorro el archivo para extraer los puntos y convertirlos a enteros.
        registro>>ced;
        registro>>nom;
        registro>>puntos;
        puntaje =stoi(puntos);//Convierto el string que obtiene el puntaje a entero.
        puntajes[i]=puntaje;//Guardo los puntos en un arreglo
        nombres[i] = nom;//Guardo los nombres en otro arreglo
    }
    registro.close();
    //Metodo burbuja para ordenar los puntajes y nombres
    cout<<endl;
    for (int i=0;i<num_jug;i++){
        for (int p=0;p<num_jug-1;p++){
            if (puntajes[p]<puntajes[p+1]){
                int tempo = puntajes[p];
                puntajes[p] = puntajes[p+1];
                puntajes[p+1] =tempo;
//Uso el mismo if y ordeno el arreglo de nombres igual que los puntos, basandome en la posición.
                string tmp = nombres[p];
                nombres[p] = nombres[p+1];
                nombres[p+1] = tmp;
            }
        }
    }
//Realizo ciclo para que imprima maximo 10 y condiciono que el puntaje no esté en 0 para que no salgan todos los jugadores.
    cout<<" ||| TOP 10 DE JUGADORES ||| \n"<<endl;
    cout<< " Nombre "<<setw(15)<<" Puntaje \n"<<endl;//Imprimo encabezado
    for (int i=0;i<10;i++){
        if (puntajes[i]!=0){
            cout<<setw(7)<<nombres[i]<<" "<<setw(10)<< puntajes[i] <<endl;
        }
    }
}

bool string_numerico (string jugador){
    int tamano=jugador.size(); //Extraigo el largo del string para usarlo como condición.
    for (int i=0;i<tamano;i++){
        if (jugador[i] < 48 || jugador[i]>57){ //Si el string es menor o mayor a ese rango en ASCII no es numérico.
            cout << " La cedula debe contener solo digitos del 0-9" << endl;
            return false;
        }
    }
    return true;
}
