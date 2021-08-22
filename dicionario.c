#include "dicionario.h"

int verifica(char a[],char b[]){			//Função que verifica qual string vem primeiro alfabeticamente
     int i,j;
     int ind=0;
     for(i=0,j=0 ; a[i]!='\0'&&b[j]!='\0' ; i++,j++){		//Percorre as Strings
       if(a[i]>b[j]){										//Compara até encontrar um caracter maior em a;
         ind=1;												//Indica o caso
         break;												//Sai do loop
       }
       else if(b[j]>a[i]){									//Compara até encontrar um caracter maior em b;
         ind=-1;											//Indica o caso
         break;												//Sai do loop
       }
     }
     return ind;											//retorna a indicadora
}

void chama_busca(void){										//Função que auxilia na execução da função busca
    int ind=0;

    while(ind!=3){
		printf("\n1- Lista de Palavras / 2-Digitar Palavra / 3 - Retornar: ");
		scanf("%d", &ind);
        switch (ind) {
            case 1:
                ler_palavras(raiz);												//Função que lista as palavras no dicionario
                printf("\n");
                break;
            case 2:
                busca();														//Função que realiza em si a busca no Dicionario
                break;
            case 3:
                break;
            default:
                printf("INVALIDO!!!");
                break;
        }
    }
}

void busca(void){										//Função que realiza a busca no Dicionario
    int flag=0;
    Dicionario *ptr1;
    ptr1=raiz;
    char str1[TAM];
    printf("\nEscreva a palavra que busca: ");
    scanf("%s",str1);									//str se refere a palavra a ser buscada
    while(ptr1!=NULL && flag==0){
        if(verifica(str1,ptr1->palavra)>0)				//Chama a função para definir se a palavra vem antes ou depois alfabeticamente da palavra no nó do Dicionario
            ptr1=ptr1->dir;								//Caso venha depois vai para o nó da direita
        else if(verifica(str1,ptr1->palavra)<0)
            ptr1=ptr1->esq;								//Caso venha antes vai para o nó da esquerda
        else if(verifica(str1,ptr1->palavra)==0){		//Caso onde a palavra no nó coincide com a informada pelo usuario
            flag=1;										//Altera a indicadora para sair do loop
            printf("\nSignificado: %s",ptr1->significado);
        }
    }
    if(flag==0)											//Se o loop acabar e a indicadora estiver inalterada
        printf("\nPalavra não encontrada\n");			//a palavra não está no Dicionario
}

void inserir(Dicionario *temp){									//Função para inserir termos e significados no Dicionario
	int flag=0;
	Dicionario *ptr1, *ptr2;
	ptr1=raiz;
	if(raiz==NULL)												//Caso a raiz esteja vazia simplesmente insere o nó recebido na raiz;
		raiz = temp;
	else{
		while(ptr1!=NULL ){										//Percorre o Dicionrio da raiz até o nó vazio
			if(verifica(temp->palavra,ptr1->palavra)>0){		//Chama a função para definir se a palavra no nó temporario recebido vem antes ou depois alfabeticamente da palavra no nó atual do Dicionario
				ptr2=ptr1;										//Guarda o nó atual
				ptr1=ptr1->dir;									//Segue para o nó direita
			}else if(verifica(temp->palavra,ptr1->palavra)<0){	//Chama a função para definir se a palavra no nó temporario recebido vem antes ou depois alfabeticamente da palavra no nó atual do Dicionario
				ptr2=ptr1;										//Guarda o nó atual
				ptr1=ptr1->esq;									//Segue para esquerda
			}else if(verifica(temp->palavra,ptr1->palavra)==0){	//Chama a função para definir se a palavra no nó temporario recebido é igual a palavra no nó atual do Dicionario
				printf("%s", ptr1->palavra);
				flag=1;											//Altera a indicadora para não entrar no proximo condicional
				printf("\nPalavra ja existente");
				break;											//Sai do loop
			}
		}
		if(flag==0 && ptr1==NULL){								//Caso a palavra não esteja no dicionario e tenha chego em um nó vazio
			if(verifica(ptr2->palavra,temp->palavra)==1)		//Chama a função para definir se a palavra no nó temporario recebido vem antes ou depois alfabeticamente da palavra no nó pai do vazio encontrado
				ptr2->esq=temp;									//Guarda o nó temporario a esquerda do ultimo nó não vazio
			else if(verifica(ptr2->palavra,temp->palavra)==-1)	//Chama a função para definir se a palavra no nó temporario recebido vem antes ou depois alfabeticamente da palavra no nó pai do vazio encontrado
				ptr2->dir=temp;									//Guarda o nó temporario a direita do ultimo nó não vazio
		}

    }
    temp=(Dicionario*)malloc(sizeof(Dicionario));				//Aloca um novo nó temporario
    temp->esq=NULL;
    temp->dir=NULL;
}

void exportar_dicionario(Dicionario *ptr1, FILE *f){					//Função para exportar o Dicionario para um arquivo txt
    if(raiz==NULL)														//Verificação dicionário vazio
        printf("\nDicionario Vazio\n");									//Informa dicionario vazio
    else if(ptr1 !=NULL){
        exportar_dicionario(ptr1->esq, f);								//Chega primeiro nos nós mais a esquerda

        fprintf(f,"\n|%s|: %s\n", ptr1->palavra,ptr1->significado);		//Imprime no arquivo

        exportar_dicionario(ptr1->dir,f);								//Segue depois para a direita
    }
}

