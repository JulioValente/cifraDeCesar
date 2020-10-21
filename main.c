#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

void nl(int y){  //função para novas linhas.
    for(int i=0;i<y;i++){
        printf("\n");
    }
}

void tabul (int t){ //função para tabulações.
	int i;

	for(i=0; i<t; i++){
		printf("\t");
	}
}

void cabecalho (){ //função do cabeçalho.
	printf("*================================================================================================================*");
	printf("\n\t\t\t\tdecodificador");
	printf("\n*================================================================================================================*");
	printf("\n\n");

	printf(" ->");
	tabul(3);
	printf("decodifica uma mensagem recebida por um arquivo de mensagem");
	nl(2);

	printf(" ->");
	tabul(3);
	printf("não pode ser escrito com caracteres especiais");
	nl(3);
}

void rodaMensagem(char *mensagem, int tamanho, int numRotacoes){ //função para deslocar os caracteres da mensagem.
    for(int i=0; i<tamanho;i++){
        mensagem[i] = ((mensagem[i]-'A')+numRotacoes)%26 + 'A';
    }
}

void rodaMensagemAntHorario(char *mensagem, int tamanho, int numRotacoes){ //função para deslocar os caracteres da mensagem.
	int i;
    for(i=0; i<tamanho;i++){
        mensagem[i] = ((mensagem[i]-'A')+numRotacoes)%26 - 'Z';
    }
}

int verificaChar(char c){ //verifica se o caractere é vogal ou consoante. Retorna v para vogal e s para consoante.
    return (c=='A' || c=='E' || c=='I' || c=='O' || c=='U')?'v':'s';
}

int verificaMensagem(char *mensagem, int tamanho){ //Verifica a coerência da mensagem. Retrona 1 se a mensagem é coerente e 0 caso contrário.
    char estruturaMensagem[11];

    /*armazena os primeiros caracteres da mensagem*/
    if(tamanho<10){
        for(int i=0;i<tamanho;i++){
            estruturaMensagem[i] = verificaChar(mensagem[i]);
        }
        estruturaMensagem[tamanho] = '\0';
    }else{
        for(i=0;i<10;i++){

        }
        estruturaMensagem[10] = '\0';
    }
    /**/

    /*verifica a estruturação das primeiras letras da mensagem*/
    char *estruturacoes[] = {"sv", "svv", "svvv", "ssv", "ssvv", "ssvvv", "vs", "vss", "vsss"}; //possíveis estruturações
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            char temp[10];
            strcpy(temp,estruturacoes[i]);
            strcat(temp, estruturacoes[j]);
            if(!strcmp(estruturaMensagem, temp)){
                return 1;
            }
        }
    }
    return 0;
    /**/
}

void decifraMensagem(char *mensagem, int tamanho){ //decifra a mensagem automaticamente.
    int i;
  
    for(i=1;i<26;i++){
      for(i=1;i<26;i++){

        rodaMensagem(mensagem, tamanho, i);

        if(verificaMensagem(mensagem, tamanho)){
            break;
        }
    }
}

int main(){
    FILE *arquivo;
    char nomeArquivo[30];
    char mensagem[100];
    int mensagemTamanho=0;

    setlocale(LC_ALL, "");

    cabecalho();

    printf("Digite o nome do arquivo: ");
    nl(2);
    scanf("%s", nomeArquivo);

    strcat(nomeArquivo, "_dec.txt"); //adiciona o formato do arquivo.

    arquivo = fopen(nomeArquivo, "r");

    if(arquivo == NULL){ //verifica se o arquivo foi aberto.
        nl(1);
        printf("Não foi possível abrir o arquivo.");
        nl(2);
        printf("Digite qualquer tecla para sair.");
        getch();
        return 1;
    }


    /*armazena a mensagem do arquivo*/

    char c;

    setlocale(LC_ALL, "");
    
    /*rodando o programa*/
    while(1){
    	switch(menu()){
    		case '1': 	system("cls");
    					printf(" chabonga");
    					getch();
    			break;
    			
    		case '2': 	system("cls");
						printf("Digite o nome do arquivo: ");
					    nl(2);
						scanf("%s", nomeArquivo);
					
						strcpy(temp, nomeArquivo); //copia o nome do arquivo para uma variável temporária.
					    strcat(temp, ".txt"); //adiciona o formato do arquivo.
					    arquivo = fopen(temp, "r");
					
					    if(arquivo == NULL){ //verifica se o arquivo foi aberto.
					        nl(1);
					        printf("Não foi possível abrir o arquivo.");
					        nl(2);
					        printf("Digite qualquer tecla para sair.");
					        getch();
					        return 1;
					    }
					
					
					    /*armazena a mensagem do arquivo*/
					
					    c = fgetc(arquivo);
					    while(c!=EOF){
					        if(c >= 'A' && c <= 'z'){
					            mensagem[mensagemTamanho] = toupper(c);
					            mensagemTamanho++;
					        }
					        c=fgetc(arquivo);
					    }
					
					    /**/
					
					    if(fclose(arquivo) == EOF){ //verifica se o arquivo foi fechado.
					        nl(2);
					        printf("Não foi possível fechar o arquivo.");
					        nl(2);
					        printf("Digite qualquer tecla para sair.");
					        getch();
					        return 1;
					    }
					
						decod(mensagem);
					
					
						/*salvando a mensagem*/
					    strcat(nomeArquivo, "_dec.txt"); //adiciona o formato do arquivo.
					    arquivo = fopen(nomeArquivo, "w+t");
					
					    if(arquivo == NULL){ //verifica se o arquivo foi criado.
					        nl(1);
					        printf("Não foi possível abrir o arquivo.");
					        nl(2);
					        printf("Digite qualquer tecla para sair.");
					        getch();
					        return 1;
					    }
					
					    fprintf(arquivo, "%s", mensagem);
					
					    if(fclose(arquivo) == EOF){ //verifica se o arquivo foi fechado.
					        nl(2);
					        printf("Não foi possível fechar o arquivo.");
					        nl(2);
					        printf("Digite qualquer tecla para sair.");
					        getch();
					        return 1;
					    }
					
					
					    nl(1);
					    printf("Operação concluída com sucesso.");
					
					    /**/
					
					    //fim do programa.
					    nl(2);
					    printf("Digite qualquer tecla para sair.");
					    getch();
    			break;
    			
    		case '3': return 0;
    			
    		default: nl(2);
				   	 printf(" opção inválida");
					 getch();	
		}	
	}
	/**/

    //fim do programa.
    nl(2);
    printf("Digite qualquer tecla para sair.");
    getch();

	return 0;
}
