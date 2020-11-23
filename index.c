#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//l1.anoCadastro = atoi(token);
//printf("%d", l1.anoCadastro);
//token = strtok(NULL, ",");
//l1.mesCadastro = atoi(token);

typedef struct{
  int anoCadastro, mesCadastro, diaCadastro, anoObito, mesObito, diaObito, qtdDiaCadastro, qtdMesCadastro, qtdAnoCadastro;
  char dataIdadeCadastro[50], anoIdadeCadastro[50], mesIdadeCadastro[50], diaIdadeCadastro[50], classificacao[50], municipio[50], ComorbidadePulmao[3], ComorbidadeCardio[5], ComorbidadeRenal[5], ComorbidadeDiabetes[5], ComorbidadeTabagismo[5], ComorbidadeObesidade[5], FicouInternado[50];
}tArquivo;

int main(void) {
  int i=0, temp=0;
  char linhas[202363],*token;
  tArquivo c;  
  FILE *arq;
  arq=fopen("covid19ES.csv","r"); 
  if(arq==NULL){
    printf("Erro na abertura do arquivo");
    exit(1);
  }
  for(i=0;i<202363;i++){
    //Leitura do arquivo completo;
    fgets(linhas, 1000, arq);
    //printf("LINHA %d \n\n\n\n", i);
    //Separação da string dataCadastro p/ três inteiros;
    token = strtok(linhas, ",");
    sscanf(token, "%d-%d-%d", &c.anoCadastro, &c.mesCadastro, &c.diaCadastro);
    if(c.anoCadastro==0){
      temp=1;
    }else{
    printf("LINHA %d \n\n", i);
    printf("Data Cadastro:%d/%d/%d\n", c.anoCadastro, c.mesCadastro, c.diaCadastro);
    
    //Separação da string dataÓbito p/ três inteiros;
    token = strtok(NULL, ",");
    sscanf(token, "%d-%d-%d", &c.anoObito, &c.mesObito, &c.diaObito);
    printf("Data Obito:%d/%d/%d\n", c.anoObito, c.mesObito, c.diaObito);
    
    //Classificacao;
    token = strtok(NULL, ",");
    strcpy(c.classificacao,token);
    printf("Classificacao: %s\n", c.classificacao);
    
    //Municipio;
    token = strtok(NULL, ",");
    strcpy(c.municipio,token);
    printf("Municipio:%s\n",c.municipio);
    
    //Separação da string idadeCadastro p/ três inteiros;

    //tentativa 1;

    token = strtok(NULL,","); 
    sscanf(token, "\"%d anos", &c.qtdAnoCadastro);
    printf("Idade Cadastro: %d anos,", c.qtdAnoCadastro);

    token=strtok(NULL,",");
    sscanf(token," %d meses",&c.qtdMesCadastro);
    printf(" %d meses,",c.qtdMesCadastro);

    token=strtok(NULL,",");
    sscanf(token," %d dias\"",&c.qtdDiaCadastro);
    printf(" %d dias\n",c.qtdDiaCadastro);
    //"42 anos, 0 meses, 25 dias";
    
    /*token = strtok(NULL, ",");
    strcpy(c.mesIdadeCadastro, token);
    printf("%s",c.mesIdadeCadastro);

    token = strtok(NULL, ",");
    strcpy(c.diaIdadeCadastro, token);
    printf("%s\n",c.diaIdadeCadastro);*/

    /*token = strtok(NULL, ",");
    strcpy(c.dataIdadeCadastro, token);
    printf("Idade Cadastro: %s,", c.dataIdadeCadastro);
    token = strtok(NULL, ",");
    strcpy(c.dataIdadeCadastro, token);
    printf("%s\n", c.dataIdadeCadastro);
    token = strtok(NULL, ",");*/

    //ComorbidadePulmao;
    token = strtok(NULL, ",");
    strcpy(c.ComorbidadePulmao,token);
    printf("Comorbidade Pulmao:%s\n",c.ComorbidadePulmao);
        
    //ComorbidadeCardio;
    token = strtok(NULL,",");
    strcpy(c.ComorbidadeCardio,token);
    printf("ComorbidadeCardio:%s\n",c.ComorbidadeCardio);
    
    //ComorbidadeRenal;
    token = strtok(NULL, ",");
    strcpy(c.ComorbidadeRenal,token);
    printf("ComorbidadeRenal:%s\n",c.ComorbidadeRenal);
    
    //ComorbidadeDiabetes;
    token= strtok(NULL,",");
    strcpy(c.ComorbidadeDiabetes,token);
    printf("ComorbidadeDiabetes:%s\n",c.ComorbidadeDiabetes);
    //ComorbidadeTabagismo;
    token= strtok(NULL,",");
    strcpy(c.ComorbidadeTabagismo,token);
    printf("ComorbidadeTabagismo:%s\n",c.ComorbidadeTabagismo);

    //ComorbidadeObesidade;
    token = strtok(NULL, ",");
    strcpy(c.ComorbidadeObesidade,token);
    printf("ComorbidadeObesidade:%s\n",c.ComorbidadeObesidade);

    //FicouInternado;
    token = strtok(NULL, ",");
    strcpy(c.FicouInternado,token);
    printf("FicouInternado:%s\n",c.FicouInternado);
    }
  } 
  fclose(arq);
  return 0;
}