void ler_dicionario(Dicionario *ptr1){									//Função para realizar a leitura completa do dicionario no programa
  if(raiz==NULL)														//Verificação dicionário vazio
        printf("\nDicionario Vazio\n");									//Informa dicionario vazio
  else if(ptr1 !=NULL){
   ler_dicionario(ptr1->esq);											//Lê primeiro os nós mais a esquerda

   printf("\n|%s|: %s\n",ptr1->palavra,ptr1->significado);				//Imprime na tela

   ler_dicionario(ptr1->dir);											//Segue depois para direita
  }
}

void ler_palavras(Dicionario *ptr1){									//Função para realizar a leitura apenas das palavras do dicionario no programa
  if(raiz==NULL)														//Verificação dicionário vazio
    printf("\nDicionario Vazio\n");										//Informa dicionario vazio
  else if(ptr1 !=NULL){
   ler_palavras(ptr1->esq);												//Lê primeiro os nós mais a esquerda

   printf("\nP:%s\n",ptr1->palavra);									//Imprime na tela

   ler_palavras(ptr1->dir);												//Segue depois para direita
  }
}

void preenche_dic(Dicionario *temp){									//Função para ler o que o usuario quer inserir
    temp=(Dicionario*)malloc(sizeof(Dicionario));						//Aloca nó temporario
    temp->esq=NULL;
    temp->dir=NULL;
    printf("\nInsira a palavra:\n");
    scanf("%s", temp->palavra);											//Insere a palavra digitada no campo palavra do nó temporario
    printf("\nInsira o significado:\n");
    scanf("%s",temp->significado);										//Insere o texto digitado no campo significado do nó temporario
    inserir(temp);														//Insere o nó temporario no dicionario
}

void regras_infos(void){												//Função para indicas regras e informações sobre a utilização do programa
    printf("\n1.Neste Dicionario as palavras estão listadas a esquerda, com sua definição a direita e após dois pontos(':')");
    printf("\n");
    printf("\n2.Para buscar as palavras por favor insira entre aspas, com exceção das que foram inseridas, que devem ser pesquisadas\nexatamente como foram escritas");
    printf("\n");
    printf("\n3.Evite digitar letras nas opções numéricas");
    printf("\n");
    printf("\n4.A base de dados utilizada está no idioma inglês");
    printf("\n");
    printf("\n5.Procure inserir seguindo o padrão do dicionario");
    printf("\n");
    printf("\n6.O Arquivo gerado da exportação será um .txt com nome Dicionario");
	printf("\n");
    printf("\n7.Os termos serão exportados ou impressos em ordem alfabetica");
	printf("\n");
    printf("\n8.O padrão do dicionario foi baseado na base de dados");
    printf("\n");
	printf("\n9.O numero maximo de caracteres de uma palavra/termo ou significado é 3000");
    printf("\n");
	printf("\n8.O padrão do dicionario foi baseado na base de dados");
    printf("\n");
}

void base_dic2(FILE *arq){												//Função que realiza a leitura da Base de Dados
    Dicionario *temp;
    char str1[TAM], str2[TAM], aux[TAM];
    int flag1=0;
    int flag2=0;
    int i=0;
    temp =(Dicionario*)malloc(sizeof(Dicionario));						//Aloca nó temporario
    temp->esq=NULL;
    temp->dir=NULL;
    while (!feof(arq)) {												//Percorre o arquivo de acordo com a constante
        fscanf(arq, "%s", str1);										//Lê a string no arquivo
        if(str1[0]=='"'&& str1[1]>91){									//Busca o cararcter '"' e letras minusculas
            while(str1[strlen(str1)-1]!='"'){							//Percorre até encontrar '"' novamente
                fscanf(arq, "%s", str2);								//Lê a proxima string
                strcat (str1," ");										//Insere um espaço após a anterior
                strcat (str1, str2);									//Junta com a string anterior
            }
            strcpy(temp->palavra,str1);									//Insere a string completa no nó temporario no campo palavra
            flag1=1;													//Indicadora que entrou no loop
        }else if (str1[0]=='"'&&(str1[1]>64 || str1[1]<91) && flag1==1){//Busca o cararcter '"' e letras Maiusculas
            while(str1[strlen(str1)-1]!='"'){							//Percorre até encontrar '"' novamente
                fscanf(arq, "%s", str2);								//Lê a proxima string
                strcat (str1," ");										//Insere um espaço após a anterior
                strcat (str1, str2);									//Junta com a string anterior
            }
            strcpy(temp->significado, str1);							//Insere a string completa no nó temporario no campo significado
            flag2=1;													//Indicadora que entrou nesse loop
        }
        if(flag1==1 && flag2==1){										//Caso tenha entrado em ambos os loops
            inserir(temp);												//Insere o nó temporario no dicionario
            flag1=0;													//Reseta a indicadora
            flag2=0;
            temp =(Dicionario*)malloc(sizeof(Dicionario));				//Aloca novo nó temporario
            temp->esq=NULL;
            temp->dir=NULL;
        }
        i++;
    }
}
