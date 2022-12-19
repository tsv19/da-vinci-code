// Autores:
// João Lucas Cordeiro - GRR20190427
// Tiago Serique - GRR20195138

#include <string>
#include <iostream>
#include <algorithm>
#include <string.h>


#define PF "deraonlhsivftgpcbuqmxzkwy"
// Tabela Play Fair
// DERAO
// NLHSI
// VFTGP
// CBUQM
// XZKWY
// DERAONLHSIVFTGPCBUQMXZKWY

#define VG "davincicode"
// DAVINCICODE

int vetor_playfair[26];
int vetor_vigenere[26];
char matriz[25+1]; 		// +1 por causa do '\0'
char chavevg[11+1]; 	// +1 por causa do '\0'

//funcao que retorna se o caractere é letra ou nao
//(usado depois de transformar todas as maiusculas em minusculas)
bool ehLetra(const char &c){
	return ( c >= 97 && c <= 122 )? true : false;
}

//funcao que retorna se o caractere é numero ou nao
bool ehNumero(const char &c){
	return ( c >= 48 && c <= 57 )? true : false;
}

//funcao que inicia os vetores usados nas cifras
void iniciaVetoresCifra(){
	strcpy(matriz, PF);
	strcpy(chavevg, VG);

	//o vetor_playfair guarda onde a letra daquele indice está na matriz pf
	for (size_t i {0} ; i < 26 ; i++){
		int posicao {matriz[i] - 97};
		vetor_playfair[posicao] = i;
	}
	vetor_playfair[9] = vetor_playfair[8];	//copia o I no J

	//o vetor_vigenere guarda quantas posições a letra sera deslocada de acordo com a posicao na chave
	for (size_t i {0} ; i < 11 ; i++){
		int deslocamento {chavevg[i] - 97};
		vetor_vigenere[i] = deslocamento;
	}
}

//funcao que faz a cifra vigenere
std::string cifra2(const std::string &entrada){
	std::string saida {};
	int i_chave {0};

	for (size_t i {0} ; i < entrada.length() ; ){
		//nao cifra o que nao for letra
		while ( !(ehLetra(entrada[i])) ){
			saida += entrada[i];
			i++;
		}

		//faz o deslocamento de acordo com a posicao na chave
		int c {entrada[i] + vetor_vigenere[i_chave]};

		//caso a letra saia do campo de letras minusculas com a soma
		if ( c > 122 ) saida += (char)(c % 123 + 97);
		else saida += c;

		i_chave = (i_chave + 1) % 11;
		i++;
	}

	return saida;
}

//funcao que faz a cifra play fair
std::string cifra1(const std::string &entrada){
	std::string saida {};

	for (size_t i {0} ; i < entrada.length() ;){
		std::string aux {};

		char letra1 {entrada[i]};
		//nao cripta o que nao for letra
		while ( !(ehLetra(letra1)) && (i < entrada.length())){
			saida += letra1;
			i++;
			letra1 = entrada[i];
		}

		//cabou a string
		if (i >= entrada.length())
			continue;

		i++;

		char letra2 {entrada[i]};
		//guarda o que nao for letra entre duas letras em aux
		while ( !(ehLetra(letra2))){
			aux += letra2;
			i++;
			letra2 = entrada[i];
		}

		char saida1 {};
		char saida2 {};

		//pega quais linhas e colunas de cada letra
		int linha1	{vetor_playfair[letra1 - 97] / 5};
		int linha2	{vetor_playfair[letra2 - 97] / 5};
		int coluna1	{vetor_playfair[letra1 - 97] % 5};
		int coluna2	{vetor_playfair[letra2 - 97] % 5};

		//faz a cifra
		if ( linha1 == linha2 ){
			saida1 = matriz[linha1*5 + ((coluna1+1) % 5)];
			saida2 = matriz[linha2*5 + ((coluna2+1) % 5)];
		}
		else if ( coluna1 == coluna2 ){
			saida1 = matriz[((linha1+1) % 5)*5 + coluna1];
			saida2 = matriz[((linha2+1) % 5)*5 + coluna2];
		}
		else{
			saida1 = matriz[(linha1)*5 + coluna2];
			saida2 = matriz[(linha2)*5 + coluna1];
		}

		//coloca as letras com aux no meio
		saida += saida1;
		saida += aux;
		saida += saida2;

		i++;
	}

	return saida;
}

//funcao que deixa os caracteres maiusculos, minusculos
void deixaMinuscula(std::string &entrada){
	for (size_t i {0} ; i < entrada.length() ; i++)
		if (entrada[i] >= 65 && entrada[i] <= 90)
			entrada[i] = entrada[i] + 32;
}

void trataEntrada(std::string &entrada_tratada){
	std::string entrada_parcial {};
	std::string entrada {};
	
	// pega linha inteira de uma vez e coloca na string de entrada
	
	while (getline(std::cin, entrada_parcial)){
		entrada += entrada_parcial;
	}

	// remove os espacos vazios da string, se houverem
	entrada.erase(remove(entrada.begin(), entrada.end(), ' '), entrada.end());
	deixaMinuscula(entrada);

	for (size_t i {0} ; i < entrada.size() ;){
		char letra1 {(char) tolower(entrada[i])};

		//enquanto não for letra e não ultrapassar o tamanho da string
		while ( !(ehLetra(letra1)) && (i < entrada.size())){
			//se for um número, coloca na string
			if (ehNumero(letra1))
				entrada_tratada += letra1;
			i++;
			letra1 = entrada[i];
		}
		//passando daqui, letra1 com certeza possui uma letra ou acabou a string

		//acabou a string
		if ((i >= entrada.size()))
			continue;

		entrada_tratada += letra1;
		i++;
		
		char letra2 {(char) tolower(entrada[i])};

		while ( !(ehLetra(letra2)) && (i < entrada.size())){
			//se for um número, coloca na string
			if (ehNumero(letra2))
				entrada_tratada += letra2;
			i++;
			letra2 = entrada[i];
		}

		if ( letra1 == letra2 || letra2 == '\0' || !ehLetra(letra2))
			entrada_tratada += 'x';
		else
			entrada_tratada += letra2;

		//no caso das letras iguais, a letra2 será usada na proxima dupla
		if (letra1 != letra2)
			i++;
	}
}


int main(){
	std::string entrada {};

	iniciaVetoresCifra();
	trataEntrada(entrada);

	//std::cout << entrada << std::endl;		//para ver a string tratada, o que realmente foi encriptado
	//std::cout << "Cifra final:" << std::endl;
	std::cout << cifra2(cifra1(entrada)) << std::endl;
}