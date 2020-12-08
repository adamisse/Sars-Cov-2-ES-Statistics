#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

//Bruno Menegaz Acerbi - 2020101066
//Matheus Adami Bernardes Moreira - 2020100975

//Cabecario das funcoes
int EntreDatas(int DiaEntrada,int MesEntrada,int DiaSaida,int MesSaida,int DiaCadastro,int MesCadastro);
int MAIORQUEN(int n,int contador);

//Struct para as datas limitantes de entrada
typedef struct{
int dia,mes,ano;
}tDatas;
//Struct para os contadores dos diferentes municipios
typedef struct{
  int contadorVILAVELHA,contadorSERRA,contadorCARIACICA,contadorVITORIA,contadorCDI,contadorLINHARES,contadorSM,contadorGUARAPARI,contadorCOLATINA,contadorARACRUZ,contadorVIANA,contadorNV,contadorBSF,contadorSMJ,contadorMARATAIZES,contadorSGP,contadorCASTELO,contadorITAPEMIRIM,contadorDM,contadorCB,contadorBG,contadorGUACUI,contadorJAGUARE,contadorSOORETAMA,contadorAC,contadorALEGRE,contadorANCHIETA,contadorIUNA,contadorPINHEIROS,contadorIBATIBA,contadorPC,contadorMS,contadorVNI,contadorST,contadorPANCAS,contadorECOPORANGA,contadorPIUMA,contadorFUNDAO,contadorVA,contadorRB,contadorMONTANHA,contadorMF,contadorMFLORIANO,contadorJN,contadorMUQUI,contadorMANTENOPOLIS,contadorBE,contadorITAGUACU,contadorACHAVEZ,contadorVV,contadorICONHA,contadorIRUPI,contadorCC,contadorMARILANDIA,contadorGL,contadorBREJETUBA,contadorIBIRACU,contadorSRC,contadorSL,contadorJM,contadorPK,contadorAV,contadorRNS,contadorADN,contadorLT,contadorITARANA,contadorSJC,contadorBJN,contadorAB,contadorVP,contadorIBITIRAMA,contadorSDN,contadorPB,contadorARN,contadorAPIACA,contadorDRP,contadorMUCURICI,contadorDSL;
}tMunicipios;
//Struct para as variaveis do arquivo .csv
typedef struct{
  int anoCadastro, mesCadastro, diaCadastro, anoObito, mesObito, diaObito, qtdAnoCadastro;
  char dataIdadeCadastro[50], anoIdadeCadastro[50], mesIdadeCadastro[50], diaIdadeCadastro[50], classificacao[50], municipio[50], ComorbidadePulmao[5], ComorbidadeCardio[5], ComorbidadeRenal[5], ComorbidadeDiabetes[5], ComorbidadeTabagismo[5], ComorbidadeObesidade[5], FicouInternado[50];
}tVariaveis;
//Struct para contabilizar os casos entre datas do item 5 e salvar o nome do respectivo municipio
typedef struct{
  char Nome[30];
  int contador;
}tItem5;

//Funcao pra filtrar numeros dentro de uma string XXXX-XX-XX
tDatas FiltrodeDatas(char *data){
tDatas r;
sscanf(data,"%d-%d-%d",&r.ano,&r.mes,&r.dia);
return r;
}

//Funcao para verificar se numero de casos >N
int MAIORQUEN(int n,int contador){
  if(contador>n) return 1;
  return 0;
}

//Funcao p/ verificar se data enta dentro de um intervalo de 2 datas predefinidas
int EntreDatas(int DiaEntrada,int MesEntrada,int DiaSaida,
int MesSaida,int DiaCadastro,int MesCadastro){
if((MesEntrada<MesCadastro || (MesEntrada==MesCadastro && DiaEntrada<=DiaCadastro))&&(MesSaida>MesCadastro || (MesSaida==MesCadastro && DiaSaida>=DiaCadastro))) return 1;
return 0;
}


