#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int task;
int N; // N empresas que ele esta a pensar em adicionar ao seu portfolio
int D; // coletou os valores diarios das acoes ao longo de D dias
int K; // nunca ter mais do que K acoes de cada empresa
int R; // taxa fixa

/**
 * John nunca pode ter mais do que K acoes de cada empresa
 * Em cada dia, John pode realizar no maximo uma transação(comprar ou vender quantas acoes quiser dessa empresa).
 * A bolsa que John usa/cobra uma taxa fixa R para cada acao(ex: se comprar 2 acoes em uma transacao sera 2 * R),
    nao havendo para a venda destas
 */

/** Tarefas
 * Tarefa 1 : imprimir o melhor lucro que John poderia ter com a negociacao de acoes de cada empresa.
 * Tarefa 2 : para cada empresa, imprimir o melhor lucro e imprimir a informacao de quantas acoes para
   comprar ou vender todos os dias para obter o melhor lucro(atribuir numeros positivos para compras e negativos para vendas)
 * Tarefa 3 : imprimir o melhor lucro e quantos esquemas de negociacao diferentes davam esse mesmo lucro (lucro numero)
    (a+b) mod  m = ((a mod  m)+(b mod  m)) mod  m para o numero de esquemas
 */

vector<vector<int>> V; // vector que em cada linha representa uma empresa e cada coluna representa um dia
int profit; // usado para imprimir o lucro total no final
vector<int> johnShares; // usado para saber quantos shares o John ja comprou de uma empresa (<= k)

void writeVector() {
    int num;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < D; j++) {
            cin >> num;
            V[i][j] = num;
        }
    }
}

void task1(){

}

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    cin >> task;

    cin >> N >> D >> K >> R;

    V = vector<vector<int>>(N, (vector<int>(D, 0)));
    johnShares = vector<int> (D, 0);
    profit = 0;

    writeVector();

    // fazer funcao para o ex ahah
    switch (task) {
    case 1:
        cout << "teste" << endl;
        
        break;
    case 2:

        break;
    case 3:

        break;
    default:
        break;
    }

    return 0;
}