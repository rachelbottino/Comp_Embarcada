#include <stdio.h>
#define MAX_PROD 100

void main(){
	int p;
	int tot;
	char item[MAX_PROD][80];
	double preco[3];
	double valor;
	double subtotal;
	double pagar;
	int qtd[3];
	double imposto;
	printf("Quantos produtos diferentes: \n");
	scanf("%d, &tot);
	for (p=0; p<tot; p++){
		printf("\nNome do produto: \n");
		scanf("%s, item[p]);
		printf("\nPreço: \n");
		scanf("%lf, &preco[p]);
		printf("\nQuantidade: \n");
		scanf("%d, &qtd[p]);
	}
	printf("|  Produto  |  Preço/un  |  Quantidade  |  Pagar  |\n");
	for (p=0; p<tot; p++){
		valor = preco[p]*qtd[p];
		printf("|  %s  |  R$%lf  |  %d  |  R$%lf  |\n", item[p]. preco[p], qtd[p], valor);
		subtotal += valor;
	}
	imposto = 0.1*subtotal;
	pagar = subtotal+imposto;
	printf("|  Sub Total:    | R$%lf  |\n", subtotal);
	printf("|  Imposto 0.10: | R$%lf  |\n", imposto);
	printf("|      Total:    | R$%lf  |\n", pagar);

}