int main(void) {
  //Declaracao de algumas variaveis
  int n,CasosnoIntervalo=0,TopCidades,i,TotalInternacoes=0,TotalMorteInternado=0,TotalMortes=0,TotalConfirmados=0,TotalMorteSemComorbidadeED=0,TotalMortesED=0;
  //Declaracao das diferentes datas limitantes
  tDatas entrada,saida,entrada2,saida2,entrada3,saida3;
  //Porcentagens dos topicos 6,7 alem das variaveis do calculo da media e do desvio padrao
  float PorCInternados,PorCMorreram,PorCMorreramInternados,PorCMorreramSComorbidade,MediaIdade=0,DP,somatorio=0;
  //Vetor e tamanho do vetor que armazena a idade dos mortos ultilizada na parte 7
  int TAM=0;
  int VetorIdade[2701];
  //Declaracao das variaveis do arquivo de entrada
  tVariaveis c; 
  //Declaracao dos contadores de cada municipios para as diferentes aplicacoes
  tMunicipios Total={0},Internacao={0},Morte={0},MorteInternado={0};
  //Vetor ultilizado para salvar os dados e modular o item 5
  tItem5 V[78];
  for(i=0;i<78;i++)
    V[i].contador=0;
  //Vetor onde sera armazenado todas as linhas do .csv
  char linhas[202363],*token;
  //Um contador que sera usado no item 5
  int ContadorMuniED[78];
    for(i=0;i<78;i++)
      ContadorMuniED[i]=0;
  //Variaveis de entrada
  char NomePasta[20];
  char DataEntrada[12];
  char DataSaida[12];
  char DataEntrada2[12];
  char DataSaida2[12];
  char MunicipiosAnalisados[30];
  char DataEntrada3[12];
  char DataSaida3[12];
  char quebra;
  //Captura das diferentes entradas
  scanf("%s",&*NomePasta);
  scanf("%d",&n);
  scanf("%s",&*DataEntrada);
  scanf("%s",&*DataSaida);
  scanf("%d",&TopCidades);
  scanf("%s",&*DataEntrada2); 
  scanf("%s",&*DataSaida2);
  scanf("%c",&quebra);// captura da quebra da linha 
  scanf("%[^\n]",&*MunicipiosAnalisados);
  scanf("%s",&*DataEntrada3);
  scanf("%s",&*DataSaida3); 
  //Conversao da String MunicipiosAnalisados em MAISCULO 
  for(i=0;i<30;i++)
    MunicipiosAnalisados[i]=toupper(MunicipiosAnalisados[i]);

  //Strings das Datas sendo separadas pela funcao FiltrodeDatas
  entrada=(FiltrodeDatas(DataEntrada));
  saida=(FiltrodeDatas(DataSaida));
  entrada2=(FiltrodeDatas(DataEntrada2));
  saida2=(FiltrodeDatas(DataSaida2));
  entrada3=(FiltrodeDatas(DataEntrada3));
  saida3=(FiltrodeDatas(DataSaida3));

  //Abertura do arquivo .csv 
  FILE *arq;
  arq=fopen("covid19ES.csv","r"); 
  //Criacao do diretorio para onde as saidas.txt serao encaminhadas
  char Comand[20];
  strcpy(Comand,"mkdir \\");
  strcat(Comand,NomePasta);
  system(Comand);
  
  //Criacao das saidas.txt com as respostas de cada topico pedido dentro da pasta
  char *item3="item3.txt",*item4="item4.txt", *item5="item5.txt", *item6="item6.txt", *item7="item7.txt";
  char auxiliar[20];
  strcpy(auxiliar,NomePasta);

  FILE *Resp3 = fopen(strcat(auxiliar,item3),"wt");
  strcpy(auxiliar,NomePasta);
  FILE *saida4 = fopen(strcat(auxiliar,item4),"wt"); 
  strcpy(auxiliar,NomePasta);
  FILE *saida5 = fopen(strcat(auxiliar,item5),"wt");
  strcpy(auxiliar,NomePasta);
  FILE *saida6 = fopen(strcat(auxiliar,item6),"wt");
  strcpy(auxiliar,NomePasta);
  FILE *saida7 = fopen(strcat(auxiliar,item7),"wt");

  //Verificacao das Aberturas
  if(arq==NULL){
    printf("Erro na abertura do arquivo .csv");
    exit(1);
  }
  if(saida4==NULL || Resp3==NULL || saida7==NULL || saida6==NULL || saida5==NULL){
    printf("Erro na abertura das entradas");
    exit(1);
  }

  //Atribuicao das linhas do arquivo .csv em vetores
  for(i=0;i<202363;i++){
      //Funcao para ler as linhas arquivo;
      fgets(linhas, 1000, arq);
    
      token = strtok(linhas, ",");
      //Descarte da Primeira Linha
      if(strcmp(token,"DataCadastro")!=0){
      //Separação da string dataCadastro p/ três inteiros;
      sscanf(token, "%d-%d-%d", &c.anoCadastro, &c.mesCadastro, &c.diaCadastro);

      //Separação da string dataÓbito p/ três inteiros;
      token = strtok(NULL, ",");
      sscanf(token, "%d-%d-%d", &c.anoObito, &c.mesObito, &c.diaObito);
      
      //Atribuindo Classificacao em uma variavel manipulavel;
      token = strtok(NULL, ",");
      strcpy(c.classificacao,token);
      
      //Atribuindo Municipio a uma variavel manipulavel;
      token = strtok(NULL, ",");
      strcpy(c.municipio,token);
      
      //Separação da string idadeCadastro
      //Ano
      token = strtok(NULL,","); 
      sscanf(token, "\"%d anos", &c.qtdAnoCadastro);
      token=strtok(NULL,"\"");

      //Atribuindo Corbidade de Pulmao em uma variavel manipulavel;
      token = strtok(NULL, ",");
      strcpy(c.ComorbidadePulmao,token);
    
      //Atribuindo Comorbidade Cardio em uma variavel manipulavel;
      token = strtok(NULL,",");
      strcpy(c.ComorbidadeCardio,token);

      //Atribuindo Comorbidade Renal em uma variavel manipulavel;
      token = strtok(NULL, ",");
      strcpy(c.ComorbidadeRenal,token);

      //Atribuindo Comorbidade Diabetica em uma variavel manipulavel;
      token= strtok(NULL,",");
      strcpy(c.ComorbidadeDiabetes,token);

      //Atribuindo Comorbidade Tabagista em uma variavel manipulavel;
      token= strtok(NULL,",");
      strcpy(c.ComorbidadeTabagismo,token);

      //Atribuindo Comorbidade de Obesidade em uma variavel manipulavel;
      token = strtok(NULL, ",");
      strcpy(c.ComorbidadeObesidade,token);

      //Atribuindo estado de internacao em uma variavel manipulavel;
      token = strtok(NULL, ",");
      strcpy(c.FicouInternado,token);
      
  //PARTE 3 e 6
  if(strcmp(c.classificacao,"Confirmados")==0){
    //Calcula o Total de Internacoes,Mortes e Internacoes com mortes confirmados de COVID19
    TotalConfirmados++;
    if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        TotalMortes++;
      }
    if(strcmp(c.FicouInternado, "Sim\n")==0){
        TotalInternacoes++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0)
          TotalMorteInternado++;
      }

    //Calcula o numero de Internacoes,Mortes e Internacoes com mortes por municipio
    if(strcmp(c.municipio, "VILA VELHA")==0){
      Total.contadorVILAVELHA++;
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorVILAVELHA++;
      }
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorVILAVELHA++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorVILAVELHA++;
        }
      }
    }
    if(strcmp(c.municipio, "SERRA")==0){ 
      Total.contadorSERRA++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorSERRA++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorSERRA++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorSERRA++;
      }
    }
    if(strcmp(c.municipio, "CARIACICA")==0){
      Total.contadorCARIACICA++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorCARIACICA++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorCARIACICA++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorCARIACICA++;
      }
    }
    if(strcmp(c.municipio, "VITORIA")==0){
      Total.contadorVITORIA++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorVITORIA++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorVITORIA++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorVITORIA++;
      }
    }
    if(strcmp(c.municipio, "CACHOEIRO DE ITAPEMIRIM")==0){
      Total.contadorCDI++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorCDI++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorCDI++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorCDI++;
      }
    }
    if(strcmp(c.municipio, "LINHARES")==0){
      Total.contadorLINHARES++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorLINHARES++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorLINHARES++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorLINHARES++;
      }
    }
    if(strcmp(c.municipio, "SAO MATEUS")==0){
      Total.contadorSM++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorSM++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorSM++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorSM++;
      }
    }
    if(strcmp(c.municipio, "GUARAPARI")==0){
      Total.contadorGUARAPARI++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorGUARAPARI++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorGUARAPARI++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorGUARAPARI++;
      }
    }
    if(strcmp(c.municipio, "COLATINA")==0){
      Total.contadorCOLATINA++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorCOLATINA++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorCOLATINA++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorCOLATINA++;
      }
    }
    if(strcmp(c.municipio, "ARACRUZ")==0){
      Total.contadorARACRUZ++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorARACRUZ++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorARACRUZ++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorARACRUZ++;
      }
    }
    if(strcmp(c.municipio, "VIANA")==0){
      Total.contadorVIANA++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorVIANA++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorVIANA++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorVIANA++;
      }
    }
    if(strcmp(c.municipio, "NOVA VENECIA")==0){
      Total.contadorNV++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorNV++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorNV++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorNV++;
      }
    }
    if(strcmp(c.municipio, "BARRA DE SAO FRANCISCO")==0){
      Total.contadorBSF++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorBSF++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorBSF++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorBSF++;
      }
    }
    if(strcmp(c.municipio, "SANTA MARIA DE JETIBA")==0){
      Total.contadorSMJ++;
    if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorSMJ++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorSMJ++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorSMJ++;
      }
    }
    if(strcmp(c.municipio, "MARATAIZES")==0){
      Total.contadorMARATAIZES++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorMARATAIZES++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorMARATAIZES++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorMARATAIZES++;
      }
    }
    if(strcmp(c.municipio, "SAO GABRIEL DA PALHA")==0){
      Total.contadorSGP++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorSGP++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorSGP++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorSGP++;
      }
    }
    if(strcmp(c.municipio, "CASTELO")==0){
      Total.contadorCASTELO++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorCASTELO++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorCASTELO++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorCASTELO++;
      }
    }
    if(strcmp(c.municipio, "ITAPEMIRIM")==0){
      Total.contadorITAPEMIRIM++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorITAPEMIRIM++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorITAPEMIRIM++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorITAPEMIRIM++;
      }
    }
    if(strcmp(c.municipio, "DOMINGOS MARTINS")==0){
      Total.contadorDM++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorDM++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorDM++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorDM++;
      }
    }
    if(strcmp(c.municipio, "CONCEICAO DA BARRA")==0){
      Total.contadorCB++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorCB++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorCB++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorCB++;
      }
    }
    if(strcmp(c.municipio, "BAIXO GUANDU")==0){
      Total.contadorBG++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorBG++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorBG++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorBG++;
      }
    }
    if(strcmp(c.municipio, "GUACUI")==0){
      Total.contadorGUACUI++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorGUACUI++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorGUACUI++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorGUACUI++;
      }
    }
    if(strcmp(c.municipio, "JAGUARE")==0){
      Total.contadorJAGUARE++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorJAGUARE++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorJAGUARE++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorJAGUARE++;
      }
    }
    if(strcmp(c.municipio, "SOORETAMA")==0){
      Total.contadorSOORETAMA++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorSOORETAMA++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorSOORETAMA++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorSOORETAMA++;
      }
    }
    if(strcmp(c.municipio, "AFONSO CLAUDIO")==0){
      Total.contadorAC++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorAC++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorAC++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorAC++;
      }
    }
    if(strcmp(c.municipio, "ALEGRE")==0){
      Total.contadorALEGRE++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorALEGRE++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorALEGRE++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorALEGRE++;
      }
    }
    if(strcmp(c.municipio, "ANCHIETA")==0){
      Total.contadorANCHIETA++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorANCHIETA++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorANCHIETA++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorANCHIETA++;
      }
    }
    if(strcmp(c.municipio, "IUNA")==0){
      Total.contadorIUNA++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorIUNA++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorIUNA++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorIUNA++;
      }
    }
    if(strcmp(c.municipio, "PINHEIROS")==0){
      Total.contadorPINHEIROS++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorPINHEIROS++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorPINHEIROS++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorPINHEIROS++;
      }
    }
    if(strcmp(c.municipio, "IBATIBA")==0){
      Total.contadorIBATIBA++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorIBATIBA++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorIBATIBA++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorIBATIBA++;
      }
    }
    if(strcmp(c.municipio, "PEDRO CANARIO")==0){
      Total.contadorPC++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorPC++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorPC++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorPC++;
      }
    }
    if(strcmp(c.municipio, "MIMOSO DO SUL")==0){
      Total.contadorMS++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorMS++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorMS++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorMS++;
      }
    }
    if(strcmp(c.municipio, "VENDA NOVA DO IMIGRANTE")==0){
      Total.contadorVNI++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorVNI++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorVNI++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorVNI++;
      }
    }
    if(strcmp(c.municipio, "SANTA TERESA")==0){
      Total.contadorST++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorST++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorST++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorST++;
      }
    }
    if(strcmp(c.municipio, "PANCAS")==0){
      Total.contadorPANCAS++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorPANCAS++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorPANCAS++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorPANCAS++;
      }
    }
    if(strcmp(c.municipio, "ECOPORANGA")==0){
      Total.contadorECOPORANGA++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorECOPORANGA++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorECOPORANGA++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorECOPORANGA++;
      }
    }
    if(strcmp(c.municipio, "PIUMA")==0){
      Total.contadorPIUMA++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorPIUMA++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorPIUMA++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorPIUMA++;
      }
    }
    if(strcmp(c.municipio, "FUNDAO")==0){
      Total.contadorFUNDAO++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorFUNDAO++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorFUNDAO++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorFUNDAO++;
      }
    }
    if(strcmp(c.municipio, "VARGEM ALTA")==0){
      Total.contadorVA++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorVA++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorVA++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorVA++;
      }
    }
    if(strcmp(c.municipio, "RIO BANANAL")==0){
      Total.contadorRB++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorRB++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorRB++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorRB++;
      }
    }
    if(strcmp(c.municipio, "MONTANHA")==0){
      Total.contadorMONTANHA++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorMONTANHA++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorMONTANHA++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorMONTANHA++;
      }
    }
    if(strcmp(c.municipio, "MUNIZ FREIRE")==0){
      Total.contadorMF++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorMF++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorMF++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorMF++;
      }
    }
    if(strcmp(c.municipio, "MARECHAL FLORIANO")==0){
      Total.contadorMFLORIANO++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorMFLORIANO++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorMFLORIANO++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorMFLORIANO++;
      }
    }
    if(strcmp(c.municipio, "JOAO NEIVA")==0){
      Total.contadorJN++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorJN++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorJN++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorJN++;
      }
    }
    if(strcmp(c.municipio, "MUQUI")==0){
      Total.contadorMUQUI++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorMUQUI++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorMUQUI++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorMUQUI++;
      }
    }
    if(strcmp(c.municipio, "MANTENOPOLIS")==0){
      Total.contadorMANTENOPOLIS++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorMANTENOPOLIS++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorMANTENOPOLIS++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorMANTENOPOLIS++;
      }
    }
    if(strcmp(c.municipio, "BOA ESPERANCA")==0){
      Total.contadorBE++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorBE++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorBE++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorBE++;
      }
    }
    if(strcmp(c.municipio, "ITAGUACU")==0){
      Total.contadorITAGUACU++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorITAGUACU++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorITAGUACU++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorITAGUACU++;
      }
    }
    if(strcmp(c.municipio, "ALFREDO CHAVES")==0){
      Total.contadorACHAVEZ++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorACHAVEZ++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorACHAVEZ++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorACHAVEZ++;
      }
    }
    if(strcmp(c.municipio, "VILA VALERIO")==0){
      Total.contadorVV++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorVV++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorVV++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorVV++;
      }
    }
    if(strcmp(c.municipio, "ICONHA")==0){
      Total.contadorICONHA++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorICONHA++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorICONHA++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorICONHA++;
      }
    }
    if(strcmp(c.municipio, "IRUPI")==0){
      Total.contadorIRUPI++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorIRUPI++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorIRUPI++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorIRUPI++;
      }
    }
    if(strcmp(c.municipio, "CONCEICAO DO CASTELO")==0){
      Total.contadorCC++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorCC++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorCC++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorCC++;
      }
    }
    if(strcmp(c.municipio, "MARILANDIA")==0){
      Total.contadorMARILANDIA++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorMARILANDIA++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorMARILANDIA++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorMARILANDIA++;
      }
    }
    if(strcmp(c.municipio, "GOVERNADOR LINDENBERG")==0){
      Total.contadorGL++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorGL++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorGL++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorGL++;
      }
    }
    if(strcmp(c.municipio, "BREJETUBA")==0){
      Total.contadorBREJETUBA++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorBREJETUBA++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorBREJETUBA++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorBREJETUBA++;
      }
    }
    if(strcmp(c.municipio, "IBIRACU")==0){
      Total.contadorIBIRACU++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorIBIRACU++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorIBIRACU++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorIBIRACU++;
      }
    }
    if(strcmp(c.municipio, "SAO ROQUE DO CANAA")==0){
      Total.contadorSRC++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorSRC++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorSRC++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorSRC++;
      }
    }
    if(strcmp(c.municipio, "SANTA LEOPOLDINA")==0){
      Total.contadorSL++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorSL++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorSL++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorSL++;
      }
    }
    if(strcmp(c.municipio, "JERONIMO MONTEIRO")==0){
      Total.contadorJM++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorJM++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorJM++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorJM++;
      }
    }
    if(strcmp(c.municipio, "PRESIDENTE KENNEDY")==0){
      Total.contadorPK++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorPK++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorPK++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorPK++;
      }
    }
    if(strcmp(c.municipio, "ATILIO VIVACQUA")==0){
      Total.contadorAV++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorAV++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorAV++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorAV++;
      }
    }
    if(strcmp(c.municipio, "RIO NOVO DO SUL")==0){
      Total.contadorRNS++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorRNS++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorRNS++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorRNS++;
      }
    }
    if(strcmp(c.municipio, "AGUA DOCE DO NORTE")==0){
      Total.contadorADN++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorADN++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorADN++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorADN++;
      }
    }
    if(strcmp(c.municipio, "LARANJA DA TERRA")==0){
      Total.contadorLT++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorLT++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorLT++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorLT++;
      }
    }
    if(strcmp(c.municipio, "ITARANA")==0){
      Total.contadorITARANA++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorITARANA++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorITARANA++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorITARANA++;
      }
    }
    if(strcmp(c.municipio, "SAO JOSE DO CALCADO")==0){
      Total.contadorSJC++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorSJC++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorSJC++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorSJC++;
      }
    }
    if(strcmp(c.municipio, "BOM JESUS DO NORTE")==0){
      Total.contadorBJN++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorBJN++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorBJN++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorBJN++;
      }
    }
    if(strcmp(c.municipio, "AGUIA BRANCA")==0){
      Total.contadorAB++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorAB++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorAB++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorAB++;
      }
    }
    if(strcmp(c.municipio, "VILA PAVAO")==0){
      Total.contadorVP++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorVP++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorVP++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorVP++;
      }
    }
    if(strcmp(c.municipio, "IBITIRAMA")==0){
      Total.contadorIBITIRAMA++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorIBITIRAMA++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorIBITIRAMA++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorIBITIRAMA++;
      }
    }
    if(strcmp(c.municipio, "SAO DOMINGOS DO NORTE")==0){
      Total.contadorSDN++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorSDN++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorSDN++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorSDN++;
      }
    }
    if(strcmp(c.municipio, "PORTO BELO")==0){
      Total.contadorPB++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorPB++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorPB++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorPB++;
      }
    }
    if(strcmp(c.municipio, "ALTO RIO NOVO")==0){
      Total.contadorARN++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorARN++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorARN++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorARN++;
      }
    }
    if(strcmp(c.municipio, "APIACA")==0){
      Total.contadorAPIACA++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorAPIACA++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorAPIACA++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorAPIACA++;
      }
    }
    if(strcmp(c.municipio, "DORES DO RIO PRETO")==0){
      Total.contadorDRP++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorDRP++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorDRP++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorDRP++;
      }
    }
    if(strcmp(c.municipio, "MUCURICI")==0){
      Total.contadorMUCURICI++;
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorMUCURICI++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorMUCURICI++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorMUCURICI++;
      }
    }
    if(strcmp(c.municipio, "DIVINO DE SAO LOURENCO")==0){
      Total.contadorDSL++; 
      if(strcmp(c.FicouInternado,"Sim\n")==0){
        Internacao.contadorDSL++;
        if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
          MorteInternado.contadorDSL++;
        }
      }
      if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
        Morte.contadorDSL++;
      }
    }
  }
  //PARTE 4
  //Chama a funcao EntreDatas para verificar se a data no vetor esta entre as limitantes
  if(EntreDatas(entrada.dia,entrada.mes,saida.dia,saida.mes,c.diaCadastro,c.mesCadastro)==1){
    if(strcmp(c.classificacao,"Confirmados")==0)
      CasosnoIntervalo++;
  }
  //PARTE 5
  //Verifica se a data do vetor esta entre as datas de limitacao e contabiliza os casos "Confirmados" para cada municipio e salva a string com o nome da cidade dentro de um vetor
  if(EntreDatas(entrada2.dia,entrada2.mes,saida2.dia,saida2.mes,c.diaCadastro,c.mesCadastro)==1){
    if(strcmp(c.classificacao,"Confirmados")==0){
        if(strcmp(c.municipio, "VILA VELHA")==0){
           strcpy(V[0].Nome,"VILA VELHA");
          V[0].contador++;
        }
        if(strcmp(c.municipio, "SERRA")==0){
          strcpy(V[1].Nome,"SERRA");
          V[1].contador++;
        }
        if(strcmp(c.municipio, "CARIACICA")==0){
          strcpy(V[2].Nome,"CARIACICA");
          V[2].contador++;
        }
        if(strcmp(c.municipio, "VITORIA")==0){
          strcpy(V[3].Nome,"VITORIA");
          V[3].contador++;
        }
        if(strcmp(c.municipio, "CACHOEIRO DE ITAPEMIRIM")==0){
          strcpy(V[4].Nome,"CACHOEIRO DE ITAPEMIRIM");
          V[4].contador++;
        }
        if(strcmp(c.municipio, "LINHARES")==0){
          strcpy(V[5].Nome,"LINHARES");
          V[5].contador++;
        }
        if(strcmp(c.municipio, "SAO MATEUS")==0){
          strcpy(V[6].Nome,"SAO MATEUS");
          V[6].contador++;
        }
        if(strcmp(c.municipio, "GUARAPARI")==0){
          strcpy(V[7].Nome,"GUARAPARI");
          V[7].contador++;
        }
        if(strcmp(c.municipio, "COLATINA")==0){
          strcpy(V[8].Nome,"COLATINA");
          V[8].contador++;
        }
        if(strcmp(c.municipio, "ARACRUZ")==0){
          strcpy(V[9].Nome,"ARACRUZ");
          V[9].contador++;
        }
        if(strcmp(c.municipio, "VIANA")==0){
          strcpy(V[10].Nome,"VIANA");
          V[10].contador++;
        }
        if(strcmp(c.municipio, "NOVA VENECIA")==0){
          strcpy(V[11].Nome,"NOVA VENECIA");
          V[11].contador++;
        }
        if(strcmp(c.municipio, "BARRA DE SAO FRANCISCO")==0){
          strcpy(V[12].Nome,"BARRA DE SAO FRANCISCO");
          V[12].contador++;
        }
        if(strcmp(c.municipio, "SANTA MARIA DE JETIBA")==0){
          strcpy(V[13].Nome,"SANTA MARIA DE JETIBA");
          V[13].contador++;
        }
        if(strcmp(c.municipio, "MARATAIZES")==0){
          strcpy(V[14].Nome,"MARATAIZES");
          V[14].contador++;
        }
        if(strcmp(c.municipio, "SAO GABRIEL DA PALHA")==0){
          strcpy(V[15].Nome,"SAO GABRIEL DA PALHA");
          V[15].contador++;
        }
        if(strcmp(c.municipio, "CASTELO")==0){
          strcpy(V[16].Nome,"CASTELO");
          V[16].contador++;
        }
        if(strcmp(c.municipio, "ITAPEMIRIM")==0){
          strcpy(V[17].Nome,"ITAPEMIRIM");
          V[17].contador++;
        }
        if(strcmp(c.municipio, "DOMINGOS MARTINS")==0){
          strcpy(V[18].Nome,"DOMINGOS MARTIN");
          V[18].contador++;
        }
        if(strcmp(c.municipio, "CONCEICAO DA BARRA")==0){
          strcpy(V[19].Nome,"CONCEICAO DA BARRA");
          V[19].contador++;
        }
        if(strcmp(c.municipio, "BAIXO GUANDU")==0){
          strcpy(V[20].Nome,"BAIXO GUANDU");
          V[20].contador++;
        }
        if(strcmp(c.municipio, "GUACUI")==0){
          strcpy(V[21].Nome,"GUACUI");
          V[21].contador++;
        }
        if(strcmp(c.municipio, "JAGUARE")==0){
          strcpy(V[22].Nome,"JAGUARE");
          V[22].contador++;
        }
        if(strcmp(c.municipio, "SOORETAMA")==0){
          strcpy(V[23].Nome,"SOORETAMA");
          V[23].contador++;
        }
        if(strcmp(c.municipio, "AFONSO CLAUDIO")==0){
          strcpy(V[24].Nome,"AFONSO CLAUDIO");
          V[24].contador++;
        }
        if(strcmp(c.municipio, "ALEGRE")==0){
          strcpy(V[25].Nome,"ALEGRE");
          V[25].contador++;
        }
        if(strcmp(c.municipio, "ANCHIETA")==0){
          strcpy(V[26].Nome,"ANCHIETA");
          V[26].contador++;
        }
        if(strcmp(c.municipio, "IUNA")==0){
          strcpy(V[27].Nome,"IUNA");
          V[27].contador++;
        }
        if(strcmp(c.municipio, "PINHEIROS")==0){
          strcpy(V[28].Nome,"PINHEIROS");
          V[28].contador++;
        }
        if(strcmp(c.municipio, "IBATIBA")==0){
          strcpy(V[29].Nome,"IBATIBA");
          V[29].contador++;
        }
        if(strcmp(c.municipio, "PEDRO CANARIO")==0){
          strcpy(V[30].Nome,"PEDRO CANARIO");
          V[30].contador++;
        }
        if(strcmp(c.municipio, "MIMOSO DO SUL")==0){
          strcpy(V[31].Nome,"MIMOSO DO SUL");
          V[31].contador++;
        }
        if(strcmp(c.municipio, "VENDA NOVA DO IMIGRANTE")==0){
          strcpy(V[32].Nome,"VENDA NOVA DO IMIGRANTE");
          V[32].contador++;
        }
        if(strcmp(c.municipio, "SANTA TERESA")==0){
          strcpy(V[33].Nome,"SANTA TERESA");
          V[33].contador++;
        }
        if(strcmp(c.municipio, "PANCAS")==0){
          strcpy(V[34].Nome,"PANCAS");
          V[34].contador++;
        }
        if(strcmp(c.municipio, "ECOPORANGA")==0){
          strcpy(V[35].Nome,"ECOPORANGA");
          V[35].contador++;
        }
        if(strcmp(c.municipio, "PIUMA")==0){
          strcpy(V[36].Nome,"PIUMA");
          V[36].contador++;
        }
        if(strcmp(c.municipio, "FUNDAO")==0){
          strcpy(V[37].Nome,"FUNDAO");
          V[37].contador++;
        }
        if(strcmp(c.municipio, "VARGEM ALTA")==0){
          strcpy(V[38].Nome,"VARGEM ALTA");
          V[38].contador++;
        }
        if(strcmp(c.municipio, "RIO BANANAL")==0){
          strcpy(V[39].Nome,"RIO BANANAL");
          V[39].contador++;
        }
        if(strcmp(c.municipio, "MONTANHA")==0){
          strcpy(V[40].Nome,"MONTANHA");
          V[40].contador++;
        }
        if(strcmp(c.municipio, "MUNIZ FREIRE")==0){
          strcpy(V[41].Nome,"MUNIZ FREIRE");
          V[41].contador++;
        }
        if(strcmp(c.municipio, "MARECHAL FLORIANO")==0){
          strcpy(V[42].Nome,"MARECHAL FLORIANO");
          V[42].contador++;
        }
        if(strcmp(c.municipio, "JOAO NEIVA")==0){
          strcpy(V[43].Nome,"JOAO NEIVA");
          V[43].contador++;
        }
        if(strcmp(c.municipio, "MUQUI")==0){
          strcpy(V[44].Nome,"MUQUI");
          V[44].contador++;
        }
        if(strcmp(c.municipio, "MANTENOPOLIS")==0){
          strcpy(V[45].Nome,"MANTENOPOLIS");
          V[45].contador++;
        }
        if(strcmp(c.municipio, "BOA ESPERANCA")==0){
          strcpy(V[45].Nome,"BOA ESPERANCA");
          V[45].contador++;
        }
        if(strcmp(c.municipio, "ITAGUACU")==0){
          strcpy(V[46].Nome,"ITAGUACU");
          V[46].contador++;
        }
        if(strcmp(c.municipio, "ALFREDO CHAVES")==0){
          strcpy(V[47].Nome,"ALFREDO CHAVES");
          V[47].contador++;
        }
        if(strcmp(c.municipio, "VILA VALEIRO")==0){
          strcpy(V[48].Nome,"VILA VALEIRO");
          V[48].contador++;
        }
        if(strcmp(c.municipio, "ICONHA")==0){
          strcpy(V[49].Nome,"ICONHA");
          V[49].contador++;
        }
        if(strcmp(c.municipio, "IRUPI")==0){
          strcpy(V[50].Nome,"IRUPI");
          V[50].contador++;
        }
        if(strcmp(c.municipio, "CONCEICAO DO CASTELO")==0){
          strcpy(V[51].Nome,"CONCEICAO DO CASTELO");
          V[51].contador++;
        }
        if(strcmp(c.municipio, "MARILANDIA")==0){
          strcpy(V[52].Nome,"MARILANDIA");
          V[52].contador++;
        }
        if(strcmp(c.municipio, "GOVERNADOR LINDENBERG")==0){
          strcpy(V[53].Nome,"GOVERNADOR LINDENBERG");
          V[53].contador++;
        }
        if(strcmp(c.municipio, "BREJETUBA")==0){
          strcpy(V[54].Nome,"BREJETUBA");
          V[54].contador++;
        }
        if(strcmp(c.municipio, "IBIRACU")==0){
          strcpy(V[56].Nome,"IBIRACU");
          V[56].contador++;
        }
        if(strcmp(c.municipio, "SAO ROQUE DO CANAA")==0){
          strcpy(V[57].Nome,"SAO ROQUE DO CANAA");
          V[57].contador++;
        }
        if(strcmp(c.municipio, "SANTA LEOPOLDINA")==0){
          strcpy(V[58].Nome,"SANTA LEOPOLDINA");
          V[58].contador++;
        }
        if(strcmp(c.municipio, "JERONIMO MONTEIRO")==0){
          strcpy(V[59].Nome,"JERONIMO MONTEIRO");
          V[59].contador++;
        }
        if(strcmp(c.municipio, "PRESIDENTE KENNEDY")==0){
          strcpy(V[60].Nome,"PRESIDENTE KENNEDY");
          V[60].contador++;
        }
        if(strcmp(c.municipio, "ATILIO VIVACQUA")==0){
          strcpy(V[61].Nome,"ATILIO VIVACQUIA");
          V[61].contador++;
        }
        if(strcmp(c.municipio, "RIO NOVO DO SUL")==0){
          strcpy(V[62].Nome,"RIO NOVO DO SUL");
          V[62].contador++;
        }
        if(strcmp(c.municipio, "AGUA DOCE DO NORTE")==0){
          strcpy(V[63].Nome,"AGUA DOCE DO NORTE");
          V[63].contador++;
        }
        if(strcmp(c.municipio, "LARANJA DA TERRA")==0){
          strcpy(V[64].Nome,"LARANJA DA TERRA");
          V[64].contador++;
        }
        if(strcmp(c.municipio, "ITARANA")==0){
          strcpy(V[65].Nome,"ITARANA");
          V[65].contador++;
        }
        if(strcmp(c.municipio, "SAO JOSE DO CALCADO")==0){
          strcpy(V[66].Nome,"SAO JOSE DO CALCADO");
          V[66].contador++;
        }
        if(strcmp(c.municipio, "BOM JESUS DO NORTE")==0){
          strcpy(V[67].Nome,"BOM JESUS DO NORTE");
          V[67].contador++;
        }
        if(strcmp(c.municipio, "AGUIA BRANCA")==0){
          strcpy(V[68].Nome,"AGUIA BRANCA");
          V[68].contador++;
        }
        if(strcmp(c.municipio, "VILA PAVAO")==0){
          strcpy(V[69].Nome,"VILA PAVAO");
          V[69].contador++;
        }
        if(strcmp(c.municipio, "IBITIRAMA")==0){
          strcpy(V[70].Nome,"IBITIRAMA");
          V[70].contador++;
        }
        if(strcmp(c.municipio, "SAO DOMINGOS DO NORTE")==0){
          strcpy(V[71].Nome,"SAO DOMINGOS DO NORTE");
          V[71].contador++;
        }
        if(strcmp(c.municipio, "PORTO BELO")==0){
          strcpy(V[72].Nome,"PORTO BELO");
          V[72].contador++;
        }
        if(strcmp(c.municipio, "ALTO RIO NOVO")==0){
          strcpy(V[73].Nome,"ALTO RIO NOVO");
          V[73].contador++;
        }
        if(strcmp(c.municipio, "APIACA")==0){
          strcpy(V[74].Nome,"APIACA");
          V[74].contador++;
        }
        if(strcmp(c.municipio, "DORES DO RIO PRETO")==0){
          strcpy(V[75].Nome,"DORES DO RIO PRETO");
          V[75].contador++;
        }
        if(strcmp(c.municipio, "MUCURICI")==0){
          strcpy(V[76].Nome,"MUCURICI");
          V[76].contador++;
        }
        if(strcmp(c.municipio, "DIVINO DE SAO LOURENCO")==0){
          strcpy(V[77].Nome,"DIVINO DE SAO LOURENCO");
          V[77].contador++;
        } 
      }
    }
  //Parte 7  
  //Contabiliza o total de mortes e mortes sem comorbidade de COVID-19 dentro do intervalo de datas fornecido alem de armazenar a idade das pessoas que morreram em um vetor VetorIdade
      if(EntreDatas(entrada3.dia,entrada3.mes,saida3.dia,saida3.mes,c.diaCadastro,c.mesCadastro)==1){
        if(strcmp(c.classificacao,"Confirmados")==0){
          if(c.anoObito!=0 || c.mesObito!=0 || c.diaObito!=0){
            TotalMortesED++;
            VetorIdade[TAM]=c.qtdAnoCadastro;
            TAM++;
            MediaIdade+=c.qtdAnoCadastro;
            if((strcmp(c.ComorbidadeRenal, "Sim")!=0) && (strcmp(c.ComorbidadeCardio, "Sim")!=0) && (strcmp(c.ComorbidadePulmao, "Sim")!=0) && (strcmp(c.ComorbidadeDiabetes, "Sim")!=0) && (strcmp(c.ComorbidadeObesidade, "Sim")!=0) && (strcmp(c.ComorbidadeTabagismo, "Sim")!=0))
              TotalMorteSemComorbidadeED++;
          }
        }
      }
    }
  } 
  //PRINT DA PARTE 3
  //Chama a funcao 'MAIORQUEN' que verifica se o contador de cada cidade ultrapassa o limitante 'N' fornecido na entrada, caso sim, printa sua respectiva cidade
  if(MAIORQUEN(n,Total.contadorAC)==1)
    fprintf(Resp3,"- AFONSO CLAUDIO: %d casos\n",Total.contadorAC);
  if(MAIORQUEN(n,Total.contadorADN)==1)
    fprintf(Resp3,"- AGUA DOCE DO NORTE: %d casos\n",Total.contadorADN);
  if(MAIORQUEN(n,Total.contadorAB)==1)
    fprintf(Resp3,"- AGUIA BRANCA: %d casos\n",Total.contadorAB);
  if(MAIORQUEN(n,Total.contadorALEGRE)==1)
    fprintf(Resp3,"- ALEGRE: %d casos\n",Total.contadorALEGRE);
  if(MAIORQUEN(n,Total.contadorACHAVEZ)==1)
    fprintf(Resp3,"- ALFREDO CHAVES: %d casos\n",Total.contadorACHAVEZ);
  if(MAIORQUEN(n,Total.contadorACHAVEZ)==1)
    fprintf(Resp3,"- ALTO RIO NOVO: %d casos\n",Total.contadorARN);
  if(MAIORQUEN(n,Total.contadorANCHIETA)==1)
    fprintf(Resp3,"- ANCHIETA: %d casos\n",Total.contadorANCHIETA);
  if(MAIORQUEN(n,Total.contadorAPIACA)==1)
    fprintf(Resp3,"- APIACA: %d casos\n",Total.contadorAPIACA);
  if(MAIORQUEN(n,Total.contadorARACRUZ)==1)
    fprintf(Resp3,"- ARACRUZ: %d casos\n",Total.contadorARACRUZ);
  if(MAIORQUEN(n,Total.contadorAV)==1)
    fprintf(Resp3,"- ATILIO VIVACQUA: %d casos\n",Total.contadorAV);
  if(MAIORQUEN(n,Total.contadorBG)==1)
    fprintf(Resp3,"- BAIXO GUANDU: %d casos\n",Total.contadorBG);  
  if(MAIORQUEN(n,Total.contadorBSF)==1)
    fprintf(Resp3,"- BARRA DE SAO FRANCISCO: %d casos\n",Total.contadorBSF);
  if(MAIORQUEN(n,Total.contadorBE)==1)
    fprintf(Resp3,"- BOA ESPERANCA: %d casos\n",Total.contadorBE); 
  if(MAIORQUEN(n,Total.contadorBJN)==1)
    fprintf(Resp3,"- BOM JESUS DO NORTE: %d casos\n",Total.contadorBJN);
  if(MAIORQUEN(n,Total.contadorBREJETUBA)==1)
    fprintf(Resp3,"- BREJETUBA: %d casos\n",Total.contadorBREJETUBA);
  if(MAIORQUEN(n,Total.contadorCDI)==1)
    fprintf(Resp3,"- CACHOEIRO DE ITAPEMIRIM: %d casos\n",Total.contadorCDI);
  if(MAIORQUEN(n,Total.contadorCARIACICA)==1)
    fprintf(Resp3,"- CARIACICA: %d casos\n",Total.contadorCARIACICA);
  if(MAIORQUEN(n,Total.contadorCASTELO)==1)
    fprintf(Resp3,"- CASTELO: %d casos\n",Total.contadorCASTELO);
  if(MAIORQUEN(n,Total.contadorCOLATINA)==1)
    fprintf(Resp3,"- COLATINA: %d casos\n",Total.contadorCOLATINA);
  if(MAIORQUEN(n,Total.contadorCB)==1)
    fprintf(Resp3,"- CONCEICAO DA BARRA: %d casos\n",Total.contadorCB);
  if(MAIORQUEN(n,Total.contadorCC)==1)
    fprintf(Resp3,"- CONCEICAO DO CASTELO: %d casos\n",Total.contadorCC);
  if(MAIORQUEN(n,Total.contadorDSL)==1)
    fprintf(Resp3,"- DIVINO DE SAO LOURENCO: %d casos\n",Total.contadorDSL);
  if(MAIORQUEN(n,Total.contadorDM)==1)
    fprintf(Resp3,"- DOMINGOS MARTINS: %d casos\n",Total.contadorDM);
  if(MAIORQUEN(n,Total.contadorDRP)==1)
    fprintf(Resp3,"- DORES DO RIO PRETO: %d casos\n",Total.contadorDRP);
  if(MAIORQUEN(n,Total.contadorECOPORANGA)==1)
    fprintf(Resp3,"- ECOPORANGA: %d casos\n",Total.contadorECOPORANGA);
  if(MAIORQUEN(n,Total.contadorFUNDAO)==1)
    fprintf(Resp3,"- FUNDAO: %d casos\n",Total.contadorFUNDAO);
  if(MAIORQUEN(n,Total.contadorGL)==1)
    fprintf(Resp3,"- GOVERNADOR LINDENBERG: %d casos\n",Total.contadorGL);
  if(MAIORQUEN(n,Total.contadorGUACUI)==1)
    fprintf(Resp3,"- GUACUI: %d casos\n",Total.contadorGUACUI);
  if(MAIORQUEN(n,Total.contadorGUARAPARI)==1)
    fprintf(Resp3,"- GUARAPARI: %d casos\n",Total.contadorGUARAPARI);
  if(MAIORQUEN(n,Total.contadorIBATIBA)==1)
    fprintf(Resp3,"- IBATIBA: %d casos\n",Total.contadorIBATIBA);
  if(MAIORQUEN(n,Total.contadorIBIRACU)==1)
    fprintf(Resp3,"- IBIRACU: %d casos\n",Total.contadorIBIRACU);
  if(MAIORQUEN(n,Total.contadorIBITIRAMA)==1)
    fprintf(Resp3,"- IBITIRAMA: %d casos\n",Total.contadorIBITIRAMA);
  if(MAIORQUEN(n,Total.contadorICONHA)==1)
    fprintf(Resp3,"- ICONHA: %d casos\n",Total.contadorICONHA);
  if(MAIORQUEN(n,Total.contadorIRUPI)==1)
    fprintf(Resp3,"- IRUPI: %d casos\n",Total.contadorIRUPI);
  if(MAIORQUEN(n,Total.contadorITAGUACU)==1)
    fprintf(Resp3,"- ITAGUACU: %d casos\n",Total.contadorITAGUACU);
  if(MAIORQUEN(n,Total.contadorITAPEMIRIM)==1)
    fprintf(Resp3,"- ITAPEMIRIM: %d casos\n",Total.contadorITAPEMIRIM);
  if(MAIORQUEN(n,Total.contadorITARANA)==1)
    fprintf(Resp3,"- ITARANA: %d casos\n",Total.contadorITARANA);
  if(MAIORQUEN(n,Total.contadorIUNA)==1)
    fprintf(Resp3,"- IUNA: %d casos\n",Total.contadorIUNA);
  if(MAIORQUEN(n,Total.contadorJAGUARE)==1)
    fprintf(Resp3,"- JAGUARE: %d casos\n",Total.contadorJAGUARE);
  if(MAIORQUEN(n,Total.contadorJM)==1)
    fprintf(Resp3,"- JERONIMO MONTEIRO: %d casos\n",Total.contadorJM);
  if(MAIORQUEN(n,Total.contadorJN)==1)
    fprintf(Resp3,"- JOAO NEIVA: %d casos\n",Total.contadorJN);
  if(MAIORQUEN(n,Total.contadorLT)==1)
    fprintf(Resp3,"- LARANJA DA TERRA: %d casos\n",Total.contadorLT);
  if(MAIORQUEN(n,Total.contadorLINHARES)==1)
    fprintf(Resp3,"- LINHARES: %d casos\n",Total.contadorLINHARES);
  if(MAIORQUEN(n,Total.contadorMANTENOPOLIS)==1)
    fprintf(Resp3,"- MANTENOPOLIS: %d casos\n",Total.contadorMANTENOPOLIS);
  if(MAIORQUEN(n,Total.contadorMARATAIZES)==1)
    fprintf(Resp3,"- MARATAIZES: %d casos\n",Total.contadorMARATAIZES);
  if(MAIORQUEN(n,Total.contadorMFLORIANO)==1)
    fprintf(Resp3,"- MARECHAL FLORIANO: %d casos\n",Total.contadorMFLORIANO);
  if(MAIORQUEN(n,Total.contadorMARILANDIA)==1)
    fprintf(Resp3,"- MARILANDIA: %d casos\n",Total.contadorMARILANDIA);
  if(MAIORQUEN(n,Total.contadorMS)==1)
    fprintf(Resp3,"- MIMOSO DO SUL: %d casos\n",Total.contadorMS);
  if(MAIORQUEN(n,Total.contadorMONTANHA)==1)
    fprintf(Resp3,"- MONTANHA: %d casos\n",Total.contadorMONTANHA);
  if(MAIORQUEN(n,Total.contadorMUCURICI)==1)
    fprintf(Resp3,"- MUCURICI: %d casos\n",Total.contadorMUCURICI);
  if(MAIORQUEN(n,Total.contadorMF)==1)
    fprintf(Resp3,"- MUNIZ FREIRE: %d casos\n",Total.contadorMF);
  if(MAIORQUEN(n,Total.contadorMUQUI)==1)
    fprintf(Resp3,"- MUQUI: %d casos\n",Total.contadorMUQUI);
  if(MAIORQUEN(n,Total.contadorNV)==1)
    fprintf(Resp3,"- NOVA VENECIA: %d casos\n",Total.contadorNV);
  if(MAIORQUEN(n,Total.contadorPANCAS)==1)
    fprintf(Resp3,"- PANCAS: %d casos\n",Total.contadorPANCAS);
  if(MAIORQUEN(n,Total.contadorPC)==1)
    fprintf(Resp3,"- PEDRO CANARIO: %d casos\n",Total.contadorPC);
  if(MAIORQUEN(n,Total.contadorPINHEIROS)==1)
    fprintf(Resp3,"- PINHEIROS: %d casos\n",Total.contadorPINHEIROS);
  if(MAIORQUEN(n,Total.contadorPIUMA)==1)
    fprintf(Resp3,"- PIUMA: %d casos\n",Total.contadorPIUMA);
  if(MAIORQUEN(n,Total.contadorPB)==1)
    fprintf(Resp3,"- PONTO BELO: %d casos\n",Total.contadorPB);
  if(MAIORQUEN(n,Total.contadorPK)==1)
    fprintf(Resp3,"- PRESIDENTE KENNEDY: %d casos\n",Total.contadorPK);
  if(MAIORQUEN(n,Total.contadorRB)==1)
    fprintf(Resp3,"- RIO BANANAL: %d casos\n",Total.contadorRB);     
  if(MAIORQUEN(n,Total.contadorRNS)==1)
    fprintf(Resp3,"- RIO NOVO DO SUL: %d casos\n",Total.contadorRNS);    
  if(MAIORQUEN(n,Total.contadorSL)==1)
    fprintf(Resp3,"- SANTA LEOPOLDINA: %d casos\n",Total.contadorSL);     
  if(MAIORQUEN(n,Total.contadorSMJ)==1)
    fprintf(Resp3,"- SANTA MARIA DE JETIBA: %d casos\n",Total.contadorSMJ);
  if(MAIORQUEN(n,Total.contadorST)==1)
    fprintf(Resp3,"- SANTA TERESA: %d casos\n",Total.contadorST);    
  if(MAIORQUEN(n,Total.contadorSDN)==1)
    fprintf(Resp3,"- SAO DOMINGOS DO NORTE: %d casos\n",Total.contadorSDN);
  if(MAIORQUEN(n,Total.contadorSGP)==1)
    fprintf(Resp3,"- SAO GABRIEL DA PALHA: %d casos\n",Total.contadorSGP);
  if(MAIORQUEN(n,Total.contadorSJC)==1)
    fprintf(Resp3,"- SAO JOSE DO CALCADO: %d casos\n",Total.contadorSJC);
  if(MAIORQUEN(n,Total.contadorSM)==1)
    fprintf(Resp3,"- SAO MATEUS: %d casos\n",Total.contadorSM);
  if(MAIORQUEN(n,Total.contadorSRC)==1)
    fprintf(Resp3,"- SAO ROQUE DO CANAA: %d casos\n",Total.contadorSRC);   
  if(MAIORQUEN(n,Total.contadorSERRA)==1)
    fprintf(Resp3,"- SERRA: %d casos\n",Total.contadorSERRA);
  if(MAIORQUEN(n,Total.contadorSOORETAMA)==1)
    fprintf(Resp3,"- SOORETAMA: %d casos\n",Total.contadorSOORETAMA);
  if(MAIORQUEN(n,Total.contadorVA)==1)
    fprintf(Resp3,"- VARGEM ALTA: %d casos\n",Total.contadorVA);
  if(MAIORQUEN(n,Total.contadorVNI)==1)
    fprintf(Resp3,"- VENDA NOVA DO IMIGRANTE: %d casos\n",Total.contadorVNI); 
  if(MAIORQUEN(n,Total.contadorVIANA)==1)
    fprintf(Resp3,"- VIANA: %d casos\n",Total.contadorVIANA);
  if(MAIORQUEN(n,Total.contadorVP)==1)
    fprintf(Resp3,"- VILA PAVAO: %d casos\n",Total.contadorVP);
  if(MAIORQUEN(n,Total.contadorVV)==1)
    fprintf(Resp3,"- VILA VALERIO: %d casos\n",Total.contadorVV);     
  if(MAIORQUEN(n,Total.contadorVILAVELHA)==1)
    fprintf(Resp3,"- VILA VELHA: %d casos\n",Total.contadorVILAVELHA);    
  if(MAIORQUEN(n,Total.contadorVITORIA)==1)
    fprintf(Resp3,"- VITORIA: %d casos\n",Total.contadorVITORIA);

  //PRINT DA PARTE 4
  //Printa o numero de casos 'Confirmados' em todas as cidades entra as datas limitantes fornecidas
  fprintf(saida4,"- Total de pessoas: %d\n",CasosnoIntervalo);

  //PARTE 5
  //Modulcao das variaveis da parte 5 feita a partir de uma logica Bubble Sort com a passagem de tanto os contadores quanto os nomes de cada municipio
  int j, temp;
  char NomeAux[30];
  for(j=0;j<TopCidades;j++){
    for(i=0;i<77;i++){
      if(V[i].contador<V[i+1].contador){
        strcpy(NomeAux,V[i].Nome);
        strcpy(V[i].Nome,V[i+1].Nome);
        strcpy(V[i+1].Nome,NomeAux);
        
        temp=V[i].contador;
        V[i].contador = V[i+1].contador;
        V[i+1].contador = temp;
      }
    }
  }
  
 //Print da parte 5
  for(i=0;i<TopCidades;i++){
    if(V[i].contador!=0){
    fprintf(saida5,"- %s: %d casos\n", V[i].Nome, V[i].contador);
    }
  }
  

  //PARTE 6
  //Devolve as porcentagens pedidas no topico 6 p/ cada municipio ou para 'TODAS'
  fprintf(saida6,"- Resultados para %s:\n",MunicipiosAnalisados);
  if(strcmp(MunicipiosAnalisados,"TODAS")==0){
    //Calculo das porcentagens 
    PorCInternados=((TotalInternacoes*100.0)/TotalConfirmados);
    PorCMorreram=((TotalMortes*100.0)/TotalConfirmados);
    PorCMorreramInternados=((TotalMorteInternado*100.0)/TotalMortes);
    //Print das porcentagens
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
  //Implementando a lógica das porcentagens para cada municipio de forma separada porem com o mesmo processo
  if(strcmp(MunicipiosAnalisados,"VITORIA")==0){
    PorCInternados=((Internacao.contadorVITORIA*100.0)/Total.contadorVITORIA);
    PorCMorreram=((Morte.contadorVITORIA*100.0)/Total.contadorVITORIA);
    PorCMorreramInternados=((MorteInternado.contadorVITORIA*100.0)/Morte.contadorVITORIA);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
  if(strcmp(MunicipiosAnalisados,"VILA VELHA")==0){
    PorCInternados=((Internacao.contadorVILAVELHA*100.0)/Total.contadorVILAVELHA);
    PorCMorreram=((Morte.contadorVILAVELHA*100.0)/Total.contadorVILAVELHA);
    PorCMorreramInternados=((MorteInternado.contadorVILAVELHA*100.0)/Morte.contadorVILAVELHA);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
   if(strcmp(MunicipiosAnalisados,"SERRA")==0){
    PorCInternados=((Internacao.contadorSERRA*100.0)/Total.contadorSERRA);
    PorCMorreram=((Morte.contadorSERRA*100.0)/Total.contadorSERRA);
    PorCMorreramInternados=((MorteInternado.contadorSERRA*100.0)/Morte.contadorSERRA);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
   if(strcmp(MunicipiosAnalisados,"CARIACICA")==0){
    PorCInternados=((Internacao.contadorCARIACICA*100.0)/Total.contadorCARIACICA);
    PorCMorreram=((Morte.contadorCARIACICA*100.0)/Total.contadorCARIACICA);
    PorCMorreramInternados=((MorteInternado.contadorCARIACICA*100.0)/Morte.contadorCARIACICA);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
   if(strcmp(MunicipiosAnalisados,"CACHOEIRO DE ITAPEMIRIM")==0){
    PorCInternados=((Internacao.contadorCDI*100.0)/Total.contadorCDI);
    PorCMorreram=((Morte.contadorCDI*100.0)/Total.contadorCDI);
    PorCMorreramInternados=((MorteInternado.contadorCDI*100.0)/Morte.contadorCDI);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
   if(strcmp(MunicipiosAnalisados,"LINHARES")==0){
    PorCInternados=((Internacao.contadorLINHARES*100.0)/Total.contadorLINHARES);
    PorCMorreram=((Morte.contadorLINHARES*100.0)/Total.contadorLINHARES);
    PorCMorreramInternados=((MorteInternado.contadorLINHARES*100.0)/Morte.contadorLINHARES);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
   if(strcmp(MunicipiosAnalisados,"SAO MATEUS")==0){
    PorCInternados=((Internacao.contadorSM*100.0)/Total.contadorSM);
    PorCMorreram=((Morte.contadorSM*100.0)/Total.contadorSM);
    PorCMorreramInternados=((MorteInternado.contadorSM*100.0)/Morte.contadorSM);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
   if(strcmp(MunicipiosAnalisados,"GUARAPARI")==0){
    PorCInternados=((Internacao.contadorGUARAPARI*100.0)/Total.contadorGUARAPARI);
    PorCMorreram=((Morte.contadorGUARAPARI*100.0)/Total.contadorGUARAPARI);
    PorCMorreramInternados=((MorteInternado.contadorGUARAPARI*100.0)/Morte.contadorGUARAPARI);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
   if(strcmp(MunicipiosAnalisados,"COLATINA")==0){
    PorCInternados=((Internacao.contadorCOLATINA*100.0)/Total.contadorCOLATINA);
    PorCMorreram=((Morte.contadorCOLATINA*100.0)/Total.contadorCOLATINA);
    PorCMorreramInternados=((MorteInternado.contadorCOLATINA*100.0)/Morte.contadorCOLATINA);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
   if(strcmp(MunicipiosAnalisados,"ARACRUZ")==0){
    PorCInternados=((Internacao.contadorARACRUZ*100.0)/Total.contadorARACRUZ);
    PorCMorreram=((Morte.contadorARACRUZ*100.0)/Total.contadorARACRUZ);
    PorCMorreramInternados=((MorteInternado.contadorARACRUZ*100.0)/Morte.contadorARACRUZ);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
   if(strcmp(MunicipiosAnalisados,"VIANA")==0){
    PorCInternados=((Internacao.contadorVIANA*100.0)/Total.contadorVIANA);
    PorCMorreram=((Morte.contadorVIANA*100.0)/Total.contadorVIANA);
    PorCMorreramInternados=((MorteInternado.contadorVIANA*100.0)/Morte.contadorVIANA);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
   if(strcmp(MunicipiosAnalisados,"NOVA VENECIA")==0){
    PorCInternados=((Internacao.contadorNV*100.0)/Total.contadorNV);
    PorCMorreram=((Morte.contadorNV*100.0)/Total.contadorNV);
    PorCMorreramInternados=((MorteInternado.contadorNV*100.0)/Morte.contadorNV);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
   if(strcmp(MunicipiosAnalisados,"BARRA DE SAO FRANCISCO")==0){
    PorCInternados=((Internacao.contadorBSF*100.0)/Total.contadorBSF);
    PorCMorreram=((Morte.contadorBSF*100.0)/Total.contadorBSF);
    PorCMorreramInternados=((MorteInternado.contadorBSF*100.0)/Morte.contadorBSF);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
   if(strcmp(MunicipiosAnalisados,"SANTA MARIA DE JETIBA")==0){
    PorCInternados=((Internacao.contadorSMJ*100.0)/Total.contadorSMJ);
    PorCMorreram=((Morte.contadorSMJ*100.0)/Total.contadorSMJ);
    PorCMorreramInternados=((MorteInternado.contadorSMJ*100.0)/Morte.contadorSMJ);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
   if(strcmp(MunicipiosAnalisados,"MARATAIZES")==0){
    PorCInternados=((Internacao.contadorMARATAIZES*100.0)/Total.contadorMARATAIZES);
    PorCMorreram=((Morte.contadorMARATAIZES*100.0)/Total.contadorMARATAIZES);
    PorCMorreramInternados=((MorteInternado.contadorMARATAIZES*100.0)/Morte.contadorMARATAIZES);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
   if(strcmp(MunicipiosAnalisados,"SAO GABRIEL DA PALHA")==0){
    PorCInternados=((Internacao.contadorSGP*100.0)/Total.contadorSGP);
    PorCMorreram=((Morte.contadorSGP*100.0)/Total.contadorSGP);
    PorCMorreramInternados=((MorteInternado.contadorSGP*100.0)/Morte.contadorSGP);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
   if(strcmp(MunicipiosAnalisados,"CASTELO")==0){
    PorCInternados=((Internacao.contadorCASTELO*100.0)/Total.contadorCASTELO);
    PorCMorreram=((Morte.contadorCASTELO*100.0)/Total.contadorCASTELO);
    PorCMorreramInternados=((MorteInternado.contadorCASTELO*100.0)/Morte.contadorCASTELO);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
   if(strcmp(MunicipiosAnalisados,"ITAPEMIRIM")==0){
    PorCInternados=((Internacao.contadorITAPEMIRIM*100.0)/Total.contadorITAPEMIRIM);
    PorCMorreram=((Morte.contadorITAPEMIRIM*100.0)/Total.contadorITAPEMIRIM);
    PorCMorreramInternados=((MorteInternado.contadorITAPEMIRIM*100.0)/Morte.contadorITAPEMIRIM);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
   if(strcmp(MunicipiosAnalisados,"DOMINGOS MARTINS")==0){
    PorCInternados=((Internacao.contadorDM*100.0)/Total.contadorDM);
    PorCMorreram=((Morte.contadorDM*100.0)/Total.contadorDM);
    PorCMorreramInternados=((MorteInternado.contadorDM*100.0)/Morte.contadorDM);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);  }
   if(strcmp(MunicipiosAnalisados,"CONCEICAO DA BARRA")==0){
    PorCInternados=((Internacao.contadorCB*100.0)/Total.contadorCB);
    PorCMorreram=((Morte.contadorCB*100.0)/Total.contadorCB);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);  }
  if(strcmp(MunicipiosAnalisados,"BAIXO GUANDU")==0){
    PorCInternados=((Internacao.contadorBG*100.0)/Total.contadorBG);
    PorCMorreram=((Morte.contadorBG*100.0)/Total.contadorBG);
    PorCMorreramInternados=((MorteInternado.contadorBG*100.0)/Morte.contadorBG);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);  }
  if(strcmp(MunicipiosAnalisados,"GUACUI")==0){
    PorCInternados=((Internacao.contadorGUACUI*100.0)/Total.contadorGUACUI);
    PorCMorreram=((Morte.contadorGUACUI*100.0)/Total.contadorGUACUI);
    PorCMorreramInternados=((MorteInternado.contadorGUACUI*100.0)/Morte.contadorGUACUI);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);  }
  if(strcmp(MunicipiosAnalisados,"JAGUARE")==0){
    PorCInternados=((Internacao.contadorJAGUARE*100.0)/Total.contadorJAGUARE);
    PorCMorreram=((Morte.contadorJAGUARE*100.0)/Total.contadorJAGUARE);
    PorCMorreramInternados=((MorteInternado.contadorJAGUARE*100.0)/Morte.contadorJAGUARE);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);  }
  if(strcmp(MunicipiosAnalisados,"SOORETAMA")==0){
    PorCInternados=((Internacao.contadorSOORETAMA*100.0)/Total.contadorSOORETAMA);
    PorCMorreram=((Morte.contadorSOORETAMA*100.0)/Total.contadorSOORETAMA);
    PorCMorreramInternados=((MorteInternado.contadorSOORETAMA*100.0)/Morte.contadorSOORETAMA);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);  
    }
  if(strcmp(MunicipiosAnalisados,"AFONSO CLAUDIO")==0){
    PorCInternados=((Internacao.contadorAC*100.0)/Total.contadorAC);
    PorCMorreram=((Morte.contadorAC*100.0)/Total.contadorAC);
    PorCMorreramInternados=((MorteInternado.contadorAC*100.0)/Morte.contadorAC);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados); 
    }
  if(strcmp(MunicipiosAnalisados,"ALEGRE")==0){
    PorCInternados=((Internacao.contadorALEGRE*100.0)/Total.contadorALEGRE);
    PorCMorreram=((Morte.contadorALEGRE*100.0)/Total.contadorALEGRE);
    PorCMorreramInternados=((MorteInternado.contadorALEGRE*100.0)/Morte.contadorALEGRE);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);  
    }
  if(strcmp(MunicipiosAnalisados,"ANCHIETA")==0){
    PorCInternados=((Internacao.contadorANCHIETA*100.0)/Total.contadorANCHIETA);
    PorCMorreram=((Morte.contadorANCHIETA*100.0)/Total.contadorANCHIETA);
    PorCMorreramInternados=((MorteInternado.contadorANCHIETA*100.0)/Morte.contadorANCHIETA);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);  
    }
  if(strcmp(MunicipiosAnalisados,"IUNA")==0){
    PorCInternados=((Internacao.contadorIUNA*100.0)/Total.contadorIUNA);
    PorCMorreram=((Morte.contadorIUNA*100.0)/Total.contadorIUNA);
    PorCMorreramInternados=((MorteInternado.contadorIUNA*100.0)/Morte.contadorIUNA);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
    }
  if(strcmp(MunicipiosAnalisados,"PINHEIROS")==0){
    PorCInternados=((Internacao.contadorPINHEIROS*100.0)/Total.contadorPINHEIROS);
    PorCMorreram=((Morte.contadorPINHEIROS*100.0)/Total.contadorPINHEIROS);
    PorCMorreramInternados=((MorteInternado.contadorPINHEIROS*100.0)/Morte.contadorPINHEIROS);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados); 
    }
  if(strcmp(MunicipiosAnalisados,"IBATIBA")==0){
    PorCInternados=((Internacao.contadorIBATIBA*100.0)/Total.contadorIBATIBA);
    PorCMorreram=((Morte.contadorIBATIBA*100.0)/Total.contadorIBATIBA);
    PorCMorreramInternados=((MorteInternado.contadorIBATIBA*100.0)/Morte.contadorIBATIBA);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);  
    }
  if(strcmp(MunicipiosAnalisados,"PEDRO CANARIO")==0){
    PorCInternados=((Internacao.contadorPC*100.0)/Total.contadorPC);
    PorCMorreram=((Morte.contadorPC*100.0)/Total.contadorPC);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);  
    }
  if(strcmp(MunicipiosAnalisados,"MIMOSO DO SUL")==0){
    PorCInternados=((Internacao.contadorMS*100.0)/Total.contadorMS);
    PorCMorreram=((Morte.contadorMS*100.0)/Total.contadorMS);
    PorCMorreramInternados=((MorteInternado.contadorMS*100.0)/Morte.contadorMS);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);  
    }
  if(strcmp(MunicipiosAnalisados,"VENDA NOVA DO IMIGRANTE")==0){
    PorCInternados=((Internacao.contadorVNI*100.0)/Total.contadorVNI);
    PorCMorreram=((Morte.contadorVNI*100.0)/Total.contadorVNI);
    PorCMorreramInternados=((MorteInternado.contadorVNI*100.0)/Morte.contadorVNI);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados); 
     }
  if(strcmp(MunicipiosAnalisados,"SANTA TERESA")==0){
    PorCInternados=((Internacao.contadorST*100.0)/Total.contadorST);
    PorCMorreram=((Morte.contadorST*100.0)/Total.contadorST);
    PorCMorreramInternados=((MorteInternado.contadorST*100.0)/Morte.contadorST);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);  
    }
  if(strcmp(MunicipiosAnalisados,"PANCAS")==0){
    PorCInternados=((Internacao.contadorPANCAS*100.0)/Total.contadorPANCAS);
    PorCMorreram=((Morte.contadorPANCAS*100.0)/Total.contadorPANCAS);
    PorCMorreramInternados=((MorteInternado.contadorPANCAS*100.0)/Morte.contadorPANCAS);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);  
    }
  if(strcmp(MunicipiosAnalisados,"ECOPORANGA")==0){
    PorCInternados=((Internacao.contadorECOPORANGA*100.0)/Total.contadorECOPORANGA);
    PorCMorreram=((Morte.contadorECOPORANGA*100.0)/Total.contadorECOPORANGA);
    PorCMorreramInternados=((MorteInternado.contadorECOPORANGA*100.0)/Morte.contadorECOPORANGA);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados); 
    }
  if(strcmp(MunicipiosAnalisados,"PIUMA")==0){
    PorCInternados=((Internacao.contadorPIUMA*100.0)/Total.contadorPIUMA);
    PorCMorreram=((Morte.contadorPIUMA*100.0)/Total.contadorPIUMA);
    PorCMorreramInternados=((MorteInternado.contadorPIUMA*100.0)/Morte.contadorPIUMA);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);  
    }
  if(strcmp(MunicipiosAnalisados,"FUNDAO")==0){
    PorCInternados=((Internacao.contadorFUNDAO*100.0)/Total.contadorFUNDAO);
    PorCMorreram=((Morte.contadorFUNDAO*100.0)/Total.contadorFUNDAO);
    PorCMorreramInternados=((MorteInternado.contadorFUNDAO*100.0)/Morte.contadorFUNDAO);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);  
    }
  if(strcmp(MunicipiosAnalisados,"VARGEM ALTA")==0){
    PorCInternados=((Internacao.contadorVA*100.0)/Total.contadorVA);
    PorCMorreram=((Morte.contadorVA*100.0)/Total.contadorVA);
    PorCMorreramInternados=((MorteInternado.contadorVA*100.0)/Morte.contadorVA);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);  
    }
  if(strcmp(MunicipiosAnalisados,"RIO BANANAL")==0){
    PorCInternados=((Internacao.contadorRB*100.0)/Total.contadorRB);
    PorCMorreram=((Morte.contadorRB*100.0)/Total.contadorRB);
    PorCMorreramInternados=((MorteInternado.contadorRB*100.0)/Morte.contadorRB);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);  
    }
  if(strcmp(MunicipiosAnalisados,"MONTANHA")==0){
    PorCInternados=((Internacao.contadorMONTANHA*100.0)/Total.contadorMONTANHA);
    PorCMorreram=((Morte.contadorMONTANHA*100.0)/Total.contadorMONTANHA);
    PorCMorreramInternados=((MorteInternado.contadorMONTANHA*100.0)/Morte.contadorMONTANHA);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
  if(strcmp(MunicipiosAnalisados,"MUNIZ FREIRE")==0){
    PorCInternados=((Internacao.contadorMF*100.0)/Total.contadorMF);
    PorCMorreram=((Morte.contadorMF*100.0)/Total.contadorMF);
    PorCMorreramInternados=((MorteInternado.contadorMF*100.0)/Morte.contadorMF);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
  if(strcmp(MunicipiosAnalisados,"MARECHAL FLORIANO")==0){
    PorCInternados=((Internacao.contadorMFLORIANO*100.0)/Total.contadorMFLORIANO);
    PorCMorreram=((Morte.contadorMFLORIANO*100.0)/Total.contadorMFLORIANO);
    PorCMorreramInternados=((MorteInternado.contadorMFLORIANO*100.0)/Morte.contadorMFLORIANO);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
  if(strcmp(MunicipiosAnalisados,"JOAO NEIVA")==0){
    PorCInternados=((Internacao.contadorJN*100.0)/Total.contadorJN);
    PorCMorreram=((Morte.contadorJN*100.0)/Total.contadorJN);
    PorCMorreramInternados=((MorteInternado.contadorJN*100.0)/Morte.contadorJN);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
  if(strcmp(MunicipiosAnalisados,"MUQUI")==0){
    PorCInternados=((Internacao.contadorMUQUI*100.0)/Total.contadorMUQUI);
    PorCMorreram=((Morte.contadorMUQUI*100.0)/Total.contadorMUQUI);
    PorCMorreramInternados=((MorteInternado.contadorMUQUI*100.0)/Morte.contadorMUQUI);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
  if(strcmp(MunicipiosAnalisados,"MANTENOPOLIS")==0){
    PorCInternados=((Internacao.contadorMANTENOPOLIS*100.0)/Total.contadorMANTENOPOLIS);
    PorCMorreram=((Morte.contadorMANTENOPOLIS*100.0)/Total.contadorMANTENOPOLIS);
    PorCMorreramInternados=((MorteInternado.contadorMANTENOPOLIS*100.0)/Morte.contadorMANTENOPOLIS);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
  if(strcmp(MunicipiosAnalisados,"BOA ESPERANCA")==0){
    PorCInternados=((Internacao.contadorBE*100.0)/Total.contadorBE);
    PorCMorreram=((Morte.contadorBE*100.0)/Total.contadorBE);
    PorCMorreramInternados=((MorteInternado.contadorBE*100.0)/Morte.contadorBE);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
  if(strcmp(MunicipiosAnalisados,"ITAGUACU")==0){
    PorCInternados=((Internacao.contadorITAGUACU*100.0)/Total.contadorITAGUACU);
    PorCMorreram=((Morte.contadorITAGUACU*100.0)/Total.contadorITAGUACU);
    PorCMorreramInternados=((MorteInternado.contadorITAGUACU*100.0)/Morte.contadorITAGUACU);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
  if(strcmp(MunicipiosAnalisados,"ALFREDO CHAVES")==0){
    PorCInternados=((Internacao.contadorACHAVEZ*100.0)/Total.contadorACHAVEZ);
    PorCMorreram=((Morte.contadorACHAVEZ*100.0)/Total.contadorACHAVEZ);
    PorCMorreramInternados=((MorteInternado.contadorACHAVEZ*100.0)/Morte.contadorACHAVEZ);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
  if(strcmp(MunicipiosAnalisados,"VILA VALERIO")==0){
    PorCInternados=((Internacao.contadorVV*100.0)/Total.contadorVV);
    PorCMorreram=((Morte.contadorVV*100.0)/Total.contadorVV);
    PorCMorreramInternados=((MorteInternado.contadorVV*100.0)/Morte.contadorVV);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
  if(strcmp(MunicipiosAnalisados,"ICONHA")==0){
    PorCInternados=((Internacao.contadorICONHA*100.0)/Total.contadorICONHA);
    PorCMorreram=((Morte.contadorICONHA*100.0)/Total.contadorICONHA);
    PorCMorreramInternados=((MorteInternado.contadorICONHA*100.0)/Morte.contadorICONHA);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
  if(strcmp(MunicipiosAnalisados,"IRUPI")==0){
    PorCInternados=((Internacao.contadorIRUPI*100.0)/Total.contadorIRUPI);
    PorCMorreram=((Morte.contadorIRUPI*100.0)/Total.contadorIRUPI);
    PorCMorreramInternados=((MorteInternado.contadorIRUPI*100.0)/Morte.contadorIRUPI);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
  if(strcmp(MunicipiosAnalisados,"CONCEICAO DO CASTELO")==0){
    PorCInternados=((Internacao.contadorCC*100.0)/Total.contadorCC);
    PorCMorreram=((Morte.contadorCC*100.0)/Total.contadorCC);
    PorCMorreramInternados=((MorteInternado.contadorCC*100.0)/Morte.contadorCC);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
  if(strcmp(MunicipiosAnalisados,"MARILANDIA")==0){
    PorCInternados=((Internacao.contadorMARILANDIA*100.0)/Total.contadorMARILANDIA);
    PorCMorreram=((Morte.contadorMARILANDIA*100.0)/Total.contadorMARILANDIA);
    PorCMorreramInternados=((MorteInternado.contadorMARILANDIA*100.0)/Morte.contadorMARILANDIA);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
  if(strcmp(MunicipiosAnalisados,"GOVERNADOR LINDENBERG")==0){
    PorCInternados=((Internacao.contadorGL*100.0)/Total.contadorGL);
    PorCMorreram=((Morte.contadorGL*100.0)/Total.contadorGL);
    PorCMorreramInternados=((MorteInternado.contadorGL*100.0)/Morte.contadorGL);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
  if(strcmp(MunicipiosAnalisados,"BREJETUBA")==0){
    PorCInternados=((Internacao.contadorBREJETUBA*100.0)/Total.contadorBREJETUBA);
    PorCMorreram=((Morte.contadorBREJETUBA*100.0)/Total.contadorBREJETUBA);
    PorCMorreramInternados=((MorteInternado.contadorBREJETUBA*100.0)/Morte.contadorBREJETUBA);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
  if(strcmp(MunicipiosAnalisados,"IBIRACU")==0){
    PorCInternados=((Internacao.contadorIBIRACU*100.0)/Total.contadorIBIRACU);
    PorCMorreram=((Morte.contadorIBIRACU*100.0)/Total.contadorIBIRACU);
    PorCMorreramInternados=((MorteInternado.contadorIBIRACU*100.0)/Morte.contadorIBIRACU);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
  if(strcmp(MunicipiosAnalisados,"SAO ROQUE DO CANAA")==0){
    PorCInternados=((Internacao.contadorSRC*100.0)/Total.contadorSRC);
    PorCMorreram=((Morte.contadorSRC*100.0)/Total.contadorSRC);
    PorCMorreramInternados=((MorteInternado.contadorSRC*100.0)/Morte.contadorSRC);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
  if(strcmp(MunicipiosAnalisados,"SANTA LEOPOLDINA")==0){
    PorCInternados=((Internacao.contadorSL*100.0)/Total.contadorSL);
    PorCMorreram=((Morte.contadorSL*100.0)/Total.contadorSL);
    PorCMorreramInternados=((MorteInternado.contadorSL*100.0)/Morte.contadorSL);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
  if(strcmp(MunicipiosAnalisados,"JERONIMO MONTEIRO")==0){
    PorCInternados=((Internacao.contadorJM*100.0)/Total.contadorJM);
    PorCMorreram=((Morte.contadorJM*100.0)/Total.contadorJM);
    PorCMorreramInternados=((MorteInternado.contadorJM*100.0)/Morte.contadorJM);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
  if(strcmp(MunicipiosAnalisados,"PRESIDENTE KENNEDY")==0){
    PorCInternados=((Internacao.contadorPK*100.0)/Total.contadorPK);
    PorCMorreram=((Morte.contadorPK*100.0)/Total.contadorPK);
    PorCMorreramInternados=((MorteInternado.contadorPK*100.0)/Morte.contadorPK);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
  if(strcmp(MunicipiosAnalisados,"ATILIO VIVACQUA")==0){
    PorCInternados=((Internacao.contadorAV*100.0)/Total.contadorAV);
    PorCMorreram=((Morte.contadorAV*100.0)/Total.contadorAV);
    PorCMorreramInternados=((MorteInternado.contadorAV*100.0)/Morte.contadorAV);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
  if(strcmp(MunicipiosAnalisados,"RIO NOVO DO SUL")==0){
    PorCInternados=((Internacao.contadorRNS*100.0)/Total.contadorRNS);
    PorCMorreram=((Morte.contadorRNS*100.0)/Total.contadorRNS);
    PorCMorreramInternados=((MorteInternado.contadorRNS*100.0)/Morte.contadorRNS);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
  if(strcmp(MunicipiosAnalisados,"AGUA DOCE DO NORTE")==0){
    PorCInternados=((Internacao.contadorADN*100.0)/Total.contadorADN);
    PorCMorreram=((Morte.contadorADN*100.0)/Total.contadorADN);
    PorCMorreramInternados=((MorteInternado.contadorADN*100.0)/Morte.contadorADN);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
  if(strcmp(MunicipiosAnalisados,"LARANJA DA TERRA")==0){
    PorCInternados=((Internacao.contadorLT*100.0)/Total.contadorLT);
    PorCMorreram=((Morte.contadorLT*100.0)/Total.contadorLT);
    PorCMorreramInternados=((MorteInternado.contadorLT*100.0)/Morte.contadorLT);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
  if(strcmp(MunicipiosAnalisados,"ITARANA")==0){
    PorCInternados=((Internacao.contadorITARANA*100.0)/Total.contadorITARANA);
    PorCMorreram=((Morte.contadorITARANA*100.0)/Total.contadorITARANA);
    PorCMorreramInternados=((MorteInternado.contadorITARANA*100.0)/Morte.contadorITARANA);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
  if(strcmp(MunicipiosAnalisados,"SAO JOSE DO CALCADO")==0){
    PorCInternados=((Internacao.contadorSJC*100.0)/Total.contadorSJC);
    PorCMorreram=((Morte.contadorSJC*100.0)/Total.contadorSJC);
    PorCMorreramInternados=((MorteInternado.contadorSJC*100.0)/Morte.contadorSJC);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
  if(strcmp(MunicipiosAnalisados,"BOM JESUS DO NORTE")==0){
    PorCInternados=((Internacao.contadorBJN*100.0)/Total.contadorBJN);
    PorCMorreram=((Morte.contadorBJN*100.0)/Total.contadorBJN);
    PorCMorreramInternados=((MorteInternado.contadorBJN*100.0)/Morte.contadorBJN);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
  if(strcmp(MunicipiosAnalisados,"AGUIA BRANCA")==0){
    PorCInternados=((Internacao.contadorAB*100.0)/Total.contadorAB);
    PorCMorreram=((Morte.contadorAB*100.0)/Total.contadorAB);
    PorCMorreramInternados=((MorteInternado.contadorAB*100.0)/Morte.contadorAB);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
  if(strcmp(MunicipiosAnalisados,"VILA PAVAO")==0){
    PorCInternados=((Internacao.contadorVP*100.0)/Total.contadorVP);
    PorCMorreram=((Morte.contadorVP*100.0)/Total.contadorVP);
    PorCMorreramInternados=((MorteInternado.contadorVP*100.0)/Morte.contadorVP);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
  if(strcmp(MunicipiosAnalisados,"IBITIRAMA")==0){
    PorCInternados=((Internacao.contadorIBITIRAMA*100.0)/Total.contadorIBITIRAMA);
    PorCMorreram=((Morte.contadorIBITIRAMA*100.0)/Total.contadorIBITIRAMA);
    PorCMorreramInternados=((MorteInternado.contadorIBITIRAMA*100.0)/Morte.contadorIBITIRAMA);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
  if(strcmp(MunicipiosAnalisados,"SAO DOMINGOS DO NORTE")==0){
    PorCInternados=((Internacao.contadorSDN*100.0)/Total.contadorSDN);
    PorCMorreram=((Morte.contadorSDN*100.0)/Total.contadorSDN);
    PorCMorreramInternados=((MorteInternado.contadorSDN*100.0)/Morte.contadorSDN);
   fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
  if(strcmp(MunicipiosAnalisados,"PONTO BELO")==0){
    PorCInternados=((Internacao.contadorPB*100.0)/Total.contadorPB);
    PorCMorreram=((Morte.contadorPB*100.0)/Total.contadorPB);
    PorCMorreramInternados=((MorteInternado.contadorPB*100.0)/Morte.contadorPB);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
  if(strcmp(MunicipiosAnalisados,"ALTO RIO NOVO")==0){
    PorCInternados=((Internacao.contadorARN*100.0)/Total.contadorARN);
    PorCMorreram=((Morte.contadorARN*100.0)/Total.contadorARN);
    PorCMorreramInternados=((MorteInternado.contadorARN*100.0)/Morte.contadorARN);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
  if(strcmp(MunicipiosAnalisados,"APIACA")==0){
    PorCInternados=((Internacao.contadorAPIACA*100.0)/Total.contadorAPIACA);
    PorCMorreram=((Morte.contadorAPIACA*100.0)/Total.contadorAPIACA);
    PorCMorreramInternados=((MorteInternado.contadorAPIACA*100.0)/Morte.contadorAPIACA);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
  if(strcmp(MunicipiosAnalisados,"DORES DO RIO PRETO")==0){
    PorCInternados=((Internacao.contadorDRP*100.0)/Total.contadorDRP);
    PorCMorreram=((Morte.contadorDRP*100.0)/Total.contadorDRP);
    PorCMorreramInternados=((MorteInternado.contadorDRP*100.0)/Morte.contadorDRP);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
  if(strcmp(MunicipiosAnalisados,"MUCURICI")==0){
    PorCInternados=((Internacao.contadorMUCURICI*100.0)/Total.contadorMUCURICI);
    PorCMorreram=((Morte.contadorMUCURICI*100.0)/Total.contadorMUCURICI);
    PorCMorreramInternados=((MorteInternado.contadorMUCURICI*100.0)/Morte.contadorMUCURICI);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }
  if(strcmp(MunicipiosAnalisados,"DIVINO DE SAO LOURENCO")==0){
    PorCInternados=((Internacao.contadorDSL*100.0)/Total.contadorDSL);
    PorCMorreram=((Morte.contadorDSL*100.0)/Total.contadorDSL);
    PorCMorreramInternados=((MorteInternado.contadorDSL*100.0)/Morte.contadorDSL);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n",PorCInternados);
    fprintf(saida6,"- A %% de pessoas com Covid-19 que morreram: %.3f%%\n",PorCMorreram);
    fprintf(saida6,"- A %% de pessoas que ficaram internadas e morreram: %.3f%%\n",PorCMorreramInternados);
  }  
  
  //Calculo da Media de Idades,Porcentagem de mortes sem comorbidade e o desvio padrao da idade(PARTE 7)
  if(TotalMortesED!=0){
  PorCMorreramSComorbidade=(TotalMorteSemComorbidadeED*100.0)/TotalMortesED;
  MediaIdade=MediaIdade/TotalMortesED;
  }
  for(i=0;i<TAM;i++){
    if(VetorIdade[i]-MediaIdade>0){
      somatorio+=(VetorIdade[i]-MediaIdade)*(VetorIdade[i]-MediaIdade);
    }
    if(MediaIdade-VetorIdade[i]>=0){
      somatorio+=(MediaIdade-VetorIdade[i])*(MediaIdade-VetorIdade[i]);
    }
  }
  DP=sqrt(somatorio/(TAM-1));
  //Print da PARTE 7
  fprintf(saida7,"A media e desvio padrao da idade: %.3f -- %.3lf\n",MediaIdade,DP);
  fprintf(saida7,"A %% de pessoas que morreram sem comorbidade: %.3f%%",PorCMorreramSComorbidade);

  //Fechamento dos arquivos, tando o .csv quanto os arquivos de saida
  fclose(Resp3);
  fclose(saida4);
  fclose(saida5);
  fclose(saida6);
  fclose(saida7);
  fclose(arq);
  return 0;
}
